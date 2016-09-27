#include <algorithm>
#include <numeric>

void pulls()
{
    gStyle->SetOptStat(0);


    std::ifstream ifs( "output/pulls.dat" );
    TH1D h( "", "", 25, -5, 5 );
    int count = 0;
    std::vector<double> pulls;
    for ( std::string buf; std::getline( ifs, buf ); )
    {
        std::stringstream ss(buf);
        int index;
        double mass;
        double pull;
        ss >> index >>  mass >> pull;
        ++count;
        pulls.push_back(pull);
        h.Fill( pull );
    }

    //calculate mean
    double total = std::accumulate( begin( pulls ), end( pulls ), 0.0 );
    double n = pulls.size();
    double mean = total / n;
    std::cout << mean << std::endl;

    //calculate standard deviation
    double sum_squares = std::accumulate( begin( pulls ), end(pulls), 0.0,
            []( const double & lhs, const double & rhs ){
            return lhs + rhs * rhs ; } );

    double variance = sum_squares / n - mean * mean;
    double stddev = std::sqrt( variance );

    std::cout << mean << std::endl;
    std::cout << stddev << std::endl;



    std::cout << count << std::endl;
    std::cout << h.GetMean() << std::endl;
    std::cout << h.GetRMS() << std::endl;


    TCanvas c{"c", "c", 500, 500 };
    c.SetGrid();
    h.Draw();
    h.GetXaxis()->SetTitle("pull" );
    TLatex tmu( 1.1, 25, "#mu: 0.03 #pm  0.10" );
    TLatex tsigma( 1.1, 22, "#sigma: 0.95 #pm  0.07" );
    tmu.Draw("same" );
    tsigma.Draw("same" );
    h.SetLineColor( kBlack );
    h.SetLineWidth( 2 );
    //h.Fit( "gaus" );
    c.Print( "output/pull_dist.pdf", "pdf" );
}
