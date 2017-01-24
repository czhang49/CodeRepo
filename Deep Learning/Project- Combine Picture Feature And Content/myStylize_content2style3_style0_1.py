import tensorflow as tf
import numpy as np
import scipy.misc
import vgg
initializer = tf.random_normal_initializer(mean=0.0, stddev=0.1, dtype=tf.float32)


def content(layer):
	'''
	function to construct content tensors
	'''
	return layer


def styles(layer, type = ""):
	'''
	function to construct style tensors
	'''
	_, height, width, number = map(lambda i: i.value, layer.get_shape())
	size = height * width * number
	feats = tf.reshape(layer, (-1, number))
	gram = tf.matmul(tf.transpose(feats), feats)/size  # gram is a matrix
	return gram



def evalFeatureLayers(graph, tensor, myImage):
	# myImage is already preprocessed
	with tf.Session() as sess:
		res = sess.run(tensor,feed_dict={"inputImage:0": myImage})
		return res

def getFeatures(graph, layerNames = ["conv1_1"], featureType = "content", returnTensor = True, inputImage = None):
	# contentImage has been normalized
	features = {}

	for layerName in layerNames:
		print "2",layerName
		layer = tf.get_default_graph().get_tensor_by_name(layerName+":0")
		if featureType == "content":
			tensor = content(layer)
		elif featureType == "style":
			tensor = styles(layer)
		print tensor
		if returnTensor:
			features[layerName] = tensor
		else:
			layerValues = evalFeatureLayers(graph, tensor, inputImage)
			features[layerName] = layerValues

	return features


# get the content and styple representation

def stylize(contentImage, styleImage,k,j,i, contentLayerNames = ['conv4_2'], styleLayerNames = ['conv1_1', 'conv2_1', 'conv3_1', 'conv4_1', 'conv5_1']):

	imageShape = contentImage.shape
	styleImage = scipy.misc.imresize(styleImage, imageShape)

	contentImage = np.expand_dims(contentImage, axis = 0)
	styleImage = np.expand_dims(styleImage, axis = 0)

	# get the graph
	g = tf.Graph()
	with g.as_default():
		#with tf.Session() as sess:
			# writer = tf.train.SummaryWriter("log_tb",sess.graph)
		image = tf.placeholder('float', shape=(None,imageShape[0],imageShape[1],imageShape[2]),name = "inputImage")
		net, mean_pixel = vgg.net("./models/imagenet-vgg-verydeep-19.mat", image) # input as placeholder

		contentImage = contentImage- mean_pixel
		styleImage = styleImage - mean_pixel

		contentFeatures = getFeatures(g, layerNames = contentLayerNames, featureType = "content", returnTensor=False, inputImage=contentImage)
		styleFeatures = getFeatures(g, layerNames = styleLayerNames, featureType = "style", returnTensor=False, inputImage=styleImage)


	tf.reset_default_graph()

	# get a new graph
	g = tf.Graph()
	with g.as_default():
		image = tf.get_variable("initialImage", shape = (1,)+imageShape,initializer = initializer)

		# reconstruct the tensorflow graph with input as variable
		net, _ = vgg.net("./models/imagenet-vgg-verydeep-19.mat", image)

		contentLoss = 0.0
		styleLoss = 0.0

		for layerName in contentLayerNames:
			contentTensor = getFeatures(g, layerNames = [layerName], featureType = "content", returnTensor=True)
			contentLoss = contentLoss + tf.nn.l2_loss(contentFeatures[layerName] - contentTensor[layerName])

		styleLayerWeights = 1.0/len(styleLayerNames)
		for layerName in styleLayerNames:
			styleTensor = getFeatures(g, layerNames = [layerName], featureType = "style", returnTensor=True)
			styleLoss = styleLoss + styleLayerWeights*tf.nn.l2_loss(styleFeatures[layerName] - styleTensor[layerName])


		loss = contentLoss

		train = tf.train.AdamOptimizer(1e1).minimize(loss)

		with tf.Session() as sess:
			sess.run(tf.initialize_all_variables())
			for m in range(1000):
				print m
				sess.run(train)

			resultImage = sess.run("initialImage:0")
			resultImage[0,:,:,:] += mean_pixel
			return resultImage

if __name__ == '__main__':
	import scipy.misc
	import matplotlib.pyplot as plt

	for k in range (2,3):
		for j in range (3,4):
			content_path ='./examples_chen/content_' + str (k) + '.jpg'
			style_path = './examples_chen/style_' + str (j) + '.jpg'
			contentImage = scipy.misc.imread(content_path).astype(np.float)
			styleImage = scipy.misc.imread(style_path).astype(np.float)
		#contentImage = scipy.misc.imread("./examples/content_1.jpg").astype(np.float)
		#styleImage = scipy.misc.imread("./examples/style_1.jpg").astype(np.float)

		#contentLayerNames = ['relu4_2']
		#styleLayerNames = ['relu1_1', 'relu2_1', 'relu3_1', 'relu4_1', 'relu5_1']
		#######################################################
			for i in range (1,5):
				contentLayerNames = ['conv' + str(i) + '_1']
			#contentLayerNames = ['conv1_1']
				styleLayerNames = ['conv1_1', 'conv2_1', 'conv3_1', 'conv4_1', 'conv5_1']

				resultImage = stylize(contentImage, styleImage,k,j,i, contentLayerNames = contentLayerNames, styleLayerNames = styleLayerNames)
				resultImage = resultImage[0,:,:,:]
				img = np.clip(resultImage, 0, 255).astype(np.uint8)
				output_path = './outputs_chen/content' + str(k) + '_style' + str(j) + '_CLconv' + str(i) + '1_SLconv11conv21conv31conv41conv51_style0.jpg'
		#scipy.misc.imsave("./outputs/content1_style1_CLconv11_SLconv11conv21conv31conv41conv51.jpg", img)
				scipy.misc.imsave(output_path, img)
