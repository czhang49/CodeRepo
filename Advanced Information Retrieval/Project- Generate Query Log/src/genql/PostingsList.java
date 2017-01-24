

package genql;

import java.io.*;
import java.util.*;

/**
 *   A postingsEntries of postings for a given word.
 */
public class PostingsList implements Serializable, Comparable {

    /** The postings postingsEntries as a linked postingsEntries sorted by ascending docID */
    public LinkedList<genql.PostingsEntry> postingsEntries = new LinkedList<genql.PostingsEntry>();

    public String token;

    private int popularity = 0;

    public PostingsList() {
        this.token = null;
    }

    public PostingsList(String token) {
        this.token = token;
    }

    /**  Number of postings in this postingsEntries  */
    public int size() {
	   return postingsEntries.size();
    }

    public boolean isEmpty() {
        return postingsEntries.isEmpty();
    }

    public void increasePopularity() {
        ++popularity;
    }

    public void setPopularity(int popularity) {
        this.popularity = popularity;
    }

    public int getPopularity() {
        return popularity;
    }

    public void clear() {
        postingsEntries.clear();
    }

    /**  Returns the ith posting */
    public genql.PostingsEntry get( int i ) {
	   return postingsEntries.get( i );
    }

    public void addToken(int docID, int offset, genql.PostingsEntry fullEntry) {
        genql.PostingsEntry pe = null;

        // If it is a new document (higher ID)
        if(postingsEntries.isEmpty() || postingsEntries.getLast().docID < docID) {
            if(fullEntry == null) {
                pe = new genql.PostingsEntry(docID);
            } else {
                pe = fullEntry;
            }
            postingsEntries.add(pe);

        // If it belongs to the current working document (last one inserted)
        } else if(postingsEntries.getLast().docID == docID) {
            pe = postingsEntries.getLast();

        // Otherwise, we must check if the document exists
        } else {
            genql.PostingsEntry tmp;
            ListIterator<genql.PostingsEntry> iter = postingsEntries.listIterator();
            while(iter.hasPrevious() && pe == null) {
                tmp = iter.previous();
                if(tmp.docID == docID) {
                    // The document exists
                    pe = tmp;
                } else if(tmp.docID > docID) {
                    iter.next();
                    pe = new genql.PostingsEntry(docID);
                    iter.add(pe);
                }
            }
            // The document does not exist
            if(pe == null) {
                pe = new genql.PostingsEntry(docID);
                postingsEntries.add(pe);
            }
        }

        if(fullEntry == null) {
            // Offset insertion
            pe.addOffset(offset);
        }
    }

    public ListIterator<genql.PostingsEntry> postingsEntriesIterator() {
        return postingsEntries.listIterator();
    }

    @Override
    public int compareTo(Object o) {
        if(o instanceof PostingsList) {
            int r = Integer.compare(getPopularity(), ((PostingsList) o).getPopularity());
            if(r == 0) {
                r = Integer.compare(postingsEntries.size(), ((PostingsList) o).postingsEntries.size());
                if(r == 0) {
                    return token.compareTo(((PostingsList) o).token);
                }
            }
            return r;
        }
        return 0;
    }


}



