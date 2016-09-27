#!/usr/bin/env python
import glob
import sys
import os.path as osp

o = sys.stdout

def start():
    o.write( r'\begin{figure}[h!]' + '\n' )
    o.write( r'\centering' + '\n' )
    o.write( r'\begin{tabular}{ccc}' + '\n' )

def stop():
    o.write( '\n' )
    o.write( r'\end{tabular}' + '\n' )
    o.write( r'\end{figure}' + '\n' )
    o.write( r'\clearpage' + '\n' )

def title( name ):
    o.write( r'\section{{{0}}}'.format( name ) + '\n' )

def plot( folder, plots ):
    start()
    for plot in plots:
        o.write( r'\includegraphics[width=0.25\textwidth]{{{0}}}&'.format( osp.join( folder, plot ) ) + '\n' )
        o.write( r'\includegraphics[width=0.25\textwidth]{{{0}}}&'.format( osp.join(folder, plot + '_rat_fit' ) )  + '\n') 
        o.write( r'\includegraphics[width=0.25\textwidth]{{{0}}}\\'.format( osp.join(folder, plot + '_rat_fit_opt' ) )  + '\n') 
    stop()
    
o.write( r'''\documentclass{article}
\usepackage{graphicx}
\graphicspath{{/Users/francisnewson/Documents/Birmingham/na62/note/working/halo_check/}}
\usepackage[a4paper,margin=0.2in]{geometry}
\begin{document}
''' )


plots = [ 'h_cda', 'h_m2m_kmu', 'h_p', 'h_t', 'h_z' ]

if False:
    for t in [ 'full', 'neg', 'pos' ]:
        folder = 'output/2015-09-03pm/{0}_merge/all/'.format( t )
        title( 'Upper + lower : {0}'.format( t ) )
        plot( folder, plots )

        folder = 'output/2015-09-03pm/{0}_merge/upper/'.format( t )
        title( 'Upper : {0}'.format( t ) )
        plot( folder, plots )

        folder = 'output/2015-09-03pm/{0}_merge/lower/'.format( t)
        title( 'Lower : {0}'.format( t ) )
        plot( folder, plots )

version = '2015-09-05am'
version = '2015-09-12'

if True:
    for reg in [ "pos_check_upper", "neg_check_upper", "both_check_upper", 
            "pos_check_lower", "neg_check_lower", "both_check_lower", 
            "pos_check_full", "neg_check_full" ,"both_check_full" ]:
        folder = 'output/{0}/{1}'.format(version, reg )
        title( reg.replace( '_', ' ') )
        plot( folder, plots )

o.write( r'\end{document}' + '\n' )
