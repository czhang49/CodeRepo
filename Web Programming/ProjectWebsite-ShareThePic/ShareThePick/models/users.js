
// Load required packages
var mongoose = require('mongoose');
var bcrypt = require('bcrypt-nodejs');

// Define our user schema
var UserSchema   = new mongoose.Schema({
  name: {type: String},
  email: {type: String},
    password: {type: String},
  description: {type: String, default: "Hi everyone, I'm new to ShareThePik"},
  location:{type: String},
  profilepic: {type: String},

  date_created:  {type: Date, default: Date.now},

  number_photo: {type: Number, default: 0},

  list_event:{type: [String]}

});

// methods ======================
// generating a hash
UserSchema.methods.generateHash = function(password) {
    return bcrypt.hashSync(password, bcrypt.genSaltSync(8), null);
};

// checking if password is valid
UserSchema.methods.validPassword = function(password) {
    return bcrypt.compareSync(password, this.password);
};

// Export the Mongoose model
module.exports = mongoose.model('User', UserSchema);
