// Load required packages
var mongoose = require('mongoose');

// Define our task schema
var TaskSchema   = new mongoose.Schema({
  name: {type: String, required: true},
  description: {type: String,default: 'NoDescription'},
  deadline:  {type: Date, required: true},
  completed:  {type:Boolean, default: 0},
  assignedUser:  {type:String, default: 'NotAssigned'},
  assginedUserName: {type:String,default:'NotAssigned'},
  dateCreated:  {type: Date, default: Date.now}
});

// Export the Mongoose model
module.exports = mongoose.model('Task', TaskSchema);
