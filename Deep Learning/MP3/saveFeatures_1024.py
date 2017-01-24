import numpy as np
import cv2
import os
import sys

import chainer
from chainer import cuda, Function, gradient_check, Variable, optimizers, serializers, utils
from chainer import Link, Chain, ChainList
import chainer.functions as F
import chainer.links as L

from VGGNet import VGGNet
from VGGNet_1024 import VGGNet_1024
from helperFunctions import getUCF101
from helperFunctions import preprocessVideo

import time
import math

GPU_on = True

featuresDirectory = 'UCF-101_features'
framePredictionDirectory = 'UCF-101_framePrediction'

if(not os.path.isdir(featuresDirectory)):
	os.makedirs(featuresDirectory)
	directories = os.listdir('UCF-101')
	for directory in directories:
		os.makedirs(featuresDirectory+'/'+directory)

if(not os.path.isdir(framePredictionDirectory)):
	os.makedirs(framePredictionDirectory)
	directories = os.listdir('UCF-101')
	for directory in directories:
		os.makedirs(framePredictionDirectory+'/'+directory)


# class_list - numpy array of class action names
# train - train[0] is numpy array of video filenames, train[1] is numpy array of class indices
# test - test[0] is nupmy array of video filenames, test[1] is numpy array of class indices
class_list, train, test = getUCF101()

vgg_1024 = VGGNet_1024()
serializers.load_hdf5('VGG_1024.model',vgg_1024)

if(GPU_on):
	vgg_1024.to_gpu()
print "Models loaded..."

filenames = np.concatenate((train[0],test[0]))
class_labels = np.concatenate((train[1],test[1]))
dataset = (filenames,class_labels)

dataset_batch_number = int(sys.argv[1]) # 0 through 11

# length of training set
dataset_batch_length = 1110 # len of dataset divided by 12, 13320/12
no_of_classes = 101
batch_size = 36
count = 0.0
for i in xrange(dataset_batch_number*dataset_batch_length,(dataset_batch_number+1)*dataset_batch_length):

	t1 = time.time()

	action_class = dataset[1][i]
	filename = dataset[0][i]
	filename_split = filename.split('/')

	prediction_save_filename = framePredictionDirectory+'/'+filename_split[1]+'/'+filename_split[2].split('.avi')[0]+'.npy'
	features_save_filename = featuresDirectory+'/'+filename_split[1]+'/'+filename_split[2].split('.avi')[0]+'.npy'

	if(os.path.isfile(prediction_save_filename) or os.path.isfile(features_save_filename)):
		print "Already Saved: " + filename
		continue

	video_data = preprocessVideo(filename)

	nFrames = video_data.shape[0]

	no_of_batches = int(math.ceil(float(nFrames)/batch_size))

	video_predictions = np.zeros((nFrames,no_of_classes),np.float32)
	video_features = np.zeros((nFrames,1024),np.float32)
	for j in range(no_of_batches):
		vgg_1024.zerograds()
		if(j==(no_of_batches-1)): # last batch, might not be full size
			if(GPU_on):
				x_batch = cuda.to_gpu(video_data[(j*batch_size):nFrames])
				y = np.zeros((nFrames-j*batch_size,))
				y_batch = cuda.to_gpu(y.astype(np.int32))
				pred, fc7 = vgg_1024(x_batch,y_batch,is_train=False, extract_features=True)
				pred.to_cpu()
				fc7.to_cpu()
				video_predictions[(j*batch_size):nFrames,:] = pred.data
				video_features[(j*batch_size):nFrames,:] = fc7.data
		else:
			if(GPU_on):
				x_batch = cuda.to_gpu(video_data[(j*batch_size):((j+1)*batch_size)])
				y = np.zeros((batch_size,))
				y_batch = cuda.to_gpu(y.astype(np.int32))
				pred,fc7 = vgg_1024(x_batch,y_batch,is_train=False, extract_features=True)
				pred.to_cpu()
				fc7.to_cpu()
				video_predictions[(j*batch_size):((j+1)*batch_size),:] = pred.data
				video_features[(j*batch_size):((j+1)*batch_size),:] = fc7.data
	
	np.save(prediction_save_filename,video_predictions)
	np.save(features_save_filename,video_features)

	t2 = time.time()

	count += 1.0
	print count, " Elapsed Time: %.2f" % float(t2-t1), "nFrames: " + str(nFrames)







