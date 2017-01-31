
var imdbApp = angular.module("imdbApp", ["ngRoute","movieAnimations","imdbController"]);

imdbApp.config(["$routeProvider",
  function($routeProvider) {
    $routeProvider.
      when("/gallery", {
        templateUrl: "./partials/gallery.html",
	controller: "galleryController"
      }).
      when("/details/:rank", {
        templateUrl: "./partials/details.html",
	controller: "detailsController"
      }).
      when("/list", {
        templateUrl: "./partials/list.html",
	controller:"listController"
      }).
      otherwise({
        redirectTo:"/list"
      });
  }]);
