void do_pulls( std::string input, std::string output, double rms )
{
    gStyle->SetOptStat(0);

    std::ifstream ifs( input );
    TH1D h( "", "", 25, -5, 5 );
    for ( std::string buf; std::getline( ifs, buf ); )
    {
        std::stringstream ss(buf);
        int index;
        double mass;
        double pull;
        ss >> index >>  mass >> pull;
        h.Fill( pull );
    }

    TCanvas c{"c", "c", 500, 500 };
    c.SetGrid();
    h.Draw();
    h.GetXaxis()->SetTitle("pull" );
    TText tt( 1.3, 22, Form("RMS: %.2f", rms) );
    tt.Draw("same" );
    h.SetLineColor( kBlack );
    h.SetLineWidth( 2 );
    c.Print( output.c_str() , "pdf" );

}
void k3pi_pulls()
{
    do_pulls( "output/2015-10-21_orig_k3pi/pulls.dat",
 "output/2015-10-21_orig_k3pi/pull_dist.pdf", 0.93 );

    do_pulls( "output/2015-10-21_semi_k3pi/pulls.dat",
 "output/2015-10-21_semi_k3pi/pull_dist.pdf", 0.90 );

    do_pulls( "output/2015-10-21_extra_k3pi/pulls.dat",
 "output/2015-10-21_extra_k3pi/pull_dist.pdf", 0.75 );
}
