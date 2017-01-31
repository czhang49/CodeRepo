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
    kappa = Constant(0.1)

if example == 'c':
    f     = conditional( le( sqrt(x[0]**2 + x[1]**2), 0.25), 25.0, 0.0)
    kappa = conditional( le( sqrt(x[0]**2 + x[1]**2), 0.25), 25.0, 0.1)

# Step 1

# Step 2

# Step 3

# Step 4
