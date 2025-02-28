import twophase.solver  as sv

# Example cube state (valid format, 54 characters long)
cubestring = 'DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL'

sv.solve(cubestring,19,2)
print("Solution:", sv)
