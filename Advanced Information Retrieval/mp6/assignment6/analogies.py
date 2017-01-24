import metapy
from numpy.linalg import norm
from svd_embeddings import SVDEmbeddings
import sys

def compute_reciprocal_rank(word, candidates):
    ##### IMPLEMENT ME! #####
    for i in range (0,len(candidates)):
        if word == candidates[i]:
            return 1/i

    return 0.0

if len(sys.argv) != 2:
    print("Usage: {} [filename | --glove]".format(sys.argv[0]))
    sys.exit(1)

use_glove = len(sys.argv) > 1 and sys.argv[1] == "--glove"
glove = metapy.embeddings.load_embeddings("config.toml")
emb = glove

if not use_glove:
    emb = SVDEmbeddings(sys.argv[1])

def top_k(w_x, w_y, w_z, k=10):
    x = glove.at(w_x)
    y = glove.at(w_y)
    z = glove.at(w_z)

    if not use_glove:
        query = emb.at(y[0]) - emb.at(x[0]) + emb.at(z[0])
    else:
        query = y[1] - x[1] + z[1]

    query /= norm(query, 2)

    # query for k + 3 to accomodate for the query words possibly being in
    # the top k words
    results = emb.top_k(query, k + 3)
    # filter out all query words
    results = [result for result in results if not result[0] in (x[0],
        y[0], z[0])]
    # limit to top 10
    results = results[0:10]

    return [glove.term(result[0]) for result in results]

num_analogies = 0
sum_reciprocal_rank = 0
with open("analogies.txt") as f:
    for line in f:
        line = line.strip()
        words = line.split()

        candidates = top_k(words[0], words[1], words[2])
        num_analogies += 1
        sum_reciprocal_rank += compute_reciprocal_rank(words[3], candidates)

print("MRR: {}".format(sum_reciprocal_rank / num_analogies))
