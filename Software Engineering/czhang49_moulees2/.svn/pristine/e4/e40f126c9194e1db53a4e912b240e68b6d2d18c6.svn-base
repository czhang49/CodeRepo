package edu.illinois.cs427.mp3;

import java.util.List;
import net.sf.json.*;
import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.lang.Exception;


/**
 * Container class for all the collections (that eventually contain books).
 * Its main responsibility is to save the collections to a file and restore them from a file.
 */
public final class Library {
    private List<Collection> collections;

    /**
     * Builds a new, empty library.
     */
    public Library() {
        collections = new ArrayList<Collection>();
    }

    /**
     * Builds a new library and restores its contents from the given file.
     *
     * @param fileName the file from where to restore the library.
     */
    public Library(String fileName) {

        String buf = "";

        try {
            Scanner s = new Scanner(new File(fileName));

            while(s.hasNextLine())
                buf += s.nextLine();

        } catch(Exception e) {
            ;
        }


        collections = new ArrayList<Collection>();

        if(!buf.isEmpty()) {
            // read JSON from string (represented like Map)
            JSONObject libraryObj = (JSONObject)JSONSerializer.toJSON(buf);

            // collectionObj['elements']
            JSONArray restoreCollections = (JSONArray)(libraryObj.getJSONObject("collections").getJSONArray("elements"));


            // restore collections from JSONObject
            for(Object o: restoreCollections) {
                Collection c = new Collection(o.toString());
                collections.add(c);
            }


        }

    }

    /**
     * Saved the contents of the library to the given file.
         *
     * @param fileName the file where to save the library
     */
   
    public void saveLibraryToFile(String fileName) {

        JSONObject libraryObj = new JSONObject();

        for(Collection c: getCollections())
            libraryObj.accumulate("collections", c);

        String serializedLib = libraryObj.toString();


        try {
            FileWriter fw = new FileWriter(new File(fileName));
            fw.write(serializedLib);
            fw.close();
        } catch(Exception e) {
            ;
        }

    }

    /**
     * Returns the collections contained in the library.
     *
     * @return library contained elements
     */
    public List<Collection> getCollections() {
        return collections;
    }
}
