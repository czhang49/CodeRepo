import numpy as np

class SVDEmbeddings:
    def __init__(self, filename):
        self.emb = np.load(filename)

    def top_k(self, query, k=10):
        sims = self.emb.dot(query.T).flatten()

        # quick select for top k
        best = np.argpartition(-sims, k)[:k]
        best = best[np.argsort(-sims[best])]

        return [(int(result), np.asscalar(sims[result])) for result in best]

    def at(self, word_id):
        return self.emb[[word_id],:]
