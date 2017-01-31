from dolfin import *
import numpy as np
import math
h=[]
e=[]
nmeshes=4
mesh=UnitSquare(4,4)
f = Expression('2.0*pi*pi*sin(pi*x[0])*sin(pi*x[1])')
class uexact(Expression):
    def eval(self, values,x):
        values[0]=sin(pi*x[0])*sin(pi*x[1])
for i in range(nmeshes):
    print '...running mesh %d of %d'%(i,nmeshes)
    mesh = refine(mesh)
    u_exact=uexact()
##    V=VectorFunctionSpace(mesh,'CG',1)
    V=FunctionSpace(mesh,'RT',1)
    Q=FunctionSpace(mesh,'DG',0)
    W=V*Q
    x = W.cell().x
    def u0_boundary(x):
      tol = 1E-10
      return  abs(x[0]-1.0)<tol or \
              abs(x[1]-1.0)<tol or \
              abs(x[1])<tol or \
              abs(x[0])<tol
    (q,u)=TrialFunctions(W)
    (tau,v)=TestFunctions(W)
    ## define problem
    a=(dot(tau,q)+div(tau)*u+v*div(q))*dx
    L=-v*f*dx
    bc=DirichletBC(W.sub(1),u_exact,u0_boundary)
    QU=Function(W)
    solve(a==L,QU,bc)
    (q,u)=QU.split()
##    plot(u)
##    plot(q)
##    interactive()
    err = errornorm(u_exact, u, norm_type='l2', degree_rise=3, mesh=mesh)
    e.append(err)
    h.append(mesh.hmax())
e = np.array(e)
h = np.array(h)
rate = np.log(e[1:] / e[:-1]) / np.log(h[1:] / h[:-1])

