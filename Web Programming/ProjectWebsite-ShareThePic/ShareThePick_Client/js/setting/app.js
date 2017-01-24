var settingApp = angular.module('settingApp', ['ngRoute', 'dataService', 'ngAutocomplete','ngSanitize','ngFileUpload']);
settingApp.config(['$httpProvider', function ($httpProvider) {
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

settingApp.controller('nav',['$scope', 'CommonData', '$location', function($scope, dataService, $location){
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

settingApp.controller('header', ['$scope', 'CommonData', function($scope, dataService){
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

settingApp.controller('changePwd', ['$scope', 'CommonData', function($scope, dataService){
    var id = utils.getUserId();
    $scope.old = "";
    $scope.new = "";
    $scope.repeat = "";

    $scope.changePwd = function(){
        if ($scope.old == "" || $scope.new == "") {
            utils.alert('#changePasswd', 'Old and new Password required!', 'alert');
            return;
        }
        if ($scope.new != $scope.repeat) {
            utils.alert('#changePasswd', 'Repeat password not match!', 'alert');
            return;
        }
        dataService.getUser(id, function(user){
            if (user.data){
                user.data.newPassword = $scope.new;
                dataService.updateUser(id, user.data, function(data1, status){
                    if (status >= 200 && status < 300) {
                        utils.alert('#changePasswd', 'Password has been changed!', 'success');
                    } else {
                        utils.alert('#changePasswd', 'Old Password not correct!', 'alert');
                    }
                });
            }
        });
    };

    $scope.cancel = function(){
        $scope.old = "";
        $scope.new = "";
        $scope.repeat = "";
    };
}]);

settingApp.controller('changeInfo', ['$scope', 'CommonData', 'Upload', '$location', function($scope, dataService, Upload, $location){
    var id = utils.getUserId();
    $scope.data = {};
    $scope.data.name = "";
    $scope.data.email = "";
    $scope.data.description = "";
    $scope.pic = "";

    $scope.$watch('pic', function(){
        $scope.updateProfilePic($scope.pic);
    });

    var buffer = null;
    function getInfo(){
        dataService.getUser(id, function(data){
            if (data.data) {
                $scope.data.name = data.data.name;
                $scope.data.email = data.data.email;
                $scope.data.description = data.data.description;
                buffer = data.data;
            }
        });
    }

    $scope.update = function(){
        dataService.getUser(id, function(old){
            if (old.data){
                old.data.description = $scope.data.description;
                //console.log(old.data);
                dataService.updateUser(id, old.data, function(ret,status){
                    if (status >= 200 && status < 300){
                        utils.alert('#changePersonalInfo', 'Successfully updated!', 'success');
                        //console.log(ret);
                        window.location.reload();
                    } else {
                        utils.alert('#changePersonalInfo', ret.message, 'alert');
                    }
                });
            }
        });
    };

    $scope.cancel = function(){
        getInfo();
    };

    $scope.updateProfilePic = function(files){
        if (files && files.length) {
            for (var i = 0; i < files.length; i++) {
                var file = files[i];
                var fileName = file.name.replace(/[\s\.]/g,'_');
                Upload.upload({
                    url: dataService.getPicsUrl(),
                    fields: {
                        'name': fileName,
                        'event': id
                    },
                    file: file
                }).success(function (data) {
                    console.log(data.data.name);
                    dataService.getUser(id, function(user){
                        if (user && user.data) {
                            user.data.profilepic = data.data.name;
                        }
                        dataService.updateUser(id, user.data, function(ret){
                            window.location = $location.absUrl();
                        });
                    });

                });
            }
        }
    };

    getInfo();
}]);