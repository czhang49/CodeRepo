
// Load required packages
var mongoose = require('mongoose');

// Define our user schema
var PicsSchema   = new mongoose.Schema({
  event: {type: String, required: true},
  uploader: {type: String},
  name: {type: String},
  commentBlocks:{type: [String]},
  path: {type: String, required: true},

});

// Export the Mongoose model
module.exports = mongoose.model('Pic', PicsSchema);
