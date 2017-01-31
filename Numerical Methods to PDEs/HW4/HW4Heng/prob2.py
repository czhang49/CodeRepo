from dolfin import *
import numpy as np

# Step exact solution
mesh = UnitSquare(400,400)
f = Expression('1.0/(pow(pow(x[0]-1.0/3.0,2)+pow(x[1]-1.0/3.0,2),2))')
V = FunctionSpace(mesh, 'Lagrange', 1)
x = V.cell().x
u1=Constant(0.0)
def u0_boundary(x):
        tol = 1E-10
        return abs(x[0]-0.0)<tol or \
               abs(x[1]-0.0)<tol or \
               abs(x[1]-1.0)<tol or \
               abs(x[0]-1.0)<tol
        
        
bc= DirichletBC(V,u1,u0_boundary)
u=TrialFunction(V)
v=TestFunction(V)
a=inner(nabla_grad(u),nabla_grad(v))*dx
L=f*v*dx
u_exact=Function(V)
solve(a == L,u_exact,bc)

plot(u_exact,mesh,interactive=True)
# mesh refinement
mesh = UnitSquare(4,4)
h = []
eL2 = []
eH1 = []
nmeshes = 4
for i in range(nmeshes):
    print '...running mesh %d of %d'%(i,nmeshes)
    mesh = refine(mesh)
    V = FunctionSpace(mesh, 'Lagrange', 1)
    x=V.cell().x
    def u0_boundary(x):
        tol = 1E-10
        return abs(x[0]-0.0)<tol or \
               abs(x[1]-0.0)<tol or \
               abs(x[1]-1.0)<tol or \
               abs(x[0]-1.0)<tol
    bc= DirichletBC(V,u1,u0_boundary)
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

eL2 = np.array(eL2)
eH1 = np.array(eH1)
h = np.array(h)
rateL2 = np.log(eL2[1:] / eL2[:-1]) / np.log(h[1:] / h[:-1])
rateH1 = np.log(eH1[1:] / eH1[:-1]) / np.log(h[1:] / h[:-1])
plot(u,mesh,interactive=True)
