package genql;

import java.io.*;
import java.util.*;

/**
 * Implements an inverted index as a Hashtable from words to PostingsLists.
 */
public class HashedIndex extends Index {

    /**
     * The index as a hashtable.
     */
    public HashMap<String, PostingsList> index = new HashMap<String, PostingsList>();

    /**
     * Tree containing the 10% most popular postingslist sorted by popularity
     */
    private TreeSet<PostingsList> popularitySet = new TreeSet<PostingsList>();
    private Iterator<PostingsList> popularityIterator;
    private int popularityIteratorIdx = -1;
    private int docElapsed = 0;
    private int doc_counter = 0;
    private int requests_counter = 0;
    private static final String POPULARITY_FILE_NAME = "tree_set";
    private static final String DOCUMENT_ID_FILE_NAME = "doc_id_map";
    private static final String INDEX_FILE_NAME = "global_index_map";
    private static final String DOCUMENT_LENGTH_FILE_NAME = "doc_length_map";
    private static final String PAGERANKS_FILE_NAME = "map_page_ranks";
    private int word_threshold;

    private static final boolean CACHE = false;
    private static final boolean CLEAN_CACHE = false;
    private static final boolean GLOBAL_CACHE = false;
    private static final String CACHE_PATH = "./cache/";

    private static final int TF_IDF_WEIGHT = 5;
    private static final int PAGERANK_WEIGHT = 5;

    /**
     * Each X documents, words below popularity threshold (Y %) are removed from
     * memory
     */
    private static final int DOC_ELAPSED_THRESHOLD = 1000; //1000 docs
    /**
     * Percentage of words kept in memory
     */
    private static final int WORD_MEMORY_THRESHOLD = 0; //1%
    /**
     * Minimum number of words always in memory (used while indexing until the
     * percentage above gets higher)
     */
    private static final int MIN_WORD_MEMORY = 10; //1000
    /**
     * The unpopular tokens (after the word threshold) are removed every N
     * queries
     */
    private static final int REQUESTS_BEFORE_CLEANING = 3;

    /**
     * If true, displays the processing time for a query
     */
    private static final boolean DISPLAY_QUERY_TIME = true;

    /**
     * ===== RELEVANCE FEEDBACK =====
     */
    private static final boolean UNINVERTED_INDEX = true;
    /**
     * Uninverted index - Key: document ID - Value: Hashmap: - Key: word -
     * Value: Frequency in the current document
     */
    HashMap<Integer, HashMap<String, Integer>> uninverted_index = new HashMap<Integer, HashMap<String, Integer>>();
    private int tmpUninvertedDocID = -1;
    private HashMap<String, Integer> tmpUninvertedDoc = null;

    /**
     * ===== RANKED RETRIEVAL SPEED UP =====
     */
    /**
     * Ranked query prerequisite - The query will return every document
     * containing at least N words of the query (union if 0). Disabled if value
     * is <= 1
     */
    private static final int RANKED_TERMS = 1;

    /**
     * - Key: word - Value: Array of pairs <DocID, TF-IDF score>
     */
    private HashMap<String, ArrayList<AbstractMap.SimpleEntry<Integer, Double>>> tfidfScores = new HashMap<String, ArrayList<AbstractMap.SimpleEntry<Integer, Double>>>();
    /**
     * Used to speedup the ranked query. At indexing, the N highest TF-IDF
     * scores are kept in memory and used by ranked retrieval Integer.MAX_VALUE
     * to disable
     */
    private static final int RANKED_DOC_PER_WORD = Integer.MAX_VALUE;

    /**
     * Inserts this token in the index.
     */
    public void insert(String token, int docID, int offset) {
        PostingsList ps = index.get(token);
        if (ps == null) {
            ps = new PostingsList(token);
            index.put(token, ps);
            popularitySet.add(ps);
        } else if (!GLOBAL_CACHE) {
            popularitySet.remove(ps);
            ps.increasePopularity();
            popularitySet.add(ps);
        }

        ps.addToken(docID, offset, null);

        insert_uninverted(token, docID);
    }

