import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import scipy.optimize as scopt
import math

mk = 0.493677
mk2 = mk**2

mmu = 0.1056583
mmu2 = mmu**2

pk = 74
ek = math.sqrt( pk**2 + mk2 )


def upper_mass( p ):
    return mk2 + mmu2 - 2 * ( ek * math.sqrt( mmu2 + pow( p, 2 )) - pk* p )

def lower_mass( p ):
    return mk2 + mmu2 - 2 * ( ek * math.sqrt( mmu2 + pow(p, 2)) + pk* p )

def theta( p, m ):
        return math.acos( 1 / ( pk * p ) * ( ek * math.sqrt( mmu2 + p**2 ) + 0.5 * ( m**2 - mk2 - mmu2 ) ) )

def mtheta( m ):
    def inner( p ):
        return theta( p, m )
    return inner

plt.rcParams.update({'figure.autolayout': True})

vupper_mass = np.vectorize( upper_mass )
vlower_mass = np.vectorize( lower_mass )

fm0 = mtheta(0)
vfm0 = np.vectorize( fm0 )

fm300 = mtheta(0.300)
vfm300 = np.vectorize( fm300 )

fm350 = mtheta(0.350)
vfm350 = np.vectorize( fm350 )


fm370 = mtheta(0.370)
vfm370 = np.vectorize( fm370 )

fm380 = mtheta(0.380)
vfm380 = np.vectorize( fm380 )

#momentum range
p = np.linspace( 5, 75, 750 )

#create canvas
fig,ax = plt.subplots(figsize = [8,6]  )

ax.plot( vupper_mass( p), p, color = 'black', lw = 2 )
ax.grid()
ax.set_xlim( -0.5, 0.3 )
plt.xlabel( r'$\mathrm{Reconstructed}$ $m^{2}_{\mathrm{miss}}$' )
plt.ylabel( r'$p_{\mathrm{measured}}$' )
plt.draw()
plt.savefig( 'output/m2_lim.pdf', format = 'pdf', 
        transparent = 'true' );

plt.close()

p = np.linspace( 5, 74, 740 )

fig,ax = plt.subplots(figsize = [8,6]  )

print ('Calculating' )


p0 = []
val0 = []

p300 = []
val300 = []

p350 = []
val350 = []

p370 = []
val370 = []

p380 = []
val380 = []

for ip in p:
    try:
        val0.append(vfm0(ip ))
        p0.append( ip ) 
    except ValueError:
        pass
    try:
        val300.append(vfm300(ip ))
        p300.append( ip ) 
    except ValueError:
        pass
    try:
        val350.append(vfm350(ip ))
        p350.append( ip ) 
    except ValueError:
        pass
    try:
        val370.append(vfm370(ip ))
        p370.append( ip ) 
    except ValueError:
        pass
    try:
        val380.append(vfm380(ip ))
        p380.append( ip ) 
    except ValueError:
        pass

print ('Plotting' )

ax.plot( p0, val0, color = 'black', lw = 1, ls = '-', label = '  0 MeV' )
ax.plot( p300, val300, color = 'black', lw = 2, ls = '-', label = '300 MeV' )
ax.plot( p350, val350, color = 'black', lw = 2, ls = '--', label = '350 MeV' )
ax.plot( p370, val370, color = 'black', lw = 2, ls = '-.', label = '370 MeV' )
ax.plot( p380, val380, color = 'black', lw = 2, ls = ':', label = '380 MeV' )

plt.xlabel( r'$\mathrm{Muon}$ $\mathrm{momentum}$ $\mathrm{GeV/c}$' )
plt.ylabel( r'$\mathrm{Muon}$-$\mathrm{Kaon}$ $\mathrm{angle}$ ${\theta}$' )
ax.grid()

lines, labels = ax.get_legend_handles_labels()
ax.legend( lines, labels, loc = 'upper right' )
plt.draw()

plt.draw()
plt.savefig( 'output/p_t.pdf', format = 'pdf', 
        transparent = 'true' );
