#!/usr/bin/env python
import matplotlib.pyplot as plt
import pandas as pd

dt = pd.read_csv( 'data/bf.dat', delim_whitespace = True )

fig = plt.figure()
ax = fig.add_subplot( 111 )
ax.plot( dt['z'], dt['bx'] )
ax.plot( dt['z'], dt['by'] )
plt.savefig( 'output/bxy.pdf', format = 'pdf' )
