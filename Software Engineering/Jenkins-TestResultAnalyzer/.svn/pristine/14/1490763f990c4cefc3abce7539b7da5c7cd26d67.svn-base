// Creates the dropdown menus that allows the user to select which two builds they want to compare.

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

function compareBuilds(items, idx1, idx2) {
    removeOtherFromArray(items['builds'], idx1, idx2);
    findChanges(items['results'], idx1, idx2);
}

function removeOtherFromArray(arr, min, max) {
    arr.splice(max + 1, arr.length);
    arr.splice(min + 1, max - min - 1);
    arr.splice(0, min);
}

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


function createCheckboxButton() {
    var checkbutton = '<button id="getcheckedbuilds">Compare Checked Builds</button>';
    return checkbutton;
}

function showCheckedBuilds(){
    var noOfBuilds = $j('#noofbuilds').val();
    var statusFilter = $j('#teststatus').val();
    displayValues = $j("#show-durations").is(":checked");

    remoteAction.getTreeResult(noOfBuilds, statusFilter, $j.proxy(function(t) {
        var itemsResponse = t.responseObject();
        testResultData = itemsResponse; //gets data out for other uses
        removeBuilds(itemsResponse);

        if (itemsResponse['results'].length > 0) {
            reset();
            treeMarkup = analyzerTemplate(itemsResponse);
            $j(".table").html(treeMarkup);
            addEvents();
        }
    }, this));
}

function removeBuilds(items) {
    var buildArr = items['builds'];
    var resultArr = items['results'];
    console.log(buildArr);
    console.log(resultArr);
    console.log(checked);
/*
    var newBuild = [];
    var newResult = [];

    for(var i=0; i<buildArr.length; i++){
        for(var j=0; j<checked.length; j++){
            if(buildArr[i] == checked[j]){
                newBuild.push(buildArr[i]);
                newResult.push(resultArr[i]);
            }
        }    
    }

    items['builds'] = newBuild;
    items['results'] = newResult;
    */
}
