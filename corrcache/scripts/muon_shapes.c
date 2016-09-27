void prep( TGraphAsymmErrors& h , int color )
{
    h.SetLineColor( color );
    h.SetLineWidth( 2 );
    h.SetLineStyle( 1 );
}

void do_plot()
{
    TFile tf { "data/p5.data.q11t.v3.pos_muon_shapes_muon_shapes.root"};

    auto * cm10 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_10/errs" );
    prep( *cm10, TColor::GetColor( "#66c2a5" ) );
    auto * cm20 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_20/errs" );
    prep( *cm20, TColor::GetColor( "#fc8d62" ) );
    auto * cm30 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_30/errs" );
    prep( *cm30, TColor::GetColor( "#8da0cb" ) );
    auto * cm40 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_40/errs" );
    prep( *cm40, TColor::GetColor( "#e78ac3" ) );
    auto * cm50 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_50/errs" );
    prep( *cm50, TColor::GetColor( "#a6d854" ) );
    auto * cm60 = get_thing<TGraphAsymmErrors>( tf, "p5.data.q11t.v3.pos/check_multiplier_60/errs" );
    prep( *cm60, TColor::GetColor( "#e5c494" ) );

    TCanvas c{ "c", "c", 300, 200 };
    c.SetGrid();

    cm10->Draw();
    cm10->GetXaxis()->SetRangeUser( 0, 7 );
    cm10->SetMinimum( 0.8 );
    cm10->SetMaximum( 1.0 );
    cm10->SetTitle( "" );
    cm10->GetXaxis()->SetTitle( "MUV cut multiplier #xi" );
    cm10->GetYaxis()->SetTitle( "Efficiency" );

    cm20->Draw("same");
    cm30->Draw("same");
    cm40->Draw("same");
    cm50->Draw("same");
    cm60->Draw("same");


    TLegend leg( 0.40, 0.2, 0.85, 0.55 );
    leg.AddEntry( cm10,  "5 GeV/c < p_{#mu} < 15 GeV/c", "l" );
    leg.AddEntry( cm20, "15 GeV/c < p_{#mu} < 25 GeV/c", "l" );
    leg.AddEntry( cm30, "25 GeV/c < p_{#mu} < 35 GeV/c", "l" );
    leg.AddEntry( cm40, "35 GeV/c < p_{#mu} < 45 GeV/c", "l" );
    leg.AddEntry( cm50, "45 GeV/c < p_{#mu} < 55 GeV/c", "l" );
    leg.AddEntry( cm60, "55 GeV/c < p_{#mu} < 65 GeV/c", "l" );

    leg.Draw("same");
    c.Print( "output/muv_multiplier.pdf", "pdf" );
}

void muon_shapes()
{
    do_plot();
}

