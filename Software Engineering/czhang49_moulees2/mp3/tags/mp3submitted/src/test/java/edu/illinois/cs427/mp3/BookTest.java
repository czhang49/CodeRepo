package edu.illinois.cs427.mp3;

import static org.junit.Assert.assertTrue;
import org.junit.Test;
import java.util.*;
import net.sf.json.*;

public class BookTest {
    
    @Test
    public void testBookConstructor1() {
    	Book mybook = new Book("CS427mp3","czhang49");
	assertTrue(mybook.getTitle()=="CS427mp3");
	assertTrue(mybook.getAuthor()=="czhang49");	
    }
    @Test
    public void testBookConstrctor2(){
	
 	JSONObject mybookjson = new JSONObject();
	mybookjson.put("title","CS427mp3");
	mybookjson.put("author","moulees2");
	String mybookstring= mybookjson.toString();
	System.out.println(mybookstring);


	Book mybook = new Book(mybookstring);
 	
	assertTrue(mybook.getTitle().equals("CS427mp3"));
	assertTrue(mybook.getAuthor().equals("moulees2"));	

    }
    @Test
    public void testGetStringRepresentation1() {
        //TODO imple ment this
    	Book mybook = new Book("CS427mp3","czhang49");
    	String mybookstring = mybook.getStringRepresentation();
        JSONObject mybookobj = (JSONObject)JSONSerializer.toJSON(mybookstring); 

	assertTrue(mybookobj.getString("title").equals("CS427mp3"));
	assertTrue(mybookobj.getString("author").equals("czhang49"));

   }
    @Test
    public void testGetContainingCollections1() {
        //TODO implement this
    
	Collection mycollection = new Collection("CS427");
    	Book mybook = new Book("mp3main","moulees2");
	mybook.setParentCollection(mycollection);
	List<Collection> mybookcollections = mybook.getContainingCollections();
	assertTrue(mybookcollections.get(0).getName().equals("CS427"));	
    }
}
