package cs446.homework2;

import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

import weka.core.Attribute;
import weka.core.FastVector;
import weka.core.Instance;
import weka.core.Instances;
import weka.core.converters.ArffSaver;

public class FeatureGenerator {

    static String[] one_hot_features;
    static String[] numeric_features = {"first_len", "last_len"};//Unfortunately, the ID3 implementation we have won't handle this.
    private static java.util.Map<String,Attribute> attribute_dict = new java.util.HashMap<String,Attribute>();
    private static FastVector attributes;
    private static Attribute classLabel;	
    private static FastVector zeroOne;
    private static FastVector labels;

    public static final int NUM_CHARS_PER_NAME = 5;

    static {

	zeroOne = new FastVector(2);
	zeroOne.addElement("1");
	zeroOne.addElement("0");

	labels = new FastVector(2);
	labels.addElement("-1");
	labels.addElement("1");

	//Create one-hot features for the first five characters in both first and last name.
	String[] base = new String[] { "firstName", "lastName" };
	
	List<String> ff = new ArrayList<String>();

	for (String f : base) {
	    for (int i = 0 ; i< NUM_CHARS_PER_NAME ; i++){
		for (char letter = 'a'; letter <= 'z'; letter++) {
			ff.add(f + i + "=" + letter);
	    	}
	    }
	}

	attributes = new FastVector();	
	for(String featureName : ff){
		Attribute one_attr = new Attribute(featureName, zeroOne); // Creates a _textual_ attribute that only allows values "0" and "1".
		attribute_dict.put(featureName,one_attr);
		attributes.addElement(one_attr);
	}


	//creates _numeric_ attributes for the length of the strings.
	for(String numeric_name : numeric_features){
		for(int i = 1; i <= NUM_CHARS_PER_NAME; i++){
			String att_name = numeric_name + "=" + i;
			Attribute a_len_attribute = new Attribute(att_name, zeroOne);
			attribute_dict.put(att_name, a_len_attribute);
			attributes.addElement(a_len_attribute);

			ff.add(att_name);
		}
	}

	one_hot_features = ff.toArray(new String[ff.size()]);

	/**
	 * THis is what we wanted to do, oh well.
	 */
	/*
	Attribute first_len_attr = new Attribute("first_len");
	attribute_dict.put("first_len", first_len_attr);
	attributes.addElement(first_len_attr);

	Attribute last_len_attr = new Attribute("last_len");
	attribute_dict.put("last_len", last_len_attr);
	attributes.addElement(last_len_attr);
	*/

	/**
	 * STUDENTS : If you are going to create your own features, then you need to create an "Attribute" object here.
	 *
	 * You MUST add it to the fastvector "attributes", you MAY want to add it to the "attribute_dict" or create your own parallel dictionary so that you can use them by name later. (See how this code uses the "attribute_dict" later on.)
	 *
	 */

	//Please leave the class as the last attribute, though not strictly neccessary.
	classLabel = new Attribute("Class", labels);
	attribute_dict.put("Class",classLabel);
	attributes.addElement(classLabel);

    }

    public static Instances readData(String fileName) throws Exception {

	Instances instances = initializeAttributes();
	Scanner scanner = new Scanner(new File(fileName));

	while (scanner.hasNextLine()) {
	    String line = scanner.nextLine();

	    Instance instance = makeInstance(instances, line);

	    instances.add(instance);
	}

	scanner.close();

	return instances;
    }

    private static Instances initializeAttributes() {

	String nameOfDataset = "Badges";

	Instances instances = new Instances(nameOfDataset, attributes, 0);

	instances.setClass(classLabel);

	return instances;

    }

    private static Instance create_empty_instance(Instances instances){

	//Magic to create a new instance that will fit with and existing dataset.
	Instance instance = new Instance(instances.numAttributes());
	instance.setDataset(instances);
	//In Weka, each attribute has to be set explicitly, or it gets "unknown". We want to set some defaults because in our one-hot encoding, we will encode unknowns as several zeros.
	for(String att_name : one_hot_features){
		instance.setValue(attribute_dict.get(att_name), "0");
	}

	/*
	 * wanted to do
	 */
	/*
	//Likewise for the numeric features, just for style/consistency. We will actually always set these.
	for(String att_name : numeric_features){
		instance.setValue(attribute_dict.get(att_name), 0);
	}
	*/

	return instance;
    }

    private static Instance makeInstance(Instances instances, String inputLine) {
	inputLine = inputLine.trim();

	String[] parts = inputLine.split("\\s+");
	String label = parts[0];
	String firstName = parts[1].toLowerCase();
	String lastName = parts[2].toLowerCase();

	Instance instance = create_empty_instance(instances);

	//We have the label for that instance.
	if(!"?".equals(label)){
		instance.setClassValue(label);
	}

	/*
	 * This is what we wanted to do
	 */
	/*
	//set the length of the strings
	instance.setValue(attribute_dict.get("first_len"), firstName.length());
	instance.setValue(attribute_dict.get("last_len"), lastName.length());
	*/
	/*
	 * Instead
	 */

	instance.setValue(attribute_dict.get("first_len=" + Math.min(firstName.length(),NUM_CHARS_PER_NAME)), "1");
	instance.setValue(attribute_dict.get("last_len=" + Math.min(lastName.length(), NUM_CHARS_PER_NAME)), "1");





	/**
	 *This code handles setting up the appropriate one-hot features for the first NUM_CHARS_PER_NAME letters in each string.
	 *
	 *
	 */
	String[][] first_last =  {{"firstName",firstName},{"lastName",lastName}};

	for( String[] which : first_last){
		String attribute_name_base = which[0];
		String the_name = which[1];

		for(int i = 0; i < Math.min(NUM_CHARS_PER_NAME,the_name.length()); i++){
			String name_of_attribute_to_set = attribute_name_base+i + "=" + the_name.charAt(i);

			Attribute the_attribute_to_set = attribute_dict.get(name_of_attribute_to_set);

			instance.setValue(the_attribute_to_set, "1");//We should just be able to use the string names!
		}
	}

	/**
	 * STUDENTS : If you choose to implement your own features, here is where you should populate them.
	 *
	 * This could include derived features, for example, you could look at the features that we've already prepared for you.
	 * If you are using "one-hot" type features, consider looking in the function "create_empty_instance" (and the above in this function) for one example on how to do this.
	 * Do not edit "create_empty_instance", do your initialization here.
	 */


	return instance;
    }

    public static void main(String[] args) throws Exception {

	if (args.length != 2) {
	    System.err
		    .println("Usage: FeatureGenerator input-badges-file features-file");
	    System.exit(-1);
	}
	Instances data = readData(args[0]);

	ArffSaver saver = new ArffSaver();
	saver.setInstances(data);
	saver.setFile(new File(args[1]));
	saver.writeBatch();
    }
}
