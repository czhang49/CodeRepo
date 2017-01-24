/**
 * Compares the results of two selected builds and displays the differences
 * as text on the plugin page.
 *
 * @author Patrick Sapin
 */

 $j = $;

/**
 * creates unordered list
 * iterates through given result data JSON object
 * compares each test case in most recent build to previous build
 * add list items for each test case with differences between those builds
 * @method getDiffs
 * @return list
 */
function getDiffs(resultData, firstBuild, secondBuild) {
    //empty list to append to
    var diffList = $j('<ul />');
    var packages = resultData['results'];
    var numBuilds = resultData['builds'].length;
    if (numBuilds < 2) {
        return diffList;
    }
    //iterate packages
    var numPackages = packages.length;
    for (var pkgIdx = 0; pkgIdx < numPackages; pkgIdx++) {
        //iterate classes
        var classes = packages[pkgIdx]['children'];
        var numClasses = classes.length;
        for (var clsIdx = 0; clsIdx < numClasses; clsIdx++) {
            //iterate tests (no action taken on iteration atm)
            var testCases = classes[clsIdx]['children'];
            var numTestCases = testCases.length;
            for (var tstIdx = 0; tstIdx < numTestCases; tstIdx++) {
                //get results for current test case
                var testCaseResults = testCases[tstIdx]['buildResults'];
                //get last build results and second to last build results
                var latestResult = testCaseResults[firstBuild];
                var nextLatestResult = testCaseResults[secondBuild];
                //compare and add to list
                diffList = addDifferentResultsToList(diffList, latestResult,
                               nextLatestResult, testCases[tstIdx]['text']);
            }

        }
    }
    return diffList;
}

/**
 * Given the unordered list element and two build results JSON objects,
 * if status of builds are different, create new list item and add to list
 * @method addDifferentResultsToList
 * @return list whether modified or not
 */
function addDifferentResultsToList(diffList, newBuildResults, oldBuildResults, testName) {
    var newStatus = newBuildResults['status'];
    var oldStatus = oldBuildResults['status'];
    if (newStatus != oldStatus) {
        var item = $j('<li />');
        item.html('<span>' + testName + ' changed from ' + oldStatus + ' to ' + newStatus + '</span>');
        diffList.append(item);
    }
    return diffList;
}
