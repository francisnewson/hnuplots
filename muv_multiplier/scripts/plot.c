void do_plot()
{
    TFile tf { "data/p5.data.q11t.v3.pos_muon_shapes_muon_shapes.root"};

    auto * all = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier/errs" );
    auto * hp = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_high_mom/errs" );

    TCanvas c{ "c", "c", 300, 200 };
    c.SetGrid();

    all->Draw();
    all->GetXaxis()->SetRangeUser( 0, 7 );
    all->SetMinimum( 0.8 );
    all->SetMaximum( 1.0 );
    all->SetTitle( "" );
    all->GetXaxis()->SetTitle( "MUV cut multiplier #xi" );
    all->GetYaxis()->SetTitle( "Efficiency" );

    all->SetLineColor( kGreen + 2 );
    all->SetLineWidth( 2 );
    all->SetLineStyle( 2 );

    hp->SetLineColor( kBlue + 2 );
    hp->SetLineWidth( 2 );

    TLegend leg( 0.40, 0.2, 0.85, 0.35 );
    leg.AddEntry( hp, "30 GeV/c < p_{#mu} < 60 GeV/c", "l" );
    leg.AddEntry( all, "all events", "l" );

    leg.Draw("same");

    hp->Draw("same" );
    c.Print( "output/muv_multiplier.pdf", "pdf" );
}

void plot()
{
    do_plot();
}
