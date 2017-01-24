Chen Zhang  czhang49@illinois.edu
There are five functions :
SGD.java FeatureGenerator.java Id3.java transform.java WekaTester.java


transform.java is to tranform the original feature space to the stump feature
space.


SGD is the Stochastic gradient descent method.


WekaTester.java controls everything. 
In WekaTester, there is a variable method and a variable depth.
method=1 uses SGD
method=2 uses Id3 with different input of depth
method=3 uses SGD with stumps as features, with different input of depth.
