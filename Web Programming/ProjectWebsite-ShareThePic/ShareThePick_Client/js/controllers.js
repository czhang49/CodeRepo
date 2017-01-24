var demoControllers = angular.module('demoControllers', []);

demoControllers.controller('loginController', function($scope, $rootScope, $http, $location){
    $scope.user = {};

    //register the login() function used in form
    $scope.login = function(){
        $http.post('/login',{
            email: $scope.user.email,
            password: $scope.user.password
        })
            .success(function(user){
                //no error: authentication OK
                $rootScope.message = 'Authentication successful';
                $location.url('/getUser');
            })
            .error(function(){
                $rootscope.message = 'Authentication failed';
                $location.url('/login');
            })
    };

});

demoControllers.controller('profileController', function(){

});


/*demoControllers.controller('FirstController', ['$scope', 'CommonData'  , function($scope, CommonData) {
  $scope.data = "";
   $scope.displayText = ""

  $scope.setData = function(){
    CommonData.setData($scope.data);
    $scope.displayText = "Data set"

  };

}]);

demoControllers.controller('SecondController', ['$scope', 'CommonData' , function($scope, CommonData) {
  $scope.data = "";

  $scope.getData = function(){
    $scope.data = CommonData.getData();

  };

}]);


demoControllers.controller('LlamaListController', ['$scope', '$http', 'Llamas', '$window' , function($scope, $http,  Llamas, $window) {

  Llamas.get().success(function(data){
    $scope.llamas = data;
  });


}]);

demoControllers.controller('SettingsController', ['$scope' , '$window' , function($scope, $window) {
  $scope.url = $window.sessionStorage.baseurl;

  $scope.setUrl = function(){
    $window.sessionStorage.baseurl = $scope.url; 
    $scope.displayText = "URL set";

  };

}]);*/

