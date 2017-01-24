/**
 * Created by new on 5/4/15.
 */

// Get the packages we need
var express = require('express');
var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var fs=require('fs');

var router = express.Router();

var Event = require('./../models/events.js');


var eventsRoute = router.route('/');

//Base get request.
//Reply back with all the events
eventsRoute.get(function(req, res){


    console.log("Event Get");
    var query = req.query;

    //We need to handle Params
    var where = {};
    var sort = {};
    var select = {};
    var skip = {};
    var limit = {};
    var count = false;

    //Just Handle Where and go to sleep
    for(var key in query){
        key = key.toLowerCase();

        if(key === "where"){
            where = JSON.parse(query[key]);
            //where = query[key];
        }
        else if(key === "sort"){
            sort = JSON.parse(query[key]);
        }
        else if(key === "sort"){
            sort = JSON.parse(query[key]);
        }
        else if(key === "select"){
            select = JSON.parse(query[key]);
        }
        else if(key === "skip"){
            skip = JSON.parse(query[key]);
        }
        else if(key === "limit"){
            limit = JSON.parse(query[key]);
        }
    }

    Event.find(where).sort(sort).select(select).skip(skip).limit(limit).exec(function (error, doc) {
        if (error) {
            res.status(500);
            var toSend = {
                message: "500 There was a problem with the Mongoose Server"
            };
            res.send(toSend);

        }
        else {
            res.status(200);

            var toSend = {
                message: "200 Replied with of query user",
                data: doc
            };
            res.send(toSend);
        }
    });
});


/**
 * TODO: CHECK For EMAIL NAME TO BE PRESENT
 */
eventsRoute.post(function (req, res) {

    console.log("Event POST");
    var event = new Event();

    event.name = req.body.name;
    event.description = req.body.description;
    event.location = req.body.location;
    //event.list_user_id = [];
    event.list_user_id = req.body.list_user_id;
    if(req.body.start_date == null || req.body.start_date == undefined){
        event.start_date = Date.now();
    }
    else{
        event.start_date = req.body.start_date;
    }

    if(req.body.end_date == null || req.body.end_date == undefined){
        event.end_date = Date.now();
    }
    else{
        event.end_date = req.body.end_date;
    }

    if(!req.body.name){

        res.status(400);
        toSend = {
            message: "Name Not Provided",
            data: []
        };
        res.send(toSend);
    }
    else{



        event.save(function(err){
            if(err){
                res.status(400);
                toSend = {
                    message: "There was a server error",
                    data: event
                };
                res.send();
                return console.error(err);

            }
            else{
                res.status(201);
                res.json({message:'The new user is created',data:event});
            }
        });
    }


});


eventsIdRouter = router.route('/:id([^]*)');

eventsIdRouter.get(function(req, res){


    console.log("Event GET id");
    var requestedId = req.params.id;

    Event.findOne({"_id" : requestedId}, function(error, doc){

        if (error) {
            res.status(500);
            var toSend = {
                message: " 500 There was a problem with the Mongoose Server",
                data: []
            };
            res.send(toSend);
        }
        else{
            if(doc == null){
                res.status(404);
                var toSend = {
                    message: "404 User Not Found",
                    data : requestedId
                };
                res.send(toSend);
            }
            else{
                res.status(200);
                var toSend = {
                    message: "200 Success",
                    data : doc
                };
                res.send(toSend);
            }
        }
    });

});

/**
 * Events Route Optionss
 */
eventsRoute.options(function(req, res){
    res.status(200);
    res.end();
});


eventsIdRouter.delete(function (req, res) {

    console.log("Event DELETE");

    var requestedId = req.params.id;

    Event.findById(requestedId, function(error, event) {

        if (error) {
            res.status(500);
            var toSend = {
                message: "500 There was a problem with the Mongoose Server",
                data: task
            };
            res.send(toSend);
        }
        else{
            if(event == null){
                res.status(404);
                var toSend = {
                    message: "404 User Not Found",
                    data : []
                };
                res.send(toSend);
            }
            else{
                Event.remove({"_id": requestedId}, function (error, doc) {
                    if (error) {
                        res.status(500);
                        var toSend = {
                            message: "500 There was a problem with the Mongoose Server",
                            data: []
                        };
                        res.send(toSend);
                    }
                    else {
                        res.status(200);
                        var toSend = {
                            message: "200 The user was successfully deleted",
                            data: []
                        };
                        res.send(toSend);
                    }
                });
            }
        }
    });

});


/**
 * TODO: update start and end date
 * TODO: Error handling
 */
eventsIdRouter.put(function (req, res) {
    var requestedId = req.params.id;

    var givenName = req.body.name;
    var givenDescription = req.body.description;
    var givenLocation = req.body.location;
    var given_list = req.body.list_user_id;

    if(given_list == null || given_list == undefined){
        given_list = [];
    }

    Event.findById(requestedId, function(error, event){
        if(error){

        }
        else {
            if (event == null) {
                res.status(404);
                var toSend = {
                    message: "404 Invalid Id",
                    data: []
                };
                res.send(toSend);
            } else {

                event.name = givenName;
                event.description = givenDescription;
                event.location = givenLocation;
                event.list_user_id = given_list;

                event.save(function (error) {

                    res.status(200);
                    var toSend = {
                        message: "200 Updated",
                        data: event
                    };
                    res.send(toSend);
                });
            }
        }
    });

});

eventsIdRouter.options(function(req, res){
    res.status(200);
    res.end();
});

module.exports = router;