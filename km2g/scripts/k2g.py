import numpy as np
import scipy.integrate

mMu = 0.1056583715
mE  = 0.000511
mK = 0.493677

rm = ( mMu / mK )**2
re = ( mE / mK )**2

F_K_old = 0.11346
F_K_new = 0.1561

abar = 0.00116140973
g_km2 = 0.6355

######

def A_SD( r, F_K ):
    return g_km2 * abar / 4.0/ r/ ( 1 - r )**2  * ( mK / F_K )**2

def A_INT( r , F_K ):
    return 4 * r * F_K / mK * A_SD( r, F_K )

######

def f_SDP( x , y, r ):
    return ( x + y - 1 - r ) * ( ( x + y - 1 )* ( 1 - x ) - r )

def f_SDM( x , y, r ):
    return ( 1 - y + r ) * ( ( 1 - x ) * ( 1 - y ) + r ) 

def f_INTP( x , y, r  ):
    b1 =  ( 1 - y + r )/ ( x * ( x + y - 1 - r ))
    b2 =  ( 1 - x ) * ( 1 - x - y )  + r 
    res = b1 * b2 
    return b1  * b2 

def f_INTM( x, y, r ):
    b1 =  ( 1 - y + r )/ ( x * ( x + y - 1 - r ))
    b2 = ( x**2 - ( 1 - x ) * ( 1 - x - y ) - r )
    return b1 * b2

######

def p_sdm( x , y, r, F_K,  F_V, F_A ):
    return A_SD( r, F_K)  *  ( F_V - F_A )**2 * f_SDM( x, y, r ) 

def p_sdp( x , y, r, F_K,  F_V, F_A ):
    return A_SD( r, F_K ) *  ( F_V + F_A )**2 * f_SDP( x, y, r ) 

def p_intm( x , y, r, F_K,  F_V, F_A ):
    return - A_INT(r, F_K) *  ( F_V - F_A ) * f_INTM( x, y, r ) 

def p_intp( x , y, r, F_K,  F_V, F_A ):
    return  - A_INT(r, F_K) *  ( F_V + F_A ) * f_INTP( x, y, r ) 

######

def g_integrate( f, r ):
    return scipy.integrate.dblquad( f,
            2 * np.sqrt( r ), 1 + r ,
            lambda y: 1 - 0.5 * ( y + np.sqrt( y**2 - 4 * r )) ,
            lambda y: 1 - 0.5 * ( y - np.sqrt( y**2 - 4 * r )),
            epsabs = 1e-9, epsrel = 1e-9 )
######

def g_integrate_raw( f, r ):
    ipf = lambda x,y : f( x,y,r)
    return g_integrate( ipf, r )

def g_integrate_cp4( r, F_K, F_V, F_A, f ):
    ipf = lambda x,y : f( x, y, r, F_K, F_V, F_A )
    return g_integrate( ipf, r )

def g_integrate_cp6( r, F_K, F_V0, F_VX, F_A0, F_AX, f):
    ipf = lambda x,y : f( x, y, r, F_K,
            F_V0 + F_VX * ( 1.0 - x ) * mK**2, 
            F_A0 + F_AX * ( 1.0 - x ) * mK**2)
    return g_integrate( ipf, r )

def g_integrate_kloe( r, F_K,  f ):
    ipf = lambda x,y : f( x, y, r, F_K,
            0.0885 * ( 1.0 + 0.38 * ( 1.0 - x )), 0.0365)
    return g_integrate( ipf, r )

######

def range( x , y, r ):
    if x < 0.00:
        return False

    if x > 1 - r:
        return False

    if ( 1 - x + r / ( 1 - x ) ) > y :
        return False

    if ( 1 + r ) < y :
        return False

    return True;

def mask_range( x, y, r):
    return not range( x, y, r )


######

def g_plot( ax, f, r ):

    nx = 1000
    ny = 1000

    x = np.linspace ( 0, 1, nx )
    y = np.linspace( 0.2, 1.2 , ny )

    X, Y =  np.meshgrid( x, y, )


    def myf( x,y ):
        if mask_range( x, y, r ):
            return 0.0
        else:
            return f( x, y, r )

    mask = lambda x,y : mask_range( x, y, r )

    mrange = np.vectorize( mask );

    vf = np.vectorize( myf )
    Z = vf( X, Y )
    Zm = np.ma.masked_where( mrange( X, Y ), Z) 
    ax.grid( True )
    ax.set_xlabel( 'y' )
    ax.set_ylabel( 'x' )
    plotted = ax.pcolor( Y, X, Zm, rasterized = True )
    ax.grid( True )
    return plotted
