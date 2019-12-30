import py222
import solver
import numpy as np

# get solved state
s = py222.initState()

# apply some scramble
s = py222.doAlgStr(s, "F2")

# solve cube
solver.solveCube(s)