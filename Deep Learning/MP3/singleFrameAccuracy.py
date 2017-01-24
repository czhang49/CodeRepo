import numpy as np
import os
import sys

import time
import math

from helperFunctions import getUCF101

import h5py


class_list, train, test = getUCF101()

test_hdf5 = h5py.File('testPredictions1024.hdf5','r')
print "Test..."
keys = test_hdf5.keys()
for key in keys:
	data = test_hdf5[key][:]
print "DONE LOADING..."

for i in xrange(len(test[0])):
	test[0][i] = test[0][i].split('/')[2].split('.avi')[0]

dataset_length = len(test[0])

random_indices = np.random.permutation(dataset_length)

accuracy = 0.0
top10_accuracy = 0.0
top5_accuracy = 0.0
count = 0.0
for j in xrange(dataset_length):
	i = random_indices[j]
	t1 = time.time()

	video_predictions = test_hdf5[test[0][i]][:]

	nFrames = video_predictions.shape[0]

	video_predictions = np.log(video_predictions)
	video_predictions = video_predictions.sum(axis=0)

	top10_predictions = np.argsort(-video_predictions)[0:10]

	predicted_class = video_predictions.argmax()
	action_class = test[1][i]

	if(action_class==predicted_class):
		accuracy += 1.0

	if(np.any(top10_predictions[0:5]==action_class)):
		top5_accuracy += 1.0

	if(np.any(top10_predictions==action_class)):
		top10_accuracy += 1.0

	count += 1.0

	t2 = time.time()

	print count, "Time: %.2f" % float(t2-t1), "Accuracy(1,5,10): (%.3f,%.3f,%.3f)" % (float(accuracy/count), float(top5_accuracy/count), float(top10_accuracy/count)), "Number of Frames " + str(nFrames)
