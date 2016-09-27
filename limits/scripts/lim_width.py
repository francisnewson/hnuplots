#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas

#load data sources
dt = pandas.read_csv( 'data/width/width_lim_good.txt',
	encoding = 'utf-8', delim_whitespace = True,
        header = None, names = ['mass', 'width', 'lim', 'anotherwidth' ] )

print( dt)
indices  = dt.groupby( ['mass']).apply( lambda x : x['lim'].idxmin() ) 
print( indices )

best =  ( dt.loc[ indices ] )

#intialize
fig = plt.figure( figsize = [8,6] )
ax = fig.add_subplot(111)

ax.grid('on')
ax.set_ylim( 0.3, 1.7 )
ax.plot( 0.001 * best['mass'], best['width'], 'o', mec  = 'none' )

ax.set_ylim( 0, 2 )
ax.set_xlabel( r"Neutrino mass $(\unit[]{GeV/c^2})$")
ax.set_ylabel( r"Optimum $n$ (number of $\sigma_h$ in half-width" )

plt.savefig( 'output/best_width.pdf' )
