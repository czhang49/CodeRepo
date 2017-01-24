package genql;

import java.util.HashMap;
import java.util.Iterator;

public abstract class Index {

    /* Query types */
    public static final int INTERSECTION_QUERY = 0;
    public static final int PHRASE_QUERY = 1;
    public static final int RANKED_QUERY = 2;

    /* Ranking types */
    public static final int TF_IDF = 0;

    /* Structure types */
    public static final int UNIGRAM = 0;
    public static final int BIGRAM = 1;
    public static final int SUBPHRASE = 2;

    public HashMap<String, String> docIDs = new HashMap<String, String>();
    public HashMap<String, Integer> docLengths = new HashMap<String, Integer>();

    /**
     * Document norms
     */
    protected HashMap<Integer, Double> docNorm = new HashMap<Integer, Double>();

    abstract public void insert(String token, int docID, int offset);

    abstract public Iterator<String> getDictionary();

    abstract public genql.PostingsList getPostings(String token);

    abstract public genql.PostingsList search(genql.Query query, int queryType, int rankingType, int structureType);

    abstract public void cleanup();

    abstract public void indexingOver();

    abstract public void nextDoc();

    abstract public boolean importIndex();
}
