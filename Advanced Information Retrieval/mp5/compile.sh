#!/bin/bash

COMPILE="javac"
RUN="java"
OUTDIR="./bin/"
CLASSPATH=".:$OUTDIR"
FILES1="./src/CS598/HW5/chen_program.java"
# FILES2="./src/CS598/HW2/chen_pair.java"
MAINCLASS="CS598/HW5/CS598HW5"



# need to echo the things, otherwise return the result of the program (stdout) and assign it to cmd_compile
# the ampersand at the ends make it a string only, without carrying out the command that is echoed
# when compile, need to provide source file, outdirectory if any, and classpath if the classes are used in compiling
# not sure if sourcepaht is necessary or not
# cmd_compile2= `echo "$COMPILE" -d "$OUTDIR" "$FILES2" `
cmd_compile1= `echo "$COMPILE" -classpath "$CLASSPATH" -d "$OUTDIR" "$FILES1" ` 


# if refer to the variable in a string, then it is simply a part of string.
# if refer to a variable independently, then it behaves like a command
#$cmd_compile2
#$cmd_compile1

# echo "Compilation command: \"$cmd_compile2\" ";
echo "Compilation command: \"$cmd_compile1\" ";

echo "------------Finished -------------------"

# when run , need to provide classpath, and main class. or mainclass only.
# whatever go into the mainclass represents a series of packages and classes
