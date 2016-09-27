#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas
import os.path as osp
from mpl_toolkits.axes_grid1.parasite_axes import SubplotHost

infolder = '2015-09-22'
folder = '2015-09-14_tgt'
infile = 'tgt_lim.txt'

myd = pandas.read_csv( osp.join('data/', infolder, infile ), sep=r'\s+', encoding = 'utf-8' )

sigd = myd[ (myd['mass'] > 275) & (myd['mass'] < 376) ].copy()

fig = plt.figure( figsize = [6,6] )
ax = SubplotHost( fig, 1, 1, 1, )
fig.add_subplot(ax)

ax.set_xlim( 0.27, 0.39 )
ax.grid( True)

ax.plot(0.001 *sigd['mass'], sigd['ul_mu'], 'k--' )
ax.plot(0.001 * sigd['mass'], sigd['dt_ul_mu'], 'k-+' )

ax.fill_between(0.001 * sigd['mass'], sigd['low3_ul_mu'],  sigd['high3_ul_mu'], facecolor  = '#27E50C', label = '$3\sigma$' )
ax.fill_between(0.001 * sigd['mass'], sigd['low1_ul_mu'],  sigd['high1_ul_mu'], facecolor  = '#FCFF2B', label = '$1 \sigma$' )
p1 = plt.Rectangle((0, 0), 1, 1, fc="#FCFF2B")
p3 = plt.Rectangle((0, 0), 1, 1, fc="#27E50C")
leg = plt.legend( [p1, p3], [ '$1 \sigma$', '$3 \sigma$' ] )


ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Upper limit on number of heavy neutrinos detected' )


plt.savefig( osp.join('output', folder, 'mu.pdf'), format = 'pdf', transparent = 'true' )
