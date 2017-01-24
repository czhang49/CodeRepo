/**
 * Creates the dropdown menus that allows the user to select to build numbers
 * to compare. Also contains helper functions for the functionality allowing
 * users to only display results of an arbitrary nubmer of selected builds
 * using checkboxes.
 *
 * @author Yisong Yue
 * @author Shaan Iqbal
 * @author Sun Woo Kim
 */

$j = $;

/**
 * Populates the "Compare builds" drop down menus on the page with availabe
 * build numbers. Invoked by populateTemplate().
 * @param {JavaScript object} resultData A JSON object containing all test
 *                                       results retrieved from the Java side
 */
function addOptions(resultData) {
    // clear out all options previously in this drop down
    $j("#selectFirstBuild").find('option').remove();
    $j("#selectSecondBuild").find('option').remove();
    var numBuilds = resultData['builds'].length;
    for (var i = 0; i < numBuilds; i++) {
        var buildNumber = resultData['builds'][i];
        $j("#selectFirstBuild").append($j("<option>")
            .val(i)
            .html(buildNumber)
        );
        $j("#selectSecondBuild").append($j("<option>")
            .val(i)
            .html(buildNumber)
        );
    }
}

/**
 * Retrieves test result data and further modifies it to remove data of all
 * builds other than the two that are selected to compare, as well as the test
 * suites/cases that have the same result (status) in both of the selected
 * builds. Displays the difference as text and as the content of the table.
 * The table is not updated if no difference is found.
 */
function showDiffs() {
    var noOfBuilds = $j('#noofbuilds').val();
    var statusFilter = $j('#teststatus').val();
    displayValues = $j("#show-durations").is(":checked");

    remoteAction.getTreeResult(noOfBuilds, statusFilter, $j.proxy(function(t) {
        var itemsResponse = t.responseObject();
        var firstBuildIndex = $j('#selectFirstBuild').val();
        var secondBuildIndex = $j('#selectSecondBuild').val();
        testResultData = itemsResponse; //gets data out for other uses
        var max = Math.max(firstBuildIndex, secondBuildIndex);
        var min = Math.min(firstBuildIndex, secondBuildIndex);
        var diffList = getDiffs(itemsResponse, min, max);
        if (diffList.html() != "") {
            $j("#diffList").html(diffList); // add list with differences
        } else {
            $j("#diffList").html("No differences between these two builds");
        }
        if (firstBuildIndex != secondBuildIndex) {
            compareBuilds(itemsResponse, min, max);
            if (itemsResponse['results'].length > 0) {
                reset();
                treeMarkup = analyzerTemplate(itemsResponse);
                $j(".table").html(treeMarkup);
                addEvents();
            }
        }
    }, this));
}

/**
 * Helper function that removes test result data from "items" not needed for
 * displaying when comparing two builds.
 * @param {JavaScript object} items A JSON object containing all test results
 *                                  retrieved from the Java side
 * @param {int} idx1 Index of first selected build number in the array of data
 * @param {int} idx2 Index of second selected build number in the array of data
 */
function compareBuilds(items, idx1, idx2) {
    removeOtherFromArray(items['builds'], idx1, idx2);
    findChanges(items['results'], idx1, idx2);
}

/**
 * Helper function that removes all items from the input array except those at
 * the two selected indices.
 *
 * @param {JavaScript array} arr The array to remove items from
 * @param {int} min The smaller of the two selected indices
 * @param {int} max The larger of the two selected indices
 */
function removeOtherFromArray(arr, min, max) {
    arr.splice(max + 1, arr.length);
    arr.splice(min + 1, max - min - 1);
    arr.splice(0, min);
}

/**
 * Helper function that recursively removes all test cases/suites that have the
 * same result(s) for the builds at selected indices in the result data.
 * @param {JavaScript array} results The array of test result data
 * @param {int} idx1 Index of first selected build number in the array of data
 * @param {int} idx2 Index of second selected build number in the array of data
 */
function findChanges(results, idx1, idx2) {
    for (var i = results.length - 1; i >= 0; i--) {
        removeOtherFromArray(results[i]['buildResults'], idx1, idx2);
        if (results[i]['buildResults'][0]['status']
                == results[i]['buildResults'][1]['status']) {
            results.splice(i, 1);
        } else {
            findChanges(results[i]['children'], idx1, idx2);
        }
    }
}


/**
 * Returns html code that is implemented in the jelly file to create the
 * button that compares checked builds. Invoked by populateTemplate().
 * @return {string} string containing the html code to create the
 *                  'Compare Checked Builds' button
 */
function createCheckboxButton() {
    var checkbutton = '<button id="getcheckedbuilds">Compare Checked Builds</button>';
    return checkbutton;
}

/**
 * Populates the chart after getting the builds that were checked in the
 * checkboxes and removes all other builds that were not checked
 */
function showCheckedBuilds(){
    var noOfBuilds = $j('#noofbuilds').val();
    var statusFilter = $j('#teststatus').val();
    displayValues = $j("#show-durations").is(":checked");

    remoteAction.getTreeResult(noOfBuilds, statusFilter, $j.proxy(function(t) {
        var itemsResponse = t.responseObject();
        testResultData = itemsResponse; //gets data out for other uses
        checked = checked.map(Number);
        checked.sort(function(a, b){return a-b});
        removeBuilds(itemsResponse);
        checked = [];

        if (itemsResponse['results'].length > 0) {
            reset();
            treeMarkup = analyzerTemplate(itemsResponse);
            $j(".table").html(treeMarkup);
            addEvents();
        }
    }, this));
}

/**
 * Helper function that removes all other builds and its respective results
 * that were not checked
 * @param {JavaScript object} items A JSON object containing all test results
 *                                  retrieved from the Java side
 */
function removeBuilds(items) {
    removeFromArray(items['builds']);
    removeResults(items['results']);
}

/**
 * Helper function that removes all items in an array that weren't checked
 * @param {JavaScript array} arr The array to remove items from
 */
function removeFromArray(arr,checkedarray) {

    arr.reverse();
    var end = checked.length-1;
    var max = checked[end];
    var min = checked[0];
    arr.splice(max, arr.length);
    for(var i= end-1; i>=0; i--){
        arr.splice(checked[i], checked[i+1]-checked[i]-1);
    }
    arr.splice(0, min-1);
    arr.reverse();
}

/**
 * Helper function that recursively removes all results of the builds that were
 * not checked.
 * @param {JavaScript array} results The array of test result data
 */
function removeResults(results) {
    for (var i = results.length - 1; i >= 0; i--) {
        removeFromArray(results[i]['buildResults']);
        removeResults(results[i]['children']);
    }
}
