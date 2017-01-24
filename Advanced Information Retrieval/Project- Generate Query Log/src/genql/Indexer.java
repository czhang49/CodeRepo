package genql;

import java.io.*;
import java.util.List;

/**
 * Processes a directory structure and indexes all text files.
 */
public class Indexer {

    /**
     * The index to be built up by this indexer.
     */
    public genql.Index index;

    /**
     * The index to be built up by this indexer.
     */
    public genql.Index bigram_index;

    /**
     * The next docID to be generated.
     */
    private int lastDocID = 0;


    /* ----------------------------------------------- */
    /**
     * Generates a new document identifier as an integer.
     */
    private int generateDocID() {
        return lastDocID++;
    }

    /**
     * Generates a new document identifier based on the file name.
     */
    private int generateDocID(String s) {
        return s.hashCode();
    }


    /* ----------------------------------------------- */
    /**
     * Initializes the index as a HashedIndex.
     */
    public Indexer() {
        index = new genql.HashedIndex();
        bigram_index = new genql.BigramIndex();
    }


    /* ----------------------------------------------- */
    /**
     * Tokenizes and indexes the file @code{f}. If @code{f} is a directory, all
     * its files and subdirectories are recursively processed.
     */
    public void processFiles(File f) {
        // do not try to index fs that cannot be read
        if (f.canRead()) {
            if (f.isDirectory()) {
                String[] fs = f.list();
                // an IO error could occur
                if (fs != null) {
                    for (int i = 0; i < fs.length; i++) {
                        processFiles(new File(f, fs[i]));
                    }
                }
            } else {
                //System.err.println( "Indexing " + f.getPath() );
                // First register the document and get a docID
                int docID = generateDocID();
                index.docIDs.put("" + docID, f.getPath());
                try {
                    Reader reader = new FileReader(f);

                    reader = new FileReader(f);

                    genql.SimpleTokenizer tok = new genql.SimpleTokenizer(reader);
                    int offset = 0;
                    while (tok.hasMoreTokens()) {
                        String token = tok.nextToken();
                        insertIntoIndex(docID, token, offset++);
                    }
                    index.docLengths.put("" + docID, offset);
                    index.nextDoc();
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void processTSVFile(File f) {
        // do not try to index fs that cannot be read
        if (f.canRead()) {
            if (f.isDirectory()) {
                String[] fs = f.list();
                // an IO error could occur
                if (fs != null) {
                    for (int i = 0; i < fs.length; i++) {
                        processTSVFile(new File(f, fs[i]));
                    }
                }
            } else {
                final List<String> lines = IOUtils.readFileLineByLine(f.getAbsolutePath(), false);
                for (String line : lines) {
                    //System.err.println( "Indexing " + f.getPath() );
                    // First register the document and get a docID
                    int docID = generateDocID();
                    index.docIDs.put("" + docID, f.getPath() + ":" + docID);
                    try {
                        Reader reader = new StringReader(line);

                        genql.SimpleTokenizer tok = new genql.SimpleTokenizer(reader);
                        int offset = 0;
                        while (tok.hasMoreTokens()) {
                            String token = tok.nextToken();
                            insertIntoIndex(docID, token, offset++);
                        }
                        index.docLengths.put("" + docID, offset);
                        index.nextDoc();
                        reader.close();

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public void sync_indexes() {
        bigram_index.docIDs = index.docIDs;
        bigram_index.docLengths = index.docLengths;
    }

    /**
     * Indexes one token.
     */
    public void insertIntoIndex(int docID, String token, int offset) {
        index.insert(token, docID, offset);
        bigram_index.insert(token, docID, offset);
    }
}
