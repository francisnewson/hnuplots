#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas
import os.path as osp
from mpl_toolkits.axes_grid1.parasite_axes import SubplotHost
import sys

infile = 'tgt_lim.txt'

orig = pandas.read_csv( osp.join('data/', '2015-09-22', infile ),
        delim_whitespace = True,  encoding = 'utf-8' )

semi =  pandas.read_csv( osp.join('data/', 'semi_k3pi', infile ),
        delim_whitespace = True,  encoding = 'utf-8' )

extra =  pandas.read_csv( osp.join('data/', 'extra_k3pi', infile ),
        delim_whitespace = True,  encoding = 'utf-8' )


fig = plt.figure( figsize = [8,6] )
ax = SubplotHost( fig, 1, 1, 1, )
fig.add_subplot(ax)


ax.grid('on')

for dt, color, name in zip(
        [orig, semi, extra], ['green', 'orange', 'red'], ['3.5\%', '11\%', '35\%'] ):
    sigd = dt[ (dt['mass'] > 275) & (dt['mass'] < 376) ].copy()
    ax.plot(0.001 * sigd['mass'], sigd['dt_ul_u2'], '-', color =color,lw = 1 , label = name) 

lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, loc = 'upper left', prop={'size':20} )

plt.tight_layout()
plt.savefig( 'output/k3pi_comp_ul.pdf' )

ax.set_yscale('log')
plt.savefig( 'output/k3pi_comp_ul_log.pdf' )
