package org.jenkinsci.plugins.testresultsanalyzer;

import hudson.model.Action;
import hudson.model.Item;
import hudson.model.AbstractProject;
import hudson.model.Actionable;
import hudson.model.Run;
import hudson.model.Job;
import hudson.tasks.junit.PackageResult;
import hudson.tasks.junit.TestResult;
import hudson.tasks.test.AbstractTestResultAction;
import hudson.util.RunList;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import org.jenkinsci.plugins.testresultsanalyzer.result.data.ResultData;
import org.jenkinsci.plugins.testresultsanalyzer.result.info.PackageInfo;
import org.jenkinsci.plugins.testresultsanalyzer.result.info.ResultInfo;
import org.kohsuke.stapler.bind.JavaScriptMethod;

public class TestResultsAnalyzerAction extends Actionable implements Action{
@SuppressWarnings("rawtypes") AbstractProject project;
    private List<Integer> builds = new ArrayList<Integer>() ;

    ResultInfo resultInfo;


    public TestResultsAnalyzerAction(@SuppressWarnings("rawtypes") AbstractProject project){
        this.project = project;
    }

    /**
     * Gets all the dependant jobs of the AbstractProject. If in a module already
     * will only find one job and return an empty string. If not yet in a module,
     * will find multiple jobs and will create an HTML list containing links to the
     * appropriate plugin pages for each module.
     *
     * @return the HTML list of link to modules or an empty string
     */
    public String getModuleList() {
        Collection<Job> allJobs = project.getAllJobs();
        ArrayList<Job> jobList = new ArrayList<Job>(allJobs);
        String ret = "";
        int numJobs = jobList.size();
        if (numJobs > 1) {
            ret = "<h1>Select a module to analyze:</h1><ul>";
            for (int i=0; i < numJobs; i++){
                String displayName = jobList.get(i).getDisplayName();
                String name = jobList.get(i).getFullName();
                if (name.indexOf('/') != -1) { // forward slash in getFullName means this Job is a module
                    ret += "<li><h2><a href='../../"+name+"/"+Constants.URL+"'>"+displayName+"</a></h2></li>";
                }
            }
            ret += "</ul>";
        }
        return ret;
    }

    /**
     * The display name for the action.
     *
     * @return the name as String
     */
    public final String getDisplayName() {
        return this.hasPermission() ? Constants.NAME : null;
    }

    /**
     * The icon for this action.
     *
     * @return the icon file as String
     */
    public final String getIconFileName() {
        return this.hasPermission() ? Constants.ICONFILENAME : null;
    }

    /**
     * The url for this action.
     *
     * @return the url as String
     */
    public String getUrlName() {
        return this.hasPermission() ? Constants.URL : null;
    }

    /**
     * Search url for this action.
     *
     * @return the url as String
     */
    public String getSearchUrl() {
        return this.hasPermission() ? Constants.URL : null;
    }

    /**
     * Checks if the user has CONFIGURE permission.
     *
     * @return true - user has permission, false - no permission.
     */
    private boolean hasPermission() {
        return project.hasPermission(Item.READ);
    }

    @SuppressWarnings("rawtypes")
    public AbstractProject getProject(){
        return this.project;
    }


    @JavaScriptMethod
    public JSONArray getNoOfBuilds(String noOfbuildsNeeded) {
        JSONArray jsonArray;
        int noOfBuilds = getNoOfBuildRequired(noOfbuildsNeeded);

        jsonArray = getBuildsArray(getBuildList(noOfBuilds));

        return jsonArray;
    }

    private JSONArray getBuildsArray(List<Integer> buildList) {
        JSONArray jsonArray = new JSONArray();
        for (Integer build : buildList) {
            jsonArray.add(build);
        }
        return jsonArray;
    }

    private List<Integer> getBuildList(int noOfBuilds) {
        if ((noOfBuilds <= 0) || (noOfBuilds >= builds.size())) {
            return builds;
        }
        List<Integer> buildList = new ArrayList<Integer>();
        for (int i = 0; i <= (noOfBuilds - 1); i++) {
            buildList.add(builds.get(i));
        }
        return buildList;
    }

    private int getNoOfBuildRequired(String noOfbuildsNeeded){
        int noOfBuilds;
        try {
            noOfBuilds = Integer.parseInt(noOfbuildsNeeded);
        } catch (NumberFormatException e) {
            noOfBuilds = -1;
        }
        return noOfBuilds;
    }

