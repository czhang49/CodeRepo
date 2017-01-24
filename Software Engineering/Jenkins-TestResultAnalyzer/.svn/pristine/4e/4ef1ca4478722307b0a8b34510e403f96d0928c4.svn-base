
describe("test-result-analyzer-template.js createURL:", function() {

    var buildNumber;
    var parent;

    var testPackageName = 'Test.Package';
    var testClassName = 'TestClass';
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
                    parentname: testClassName,
                    text: testCaseName,
                    type: "package"
                } ],
                hierarchyLevel: 1,
                isChild: true,
                parentclass: "base-Test_Package",
                parentname: testPackageName,
                text: testClassName,
                type: "package"
            } ],
            hierarchyLevel: 0,
            parentclass: "base",
            parentname: "base",
            text: testPackageName,
            type: "package"
        } ]
    };

    beforeEach(function() {
        buildNumber = 1;
        parent = fullDepthJSON.results[0];
    });


    it("Package-level row returns a URL to that package's test report page", function() {
        var output = createURL(buildNumber, parent);
        var expected = "../"+buildNumber+"/testReport/"+testPackageName;
        expect(output).toEqual(expected);
    });

    it("Class-level row returns a URL to that class's test report page", function() {
        parent = parent.children[0];
        currentPackageURL = "../"+buildNumber+"/testReport/"+testPackageName;
        var output = createURL(buildNumber, parent);
        var expected = "../"+buildNumber+"/testReport/"+testPackageName+'/'+testClassName;

        expect(output).toEqual(expected);
    });

    it("Testcase-level row returns a URL to that test case's test report page", function() {
        parent = parent.children[0].children[0];
        currentPackageURL = "../"+buildNumber+"/testReport/"+testPackageName;
        var output = createURL(buildNumber, parent);

        var expected = "../"+buildNumber+"/testReport/"+testPackageName+'/'+testClassName+'/'+testCaseName+"/";

        expect(output).toEqual(expected);
    });

    it("Testcases with forward slashes in the name are replaced with underscores in URL", function() {
        parent = parent.children[0].children[0];
        var testCaseWithSlashesName = 'org/test/BuildResult';
        var testCaseWithoutSlashesName = 'org_test_BuildResult';
        parent.text = testCaseWithSlashesName;
        currentPackageURL = "../"+buildNumber+"/testReport/"+testPackageName;
        var output = createURL(buildNumber, parent);

        var expected = "../"+buildNumber+"/testReport/"+testPackageName+'/'+testClassName+'/'+testCaseWithoutSlashesName+"/";

        expect(output).toEqual(expected);
    });
});

