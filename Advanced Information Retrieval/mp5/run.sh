#!/bin/bash

COMPILE="javac"
RUN="java"
OUTDIR="./bin/"
CLASSPATH=".:$OUTDIR"
FILES="./src/CS598/HW5/chen_program.java"
MAINCLASS="CS598/HW5/CS598HW5"


cmd_run= `echo "$RUN" -classpath "$CLASSPATH" "$MAINCLASS"`

$cmd_run

echo "Running command: \"$cmd_run\" ";

echo "------------Finished -------------------"
