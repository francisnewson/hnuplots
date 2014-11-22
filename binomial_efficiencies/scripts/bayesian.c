#include "TEfficiency.h"
#include <iomanip>

double up( double pass)
{
    return TEfficiency::Bayesian( 1000, pass ,0.68, 1, 1, true);
}

double down( double pass)
{
    return TEfficiency::Bayesian( 1000, pass ,0.68, 1, 1, false);
}

void bayesian()
{
    std::ofstream fout( "aux/bayes_n1000.dat");
    fout << std::setw(20) << "n" << std::setw(20) << "up" << std::setw(20) << "down" << std::setw(20) << "width" << std::endl;
    for ( int n = 0 ; n != 1001; ++n )
    {
        fout << std::setw(20) << n 
            << std::setw(20) << up( n) << std::setw(20) << down(n) 
            << std::setw(20) << up(n) - down(n) << std::endl;
    }
}

void FC()
{
    std::ofstream fout( "aux/fc_n1000.dat");
    fout << std::setw(20) << "n" 
        << std::setw(20) << "up" << std::setw(20) << "down"
        << std::setw(20) << "width" << std::endl;

        for ( int n = 0 ; n != 101; ++n )
        {
            double up;
            double down;
            TEfficiency::FeldmanCousinsInterval( 100, n, 0.68, down, up );

            if ( n%10 == 0 )
            {
                std::cerr << "Done " << std::setw(3) << n << std::endl;
            }

        fout << std::setw(20) << n 
            << std::setw(20) << up << std::setw(20) << down 
            << std::setw(20) << up - down << std::endl;
        }
}
