import numpy as np
import cv2
import os

import chainer
from chainer import cuda, Function, gradient_check, Variable, optimizers, serializers, utils
from chainer import Link, Chain, ChainList
import chainer.functions as F
import chainer.links as L

from VGGNet import VGGNet
from VGGNet_1024 import VGGNet_1024
from helperFunctions import getUCF101
from helperFunctions import preprocessImage

import time
import math

from multiprocessing import Pool

GPU_on = True

# class_list - numpy array of class action names
# train - train[0] is numpy array of video filenames, train[1] is numpy array of class indices
# test - test[0] is numpy array of video filenames, test[1] is numpy array of class indices
class_list, train, test = getUCF101()


# load pretrained VGG CNN
print "Preload Models..."
vgg = VGGNet()
serializers.load_hdf5('VGG.model',vgg)

# load weights from pretrained model into new model
vgg_1024 = VGGNet_1024()
layer_names = ['conv1_1','conv1_2','conv2_1','conv2_2','conv3_1','conv3_2','conv3_3','conv4_1','conv4_2','conv4_3','conv5_1','conv5_2','conv5_3','fc6']
new_layers = ['fc7','fc8']

for layer_name in layer_names:
	layer = getattr(vgg,layer_name)
	setattr(vgg_1024,layer_name,layer)
del vgg

#serializers.load_hdf5('VGG_1024.model',vgg_1024)

if(GPU_on):
	vgg_1024.to_gpu()
print "Models loaded..."

optimizer = optimizers.MomentumSGD(momentum=0.9)
optimizer.setup(vgg_1024)
optimizer.add_hook(chainer.optimizer.WeightDecay(0.0005))
optimizer.lr = 0.0005

train_length = len(train[0])
batch_size = 36 # nearly the limit for GPU memory with this particular vgg model loaded
num_epochs = 20

pool_threads = Pool(12) # can call a function with a list of arguments to be run on separate cpu cores


print "Begin Training..."
t = time.time()
log_loss = 0.0
for epoch in range(num_epochs):

	random_indices = np.random.permutation(train_length)

	count = 0
	init = 0
	for i in range(0,train_length-batch_size,batch_size):
		next_batch = 0

		video_list = [train[0][k] for k in random_indices[i:(batch_size+i)]]
		img_data = pool_threads.map(preprocessImage,video_list) # load a bunch of random frames from random clips
		for img in img_data:
			if img.size==0: # there was an exception, skip this batch
				next_batch = 1
		if(next_batch==1):
			count += 1
			continue

		img_data = np.asarray(img_data)

		y = train[1][random_indices[i:(batch_size+i)]]

		if(GPU_on):
			x_batch = cuda.to_gpu(img_data)
			y_batch = cuda.to_gpu(y.astype(np.int32))

		vgg_1024.zerograds()

		loss, accuracy = vgg_1024(x_batch,y_batch, is_train=True)

		loss.backward()
		optimizer.update()


		count += 1

		if(init==0):
			init = 1
			train_accuracy = 100.0*np.float(accuracy.data)
			log_loss = loss.data
		else:
			train_accuracy = 0.95*train_accuracy + 0.05*(100.0*np.float(accuracy.data))
			log_loss = 0.95*log_loss + 0.05*loss.data

		print "Time: %.2f" % float(time.time()-t), "Epoch Number: %.2f" % float(epoch + float(count)/float(math.floor(train_length/batch_size)+1)), "Train accuracy: %.3f" % float(train_accuracy), "Train loss: %.3f" % float(log_loss), "Batch accuracy: %.3f" % np.float(accuracy.data)
		t = time.time()

serializers.save_hdf5('VGG_1024.model',vgg_1024)
