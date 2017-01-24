import tensorflow as tf
import numpy as np
import scipy.io
import scipy.misc
def create_graph():
	"""Creates a graph from saved GraphDef file and returns a saver."""
	# Creates graph from saved graph_def.pb.
	with tf.gfile.FastGFile('./models/inception_v4.pb', 'rb') as f:
		graph_def = tf.GraphDef()
		graph_def.ParseFromString(f.read())
		_ = tf.import_graph_def(graph_def, name='')

create_graph()

# image_data = tf.gfile.FastGFile("/Users/wenzhaoxu/Desktop/cropped_panda.jpg", 'rb').read()
image_data = scipy.misc.imread("/Users/wenzhaoxu/Desktop/cropped_panda.jpg").astype(np.float)
s = image_data.shape
print s
pre_image = np.zeros((1,s[0],s[1],s[2]))
pre_image[0,:,:,:] = image_data

print image_data.shape
with tf.Session() as sess:
	# writer = tf.train.SummaryWriter("log_tb",sess.graph)
	softmax_tensor = sess.graph.get_tensor_by_name('InceptionV4/Logits/Predictions:0')
	inputImage = sess.graph.get_tensor_by_name("InputImage:0")
	print softmax_tensor, inputImage
	predictions = sess.run(softmax_tensor, {'InputImage:0': pre_image})
	print predictions


