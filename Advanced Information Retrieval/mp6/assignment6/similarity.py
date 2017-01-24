from __future__ import division
import metapy
from svd_embeddings import SVDEmbeddings
import sys
from random import shuffle

if len(sys.argv) != 4:
    print("Usage: {} svd_file_p1 svd_file_p0.5 svd_file_p0".format(sys.argv[0]))
    sys.exit(1)

svd_p10 = SVDEmbeddings(sys.argv[1])
svd_p05 = SVDEmbeddings(sys.argv[2])
svd_p00 = SVDEmbeddings(sys.argv[3])
svds = [svd_p10, svd_p05, svd_p00]

glove = metapy.embeddings.load_embeddings('config.toml')

wins = [0, 0, 0, 0]
total_questions = 0

with open("similarity.txt") as f:
    for line in f:
        word = line.strip()
        print("Query: {}".format(word))

        word_id, glove_q = glove.at(word)
        svd_qs = [svd.at(word_id) for svd in svds]

        glove_c = [c[0] for c in glove.top_k(glove_q, 2) if c[0] != word_id]
        svd_cs = [[x[0] for x in lst if x[0] != word_id][0] for lst in
                 (svd.top_k(query, 2) for svd, query in zip(svds, svd_qs))]

        candidates = svd_cs + glove_c

        # want: map from idx -> methods returning that term
        terms = list(set(glove.term(tid) for tid in candidates))
        shuffle(terms)

        for i, term in enumerate(terms):
            print("{}) {}".format(i + 1, term))

        winner = None
        while winner == None or winner < 0 or winner > len(terms):
            winner = int(input('Winner: ')) - 1

        winning_id = glove.at(terms[winner])[0]
        for i, candidate in enumerate(candidates):
            if candidate == winning_id:
                wins[i] += 1

        total_questions += 1
        print()

print()
print("Total questions: {}".format(total_questions))
print("SVD p=1.0: {}".format(wins[0] / total_questions))
print("SVD p=0.5: {}".format(wins[1] / total_questions))
print("SVD p=0.0: {}".format(wins[2] / total_questions))
print("GloVe:     {}".format(wins[3] / total_questions))
