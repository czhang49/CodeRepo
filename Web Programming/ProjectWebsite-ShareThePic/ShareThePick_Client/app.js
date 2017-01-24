var express = require('express');
var router = express.Router();
var app = express();



app.use(express.static(__dirname + '/public'));



app.use('/', router);

var homeRoute = router.route('/');

homeRoute.get(function(req, res) {
    res.json({ message: 'Hello World!' });
});


var port = process.env.PORT || 3000;
console.log("Express server running on " + port);
app.listen(port);