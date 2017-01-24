/**
 * Created by Show on 5/6/15.
 */
var utils = {
    QueryString: function () {
        var query_string = {};
        var query = window.location.search.substring(1);
        var vars = query.split("&");
        for (var i=0;i<vars.length;i++) {
            var pair = vars[i].split("=");
            // If first entry with this name
            if (typeof query_string[pair[0]] === "undefined") {
                query_string[pair[0]] = pair[1];
                // If second entry with this name
            } else if (typeof query_string[pair[0]] === "string") {
                var arr = [ query_string[pair[0]], pair[1] ];
                query_string[pair[0]] = arr;
                // If third or later entry with this name
            } else {
                query_string[pair[0]].push(pair[1]);
            }
        }
        return query_string;
    },
    redirectLogin: function(){
        location.href = "./index.html";
    },
    alert: function(id, message, type){
        $(id).append('<div data-alert class="alert-box ' + type + ' radius">' + message + '<a href="#" class="close">&times;</a> </div>');
        $(document).foundation('alert', 'reflow');
    },
    getUserId: function(){
        var id = utils.QueryString().id;
        if (!id) {
            utils.redirectLogin();
            return null;
        }
        return id;
    },
    getEventId: function(){
        var id = utils.QueryString().id;
        if (!id) {
            utils.redirectLogin();
            return null;
        }
        return id;
    }
};