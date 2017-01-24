package pkg;
import java.util.*;

public class SequenceUtil {
    /** [TODO]: The method should return a Sequence of objects
     *  that are in both of the two argument Sequence objects.
     */
    // In this intersect, the elements of a are placed after b if these elements are not already in b
    public static Sequence intersect(Sequence a, Sequence b) {

	if (a.getElements()==null && b.getElements()==null)
          return null;

	Object[] intermediate=a.getElements();

	for (Object item:intermediate)
	{
	  if (b.has(item))
	    continue;
	  b.insert(item);
	}
	
	return b;
    }
}
