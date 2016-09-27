#!/usr/bin/env python
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import scipy.optimize as scopt
import pandas as pd
import math


pass_data = pd.read_csv( 'aux/cp_pass.dat', delim_whitespace = True )

#create canvas
fig,ax = plt.subplots(figsize = [5,5]  )

######

ax.plot( pass_data['npass'], pass_data['width'], 'k' )

ax.grid( 'on' )
ax.set_title ( r'Fixed $N_\textrm{total} = 1500$' )
ax.set_xlabel( r'$N_\textrm{pass}$' )
ax.set_ylabel( r'$\sigma_\eta$')

plt.tight_layout()
plt.savefig( 'output/clopper_pearsons_npass_width.pdf', format = 'pdf', transparent = 'true' );

plt.cla()

######

ax.plot( pass_data['npass'], pass_data['up']  , 'k' )
ax.plot( pass_data['npass'], pass_data['npass'] / 1500 , 'k' )
ax.plot( pass_data['npass'], pass_data['down']  , 'k' )

ax.grid( 'on' )
ax.set_title ( r'Fixed $N_\textrm{total} = 1500$' )
ax.set_xlabel( r'$N_\textrm{pass}$' )
ax.set_ylabel( r'$\eta$')

plt.tight_layout()
plt.savefig( 'output/clopper_pearsons_npass.pdf', format = 'pdf', transparent = 'true' );

plt.cla()

######

ax.plot( pass_data['npass'], pass_data['width'] / (pass_data['npass'] / 1500 )  , 'k' )

ax.grid( 'on' )
ax.set_title ( r'Fixed $N_\textrm{total} = 1500$' )
ax.set_xlabel( r'$N_\textrm{pass}$' )
ax.set_ylabel( r'relative error $\sigma_\eta\ /\ \eta$')
ax.set_ylim( [0,0.1] )
ax.set_xlim( [1000,1500] )

plt.tight_layout()
plt.savefig( 'output/clopper_pearsons_npass_rel.pdf', format = 'pdf', transparent = 'true' );

plt.cla()

######

total_data = pd.read_csv( 'aux/cp_total.dat', delim_whitespace = True )

ax.plot( total_data['ntotal'], total_data['width'], 'k' )

ax.grid( 'on' )
ax.set_title ( r'Fixed $\eta = 95$' )
ax.set_xlabel( r'$N_\textrm{total}$' )
ax.set_ylabel( r'$\sigma_\eta$')

plt.tight_layout()
plt.savefig( 'output/clopper_pearsons_ntotal.pdf', format = 'pdf', transparent = 'true' );

plt.cla()

######

ax.plot( total_data['ntotal'], total_data['width'] / 0.95  , 'k' )

ax.grid( 'on' )
ax.set_title ( r'Fixed $\eta = 95$' )
ax.set_xlabel( r'$N_\textrm{total}$' )
ax.set_ylabel( r'relative error $\sigma_\eta\ /\ \eta$')

plt.tight_layout()
plt.savefig( 'output/clopper_pearsons_ntotal_rel.pdf', format = 'pdf', transparent = 'true' );
