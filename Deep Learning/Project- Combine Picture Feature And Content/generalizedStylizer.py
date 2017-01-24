import os
os.environ["CUDA_VISIBLE_DEVICES"]=""
import tensorflow as tf
import pickle
import scipy.misc
import numpy as np
# slim = tf.contrib.slim
modelList = ["vgg_19","vgg_16","inception4","resnet_v1_152","inception_resnet_v2"]


def content(layer):
	# layer = tf.get_default_graph().get_tensor_by_name(layerName)
	return layer

def style(layer):
	# layer = tf.get_default_graph().get_tensor_by_name(layerName)

	_, height, width, number = map(lambda i: i.value, layer.get_shape())
	size = height * width * number
	feats = tf.reshape(layer, (-1, number))
	gram = tf.matmul(tf.transpose(feats), feats)/size  # gram is a matrix
	return gram

def getFeatureTensors(layerNames, featureType = "content"):
	# contentImage has been normalized
	features = {}
	for layerName in layerNames:
		# print "2",layerName
		layer = tf.get_default_graph().get_tensor_by_name(layerName)
		if featureType == "content":
			tensor = content(layer)
		elif featureType == "style":
			tensor = style(layer)
		# print tensor
		
		features[layerName] = tensor

	print features
	
	return features



def stylize(model, contentImage, styleImage, contentLayerNames, styleLayerNames):
	tf.reset_default_graph()

	with tf.Session() as sess:
		saver = tf.train.import_meta_graph('./plainModel/%s_resave.meta' %(model,))
	  	endPoints = pickle.load(open("./plainModel/%s_resave_endPoints.p" %(model,)))

		# endPoints = createGraph(model)
		inputImage = tf.get_default_graph().get_tensor_by_name("inputImage:0")
		image_size = inputImage.get_shape()[2]
		# print "available node:",endPoints.keys()
		# print image_size
		# print tf.trainable_variables()
		mean_pix = np.mean(contentImage,axis = (0,1))
		# print mean_pix

		contentImage = contentImage - mean_pix
		styleImage = styleImage - mean_pix
		contentImage = np.expand_dims(scipy.misc.imresize(contentImage, (image_size,image_size,3)),axis = 0).astype(np.float)
		styleImage = np.expand_dims(scipy.misc.imresize(styleImage, (image_size,image_size,3)),axis = 0).astype(np.float)

		# print inputImage
		contentTensor = getFeatureTensors([endPoints[k] for k in endPoints.keys() if k in contentLayerNames], "content")
		styleTensor = getFeatureTensors([endPoints[k] for k in endPoints.keys() if k in styleLayerNames], "style")

		saver.restore(sess, "./plainModel/%s_resave" %(model,))
		contentTarget = sess.run(contentTensor, {inputImage:contentImage})
		styleTarget = sess.run(styleTensor, {inputImage:styleImage})

	# construct loss
	tf.reset_default_graph()


	with tf.Session() as sess:
		saver = tf.train.import_meta_graph('./plainModel/%s_resave.meta' %(model,))
		saver.restore(sess, "./plainModel/%s_resave" %(model,))
		inputImage = [v for v in tf.all_variables() if v.name == "inputImage:0"][0]
			 # = tf.get_default_graph().get_tensor_by_name("inputImage:0")
		# print sess.run(inputImage)
		contentLoss = 0.0
		styleLoss = 0.0	
		contentTensor = getFeatureTensors([endPoints[k] for k in endPoints.keys() if k in contentLayerNames], "content")
		styleTensor = getFeatureTensors([endPoints[k] for k in endPoints.keys() if k in styleLayerNames], "style")
			
		for key in contentTensor.keys():
			contentLoss += tf.nn.l2_loss(contentTensor[key] - contentTarget[key])

		for key in styleTensor.keys():
			styleLoss += tf.nn.l2_loss(styleTensor[key] - styleTarget[key])

		loss = contentLoss+1000.0*styleLoss
		temp = set(tf.global_variables())
		# print type(inputImage)
		# writer = tf.train.SummaryWriter("log_tb",sess.graph)
		train_op = tf.train.AdamOptimizer(learning_rate=1e1).minimize(loss, var_list = [inputImage])
		sess.run(tf.initialize_variables(set(tf.all_variables())-temp))
		sess.run(tf.initialize_variables([inputImage]))
			
		print "created graph"
		for i in range(10):
			print i
			sess.run(train_op)
			
		return sess.run(inputImage)

if __name__ == '__main__':
	contentImage = scipy.misc.imread("./examples/1-content.jpg").astype(np.float)
	styleImage = scipy.misc.imread("./examples/1-style.jpg").astype(np.float)
	
	contentLayerNames = ['vgg_19/conv4/conv4_2']
	styleLayerNames = ['vgg_19/conv4/conv4_1', 'vgg_19/conv5/conv5_1',\
	'vgg_19/conv1/conv1_1', 'vgg_19/conv2/conv2_1', 'vgg_19/conv3/conv3_1']

	print stylize("vgg_19", contentImage, styleImage, contentLayerNames, styleLayerNames)