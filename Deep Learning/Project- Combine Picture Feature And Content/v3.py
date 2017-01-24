import tensorflow as tf
import numpy as np
import scipy.misc
import matplotlib.pyplot as plt

def create_graph():
	"""Creates a graph from saved GraphDef file and returns a saver."""
	# Creates graph from saved graph_def.pb.
	with tf.gfile.FastGFile('/Users/wenzhaoxu/Desktop/classify_image_graph_def.pb', 'rb') as f:
		graph_def = tf.GraphDef()
		graph_def.ParseFromString(f.read())
		_ = tf.import_graph_def(graph_def, name='')

create_graph()

#image_data = tf.gfile.FastGFile("/Users/wenzhaoxu/Desktop/cropped_panda.jpg", 'rb').read()
image_data = scipy.misc.imread("/Users/wenzhaoxu/Desktop/cropped_panda.jpg")
image_data = scipy.misc.imresize(image_data, (299,299,3))

print image_data.shape
mean =  np.mean(image_data,axis = (0,1))

# image_data = image_data - mean

with tf.Session() as sess:
	# print "write"
	content_predictions = sess.run('conv/Conv2D:0', {"DecodeJpeg:0": image_data})

tf.reset_default_graph()



with tf.gfile.FastGFile('/Users/wenzhaoxu/Desktop/classify_image_graph_def.pb', 'rb') as f:
	graph_def = tf.GraphDef()
	graph_def.ParseFromString(f.read())

	# noise = np.random.normal(size=(299,299,3), scale=np.std(image_data) * 0.1)
	inputImage = tf.get_variable("inputImage", shape = [299,299,3], initializer = \
		tf.constant_initializer(value = 104,dtype=tf.float32))
	
	tf_new_image = tf.expand_dims(inputImage,0)
	print tf_new_image
	_ = tf.import_graph_def(graph_def, input_map={"ResizeBilinear:0": tf_new_image})
	# _ = tf.import_graph_def(graph_def,name = "import")
	

target_predictions = tf.get_default_graph().get_tensor_by_name("import/conv/Conv2D:0")
loss = tf.nn.l2_loss(content_predictions - target_predictions)
# image = tf.Variable(initial,name = "targetImage")


with tf.Session() as sess:
	writer = tf.train.SummaryWriter("log_tb",sess.graph)
	sess.run(tf.initialize_variables(var_list = [inputImage]))
	train_step = tf.train.MomentumOptimizer(learning_rate = 0.1, momentum = 0.9).minimize(loss)
	
	for i in range(2000):
		print i
		sess.run(train_step)

	newImage = sess.run(inputImage)
	print newImage
	print newImage.shape
	plt.imshow(newImage)
	plt.show()


