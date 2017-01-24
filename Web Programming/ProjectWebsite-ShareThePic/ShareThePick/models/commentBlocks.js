
// Load required packages
var mongoose = require('mongoose');

// Define our user schema
var commentBlocksSchema   = new mongoose.Schema({
  name: {type: String, required: true},
  picture: {type: String, required: true},
  order: {type: Number, required: true},
  content:{type: String, default: " "}

});

// Export the Mongoose model
module.exports = mongoose.model('CommentBlock', commentBlocksSchema);
