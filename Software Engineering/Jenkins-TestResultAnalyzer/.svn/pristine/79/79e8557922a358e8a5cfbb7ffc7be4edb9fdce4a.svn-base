package org.jenkinsci.plugins.testresultsanalyzer;

import java.util.List;
import java.util.Set;

import org.jenkinsci.plugins.testresultsanalyzer.result.info.ResultInfo;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

public class JsTreeUtil {

    public JSONObject getJsTree(List<Integer> builds, ResultInfo resultInfo, String statusFilter) {
        JSONObject tree = new JSONObject();

        JSONArray buildJson = new JSONArray();
        for (Integer buildNumber : builds) {
            buildJson.add(buildNumber.toString());
        }
        tree.put("builds", buildJson);
        JSONObject packageResults = resultInfo.getJsonObject();
        JSONArray results = new JSONArray();
        for (Object packageName : packageResults.keySet()) {

            JSONObject packageJson = packageResults.getJSONObject((String) packageName);
            JSONObject subtree = createJson(builds, packageJson, statusFilter);
            if (subtree != null) {
                results.add(subtree);
            }
        }
        tree.put("results", results);
        return tree;
    }

    private JSONObject getBaseJson() {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("text", "");
        jsonObject.put("buildResults", new JSONArray());
        return jsonObject;
    }

    private JSONObject createJson(List<Integer> builds, JSONObject dataJson, String statusFilter) {
        JSONObject baseJson = getBaseJson();
        baseJson.put("text", dataJson.get("name"));
        baseJson.put("type", dataJson.get("type"));
        baseJson.put("buildStatuses", dataJson.get("buildStatuses"));
        JSONObject packageBuilds = dataJson.getJSONObject("builds");
        JSONArray treeDataJson = new JSONArray();
        boolean addToTree = false;
        if (statusFilter.equals("all")) {
            addToTree = true;
        }
        for (Integer buildNumber : builds) {
            JSONObject build = new JSONObject();
            if (packageBuilds.containsKey(buildNumber.toString())) {
                JSONObject buildResult = packageBuilds.getJSONObject(buildNumber.toString());
                buildResult.put("buildNumber", buildNumber.toString());
                build = buildResult;
                String status = buildResult.getString("status");
                if (status.equals(statusFilter)) {
                    addToTree = true;
                }
            } else {
                build.put("status", "N/A");
                build.put("buildNumber", buildNumber.toString());
            }
            treeDataJson.add(build);
        }
        if (!addToTree) {
            return null;
        }
        baseJson.put("buildResults", treeDataJson);

        if (dataJson.containsKey("children")) {
            JSONArray childrens = new JSONArray();
            JSONObject childrenJson = dataJson.getJSONObject("children");
            @SuppressWarnings("unchecked")
            Set<String> childeSet = (Set<String>) childrenJson.keySet();
            for (String childName : childeSet) {
                JSONObject subtree = createJson(builds, childrenJson.getJSONObject(childName), statusFilter);
                if (subtree != null) {
                    childrens.add(subtree);
                }
            }
            baseJson.put("children", childrens);
        }

        return baseJson;
    }
}
