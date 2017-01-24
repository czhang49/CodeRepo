var loginApp = angular.module('loginApp', ['dataService','dataService']);

loginApp.config(['$httpProvider', function ($httpProvider) {
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

loginApp.controller('login', ['$rootScope', '$scope', '$location', 'CommonData', function($rootScope, $scope, $location, dataService) {
    $scope.email = "";
    $scope.password = "";

    $scope.signup = {};
    $scope.signup.userName = "123";
    $scope.signup.email = "";
    $scope.signup.password = "";
    $scope.pwdRepeat = "";

    $scope.signin = function() {
        dataService.login($scope.email, $scope.password, function(data, status){
            if (status >= 200 && status < 300 && data) {
                var url = "http://" + $location.host() + ":" + $location.port() + "/user.html?id=" + data._id;
                window.location.href = url;
            } else {
                utils.alert('#login ul','Invalid Email or Password','alert');
            }
        });
    };

    $scope.showSignUp = function(){
        $('#signup').foundation('reveal', 'open');
    };

    $scope.signup = function() {
        if ($scope.signup.userName == "" || $scope.signup.email == "" || $scope.signup.password == ""){
            utils.alert('#form','All fields are required','alert');
            return;
        }
        if ($scope.signup.password != $scope.pwdRepeat) {
            utils.alert('#form','Repeat password not match','alert');
            return;
        }
        dataService.signup($scope.signup.userName, $scope.signup.email, $scope.signup.password, function(data, status){
            if (status >= 200 && status < 300 && data) {
                var url = "http://" + $location.host() + ":" + $location.port() + "/user.html?id=" + data._id;
                window.location.href = url;
            } else {
                utils.alert('#form','Invalid Email','alert');
            }
        });
    };

    $scope.aboutus = function(){
        $('#aboutUs').foundation('reveal', 'open');
    };
}]);