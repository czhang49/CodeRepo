import os
import numpy as np
import cv2
import time
import imageio
	
def preprocessVideo(filename):
	

	mean = np.array([103.939, 116.779, 123.68])
	i=0
	try:
		vid = imageio.get_reader(filename)
		nFrames = vid.get_length()

		video_data = np.zeros((nFrames-1,3,224,224),dtype=np.float32) # don't save the last frame, it's corrupted on a lot of videos

		for i in range(0,nFrames-1):

			frame = np.asarray(vid.get_data(i))
			frame = frame.astype(np.float32)
			frame -= mean
			frame = cv2.resize(frame, (224,224)).transpose((2,0,1))
			video_data[i,:,:,:] = frame

		vid.close()
	except:
		print "Exception: " + filename
		if(i>0): # got at least one frame though before the exception
			new_video_data = video_data[0:i,:,:,:]
			video_data = new_video_data
		else:
			video_data = np.zeros((224,224,3),np.float32)
			video_data -= mean
			video_data = video_data.transpose((2,0,1))
			video_data = video_data[np.newaxis,:,:,:]
	return video_data

def getUCF101():

	# action class labels
	class_file = open('ucfTrainTestlist/classInd.txt','r')
	lines = class_file.readlines()
	lines = [line.split(' ')[1].strip() for line in lines]
	class_file.close()
	class_list = np.asarray(lines)

	# training data
	train_file = open('ucfTrainTestlist/trainlist01.txt','r')
	lines = train_file.readlines()
	filenames = ['UCF-101/' + line.split(' ')[0] for line in lines]
	y_train = [int(line.split(' ')[1].strip())-1 for line in lines]
	y_train = np.asarray(y_train)
	train_file.close()

	train = (np.asarray(filenames),y_train)

	# testing data
	test_file = open('ucfTrainTestlist/testlist01.txt','r')
	lines = test_file.readlines()
	filenames = ['UCF-101/' + line.split(' ')[0].strip() for line in lines]
	classnames = [filename.split('/')[1] for filename in filenames]
	y_test = [np.where(classname == class_list)[0][0] for classname in classnames]
	y_test = np.asarray(y_test)
	test_file.close()

	test = (np.array(filenames),y_test)

	return class_list, train, test

def preprocessImage(filename):
	
	mean = np.array([103.939, 116.779, 123.68])

	try:
		vid = imageio.get_reader(filename)
		nFrames = vid.get_length()
		frame_no = np.random.randint(nFrames)


		frame = np.asarray(vid.get_data(frame_no))
		frame = frame.astype(np.float32)
		frame = frame[:,:,(2,1,0)]
		frame -= mean

		# ### DATA AUGMENTATION
		## RANDOM CROP
		# if(np.random.randint(2)==0):
		# 	w = np.random.randint(frame.shape[1]-224)
		# 	h = np.random.randint(frame.shape[0]-224)
		# 	frame = frame[h:(h+224),w:(w+224)]

		# ## RESIZE
		# resize_factor = np.random.rand()/2.0+0.75
		# frame = cv2.resize(frame,(int(frame.shape[0]*resize_factor),int(frame.shape[1]*resize_factor)))
		
		## FLIP
		if(np.random.randint(2)==0):
			frame = cv2.flip(frame,1)

		# resize to appropriate dimension
		frame = cv2.resize(frame,(224,224))

		frame = frame.transpose((2,0,1))

	except:
		print "Exception: " + filename

		frame = np.array([])

	return frame


def repeatSequence(rnn_input,length_of_sequence):

	while(rnn_input.shape[0]<length_of_sequence):
		rnn_input_flipped = np.flipud(rnn_input)
		rnn_input=np.vstack((rnn_input,rnn_input_flipped))
	return rnn_input

