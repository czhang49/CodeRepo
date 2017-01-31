from pylab import *
from scipy import *
import scipy.sparse.linalg as sla
import scipy.sparse as sparse
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import time


#######################################
# Specify h and lambda => Calculate k #
#######################################

h = 1/20.
mu = 20
k = h**2*mu

########################
# Develop (x,y,t) grid #
########################

x_dim = 1/h
y_dim = x_dim
t_dim = 1/k

x = np.linspace(0,1,x_dim)
y = np.linspace(0,1,y_dim)
t = np.linspace(0,0.8,t_dim)

################################################
# Specify initial data and boundary conditions #
################################################

ic = mat(zeros((x_dim,y_dim)))

for i in range (0,len(x)):
    for j in range (0,len(y)):
        if (x[i]-0.5)**2+(y[j]-0.5)**2 >= 1/16. and (x[i]-0.5)**2+(y[j]-0.5)**2 <= 1/8.:
            ic[i,j] = 5


##########################
# Plot initial condition #
##########################

fig = plt.figure(1)
axis = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)
surf = axis.plot_surface(X, Y, ic, rstride=1, cstride=1, cmap=cm.winter,
        linewidth=0, antialiased=False)
plt.show()


###########################################
# Construct diagonal matrix for inversion #
###########################################

onez = np.ones((x_dim*y_dim,))
A = sparse.spdiags(np.vstack((-mu*onez,-mu*onez/2,(1+3*mu)*onez,-mu*onez/2,-mu*onez)), np.array([-x_dim,-1,0,1,x_dim]),x_dim*y_dim,x_dim*y_dim).todense()
B = sparse.spdiags(np.vstack((mu*onez,mu*onez/2,(1-3*mu)*onez,mu*onez/2,mu*onez)), np.array([-x_dim,-1,0,1,x_dim]),x_dim*y_dim,x_dim*y_dim).todense()


##############################################
# Establish boundary condtions for each edge #
##############################################
'''
(a,b) correspond to (x,y) when establishing the bounday conditions
The first two loops establish the Neumann BC's
The secton two loops establish the Dirichlet BC's
'''

for a in range(0,len(x)):
    A[a,a+x_dim] = A[a,a+x_dim] - mu
    B[a,a+x_dim] = B[a,a+x_dim] + mu
for b in range(0,len(y)):
    if not (b == 0):
        A[b*y_dim,b*y_dim + 1] = A[b*y_dim,b*y_dim + 1] - mu/2
        A[b*y_dim,b*y_dim - 1] = 0
        B[b*y_dim,b*y_dim + 1] = B[b*y_dim,b*y_dim + 1] + mu/2
        B[b*y_dim,b*y_dim - 1] = 0
    else:
        A[b*y_dim,b*y_dim + 1] = A[b*y_dim,b*y_dim + 1] - mu/2
        B[b*y_dim,b*y_dim + 1] = B[b*y_dim,b*y_dim + 1] + mu/2
for a in range(0,len(x)):
    A[(y_dim-1)*x_dim + a,(y_dim - 1)*x_dim + a] = 10**20
    B[(y_dim-1)*x_dim + a,(y_dim - 1)*x_dim + a] = 10**20
for b in range(0,len(y)):
    A[(b+1)*x_dim - 1,(b+1)*x_dim - 1] = 10**20
    B[(b+1)*x_dim - 1,(b+1)*x_dim - 1] = 10**20


u = mat(zeros((x_dim*y_dim,t_dim)))
u[:,0] = ic.reshape(x_dim*y_dim,1)
for i in range (1,len(t)):
    u[:,i] = sparse.linalg.spsolve(A,B*u[:,i-1]).reshape(x_dim*y_dim,1)




#######################################
# Plot results for various time-steps #
#######################################

fig = plt.figure(2)
axis = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)
surf = axis.plot_surface(X, Y, u[:,1/k/4].reshape(x_dim,y_dim) , rstride=1, cstride=1, cmap=cm.winter, linewidth=0, antialiased=False)
plt.show()

fig = plt.figure(3)
axis = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)
surf = axis.plot_surface(X, Y, u[:,1/k/2].reshape(x_dim,y_dim) , rstride=1, cstride=1, cmap=cm.winter, linewidth=0, antialiased=False)
plt.show()

fig = plt.figure(4)
axis = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)
surf = axis.plot_surface(X, Y, u[:,3/k/4].reshape(x_dim,y_dim) , rstride=1, cstride=1, cmap=cm.winter, linewidth=0, antialiased=False)
plt.show()

fig = plt.figure(4)
axis = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)
surf = axis.plot_surface(X, Y, u[:,1/k-1].reshape(x_dim,y_dim) , rstride=1, cstride=1, cmap=cm.winter, linewidth=0, antialiased=False)
plt.show()

    