    public void insert_uninverted(String token, int docID) {
        if (UNINVERTED_INDEX) {
            HashMap<String, Integer> doc;

            if (docID == tmpUninvertedDocID) {
                doc = tmpUninvertedDoc;
            } else {
                doc = uninverted_index.get(docID);
                if (doc == null) {
                    doc = new HashMap<String, Integer>();
                    uninverted_index.put(docID, doc);
                }
                tmpUninvertedDoc = doc;
                tmpUninvertedDocID = docID;
            }

            Integer count = doc.get(token);
            if (count == null) {
                doc.put(token, 1);
            } else {
                doc.put(token, count + 1);
            }
        }
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
    public PostingsList getPostings(String token) {
        return index.get(token);
    }

    private List<Integer> getSentencePositions(List<ListIterator<Integer>> offsetIterators) {
        List<Integer> positions = new LinkedList<Integer>();
        // Iterator on the lists of offsets
        Iterator<ListIterator<Integer>> offsetIterIterator = offsetIterators.iterator();
        ListIterator<Integer> pp0 = offsetIterIterator.next(), pp2;
        int tmp0, tmp1, tmp2;
        boolean sentence;

        // For each offset of the first list
        while (pp0.hasNext()) {
            tmp0 = pp0.next();
            tmp1 = tmp0;
            sentence = true;

            // For every other list of offsets, we check if if contains an offset following the previous one
            while (offsetIterIterator.hasNext()) {
                pp2 = offsetIterIterator.next();

                // While the current offset is lower than the previous one
                while (pp2.hasNext() && pp2.next() < tmp1) ;
                tmp2 = pp2.previous();
                // If the second word is not exactly after the previous one
                if (tmp2 != tmp1 + 1) {
                    // The previous word position cannot lead to a sentence, we jump to the next one
                    sentence = false;
                    break;
                }
                // The second word follows the previous one, we try the others
                pp2.next();
                tmp1 = tmp2;
            }

            // The document contains the right sentence
            if (sentence) {
                positions.add(tmp0);
            }

            // Position the list iterator on the first list of offsets
            offsetIterIterator = offsetIterators.iterator();
            // The first iterator is already known
            offsetIterIterator.next();
        }

        return positions;
    }

    private PostingsList getIntersectionPostings(List<String> tokens, int queryType) {
        PostingsList result = new PostingsList();
        // For each token, a list of documents (a document is a PostingsEntry containing a list of offsets)
        LinkedList<ListIterator<PostingsEntry>> docsIterators = new LinkedList<ListIterator<PostingsEntry>>();
        LinkedList<PostingsList> tokensPostings = new LinkedList<PostingsList>();
        int maxDocID, nlists = 0, tmp;
        int[] wordFrequencies = new int[tokens.size()];

        // Postings retrieval
        for (String t : tokens) {
            PostingsList postings = getPostings(t);
            if (postings == null) {
                return null;
            }
            tokensPostings.add(postings);
            docsIterators.add(postings.postingsEntriesIterator());
        }

        // We start with the smallest list (heuristic)
        if (queryType == Index.INTERSECTION_QUERY) {
            Collections.sort(tokensPostings, new Comparator<PostingsList>() {
                public int compare(PostingsList a1, PostingsList a2) {
                    return a2.size() - a1.size(); // assuming you want biggest to smallest
                }
            });
            docsIterators.clear();
            for (PostingsList postings : tokensPostings) {
                docsIterators.add(postings.postingsEntriesIterator());
            }
        }

        // While none of the lists have been completely explored
        while (true) {
            // We find the list having the bigger docID among the current iterators
            maxDocID = Integer.MIN_VALUE;
            for (ListIterator<PostingsEntry> iter : docsIterators) {
                if (!iter.hasNext()) {
                    return result;
                }

                tmp = iter.next().docID;
                //We reset the number of iterators positioned at maxDocID
                if (tmp > maxDocID) {
                    maxDocID = tmp;
                    nlists = 1;
                    //We increment the number of iterators positioned at maxDocID
                } else if (tmp == maxDocID) {
                    ++nlists;
                }
            }

            // Every iterator point on the same document ID
            if (nlists == tokens.size()) {
                // Intersection query
                if (queryType == Index.INTERSECTION_QUERY) {
                    result.addToken(maxDocID, -1, null);

                    // Phrase query
                } else if (queryType == Index.PHRASE_QUERY) {
                    LinkedList<ListIterator<Integer>> offsetIterators = new LinkedList<ListIterator<Integer>>();
                    // For each documents iterator (one per token)
                    for (ListIterator<PostingsEntry> iter : docsIterators) {
                        // Add to the list an iterator on the list of offset for a given token and document
                        offsetIterators.add(iter.previous().listIterator());
                        iter.next();
                    }
                    // Retrieve for the given document the starting position of the sentences
                    List<Integer> positions = getSentencePositions(offsetIterators);
                    // If the document contains at least one sentence (
                    if (!positions.isEmpty()) {
                        // It is a result
                        result.addToken(maxDocID, -1, null);
                    }
                }
            } else {
                // For every other list
                for (ListIterator<PostingsEntry> iter : docsIterators) {
                    if (iter.previous().docID != maxDocID) {
                        iter.next();
                        // We iterate until we reach a docID higher or equal, or the end of the list
                        while (iter.hasNext() && iter.next().docID < maxDocID);
                        if (iter.previous().docID < maxDocID) {
                            return result;
                        }
                    }
                }
            }
        }
    }

    private void displayQueryTime(long startTime) {
        if (HashedIndex.DISPLAY_QUERY_TIME) {
            System.out.println(String.format("Query processed in %d nanoseconds", System.nanoTime() - startTime));
        }
    }

    /**
     * Searches the index for postings matching the query.
     */
    public PostingsList search(Query query, int queryType, int rankingType, int structureType) {
        long startTime = System.nanoTime();

        if (!loadTokens(query.terms)) {
            displayQueryTime(startTime);
            return null;
        }

        PostingsList ps = null;

        if (query.size() > 0) {
            if (queryType == Index.INTERSECTION_QUERY || queryType == Index.PHRASE_QUERY) {
                ps = getIntersectionPostings(query.terms, queryType);
            } else if (queryType == Index.RANKED_QUERY) {
                ps = getRankedPostings(query.terms, rankingType, query);
            }
        } else {
            displayQueryTime(startTime);
            return null;
        }

        ++requests_counter;

        // Cleaning unpopular entries
        if (CACHE && requests_counter == REQUESTS_BEFORE_CLEANING) {
            requests_counter = 0;

            Iterator<PostingsList> iter = popularitySet.descendingIterator();
            int i = 0, threshold = word_threshold;

            while (i < threshold && iter.hasNext()) {
                iter.next();
                ++i;
            }
            i = 0;
            if (iter.hasNext()) {
                PostingsList tmp = iter.next();
                while (!tmp.postingsEntries.isEmpty() && iter.hasNext()) {
                    ++i;
                    tmp.postingsEntries.clear();
                    tmp = iter.next();
                }
            }
            System.out.println(String.format("%d tokens removed from memory.", i, popularitySet.size() - i));
        }

        displayQueryTime(startTime);
        return ps;
    }

    /**
     * Save the words populatity
     */
    public void cleanup() {
        if (GLOBAL_CACHE) {
            exportGlobalIndex();
        } else if (CACHE) {
            exportPopularitySet();
        }
    }

    /* ----------------------------------------------- */
 /*                    RANKING                      */
 /* ----------------------------------------------- */
    private void computeDocumentNorms() {
        System.out.println("Computing document norms...");
        int i;
        Double score;
        ArrayList<AbstractMap.SimpleEntry<Integer, Double>> array;

        for (Map.Entry<String, PostingsList> entry : index.entrySet()) {
            array = new ArrayList<AbstractMap.SimpleEntry<Integer, Double>>(entry.getValue().postingsEntries.size());

            for (PostingsEntry pe : entry.getValue().postingsEntries) {
                Double tmp = docNorm.get(pe.docID);
                if (tmp == null) {
                    tmp = 0.0;
                }

                score = pe.score * Math.log(uninverted_index.size() / (double) entry.getValue().postingsEntries.size());
                array.add(new AbstractMap.SimpleEntry<Integer, Double>(pe.docID, score));

                tmp += score;
                docNorm.put(pe.docID, tmp);
            }

            array.sort(new Comparator<AbstractMap.SimpleEntry<Integer, Double>>() {
                public int compare(AbstractMap.SimpleEntry<Integer, Double> e1, AbstractMap.SimpleEntry<Integer, Double> e2) {
                    return Double.compare(e2.getValue(), e1.getValue()); // assuming you want biggest to smallest
                }
            });

            int size = Math.min(array.size(), RANKED_DOC_PER_WORD);
            ArrayList<AbstractMap.SimpleEntry<Integer, Double>> tokenScores = new ArrayList<AbstractMap.SimpleEntry<Integer, Double>>(size);
            i = 0;
            for (AbstractMap.SimpleEntry<Integer, Double> e : array) {
                tokenScores.add(e);
                ++i;
                if (i == size) {
                    break;
                }
            }
            tfidfScores.put(entry.getKey(), tokenScores);
        }
        System.out.println("Done");
    }

    private PostingsList getRankedPostings(List<String> tokens, int rankingType, Query query) {
        class MutableInt {

            int value = 1; // note that we start at 1 since we're counting

            public void increment() {
                ++value;
            }

            public int get() {
                return value;
            }
        }

        int tokenIdx = 0;
        double tfidfScore, cos_sim;
        Vector queryVector = null;
        HashMap<Integer, Vector> docVectors = null;
        PostingsList ps;
        PostingsEntry pe;
        TreeSet<PostingsEntry> pagerankedDocs = null;
        PostingsEntry[] docArray;
        HashMap<Integer, MutableInt> docValidity = null;
        /*
        Set<String> uniqueTokens = new TreeSet<String>();
        uniqueTokens.addAll(tokens);
        tokens.clear();
        tokens.addAll(uniqueTokens);
         */
        // Query vector
        if (query.vector == null) {
            queryVector = Vector.ones(tokens.size());
            queryVector.normalize();
        } else {
            queryVector = query.vector;
        }
        docVectors = new HashMap<Integer, Vector>();

        //Determine for each document whether it contains enough words from the query or not
        int threshold = Math.min(tokens.size(), HashedIndex.RANKED_TERMS);
        if (HashedIndex.RANKED_TERMS > 1) {
            MutableInt count;
            docValidity = new HashMap<Integer, MutableInt>();

            for (String token : tokens) {
                ArrayList<AbstractMap.SimpleEntry<Integer, Double>> scores = tfidfScores.get(token);
                for (AbstractMap.SimpleEntry<Integer, Double> entry : scores) {
                    count = docValidity.get(entry.getKey());
                    if (count == null) {
                        docValidity.put(entry.getKey(), new MutableInt());
                    } else {
                        count.increment();
                    }
                }
            }
        }

        // Compute the TF-IDF vectors for each document
        for (String token : tokens) {
            ArrayList<AbstractMap.SimpleEntry<Integer, Double>> scores = tfidfScores.get(token);
            for (AbstractMap.SimpleEntry<Integer, Double> entry : scores) {
                // Ignore the document if it does not contain enough words from the query
                if (docValidity == null || docValidity.get(entry.getKey()).value >= threshold) {
                    Vector v = docVectors.get(entry.getKey());
                    if (v == null) {
                        v = new Vector(tokens.size());
                        docVectors.put(entry.getKey(), v);
                    }

                    // Update the TF-IDF score of one term for one document
                    tfidfScore = entry.getValue();
                    v.set(tokenIdx, tfidfScore);

                }
            }
            ++tokenIdx;
        }

        // Compute the cosine similarity score of each document
        docArray = new PostingsEntry[docVectors.size()];
        int i = 0;
        Iterator<Map.Entry<Integer, Vector>> iter = docVectors.entrySet().iterator();

        while (iter.hasNext()) {
            Map.Entry pair = iter.next();
            pe = new PostingsEntry((Integer) pair.getKey());

            ((Vector) pair.getValue()).divide(docNorm.get((Integer) pair.getKey()));

            cos_sim = queryVector.cosineSimilarity((Vector) pair.getValue());

            if (rankingType == Index.TF_IDF) {
                pe.score = cos_sim;
            }
            docArray[i] = pe;
            ++i;
        }

        // Sort the results
        Arrays.sort(docArray);
        ps = new PostingsList();
        for (PostingsEntry tmp : docArray) {
            ps.postingsEntries.add(tmp);
        }

        return ps;
    }

    public double getTfIdfScore(String token, Integer docID) {
        ArrayList<AbstractMap.SimpleEntry<Integer, Double>> scores = tfidfScores.get(token);
        for (AbstractMap.SimpleEntry<Integer, Double> entry : scores) {
            if (entry.getKey().equals(docID)) {
                return entry.getValue();
            }
        }
        return 0;
    }


    /* ----------------------------------------------- */
 /*                     CACHE                       */
 /* ----------------------------------------------- */
    public void nextDoc() {
        ++docElapsed;
        if (docElapsed == DOC_ELAPSED_THRESHOLD && CACHE && !GLOBAL_CACHE) {
            ++doc_counter;
            System.out.println(String.format("%d documents indexed", doc_counter * DOC_ELAPSED_THRESHOLD));
            indexingThresholdReached();
            docElapsed = 0;
        }
    }

    private void updatePostingsFile(PostingsList ps) {
        File f = new File(CACHE_PATH + ps.token);
        // Merge the existing postings list with the one on the disk
        if (f.exists()) {
            PostingsList tmp = new PostingsList();
            try {
                // Read the existing postings list from the disk
                ObjectInputStream input = new ObjectInputStream(new FileInputStream(f));
                tmp.postingsEntries = (LinkedList<PostingsEntry>) input.readObject();
                input.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
            // Merge the two postings list
            for (PostingsEntry pe : ps.postingsEntries) {
                tmp.addToken(pe.docID, -1, pe);
            }
            ps.postingsEntries = tmp.postingsEntries;
        }
        // Write the postings list on the disk
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(f));
            oos.writeObject(ps.postingsEntries);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void indexingThresholdReached() {
        updateWordThreshold();
        PostingsList ps = getNextUnpopularPostingsList();
        while (ps != null && !ps.postingsEntries.isEmpty()) {
            updatePostingsFile(ps);
            // Clear memory
            ps.clear();
            ps = getNextUnpopularPostingsList();
        }
    }

    private void exportGlobalIndex() {
        System.out.println("Exporting global index...");
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(CACHE_PATH + INDEX_FILE_NAME));
            oos.writeObject(index);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void exportDocumentsLength() {
        System.out.println("Exporting documents length...");
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(CACHE_PATH + DOCUMENT_LENGTH_FILE_NAME));
            oos.writeObject(super.docLengths);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void exportDocumentIDs() {
        System.out.println("Exporting documents ID...");
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(CACHE_PATH + DOCUMENT_ID_FILE_NAME));
            oos.writeObject(super.docIDs);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void exportPopularitySet() {
        System.out.println("Exporting popularity set...");
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(CACHE_PATH + POPULARITY_FILE_NAME));
            oos.writeObject(popularitySet);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Insert in the map the words required by the query and update their popularity
    private boolean loadTokens(LinkedList<String> tokens) {
        for (String token : tokens) {
            PostingsList ps = index.get(token);

            if (ps == null) {
                return false;
            }

            if (ps.postingsEntries.isEmpty()) {
                try {
                    ObjectInputStream input = new ObjectInputStream(
                            new FileInputStream(new File(CACHE_PATH + ps.token)));
                    ps.postingsEntries = (LinkedList<PostingsEntry>) input.readObject();
                    input.close();
                } catch (Exception e) {
                    //The file does not exist
                    return false;
                }
                System.out.println("Entries of token '" + token + "' imported");
            }

            popularitySet.remove(ps);
            ps.increasePopularity();
            popularitySet.add(ps);
        }
        return true;
    }

    private void cleanCache() {
        File dir = new File(CACHE_PATH);
        File[] files = dir.listFiles();
        if (files != null) {
            for (File file : files) {
                file.delete();
            }
        }
        System.out.println("Cache cleaned");
    }

    public boolean importIndex() {

        if (!CACHE) {
            return false;
        }

        if (CLEAN_CACHE) {
            cleanCache();
        }
        if (GLOBAL_CACHE) {
            return importGlobalIndex() && importDocumentIDs() && importDocumentsLength();
        }
        if (CACHE && !existCache()) {
            cleanCache();
            return false;
        }

        importDocumentIDs();
        importDocumentsLength();
        importPopularitySet();

        Iterator<PostingsList> iter;
        int i = 0;

        if (popularitySet.descendingIterator().next().getPopularity() == 0) {
            iter = popularitySet.iterator();
        } else {
            iter = popularitySet.descendingIterator();
        }

        // Import the postings list of the most popular words
        while (i < word_threshold && iter.hasNext()) {
            PostingsList ps = iter.next();
            try {
                ObjectInputStream input = new ObjectInputStream(
                        new FileInputStream(new File(CACHE_PATH + ps.token)));
                ps.postingsEntries = (LinkedList<PostingsEntry>) input.readObject();
                input.close();
            } catch (Exception e) {
                cleanCache();
                return false;
            }
            index.put(ps.token, ps);
            ++i;
        }

        // Add the other words in the map with empty postings lists
        while (iter.hasNext()) {
            PostingsList ps = iter.next();
            ps.postingsEntries = new LinkedList<PostingsEntry>();
            index.put(ps.token, ps);
        }

        popularitySet.clear();
        popularitySet.addAll(index.values());

        System.out.println("Index imported");

        return true;
    }

    private void importPopularitySet() {
        try {
            ObjectInputStream input = new ObjectInputStream(
                    new FileInputStream(new File(CACHE_PATH + POPULARITY_FILE_NAME)));
            popularitySet = (TreeSet<PostingsList>) input.readObject();
            input.close();
            updateWordThreshold();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void updateWordThreshold() {
        word_threshold = Math.max((int) (popularitySet.size() * WORD_MEMORY_THRESHOLD / 100.0), MIN_WORD_MEMORY);
    }

    private boolean importGlobalIndex() {
        try {
            ObjectInputStream input = new ObjectInputStream(
                    new FileInputStream(new File(CACHE_PATH + INDEX_FILE_NAME)));
            index = (HashMap<String, PostingsList>) input.readObject();
            input.close();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    private boolean importDocumentsLength() {
        try {
            ObjectInputStream input = new ObjectInputStream(
                    new FileInputStream(new File(CACHE_PATH + DOCUMENT_LENGTH_FILE_NAME)));
            super.docLengths = (HashMap<String, Integer>) input.readObject();
            input.close();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    private boolean importDocumentIDs() {
        try {
            ObjectInputStream input = new ObjectInputStream(
                    new FileInputStream(new File(CACHE_PATH + DOCUMENT_ID_FILE_NAME)));
            super.docIDs = (HashMap<String, String>) input.readObject();
            input.close();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    private void updateEntryScores() {
        for (PostingsList ps : index.values()) {
            for (PostingsEntry pe : ps.postingsEntries) {
                pe.score /= super.docLengths.get("" + pe.docID);
            }
        }
    }

    public void indexingOver() {
        updateEntryScores();
        computeDocumentNorms();

        if (!CACHE) {
            return;
        }
        System.out.println(String.format("%d documents indexed\nIndexing over. Saving entries...", doc_counter * DOC_ELAPSED_THRESHOLD + docElapsed));

        if (GLOBAL_CACHE) {
            exportDocumentIDs();
            exportDocumentsLength();
            exportGlobalIndex();
            return;
        }

        Iterator<PostingsList> iter = popularitySet.descendingIterator();
        int i = 1;
        updateWordThreshold();

        PostingsList ps = iter.next();
        ps.setPopularity(0);
        if (!ps.postingsEntries.isEmpty()) {
            updatePostingsFile(ps);
        }

        // Setting the popularity of every word to 0 and updating the most popular entries
        while (iter.hasNext()) {
            ps = iter.next();
            ps.setPopularity(0);
            if (!ps.postingsEntries.isEmpty()) {
                updatePostingsFile(ps);

                if (i > word_threshold) {
                    ps.clear();
                }
            }
            ++i;
        }

        exportPopularitySet();
        exportDocumentIDs();
        exportDocumentsLength();

        popularitySet.clear();
        popularitySet.addAll(index.values());

        System.out.println("Done");
    }

    /**
     * Remove from the popularity tree the word having the least popularity
     */
    private PostingsList getNextUnpopularPostingsList() {
        if (popularityIteratorIdx == -1) {
            popularityIterator = popularitySet.iterator();
            popularityIteratorIdx = 0;
        }

        if (popularitySet.size() <= word_threshold) {
            return null;
        }

        if (popularityIteratorIdx >= word_threshold) {
            popularityIteratorIdx = -1;
            return null;
        }

        PostingsList pl = popularityIterator.next();
        while (pl.postingsEntries.isEmpty()) {
            ++popularityIteratorIdx;
            pl = popularityIterator.next();
        }

        ++popularityIteratorIdx;
        return pl;
    }

    public boolean existCache() {
        return new File(CACHE_PATH + POPULARITY_FILE_NAME).exists();
    }
}
