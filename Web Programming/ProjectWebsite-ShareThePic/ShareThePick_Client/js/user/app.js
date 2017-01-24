/**
 * Created by Show on 5/6/15.
 */
var userApp = angular.module('userApp', ['ngRoute', 'dataService', 'ngAutocomplete', 'MassAutoComplete', 'ngSanitize', '720kb.datepicker']);
userApp.config(['$httpProvider', function ($httpProvider) {
    $httpProvider.interceptors.push(['$q', '$location', function($q, $location) {
        $httpProvider.defaults.withCredentials = true;
        return {
            'request': function (config) {
                config.headers = config.headers || {};
                return config;
            },
            'responseError': function(response) {
                if(response.status === 401 || response.status === 403) {
                    $location.path('/');
                }
                return $q.reject(response);
            }
        };
    }]);
}]);
userApp.controller('nav',['$scope', 'CommonData', '$location', function($scope, dataService, $location){
    $scope.me = null;
    dataService.getMyInfo(function(data,status){
        if (status >= 200 && status < 300 && data) {
            $scope.me = data;
        }
    });
    $scope.logout = function(){
        dataService.logout(function(){
            window.location = "http://" + $location.host() + ":" + $location.port();
        });
    }
}]);

userApp.controller('leftColumns', ['$scope', 'CommonData', function($scope, dataService){
    var id = utils.getUserId();
    $scope.userData = null;
    $scope.friends = [];
    $scope.profiles = [];
    $scope.list_event = [];
    $scope.getUserUrl = function(id){
        return "./user.html?id=" + id;
    };
    $scope.getImageUrl = function(id){
        return dataService.getImageUrl(id?id:'defaultProfile.jpg');
    };
    var getUserData = function(){
        dataService.getUser(id, function(data){
            if (data.data) {
                $scope.userData = data.data;
                $scope.profileImage = dataService.getImageUrl($scope.userData.profilepic);
            }
        });
    };
    var getFriends = function(){
        var a = [];
        dataService.getFriends(id,function(data){
            data.forEach(function(uid){
                a.push(uid);
                //dataService.getUser(uid, function(user){
                //    $scope.friends.push(user);
                //});
            });
            a.forEach(function(val, idx, array){
                dataService.getUser(val, function(data){
                    $scope.friends.push(data.data);
                });
            });
        });


    };
    var getEvents = function(){
        dataService.getEventByUserId(id, function(data){
            if (data && data.data) {
                $scope.list_event = data.data;
            }
        });
    };
    getUserData();
    getFriends();
    getEvents();
}]);

userApp.controller('header', ['$scope', 'CommonData', function($scope, dataService){
    var id = utils.getUserId();
    $scope.userData = null;
    $scope.profileImage = null;
    var getUserData = function(){
        dataService.getUser(id, function(data){
            if (data.data) {
                $scope.userData = data.data;
                $scope.profileImage = dataService.getImageUrl($scope.userData.profilepic ? $scope.userData.profilepic : 'defaultProfile.jpg');
            }
        });
    };

    getUserData();
}]);

