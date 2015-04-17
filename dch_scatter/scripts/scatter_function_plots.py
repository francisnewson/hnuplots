#!/usr/bin/env python
from scipy import integrate
from scipy.stats import rv_continuous
import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt

def make_gaussian( scale, sigma ):
    def fun(x):
        return scale * np.exp( - 0.5 * np.square( x / sigma) )
    return fun

def make_quadratic( scale ):
    def fun(x):
        return scale / np.square(x)
    return fun

def make_quadratic_kick( scale, peak ):
    peak_correction = 1.012
    def fun(x):
        return scale / np.square(x) * np.tanh(
                np.power( peak_correction * x / peak, 4 ) )
    return fun

def get_gaussian_gen(scale, sigma):
    my_gaus = make_gaussian( scale, sigma )

    class rv(rv_continuous ):
        def _pdf( self , x):
            return my_gaus( x )

    return rv( name= 'gaussian' )

def plot_things( 
        output_filename,
        gaus_scale, gaus_sigma, 
        quadratic_scale,
        quadratic_kick_scale, quadratic_kick_peak, **extras):

    g = make_gaussian( gaus_scale, gaus_sigma)
    q = make_quadratic( quadratic_scale)
    qk = make_quadratic_kick( quadratic_kick_scale, quadratic_kick_peak)


    fig = plt.figure( figsize = [8, 6] )
    fig.set_tight_layout(True)
    ax = fig.add_subplot( 111 )

    pts = np.linspace( - 10 * gaus_sigma, 40 * gaus_sigma, 1000 )

    ax.set_yscale( 'log' )
    ax.set_ylim( [ 1e-5*gaus_scale, 10*gaus_scale ] )

    ax.plot( pts, g(pts ), '-', label = 'Gaussian' )
    ax.plot( pts, q(pts ), '-', label = 'Quadratic tail' )
    ax.plot( pts, qk(pts ), '-', label = 'Quadratic kick' )
    ax.plot( pts, g(pts) + qk(pts ), '-', label = 'Corrected spectrum' )

    handles, labels = ax.get_legend_handles_labels()
    plt.legend( handles, labels , loc = 'upper right')
    plt.savefig( output_filename, format = 'pdf', transparent = True )

def integrate_things(
        gaus_scale, gaus_sigma, 
        quadratic_kick_scale, quadratic_kick_peak, **extras):
    g = make_gaussian( gaus_scale, gaus_sigma)
    qk = make_quadratic_kick( quadratic_kick_scale, quadratic_kick_peak)

    exp_int_g = np.sqrt( 2 * np.pi ) * gaus_sigma * gaus_scale / 2
    int_g = integrate.quad( g, 0, 5*gaus_sigma ) 
    print( " Expected Gaussian: {0}".format( int_g ) )
    print( " Computed Gaussian: {0}".format( exp_int_g ) )

    int_qk = integrate.quad( qk, 0, 5*gaus_sigma ) 
    print( "    Quadratic kick: {0}".format(  int_qk ) )

    print( "             ratio: {0}".format( int_qk[0] / int_g[0] ) )

def mc_test(
        gaus_scale, gaus_sigma, 
        quadratic_kick_scale, quadratic_kick_peak, **extras):

    fg = get_gaussian_gen( gaus_scale, gaus_sigma )
    print( type( fg ) )
    print( fg )
    print( fg.rvs( size = 10 ) )



#START
plot_info = dict(
output_filename = 'output/integral_plots.pdf',
gaus_scale = 5e4, gaus_sigma = 2e-4, 
quadratic_scale = 3e-5,
quadratic_kick_scale = 3e-5, quadratic_kick_peak = 2e-4)

print( plot_info )
plot_things( **plot_info )
integrate_things( **plot_info )

failed_plot_info = dict(
output_filename = 'output/integral_plots_old.pdf',
gaus_scale = 5e4, gaus_sigma = 2e-4, 
quadratic_scale = 3e-5,
quadratic_kick_scale = 3e-5, quadratic_kick_peak = 2e-3)
plot_things( **failed_plot_info )
integrate_things( **failed_plot_info )
