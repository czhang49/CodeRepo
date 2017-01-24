
describe("test-result-analyzer-template.js CreateURL test spec", function() {

    var testCaseName = 'DifferentStatusTestBuildResult';

    it("for package-level row returns a URL to that package's test report page", function() {

    });

    it("for class-level row returns a URL to that class's test report page", function() {
        
    });

    it("for testcase-level row returns a URL to that test case's test report page", function() {
        
    });

    it("testcases with forward slashes in the name are replaced with underscores in URL", function() {

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
});

