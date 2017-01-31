import numpy as np
import scipy as sp

def uniform(n=5):
    x, y = np.meshgrid(np.linspace(0,1,n), np.linspace(0,1,n))
    V = np.vstack((x.ravel(),y.ravel())).T

    SW = np.repeat(np.arange(0,n*n - n,n, dtype=int), n-1) +\
         np.kron(np.ones((n-1,)), np.arange(0,n-1, dtype=int))
    SE = SW + 1
    NW = SW + n
    NE = NW + 1

    E = np.zeros((2*(n-1)*(n-1),3), dtype=int)
    E[0::2] = np.vstack((SW, NE, NW)).T
    E[1::2] = np.vstack((SW, SE, NE)).T

    return V, E

def xml(fname):
    from xml.dom import minidom
    d = minidom.parse('simple.xml')
    nv = int(d.getElementsByTagName('vertices')[0].getAttribute('size'))
    ne = int(d.getElementsByTagName('cells')[0].getAttribute('size'))

    V = np.zeros((nv,2)) # xy-coordinates
    E = np.zeros((ne,3), dtype=int) # 3-node triangles

    for v in d.getElementsByTagName('vertex'):
        V[v.getAttribute('index'),:] = [v.getAttribute('x'), v.getAttribute('y')]

    for v in d.getElementsByTagName('triangle'):
        E[v.getAttribute('index'),:] = [v.getAttribute('v0'), v.getAttribute('v1'), v.getAttribute('v2')]

    return V, E

if __name__=='__main__':
    V, E = generate(10)

    import matplotlib.pyplot as plt
    plt.triplot(V[:,0], V[:,1], E)
    plt.show()
