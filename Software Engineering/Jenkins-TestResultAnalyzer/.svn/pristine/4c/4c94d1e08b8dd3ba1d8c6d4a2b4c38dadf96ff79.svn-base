describe("CheckBox Event Tests", function() {
  // This fullDepthJSON is borrowed from elsewhere
  var testCaseName = 'CheckBoxEventTests';

  var tableBody = '<div class="heading">' +

      '\n' + '        <div class="table-cell">Chart</div><div class="table-cell">See children</div> <div class="table-cell">The Condensed Results</div>' +
      '{{#each builds}}' +
      '\n' + '         <div class="table-cell">{{this}}<input type="checkbox" id={{this}} value="checked-builds"/></div>' +
      '{{/each}}' +
      '\n' + '      </div>' +
      '{{#each results}}' +
      '{{store this "parentname" "base"}}' +
      '{{store this "parentclass" "base"}}' +
      '{{> tableBodyTemplate}}' +
      '\n' + '{{/each}}';

  var analyzerTemplate = Handlebars.compile(tableBody);

//  var spyEvent;
  // This checks if the selected boxes are selected
 it ("should check the selected boxes", function() {
    // This following two methods are basically doing the same thing
    $('#1').trigger( "click" );
    //spyEvent = spyOnEvent('#1', 'click');
    //expect($('#1')).toEqual("expectedList");
  //  expect('click').toHaveBeenTriggeredOn($("#1"));
    //expect(spyEvent).toHaveBeenTriggered();
  });

  // This checks if click on compare results, the needed builds are shown.
/*  describe( "Check Compare results event tests", function () {

    //showCheckedBuilds();
    it ("should show only the selected boxes", function(){

      //expect($('#1')).toBeInDOM();
      //expect($('#0')).not.toBeInDOM();
      expect(1).toEqual(1);
    });

  });*/

});


/*
describe("Button Click Event Tests", function() {
  var spyEvent;

  beforeEach(function() {
    setUpHTMLFixture();
  });

  it ("should invoke the btnShowMessage click event.", function() {
    spyEvent = spyOnEvent('#btnShowMessage', 'click');
    $('#btnShowMessage').trigger( "click" );

    expect('click').toHaveBeenTriggeredOn('#btnShowMessage');
    expect(spyEvent).toHaveBeenTriggered();
  });

  it ("should invoke the btnHideMessage click event.", function() {
    spyEvent = spyOnEvent('#btnHideMessage', 'click');
    $('#btnHideMessage').trigger( "click" );

    expect('click').toHaveBeenTriggeredOn('#btnHideMessage');
    expect(spyEvent).toHaveBeenTriggered();
  });
});*/


describe("tests for retrieving codes", function() {

  var btn = document.createElement("BUTTON");
  var para = document.createElement("p");
  var node = document.createTextNode("This is new.");
  para.appendChild(node);
  btn.appendChild(para);
  btn.className="nicainicainicai";

  var codes=btn.className;

  var code = "<textarea rows='" + codes.length + "' cols='100'>";
  for(var i=0; i<codes.length; i++)
  {
      code += (codes[i].replace(/ /g, '&nbsp')) + '&#10';
  }//end of for
  code += "</textarea>";


  it("should return no code at all", function() {
    var returnedcode=displayCode(node);
    expect(returnedcode).toEqual("No Code Found.");
  });

  it("should return the input code", function() {
    var returnedcode=displayCode(btn,btn.className);
    expect(returnedcode).toEqual(code);
  });

});
