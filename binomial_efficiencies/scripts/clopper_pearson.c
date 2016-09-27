#include "TEfficiency.h"
#include <iomanip>


double cp_up( int total, int pass, double level )
{
    return TEfficiency::ClopperPearson( total, pass, level, kTRUE );
}

double cp_dn( int total, int pass, double level )
{
    return TEfficiency::ClopperPearson( total, pass, level, kFALSE );
}

void print_cp()
{
    std::ofstream fpass ( "aux/cp_pass.dat" );
    std::ostream* os = &fpass;
    double cl = 0.9;
    int ntotal = 1500;

    (*os)
        << std::setw(20) << "npass"
        << std::setw(20) << "up" << std::setw(20) << "down"
        << std::setw(20) << "width" << std::endl;

    for ( int npass = 0 ; npass != 1520 ; npass+=20 )
    {
        (*os)
            << std::setw(20) << npass 
            << std::setw(20)  << cp_dn( ntotal, npass, cl) 
            << std::setw(20)  << cp_up( ntotal, npass, cl) 
            << std::setw(20)  
            << cp_up( ntotal, npass, cl)  - cp_dn( ntotal, npass, cl )
            << std::endl;
    }

    (*os) << std::endl;

    std::ofstream ftotal ( "aux/cp_total.dat" );
    os = &ftotal;

    (*os)
        << std::setw(20) << "ntotal"
        << std::setw(20) << "up" << std::setw(20) << "down"
        << std::setw(20) << "width" << std::endl;

    for( int ntotal = 1000; ntotal != 2020 ; ntotal+= 20 )
    {
        int npass = 95 * ntotal / 100;

        (*os )
            << std::setw(20) << ntotal 
            << std::setw(20)  << cp_dn( ntotal, npass, cl) 
            << std::setw(20)  << cp_up( ntotal, npass, cl) 
            << std::setw(20)  
            << cp_up( ntotal, npass, cl)  - cp_dn( ntotal, npass, cl )
            << std::endl;


    }
}

void grid_cp()
{
    std::ofstream ofs ( "aux/cp_grid.dat" );
    std::ofstream oft ( "aux/cp_thresh.dat" );
    double cl = 0.9;

    oft << setw(20) << "ntotal"
        << setw(20) << "eff_thresh"
        << "\n";

    ofs
        << std::setw(20) << "ntotal"
        << std::setw(20) << "eff"
        << std::setw(20) << "up"
        << std::setw(20) << "down"
        << std::setw(20) << "width"
        << std::setw(20) << "rat"
        << "\n";

    for ( int bg = 50 ; bg != 2100 ; bg += 50 )
    {
        std::cerr << bg << " / " << 2000 << std::endl;
        bool found_thresh = false;
        double threshold = 100;

        for ( int eff = 50 ; eff != 101 ; ++ eff )
        {
            double up = cp_up( bg,  eff * bg  / 100, 0.9 );
            double dn = cp_dn( bg,  eff * bg  / 100, 0.9 );
            double width = up - dn;
            //double rat =  0.5 * sqrt( bg * width * width / (0.01 * eff ) / (0.01 * eff ) + 1 );
            double rat = 2 * 1 / sqrt(  eff * eff * 0.0001 * bg * width );

            if ( ! found_thresh && rat < 1.0 )
            {
                oft 
                    << std::setw(20) << bg
                    << std::setw(20) << 0.01 * eff
                    << "\n";
                found_thresh = true;
            }

            ofs
                << std::setw(20) << bg
                << std::setw(20) << 0.01 * eff
                << std::setw(20) << up
                << std::setw(20) << dn
                << std::setw(20) << width
                << std::setw(20) << rat
                << "\n";
        }
    }
}


void clopper_pearson()
{
    std::cout << "Doing print_cp() " << std::endl;
    //print_cp();
    grid_cp();
}
