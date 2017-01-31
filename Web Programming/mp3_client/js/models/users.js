
// Load required packages
var mongoose = require('mongoose');

// Define our user schema
var UserSchema   = new mongoose.Schema({
  name: {type: String, required: false, unique: false},
  email: {type: String, required: false, unique: false},
  pendingTasks: [String],
  dateCreated:  {type: Date, default: Date.now} 
});

// Export the Mongoose model
module.exports = mongoose.model('User', UserSchema);
