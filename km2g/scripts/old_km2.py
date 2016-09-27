#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import dblquad
from scipy.integrate import nquad


mMu = 0.1056583715
mE  = 0.000511
mK = 0.493677

r = ( mMu / mK )**2
#r = ( mE / mK )**2

g_km2 = 0.6355
#g_km2 = 1.0

abar = 0.00116140973

F_K = 0.1561
#F_K = 0.11346

A_SD = g_km2 * abar  / 4 * 1 / r / (1 - r )**2 * ( mK / F_K )**2
A_IB = g_km2 * abar * 1 / ( 1 - r )**2
A_INT = g_km2 * abar * 1 / ( 1 - r ) **2 * mK / F_K
A_INT = 4 * r * F_K / mK * A_SD

def range( x , y ):
    if x < 0.00:
        return False

    if x > 1 - r:
        return False

    if ( 1 - x + r / ( 1 - x ) ) > y :
        return False

    if ( 1 + r ) < y :
        return False

    return True;

def mask_range( x, y):
    return not range( x, y )

mrange = np.vectorize( mask_range );

def f_IB( x, y, ):
    b1 = ( 1 - y +  r ) / ( x**2 * ( x + y - 1 - r) )
    b2 = ( x**2 + 2 * ( 1 - x ) * ( 1 - r ) - ( 2 * x * r * ( 1 - r ) ) / ( x + y - 1 - r ) )
    return b1 * b2

vf_IB = np.vectorize( f_IB, otypes = [np.float] )

def f_SDP( x , y ):
    return ( x + y - 1 - r ) * ( ( x + y - 1 )* ( 1 - x ) - r )

vf_SDP = np.vectorize( f_SDP, otypes = [np.float] )

def f_SDM( x , y ):
    return ( 1 - y + r ) * ( ( 1 - x ) * ( 1 - y ) + r ) 

vf_SDM = np.vectorize( f_SDM, otypes = [np.float] )

def f_INTP( x ,y  ):
    b1 =  ( 1 - y + r )/ ( x * ( x + y - 1 - r ))
    b2 =  ( 1 - x ) * ( 1 - x - y )  + r 
    res = b1 * b2 
    return b1  * b2 

vf_INTP = np.vectorize( f_INTP, otypes = [np.float] )

def f_INTM( x, y ):
    b1 =  ( 1 - y + r )/ ( x * ( x + y - 1 - r ))
    b2 = ( x**2 - ( 1 - x ) * ( 1 - x - y ) - r )
    return b1 * b2

vf_INTM = np.vectorize( f_INTM, otypes = [np.float] )

def p_ip( x, y ):
    return  A_IB * f_IB( x, y, )

def p_sdm( x, y, F_V, F_A ):
    return A_SD * (  ( F_V - F_A)**2 * f_SDM( x, y ) ) 

def p_sdp( x, y, F_V, F_A ):
    return A_SD * ( ( F_V + F_A )**2 * f_SDP( x, y ) ) 

def p_intm( x, y , F_V, F_A ):
    return - A_INT * ( ( F_V - F_A) * f_INTM( x, y ) ) 

def p_intp( x, y , F_V, F_A ):
    return - A_INT * ( ( F_V + F_A ) * f_INTP( x, y )) 

def p( x, y, ):
    return p_ip( x, y, ) + p_sd( x, y ) + p_int( x, y )

def easy( y, x ):
    return (x + 2*y)


def do_integral_cp4(  F_V, F_A, f ):
    ipf = lambda x,y : f( x, y, F_V, F_A )
    result_b = dblquad( ipf, 2 * np.sqrt( r ), 1 + r , 
            lambda y: 1 - 0.5 * ( y + np.sqrt( y**2 - 4 * r )) ,
            lambda y: 1 - 0.5 * ( y - np.sqrt( y**2 - 4 * r )),
            epsabs = 1e-10, epsrel = 1e-10
            )
    return [result_b]


def do_integral_cp6( F_V0, F_VX,  F_A0, F_AX, f ):
    ipf = lambda x,y : f( x, y, F_V0  + F_VX * ( 1.0 - x ) * mK**2, F_A0  + F_AX * ( 1.0 - x ) * mK**2 )
    result_b = dblquad( ipf, 2 * np.sqrt( r ), 1 + r , 
            lambda y: 1 - 0.5 * ( y + np.sqrt( y**2 - 4 * r )) ,
            lambda y: 1 - 0.5 * ( y - np.sqrt( y**2 - 4 * r )),
            epsabs = 1e-10, epsrel = 1e-10
            )
    return [result_b]

