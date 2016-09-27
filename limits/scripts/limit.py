#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas

#load data sources
km2hayano = pandas.read_csv( 'data/km2hayano.dat', 
		sep=r"\s+", encoding = 'utf-8' )

km2e949 = pandas.read_csv( 'data/bnle949.dat', 
		sep=r"\s+", encoding = 'utf-8' )

#intialize
fig = plt.figure( figsize = [8,6] )
ax = fig.add_subplot(111)

plt.cla()
ax.grid( True)

hayano_color = '#000000'
kmnnn_color = '#444444'
km2e949_color = '#888888'

ax.plot( km2hayano['mass'], km2hayano['U2'], label = 'KEK (1982)',
                ls = '--', lw = 2, color = hayano_color,  mec = 'none' )

ax.plot( km2e949['mass'], 0.1 * km2e949['U2'], label = 'E949 (2015)',
                ls = '-', lw = 2, color = km2e949_color,  mec = 'none' )

#Add legend
lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, frameon = True, loc = 'lower left' )
leg.get_frame().set_facecolor('#ffffff')

#Label axes
ax.set_xlim( 0, 400 )
ax.set_ylim( 1e-9, 4e-5 )
plt.xlabel( r'Heavy neutrino mass $(\unit[]{MeV/c^2}$ )' )
plt.ylabel( '$|U_{\mu h}|^{2}$' )
ax.set_yscale( 'log' )

for line in ax.get_xticklines() + ax.get_yticklines():
            line.set_markersize(10)

ax.grid( True, 'both' )
plt.tight_layout()

name = 'existing_limits'
plt.savefig( "output/{0}.pdf".format( name), format = 'pdf', transparent = 'true' )
