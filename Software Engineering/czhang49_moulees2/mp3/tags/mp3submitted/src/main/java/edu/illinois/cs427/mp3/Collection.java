package edu.illinois.cs427.mp3;

import java.util.List;
import java.util.ArrayList;
import net.sf.json.*;

/**
 * Represents a collection of books or (sub)collections.
 */
public final class Collection extends Element {
    List<Element> elements;
    private String name;
    
    /**
     * Creates a new collection with the given name.
     *
     * @param name the name of the collection
     */
    public Collection(String name) {
        elements = new ArrayList<Element>();
        this.name = name;
    }

    /**
     * Restores a collection from its given string representation.
     *
     * @param stringRepresentation the string representation
     */
    public static Collection restoreCollection(String stringRepresentation) {

        // read JSON from string (represented like Map)
        JSONObject collectionObj = (JSONObject)JSONSerializer.toJSON(stringRepresentation);

        // collectionObj['name']
        String name = collectionObj.getString("name");

        // create the collection
        Collection c = new Collection(name);

        // create list to restore collection elements
        List<Element> elements = new ArrayList<Element>();

        // collectionObj['elements']
        JSONArray restoreElements = (JSONArray)collectionObj.getJSONArray("elements");

        // restore elements from JSONObject
        for(Object e: restoreElements) {
		elements.add(new Book(e.toString()));
	}
        // set collection elements to just-restored list
        c.elements = elements;

        return c;

    }

    /**
     * Returns the string representation of a collection. 
     * The string representation should have the name of this collection, 
     * and all elements (books/subcollections) contained in this collection.
     *
     * @return string representation of this collection
     */
    public String getStringRepresentation() {

        // create JSON to hold this collection
        JSONObject collectionObj = new JSONObject();

        // set name property in JSON
        collectionObj.element("name", getName());

        // accumulate elements in arr under "elements"
        // ie: collectionObj['elements'] = [elem0, elem1...]
        for(Element e: getElements())
            collectionObj.accumulate("elements", e);

        // return serialized collectionObj
        return collectionObj.toString();

    }

    /**
     * Returns the name of the collection.
     *
     * @return the name
     */
    public String getName() {
        return this.name;
    }
    
    /**
     * Adds an element to the collection.
     * If parentCollection of given element is not null,
     * do not actually add, but just return false.
     * (explanation: if given element is already a part of  
     * another collection, you should have deleted the element 
     * from that collection before adding to another collection)
     *
     * @param element the element to add
     * @return true on success, false on fail
     */
    public boolean addElement(Element element) {

        // check if element has any parents
        if(element.getParentCollection() != null)
            return false;

        elements.add(element);

        return true;
    }
    
    /**
     * Deletes an element from the collection.
     * Returns false if the collection does not have 
     * this element.
     * Hint: Do not forget to clear parentCollection
     * of given element 
     *
     * @param element the element to remove
     * @return true on success, false on fail
     */
    public boolean deleteElement(Element element) {
        List<Element> elements = getElements();

        if(!elements.contains(element))
            return false;

        elements.remove(element);
        return true;
    }
    
    /**
     * Returns the list of elements.
     * 
     * @return the list of elements
     */
    public List<Element> getElements() {
        return elements;
    }
}
