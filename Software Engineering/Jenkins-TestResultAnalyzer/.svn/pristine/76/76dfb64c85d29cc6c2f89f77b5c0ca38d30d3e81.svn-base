/**
 * Initializes a javascript dictionary object "testCodes", in which the keys
 * are the class names of each <div> table-row containing a testcase, and
 * values are arrays of strings. Each of the strings is a line of source code
 * of the testcase. The array is set to null if no code is found.
 *
 * @author Yisong Yue
 */

var testCodes = {};
var windowUrl = window.location.href;

/**
 * Initializes the testCodes object by recursively traversing the test data
 * object, and for each test case, calling retrieveCode().
 * Invoked by populateTemplate().
 *
 * @method initTestCodes
 * @param {JavaScript array} results The array containing test result data
 * @param {string} url The url to build up from to retrieve the source file
 * @param {string} key The key to build up from to look up code for a test case
 */
function initTestCodes (results, url, key) {
    for (var i = 0; i < results.length; i++) {
        var newUrl;
        if (results[i].hierarchyLevel == undefined || results[i].hierarchyLevel == 0) {
            newUrl = url + results[i].text.replace(/\./g, "/") + "/";
        } else if (results[i].hierarchyLevel == 1) {
            newUrl = url + results[i].text.replace(/\./g, "/") + ".java";
        } else {
            newUrl = url;
        }
        var newKey = key + "-" + results[i].text.replace(/[^a-z\d/-]+/gi, "_");

        if (results[i].hierarchyLevel == 2) {
            retrieveCode(newUrl, newKey, results[i].text);
        }

        initTestCodes(results[i]['children'], newUrl, newKey);
    }
}

/**
 * Asynchronously retrieves the source code file and calls extractCode() to
 * extract the code snippet for the specified test case.
 *
 * @method retrieveCode
 * @param {string} url The url to build up from to retrieve the source file
 * @param {string} key The key to build up from to look up code for a test case
 * @param {string} testname The name of the specified test case
 */
function retrieveCode (url, key, testname) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == 4 && xhttp.status == 200) {
            callback(xhttp);
        }
    }
    xhttp.open("GET", url, true);
    xhttp.send();

    function callback(xml) {
        var code = xml.responseText;
        testCodes[key] = extractCode(code, testname);
    }       
}

/**
 * Helper function that extracts the code snippet of the specified test
 * function.
 *
 * @method extractCode
 * @param {string} code The raw text of the retrieved source code file
 * @param {string} testname The name of the specified test case
 * return An array of lines of source code of the specified test case
 *        Returns null if no source code found
 */
function extractCode (code, testname) {
    var arr = code.split('\n');
    var snippet = [];
    var started = false;
    var braceCount = null;

    for (var i = 0; i < arr.length; i++) {
        if (!started) {
            if (arr[i].indexOf("public") != -1 && arr[i].indexOf("void") != -1
                    && arr[i].indexOf(testname) != -1) {
                started = true;
                snippet.push(arr[i]);
                if (arr[i].split('{').length > 1) {
                    braceCount = arr[i].split('{').length - arr[i].split('}').length;
                }
            }
        } else {
            snippet.push(arr[i]);
            if (braceCount != null) {
                braceCount += arr[i].split('{').length - arr[i].split('}').length;
            } else if (arr[i].split('{').length > 1) {
                braceCount = arr[i].split('{').length - arr[i].split('}').length;
            }
            if (braceCount == 0) {
                return snippet;
            }
        }
    }

    return null;
}
