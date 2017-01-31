from dolfin import *
# Step 0
mesh = Mesh('simple.xml')
V = FunctionSpace(mesh, 'Lagrange', 1)
x = V.cell().x
example = 'c'

if example == 'a':
    f = Constant(0.0)
    kappa = Constant(0.1)

if example == 'b':
    f     = conditional( le( sqrt(x[0]**2 + x[1]**2), 0.25), 25.0, 00.0)
    kappa = Constant(0.5)

if example == 'c':
    f     = conditional( le( sqrt(x[0]**2 + x[1]**2), 0.25), 25.0, 0.0)
    kappa = conditional( le( sqrt(x[0]**2 + x[1]**2), 0.25), 25.0, 0.1)
    
# Step 1
u1=Expression('20*(1-x[1]*x[1])')
u2=Constant(0.0)
def BC1(x):
        tol = 1E-10
        return abs(x[0]+1)<tol
def BC2(x):
        tol = 1E-10
        return abs(x[0]-1)<tol or \
               abs(x[1]-1)<tol or \
               abs(x[1]+1)<tol
        
Gamma_1= DirichletBC(V,u1,BC1)
Gamma_2= DirichletBC(V,u2,BC2)
bc=[Gamma_1,Gamma_2]
# Step 2
u=TrialFunction(V)
v=TestFunction(V)
# Step 3
a=kappa*inner(nabla_grad(u),nabla_grad(v))*dx
L=f*v*dx
# Step 4
u=Function(V)
solve(a == L,u,bc)

plot(u)

interactive()
