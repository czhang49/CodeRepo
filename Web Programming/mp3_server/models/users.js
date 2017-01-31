
// Load required packages
var mongoose = require('mongoose');

// Define our user schema
var UserSchema   = new mongoose.Schema({
  name: {type: String, required: true,unique:true},
  email: {type: String, required: true,uique:true},
  pendingTasks: {type: [String],default:['NoPendingTask','NoPendingTask']},
  dateCreated:  {type: Date, default: Date.now} 
});

// Export the Mongoose model
module.exports = mongoose.model('User', UserSchema);
