/**
 * Created by Show on 5/6/15.
 */
angular.module('dataService', [])
    .factory('CommonData', function($http, $q){
        var baseUrl = "http://45.55.150.77:4000";
        var url_users = baseUrl + "/users";
        var url_events = baseUrl + "/events";
        var url_pics = baseUrl + "/pics";
        var url_login = baseUrl + "/auth/login";
        var url_logout = baseUrl + "/auth/logout";
        var url_getUser = baseUrl + "/auth/getUser";
        var url_signup = baseUrl + "/auth/signup";

        var ret = {
            getBaseUrl: function(){
                return baseUrl + "/";
            },
            getUserId: function(){

            },
            getUserUrl: function(){
                return url_users;
            },
            getUserIdByName: function(name, callback){
                $http.get(url_users + '?where={"name":"' + name + '"}')
                    .success(function (data) {
                        callback(data);
                    })
            },
            getUser: function(id, callback){
                $http.get(url_users + "/" + id)
                    .success(function(data){
                        callback(data);
                    });
            },
            getUserList: function(query, callback) {
                if (query) {
                    $http.get(url_users + '?where={"name":/' + query + '/i}&select={"name":1,"email":1}')
                        .success(function(data){
                            callback(data);
                        });
                } else {
                    callback({data:[]});
                }

            },
            checkPassword: function(id, pwd, callback){
                $http.get(url_users + '?where={"_id":"' + id + '", "password":"' + pwd + '"}')
                    .success(function(data){
                        if(data.data.length > 0) {
                            callback(data);
                        } else {
                            callback(false);
                        }
                    });
            },
            updateUser: function(id, data, callback){
                data = JSON.stringify(data);
                $http.put(url_users + '/' + id, data)
                    .success(function(ret, status){
                        callback(ret, status);
                    })
                    .error(function(ret, status){
                        callback(ret, status);
                    });
            },
            getImageUrl: function(id){
                return baseUrl + "/pics/getImage/" + id;
            },
            createEvent: function(data, callback){
                data = JSON.stringify(data);
                $http.post(url_events, data)
                    .success(function(ret, status){
                        callback(ret, status);
                    })
                    .error(function(ret, status){
                        callback(ret, status);
                    });
            },
            getEvent: function(id, callback){
                $http.get(url_events + '/' + id)
                    .success(function(data){
                        callback(data);
                    });
            },
            getEventByUserId: function(id, callback){
                $http.get(url_events + '?where={"list_user_id":"' + id + '"}&sort={"start_date":-1}')
                    .success(callback);

            },
            updateEvent: function(id, data, callback){
                $http.put(url_events + '/' + id, data)
                    .success(function(data, status){
                        callback(data, status);
                    })
                    .error(function(data, status){
                        callback(data, status);
                    });
            },
            getPicsUrl: function(){
                return url_pics;
            },
            getPhotosByEvent: function(eventId, callback){
                $http.get(url_pics + '/' + eventId)
                    .success(function(data){
                        callback(data);
                    });
            },
            deletePhoto: function(imageName, callback){
                $http.delete(baseUrl + "/pics/getImage/" + imageName, {})
                    .success(callback);
            },
            login: function(email, pwd, callback){
                $http.post(url_login, {email:email, password:pwd})
                    .success(callback)
                    .error(callback);
            },
            logout: function(callback){
                $http.get(url_logout)
                    .success(callback)
                    .error(callback);
            },
            getMyInfo: function(callback){
                $http.get(url_getUser)
                    .success(callback)
                    .error(callback);
            },
            signup: function(name, email, pwd, callback){
                $http.post(url_signup, {name:name, email:email, password:pwd})
                    .success(callback)
                    .error(callback);
            },
            getFullEvent: function(event, callback){
                var result = {};
                result.event = event;
                result.users = [];
                result.photos = [];
                var defs = [];
                event.list_user_id.forEach(function(id){
                    var def = $q.defer();
                    defs.push(def);
                    ret.getUser(id, function(user){
                        result.users.push(user.data);
                        def.resolve();
                    });
                });
                var def = $q.defer();
                defs.push(def);
                ret.getPhotosByEvent(event._id, function(photos){
                    result.photos = photos.data;
                });
                var promise = $q.all(defs);
                promise.then(callback(result));
            },
            getFriends: function(id, callback){
                var f = [];
                //get events first
                ret.getEventByUserId(id, function(events){
                    if (events && events.data) {
                        events.data.forEach(function(event){
                            event.list_user_id.forEach(function(id1){
                                if (f.indexOf(id1) == -1 && id1 != id) {
                                    f.push(id1);
                                }
                            });
                        });
                        callback(f);
                    }
                });
            }
        };
        return ret;
    });
