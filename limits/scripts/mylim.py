#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas
import os.path as osp
from mpl_toolkits.axes_grid1.parasite_axes import SubplotHost
import sys

#infolder = '2015-09-22'
#infolder = 'extra_k3pi'
#infolder = 'semi_k3pi'

#infolder = '2015-09-22'
#folder = '2015-09-14_tgt'
#infile = 'tgt_lim.txt'

#infolder = '2016-02-23'
#folder = '2016-02-23_tgt_lim'
#infile = 'tgt_lim.txt'

infolder = '2016-02-23'
folder = '2016-02-23_unitrig'
infile = 'tgt_lim_unitrig.txt'

#infolder = '2015-09-22'
#folder = '2015-10-21_orig_k3pi'
#infile = 'tgt_lim.txt'

#infolder = 'extra_k3pi'
#folder = '2015-10-21_extra_k3pi'
#infile = 'tgt_lim.txt'

#infolder = 'semi_k3pi'
#folder = '2015-10-21_semi_k3pi'
#infile = 'tgt_lim.txt'

#infolder = 'halo_zero'
#folder = '2015-10-21_halo_zero'
#infile = 'tgt_lim.txt'

#infolder = 'km3_br'
#folder = '2015-10-21_km3_br'
#infile = 'tgt_lim.txt'

#infile = 'loose_lim.txt'
#folder = '2015-09-14_loose'

myd = pandas.read_csv( osp.join('data/', infolder, infile ), sep=r'\s+', encoding = 'utf-8' )

#load data sources
km2hayano = pandas.read_csv( 'data/km2hayano.dat', sep=r"\s+", encoding = 'utf-8' )
e949  = pandas.read_csv( 'data/bnle949.dat', sep=r"\s+", encoding = 'utf-8' )

sigd = myd[ (myd['mass'] > 275) & (myd['mass'] < 376) ].copy()


#intialize
fig = plt.figure( figsize = [8,8] )
#fig = plt.figure( figsize = [6,4] )
ax = SubplotHost( fig, 1, 1, 1, )
fig.add_subplot(ax)

plt.cla()
plt.tight_layout()

myd['sep'] =  myd['width'] / (0.001**2*( (myd['mass']+1)**2 - ((myd['mass'] ))**2 ) )
#print( myd[['mass','sep','width']])
#ax.plot( myd['mass'], myd['sep']  )
ax.plot( myd['mass'], myd['width']  )
plt.savefig( osp.join('output', folder, 'width.pdf') , format = 'pdf', transparent = 'true' )

plt.cla()
plt.tight_layout()
ax.set_xlim( 0.24, 0.4 )
ax.grid( True)
ax.errorbar( 0.001 * myd['mass'], myd['final_acc'], yerr = myd['final_acc_err'], fmt ='ko', markersize = 2 )
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Signal acceptance' )
plt.tight_layout()
plt.savefig( osp.join('output', folder, 'final_acc.pdf') , format = 'pdf', transparent = 'true' )

plt.cla()

#sys.exit()

