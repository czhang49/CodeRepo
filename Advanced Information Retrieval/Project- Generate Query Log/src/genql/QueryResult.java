/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package genql;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author amir
 */
public class QueryResult {

    int rank;
    String doc;
    double score;

    public void setDoc(String doc) {
        this.doc = doc;
    }

    public void setRank(int rank) {
        this.rank = rank;
    }

    public void setScore(double score) {
        this.score = score;
    }

    public String getDoc() {
        return doc;
    }

    public int getRank() {
        return rank;
    }

    public double getScore() {
        return score;
    }

    public QueryResult() {
    }

    public QueryResult(int rank, String doc, double score) {
        this.rank = rank;
        this.doc = doc;
        this.score = score;
    }

    public static List<QueryResult> readQueryResultFile(String filepath, Integer limit) {
        List<QueryResult> list = new ArrayList<>();
        final List<String> lines;
        if (limit != null) {
            lines = IOUtils.readFileLineByLine(filepath, limit, false);
        } else {
            lines = IOUtils.readFileLineByLine(filepath, false);

        }
        for (String l : lines) {
            String[] split = l.split("\\t");
            if (split.length == 3) {
                QueryResult qr = new QueryResult(Integer.parseInt(split[0]), split[1], Double.parseDouble(split[2]));
                list.add(qr);
            }
        }
        return list;
    }

    public static List<QueryResult> readQueryResultFile(String filepath) {
        return readQueryResultFile(filepath, null);
    }

    public static void writeQueryResultFile(List<QueryResult> list, String filepath) {
        StringBuilder sb = new StringBuilder();
        for (QueryResult qr : list) {
            sb.append(qr.rank).append("\t").append(qr.doc).append("\t").append(qr.score).append("\n");
        }
        IOUtils.writeDataIntoFile(sb.toString(), filepath);
    }

    @Override
    protected Object clone() {
        QueryResult qr = new QueryResult();
        qr.setDoc(this.doc);
        qr.setRank(this.rank);
        qr.setScore(this.score);
        return qr;
    }

}