    public boolean isUpdated(){
        int latestBuildNumber = project.getLastBuild().getNumber();
        return !(builds.contains(latestBuildNumber));
    }

    @SuppressWarnings({ "rawtypes", "unchecked" })
    public void getJsonLoadData() {
        if (isUpdated()) {
            resultInfo = new ResultInfo();
            builds = new ArrayList<Integer>();
            RunList<Run> runs = project.getBuilds();
            Iterator<Run> runIterator = runs.iterator();
            while (runIterator.hasNext()) {
                Run run = runIterator.next();
                int buildNumber = run.getNumber();
                builds.add(run.getNumber());
                List<AbstractTestResultAction> testActions = run.getActions(hudson.tasks.test.AbstractTestResultAction.class);
                for (hudson.tasks.test.AbstractTestResultAction testAction : testActions) {
                    TestResult testResult = (TestResult) testAction.getResult();
                    Collection<PackageResult> packageResults = testResult.getChildren();
                    for (PackageResult packageResult : packageResults) { // packageresult
                        resultInfo.addPackage(buildNumber, packageResult);
                    }
                }
            }
        }
    }

    /**
     * A bridge function connecting the front-end with back-end data stores.
     * This function is invoked by populateTemplate(), and calls
     * jsTreeUtils.getJsTree() to retrieve a JSONObject containing test results.
     * @method getTreeResult
     * @param noOfBuildsNeeded An integer denoting the number of builds needed
     * @param statusFilter The string indicator for filtering test cases/suites
     * @return The generated JSON object containing test results
     */
    @JavaScriptMethod
    public JSONObject getTreeResult(String noOfBuildsNeeded, String statusFilter) {
        int noOfBuilds = getNoOfBuildRequired(noOfBuildsNeeded);
        List<Integer> buildList = getBuildList(noOfBuilds);

        JsTreeUtil jsTreeUtils = new JsTreeUtil();
        return jsTreeUtils.getJsTree(buildList, resultInfo, statusFilter);
    }

    /**
     * A bridge function connecting the front-end with back-end data stores.
     * This function is invoked by populateTemplateCondensed(), and calls
     * jsTreeUtils.getJsTree() to retrieve a JSONObject containing condensed
     * statistics about the test results.
     * @method getTreeResultCondensed
     * @param noOfBuildsNeeded An integer denoting the number of builds needed
     * @param statusFilter The string indicator for filtering test cases/suites
     * @return The generated JSONObject containing condensed test results stats
     */
    @JavaScriptMethod
    public JSONObject getTreeResultCondensed(String noOfBuildsNeeded, String statusFilter) {
        int noOfBuilds = getNoOfBuildRequired(noOfBuildsNeeded);
        List<Integer> buildList = getBuildList(noOfBuilds);
        List<Integer> buildCondense = getBuildList(3);

        JsTreeUtil jsTreeUtils = new JsTreeUtil();
        return jsTreeUtils.getJsTreeCondensed(buildCondense, buildList, resultInfo, statusFilter);
    }

    /**
     * Generates a string containing names of all the test cases whose results
     * in the last two builds are different.
     * @method getLastTwoBuilds
     * @return The generated string
     */
    public String getLastTwoBuilds() {
        String ret = "Last two builds: \n";
        Map<String,PackageInfo> results = resultInfo.getPackageResults();
        Iterator it = results.keySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, PackageInfo> pair = (Map.Entry<String, PackageInfo>) it.next();
            PackageInfo info = pair.getValue();
            Map<Integer,ResltData> buildResults = info.getBuildPackageResults();
            if (buildResults.keySet().size() >= 2) {// need at least two builds to be able to compare
                Iterator resultIt = buildResults.entrySet().iterator();
                Map.Entry<Integer, ResultData> firstEntry = (Entry<Integer, ResultData>) resultIt.next();
                Map.Entry<Integer, ResultData> secondEntry = (Entry<Integer, ResultData>) resultIt.next();
                ResultData firstBuild = firstEntry.getValue();
                ResultData secondBuild = secondEntry.getValue();
                if (firstBuild.isPassed() != secondBuild.isPassed()) {
                    ret += firstBuild.getName() + " changed.\n";
                }
            }
        }
        return ret;
    }

}
