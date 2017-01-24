/**
 * Created by Show on 5/9/15.
 */
var userApp = angular.module('eventApp', ['ngRoute', 'dataService', 'ngAutocomplete', 'MassAutoComplete', 'ngSanitize', '720kb.datepicker', 'ngFileUpload']);

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

userApp.controller('event', ['$scope','CommonData', 'Upload','$http','$q', function($scope, dataService, Upload, $http, $q){
    var id = utils.getEventId();
    var slideSize = 4;
    var names = [];
    var pswpElement = document.querySelectorAll('.pswp')[0];
    var pwOptions = {
        index: 0 // start at first slide
    };

    $scope.event = {};
    $scope.creater = null;
    $scope.Logo = null;
    $scope.photos = [];
    $scope.files = {};
    $scope.list_user_id = [];
    $scope.peopleCount = 0;

    $scope.canEdit = true;
    $scope.editEvent = {};

    $scope.addUserData = {};

    $scope.ac_option_delimited = {
        suggest: suggest_name_remote,
        on_error: console.log
    };

    $scope.$watch('files', function(){
        upload($scope.files);
    });

    function getEvent(){
        dataService.getEvent(id, function(data){
            if (data.data){


                $scope.event.name = data.data.name;
                $scope.event.location = data.data.location;
                setMap();
                $scope.event.date = new Date(data.data.start_date);
                $scope.event.start_date = data.data.start_date;
                $scope.event.end_date = data.data.end_date;
                $scope.event.list_user_id = data.data.list_user_id;
                $scope.event.description = data.data.description;

                dataService.getMyInfo(function(myInfo, status){
                    if (status >= 200 && status < 300 && myInfo) {
                        if (data.data.list_user_id.indexOf(myInfo._id) != -1){
                            console.log(data.data.list_user_id.indexOf(myInfo._id));
                            $scope.canEdit = true;
                        } else {
                            $scope.canEdit = false;
                            slideSize++;
                        }
                    }
                });

                setEditEvent();

                var userList = data.data.list_user_id;
                var createrId = data.data.list_user_id[0];

                //get creater
                dataService.getUser(createrId, function(data){
                    if (data.data) {
                        $scope.creater = data.data;
                    }
                });
                //get UserList
                $scope.peopleCount = 0;
                $scope.list_user_id = [];
                var count = 0;
                var defs = [];
                userList.forEach(function(val){
                    (function(index){
                        var def = $q.defer();
                        if (index % slideSize == 0) {
                            $scope.list_user_id.push([]);
                        }
                        dataService.getUser(val, function(data){
                            if (data.data) {
                                data.data.profileUrl = dataService.getPicsUrl() + '/getImage/' + (data.data.profilepic ? data.data.profilepic : "defaultProfile.jpg");
                                $scope.list_user_id[Math.floor(index / slideSize)].push(data.data);
                                $scope.peopleCount++;
                            }
                            def.resolve();
                        });
                        defs.push(def.promise);
                    })(count++);
                });
                if (defs.length == 0) {
                    $scope.list_user_id.push([]);
                }
                var promise = $q.all(defs);
                promise.then(function(){
                    $(document).foundation('orbit', 'reflow');
                });
            }
        });
    }

    $scope.updateEvent = function(){
        dataService.updateEvent(id, $scope.editEvent, function(data,status){
            if (status >= 200 & status < 300) {
                $('#eventEditModal').foundation('reveal', 'close');
                getEvent();
                getPhotos();
            } else {
                utils.alert('#eventEditModal', data.message, 'alert');
            }
        });
    };

    $scope.cancelUpdate = function(){
        $('#eventEditModal').foundation('reveal', 'close');
        setEditEvent();
    };

    $scope.addUser = function(){
        var userIds = [];
        var defs = [];
        $scope.addUserData.value.split(',').forEach(function(val){
            var def = $q.defer();
            dataService.getUserIdByName(val.trim(), function(data){
                if (data.data) {
                    data.data.forEach(function(user){
                        userIds.push(user._id);
                    });
                }
                def.resolve();
            });
            defs.push(def.promise);
        });
        var promise = $q.all(defs);
        promise.then(function(){
            dataService.getEvent(id, function(data){
                if(data.data){
                    userIds.forEach(function(id){
                        data.data.list_user_id.push(id);
                    });
                    dataService.updateEvent(id, data.data, function(ret, status){
                        if (status >= 200 && status < 300) {
                            getEvent();
                            getPhotos();
                            $('#addUserModal').foundation('reveal', 'close');
                            $(document).foundation('orbit', 'reflow');
                        } else {
                            utils.alert('#addUserModal', ret.message, 'alert');
                        }
                    });
                }
            });
        });
    };

    $scope.cancelAddUser = function(){
        $scope.addUserData = "";
        $('#addUserModal').foundation('reveal', 'close');
    };

    $scope.showImage = function(id){
        pwOptions.index = id;
        var gallery = new PhotoSwipe(pswpElement, PhotoSwipeUI_Default, $scope.photos, pwOptions);
        gallery.init();
    };

    $scope.deleteImage = function(idx) {
        dataService.deletePhoto($scope.photos[idx].name, function(data){
            getPhotos();
        });
    };

    $scope.removeUser = function(uid) {
        dataService.getEvent(id,function(data){
            if(data.data) {
                data.data.list_user_id = data.data.list_user_id.filter(function(val){
                    return val != uid;
                });
                dataService.updateEvent(id, data.data, function(ret){
                    console.log(ret);
                    if (ret.data) {
                        getEvent();
                        $(document).foundation('orbit', 'reflow');
                    }
                });
            }
        });
    };

    function setMap(){
        var map;
        var addresses = $scope.event.location;
        $.getJSON('http://maps.googleapis.com/maps/api/geocode/json?address='+addresses+'&sensor=false', null, function (data) {
            var p = data.results[0].geometry.location
            var latlng = new google.maps.LatLng(p.lat, p.lng);
            var myOptions = {
                zoom: 15,
                center: latlng,
            };
            map = new google.maps.Map($('#map-canvas')[0], myOptions);
            new google.maps.Marker({
                position: latlng,
                map: map
            });
        });
    }

    function upload(files){
        if (files && files.length) {
            var uploadModal = $('#uploadModal');
            uploadModal.html("<h2>Uploading " + files.length + " files....</h2>");
            for (var i = 0; i < files.length; i++) {
                var file = files[i];
                var fileName = file.name.replace(/[\s\.]/g,'_');
                uploadModal.append('<div class="progress alert">'
                                    + '<span class="meter" id="' + fileName + '" style="width:0%">' + file.name + '</span>'
                                    + '</div>');
                (function(idtag){
                    Upload.upload({
                        url: dataService.getPicsUrl(),
                        fields: {
                            'name': fileName,
                            'event': id
                        },
                        file: file
                    }).progress(function (evt) {
                        var progressPercentage = parseInt(100.0 * evt.loaded / evt.total);
                        updateProgress('#'+idtag, progressPercentage);
                    }).success(function () {
                        finishiUploadBar('#'+idtag);
                        getPhotos();
                        updateUserPhotoCount(files.length);
                    });
                })(fileName);
            }
            uploadModal.append($('<a class="close-reveal-modal" aria-label="Close">&#215;</a>'));
            uploadModal.foundation('reveal', 'open');
        }
    }

    function updateUserPhotoCount(val){
        dataService.getMyInfo(function(myinfo){
            dataService.getUser(myinfo._id, function(data, status){
                if (status >= 200 && status < 300 && data) {
                    data.number_photo += val;
                    dataService.updateUser(data._id,data,function(){});
                }
            });
        });
    }

    function updateProgress(selector, progress){
        var $span = $(selector);
        $span.css('width', progress + '%');
    }

    function finishiUploadBar(selector) {
        var $span = $(selector);
        $span.html($span.html() + " Finished!");
        $span.parent().removeClass('alert');
        $span.parent().addClass('success');
    }

    function getPhotos(){
        dataService.getPhotosByEvent(id, function(data){
            if (data.data) {
                data.data = data.data.filter(function(val){
                    val.url = dataService.getPicsUrl() + '/getImage/' + val.name;
                    return val.name != undefined;
                });
                //$scope.photos = data.data;
                $scope.photos = [];
                data.data.forEach(function(photo){
                    $scope.photos.push({
                        src: dataService.getPicsUrl() + '/getImage/' + photo.name,
                        w:500,
                        h:500,
                        title:photo.description,
                        name: photo.name
                    });
                });
                $scope.logo = $scope.photos[0];
            }
        });
    }

    function setEditEvent(){
        $scope.editEvent.name = $scope.event.name;
        $scope.editEvent.start_date = $scope.event.start_date;
        $scope.editEvent.end_date = $scope.event.end_date;
        $scope.editEvent.location = $scope.event.location;
        $scope.editEvent.description = $scope.event.description;
        $scope.editEvent.list_user_id = $scope.event.list_user_id;
    }

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

    getEvent();
    getPhotos();

}]);