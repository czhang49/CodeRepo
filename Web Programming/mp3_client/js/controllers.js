var demoControllers = angular.module('demoControllers', []);


demoControllers.controller('AddUserController', ['$scope', '$http','CommonUsers','$window', function($scope, $http,CommonUsers,$window) {
    $scope.displayText='';

    $scope.setUser = function(username,useremail){

    $scope.dataObj={name: username,
		    email:useremail};
    CommonUsers.setUser($scope.dataObj).success(function(data,status,headers){}).error(function(data, status, headers, config){});
	$scope.displayText='User Created';
  };

}]);


demoControllers.controller('AddTaskController', ['$scope', '$http','CommonTasks','$window', function($scope, $http,CommonTasks,$window) {
    $scope.displayText='';
    var comple=false;

    $scope.setCompleted=function(){comple=true;};	
    $scope.setPending=function(){comple=false;};

    $scope.setTask = function(taskname,taskdescription,taskDL){

    $scope.dataObj={name: taskname,
		    description:taskdescription,
		    deadline:taskDL,
   		    completed: comple};
    CommonTasks.setTask($scope.dataObj).success(function(data,status,headers){}).error(function(data, status, headers, config){});
	$scope.displayText='Task Created';
  };

}]);




demoControllers.controller('TaskViewController', ['$scope' , 'CommonTasks','$http','$window',function($scope,CommonTasks,$http,$window) {

    var baseUrl = $window.sessionStorage.baseurl;

   CommonTasks.getTask().success(function(AllTasks){
    $scope.tasks = AllTasks.data;
    });

   $scope.showPending=function(){
    $http({
  	url: baseUrl+'/api/tasks?where={"completed":false}',
 	method: "GET",
	}).success(function(pendingtasks){  $scope.tasks=pendingtasks.data;});
    };
   $scope.showCompleted=function(){
      $http({
  	url: baseUrl+'/api/tasks??where={"completed":true}',
 	method: "GET",
	}).success(function(completedtasks){  $scope.tasks=completedtasks.data;});
      };
   $scope.showAll=function(){
      CommonTasks.getTask().success(function(AllTasks){
         $scope.tasks = AllTasks.data;
      });
   };

$scope.DeleteTask=function(task_id){

   CommonTasks.deleteTask(task_id).success(function(data,status,headers){
     CommonTasks.getTask().success(function(AllTasks){
      $scope.tasks = AllTasks.data; 
     });
   }).error(function(data, status, headers, config){});
  
  };
}]);


demoControllers.controller('UserViewController', ['$scope', 'CommonUsers' , function($scope, CommonUsers) {

  CommonUsers.getUser().success(function(AllUsers){
    $scope.users = AllUsers.data;
  });
  
  $scope.DeleteUser=function(user_id){

   CommonUsers.deleteUser(user_id).success(function(data,status,headers){
     CommonUsers.getUser().success(function(AllUsers){
      $scope.users = AllUsers.data;
     });
   }).error(function(data, status, headers, config){});
  
  };

}]);

demoControllers.controller('SettingsController', ['$scope' , '$window' , function($scope, $window) {
  $scope.url = $window.sessionStorage.baseurl;

  $scope.setUrl = function(){
    $window.sessionStorage.baseurl = $scope.url; 
    $scope.displayText = "URL set";

  };

}]);


demoControllers.controller('DetailUserController', ['$scope', 'CommonUsers' ,'CommonTasks',"$routeParams",'$http','$window', function($scope, CommonUsers,CommonTasks,$routeParams,$http,$window) {
	
  var baseUrl = $window.sessionStorage.baseurl;
  CommonUsers.getOneUser($routeParams._id).success(function(OneUser){
	$scope.user=OneUser.data;
	$scope.userpendingTasksID=OneUser.data.pendingTasks;
         

     $http({
  	url: baseUrl+'/api/tasks?where={"_id":{"$in":'+JSON.stringify($scope.userpendingTasksID)+'},"completed": false}',
 	method: "GET",
	}).success(function(data_pendingtasks){      $scope.userpendingTasks=data_pendingtasks.data; });

     });




      $scope.markcomplete=function(task_id){
	 CommonTasks.getOneTask(task_id).success(function(data,status,headers){ 
         $scope.dataObj=data.data;
	 $scope.dataObj.completed=true;
      
         CommonTasks.putTask(task_id,$scope.dataObj).success(function(data,status,headers){});

        $http({
  	  url: baseUrl+'/api/tasks?where={"_id":{"$in":'+JSON.stringify($scope.userpendingTasksID)+'},"completed": false}',
 	  method: "GET",
	 }).success(function(data_pendingtasks){        $scope.userpendingTasks=data_pendingtasks.data; });

	location.reload();
      })};


	// because of some mis understanding, all the tasks are called pending task.
      $scope.showcomplete=function(){
	$http({
  	url: baseUrl+'/api/tasks?where={"_id":{"$in":'+JSON.stringify($scope.userpendingTasksID)+'},"completed": true}',
 	method: "GET",
	}).success(function(data_completedtasks){    $scope.usercompletedTasks=data_completedtasks.data; });
     
      };

}]);




demoControllers.controller('DetailTaskController', ['$scope', 'CommonUsers' ,'CommonTasks',"$routeParams",'$http','$window', function($scope, CommonUsers,CommonTasks,$routeParams,$http,$window) {

	var Doer_ID;
	var baseUrl = $window.sessionStorage.baseurl;
  	CommonTasks.getOneTask($routeParams._id).success(function(OneTask){
	$scope.task=OneTask.data; var Doer_ID=OneTask.data.assignedUser;

        $http({
  	 url: baseUrl+'/api/users?where={"_id":'+JSON.stringify(Doer_ID)+'}',
 	 method: "GET",
	 }).success(function(task_doer){     $scope.Doer=task_doer.data;});

	 });


       

}]);



demoControllers.controller('EditTaskController', 'CommonTasks',['$scope', 'CommonUsers' , function($scope, CommonUsers,CommonTasks) {

  CommonUsers.getUser().success(function(AllUsers){
    $scope.users = AllUsers.data;
  });

    var comple=false;

    $scope.setCompleted=function(){comple=true;};	
    $scope.setPending=function(){comple=false;};

    $scope.setTask = function(taskname,taskdescription,taskDL){

    $scope.dataObj={name: taskname,
		    description:taskdescription,
		    deadline:taskDL,
   		    completed: comple};
    CommonTasks.putTask($scope.dataObj).success(function(data,status,headers){}).error(function(data, status, headers, config){});
	$scope.displayText='Task Created';
  };

}]);
