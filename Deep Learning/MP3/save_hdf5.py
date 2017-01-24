import numpy as np
import os
import h5py
import time

from helperFunctions import getUCF101

class_list, train, test = getUCF101()

files = train[0]

# SAVE TRAIN FEATURES
train_hdf5 = h5py.File('train1024.hdf5','w')
count = 0
featuresDirectory = 'UCF-101_features'
for filename in files:
	t1 = time.time()

	filename = filename.split('.avi')[0]
	filename_split = filename.split('/')
	filename = featuresDirectory + '/' + filename_split[1] + '/' + filename_split[2] + '.npy'

	data = np.load(filename)
	hdf5_key = filename.split('/')[2].split('.npy')[0]
	train_hdf5.create_dataset(hdf5_key, data=data)
	t2 = time.time()
	count += 1
	print count, "%.2f" % float(t2-t1)
train_hdf5.close()

# SAVE TEST FEATURES
files = test[0]
test_hdf5 = h5py.File('test1024.hdf5','w')
count = 0
for filename in files:
	t1 = time.time()

	filename = filename.split('.avi')[0]
	filename_split = filename.split('/')
	filename = featuresDirectory + '/' + filename_split[1] + '/' + filename_split[2] + '.npy'

	data = np.load(filename)
	hdf5_key = filename.split('/')[2].split('.npy')[0]
	test_hdf5.create_dataset(hdf5_key, data=data)
	t2 = time.time()
	count += 1
	print count, "%.2f" % float(t2-t1)
test_hdf5.close()

#SAVE TEST OUTPUT
files = test[0]
framePredictionDirectory = 'UCF-101_framePrediction'
test_hdf5 = h5py.File('testPredictions1024.hdf5','w')
count = 0
for filename in files:
	t1 = time.time()

	filename = filename.split('.avi')[0]
	filename_split = filename.split('/')
	filename = framePredictionDirectory + '/' + filename_split[1] + '/' + filename_split[2] + '.npy'

	data = np.load(filename)
	hdf5_key = filename.split('/')[2].split('.npy')[0]
	test_hdf5.create_dataset(hdf5_key, data=data)
	t2 = time.time()
	count += 1
	print count, "%.2f" % float(t2-t1)
test_hdf5.close()