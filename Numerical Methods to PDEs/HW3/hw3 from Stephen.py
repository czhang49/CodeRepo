from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg as la
import scipy.sparse as sparse
import scipy.sparse.linalg as sla

import mesh2d


# Step 0
mesh = 'xml'

if mesh == 'xml':
    """
    unstructured mesh [-1,1]^2 (with circle at 1/4)
    """
    V, E = mesh2d.xml('simple.xml')

    ne = E.shape[0]
    nv = V.shape[0]
    g = lambda x: 20 * (1 - x**2)

# plt.triplot(V[:,0],V[:,1],E)
# plt.show()


if mesh == 'uniform':
    """
    uniform mesh [-1,1]^2
    """
    V, E = mesh2d.uniform(25)
    V = 2.0 * V - 1.0

    ne = E.shape[0]
    nv = V.shape[0]

# Specify problem 1, 2, or 3
problem = 2

    # Define value of boundary function
def g(x):
    return 20 * (1 - x**2)

    # Define "material properties"
def kappa(x,y):
    if problem == 1:
        return 0.1
    elif problem == 2:
        return 0.5
    elif problem == 3:
        if (x**2 + y**2)**(0.5) <= 0.25:
            return 25
        elif (x**2 + y**2)**(0.5) > 0.25:
            return 0.1

    # Define forcing function
def f(x,y):
    if problem == 1:
        return 0.0
    else:
        if (x**2 + y**2)**(0.5) <= 0.25:
            return 25
        elif (x**2 + y**2)**(0.5) > 0.25:
            return 0.0

AA = np.zeros((ne, 9))
IA = np.zeros((ne, 9))
JA = np.zeros((ne, 9))
bb = np.zeros((ne, 3))
ib = np.zeros((ne, 3))
jb = np.zeros((ne, 3))


for ei in range(0,ne):
    # Step 1
        # Extract vertext numbers for each element
    v = np.zeros((3,))
    v = E[ei,:]

        # Determine x and y coordinate for each vertex
    coord = np.zeros((2,3))
    for a in range(0,3):
        coord[:,a] = V[v[a]]

    # Step 2
        # Compute J, J^-T, detJ
    J = np.matrix( [[coord[0,1] - coord[0,0], coord[0,2] - coord[0,0]], [coord[1,1] - coord[1,0], coord[1,2] - coord[1,0]]] )
    detJ = J[0,0]*J[1,1] - J[0,1]*J[1,0]
    invJ_t = np.matrix( [[J[1,1], -J[1,0]], [-J[0,1], J[0,0] ]] ) / detJ

    # Step 3
        # Compute dbasis
    dbasis = np.matrix( [[-1, 1, 0],[-1, 0, 1]] )
    
    # Step 4
        # Compute dphi and its transpose
    dphi = invJ_t*dbasis
    dphi_t = np.transpose(dphi)

    # Step 5
        # Compute coordinates for the center of the element
    xcenter = (coord[0,0] + coord[0,1] + coord[0,2])/3.0
    ycenter = (coord[1,0] + coord[1,1] + coord[1,2])/3.0

        # Compute Aelem
    Aelem = np.zeros((3,3))
    Aelem = dphi_t*dphi*detJ*kappa(xcenter,ycenter)*0.5
    
    # Step 6
        # Compute belem
    belem = np.zeros((3,))
    belem = detJ*f(xcenter,ycenter)*np.matrix( [[1/6.0],[1/6.0],[1/6.0]] )

    # Step 7
    AA[ei,:] = Aelem.ravel()
    IA[ei,:] = [v[0], v[0], v[0], v[1], v[1], v[1], v[2], v[2], v[2]]
    JA[ei,:] = [v[0], v[1], v[2], v[0], v[1], v[2], v[0], v[1], v[2]]
    bb[ei,:] = belem.ravel()
    ib[ei,:] = [v[0], v[1], v[2]]
    jb[ei,:] = 0

# Step 8
A = sparse.coo_matrix((AA.ravel(), (IA.ravel(), JA.ravel())))
A = A.tocsr()
A = A.tocoo()
b = sparse.coo_matrix((bb.ravel(), (ib.ravel(), jb.ravel())))
b = b.tocsr()
b = np.array(b.todense()).ravel()

# Step 9
u0 = np.zeros((nv,))

    # Establish boundary conditions
for i in range(0,nv):
    # Check if x = -1
    if V[i,0] == -1:
        u0[i,] = g(V[i,1])

b = b - A*u0
    # Convert A to format in which elements A_ij can be accessed
A = A.tolil()

    # Set b_i equal to zero where BC's are prescribed
for i in range(0,nv):
    if V[i,0] == -1.0 or V[i,0] == 1.0 or V[i,1] == -1.0 or V[i,1] == 1.0:
        b[i] = 0.0
        for j in range(0,nv):
            if j == i:
                A[i,j] = 1.0
            else:
                A[i,j] = 0.0
                A[j,i] = 0.0


# Step 10
    # Find solution
A = A.tocsr()
u = sla.spsolve(A,b)

u = u + u0

# Step 11
import mytrisurf
fig = plt.figure()
mytrisurf.mytrisurf(V[:,0], V[:,1], u, E)
plt.show()




