
package genql;

import java.io.Serializable;
import java.util.*;

public class PostingsEntry implements Comparable<PostingsEntry>, Serializable {
    public int docID;
    public double score = 0; //Term frequency
    public genql.Vector tfIdf;
    /** Tokens positions sorted by ascending order */
    public LinkedList<Integer> offsets = new LinkedList<Integer>();

    public PostingsEntry(int docID) {
        this.docID = docID;
    }

    public PostingsEntry(int docID, LinkedList<Integer> offsets) {
        this.docID = docID;
        this.offsets = offsets;
    }

    public void addOffset(int offset) {
        ++score;

        if(offset == -1) {
            return;
        }

        //If the current offset is higher than the last one inserted
        if(offsets.isEmpty() || offsets.getLast() < offset) {
            offsets.add(offset);

        //Otherwise, we iterate through the list
        } else {
            ListIterator<Integer> iter = offsets.listIterator();
            while(iter.hasNext()) {
                if(iter.next() > offset) {
                    iter.previous();
                    iter.add(offset);
                    return;
                }
            }
        }
    }

    public ListIterator<Integer> listIterator() {
        return offsets.listIterator();
    }

    /**
     *  PostingsEntries are compared by their score (only relevant
     *  in ranked retrieval).
     *
     *  The comparison is defined so that entries will be put in
     *  descending order.
     */
    public int compareTo( PostingsEntry other ) {
	   return Double.compare( other.score, score );
    }
}
