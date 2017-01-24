#!/usr/bin/env bash
allimgs="outHalf.png
outCopy.png
outRotated.png
outPruned.png
outEtc.png"

make -q
if [ $? -ne 0 ]
then
    make all
    if [ $? -ne 0 ]
    then
        exit -1
    fi
fi

./mp_qtree > mp_qtree.out
diff -u mp_qtree.out soln_mp_qtree.out

for image in $allimgs
do
    diff $image soln_$image
done