def do_integral_kloe( f ):
    ipf = lambda x,y : f( x, y, 0.0885 * ( 1.0 + 0.38 * ( 1.0 - x )), 0.0365)
    result_b = dblquad( ipf, 2 * np.sqrt( r ), 1 + r , 
            lambda y: 1 - 0.5 * ( y + np.sqrt( y**2 - 4 * r )) ,
            lambda y: 1 - 0.5 * ( y - np.sqrt( y**2 - 4 * r )),
            epsabs = 1e-10, epsrel = 1e-10
            )
    return [result_b]


def plain_integral( f ):
    result = dblquad( f, 2 * np.sqrt( r ), 1 + r , 
            lambda y: 1 - 0.5 * ( y + np.sqrt( y**2 - 4 * r )) ,
            lambda y: 1 - 0.5 * ( y - np.sqrt( y**2 - 4 * r )),
            epsabs = 1e-10, epsrel = 1e-10
            )
    return result

def do_plain_integrals():
    F_VpA = -0.137
    F_VmA = -0.052 

    F_V = 0.5 * ( F_VpA + F_VmA )
    F_A = 0.5 * ( F_VpA - F_VmA )

    total_sdm = plain_integral( f_SDM )
    print( '{0:5}: {2:.3e} ± {3:.3e} rat {1:.3e}'.format( "SDM", total_sdm[0] / 1.18e-2, *total_sdm ) )
    br =  A_SD * ( F_V - F_A )**2 * total_sdm[0]
    print( '  BR : {0:.3e} rel: {1:.3e} rat {2:.2f}'.format( br, br / g_km2, br/g_km2 / 2.11e-6 ) )

    total_sdp = plain_integral( f_SDP ) 
    print( '{0:5}: {2:.3e} ± {3:.3e} rat {1:.3e}'.format( "SDM", total_sdp[0] / 1.18e-2, *total_sdp ) )
    br =  A_SD * ( F_V + F_A )**2 * total_sdp[0]
    print( '  BR : {0:.3e} rel: {1:.3e} rat {2:.2f}'.format( br, br / g_km2, br/g_km2 / 1.46e-5 ) )

    print( 4 * r * F_K / mK )
    total_intm = tuple( ( 4 * r * F_K / mK  * x) for x in  plain_integral( f_INTM ))
    print( '{0:5}: {2:.3e} ± {3:.3e} rat {1:.2f}'.format( "INTM", total_intm[0] / 1.23e-2, *total_intm ) )
    br =  A_SD * ( F_V - F_A ) * total_intm[0]
    print( '  BR : {0:.3e} '.format( br ) )

    total_intp = tuple( (4 * r * F_K / mK  * x) for x in  plain_integral( f_INTP ))
    print( '{0:5}: {2:.3e} ± {3:.3e} rat {1:.2f}'.format( "INTP", total_intp[0] / -1.78e-3, *total_intp ) )
    br =  A_SD * ( F_V + F_A ) * total_intp[0]
    print( '  BR : {0:.3e} '.format( br ) )

def print_results( name, res,comp = None ):
    for r in res:
        if comp:
            print( '{0}: {1:.3e} ± {2:.3e} rel: {3:.3e} comp: {4:.3e}'.format(
                name, r[0], r[1], r[0]/g_km2, r[0]/g_km2/comp ) )
        else:
            print( '{0}: {1:.3e} ± {2:.3e} rel: {3:.3e}'.format( name, r[0], r[1], r[0]/g_km2 ) )

