from scipy import integrate
import numpy as np
import math
import matplotlib.pyplot as plt

a = 1
def quartic_scattering( x ):
    r = 0.965
    return pow(a/r * 1/x, 4 ) * math.tanh( pow( x * r/a, 6) )

def custom_quartic_scattering( magnitude, peak ):
    xscale = 0.965
    p0 = magnitude
    p1 = xscale / peak

    def scattering_function(x):
        return p0*pow(  x, -4 ) * math.tanh( pow( p1 * x, 6 ) ) 

    return scattering_function

def custom_quadratic_scattering( magnitude, peak ):
    xscale = 1.021
    p0 = magnitude
    p1 = xscale / peak

    def scattering_function(x):
        return p0*pow( x, -2 ) * math.tanh( pow( p1 * x, 4 ) ) 

    return scattering_function

#for mag in ( 1, 2, 3):
#    for a in np.arange( 0.1, 1.0, 0.1 ):
#        print( mag, a, integrate.quad(
#            custom_quartic_scattering(mag, a),
#            0, 5 ) )

#sf = custom_quadratic_scattering( 3e-5 / ( 2e4 * math.sqrt( 2 * math.pi )*1.56e-4), 0.0005 )
sf = custom_quadratic_scattering( 1 , 0.0006 )

print ( integrate.quad( sf, 0, 0.006 ) )

#mag = 1
#ass = np.arange( 0.1, 1.0, 0.01 )
#ints = [ integrate.quad( custom_quartic_scattering( mag, a ), 0,5 ) for a in ass ]
#fig,ax = plt.subplots(figsize = [8,6]  )
#ax.plot( ass, ints )
#plt.show()
