package cs446.homework2;

import weka.classifiers.*;
import weka.core.Instances;
import weka.core.Instance;

public class SGD extends Classifier{

	private boolean trained = false;
	/*
	 * STUDENTS : What kind of state might you need to store in a classifier?
	 */
	private double[] weights;	


	@Override
	public void buildClassifier(Instances arg0) throws Exception {
		/*
		 * STUDENTS : Implement your learning algorithm (e.g. SGD) inside this function, at the end of this function, your classifier
		 * should be prepared to classify data.
		 */
		
		weights=new double[arg0.numAttributes()];// the extra component is the w0
		int numAtt=arg0.numAttributes();		
		int numIns=arg0.numInstances();
		double R=-0.00002;
		double Sum1=0;
		double Sum2=0;		

	//	System.out.println(numAtt);
	//	System.out.println(numIns);
	//	System.out.println(arg0);

		for (int i=0;i<arg0.numAttributes();i++)
		{
			weights[i]=0.1;// the w0 is also initilized as 1
		}	
		

		for (int i=0;i<numIns;i++)
		{
			Sum1=0;
			for (int j=0;j<numAtt-1;j++)
			{
				Sum1=Sum1+weights[j]*arg0.instance(i).value(j);
			}// this part to calculate the w*X
		
			int labelii=1;
			if (arg0.instance(i).value(numAtt-1)==0)
				labelii=-1;
			Sum1=Sum1+weights[numAtt-1]*1-labelii; // This to sum the w0 and y
		
			

			for (int k=0; k<arg0.numAttributes()-1; k++)
			{
				weights[k]=weights[k]+Sum1*R*arg0.instance(i).value(k);
			}
			weights[numAtt-1]=weights[numAtt-1]+Sum1*R*1;
			

		}

		System.out.println(Sum1);
		/*
		for (int m=0;m<numAtt;m++)
		{
			System.out.println(weights[m]);
		}
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

		double decision=0;
		for (int i=0; i<instance.numAttributes()-1;i++)
		{
			decision=decision+weights[i]*instance.value(i);

		}
		decision=decision+weights[instance.numAttributes()-1]*1;
		
		int label;
		if (decision>=0)
			label=1;		
		else 
			label=0;

		
		return label; //Obviously change this!
	}

}
