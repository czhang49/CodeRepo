from dolfin import *
import numpy as np
import math
class uexact(Expression):
    def eval(self, values,x):
        psi = math.atan2(x[1],x[0])
        if psi < 0:
            psi += 2*pi
        values[0] = (x[0]**2 +x[1]**2)**(1.0/3.0)*sin(2.0/3.0*psi)


mesh = Mesh('lshape.xml')
plot(mesh,interactive=True) 
f = Constant(0.0)
# mesh refinement
h = []
eL2 = []
eH1 = []
nmeshes = 4
for i in range(nmeshes):
    print '...running mesh %d of %d'%(i,nmeshes)
    mesh = refine(mesh)
    V = FunctionSpace(mesh, 'Lagrange', 1)
    x = V.cell().x
    u_exact=uexact()
    def u0_boundary(x):
      tol = 1E-10
      return abs(x[0]+1.0)<tol or \
            abs(x[1]-1.0)<tol or \
            abs(x[1]+1.0)<tol or \
            abs(x[0]-1.0)<tol or \
            abs(x[1])<tol and x[0]>-tol or \
            abs(x[0])<tol and x[1]<tol   
 
    bc= DirichletBC(V,u_exact,u0_boundary)
    u=TrialFunction(V)
    v=TestFunction(V)
    a=inner(nabla_grad(u),nabla_grad(v))*dx
    L=f*v*dx    
    u=Function(V)
    solve(a == L,u,bc)
    errl2 = errornorm(u_exact, u, norm_type='l2', degree_rise=3, mesh=mesh)
    errh1 = errornorm(u_exact, u, norm_type='h1', degree_rise=3, mesh=mesh)
    eL2.append(errl2)
    eH1.append(errh1)
    h.append(mesh.hmax())
    plot(u,mesh,interactive=True)
eL2 = np.array(eL2)
eH1 = np.array(eH1)
h = np.array(h)
rateL2 = np.log(eL2[1:] / eL2[:-1]) / np.log(h[1:] / h[:-1])
rateH1 = np.log(eH1[1:] / eH1[:-1]) / np.log(h[1:] / h[:-1])
