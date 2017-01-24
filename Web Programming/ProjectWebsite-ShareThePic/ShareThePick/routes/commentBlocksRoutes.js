// Get the packages we need
var express = require('express');
var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var fs=require('fs');
var router = express.Router();

var CommentBlock=require('./../models/commentBlocks');

//
var homeRoute = router.route('/');


homeRoute
.get(function(req,res){
	var QueryWhere = eval("("+req.query.where+")");
	var QuerySort = eval("("+req.query.sort+")");
	var QuerySelect = eval("("+req.query.select+")");
	var QuerySkip = eval("("+req.query.skip+")");
	var QueryLimit = eval("("+req.query.limit+")");
	var QueryCount = eval("("+req.query.count+")");

	CommentBlock.find(QueryWhere).sort(QuerySort).select(QuerySelect).skip(QuerySkip).limit(QueryLimit).exec(function(err,commentBlocks){
		if(err){
			res.status(500);
			res.json({message:'There is a server error'});
			res.send(err);
		}else{
		res.status(200);
		res.json({message:'All the commentBlocks are listed',data:commentBlocks});}

	});

})
.post(function(req,res){
	var commentBlock=new CommentBlock();

  commentBlock.name=req.body.name;
  commentBlock.picture=req.body.picture;
  commentBlock.order=req.body.order;
  commentBlock.content=req.body.content;
//	user.profilepic=fs.readFileSync('smallpic.jpg');

commentBlock.save(function(err){
		if(err){
			res.status(404);
			return console.error(err);

		}
		else{
			res.status(201);
			res.json({message:'The new commentBlock is created',data:commentBlock});
		}
	});
})
.options(function(req, res){
      res.writeHead(200);
      res.end();
});

var commentBlocksIDRoute = router.route('/:commentBlock_id');

commentBlocksIDRoute
.get(function(req,res){
  CommentBlock.findById(req.params.commentBlock_id,function(err,commentBlock){
		if(err){
			res.status(404);
			res.json({message:'The comment is not found'});
			res.send(err);
		}
		else{
		res.status(200);
		res.json({message:'The comment is found',data:commentBlock});}
	});
})
.put(function(req,res){
  CommentBlock.findById(req.params.commentBlock_id,function(err,commentBlock){
		if(err){
			res.status(404);
			res.json({message:'The comment is not found'});
			res.send(err);
		}else{
      commentBlock.name=req.body.name;
      commentBlock.picture=req.body.picture;
      commentBlock.order=req.body.order;
      commentBlock.content=req.body.content;

      commentBlock.save(function(err){
				if (err){
					res.status(500);
					res.json({message:'There is a server error when updating'});
					res.send(err);
				}else{
					res.status(201);
					res.json({message:'CommentBlock Updated',data:commentBlock});
				}
			});
		}
	});
})
.delete(function(req,res){
  CommentBlock.remove({
		_id:req.params.commentBlock_id
	},function(err,commentBlock){
		if(err){
			res.status(404);
			res.json({message:'The commentBlock does not exit'});
			res.send(err);
		}else{
		res.json({message:'Successfully deleted commentBlock'});
		}
	});
});

module.exports=router;
