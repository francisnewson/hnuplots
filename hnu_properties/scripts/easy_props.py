#!/usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt

dt = pd.read_csv( 'data/hnu_stats.dat', delim_whitespace = True )

fig = plt.figure( figsize = [8, 6] )
fig.set_tight_layout(True)
ax = fig.add_subplot( 111 )

ax.grid( 'on' )
ax.set_xlabel( r'Neutrino mass ($\rm{MeV}/c^2$)' )
ax.set_ylabel( 'Acceptance' )
ax.set_ylim( 0, 1 )
ax.errorbar( dt['mass'], dt['acceptance'], yerr = dt['acc_err'], fmt = 'k--s', mec = None, markeredgecolor = None, markersize = 7 )

plt.savefig( 'output/hnu_accep.pdf' )


plt.cla()

ax.grid( 'on' )
ax.set_xlabel( r'Neutrino mass ($\rm{MeV}/c^2$)' )
ax.set_ylabel( r'Resolution ($\rm{GeV}^{2}/c^{4}$)' )
#dt['sep'] = (0.001**2)*( (dt['mass'] + 1 )**2  - ( dt['mass'] )**2 ) 

#print( dt[['mass', 'sep', 'width']] )

#ax.plot( dt['mass'], (0.001**2)*( (dt['mass'] + 1 )**2  - ( dt['mass'] )**2 ) )
#ax.plot( dt['mass'], (0.001**2)*( (dt['mass'] + 1 )**2  - ( dt['mass'] )**2 ) - dt['width'] )
#ax.set_ylim( 0, 0.0040 )
ax.plot( dt['mass'], dt['fit_sigma'], 'k--s', mec = None, markeredgecolor = None, markersize = 7 )

plt.savefig( 'output/hnu_res.pdf' )
