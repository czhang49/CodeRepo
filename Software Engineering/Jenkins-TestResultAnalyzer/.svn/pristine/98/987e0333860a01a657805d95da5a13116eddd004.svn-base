package org.jenkinsci.plugins.testresultsanalyzer;

import static org.junit.Assert.assertEquals;
import hudson.model.FreeStyleBuild;
import hudson.model.FreeStyleProject;
import hudson.tasks.junit.PackageResult;
import net.sf.json.JSONObject;

import org.jenkinsci.plugins.testresultsanalyzer.result.info.ResultInfo;
import org.junit.Rule;
import org.junit.Test;
import org.jvnet.hudson.test.JenkinsRule;

public class TestResultsAnalyzerActionTest {
	@Rule
	public JenkinsRule j = new JenkinsRule();

	@Test
	public void testGetTreeResult1() throws Exception {
		FreeStyleProject project = j.createFreeStyleProject();
		FreeStyleBuild build = project.scheduleBuild2(0).get();
		FreeStyleBuild build2 = project.scheduleBuild2(0).get();

		TestResultsAnalyzerAction action = new TestResultsAnalyzerAction(
				project);
		action.getJsonLoadData();
		JSONObject jsonObj = action.getTreeResult("2", "PASSED");
		System.out.println(jsonObj.toString());
		assertEquals("{\"builds\":[\"2\",\"1\"],\"results\":[]}",
				jsonObj.toString());
	}

	@Test
	public void testGetTreeResult2() throws Exception {
		FreeStyleProject project = j.createFreeStyleProject();
		FreeStyleBuild build = project.scheduleBuild2(0).get();
		FreeStyleBuild build2 = project.scheduleBuild2(0).get();
		FreeStyleBuild build3 = project.scheduleBuild2(0).get();
		FreeStyleBuild build4 = project.scheduleBuild2(0).get();

		TestResultsAnalyzerAction action = new TestResultsAnalyzerAction(
				project);
		action.getJsonLoadData();

		JSONObject jsonObj = action.getTreeResult("2", "all");
		assertEquals("{\"builds\":[\"4\",\"3\"],\"results\":[]}",
				jsonObj.toString());
		jsonObj = action.getTreeResult("5", "all");
		assertEquals("{\"builds\":[\"4\",\"3\",\"2\",\"1\"],\"results\":[]}",
				jsonObj.toString());
	}

	@Test
	public void testGetLastTwoBuilds() throws Exception {
		FreeStyleProject project = j.createFreeStyleProject();

		TestResultsAnalyzerAction action = new TestResultsAnalyzerAction(
				project);
		action.resultInfo = new ResultInfo();
		
		System.out.println(action.getLastTwoBuilds());
	}
}
