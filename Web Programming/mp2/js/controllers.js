var imdbController = angular.module('imdbController', []);

imdbController.controller("listController", ['$scope', '$http', function($scope, $http) {
   $http.get('./data/imdb250.json').success(function(data) {
     $scope.movies = data;
     
     $scope.reverse=1;
     $scope.changeSort1=function(){
	$scope.reverse=1;
	return;
     }
     $scope.changeSort2=function(){
	$scope.reverse=0;
	return;
     }
   });
 }]);


imdbController.controller("galleryController", ['$scope', "$filter",'$http', function($scope,$filter, $http) {
   $http.get('./data/imdb250.json').success(function(data) {
     $scope.movies = data;

   $scope.PicCategory1=function(){
	$scope.gooddata=data;
	return;
   }
   $scope.PicCategory2=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Crime"});
	return;
   }
   $scope.PicCategory3=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Drama"});
	return;
   }
   $scope.PicCategory4=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"History"});
	return;
   }
   $scope.PicCategory5=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Western"});
	return;
   }
   $scope.PicCategory6=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Biography"});
	return;
   }
   $scope.PicCategory7=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Romance"});
	return;
   }
   $scope.PicCategory8=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Adventure"});
	return;
   }
   $scope.PicCategory9=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Comedy"});
	return;
   }
   $scope.PicCategory10=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Action"});
	return;
   }
   $scope.PicCategory11=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Thriller"});
	return;
   }
   $scope.PicCategory12=function(){
	$scope.gooddata=$filter("filter")(data,{genre:"Mystery"});
	return;
   }

   });
 }]);

imdbController.controller("detailsController", ['$scope', "$filter","$routeParams",'$http', function($scope, $filter,$routeParams,$http) {
   $http.get("./data/imdb250.json").success(function(data) {

   var datagood=$filter("filter")(data,{rank:$routeParams.rank})[0];
   $scope.movie = datagood;
  
   $scope.prevMovie = $scope.movie.rank-1;
   $scope.nextMovie = $scope.movie.rank+1;
  
   if ($scope.movie.rank==1){
	$scope.prevMovie=250;
   }
   if ($scope.movie.rank==250){
	$scope.nextMovie=1;
   }

  });
}]);


//////////////////////////////////////////////////////////////

