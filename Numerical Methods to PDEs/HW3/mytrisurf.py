from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import numpy as np
import matplotlib.pyplot as plt

def mytrisurf(x,y,z,E):

    ax = plt.gca(projection='3d')
    verts = ([np.array([[x[t0],y[t0],z[t0]], 
                        [x[t1],y[t1],z[t1]], 
                        [x[t2],y[t2],z[t2]]]) for (t0,t1,t2) in E ])
    c = Poly3DCollection(verts, cmap=plt.cm.get_cmap("jet"))
    c.set_edgecolor('k')
    c.set_array(z[E].mean(axis=1))
    ax.add_collection3d(c)
    ax.set_xlim3d(x.min(),x.max())
    ax.set_ylim3d(y.min(),y.max())
    ax.set_zlim3d(z.min(),z.max())

    return ax

if __name__=='__main__':
    import numpy as np
    import matplotlib.pyplot as plt
    V = np.array([[0,0],[1,0],[2,0],[0,1],[1,1]])
    E = np.array([[0,1,3],[1,4,3],[1,2,4]])
    x = V[:,0]
    y = V[:,1]
    z = np.array([0,1,0,0.5,0.5])

    ax = mytrisurf(x,y,z,E)
    plt.show()
