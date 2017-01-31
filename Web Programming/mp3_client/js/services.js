// js/services/todos.js
angular.module('demoServices', [])
        .factory('CommonUsers', function($http,$window){
	var baseUrl = $window.sessionStorage.baseurl;
        var Userdata = "";
        
	return{
            getUser : function(){
                Userdata=$http.get(baseUrl+'/api/users');
                return Userdata;
            },
            setUser : function(newUser){
		var thepost= $http({
  			url: baseUrl+'/api/users',
  			method: "POST",
  			data: $.param(newUser),
  			headers: {
    			'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
  			}
		});
		return thepost;             
            },
	    deleteUser: function(user_id){
		alert(user_id);
		var thedelete=$http({
			url: baseUrl+'/api/users/'+user_id,
			method: "DELETE"
		});
		return thedelete;
            },
	     getOneUser: function(user_id){

		var theoneuser=$http({
			url: baseUrl+'/api/users/'+user_id,
			method:"GET"
		});
		return theoneuser;		
	    }
         }
     })
    .factory('CommonTasks', function($http, $window) { 
	var baseUrl = $window.sessionStorage.baseurl;
        var Taskdata = "";
        
	return {
            getTask : function() {
                Taskdata=$http.get(baseUrl+'/api/tasks');
                return Taskdata;
            },
            putTask: function(task_id,taskrenew){
	           var putthetask=$http({
			url:baseUrl+'/api/tasks/'+task_id,
			method:"PUT",
 			data: $.param(taskrenew),
  			headers: {
    			'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
  			}
                    });
	            return putthetask;
	    },
	   getOneTask: function(task_id){

		var theonetask=$http({
			url: baseUrl+'/api/tasks/'+task_id,
			method:"GET"
		});
		return theonetask;		
	    },
	    deleteTask: function(task_id){
		var thedelete=$http({
			url: baseUrl+'/api/tasks/'+task_id,
			method: "DELETE"
		});
		return thedelete;
            },
	    setTask : function(newTask){
		var thepost= $http({
  			url: baseUrl+'/api/tasks',
  			method: "POST",
  			data: $.param(newTask),
  			headers: {
    			'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
  			}
		});
		return thepost;             
            }
	}
    });