userApp.controller('addEvent', ['$scope', 'CommonData', '$q', '$http', '$location', function($scope, dataService, $q, $http, $location){
    var id = utils.getUserId();
    $scope.name = "";
    $scope.people = {};
    $scope.location = "";
    $scope.date ="";
    $scope.description = "";

    $scope.show = false;

    var names = [];

    dataService.getMyInfo(function(data){
        $scope.show = data && data._id && data._id == id;
    });

    $scope.addEvent = function(){
        var data = {};
        data.name = $scope.name;
        data.start_date = $scope.date;
        data.end_data = $scope.date;
        data.list_user_id = [id];
        console.log($scope.people);
        var list_user_id =  $scope.people.value ? $scope.people.value.split(',') : [];
        var promises = [];
        list_user_id.forEach(function(val){
            var def = $q.defer();
            dataService.getUserIdByName(val.trim(), function(ret){
                if (ret.data) {
                    ret.data.forEach(function(val){
                        data.list_user_id.push(val._id);
                    });
                }
                def.resolve();
            });
            promises.push(def.promise);
        });
        var deffered = $q.all(promises);
        data.location = $scope.location;
        data.description = $scope.description;
        deffered.then(function(){
            dataService.createEvent(data, function(ret, status){
                if (status >= 200 && status < 300) {
                    //update each user's event list
                    data.list_user_id.forEach(function(val){
                        dataService.getUser(val, function(user){
                            if(user && user.data) {
                                user.data.list_event.push(ret.data._id);
                                dataService.updateUser(val, data, function(d){
                                });
                            }
                        });
                    });

                    $scope.cancel();
                    $('#addEvent').append('<div data-alert class="alert-box success radius">Event has been successfully added! <a href="#" class="close">&times;</a> </div>');
                    $(document).foundation('alert', 'reflow');
                    window.location = "http://" + $location.host() + ":" + $location.port() + "/event.html?id=" + ret.data._id;
                } else {
                    $('#addEvent').append('<div data-alert class="alert-box alert radius">' + ret.message + '<a href="#" class="close">&times;</a> </div>');
                    $(document).foundation('alert', 'reflow');
                }
            });
        });
    };

    $scope.cancel = function(){
        $scope.name = "";
        $scope.people = {};
        $scope.location = "";
        $scope.date ="";
        $scope.description = "";
        console.log(123);
    };

    $scope.ac_option_delimited = {
        suggest: suggest_name_remote,
        on_error: console.log
    };


    function suggest_name() {
        var result = [];
        for (var i = 0; i < names.length && i < 10; i++) {
            var val = names[i];
            result.push({"label":val.name + '(' + val.email + ')', "value":val.name});
        }
        return result;
    }

    function suggest_name_delimited(term) {
        var ix = term.lastIndexOf(','),
            lhs = term.substring(0, ix + 1),
            rhs = term.substring(ix + 1).trim(),
            suggestions = suggest_name(rhs);
        suggestions.forEach(function (s) {
            s.value = lhs + s.value;
        });
        return suggestions;
    }

    function suggest_name_remote(term){
        var ix = term.lastIndexOf(','),
            rhs = term.substring(ix + 1).trim();
        var deferred = $q.defer();
        dataService.getUserList(rhs, function(data){
            names = data.data;
            deferred.resolve(suggest_name_delimited(term));
            setAcLocation();
        });
        return deferred.promise;
    }

    function setAcLocation(){
        var $acContainer = $('.ac-container');
        $acContainer.css({left:0, top:37});
    }

}]);
userApp.controller('timeLine', ['$scope', 'CommonData', '$location', function($scope, dataService, $location){
    var id = utils.getEventId();
    $scope.list_event = [];
    var previousMonth = "";
    var getEvents = function(){
        dataService.getEventByUserId(id, function(data){
            if (data && data.data) {
                data.data.forEach(function(event){
                    dataService.getFullEvent(event, function(fullEvent){
                        var month = new Date(fullEvent.event.start_date).getMonth();
                        if (month != previousMonth) {
                            $scope.list_event.push([]);
                        }
                        previousMonth = month;
                        $scope.list_event[$scope.list_event.length - 1].push(fullEvent);
                    });
                });
            }
        });
    };
    $scope.getEventUrl = function(eventId){
        return "http://" + $location.host() + ":" + $location.port() + "/event.html?id=" + eventId;
    };
    $scope.getUserUrl = function(userId) {
        return "http://" + $location.host() + ":" + $location.port() + "/user.html?id=" + userId;
    };
    $scope.getUserProfileUrl = function(profile){
        return dataService.getPicsUrl() + "/getImage/" + (profile ? profile : 'defaultProfile.jpg');
    };
    $scope.getPhotoUrl = function(file){
        return dataService.getPicsUrl() + "/getImage/" + (file ? file : 'defaultProfile.jpg');
    };
    $scope.getLocaleDate = function(dateStr) {
        return new Date(dateStr).toLocaleDateString();
    };
    $scope.getMonth = function(date){
        return ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sept','Oct','Nov','Dec'][new Date(date).getMonth()];
    }
    getEvents();
}]);