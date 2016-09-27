#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import scipy.optimize as scopt
import pandas as pd
import math

gd = pd.read_csv( 'aux/cp_grid.dat', delim_whitespace = True )
thresh = pd.read_csv( 'aux/cp_thresh.dat', delim_whitespace = True )

#create canvas
fig,ax = plt.subplots(figsize = [7,5]  )

ax.set_xlim( 0, 2000 )
ax.set_ylim( 0.5, 1.0 )
ax.set_xlabel( 'Expected number of background events' )
ax.set_ylabel( 'Trigger efficiency' )
plotted = ax.scatter( gd['ntotal'], gd['eff'], c = gd['rat'],marker = 's', edgecolor = 'None', cmap = 'YlGnBu_r'  )
cbar = plt.colorbar( mappable = plotted )

ax.plot( thresh['ntotal'], thresh['eff_thresh'], 'ks-' )


plt.savefig( 'output/cp_grid.pdf' )

