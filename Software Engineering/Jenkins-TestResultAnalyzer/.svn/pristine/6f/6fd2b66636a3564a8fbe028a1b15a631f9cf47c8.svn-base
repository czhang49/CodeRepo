describe("CheckBox Event Tests", function() {
  // This fullDepthJSON is borrowed from elsewhere
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

  var spyEvent;

  // This checks if the selected boxes are selected
  it ("should check the selected boxes", function() {
    // This following two methods are basically doing the same thing
    spyEvent = spyOnEvent('#0', 'click');
    $('#0').trigger( "click" );

    expect('click').toHaveBeenTriggeredOn('#0');
    expect(spyEvent).toHaveBeenTriggered();
  });

  // This checks if click on compare results, the needed builds are shown.
  describe( "Check Compare results event tests", function () {
    beforeTestCompare(function(){
      showCheckedBuilds();
    });

    it ("should show only the selected boxes", function(){
      

    });

  });

});
