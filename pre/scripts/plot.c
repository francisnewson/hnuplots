void do_plots()
{
    gStyle->SetOptStat(0);
    TFile tf{ "data/pre_shuffle.root" };

    std::vector<std::pair<std::string,std::string>> channels
    { 
        {"km2_pos", "#mu #nu_{#mu}"}
        , {"k2pi_pos", "#pi^{+} #pi^{0}"}
        , {"ke3_pos", "#pi^{0} e^{+} #nu_{e}"}
        , {"km3_pos", "#pi^{0} #mu^{+} #nu_{#mu}"}
        , {"k3pi0_pos", "#pi^{+} #pi^{0} #pi^{0}"}
        , {"k3pi_pos", "#pi^{+} #pi^{+} #pi^{-}"}
        ,{"halo_pos", "halo"}
    };

    TCanvas c{ "c", "c", 400, 400 };

    TLegend t{ 0.15, 0.450, 0.35, 0.85 };

    for ( auto & chanpair : channels )
    {
        auto * h = get_thing<TH1>( tf, Form( "pos/pre_pre/h_m2m_kmu/hnu_stack_hists/%s", chanpair.first.c_str() ) );
        t.AddEntry( h, chanpair.second.c_str(),  "l" );
        h->SetMinimum( 1e2 );
        h->SetMaximum( 1e7 );
        h->GetXaxis()->SetRangeUser(-0.2, 0.2 );
        h->SetFillColor( 0 );
        h->SetLineWidth( 2 );
        h->SetFillStyle( 0 );
        h->SetTitle( "" );
        h->GetYaxis()->SetTitle("");
        h->Draw("same");
    }

    t.SetMargin( 0.3 );
    t.SetBorderSize(1);
    //t.Draw("same" );

    c.SetGrid();
    c.SetTitle("");

    c.SetLogy();
    c.Print( "output/pre_selection.pdf" );
}

void plot()
{
    do_plots();
}
