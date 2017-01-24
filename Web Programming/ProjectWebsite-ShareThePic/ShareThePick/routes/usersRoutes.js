// Get the packages we need
var express = require('express');
var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var fs=require('fs');
var router = express.Router();

var User=require('./../models/users');
var multer=require('multer');
var path = require('path');

router.use(multer({dest: './upload/',
    rename: function (fieldname, filename){
        return filename + Date.now();
    },
    onFileUploadStart: function (file) {
        console.log(file.originalname+ 'is starting ..')
    },
    onFileUploadComplete: function(file){
        console.log(file.fieldname +'uploaded to ' + file.path);
        file_name=file.name;
        file_path=file.path;
        done=true;
    }
}));

//
var homeRoute = router.route('/');

// This part starts the users Routes

homeRoute
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

	var flag = false;
	if (req.body.name == null || req.body.name == undefined){
		flag = true;
	}
	if (req.body.email == null || req.body.email == undefined){
		flag = true;
	}

	user.name=req.body.name;
	user.email=req.body.email;
	user.description=req.body.description;
	user.location=req.body.location;
	user.date_created=req.body.date_created;
	user.number_photo=req.body.number_photo;
	user.list_event=req.body.list_event;
//	user.profilepic=fs.readFileSync('smallpic.jpg');
	user.profilepic=req.body.profilepic;

	if(flag){
		res.status(400);
		toSend = {
			message: "Name or email not give",
			data:[]
		}
		res.send(toSend);
	}
	else{
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
  }
})

.options(function(req, res){
      res.writeHead(200);
      res.end();
});

var usersIDRoute = router.route('/:user_id');

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
            if(req.body.name != undefined){
                user.name=req.body.name;
            }
            if(req.body.description != undefined){
                user.description=req.body.description;
            }

            if(req.body.password != undefined){
                if(req.body.newPassword == undefined){
                    user.password =req.body.password;
                }else{
                    user.password = user.generateHash(req.body.newPassword);
                }
            }

            if(req.body.location != undefined){
                user.location=req.body.location;
            }

            if(req.body.profilepic != undefined){
                user.profilepic = req.body.profilepic;
            }

            if(req.body.number_photo != undefined){
                user.number_photo = req.body.number_photo;
            }


			user.save(function(err){
				if (err){
					res.status(500);
					res.json({message:'There is a server error when updating'});
					res.send(err);
				}else{
					res.status(201);
					res.json({message:'User Updated',data:user});
				}
			});
		}
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
		res.json({message:'Successfully deleted user'});
		}
	});
});

module.exports=router;
