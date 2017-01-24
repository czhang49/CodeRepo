// Get the packages we need



var express = require('express');
var path = require('path');
var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var flash    = require('connect-flash');
var morgan = require('morgan');
var fs=require('fs');


var app = express();

var router = express.Router();
var usersRoutes=require('./routes/usersRoutes');
var commentBlocksRoutes=require('./routes/commentBlocksRoutes');
var picsRoutes=require('./routes/picsRoutes');
var eventsRoutes = require('./routes/events.js');

//var loginRouter = require('./routes/login')(app, passport);

//replace this with your Mongolab URL
mongoose.connect('mongodb://ShareThePik:ShareThePik@ds053937.mongolab.com:53937/share_thepik_server_chen');

// Create our Express application


// Use environment defined port or 4000
var port = process.env.PORT || 4000;

//Allow CORS so that backend and frontend could pe put on different servers
var allowCrossDomain = function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "http://do.di4fun.com:3000");
  res.header("Access-Control-Allow-Headers", "X-Requested-With, X-HTTP-Method-Override, Content-Type, Accept");
  res.header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE");
  res.header("Access-Control-Allow-Credentials","true");
  next();
};
app.use(allowCrossDomain);

// Use the body-parser package in our application
app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(bodyParser.json());


//var authRoutes = require('./routes/auth.js')(passport);

// Configuring Passport
var passport = require('passport');
var expressSession = require('express-session');
app.use(expressSession({secret: 'mySecretKey'}));
app.use(passport.initialize());
app.use(passport.session());



// All our routes will start with /api
app.use('/users',usersRoutes);
app.use('/commentBlocks',commentBlocksRoutes);
app.use('/pics',picsRoutes);
app.use('/events', eventsRoutes);
//app.use('/auth', authRoutes);

require('./config/passport')(passport);
require('./routes/auth')(app, passport);


app.listen(port);
console.log('Server running on port ' + port);
