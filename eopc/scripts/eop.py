#!/usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt

dt = pd.read_csv( 'data/eopCorrfile.dat', delim_whitespace = True,
        names = ['cpd', 'cell', 'corr'], header = None )

print( dt['corr'].std() )

fig = plt.figure()
ax = fig.add_subplot( 111 )

ax.hist( dt['corr'], 50 )
ax.set_yscale( 'log' )
plt.savefig( 'output/corr.pdf',  format = 'pdf' )
