import numpy as np
import os
import sys

import time
import math

import h5py

from helperFunctions import getUCF101

class_list, train, test = getUCF101()

train_hdf5 = h5py.File('train1024.hdf5','r')
print "Train..."
keys = train_hdf5.keys()
for key in keys:
	data = train_hdf5[key][:]
print "DONE LOADING..."

# the keys for accessing data in train_hdf5 are the filenames without the .avi extension
for i in xrange(len(train[0])):
	train[0][i] = train[0][i].split('/')[2].split('.avi')[0]

dataset_length = len(train[0])

# get the mean input for each dimension
mean_input = np.zeros((1024,),np.float32)
for i in xrange(dataset_length):
	t1 = time.time()

	rnn_input = train_hdf5[train[0][i]][:]
	curr_mean = rnn_input.mean(axis=0)
	mean_input += curr_mean/float(dataset_length)

	t2 = time.time()
	print i, "%.2f" % float(t2-t1), "%.2f" % float(mean_input.mean())

# get the standard deviation for each dimension
squared_error = np.zeros((1024,),np.float32)
for i in xrange(dataset_length):
	t1 = time.time()

	rnn_input = train_hdf5[train[0][i]][:]
	squared = np.square(rnn_input-mean_input)
	squared_error += squared.mean(axis=0)/dataset_length	

	t2 = time.time()
	print i, "%.2f" % float(t2-t1), "%.2f" % float(squared_error.mean())
std_dev = np.sqrt(squared_error)
train_hdf5.close()


# normalize train data
train_hdf5 = h5py.File('train512.hdf5','r+')
print "Train..."
keys = train_hdf5.keys()
for key in keys:
	data = train_hdf5[key][:]
print "DONE LOADING..."

for i in xrange(dataset_length):
	t1 = time.time()

	rnn_input = train_hdf5[train[0][i]][:]
	normalized = (rnn_input - mean_input)/std_dev
	train_hdf5[train[0][i]][:] = normalized

	t2 = time.time()
	print i, "%.2f" % float(t2-t1)
train_hdf5.close()

# normalize test data
test_hdf5 = h5py.File('test512.hdf5','r+')#, driver='core')
print "Test..."
keys = test_hdf5.keys()
for key in keys:
	data = test_hdf5[key][:]
print "DONE LOADING..."

for i in xrange(len(test[0])):
	test[0][i] = test[0][i].split('/')[2].split('.avi')[0]

dataset_length = len(test[0])

for i in xrange(dataset_length):
	t1 = time.time()

	rnn_input = test_hdf5[test[0][i]][:]
	normalized = (rnn_input - mean_input)/std_dev
	test_hdf5[test[0][i]][:] = normalized

	t2 = time.time()
	print i, "%.2f" % float(t2-t1)
test_hdf5.close()