package genql;

import java.util.*;

public class BigramIndex extends genql.Index {

    /**
     * The index as a hashtable.
     */
    private HashMap<String, HashMap<String, genql.PostingsList>> index = new HashMap<String, HashMap<String, genql.PostingsList>>();
    private String previous = null;
    private int currentDocID = -1;

    private int nbigrams = 0;

    /**
     * Inserts this token in the index, linked to the previous word (bigram)
     */
    public void insert(String token, int docID, int offset) {

        HashMap<String, genql.PostingsList> map;

        if (currentDocID != docID) {
            previous = null;
            currentDocID = docID;
        }

        if (previous == null) {
            previous = token;
            return;
        }

        map = index.get(previous);
        if (map == null) {
            map = new HashMap<String, genql.PostingsList>();
            index.put(previous, map);
        }

        genql.PostingsList ps = map.get(token);
        if (ps == null) {
            ps = new genql.PostingsList(token);
            map.put(token, ps);
            ++nbigrams;
        }

        ps.addToken(docID, -1, null);
        previous = token;
    }

    /**
     * Returns all the words in the index.
     */
    public Iterator<String> getDictionary() {
        return index.keySet().iterator();
    }

    /**
     * Returns the postings for a specific term, or null if the term is not in
     * the index.
     */
    public genql.PostingsList getPostings(String token1, String token2) {
        HashMap<String, genql.PostingsList> map = index.get(token1);
        if (map != null) {
            return map.get(token2);
        }
        return null;
    }

    public genql.PostingsList search(genql.Query query, int queryType, int rankingType, int structureType) {
        genql.PostingsList ps = new genql.PostingsList();
        LinkedList<String> tokens = query.terms;

        if (queryType == genql.Index.RANKED_QUERY && rankingType == genql.Index.TF_IDF && structureType == genql.Index.BIGRAM) {
            int tokenIdx = 0;
            double tfidfScore, cos_sim;
            genql.Vector queryVector = null;
            HashMap<Integer, genql.Vector> docVectors = null;
            genql.PostingsEntry pe;
            TreeSet<genql.PostingsEntry> pagerankedDocs = null;
            genql.PostingsEntry[] docArray;

            //TF-IDF QUERY
            // Query vector
            if (query.vector == null) {
                queryVector = genql.Vector.ones(tokens.size() - 1);
                queryVector.normalize();
            } else {
                queryVector = query.vector;
            }
            docVectors = new HashMap<Integer, genql.Vector>();

            // RANKED QUERY
            // Compute the TF-IDF vectors for each document
            String previousTk = null;
            for (String token : tokens) {
                if (previousTk == null) {
                    previousTk = token;
                    continue;
                }

                genql.PostingsList tokenPostings = getPostings(previousTk, token);
                if (tokenPostings != null) {
                    for (genql.PostingsEntry entry : tokenPostings.postingsEntries) {
                        genql.Vector v = docVectors.get(entry.docID);
                        if (v == null) {
                            v = new genql.Vector(tokens.size() - 1);
                            docVectors.put(entry.docID, v);
                        }

                        // Update the TF-IDF score of one term for one document
                        tfidfScore = entry.score * Math.log10(nbigrams / (double) tokenPostings.postingsEntries.size());
                        v.set(tokenIdx, tfidfScore);
                    }
                }
                ++tokenIdx;
                previousTk = token;
            }

            // Compute the cosine similarity score of each document
            docArray = new genql.PostingsEntry[docVectors.size()];
            int i = 0;
            Iterator<Map.Entry<Integer, genql.Vector>> iter = docVectors.entrySet().iterator();

            while (iter.hasNext()) {
                Map.Entry pair = iter.next();
                pe = new genql.PostingsEntry((Integer) pair.getKey());
                //((src.Vector)pair.getValue()).normalize();

                ((genql.Vector) pair.getValue()).divide(docNorm.get((Integer) pair.getKey()));

                cos_sim = queryVector.cosineSimilarity((genql.Vector) pair.getValue());

                pe.score = cos_sim;
                docArray[i] = pe;
                ++i;
            }

            // Sort the results
            Arrays.sort(docArray);
            for (genql.PostingsEntry tmp : docArray) {
                ps.postingsEntries.add(tmp);
            }
        }
        return ps;
    }

    public void indexingOver() {
        updateEntryScores();
        computeDocumentNorms();
    }

    public void cleanup() {
    }

    private void updateEntryScores() {
        for (HashMap<String, genql.PostingsList> map : index.values()) {
            for (genql.PostingsList ps : map.values()) {
                for (genql.PostingsEntry pe : ps.postingsEntries) {
                    pe.score /= docLengths.get("" + pe.docID);
                }
            }
        }
    }

    private void computeDocumentNorms() {
        System.out.println("Computing document norms...");
        for (HashMap<String, genql.PostingsList> map : index.values()) {
            for (genql.PostingsList ps2 : map.values()) {
                for (genql.PostingsEntry pe : ps2.postingsEntries) {
                    Double score = docNorm.get(pe.docID);
                    if (score == null) {
                        score = 0.0;
                    }
                    score += pe.score * Math.log10(nbigrams / (double) ps2.postingsEntries.size());
                    docNorm.put(pe.docID, score);
                }
            }
        }
        System.out.println("Done");
    }

    public genql.PostingsList getPostings(String token) {
        return null;
    }

    public void nextDoc() {
    }

    public boolean importIndex() {
        return false;
    }
}
