#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np

def fom( r, eff ):
    return np.sqrt( r / ( np.square(eff) + r * eff * ((1 - eff))))

def min_fom( f ):
    return 2 * np.sqrt( (r - 1 ) / r ) 

effs = np.arange( 0.01, 1 , 0.01 )

fom_1 = lambda x: fom( 1, x )
fom_2 = lambda x: fom( 2, x )
fom_3 = lambda x: fom( 3, x )
fom_4 = lambda x: fom( 4, x )


#create canvas
fig,ax = plt.subplots(figsize = [5,5]  )

ax.grid( 'on' )
ax.set_xlabel( r'efficiency, $\eta$' )
ax.set_ylabel( r'Figure of merit')


ax.plot( effs, fom_1(effs), label = 'r = 1')
ax.plot( effs, fom_2(effs), label = 'r = 2')
ax.plot( effs, fom_3(effs), label = 'r = 3')
ax.plot( effs, fom_4(effs), label = 'r = 4')

lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels )

ax.set_ylim( 0, 5 )

plt.savefig( 'output/effs_fom.pdf', format = 'pdf' )
