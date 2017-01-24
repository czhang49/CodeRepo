package edu.illinois.cs427.mp3;

import java.util.List;
import static org.junit.Assert.assertTrue;
import org.junit.Test;
import java.io.File;
import java.io.FileWriter;
import java.lang.Exception;

public class LibraryTest {

    @Test
    public void testLibraryConstructorFromFile1() {

        String testLibFileName = "file1";

        String testLibSerialized = "{\n" +
                "    \"collections\": {\n" +
                "        \"elements\": [\n" +
                "            {\n" +
                "                \"author\": \"test_author\",\n" +
                "                \"containingCollections\": [],\n" +
                "                \"parentCollection\": null,\n" +
                "                \"stringRepresentation\": \"{\\\"title\\\":\\\"test_book\\\",\\\"author\\\":\\\"test_author\\\"}\",\n" +
                "                \"title\": \"test_book\"\n" +
                "            }\n" +
                "        ],\n" +
                "        \"name\": \"test_collection\",\n" +
                "        \"parentCollection\": null,\n" +
                "        \"stringRepresentation\": \"{\\\"name\\\":\\\"test_collection\\\",\\\"elements\\\":{\\\"author\\\":\\\"test_author\\\",\\\"containingCollections\\\":[],\\\"parentCollection\\\":null,\\\"stringRepresentation\\\":\\\"{\\\\\\\"title\\\\\\\":\\\\\\\"test_book\\\\\\\",\\\\\\\"author\\\\\\\":\\\\\\\"test_author\\\\\\\"}\\\",\\\"title\\\":\\\"test_book\\\"}}\"\n" +
                "    }\n" +
                "}";

        try {
            FileWriter fw = new FileWriter(new File(testLibFileName));
            fw.write(testLibSerialized);
            fw.close();
        } catch(Exception e) {
            // Raise an error in this test as something went wrong
            assertTrue(1 == 0);
        }

        String testBTitle = "test_book";
        String testBAuthor = "test_author";
        String testCName = "test_collection";

        // restore the library from the file
        Library testLibFromFile = new Library(testLibFileName);
        List<Collection> testCFromLib = testLibFromFile.getCollections();

    }
    @Test
    public void testSaveLibraryToFile1() {
        // TODO implement this
        String testLibFileName = "file1";

        String testLibSerialized = "{\n" +
                "    \"collections\": {\n" +
                "        \"elements\": [\n" +
                "            {\n" +
                "                \"author\": \"test_author\",\n" +
                "                \"containingCollections\": [],\n" +
                "                \"parentCollection\": null,\n" +
                "                \"stringRepresentation\": \"{\\\"title\\\":\\\"test_book\\\",\\\"author\\\":\\\"test_author\\\"}\",\n" +
                "                \"title\": \"test_book\"\n" +
                "            }\n" +
                "        ],\n" +
                "        \"name\": \"test_collection\",\n" +
                "        \"parentCollection\": null,\n" +
                "        \"stringRepresentation\": \"{\\\"name\\\":\\\"test_collection\\\",\\\"elements\\\":{\\\"author\\\":\\\"test_author\\\",\\\"containingCollections\\\":[],\\\"parentCollection\\\":null,\\\"stringRepresentation\\\":\\\"{\\\\\\\"title\\\\\\\":\\\\\\\"test_book\\\\\\\",\\\\\\\"author\\\\\\\":\\\\\\\"test_author\\\\\\\"}\\\",\\\"title\\\":\\\"test_book\\\"}}\"\n" +
                "    }\n" +
                "}";

        try {
            FileWriter fw = new FileWriter(new File(testLibFileName));
            fw.write(testLibSerialized);
            fw.close();
        } catch(Exception e) {
            // Raise an error in this test as something went wrong
            assertTrue(1 == 0);
        }

        String testBTitle = "test_book";
        String testBAuthor = "test_author";
        String testCName = "test_collection";

        // restore the library from the file
        Library testLibFromFile = new Library(testLibFileName);
	testLibFromFile.saveLibraryToFile("czhang49_moulees2");
    }
}
