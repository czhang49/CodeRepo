package cs446.homework2;

import weka.classifiers.*;
import weka.core.Instances;
import weka.core.Instance;

public class SGD extends Classifier{

	private boolean trained = false;
	/*
	 * STUDENTS : What kind of state might you need to store in a classifier?
	 */
	


	@Override
	public void buildClassifier(Instances arg0) throws Exception {
		/*
		 * STUDENTS : Implement your learning algorithm (e.g. SGD) inside this function, at the end of this function, your classifier
		 * should be prepared to classify data.
		 */

		trained = true;//keep this
	}

	@Override
	public double classifyInstance(Instance instance) throws java.lang.Exception {
		if(!trained){
			throw new Exception("The classifier is not trained!");
		}
		/*
		 * STUDENTS : Implement the decision function here.
		 *
		 * BEWARE: From the API, 
		 * 	Returns:
		 * 		index of the predicted class as a double if the class is nominal, otherwise the predicted value
		 *
		 * 		So for + -, if they are in that order in the ARFF file, you might return 0.0 and 1.0, respectively.
		 */




		return 0.0; //Obviously change this!
	}

}
