package cs446.homework2;

import java.io.File;
import java.io.FileReader;
import weka.core.converters.ArffSaver;
import java.util.Random;
import weka.filters.supervised.instance.Resample;

import weka.classifiers.Evaluation;
import weka.core.Instances;
import cs446.weka.classifiers.trees.Id3;
import cs446.homework2.SGD;
import cs446.homework2.transform;

public class WekaTester {

    public static void main(String[] args) throws Exception {

	if (args.length != 1) {
	    System.err.println("Usage: WekaTester arff-file");
	    System.exit(-1);
	}

	int method=2; // 1 being use the tree and 2 being use SGD and 3 being use stumps as features
	int depth=8;	
	// Load the data
	String testname="./../badges.test.arff";
	Instances data = new Instances(new FileReader(new File(args[0])));
	Instances testdata= new Instances(new FileReader(new File(testname)));
	//	Instances datablind= new Instances(new FileReader(new File(args[1])));

	// The last attribute is the class label
	data.setClassIndex(data.numAttributes() - 1);
	testdata.setClassIndex(testdata.numAttributes()-1);
	Instances labeled= new Instances(testdata);

	// Train on 80% of the data and test on 20%	
	
	if (method==1)
	{
		for (int i=0;i<5;i++)
		{
			Instances train = data.trainCV(5,i);
			Instances test = data.testCV(5, i);
		
			Id3 classifier = new Id3();
			classifier.setMaxDepth(depth);
				
			classifier.buildClassifier(train);
			Evaluation evaluation =new Evaluation(test);
			evaluation.evaluateModel(classifier,test);
			System.out.println(evaluation.toSummaryString());	
		
			System.out.println(classifier);
			System.out.println();
			
		}

		Id3 classifierfull=new Id3();
		classifierfull.setMaxDepth(depth);
		classifierfull.buildClassifier(data);		

		for (int j=0;j<testdata.numInstances();j++)
		{
			double clsLabel=classifierfull.classifyInstance(testdata.instance(j));			
			labeled.instance(j).setClassValue(clsLabel);
		}


		ArffSaver saver=new ArffSaver();
		saver.setInstances(labeled);
		saver.setFile(new File("./data/2.d.8.pred"));
		saver.writeBatch();

		System.out.println(classifierfull);
		System.out.println();

	}

	if (method==2)
	{
		for (int i=0;i<5;i++)
		{
			Instances train = data.trainCV(5,i);
			Instances test = data.testCV(5,i);

			SGD classifier= new SGD();
			
			classifier.buildClassifier(train);
			Evaluation evaluation = new Evaluation(test);
			evaluation.evaluateModel(classifier,test);
			System.out.println(evaluation.toSummaryString());

		}		

		SGD classifierfull= new SGD();
		classifierfull.buildClassifier(data);

		for (int j=0;j<testdata.numInstances();j++)
		{
			double clsLabel=classifierfull.classifyInstance(testdata.instance(j));			
			labeled.instance(j).setClassValue(clsLabel);
		}


		ArffSaver saver=new ArffSaver();
		saver.setInstances(labeled);
		saver.setFile(new File("./data/2.b.pred"));
		saver.writeBatch();
	}


	if (method==3)
	{
		int numStump=100;
		int trainsize=data.numInstances()/2;
		
		Id3[] forest= new  Id3[numStump];
		
	//	Instances data0=transform.Doit(forest,data,numStump);
	//	Instances testdata0=transform.Doit(forest,data,numStump);		

		Instances data0=new Instances(data);		

		for (int i=0;i<numStump;i++)
		{
			Random generator=new Random(i);	
			data.randomize(generator);

			forest[i]=new Id3();
			forest[i].setMaxDepth(depth);
			
			Instances trainstump= new Instances(data,0,trainsize); ///// Definitely change this part
			forest[i].buildClassifier(trainstump);

		}

		for (int j=0;j<5;j++)
		{
			Instances train=data.trainCV(5,j);
			Instances test=data.testCV(5,j);

	/*
	// Create a new ID3 classifier. This is the modified one where you can
	// set the depth of the tree.
	Id3 classifier = new Id3();

	// An example depth. If this value is -1, then the tree is grown to full
	// depth.
	classifier.setMaxDepth(-1);

	// Train
	classifier.buildClassifier(train);

	// Print the classfier
	System.out.println(classifier);
i	System.out.println();

	// Evaluate on the test set
	Evaluation evaluation = new Evaluation(test);
	evaluation.evaluateModel(classifier, test);
	System.out.println(evaluation.toSummaryString());
	*/
			Instances train0=transform.Doit(forest,data.trainCV(5,j),numStump);
			Instances test0=transform.Doit(forest,data.testCV(5,j),numStump);

	/*
	SGD classifierSGD=new SGD();
	classifierSGD.buildClassifier(train);
	Evaluation evaluation = new Evaluation(test);
	evaluation.evaluateModel(classifierSGD,test);
	System.out.println(evaluation.toSummaryString());

	//SGD TrailSGD=new SGD();
	//TrailSGD.buildClassifier(data);
	//double aaa;
	 //aaa=TrailSGD.classifyInstance(data);
	
	//Instances TrainSGD=data.trainCV(1,0);
	//Instances TestSGD=data.testCV(1,0);
	//SGD TrailSGD=new SGD();
	//TrailSGD.buildClassifier(data);
	  
	*/  
			System.out.println(train0.numAttributes());
			System.out.println(train0.numInstances());

			System.out.println(train.numAttributes());
			System.out.println(train.numInstances());			

			SGD classifier= new SGD();

			classifier.buildClassifier(train);
			Evaluation evaluation = new Evaluation(test);
			evaluation.evaluateModel(classifier,test);
			System.out.println(evaluation.toSummaryString());

		
			//System.out.println(train);
		}

	}


		SGD classifierfull= new SGD();
		classifierfull.buildClassifier(data);



		for (int j=0;j<testdata.numInstances();j++)
		{
			double clsLabel=classifierfull.classifyInstance(testdata.instance(j));			
			labeled.instance(j).setClassValue(clsLabel);
		}


		ArffSaver saver=new ArffSaver();
		saver.setInstances(labeled);
		saver.setFile(new File("./data/2.e.pred"));
		saver.writeBatch();

	}
}
