package org.jenkinsci.plugins.testresultsanalyzer;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.*;
import hudson.model.FreeStyleBuild;
import hudson.model.FreeStyleProject;
import hudson.tasks.junit.PackageResult;
import net.sf.json.JSONObject;
import net.sf.json.JSONArray;

import java.util.ArrayList;
import java.util.List;

import org.jenkinsci.plugins.testresultsanalyzer.result.info.ResultInfo;
import org.jenkinsci.plugins.testresultsanalyzer.JsTreeUtil;
import org.junit.Rule;
import org.junit.Test;
import org.jvnet.hudson.test.JenkinsRule;

public class JsTreeUtilTest {
	@Rule
	public JenkinsRule j = new JenkinsRule();

	@Test
	public void testGetJsTree() throws Exception {
		FreeStyleProject project = j.createFreeStyleProject();
		FreeStyleBuild build = project.scheduleBuild2(0).get();
		FreeStyleBuild build2 = project.scheduleBuild2(0).get();

		ArrayList<Integer> arl = new ArrayList<Integer>();
		arl.add(1);
		arl.add(2);
		arl.add(3);
		arl.add(4);
		ResultInfo resultInfo = new ResultInfo();
		String statusFilter = "hello";
		JsTreeUtil util = new JsTreeUtil();

		JSONObject jsonObject = util.getJsTree(arl, resultInfo, statusFilter);
		System.out.println(jsonObject.toString());
		assertFalse(jsonObject.toString().equals(""));
		assertTrue(jsonObject instanceof JSONObject);
		

	}

	@Test
	public void testGetJsTree2() throws Exception {
		FreeStyleProject project = j.createFreeStyleProject();
		FreeStyleBuild build = project.scheduleBuild2(0).get();
		FreeStyleBuild build2 = project.scheduleBuild2(0).get();

		ArrayList<Integer> buildsCondense = new ArrayList<Integer>();
		ArrayList<Integer> builds = new ArrayList<Integer>();
		builds.add(1);
		builds.add(2);
		builds.add(3);
		builds.add(4);
		ResultInfo resultInfo = new ResultInfo();
		String statusFilter = "hello";
		JsTreeUtil util = new JsTreeUtil();

		JSONObject jsonObject = util.getJsTree2(buildsCondense, builds, resultInfo, statusFilter);
		System.out.println(jsonObject.toString());
		assertFalse(jsonObject.toString().equals(""));
		assertTrue(jsonObject instanceof JSONObject);

	}



}