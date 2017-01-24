/**
 * Created by Abhishek on 5/4/15.
 */

var mongoose = require('mongoose');

var eventsSchema = new mongoose.Schema({
    name: {type: String},
    description: {type: String, default: "Default Event"},
    list_user_id: {type: Array},
    location: {type: String},
    start_date:{type: Date},
    end_date: {type: Date}

});

module.exports = mongoose.model('Events', eventsSchema);