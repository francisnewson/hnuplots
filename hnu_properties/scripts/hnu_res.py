import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas

#load data
hnu_data = pandas.read_csv( 'data/hnu.dat' , 
        sep = r'\s+', encoding = 'utf-8' )

hnu_data_pos = hnu_data[ hnu_data.pol == 'pos' ]
hnu_data_neg = hnu_data[ hnu_data.pol == 'neg' ]

#create canvas
fig,ax = plt.subplots(figsize = [6,4]  )

ax.plot( hnu_data_pos.mass, hnu_data_pos.FitSigma , 'o', markeredgecolor = 'red',
        fillstyle = 'none', label = 'Positive polarity') 

ax.plot( hnu_data_neg.mass, hnu_data_neg.FitSigma , 's', markeredgecolor = 'blue',
        fillstyle = 'none', label = 'Negative polarity') 

lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels, loc = 'upper right' )
plt.draw()

plt.savefig( 'output/resolution.pdf', format = 'pdf', 
        transparent = 'true' )
