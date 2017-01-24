package edu.illinois.cs427.mp3;

import static org.junit.Assert.assertTrue;

import org.junit.Test;

import java.util.*;

import net.sf.json.*;

public class CollectionTest {
    @Test
    public void testRestoreCollection1() {
        //TODO implement this
        Collection mycollection = new Collection("TestRestoreCollection");
	String mycollectionstring="{\"name\":\"CS427\",\"elements\":[{\"title\":\"mp3main\",\"author\":\"moulees2\"},{\"title\":\"mp3test\",\"author\":\"czhang49\"}]}"; 
	Collection newcollection =mycollection.restoreCollection(mycollectionstring);
    
	assertTrue(newcollection.getName().equals("CS427"));
	
    }

    @Test
    public void testgetName() {

        Collection mycollection = new Collection("CS427");
        assertTrue(mycollection.getName().equals("CS427"));
    }

    @Test
    public void testGetStringRepresentation1() {
        //TODO implement this
        Collection mycollection = new Collection("CS427");
        Book mybook = new Book("mp3test", "czhang49");
	mycollection.addElement(mybook);
        String mystring = mycollection.getStringRepresentation();

        JSONObject myjsonLargeobj = (JSONObject) JSONSerializer.toJSON(mystring);
        assertTrue(myjsonLargeobj.getString("name").equals("CS427"));
    
 	JSONObject myjsonobj = myjsonLargeobj.getJSONObject("elements");
    	assertTrue(myjsonobj.getString("title").equals("mp3test"));
    	assertTrue(myjsonobj.getString("author").equals("czhang49"));
    }

    @Test
    public void testAddElement1() {
        //TODO implement this
        Collection mycollection = new Collection("CS427");
        Book mybook = new Book("mp3main", "moulees2");
        assertTrue(mycollection.addElement(mybook));
    }

    @Test
    public void testAddElement2() {
	// This is added test
	Collection mycollection = new Collection ("CS427");

	Book mybook = new Book("mp3main","moulees2");
	mybook.setParentCollection(mycollection);
    	assertTrue(!mycollection.addElement(mybook));
    }
   
    @Test
    public void testDeleteElement1() {
        //TODO implement this 
        Collection mycollection = new Collection("CS427");
        String bookstring = "{\"title\":\"mp3test\",\"author\":\"czhang49\"}";
        Book mybook = new Book(bookstring);
        mycollection.addElement(mybook);
        assertTrue(mycollection.deleteElement(mybook));
        assertTrue(!mycollection.deleteElement(mybook));
    }
}
