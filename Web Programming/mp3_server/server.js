// Get the packages we need
var express = require('express');
var mongoose = require('mongoose');
var Llama = require('./models/llama');
var bodyParser = require('body-parser');
var router = express.Router();

//replace this with your Mongolab URL
mongoose.connect('mongodb://czhang49:Zc630920@ds063899.mongolab.com:63899/mp3_server');
var User=require('./models/users');
var Task=require('./models/tasks');

// Create our Express application
var app = express();

// Use environment defined port or 4000
var port = process.env.PORT || 4000;

//Allow CORS so that backend and frontend could pe put on different servers
var allowCrossDomain = function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "X-Requested-With, X-HTTP-Method-Override, Content-Type, Accept");
  res.header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE");
  next();
};
app.use(allowCrossDomain);

// Use the body-parser package in our application
app.use(bodyParser.urlencoded({
  extended: true
}));

// All our routes will start with /api
app.use('/api', router);

//Default route here
var homeRoute = router.route('/');

homeRoute.get(function(req, res) {
  res.json({ message: 'Hello World! aab' });
});

//Llama route 
var llamaRoute = router.route('/llamas');

llamaRoute.get(function(req, res) {
  res.json([{ "name": "alice", "height": 12 }, { "name": "jane", "height": 13 }]);
});

//users route
var usersRoute = router.route('/users');

usersRoute
.get(function(req,res){
	var QueryWhere = eval("("+req.query.where+")");
	var QuerySort = eval("("+req.query.sort+")");
	var QuerySelect = eval("("+req.query.select+")");
	var QuerySkip = eval("("+req.query.skip+")");
	var QueryLimit = eval("("+req.query.limit+")");
	var QueryCount = eval("("+req.query.count+")");

	User.find(QueryWhere).sort(QuerySort).select(QuerySelect).skip(QuerySkip).limit(QueryLimit).exec(function(err,users){
		if(err){
			res.status(500);
			res.json({message:'There is a server error'});
			res.send(err);
		}else{
		res.status(200);
		res.json({message:'All the users are listed',data:users});}

	});

})
.post(function(req,res){
	var user=new User();
	user.name=req.body.name;
	user.email=req.body.email;
	user.pendingTasks=req.body.pendingTasks;
 	user.save(function(err){
		if(err){
			res.status(404);
			return console.error(err);
			
		}
		else{
			res.status(201);
			res.json({message:'The new user is created',data:user});
		}
	});
})
.options(function(req, res){
      res.writeHead(200);
      res.end();
});

var usersIDRoute = router.route('/users/:user_id');

usersIDRoute
.get(function(req,res){
	User.findById(req.params.user_id,function(err,user){
		if(err){
			res.status(404);
			res.json({message:'The user is not found'});
			res.send(err);
		}
		else{
		res.status(200);
		res.json({message:'The user is found',data:user});}
	});
})
.put(function(req,res){
	User.findById(req.params.user_id,function(err,user){
		if(err){
			res.status(404);
			res.json({message:'The user is not found'});
			res.send(err);
		}else{
		user.name=req.body.name;
		user.email=req.body.email;
		user.pendingTasks=req.body.pendingTasks;
		
		user.save(function(err){		
			if (err){
				res.status(500);
				res.json({message:'There is a server error when updating'});
				res.send(err);
			}else{
			res.status(201);
			res.json({message:'User Updated',data:user});}
		});}
	});
})
.delete(function(req,res){
	User.remove({
		_id:req.params.user_id
	},function(err,user){
		if(err){
			res.status(404);
			res.json({message:'The user does not exit'});
			res.send(err);
		}else{
		res.json({message:'Successfully deleted user'});}
	});
});


//Taks Route
var tasksRoute = router.route('/tasks');

tasksRoute
.get(function(req,res){
	var QueryWhere = eval("("+req.query.where+")");
	var QuerySort = eval("("+req.query.sort+")");
	var QuerySelect = eval("("+req.query.select+")");
	var QuerySkip = eval("("+req.query.skip+")");
	var QueryLimit = eval("("+req.query.limit+")");
	var QueryCount = eval("("+req.query.count+")");

	Task.find(QueryWhere).sort(QuerySort).select(QuerySelect).skip(QuerySkip).limit(QueryLimit).exec(function(err,tasks){
		if(err){
			res.status(404);
			return console.error(err);
		}else{
		res.status(200);
		res.json({message:'All the tasks are listed',data:tasks});}

	});

})
.post(function(req,res){
	var task=new Task();
	task.name=req.body.name;
	task.description=req.body.description;
	task.deadline=req.body.deadline;
	task.completed=req.body.completed;
	task.assignedUser=req.body.assignedUser;
	task.assginedUserName=req.body.assginedUserName;

 	task.save(function(err){
		if(err){
			res.json({message:'There is a server error'});
			res.send(err);
			res.status(500).end();
		}else{
		res.status(201);
		res.json({message:'The new task is created',data:task});}
	});
})
.options(function(req, res){
      res.writeHead(200);
      res.end();
});


var tasksIDRoute = router.route('/tasks/:task_id');

tasksIDRoute
.get(function(req,res){
	Task.findById(req.params.task_id,function(err,task){
		if(err){
			res.status(404);
			res.json({message:'The task is not found'});
			res.send(err);
		}else{
		res.status(200);
		res.json({message:'The task is found',data:task});}
	});
})
.put(function(req,res){
	Task.findById(req.params.task_id,function(err,task){
		if(err){
			res.status(404);
			res.json({message:'The task is not found'});
			res.send(err);
		}else{
		task.name=req.body.name;
		task.description=req.body.description;
		task.deadline=req.body.deadline;
		task.completed=req.body.completed;
		task.assignedUser=req.body.assignedUser;
		task.assginedUserName=req.body.assginedUserName;
		
		task.save(function(err){		
			if (err){
				res.status(500);
				res.json({message:'There is a server error when updating'});
				res.send(err);
			}else{
			res.status(201);
			res.json({message:'Task Updated',data:task});}
		});}
	});
})
.delete(function(req,res){
	Task.remove({
		_id:req.params.task_id
	},function(err,task){
		if(err){
			res.status(404);
			res.json({message:'The task does not exit'});
			res.send(err);
		}
		else{
		res.json({message:'Successfully deleted task'});}
	});
});

// Start the server
/*app.get('/', function(req, res){
  res.send('_id: '+req.query.where);
});*/
app.listen(port);
console.log('Server running on port ' + port); 
