#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas
import os.path as osp
from mpl_toolkits.axes_grid1.parasite_axes import SubplotHost
import sys

infolder = '2015-09-22'
infile = 'tgt_lim.txt'

#load my results
myd = pandas.read_csv( osp.join('data/', infolder, infile ), sep=r'\s+', encoding = 'utf-8' )
sigd = myd[ (myd['mass'] > 275) & (myd['mass'] < 376) ].copy()

#load data sources
pim2  = pandas.read_csv( 'data/pim2.txt', delim_whitespace = True,  encoding = 'utf-8', header = None, names = ['mass', 'u2'] )
km2hayano = pandas.read_csv( 'data/km2hayano.dat', delim_whitespace = True, encoding = 'utf-8' )
e949  = pandas.read_csv( 'data/bnle949.dat', delim_whitespace = True,  encoding = 'utf-8' )

fig = plt.figure( figsize = [8,6] )
ax = SubplotHost( fig, 1, 1, 1, )
fig.add_subplot(ax)

#--------------------------------------------------
#U2
#--------------------------------------------------

ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Limit on $|U_{\mu h}|^2$' )

ax.set_xlim( 0.00, 0.4 )
ax.set_ylim( 5e-10, 8e-4 )
ax.grid( True)
ax.plot( 0.001 * pim2['mass'],pim2['u2'], 'r',  label = 'SIN (1981)' )
ax.plot( 0.001 * km2hayano['mass'], km2hayano['U2'],'b-', label = 'KEK (1982)' )
ax.plot( 0.001 * e949['mass'], 0.1 * e949['U2'], 'g',  label = 'E949 (2015)' )
expect, = ax.plot( 0.001 * sigd['mass'], sigd['ul_u2'], 'k-', label = 'Expected sensitivity' )
ses, = ax.plot( 0.001 * sigd['mass'], sigd['ses_u2'], 'k--', label = 'Single event sensitity' )
ax.set_yscale('log')

plt.savefig( osp.join('output', 'pub', 'u2expect_noleg.pdf'), format = 'pdf', transparent = 'true' )
plt.savefig( osp.join('output', 'pub', 'u2expect_noleg.eps'), format = 'eps', transparent = 'true' )
plt.savefig( osp.join('output', 'pub', 'u2expect_noleg.png'), format = 'png', transparent = 'true' )

lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, ncol = 2, loc = 'upper right', prop={'size':14} )

plt.savefig( osp.join('output', 'pub', 'u2expect.pdf'), format = 'pdf', transparent = 'true' )
plt.savefig( osp.join('output', 'pub', 'u2expect.eps'), format = 'eps', transparent = 'true' )
plt.savefig( osp.join('output', 'pub', 'u2expect.png'), format = 'png', transparent = 'true' )
