package pkg;

import static org.junit.Assert.assertTrue;
import org.junit.Test;

public class SequenceUtilTest {
   
    @Test
    public void testConstructor(){
	MySequence sequence0= MySequence.create();
	assertTrue(sequence0.getElements()==null);
    } 
    @Test
    public void testInsert1() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence sequence1 = MySequence.create();
	sequence1.insert("A");
	assertTrue(sequence1.has("A"));
    }
    @Test
    public void testInsert2() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence sequence2 = MySequence.create();
	sequence2.insert("A");
	assertTrue(!sequence2.has("B"));
    }
    /* [TODO]: Add more real tests here */
   @Test 
   public void testDelete1() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence sequence3 = MySequence.create();
	sequence3.insert("A");
	sequence3.delete("A");
	assertTrue(!sequence3.has("A"));
    }
    @Test
    public void testDelete2() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence sequence4 = MySequence.create();
	sequence4.insert("A");
	sequence4.insert("A");
	sequence4.delete("A");
	assertTrue(sequence4.has("A"));
    }
    @Test
    public void testSequenceUtil1() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence a = MySequence.create();
	a.insert("A");
	a.insert("B");
	a.insert("C");
	MySequence b = MySequence.create();
	b.insert("A");
	b.insert("B");
	b.insert("D");
	Sequence c = SequenceUtil.intersect(a,b);

	assertTrue(c.has("D"));
    }
    @Test
    public void testSequenceUtil2() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence a = MySequence.create();
	a.insert("A");
	a.insert("B");
	a.insert("C");
	MySequence b = MySequence.create();
	b.insert("A");
	b.insert("B");
	b.insert("D");
	Sequence c = SequenceUtil.intersect(a,b);
	c.delete("A");
	assertTrue(!c.has("A"));
    }
    @Test
    public void testSequenceUtil3() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence a = MySequence.create();
	a.insert("A");
	a.insert("B");
	a.insert("C");
	MySequence b = MySequence.create();
	b.insert("A");
	b.insert("B");
	b.insert("D");
	Sequence c = SequenceUtil.intersect(a,b);
	c.insert("A");
	c.delete("A");
	assertTrue(c.has("A"));
    }
    @Test
    public void testSequenceUtil4() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence a = MySequence.create();
	a.insert("D");
	a.insert("E");
	a.insert("C");
	MySequence b = MySequence.create();
	b.insert("A");
	b.insert("B");
	b.insert("C");
	Sequence c = SequenceUtil.intersect(a,b);
	Object[] intermediate= c.getElements();
	assertTrue(intermediate[0]=="A");
    }
    @Test
    public void testSequenceUtil5() {
        /* [TODO]: Replace assertTrue with your test */
        MySequence a = MySequence.create();
	a.insert("D");
	a.insert("E");
	a.insert("C");
	MySequence b = MySequence.create();
	b.insert("A");
	b.insert("B");
	b.insert("C");
	Sequence c = SequenceUtil.intersect(a,b);
	Object[] intermediate= c.getElements();
	assertTrue(intermediate[intermediate.length-1]=="E");
    }
}
