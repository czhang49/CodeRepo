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
 * Generates the url for the source code for a given class. This generated 
 * URL assumes that the project is organized according to the standard
 * Maven directory layout, where test classes are located in the 
 * src/test/java directory
 * @param {JavaScript object} result result data for one test
 * @param (string) url the base url of this porject
 * @return A new URL that will point to the location of the source file corresponding to
 * the result.
 */
function generateURL(result, url) {
    if (result.hierarchyLevel == undefined || result.hierarchyLevel == 0) {
        return url + result.text.replace(/\./g, "/") + "/";
    } else if (result.hierarchyLevel == 1) {
        return url + result.text.replace(/\./g, "/") + ".java";
    } else {
        return url;
    }
}

/**
 * Initializes the testCodes object by recursively traversing the test data
 * object, and for each test case, calling retrieveCode().
 * Invoked by populateTemplate().
 *
 * @param {JavaScript array} results The array containing test result data
 * @param {string} url The url to build up from to retrieve the source file
 * @param {string} key The key to build up from to look up code for a test case
 */
function initTestCodes(results, url, key) {
    for (var i = 0; i < results.length; i++) {
        var curResult = results[i];
        var newUrl = generateURL(curResult, url);
        var newKey = key + "-" + curResult.text.replace(/[^a-z\d/-]+/gi, "_");

        if (curResult.hierarchyLevel == 2) {
            retrieveCode(newUrl, newKey, curResult.text);
        }

        initTestCodes(curResult['children'], newUrl, newKey);
    }
}

/**
 * Asynchronously retrieves the source code file and calls extractCode() to
 * extract the code snippet for the specified test case.
 *
 * @param {string} url The url to build up from to retrieve the source file
 * @param {string} key The key to build up from to look up code for a test case
 * @param {string} testname The name of the specified test case
 */
function retrieveCode(url, key, testname) {
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
 * @param {string} code The raw text of the retrieved source code file
 * @param {string} testname The name of the specified test case
 * return An array of lines of source code of the specified test case
 *        Returns null if no source code found
 */
function extractCode(code, testname) {
    var linesOfCode = code.split('\n');
    var codeSnippet = [];
    var started = false;
    var braceCount = null;

    for (var i = 0; i < linesOfCode.length; i++) {
        if (!started) {
            if (linesOfCode[i].indexOf("public") != -1 && linesOfCode[i].indexOf("void") != -1 && linesOfCode[i].indexOf(testname) != -1) {
                started = true;
                codeSnippet.push(linesOfCode[i]);
                if (linesOfCode[i].split('{').length > 1) {
                    braceCount = linesOfCode[i].split('{').length - linesOfCode[i].split('}').length;
                }
            }
        } else {
            codeSnippet.push(linesOfCode[i]);
            if (braceCount != null) {
                braceCount += linesOfCode[i].split('{').length - linesOfCode[i].split('}').length;
            } else if (linesOfCode[i].split('{').length > 1) {
                braceCount = linesOfCode[i].split('{').length - linesOfCode[i].split('}').length;
            }
            if (braceCount == 0) {
                return codeSnippet;
            }
        }
    }

    return null;
}
