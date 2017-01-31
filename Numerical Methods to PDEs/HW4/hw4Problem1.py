from dolfin import *
import numpy as np

mesh = UnitSquare(4,4)
f = Expression('1.0/(pow(pow(x[0]-1.0/3.0,2)+pow(x[1]-1.0/3.0,2),1))')
h = []
e = []
nmeshes = 4
for i in range(nmeshes):
    print '...running mesh %d of %d'%(i,nmeshes)
    mesh = refine(mesh)
    V = FunctionSpace(mesh, 'Lagrange', 1)
    fv = interpolate(f, V)

    error = errornorm(f, fv, norm_type='l2', degree_rise=3, mesh=mesh)
    e.append(error)
    h.append(mesh.hmax())

e = np.array(e)
h = np.array(h)
rate = np.log(e[1:] / e[:-1]) / np.log(h[1:] / h[:-1])
plot(f,mesh,interactive=True)
