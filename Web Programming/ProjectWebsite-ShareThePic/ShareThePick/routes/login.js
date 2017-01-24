/**
 * Created by new on 5/6/15.
 */

module.exports = function(passport) {

    var router = express.Router();
    var signUp = router.route('/signup');

    signUp.post('/signup', passport.authenticate('local-signup'), function(req, res) {
        res.redirect('/profile.html');
    });

    app.post('/login', passport.authenticate('local-login'), function(req, res) {
        res.redirect('/profile.html');
    });

    app.get('/profile', isLoggedIn, function(req, res) {
        res.json({
            user: req.user
        });
    });

    app.get('/logout', function(req, res) {
        req.logout();
        res.redirect('/');
    });

    function isLoggedIn(req, res, next) {
        if(req.isAuthenticated())
            return next();

        res.json({
            error: "User not logged in"
        });
    }

};