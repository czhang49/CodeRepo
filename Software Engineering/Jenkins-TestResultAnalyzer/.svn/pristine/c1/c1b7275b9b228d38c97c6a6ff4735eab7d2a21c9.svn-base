var tableContent = '<div class="table-row {{parentclass}}-{{addName text}}" parentclass= "{{parentclass}}" parentname="{{parentname}}" name = "{{addName text}}" {{#if isChild}} style="display:none"{{/if}}>' +
    '\n' + '         ' +
    '\n' + '         ' +
    '\n' + '         <div class="table-cell"><input type="checkbox" parentclass= "{{parentclass}}" parentname="{{parentname}}" name = "checkbox-{{addName text}}" result-name = "{{addName text}}"/></div> ' +
    '<div class="children  table-cell" >  ' +
    '{{#if children}}' +
        '<div class="icon icon-plus-sign" ></div> ' +
    '{{/if}}</div>' +
    ' <div class="name row-heading table-cell" ' +
        '{{#if hierarchyLevel}}' +
            'style="padding-left:{{addspaces hierarchyLevel}}em;"' +
        '{{/if}}' +
        '>&nbsp;{{text}}<button onclick="displayCode(this)" type="button" class="btn btn-primary btn-xs">code</button></div>' +
    '' +
    '{{#each this.buildResults}}' +
    '\n' + '         <div class="table-cell build-result {{applystatus status}}" data-result=\'{{JSON2string this}}\'><a href="{{createURL buildNumber ..}}">{{applyvalue status totalTimeTaken}}</a></div>' +
    '{{/each}}' +
    '\n' + '</div>' +
    '{{#each children}}\n' +
    '\n' + '{{storeParent this "parentclass" ../parentclass ../text}}' +
    '\n' + '{{store this "parentname" ../text}}' +
    '\n' + '{{addHierarchy this ../hierarchyLevel}}' +
    '\n' + '{{store this "isChild" true}}' +
    '\n' + '{{> tableBodyTemplate this}}' +
    '{{/each}}';

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

//Display source code when code button is clicked
function displayCode(elem,key){
    if (key==null)
    {
      var key = elem.parentNode.parentNode.className.slice(10);
      var codes = testCodes[key];
    } else {
      var codes=key;
    }

    var code = "No Code Found.";
    if(codes!=null)
    {
        code = "<textarea rows='" + codes.length + "' cols='100'>";
        for(var i=0; i<codes.length; i++)
        {
            code += (codes[i].replace(/ /g, '&nbsp')) + '&#10';
        }//end of for
        code += "</textarea>";
    }//end of if

    $j("#code").html(code);
    return code;
}//end of display

function removeSpecialChars(name){
    var modName = "";
    //modName = name.split('.').join('_');
    modName = name.replace(/[^a-z\d/-]+/gi, "_");
    return modName.split('/').join('_'); //forward slashes were not being replaced correctly
}

Handlebars.registerPartial("tableBodyTemplate", tableContent);
Handlebars.registerHelper('store', function (context, key, value, options) {
    if (key !== undefined && value != undefined) {
        context[key] = value;
    }
    return "";
});

Handlebars.registerHelper('JSON2string', function (object) {
    return JSON.stringify(object);
});

Handlebars.registerHelper('storeParent', function (context, key, value1, value2, options) {
    if (value1 == undefined) {
        value1 = "";
    }
    if (value2 == undefined) {
        value2 = "";
    }

    if (key !== undefined) {
        context[key] = removeSpecialChars(value1) + "-" + removeSpecialChars(value2);
    }
    return "";
});


Handlebars.registerHelper('addName', function (name) {
    return removeSpecialChars(name);
});

Handlebars.registerHelper('applyvalue', function (status, totalTimeTaken) {
    if (displayValues == true){
        return isNaN(totalTimeTaken) ? '' : totalTimeTaken.toFixed(3) ;
    }else{
        return status;
    }
});


Handlebars.registerHelper('applystatus', function (status) {
    var statusClass = "no_status";
    switch (status) {
        case "FAILED":
            statusClass = "failed";
            break;
        case "PASSED":
            statusClass = "passed";
            break;
        case "SKIPPED":
            statusClass = "skipped";
            break;
    }
    return statusClass;
});

Handlebars.registerHelper('addspaces', function (hierarchyLevel) {
    var spaces = 1.5;

    spaces = spaces * hierarchyLevel;
    return new Handlebars.SafeString(spaces);
});

Handlebars.registerHelper('addIndent', function (hierarchyLevel) {
    var parent = "|"
    var ident = "-";
    for(var i =0;i<hierarchyLevel;i++){
        ident = ident + ident;
    }

    return new Handlebars.SafeString(parent+ident);
});

Handlebars.registerHelper('addHierarchy', function (context, parentHierarchy, options) {
    if (parentHierarchy == undefined)
        parentHierarchy = 0;
    context["hierarchyLevel"] = parentHierarchy + 1;
});

//Handlebars Helper function for createURL
Handlebars.registerHelper('createURL', function(buildNumber, parent) {
    return createURL(buildNumber, parent);
});


var currentPackageURL = "";
/**
 *  Creates a relative URL to point to the Jenkins test report page
 *  for a given package, class, or test case in the current module for the
 *  specified build
 *  @method createURL
 *  @param {int} buildNumber The number for the build being selected
 *  @param {JavaScript Object} parent The JSON object of the build result selected
 *                                    (in the table this is called in an each loop)
 */
function createURL(buildNumber, parent) {
    var url = "../"+buildNumber+"/testReport/";
    if (parent != undefined && parent.text != undefined) {
        if (parent.hierarchyLevel == undefined || parent.hierarchyLevel == 0) {
            url += parent.text;
            currentPackageURL = url;
        }
        else if (parent.hierarchyLevel == 1) {
            currentPackageURL = currentPackageURL.replace(/\d+\/testReport\//, (buildNumber+"/testReport/"));
            url = currentPackageURL+"/"+parent.text;
        }
        else if (parent.hierarchyLevel == 2) {
            currentPackageURL = currentPackageURL.replace(/\d+\/testReport\//, (buildNumber+"/testReport/"));
            url = currentPackageURL+"/"+parent.parentname+"/"+removeSpecialChars(parent.text)+"/";
        }
    }
    return url;
}

var analyzerTemplate = Handlebars.compile(tableBody);
