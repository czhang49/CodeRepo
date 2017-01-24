package edu.illinois.cs427.mp3;

import java.util.List;
import java.util.ArrayList;
import net.sf.json.*;

/**
 * This class contains the information needed to represent a book.
 *
 *
 */
public final class Book extends Element {
    private String title;
    private String author;

    /**
     * Builds a book with the given title and author.
     *
     * @param title the title of the book
     * @param author the author of the book
     */
    public Book(String title, String author) {
        this.title = title;
        this.author = author;
    }

    /**
     * Builds a book from the string representation, 
     * which contains the title and author of the book. 
     *
     * The string representation should be JSON
     *
     * @param stringRepresentation the string representation
     */
    public Book(String stringRepresentation) {

        JSONObject bookObj = (JSONObject)JSONSerializer.toJSON(stringRepresentation);

        this.title = bookObj.getString("title");
        this.author = bookObj.getString("author");

    }

    /**
     * Returns the string representation of the given book.
     * The representation contains the title and author of the book.
     *
     * @return the string representation
     */
    public String getStringRepresentation() {

        JSONObject bookObj = new JSONObject()
                .element("title", getTitle())
                .element("author", getAuthor());

        return bookObj.toString();
    }

    /**
     * Returns all the collections that this book belongs to directly and indirectly.
     * Consider the following. 
     * (1) Computer Science is a collection. 
     * (2) Operating Systems is a collection under Computer Science. 
     * (3) The Linux Kernel is a book under Operating System collection. 
     * Then, getContainingCollections method for The Linux Kernel should return a list 
     * of these two collections (Operating Systems, Computer Science), starting from 
     * the direct collection to more indirect collections.
     *
     * @return the list of collections
     */
    public List<Collection> getContainingCollections() {

        List<Collection> containingCollections = new ArrayList<Collection>();

        Collection c = this.getParentCollection();

        while(c != null) {
            containingCollections.add(c);
            c = c.getParentCollection();
        }

        return containingCollections;
    }

    /**
     * Returns the title of the book.
     *
     * @return the title
     */
    public String getTitle() {
        return this.title;
    }

    /**
     * Returns the author of the book.
     *
     * @return the author
     */
    public String getAuthor() {
        return this.author;
    }
}
