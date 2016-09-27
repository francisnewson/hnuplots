#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import sys

pwr = np.power

#CONTANTS

#universal
Gf  = 1.16637e-5 #GeV^-2
Gf2 = np.power( Gf, 2 )
hbar = 6.582e-25

#structure
f_pi = 130.0 * 0.001 #GeV ( same for +- and 0, by isospin)
f_pi2 = np.power( f_pi, 2 )

#mass
mpi0 = 134.97666 * 0.001 #GeV
mpi02 = pwr( mpi0, 2 )

mpip = 139.57018 * 0.001 #GeV
mpip2 = pwr( mpip, 2 )

me = 0.510998910 * 0.001 #GeV
me2 = pwr( me, 2)

mmu = 105.6583715 * 0.001 #GeV
mmu2 = pwr( mmu, 2 )

meta = 547.862 #GeV

#ckm
Vud = 0.97427
Vus = 0.22534
Vub = 0.00351
Vcd = 0.22520
Vcs = 0.93744
Vcb = 0.0412
Vtd = 0.00867
Vts = 0.0404
Vtb = 0.999146

#Weinberg
stw2 = 0.23120

C1 = 0.25 * ( 1 - 4 * stw2  + 8 * pwr( stw2, 2 ) )
C2 = 0.5  * stw2 * ( 2 * stw2 - 1 )
C3 = 0.25 * ( 1 + 4 * stw2 + 8 * pwr( stw2, 2 ) )
C4 = 0.5 * stw2 * ( 2 * stw2 + 1 )

#TWO BODY DECAYS
def w_H_nu( mh, fh2, u2, mn ): #should return width in GeV
    return np.choose( mn > mh, [0.0, 
        u2 / ( 32 * np.pi ) * Gf2 * fh2 * pwr(mn,3 ) * pwr( 1 - pwr(mh, 2 ) / pwr(mn, 2 ), 2 ) ] )

def w_h_l( mh, ml, fh2, Vh, u2, mn ):
   return np.choose( mn > mh + ml, [ 0.0,
   u2 / (16 * np.pi ) * Gf2 * pwr(Vh,2) * fh2 * pwr(mn,3 ) * ( pwr( 1 - pwr(ml, 2 ) / pwr(mn, 2 ), 2 )
            - pwr(mh, 2) / pwr(mn, 2 ) * ( 1 + pwr( ml , 2 ) / pwr(mn, 2 ) ) ) * np.sqrt(
                    (1 - pwr( mh - ml, 2) / pwr(mn, 2)) * ( 1 - pwr( mh + ml, 2 ) /pwr(mn, 2 ) )  ) ] )

#THREE BODY DECAYS
def w_nununu( u2, mn ):
    return Gf2 * pwr(mn, 5 ) / ( 192 * pwr(np.pi, 3 ) ) * ( 3 * u2 ) 

def w_lknu( ml, mk, u2, mn ):
    x = np.maximum( ml, mk ) / mn
    return Gf2 * pwr( mn, 5 ) / (192 * pwr(np.pi, 3)) * u2 * (
            1 - 8 * pwr(x, 2 ) + 8 * pwr(x, 6 ) - pwr(x, 8) - 12 * pwr(x, 4 )* np.log( pwr(x, 2 ) ))

def w_llnu(C_odd, C_even,  ml, u2, mn):
    x = ml / mn

    Ltop = np.choose( x < 1e-2 , [ 
            np.log( (1 - 3 * pwr(x, 2) - (1 - pwr(x,2) ) * np.sqrt( 1 - 4 * pwr(x, 2 ) ) ) ),
            np.log( 2 * pwr( x , 6 ) ) ] )

    Lbottom = np.log( pwr(x, 2 ) * ( 1 + np.sqrt( 1 - 4 * pwr( x, 2 ) ) )  )

    L = Ltop - Lbottom 

    #print( 'top: ', Ltop )
    #print( 'bottom: ', Lbottom )
    #print( 'L: ', L )

    first_bracket =  ( (1 - 14 * pwr(x,2) - 2*pwr(x,4) - 12*pwr(x,6) ) * np.sqrt( 1 - 4 * pwr(x,2)) 
        + 12 * pwr(x, 4) * ( pwr(x, 4) - 1 ) * L )

    second_bracket = ( 
            pwr(x, 2 )* ( 2 + 10 * pwr(x, 2 ) - 12 * pwr(x, 4 ) ) * np.sqrt( 1 - 4 * pwr(x, 2 ) )
        + 6 * pwr(x, 4 ) * ( 1 - 2 * pwr(x, 2 ) + 2 * pwr( x, 4) * L ) ) 

    #print( 'first: ', first_bracket )
    #print( 'C_odd: ', C_odd )
    #print( 'second: ', second_bracket )
    #print( 'C_even: ', C_even )

    return np.choose( mn > (2 * ml), [ 0.0, 
        Gf2 * pwr( mn, 5 ) / (192 * pwr(np.pi, 3)) * u2 * ( 
            C_odd * first_bracket + 4 * C_even *  second_bracket)  ] ) 

