#include "TEfficiency.h"

void plot_m2m()
{
    TFile tf{"data/all.hnu_demo.root"};
    gStyle->SetOptStat(0);

    std::vector<int> masses{ 0, 50, 100, 150, 200, 225, 250, 275, 300, 310, 320, 330, 340, 350, 360, 370, 380};
    std::vector<int> m2m_masses{ 0, 100,  200, 250, 300,  320, 340, 360,  380};

    std::reverse( m2m_masses.begin(), m2m_masses.end() );

    TCanvas c{ "c", "c", 600, 500 };
    c.SetGrid();

    TH1D * hwgt = new TH1D( "hwgt", "hwgt", 1, 0, 100000 );

    TCanvas d{ "d", "d", 100, 100 };

    for ( auto mass : m2m_masses )
    {

        d.cd();
        auto  * w = get_thing<TTree>( tf, Form( "mc.p5.hnu.%03d.nodk.pos/sample_burst_count/bursts", mass ) );
        hwgt->Reset();
        w->Draw("events>>hwgt", "weight", "Q" );
        double total_weight = hwgt->GetSumOfWeights();

        c.cd();

        auto * h = get_thing<TH1D>( tf, Form("mc.p5.hnu.%03d.nodk.pos/pre_plots/h_m2m_kmu", mass) );
        h->Scale( 50000.0 / total_weight );
        h->GetXaxis()->SetRangeUser( -0.02, 0.16 );
        h->GetYaxis()->SetRangeUser(0, 2000 );
        h->GetYaxis()->SetTitle("");
        h->SetTitle("");
        h->SetLineColor( kBlack );
        h->SetFillColor ( kGray );
        int binmax = h->GetMaximumBin();
        double max = h->GetBinContent(binmax);
        std::cout << h->GetBinWidth(1) << std::endl;
        h->Draw("same" );
        auto *t = new TLatex( (0.001*mass)* ( 0.001*mass)+0.0015, max + 100 , Form( "%d MeV/c^{2}", mass) );
        t->SetTextSize( 0.025 );
        t->SetTextAngle( 90 );
        t->Draw("same" );
    }
    c.Print( "output/h_m2m_hnu.pdf", "pdf" );

    TCanvas e{ "c", "c", 600, 500 };
    e.SetGrid();

    std::vector<int> p_masses{  250, 300,  320, 340, 360,  380};
    std::reverse( p_masses.begin(), p_masses.end() );
    std::vector<std::string> colors {"#000000", "#132a4c", "#4c6b99", "#acc3e6", "#708040", "#909090"};
    int count = 0;

    TLegend l(0.65, 0.55, 0.85, 0.85 );

    for ( auto mass : p_masses )
    {
        d.cd();
        auto  * w = get_thing<TTree>( tf, Form( "mc.p5.hnu.%03d.nodk.pos/sample_burst_count/bursts", mass ) );
        hwgt->Reset();
        w->Draw("events>>hwgt", "weight", "Q" );
        double total_weight = hwgt->GetSumOfWeights();


        e.cd();

        auto * h = get_thing<TH1D>( tf, Form("mc.p5.hnu.%03d.nodk.pos/pre_plots/h_p", mass) );
        l.AddEntry( h, Form( "%d (MeV/c^{2})", mass ), "l" );
        std::cout << colors[count] << std::endl;
        int color = TColor::GetColor( colors[count].c_str() );
        h->GetXaxis()->SetRangeUser( 0, 60 );
        h->GetXaxis()->SetTitle( "p (GeV/c)" );
        h->Scale( 50000.0 / total_weight );
        h->GetYaxis()->SetTitle("");
        h->SetTitle("");
        h->SetLineColor( color );
        h->SetLineWidth( 2 );
        h->Draw("same");

        ++count;
    }
    l.Draw("same" );
    e.Print( "output/h_p.pdf", "pdf" );

    gROOT->Reset();

    count = 0;

    e.Clear();

    for ( auto mass : p_masses )
    {
        d.cd();
        auto  * w = get_thing<TTree>( tf, Form( "mc.p5.hnu.%03d.nodk.pos/sample_burst_count/bursts", mass ) );
        hwgt->Reset();
        w->Draw("events>>hwgt", "weight", "Q" );
        double total_weight = hwgt->GetSumOfWeights();


        e.cd();

        auto * h = get_thing<TH1D>( tf, Form("mc.p5.hnu.%03d.nodk.pos/pre_plots/h_t", mass) );
        std::cout << colors[count] << std::endl;
        int color = TColor::GetColor( colors[count].c_str() );
        h->GetXaxis()->SetRangeUser( 0, 0.015 );
        h->Scale( 50000.0 / total_weight );
        h->GetYaxis()->SetTitle("");
        h->SetTitle("");
        h->SetLineColor( color );
        h->SetLineWidth( 2 );

        if ( count == 0 )
        {
            h->Draw();
        }
        {
            h->Draw("same");
        }

        h->GetXaxis()->SetRangeUser( 0, 0.015 );

        ++count;
    }
    l.Draw("same" );
    e.Print( "output/h_t.pdf", "pdf" );

    gROOT->Reset();


}

void get_stats()
{
    TFile tf{"data/all.hnu_demo.root"};
    gStyle->SetOptStat(0);

    std::vector<int> masses{ 0, 50, 100, 150, 200, 225, 250, 275, 300, 310, 320, 330, 340, 350, 360, 370, 380};
    TH1D * hwgt = new TH1D( "hwgt", "hwgt", 1, 0, 100000 );

    std::ofstream ofs( "data/hnu_stats.dat");

    ofs 
        << std::setw(20) << "mass" 
        << std::setw(20) << "fit_sigma"
        << std::setw(20) << "acceptance"
        << std::setw(20) << "acc_err"
        << std::endl;

    for ( auto mass : masses )
    {
        auto  * w = get_thing<TTree>( tf, Form( "mc.p5.hnu.%03d.nodk.pos/sample_burst_count/bursts", mass ) );
        hwgt->Reset();
        w->Draw("events>>hwgt", "weight", "Q" );
        double total_weight = hwgt->GetSumOfWeights();

        auto * h = get_thing<TH1D>( tf, Form("mc.p5.hnu.%03d.nodk.pos/pre_plots/h_m2m_kmu", mass) );
        h->Draw();
        TF1 fit{ "gaus", "gaus" };
        h->Fit( &fit );
        double width = fit.GetParameter(2);
        //double width = h->GetRMS();
        double pass_weight = h->GetSumOfWeights();
        double acceptance =  pass_weight / total_weight;

        double up = TEfficiency::ClopperPearson( total_weight , pass_weight, 0.68, true );
        double dn = TEfficiency::ClopperPearson( total_weight , pass_weight, 0.68, false );
        double acc_err = up - dn;

        ofs
            << std::setw(20) << mass 
            << std::setw(20) << width
            << std::setw(20) << acceptance
            << std::setw(20) << acc_err
            << std::endl;
    }
}

void hnu_plots()
{
    plot_m2m();
    //get_stats();
}
