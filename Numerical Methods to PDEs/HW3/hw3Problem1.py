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
    g = lambda x: 10 * (1 - x**2)

if mesh == 'uniform':
    """
    uniform mesh [-1,1]^2
    """
    V, E = mesh2d.uniform(25)
    V = 2.0 * V - 1.0

    ne = E.shape[0]
    nv = V.shape[0]

# Speficy the number of the case 
CASE=3;  # 1 2 3 Corresponds to case a b c

def g(x):
    return 20 * (1 - x**2)

def kappa(x,y):

    return 0.1

def f(x,y):
    return 0

AA = np.zeros((ne, 9))
IA = np.zeros((ne, 9))
JA = np.zeros((ne, 9))
bb = np.zeros((ne, 3))
ib = np.zeros((ne, 3))
jb = np.zeros((ne, 3))



for ei in range(0,ne):
    # Step 1
    v = np.zeros((3,))
    v = E[ei,:]
    X1=V[v[0]][0]
    X2=V[v[1]][0]
    X3=V[v[2]][0]
    Y1=V[v[0]][1]
    Y2=V[v[1]][1]
    Y3=V[v[2]][1]
    # Step 2
    Jacob=np.zeros((2,2))
    Jacob[0][0]=-X1+X2
    Jacob[0][1]=-Y1+Y2
    Jacob[1][0]=-X1+X3
    Jacob[1][1]=-Y1+Y3
    JacobInv=np.linalg.inv(Jacob)
    JacobDet=np.linalg.det(Jacob)
    
    # Step 3
    GradRef=np.zeros((2,3))
    GradRef[0][0]=-1
    GradRef[0][1]=1
    GradRef[0][2]=0
    GradRef[1][0]=-1
    GradRef[1][1]=0
    GradRef[1][2]=1
    
    # Step 4
    GradBasis=np.dot(JacobInv,GradRef)
    
    # Step 5
    Aelem = np.zeros((3,3))
    TransGradBasis=GradBasis.transpose()
    Coeff=JacobDet*np.dot(TransGradBasis,GradBasis)
    Area=0.5

    if CASE==1:
        Aelem=Coeff*0.1*Area
    if CASE==2:
        Aelem=Coeff*0.5*Area
    if CASE==3:
        Xcenter=(X1+X2+X3)/3
        Ycenter=(Y1+Y2+Y3)/3
        MaxDist=(Xcenter**2+Ycenter**2)**(0.5)
        if (MaxDist<=0.25):
            Aelem=Coeff*25*Area
        else :
            Aelem=Coeff*0.1*Area

    # Step 6
    
    Coeff2=JacobDet
    belem   = np.zeros((3,))
    InteVec = np.zeros((3,))
    InteVec[0]=1.0/6
    InteVec[1]=1.0/6
    InteVec[2]=1.0/6
    
    if CASE==1:
        belem=belem
    if CASE==2:
        Xcenter=(X1+X2+X3)/3
        Ycenter=(Y1+Y2+Y3)/3
        MaxDist=(Xcenter**2+Ycenter**2)**(0.5)
        if (MaxDist<=0.25):
            belem=Coeff2*25*InteVec;
        
    if CASE==3:
        if (MaxDist<=0.25):
            belem=Coeff2*25*InteVec

    belem=np.matrix(belem)  
    belem=belem.transpose()
    
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
Boolean=np.zeros((nv,))
for counter in range (0,nv):
    if (V[counter,0]==-1):
        u0[counter]=20*(1-(V[counter][1])*(V[counter][1]))
    if (V[counter][0]==-1 or V[counter][0]==1 or V[counter][1]==-1 or V[counter][1]==1):
        Boolean[counter]=1
b=b-A*u0
A=A.tolil()

for counter_2 in range (0,nv):
    if (Boolean[counter_2]==1):
        b[counter_2]=0.0
        A[counter_2,:]=0.0
        A[:,counter_2]=0.0
        A[counter_2,counter_2]=1

# Step 10
A = A.tocsr()
u = sla.spsolve(A,b)

u = u + u0

# Step 11
import mytrisurf
fig = plt.figure()
mytrisurf.mytrisurf(V[:,0], V[:,1], u, E)
plt.show()