def do_integration():
    F_VpA = 0.137
    F_VmA = 0.052 

    F_V = 0.5 * ( F_VpA + F_VmA )
    F_A = 0.5 * ( F_VpA - F_VmA )

    print( "A_SD: {0:e}".format( A_SD ) )
    print( 'r: {0:e}'.format( r  ) )
    print( "F_V: {0:e}, F_A {1:e}".format( F_V, F_A ) )

    res_sdm = do_integral_cp4( F_V, F_A, p_sdm)
    print_results( " SDM", res_sdm, 2.11e-6  )

    res_sdp = do_integral_cp4( F_V, F_A, p_sdp)
    print_results( " SDP", res_sdp , 1.46e-5 )

    res_intm = do_integral_cp4( F_V, F_A, p_intm )
    print_results( "INTM", res_intm )

    res_intp = do_integral_cp4( F_V, F_A, p_intp )
    print_results( "INTP", res_intp )

    ###
    print( "" )

    F_V0 =  0.082
    F_VX =  0.138775500

    F_A0 =  0.034
    F_AX = 0.003673469

    res6_sdm = do_integral_cp6( F_V0, F_VX, F_A0, F_AX, p_sdm)
    print_results( " SDM(6)", res6_sdm, 2.93e-6 )

    res6_sdp = do_integral_cp6( F_V0, F_VX, F_A0, F_AX, p_sdp)
    print_results( " SDP(6)", res6_sdp, 1.29e-5  )

    res6_intm = do_integral_cp6( F_V0, F_VX, F_A0, F_AX, p_intm )
    print_results( "INTM(6)", res6_intm )

    res6_intp = do_integral_cp6(F_V0, F_VX, F_A0, F_AX, p_intp )
    print_results( "INTP(6)", res6_intp )

    ###
    print( "" )

    res_kloe_sdm = do_integral_kloe(  p_sdm)
    print_results( " SDM(kloe)", res_kloe_sdm, 2.93e-6 )

    res_kloe_sdp = do_integral_kloe(p_sdp)
    print_results( " SDP(kloe)", res_kloe_sdp, 1.29e-5  )

    res_kloe_intm = do_integral_kloe( p_intm )
    print_results( "INTM(kloe)", res_kloe_intm )

    res_kloe_intp = do_integral_kloe( p_intp )
    print_results( "INTP(kloe)", res_kloe_intp )


def do_plots():
    nx = 1000
    ny = 1000

    x = np.linspace( 0, 1, nx )
    y = np.linspace( 0.2, 1.2, ny )

    X, Y = np.meshgrid( x, y, )


    #intialize
    fig = plt.figure( figsize = [8,6] )
    ax = fig.add_subplot(111)

    print( "Plotting INTP" )
    Z = vf_INTP( X, Y )
    Zm = np.ma.masked_where(  mrange( X, Y ), Z )
    plotted = ax.pcolor( Y, X, Zm, rasterized = True )
    cbar = plt.colorbar( plotted )
    fig.savefig( 'output/intp.pdf', format = 'pdf' )
    cbar.remove()

    plt.cla();

    print( "Plotting INTM" )
    Z = vf_INTM( X, Y )
    Zm = np.ma.masked_where(  mrange( X, Y ), Z )
    plotted = ax.pcolormesh( Y, X, Zm, rasterized = True )
    cbar = plt.colorbar( plotted )
    fig.savefig( 'output/intm.pdf', format = 'pdf' )
    cbar.remove()

    plt.cla();

    print( "Plotting SDM" )
    Z = vf_SDM( X, Y )
    Zm = np.ma.masked_where(  mrange( X, Y ), Z )
    plotted = ax.pcolormesh( Y, X, Zm, rasterized = True, vmin = 0 )
    cbar = plt.colorbar( plotted )
    fig.savefig( 'output/sdm.pdf', format = 'pdf' )
    cbar.remove()

    plt.cla();

    print( "Plotting SDP" )
    Z = vf_SDP( X, Y )
    Zm = np.ma.masked_where(  mrange( X, Y ), Z )
    plotted = ax.pcolormesh( Y, X, Zm, rasterized = True, vmin = 0 )
    cbar = plt.colorbar( plotted )
    fig.savefig( 'output/sdp.pdf', format = 'pdf' )
    cbar.remove()

    plt.cla();

    print( "Plotting IB" )
    Z = vf_IB( X, Y )
    Zm = np.ma.masked_where(  mrange( X, Y ), Z )
    plotted = ax.pcolormesh( Y, X, Zm, rasterized = True, vmin = 0 )
    cbar = plt.colorbar( plotted )
    fig.savefig( 'output/ib.pdf', format = 'pdf' )
    cbar.remove()


#do_plots()
do_integration()
print( "" )
do_plain_integrals()
