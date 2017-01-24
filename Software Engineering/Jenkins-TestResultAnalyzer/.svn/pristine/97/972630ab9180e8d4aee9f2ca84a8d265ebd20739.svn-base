describe("testcodes.js:", function() {

    var codeSnippet = '@Test\n\
        public void testBookConstructor1() {\n\
            JSONObject bookObject = new JSONObject();\n\
            bookObject.put("author", "Author1");\n\
            bookObject.put("title", "Title1");\n\
            Book newBook = new Book(bookObject.toString());\n\
            assertEquals("Author1", newBook.getAuthor());\n\
            assertEquals("Title1", newBook.getTitle());\n\
        }\n\
        @\n\
        Test\n\
        public void testGetStringRepresentation1() {\n\
            JSONObject bookObject = new JSONObject();\n\
            bookObject.put("author", "Author1");\n\
            bookObject.put("title", "Title1");\n\
            Book newBook = new Book(bookObject.toString());\n\
            assertEquals(bookObject.toString(), newBook.getStringRepresentation());\n\
        }\n';

    it("extractCode where code is not present in snippet, should return null", function() {
        var expectedExtracted = null; //this should be a failure
        var extracted = extractCode(codeSnippet, "not found");
        expect(extracted).toEqual(expectedExtracted);
    });

    it("extractCode where code is present in snippet, testing size of return value", function() {
        var extracted = extractCode(codeSnippet, "testBookConstructor1");
        expect(extracted.length).toEqual(8); //the returned array is each line in the method, so the length of the array should equal the number of lines
        expect(extracted[3].trim()).toEqual('bookObject.put("title", "Title1");');
    });

    it("extractCode where code is present in snippet, testing content of return value", function() {
        var extracted = extractCode(codeSnippet, "testBookConstructor1");
        expect(extracted[3].trim()).toEqual('bookObject.put("title", "Title1");');
    });
});
