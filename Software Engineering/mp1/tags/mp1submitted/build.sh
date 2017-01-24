#!./
# Author: Chen Zhang
# Date:   Sep.3
# Purpose:CS427 MP1 Part1

mkdir -p ~/.m2/repository/junit/junit/4.12/
echo "The junit folder has been created!"

dir1=~/.m2/repository/junit/junit/4.12/
wget -P $dir1/ "http://central.maven.org/maven2/junit/junit/4.12/junit-4.12.jar"
echo "Junit has been downloaded!"

###

mkdir -p ~/.m2/repository/org/hamcrest/hamcrest-core/1.3/
echo "The Hamcrest folder has been created!"

dir2=~/.m2/repository/org/hamcrest/hamcrest-core/1.3/
wget -P $dir2/ "http://central.maven.org/maven2/org/hamcrest/hamcrest-core/1.3/hamcrest-core-1.3.jar"
echo "Hamcrest has been downloaded!"

###
mkdir -p ./target/classes/
echo "The target classes folder has been created!"

javac -d ./target/classes/ ./src/main/java/pkg/MySequence.java  ./src/main/java/pkg/Sequence.java ./src/main/java/pkg/SequenceUtil.java 

###
mkdir -p ./target/test-classes/
echo "The target test-classes folder has been created!"

javac -d ./target/test-classes/ -cp ~/.m2/repository/junit/junit/4.12/junit-4.12.jar:./target/classes ./src/test/java/pkg/SequenceUtilTest.java

java -cp  $HOME/.m2/repository/junit/junit/4.12/junit-4.12.jar:./target/classes/:$HOME/.m2/repository/org/hamcrest/hamcrest-core/1.3/hamcrest-core-1.3.jar:./target/test-classes org.junit.runner.JUnitCore pkg.SequenceUtilTest

###
