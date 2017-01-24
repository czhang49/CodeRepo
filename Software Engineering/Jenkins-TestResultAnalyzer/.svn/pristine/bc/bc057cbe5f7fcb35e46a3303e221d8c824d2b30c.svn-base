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
//import org.jvnet.hudson.test.HudsonTestCase; 

import java.net.URL;

public class moduleTest {
    @Rule
    public JenkinsRule j = new JenkinsRule();

    public void testGetModuleList() throws Exception {
//        j.configureMaven3();
        //URL classURL = (URL) (getClass().getProtectionDomain().getCodeSource().getLocation()+"../../../src/test/sample-project.zip");
        //System.out.println("Class URL: " + classURL);
        //assertEquals("", classURL);jobs/banana/workspace/trunk/src/test/sample-project.zip 
        //expected:<> but was:<file:/home/sapin2/.jenkins/jobs/banana/workspace/trunk/target/test-classes/>
        //MavenModuleSet project = j.createMavenProject("project1");
        FreeStyleProject project = j.createFreeStyleProject("project1");
        project.setScm(new ExtractResourceSCM(getClass().getResource("/sample-project.zip")));

//        project.setScm(new SingleFileSCM ("build.xml", getClass().getResource("build.xml")));
//        assertBuildStatusSuccess(project.scheduleBuild2(0));
        assertTrue(true);
    }
}
