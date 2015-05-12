#include <iomanip>

struct muv_burst
{
    Long64_t run;
    Long64_t burst_time;

    double total;
    double pass;
};

void plot()
{
    TFile tfin( "data/muv_bursts.root" );

    TTree * tt = 0;
    tfin.GetObject( "split_muv_bursts", tt );

    muv_burst mb{0,0,0,0};
    int ret = tt->SetBranchAddress("run", &mb.run );
    ret = tt->SetBranchAddress("burst_time", &mb.burst_time );
    ret = tt->SetBranchAddress("total", &mb.total );
    ret = tt->SetBranchAddress("pass", &mb.pass );

    std::cout << ret << std::endl;

    Long64_t nentries = tt->GetEntries();
    std::cout << nentries << std::endl;

    TH1D h_eff( "heff", "Muon veto efficiency", 200, 0, 1 );
    h_eff.GetXaxis()->SetTitle( "Efficiency" );
    h_eff.GetYaxis()->SetTitle( "Number of bursts" );
    h_eff.GetYaxis()->CenterTitle();

    for ( Long64_t ient = 0 ; ient != nentries ; ++ient )
    {
        double read = tt->GetEntry( ient, 1 );

#if 0
        std::cout 
            << std::setw(10) << ient     << std::setw(10) << read  
            << std::setw(10) << mb.run   << std::setw(10) << mb.burst_time
            << std::setw(10) << mb.total << std::setw(10) << mb.pass << std::endl;
#endif

        h_eff.Fill( mb.pass / mb.total );
    }

    h_eff.SetLineColor( kBlue + 4 );
    h_eff.SetLineWidth( 2 );

    gStyle->SetOptStat(0);
    TCanvas c( "c", "C", 600, 500 );
    c.SetGrid();
    h_eff.Draw();
    c.SetLogy();

    c.SaveAs( "output/muv_eff.pdf", "pdf" );;
}
