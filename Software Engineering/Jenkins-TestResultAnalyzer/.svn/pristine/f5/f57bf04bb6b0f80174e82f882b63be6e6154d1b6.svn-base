
describe("selectdiffresults.js", function() {

    var testCaseName = 'DifferentStatusTestBuildResult';

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

    var fullDepthJSON2 = {
        builds: ["1", "0"],
        results: [ {
            //buildResults: Array[29]
            buildStatuses: ["FAILED"],
            children: [ {
                //buildResults: Array[29]
                buildStatuses: ["FAILED"],
                children: [ {
                    buildResults: [ 
                        {
                            buildNumber: "1",
                            children: [],
                            isPassed: true,
                            isSkipped: false,
                            name: testCaseName,
                            status: "FAILED",
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
                            status: "PASSED",
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

    var fullDepthJSON3 = {
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
                            buildNumber: "3",
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
                            buildNumber: "2",
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


    it("getDiffs: Returns a list of items that have changed: FAILED to PASSED", function() {
        //expected
        var expectedList = $j('<ul />');
        var expectedListElementStr = "<li><span>"+testCaseName+" changed from FAILED to PASSED</span></li>";
        expectedList.html(expectedListElementStr);
        //actual
        var diffList = $j('<ul />');
        diffList = getDiffs(fullDepthJSON, 0, 1);
        //test
        expect(diffList).toEqual(expectedList);
    });

    it("getDiffs: Returns a list of items that have changed: PASSED to FAILED", function() {
        //expected
        var expectedList = $j('<ul />');
        var expectedListElementStr = "<li><span>"+testCaseName+" changed from PASSED to FAILED</span></li>";
        expectedList.html(expectedListElementStr);
        //actual
        var diffList = $j('<ul />');
        diffList = getDiffs(fullDepthJSON2, 0, 1);
        //test
        expect(diffList).toEqual(expectedList);
    });

});



