package cs446.homework2;

import java.io.File;
import java.io.FileReader;

import weka.core.Instances;
import weka.core.Instance;
import weka.classifiers.*;
import cs446.weka.classifiers.trees.Id3;
import weka.core.Attribute;
import weka.core.FastVector;


public class transform {


	public static Instances Doit(Id3[] forest, Instances arg0,int numStump) throws Exception{


	int numInst=arg0.numInstances();
	int numAttr=arg0.numAttributes();

	
	FastVector newAttributes = new FastVector(numStump);
	char letter='a';
	for (int j=0;j<numStump+1;j++)
	{
		String S=""+letter;
		Attribute Attribute1= new Attribute(S);
		newAttributes.addElement(Attribute1);

		letter++;
	}


	Instances Newarg0 = new Instances("TransformInstances",newAttributes,numInst);

	for (int i=0; i<numInst;i++)
	{
		Instance instance = new Instance(numStump+1);		
	
		for (int j=0;j<numStump;j++)
		{
			instance.setValue(j,forest[j].classifyInstance(arg0.instance(i)));

		//	System.out.println(arg0.instance(i).hasMissingValue());
		}
		instance.setValue(numStump,arg0.instance(i).value(numAttr-1));
		
		Newarg0.add(instance);
	}


	Newarg0.setClassIndex(numStump);
	
	return Newarg0;

}	


}