ax.grid( True)
ax.set_xlim( 0.24, 0.4 )
ax.errorbar( 0.001 * myd['mass'], myd['trig_eff'], yerr = myd['raw_trig_err'], fmt ='ko' )
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Trigger efficiency' )
plt.savefig( osp.join('output', folder, 'trig_eff.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.set_ylim( 1e-6, 1e-4 )
ax.grid( True)
ax.plot( 0.001 * sigd['mass'], sigd['ul_br'], 'k--', label = 'Expected sensitivity' )
ax.plot( 0.001 * sigd['mass'], sigd['dt_ul_br'], 'k-', label = 'Measured upper limit' )

ax.set_yscale('log')
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Limit on BR' )
lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, loc = 'upper left', prop={'size':20} )

plt.savefig( osp.join('output', folder, 'br.pdf' ), format = 'pdf', transparent = 'true' )

plt.cla()

sigd['pulls'] =  (sigd['dt_obs'] - sigd['bg']) / sigd['comb_sigma']

ax.plot( 0.001 * sigd['mass'] , (sigd['dt_obs'] - sigd['bg']) / sigd['comb_sigma'] )
ax.set_xlim( 0.27, 0.39 )
ax.grid( True)
plt.savefig( osp.join( 'output', folder, 'pulls.pdf' ), format = 'pdf', trasnparent = 'true' )

print( 'pulls mean: {0}, rms: {1}'.format(sigd['pulls'].mean(), sigd['pulls'].std() ) )

with open( osp.join('output/', folder, 'pulls.dat' ), 'w' ) as ofs:
    ofs.write(  sigd[[ 'mass','pulls']].to_string() )

plt.cla()


ax.set_xlim( 0.24, 0.4 )
ax.grid( True)
ax.plot(0.001 *sigd['mass'], (sigd['dt_ul_mu'] - sigd['ul_mu']) / sigd['comb_sigma'], 'k--' )

ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Local significance' )

sigd['localsig'] =  (sigd['dt_ul_mu'] - sigd['ul_mu']) / sigd['comb_sigma']
#print( sigd[ ['mass','localsig'] ]  )

plt.savefig( osp.join('output', folder, 'localsig.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.grid( True)
ax.plot(0.001 *sigd['mass'], ( sigd['ul_mu'] / ( sigd['bg'] - sigd['ul_mu']) ) * ( 1 - sigd['trig_eff'] ), 'k-+' )
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Signal / background' )

plt.savefig( osp.join('output', folder, 'sigrat.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.set_ylim( 5e-7, 8e-5 )
ax.grid( True)
ax.plot(0.001 *sigd['mass'], sigd['ul_u2'], 'k--' )
ax.fill_between(0.001 * sigd['mass'], sigd['low2_ul_u2'],  sigd['high2_ul_u2'], facecolor  = '#FCFF2B' )
ax.fill_between(0.001 * sigd['mass'], sigd['low1_ul_u2'],  sigd['high1_ul_u2'], facecolor  = '#27E50C' )
ax.plot(0.001 * sigd['mass'], sigd['dt_ul_u2'], 'k-+' )
ax.set_yscale('log')
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Limit on $|U_{\mu h}|^2$' )


hayano_color = '#884444'
e949_color = '#448844'
ax.plot( 0.001 * km2hayano['mass'], km2hayano['U2'], label = 'KEK (1982)',
                ls = '--', lw = 2, color = hayano_color,  mec = 'none' )

ax.plot( 0.001 * e949['mass'], 0.1 * e949['U2'], label = 'E949 (2015)',
                ls = '--', lw = 2, color = hayano_color,  mec = 'none' )

plt.savefig( osp.join('output', folder, 'u2.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

#--------------------------------------------------
#U2
#--------------------------------------------------

ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Limit on $|U_{\mu h}|^2$' )

ax.set_xlim( 0.20, 0.4 )
ax.set_ylim( 5e-10, 8e-4 )
ax.grid( True)
ax.plot( 0.001 * km2hayano['mass'], km2hayano['U2'],'b-', label = 'KEK (1982)' )
ax.plot( 0.001 * e949['mass'], 0.1 * e949['U2'], 'g',  label = 'E949 (2015)' )
expect, = ax.plot( 0.001 * sigd['mass'], sigd['ul_u2'], 'k-', label = 'Expected sensitivity' )
ses, = ax.plot( 0.001 * sigd['mass'], sigd['ses_u2'], 'k--', label = 'Single event sensitity' )
ax.set_yscale('log')

lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, ncol = 2, loc = 'upper left', prop={'size':16} )


plt.savefig( osp.join('output', folder, 'u2plain.pdf'), format = 'pdf', transparent = 'true' )

expect.remove()
ses.remove()

ax.plot(0.001 * sigd['mass'], sigd['dt_ul_u2'], 'k-', label = 'Measured upper limit' )
lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, ncol = 2, loc = 'upper left', prop={'size':16} )

plt.savefig( osp.join('output', folder, 'u2meas.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.set_ylim( 5e-7, 8e-5 )
ax.grid( True)
ax.plot(0.001 *sigd['mass'], sigd['ul_u2'], 'k--', label = 'Expected sensitivity' )
ax.set_yscale('log')

lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, loc = 'lower left', ncol = 2 )

plt.savefig( osp.join('output', folder, 'exp_u2.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.set_ylim( 0, 1e-5 )
ax.grid( True)
ax.plot(0.001 *myd['mass'], myd['dt_ll_u2'], 'k-' )
ax.plot(0.001 *myd['mass'], myd['dt_ul_u2'], 'k-' )
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Lower Limit on $|U_{\mu h}|^2$' )
plt.savefig( osp.join( 'output', folder,  'll_u2.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.set_xlim( 0.24, 0.4 )
ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'Background' )
ax.grid( True )
ax.errorbar(  0.001 *  myd['mass'] - 0.0005, myd['bg'], yerr = myd['bg_err'] , fmt = 's', mec = 'None', markersize = 4, label = 'systematic' )
ax.errorbar(  0.001 * myd['mass'] + 0.0005, myd['bg'], yerr = np.sqrt(myd['bg'] ) , fmt = 's', mec = 'None', markersize = 4, label = 'statistical' )

lines, labels = ax.get_legend_handles_labels()
leg = plt.legend( lines, labels, loc = 'lower left', ncol = 2 )

plt.savefig(  osp.join('output/', folder, 'bgerr.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.grid(True)
ax.plot( 0.001 * myd['mass'], myd['err_trig'] )
ax.plot( 0.001 * myd['mass'], myd['raw_trig_sqerr'] )

plt.savefig(  osp.join('output/', folder, 'trigcomp.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.grid(True)
ax.plot( 0.001 * myd['mass'], myd['err_trig'] / myd['raw_trig_sqerr'] )

plt.savefig(  osp.join('output/', folder, 'trigrat.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()

ax.grid( True)

ax.set_xlim( 0.25, 0.4 )
statplot, = ax.plot( 0.001 * myd['mass'], myd['bg'], label = 'statistical' )

err_sources = ['err_scat', 'err_trig', 'err_muv', 'err_flux', 'err_hscale', 'err_hval', 'err_k3pi', 'err_hshape', 'err_km3',]

err_names = ['DCH tails', 'trigger efficiency', 'MUV efficiency', 'kaon flux', 
'halo scale', 'halo statistical', 'halo $K_{3\pi}$ scale', 'halo model', 'km3 err']
ax.set_ylim( 0, 15000 )
polys = ax.stackplot(  0.001 * myd['mass'], [myd[x] for x in err_sources ], label = err_sources, lw = 0 )

legend_proxies = []
for poly in polys:
        legend_proxies.append(plt.Rectangle((0, 0), 1, 1, fc=poly.get_facecolor()[0], lw = 0))

legend_names = err_names

legend_proxies.append( statplot )
legend_names.append( 'statistical' )

ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'$\sigma^2$' )
leg = plt.legend( reversed(legend_proxies), reversed(err_names), frameon = True, loc = 'upper right', ncol = 2  )

par2 = ax.twin()
xlabels = [ 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15 ]
xvalues = np.sqrt( xlabels )
par2.set_xticks( xvalues  )
par2.set_xticklabels( [ '{0:.2f}'.format( x ) for x in xlabels  ] )

plt.savefig(  osp.join('output', folder, 'sqerr.pdf'), format = 'pdf', transparent = 'true' )

#######


plt.cla()

ax.grid( True)

ax.set_xlim( 0.24, 0.4 )
statplot, = ax.plot( 0.001 * myd['mass'], myd['bg'], label = 'statistical' )

err_sources = ['err_scat', 'raw_trig_sqerr', 'err_muv', 'err_flux', 'err_hscale', 'err_hval', 'err_hshape']
err_names = ['scattering', 'Trigger efficiency', 'MUV efficiency', 'kaon flux', 'halo scale', 'halo measurement', 'halo shape']
ax.set_ylim( 0, 10000 )
polys = ax.stackplot(  0.001 * myd['mass'], [myd[x] for x in err_sources ], label = err_sources )

legend_proxies = []
for poly in polys:
        legend_proxies.append(plt.Rectangle((0, 0), 1, 1, fc=poly.get_facecolor()[0]))

legend_names = err_names

legend_proxies.append( statplot )
legend_names.append( 'statistical' )

ax.set_xlabel( r'Heavy neutrino mass GeV/$c^2$' )
ax.set_ylabel( r'$\sigma^2$' )
leg = plt.legend( reversed(legend_proxies), reversed(err_names), frameon = True, loc = 'upper right' )

par2 = ax.twin()
xlabels = [ 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15 ]
xvalues = np.sqrt( xlabels )
par2.set_xticks( xvalues  )
par2.set_xticklabels( [ '{0:.2f}'.format( x ) for x in xlabels  ] )

plt.savefig(  osp.join('output', folder, 'sqerr_raw.pdf'), format = 'pdf', transparent = 'true' )

plt.cla()
