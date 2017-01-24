describe("CheckBox Event Tests", function() {

  var testCaseName = 'CheckBoxEventTests';
  // Defines
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
  // This builds up the HTML Tags.
  var analyzerTemplate = Handlebars.compile(tableBody);

  var testarray=["0","1","2","3","4","5","6","7","8"];
  var testchecked1=[0,1];
  var testchecked2=[2,4,5];
  var testresults=["result1","result2","result3","result4","result5"];

  // This checks if the array is removed correctly
  it ("should return the correct removed array", function() {
    var returnedarray=removeFromArray(testarray,testchecked1);
    console.log(returnedarray);
    expect(returnedarray).toEqual(["8"]);
  });

  it ("should show the compare builds box is activated", function() {
    var returnedarray2=removeFromArray(testarray,testchecked2);
    
    expect(returnedarray2).toEqual([ ]);
  });

});


describe("tests for retrieving codes", function() {
  // The needed element and node structures are created, btn is the grandparent
  var btn = document.createElement("BUTTON");
  var para = document.createElement("p");
  var node = document.createTextNode("This is new.");
  para.appendChild(node);
  btn.appendChild(para);
  // the btn.className is input as some randome string. because this string
  // has no associated code in the testcode and can be used as the testcode to check
  btn.className="nicainicainicai";
  var codes=btn.className;

  // Here the code is constructed using the codes, which is the btn.className
  var code = "<textarea rows='" + codes.length + "' cols='100'>";
  for(var i=0; i<codes.length; i++)
  {
      code += (codes[i].replace(/ /g, '&nbsp')) + '&#10';
  }//end of for
  code += "</textarea>";

  // case one, when only the node (grandchild), is passed, there should be node code at all
  it("should return no code at all, because no code is inputed", function() {
    var returnedcode=displayCode(node);
    expect(returnedcode).toEqual("No Code Found.");
  });

  // case two, when the input code (the btn.className) is passed, the returnedcode should be the same as the return code
  // constructed above.
  it("should return the input code, because the raw code is inputed", function() {
    var returnedcode=displayCode(btn,btn.className);
    expect(returnedcode).toEqual(code);
  });

});
