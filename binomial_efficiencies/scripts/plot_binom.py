import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import scipy.optimize as scopt
import pandas
import math

def binom( n):
    return 2*math.sqrt(  n * ( 1- n )  / 100 ) 

def err_ratio( eta ):
    return 0.5 + math.sqrt( (1 - eta) / eta )

root_data = pandas.read_csv( 'aux/fc_n1000.dat', delim_whitespace = True )



all_n = root_data.n.values
all_up = root_data.up.values
all_down = root_data.down.values

all_lower = []
all_upper = []

for  n, up, down in zip( all_n, all_up, all_down ):
    all_lower.append( n/100 - down )
    all_upper.append( up - n/100  )

asym_error = [ all_lower, all_upper ]

all_binom = [ binom(n/100) for n in all_n ]

#create canvas
fig,ax = plt.subplots(figsize = [8,5]  )

mpl.markers.MarkerStyle( fillstyle=u'full')

ax.plot( root_data.n/100, root_data.width , 
's',color = 'none', fillstyle = 'full', 
label = 'Feldman Cousins') 

ax.plot( root_data.n/100, all_binom , 
'v', color = 'black', fillstyle = 'full',
label = 'Binomial') 
ax.grid()

lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels, loc = 'lower center' )

ax.set_xlabel( 'True efficiency' )
ax.set_ylabel( 'Error on true efficiency' )


plt.draw()
#ax.errorbar( all_n, all_n/100, yerr=asym_error, fmt='o' )

plt.savefig( 'output/binom.pdf', format = 'pdf', transparent = 'true' )

plt.close('all')

fig,ax = plt.subplots(figsize = [8,5]  )

eta_range = np.linspace(0.5,0.99,98)
err_ratio_values = [err_ratio(eta) for eta in eta_range ]
ax.plot( eta_range, err_ratio_values, color = 'black' )
ax.grid()
ax.set_xlabel( '1TRKL efficiency' )
ax.set_ylabel( 'Rel.Error(Q1) / Rel.Error(Q1x1TRKL) ')
plt.savefig( 'output/q1vsq11t.pdf', format = 'pdf', transparent = 'true' )