hnu_masses = np.linspace( 0.01, 0.5, 499 )
test_u2 = 1e-5

print(stw2,  C1, C2, C3, C4 )
print( 'muons' )
print ( w_llnu( C1, C2, mmu, test_u2, 0.3 ) )
print ( w_llnu( C3, C4, mmu, test_u2, 0.3 ) )
#print( 'electrons' )
#print ( w_llnu( C1, C2, me, test_u2, 0.3 ) )
#print ( w_llnu( C3, C4, me, test_u2, 0.3 ) )

np_w_pi0_nu = 3 * w_H_nu( mpi0, f_pi2, test_u2, hnu_masses )
np_w_pip_e = w_h_l( mpip, me, f_pi2, Vud, test_u2, hnu_masses )
np_w_pip_mu = w_h_l( mpip, mmu, f_pi2, Vud, test_u2, hnu_masses )
np_w_nununu = w_nununu( test_u2, hnu_masses )

np_w_nuemu = 2 * w_lknu( me, mmu, test_u2, hnu_masses )
np_w_nue_ee = w_llnu( C3, C4, me, test_u2, hnu_masses )
np_w_nudiff_ee = 2 * w_llnu( C1, C2, me, test_u2, hnu_masses )
np_w_numu_mumu = w_llnu( C3, C4, mmu, test_u2, hnu_masses )
np_w_nudiff_mumu = 2 * w_llnu( C1, C2, mmu, test_u2, hnu_masses )



total = (np_w_pi0_nu + np_w_pip_e + np_w_pip_mu + np_w_nununu + 
        np_w_nuemu + np_w_nue_ee + np_w_nudiff_ee + np_w_numu_mumu + np_w_nudiff_mumu )

lifetime = hbar / ( 2 * total )

fig,ax = plt.subplots(figsize = [8,6]  )
ax.set_yscale('log')
ax.grid( True )

ax.plot( hnu_masses, total,  'k-', lw = 2, label = r'$\mathrm{Total}$' )

line,  = ax.plot( hnu_masses, np_w_pi0_nu, 'k-', lw = 2, label = r'$\pi^0 \nu_{\mu, \nu, \tau}$' )
line.set_dashes( [8, 4, 2, 4, 2, 4] )

line,  = ax.plot( hnu_masses, np_w_pip_e,  'k-', lw = 2, label = r'$\pi^+ e$' )
line.set_dashes( [8, 4] )

line,  = ax.plot( hnu_masses, np_w_pip_mu, 'k-', lw = 2, label = r'$\pi^+ \mu$' )
line.set_dashes( [2,2] )

line,  = ax.plot( hnu_masses, np_w_nununu, 'k-', lw = 2, label = r'$\nu \nu \nu$' )
line.set_dashes( [8,4, 8, 4, 2, 4] )


ax.plot( hnu_masses, np_w_nuemu,       '-', color = '#66c2a5',  label = r'$\nu e \mu$' )
ax.plot( hnu_masses, np_w_nue_ee,      '-', color = '#fc8d62',  label = r'$\nu_e e e$' )
ax.plot( hnu_masses, np_w_nudiff_ee,   '-', color = '#8da0cb',  label = r'$\nu_{l \neq e} e e$' )
ax.plot( hnu_masses, np_w_numu_mumu,   '-', color = '#e78ac3',  label = r'$\nu_\mu \mu \mu$' )
ax.plot( hnu_masses, np_w_nudiff_mumu, '-', color = '#a6d854',  label = r'$\nu_{l \neq \mu} \mu \mu$' )

ax.set_ylim( 1e-24, 1e-17 )
ax.set_xlim( 0.1, 0.5 )
ax.set_xlabel( r'Neutrino mass ($\unit[]{GeV/c^2}$)' )
ax.set_ylabel( r'Partial width ($\unit[]{GeV}$)' )


lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels, loc = 'upper left', ncol = 2, handlelength = 5 )

plt.savefig( 'output/widths.pdf', format = 'pdf', transparent = 'true' )

ax.cla()

print( 'Done widths.pdf' )


ax.set_yscale('log')
ax.grid( True )
ax.set_ylim( 1e-6, 1e-1 )
ax.set_xlim( 0.1, 0.5 )
ax.set_xlabel( r'Neutrino mass ($\unit[]{GeV/c^2}$)' )
ax.set_ylabel( r'Lifetime (s)' )

ax.plot( hnu_masses, lifetime, '-k' )
plt.savefig( 'output/lifetime.pdf',  format = 'pdf', transparent = 'true' )

print( 'Done lifetime.pdf' )
