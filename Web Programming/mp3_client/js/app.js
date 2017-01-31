// var demoApp = angular.module('demoApp', ['demoControllers']);

var demoApp = angular.module('demoApp', ['ngRoute', 'demoControllers', 'demoServices']);

demoApp.config(['$routeProvider',function($routeProvider) {
  $routeProvider.
   when('/edittaskview', {
    templateUrl: 'partials/edittaskview.html',
    controller: 'EditTaskController'
  }).
    when('/adduserview', {
    templateUrl: 'partials/adduserview.html',
    controller: 'AddUserController'
  }).
  when('/addtaskview', {
    templateUrl: 'partials/addtaskview.html',
    controller: 'AddTaskController'
  }).
  when('/taskview', {
    templateUrl: 'partials/taskview.html',
    controller: 'TaskViewController'
  }).
  when('/settings', {
    templateUrl: 'partials/settings.html',
    controller: 'SettingsController'
  }).
  when('/userview', {
    templateUrl: 'partials/userview.html',
    controller: 'UserViewController'
  }).
  when('/detailuserview/:_id',{
   templateUrl: 'partials/detailuserview.html',
    controller: 'DetailUserController'
  }).
  when('/detailtaskview/:_id',{
   templateUrl: 'partials/detailtaskview.html',
    controller: 'DetailTaskController'
  }).
  otherwise({
    redirectTo: '/settings'
  });


   
}]);



var app= angular.module('app', [
      '720kb.datepicker'
      ]);

