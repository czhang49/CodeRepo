package org.jenkinsci.plugins.testresultsanalyzer;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import hudson.model.FreeStyleBuild;
import hudson.model.FreeStyleProject;
import hudson.maven.MavenModuleSet;
import hudson.tasks.junit.PackageResult;
import net.sf.json.JSONObject;

import org.jenkinsci.plugins.testresultsanalyzer.result.info.ResultInfo;
import org.junit.Rule;
import org.junit.Test;
import org.jvnet.hudson.test.JenkinsRule;
import org.jvnet.hudson.test.ExtractResourceSCM;
import org.jvnet.hudson.test.SingleFileSCM;

import java.net.URL;

public class moduleTest {
    @Rule
    public JenkinsRule j = new JenkinsRule();

    public void testGetModuleList() throws Exception {
        FreeStyleProject project = j.createFreeStyleProject("project1");
        project.setScm(new ExtractResourceSCM(getClass().getResource("/sample-project.zip")));
        assertTrue(true);
    }
}
