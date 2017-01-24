import numpy as np
from numpy.linalg import norm
import scipy
from scipy.sparse import csr_matrix, diags
from scipy.sparse.linalg import svds
import sys

if len(sys.argv) != 2:
    print("Usage: {} output_filename".format(sys.argv[0]))
    sys.exit(1)

# here are a few helper functions you might find useful...
def multiply_by_rows(matrix, coefficients):
    diag = diags(coefficients, 0)
    return diag * matrix

def multiply_by_columns(matrix, coefficients):
    diag = diags(coefficients, 0)
    return matrix * diag

print("Loading cooccurrence matrix...")
with np.load("cooccur.npz") as loader:
    PPMI = csr_matrix((loader['data'], loader['indices'],
        loader['indptr']), shape=loader['shape'])

print("Computing PPMI...")


##### FILL IN THE CODE HERE #####
# you should compute the PMI matrix and save it into the PPMI variable.
# Hint: the following functions/attributes might be useful:
#
# - csr_matrix.sum()
# - csr_matrix.data
# - array.sum()
# - np.reciprocal()
# - np.log2()
# - multiply_by_rows() (above)
# - multiply_by_columns() (above)
column_sum = np.array(PPMI.sum(axis=0),dtype = 'float')[0,:]
row_sum = np.array(PPMI.sum(axis=1),dtype = 'float')[:,0]
column_recip = np.reciprocal(column_sum)
row_recip = np.reciprocal(row_sum)

PPMI.data = PPMI.data * PPMI.sum()
multiply_by_rows(PPMI,row_recip)
multiply_by_columns(PPMI,column_recip)
PPMI.data = np.log2(PPMI.data)








##### STOP FILLING IN THE CODE HERE

# At this point, PPMI is actually PMI, so let's drop all negative values,
# sparsify, and then compute rank-50 SVD

# PPMI = max(0, PMI)
PPMI.data[PPMI.data < 0] = 0
# sparisfy
PPMI.eliminate_zeros()

print("Computing SVD...")
u, s, vt = svds(PPMI, k = 50)

p = 1
emb = u * (s ** p)

# normalize embeddings to unit length so cos(x, y) == x.T * y
emb = (emb.T / norm(emb, axis=1, ord=2)).T

print("Saving embeddings...")
np.save(sys.argv[1], emb)
print("Done!")
