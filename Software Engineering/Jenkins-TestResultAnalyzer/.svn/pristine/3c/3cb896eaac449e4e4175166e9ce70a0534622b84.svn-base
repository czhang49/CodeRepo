var colTemplate = "{'cellClass':'col1','value':'build20','header':'20','title':'20'}";
var treeMarkup = "";
var testResultData = "";
var reevaluateChartData = true;
var displayValues = false;
var checked = [];

/**
 * Clears all the tables and charts on the plugin page.
 * @method reset
 */
function reset() {
    reevaluateChartData = true;
    $j(".table").html("")
    treeMarkup = "";
    resetCharts();
}

/**
 * Collects all the values of drop down selections on the page and sends them
 * to the Java side to generate and update the content of the table.
 * @method populateTemplate
 */
function populateTemplate() {
    reset();
    var noOfBuilds = $j('#noofbuilds').val();
    var statusFilter = $j('#teststatus').val();
    displayValues = $j("#show-durations").is(":checked");

    remoteAction.getTreeResult(noOfBuilds, statusFilter, $j.proxy(function(t) {
        var itemsResponse = t.responseObject();
        testResultData = itemsResponse; //gets data out for other uses
        var diffList = getDiffs(itemsResponse, 0, 1);
        if (diffList.html() != "") {
            $j("#diffList").html(diffList); // add list with differences
        } else {
            diffList.remove();
        }
        addOptions(itemsResponse);

        var compareCheckedBuilds = createCheckboxButton();
        if (compareCheckedBuilds.html != "") {
            $j("#compareCheckedBuilds").html(compareCheckedBuilds);
        } else {
            compareCheckedBuilds.remove();
        }
        treeMarkup = analyzerTemplate(itemsResponse);
        $j(".table").html(treeMarkup);
        addEvents();
    }, this));
}

function populateTemplateCondensed() {
    reset();
    var noOfBuilds = $j('#noofbuilds').val();
    var statusFilter = $j('#teststatus').val();
    displayValues = $j("#show-durations").is(":checked");
    noOfBuilds = 'all';
    statusFilter = 'all';
    displayValues = false;
    remoteAction.getTreeResultCondensed(noOfBuilds, statusFilter, $j.proxy(function(t) {
        var itemsResponse = t.responseObject();
        treeMarkup = analyzerTemplate(itemsResponse);
        $j(".table").html(treeMarkup);
        addEvents();
    }, this));
}

function collapseAll() {
    reevaluateChartData = true;
    $j(".table").html("")
    $j(".table").html(treeMarkup);
    addEvents();
}

function expandAll() {
    reevaluateChartData = true;
    collapseAll();
    $j(".table .table-row .icon").each(function() {
        $j(this).click();
    });

}

function addEvents() {

    var toggleHandler = function(node) {
        var parent = $j(node).parent().parent(".table-row").attr("parentclass");
        var nodeName = $j(node).parent().parent(".table-row").attr("name");
        var childLocator = "[parentclass='" + parent + "-" + nodeName + "']";
        var childNodeClass = (parent + "." + nodeName).replace(/\./g, "-").replace(/\s/g, "-");
        if ($j(node).hasClass('icon-plus-sign')) {
            $j(node).removeClass('icon-plus-sign');
            $j(node).addClass('icon-minus-sign');
            $j(childLocator).show();
        } else {
            $j(node).removeClass('icon-minus-sign');
            $j(node).addClass('icon-plus-sign');
            $j(childLocator).hide();
            hideChilds($j(childLocator));
        }
    };

    var hideChilds = function(childs) {
        childs.each(function() {
            var parent = $j(this).parent().parent(".table-row").attr("parentclass");
            var nodeName = $j(this).parent().parent(".table-row").attr("name");
            var childLocator = "[parentclass='" + parent + "-" + nodeName + "']";

            if ($j(this).find('.icon').hasClass('icon-minus-sign')) {
                $j(this).find('.icon').removeClass('icon-minus-sign');
                $j(this).find('.icon').addClass('icon-plus-sign');
            }
            var childElements = $j(childLocator);
            childElements.hide();
            hideChilds(childElements);
        });

    };

    $j(".table .table-row .icon").click(function() {
        toggleHandler(this);
    });
    checkBoxEvents();
}

function checkBoxEvents() {
    $j("input[type='checkbox']").change(function() {
        reevaluateChartData = true;
        if (this.checked) {
            checkChildren(this, true);
            checkParent(this);
            checked.push(this.id);
        } else {
            checkChildren(this, false);
            checkParent(this);
            checked.pop(this.id);
        }
    });
}

function checkChildren(node, checked) {
    var parent = $j(node).attr("parentclass");
    var nodeName = $j(node).attr("result-name");
    var childLocator = "[parentclass='" + parent + "-" + nodeName + "']";
    var childElements = $j(childLocator);
    childElements.find("input[type='checkbox']").prop("checked", checked);
    childElements.each(function() {
        checkChildren(this, checked)
    });
}

function checkParent(node) {
    var parent = $j(node).attr("parentclass");
    var childLocator = "[parentclass='" + parent + "']";
    var childElements = $j(childLocator);
    var childCheckBoxes = childElements.find("input[type='checkbox']");
    var selectParent = true;
    childCheckBoxes.each(function() {
        if ($j(this).prop("checked") != true) {
            selectParent = false;
        }
    });
    var parentCheckBox = $j("." + parent).find("input[type='checkbox']");
    parentCheckBox.prop("checked", selectParent);
    if ((parentCheckBox.size() > 0) && ($j(parentCheckBox).attr("parentclass") != 'base')) {
        checkParent(parentCheckBox);
    }
}
