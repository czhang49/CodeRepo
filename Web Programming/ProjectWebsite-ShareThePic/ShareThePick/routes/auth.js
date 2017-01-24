// app/routes.js
module.exports = function(app, passport) {


    app.post('/auth/signup', passport.authenticate('local-signup'), function (req, res) {

        console.log('Auth SignUp');
        res.status(200);
        res.send(req.user);
    });

    app.options('/auth/signup', function(req, res){

        res.status(200);
        res.send();

    });

    app.post('/auth/login', passport.authenticate('local-login'), function(req, res){

        console.log('Auth Login');
        res.status(200);

        if(req.user == 'Unauthorized'){
            toSend = {
                message : "This might work",
                data : []
            }
        }
        else{
            toSend = req.user;
        }
        res.send(toSend);

    });

    app.options('/auth/login', function(req, res){

        res.status(200);
        res.send();

    });

    app.get('/auth/getUser', isLoggedIn, function(req, res){

        res.status(200);
        res.send(req.user);

    });

    app.options('/auth/getUser', function(req, res){

        res.status(200);
        res.send();

    });



    app.get('/auth/logout', function(req, res){

        req.logout();

        res.status(200);
        var toSend = {
            message: "Logout Successfull",
            date: []
        };
        res.send(toSend);

    });

    app.options('/auth/logout', function(req, res){

        res.status(200);
        res.send();

    });


};

// route middleware to make sure
function isLoggedIn(req, res, next) {

    // if user is authenticated in the session, carry on
    if (req.isAuthenticated())
        return next();

    else{
        res.status(200);
        var toSend ={
            message: "Invalid Page Access, not logged in",
            data : []
        };
        res.send(toSend);
    }
    // if they aren't redirect them to the home page

}