package pkg;
import java.util.*;

class MySequence implements Sequence {

    /** Returns an empty sequence. */
    public static MySequence create() {
        return new MySequence();
    }

    /** Returns a sequence that consists of the given objects. */
    public static MySequence create(Object... os) {
        MySequence mySeq = MySequence.create();
        for (Object o : os) {
            mySeq.insert(o);
        }
        return mySeq;
    }

    /* [TODO]: You should implement this constructor */
    private LinkedList my_objs;

    private MySequence() {
	my_objs=new LinkedList();
   }
   
    /* Feel free to add private fields/methods here */    

    /* Interface implementations. */
    /* [TODO]: You should implement these methods */

    public void insert(Object o) {
    	my_objs.add(o);
    }

    public void delete(Object o) {
	my_objs.remove(o);
    }

    public boolean has(Object o) {
	if (my_objs.contains(o))
	  return true;

        return false;
    }

    public Object[] getElements() {
 	if (my_objs.size()!=0)
	{
	   Object[] intermediate= my_objs.toArray();
	   return intermediate;
	}
        return null;
    }
}
