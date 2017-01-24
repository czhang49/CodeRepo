
describe("differentresults.js test spec", function() {

    var testCaseName = 'DifferentStatusTestBuildResult';

    var newStatus = {
        name:   testCaseName,
        status: "PASSED" 
    };
    var oldStatusPassed = {
        name:   testCaseName,
        status: "PASSED" 
    };
    var oldStatusFailed = {
        name:   testCaseName,
        status: "FAILED" 
    };

    it("addDifferentResultsToList does nothing when the statuses are the same", function() {
        //expected
        var expectedList = $j('<ul />');
        //actual
        var diffList = $j('<ul />');
        diffList = addDifferentResultsToList(diffList, newStatus, oldStatusPassed);
        //test
        expect(diffList).toEqual(expectedList);
    });

    it("addDifferentResultsToList adds a new list item when the statuses are different", function() {
        //expected
        var expectedList = $j('<ul />');
        var expectedListElementStr = "<li><span>"+testCaseName+" changed from FAILED to PASSED</span></li>";
        expectedList.html(expectedListElementStr);
        //actual
        var diffList = $j('<ul />');
        diffList = addDifferentResultsToList(diffList, newStatus, oldStatusFailed);
        //test
        expect(diffList).toEqual(expectedList);
    });

    var fullDepthJSON = {
        builds: ["1", "0"],
        results: [ {
            //buildResults: Array[29]
            buildStatuses: ["PASSED"],
            children: [ {
                //buildResults: Array[29]
                buildStatuses: ["PASSED"],
                children: [ {
                    buildResults: [ 
                        {
                            buildNumber: "1",
                            children: [],
                            isPassed: true,
                            isSkipped: false,
                            name: testCaseName,
                            status: "PASSED",
                            totalFailed: 0,
                            totalPassed: 1,
                            totalSkipped: 0,
                            totalTests: 1,
                            totalTimeTaken: 0
                        },
                        {
                            buildNumber: "0",
                            children: [],
                            isPassed: false,
                            isSkipped: false,
                            name: testCaseName,
                            status: "FAILED",
                            totalFailed: 1,
                            totalPassed: 0,
                            totalSkipped: 0,
                            totalTests: 1,
                            totalTimeTaken: 0 
                        }
                    ],
                    buildStatuses: ["PASSED"],
                    children: [],
                    hierarchyLevel: 2,
                    isChild: true,
                    parentclass: "base-Test_Package-TestClass",
                    parentname: "TestClass",
                    text: testCaseName,
                    type: "package"
                } ],
                hierarchyLevel: 1,
                isChild: true,
                parentclass: "base-Test_Package",
                parentname: "Test.Package",
                text: "TestClass",
                type: "package"
            } ],
            parentclass: "base",
            parentname: "base",
            text: "Test.Package",
            type: "package"
        } ]
    };

    it("getDiffs also returns a list of items that have changed", function() {
        //expected
        var expectedList = $j('<ul />');
        var expectedListElementStr = "<li><span>"+testCaseName+" changed from FAILED to PASSED</span></li>";
        expectedList.html(expectedListElementStr);
        //actual
        var diffList = $j('<ul />');
        diffList = getDiffs(fullDepthJSON);
        //test
        expect(diffList).toEqual(expectedList);
    });

});

