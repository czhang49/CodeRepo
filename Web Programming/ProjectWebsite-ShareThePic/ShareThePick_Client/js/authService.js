/**
 * Created by Show on 5/9/15.
 */
angular.module('authService',[])
    .factory('Main', ['$http', '$localStorage', function($http, $localStorage){
        var baseUrl = "http://127.0.0.1:4000";
        function changeUser(user) {
            angular.extend(currentUser, user);
        }

        function urlBase64Decode(str) {
            var output = str.replace('-', '+').replace('_', '/');
            switch (output.length % 4) {
                case 0:
                    break;
                case 2:
                    output += '==';
                    break;
                case 3:
                    output += '=';
                    break;
                default:
                    throw 'Illegal base64url string!';
            }
            return window.atob(output);
        }

        function getUserFromToken() {
            var token = $localStorage.token;
            var user = {};
            if (typeof token !== 'undefined') {
                var encoded = token.split('.')[1];
                user = JSON.parse(urlBase64Decode(encoded));
            }
            return user;
        }

        var currentUser = getUserFromToken();

        return {
            save: function(data, success, error) {
                $http.post(baseUrl + '/auth/signup', data).success(success).error(error)
            },
            signin: function(data, success, error) {
                $http.post(baseUrl + '/auth/login', data).success(success).error(error)
            },
            me: function(success, error) {
                $http.get(baseUrl + '/auth/getUser').success(success).error(error)
            },
            logout: function(success) {
                changeUser({});
                delete $localStorage.token;
                success();
            }
        };
    }
    ]);