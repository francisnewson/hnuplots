#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas
import os.path as osp
from mpl_toolkits.axes_grid1.parasite_axes import SubplotHost
import sys
import scipy.stats

infolder = '2015-09-22'
folder = '2015-09-14_tgt'
infile = 'tgt_lim.txt'

myd = pandas.read_csv( osp.join('data/', infolder, infile ), sep=r'\s+', encoding = 'utf-8' )

print( myd.columns )

trigs =  myd[ (myd['mass'] < 371) & (myd['mass'] > 270)][['mass','trig_eff','raw_trig_err']] 

print( trigs['raw_trig_err'].max() )
print( trigs['trig_eff'].min() )
print( trigs['trig_eff'].max() )

def chi2( row ):
    return np.square(( row['trig_eff'] - 0.899 ) / row['raw_trig_err'])


trigs['chi2'] = trigs.apply( chi2 , axis = 1)


chi2sum = trigs['chi2'].sum()
ndof = len(trigs )
prob = scipy.stats.chisqprob( chi2sum, ndof )

print( 'p( Σχ2 = {0}, dof = {1} ) = {2}'.format( chi2sum, ndof, prob ) )
