// var demoApp = angular.module('demoApp', ['demoControllers']);

var demoApp = angular.module('demoApp', ['ngRoute', 'demoControllers', 'demoServices']);

demoApp.config(['$routeProvider', function($routeProvider) {
  $routeProvider.
    when('/login', {
    templateUrl: 'partials/login-2.html',
    controller: 'loginController'
  }).
  when('/getUser', {
    templateUrl: 'partials/user.html',
    controller: 'profileController',
    resolve: {
       loggedin: checkLoggedin
    }
  }).
  when('/settings', {
    templateUrl: 'partials/settings.html',
    controller: 'SettingsController'
  }).
  when('/llamalist', {
    templateUrl: 'partials/llamalist.html',
    controller: 'LlamaListController'
  }).
  when('/llamalist', {
    templateUrl: 'partials/llamalist.html',
    controller: 'LlamaListController'
  }).
  otherwise({
    redirectTo: '/auth/login'
  });
}]);

demoApp.config(function($locationProvider, $httpProvider){
    var checkLoggedin = function($q, $timeout, $http, $location,$rootScope){
        //initialize a new promise
        var deferred = $q.defer();

        //Make an AJAX call to check if the user is logged in
        $http.get('/getUser').success(function(user){
            //authenticated
            if (user)
                deferred.resolve();
            //not authenticated
            else {
                $rootScope.message = "You need to log in";
                deferred.reject();
                $location.url('/login')
            }
        });
        return deferred.promise;
    };

   /* $httpProvider.interceptors.push(function($q, $location){
        return {
            response: function(response){
                //do something on success
                return response;
            },
            responseError: function(respose){
                if (response.status === 401)
                    $location.url('/login');
                return $q.reject(response);
            }
        };
    });*/
})


$(document).ready(function(){
    $(document).foundation();
    var $window = $(window);
    var $leftColumn = $('#leftColumn');
    var top = $leftColumn.offset().top;
    var left = $leftColumn.offset().left;
    console.log(top);
    console.log($('#rightColumn').offset().top);
    var width = $leftColumn.css('width');
    console.log(width);
    console.log($(window).width());
    if ($(window).width() > 1024) {
        $(document).on('scroll', function(){
            var scrollTop = $window.scrollTop();
            if (scrollTop >= top) {
                //console.log($leftColumn.hasClass('fixed'));
                if (!$leftColumn.hasClass('fixed')) {
                    $leftColumn.css({
                        left: left,
                        width: width
                    });
                    $leftColumn.addClass('fixed');
                }
            } else {
                if ($leftColumn.hasClass('fixed')) {
                    $leftColumn.removeClass('fixed');
                    $leftColumn.css({
                        left:0
                    });
                }
            }
        });
    }

});