// Get the packages we need
var express = require('express');
var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var fs=require('fs');
var router = express.Router();
var multer=require('multer');
var path = require('path');

var Pic=require('./../models/pics');

//
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


var homeRoute = router.route('/');

homeRoute
.get(function(req,res){
	var QueryWhere = eval("("+req.query.where+")");
	var QuerySort = eval("("+req.query.sort+")");
	var QuerySelect = eval("("+req.query.select+")");
	var QuerySkip = eval("("+req.query.skip+")");
	var QueryLimit = eval("("+req.query.limit+")");
	var QueryCount = eval("("+req.query.count+")");

	Pic.find(QueryWhere).sort(QuerySort).select(QuerySelect).skip(QuerySkip).limit(QueryLimit).exec(function(err,pics){
		if(err){
			res.status(500);
			res.json({message:'There is a server error'});
			res.send(err);
		}else{
		res.status(200);
		res.json({message:'All the pics are listed',data:pics});}

	});

})
.post(function(req,res){
	var pic=new Pic();

  pic.event=req.body.event;
  pic.uploader=req.body.uploader;
  pic.commentBlocks=req.body.commentBlocks;
  pic.path=file_path;
  pic.name=file_name;

  pic.save(function(err){
		if(err){
			res.status(404);
			return console.error(err);

		}
		else{
			res.status(201);
			res.json({message:'The new pic is created',data:pic});
		}
	});
})
.options(function(req, res){
      res.writeHead(200);
      res.end();
});

var picsIDRoute = router.route('/:event_id');

picsIDRoute
.get(function(req,res){
	Pic.find({"event": req.params.event_id},function(err,pic_list){
		if(err){
      res.status(500);
			res.json({message:'Problem with the server'});
			res.send(err);
		}
		else{
      if(pic_list == null){
        res.status(404);
  			res.json({message:'The pic is not found'});
  			res.send(err);
      }else{
        res.status(200);
        res.json({message:'The pic is found',data:pic_list});}
      }

	});
})
.delete(function(req,res){

        console.log("Pics Delete");

        Pic.find({event : req.params.event_id}, function(err, pics){
           if(err){
               res.status(500);
               res.json({message:'Server Error'});
           }else{

               console.log(pics);

               for(var i in pics){
                   var picName = pics[i].name;
                   var file = path.join(__dirname, '../upload',picName);
                   openUnlink(file);
               }

               Pic.remove({
                   event : req.params.event_id
               },function(err,pics){
                   if(err){
                       res.status(500);
                       res.json({message:'Server Error'});
                   }else{
                       console.log(pics);
                       res.status(200);
                       res.json({message:'Successfully deleted Pic'});
                   }
               });
           }

        });


});

var picsGetByIDRoute= router.route('/getImage/:pic_name');

picsGetByIDRoute
.get(function(req,res){

  image_name = req.params.pic_name;
  var file = path.join(__dirname, '../upload',image_name)
  console.log(file);

  res.status(200);
  res.sendFile(file);

})
.delete(function(req,res){


	Pic.remove({
		name:req.params.pic_name
	},function(err,pic){
		if(err){
			res.status(500);
			res.json({message:'Server Error'});
			res.send(err);
		}else{

            var file = path.join(__dirname, '../upload', req.params.pic_name);

            openUnlink(file);

		    res.json({message:'Successfully deleted picture'});
		}
	});
});

function openUnlink(name) {
    console.log(name);
    fs.open(name, 'w', function (err) {
        console.log(' + ' + name);
        fs.unlinkSync(name, function (err) {
            console.log('   - ' + name);
        });
    });
}

module.exports=router;
