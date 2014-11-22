import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import scipy.optimize as scopt
import pandas
import math

def res_fit_func( x, x0, res0, offset ):
    return res0 * np.sqrt( x0 - x) + offset

#load data
hnu_data = pandas.read_csv( 'data/hnu.dat' , 
        sep = r'\s+', encoding = 'utf-8' )

hnu_data_pos = hnu_data[ hnu_data.pol == 'pos' ]
hnu_data_neg = hnu_data[ hnu_data.pol == 'neg' ]

fit_params, fit_cov = scopt.curve_fit( res_fit_func, hnu_data_pos.mass.values, hnu_data_pos.FitSigma.values,[ 400, 0.0035, 0])
print (fit_params)
print (fit_cov)


#create canvas
fig,ax = plt.subplots(figsize = [12,8]  )

ax.plot( hnu_data_pos.mass, hnu_data_pos.FitSigma , 'o', markeredgecolor = 'red',
        fillstyle = 'none', label = 'Positive polarity') 

m = np.linspace( 0, 400, 400 )

ax.plot( m, res_fit_func(m, *fit_params ) )

#ax.plot( hnu_data_neg.mass, hnu_data_neg.FitSigma , 's', markeredgecolor = 'blue',
        #fillstyle = 'none', label = 'Negative polarity') 

lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels, loc = 'upper right' )
plt.draw()

plt.savefig( 'output/resolution.pdf', format = 'pdf', 
        transparent = 'true' )
