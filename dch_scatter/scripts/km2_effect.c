TH1 * get_total( TFile& tf )
{
    TH1 * hres = get_hist( tf, "p5.km2.v2.pos/signal_upper_muv/h_m2m_kmu" );

    TH1 * hn = get_hist( tf, "p5.km2.v2.pos/signal_lower_muv/h_m2m_kmu" );
    hres->Add( hn );

    hn = get_hist( tf, "p5.km2.v2.neg/signal_upper_muv/h_m2m_kmu" );
    hres->Add( hn );

    hn = get_hist( tf, "p5.km2.v2.neg/signal_lower_muv/h_m2m_kmu" );
    hres->Add( hn );

    return hres;
}

TH1 *  gl( const THStack* hs, std::string s )
{
    TObject * res = hs->GetHists()->FindObject( s.c_str() ) ;
    if ( ! res )
    {
        throw std::runtime_error( "Can't find " + s + " in " + hs->GetName() );
    }
    return static_cast<TH1*>(res);
}

void do_plot()
{
    TFile tf_no_scat{ "data/all.km2_noscat.root" };
    TFile tf_scat{ "data/all.km2_scat.root" };
    TFile tf_old_scat{ "data/old.km2_scat.root" };

    TH1 * hscat = get_total( tf_scat );
    TH1 * hnoscat = get_total( tf_no_scat );
    TH1 * holdscat = get_total( tf_no_scat );

    hscat->Rebin(10);
    hnoscat->Rebin(10);
    holdscat->Rebin(10);

    TCanvas c1( "c", "c", 600, 400 );
    hscat->Draw();
    hscat->GetXaxis()->SetRangeUser( -0.1, 0.2 );
    hscat->GetYaxis()->SetRangeUser( 0, 10000 );
    hscat->SetLineColor( kRed );
    hnoscat->Draw("same");
    holdscat->Draw("same");

    c1.SetGrid();

    c1.Print( "output/km2_comp_scat.pdf", "pdf" );

    hscat->GetYaxis()->SetRangeUser( 1, 1e7 );
    c1.SetLogy();
    c1.Print( "output/km2_comp_scat_log.pdf", "pdf" );

    c1.SetLogy(0);
    hscat->GetYaxis()->SetRangeUser( 0, 1000 );
    hscat->GetXaxis()->SetRangeUser( 0.08, 0.16 );
    c1.Print( "output/km2_comp_scat_zoom.pdf", "pdf" );

    hscat->Rebin(2);
    hnoscat->Rebin(2);

    hscat->Sumw2();
    hnoscat->Sumw2();

    TH1 * hdiff = static_cast<TH1*>( hscat->Clone( "hdiff" ) );
    hdiff->Add( hnoscat, -1 );
    hdiff->Divide( hnoscat );
    hdiff->Draw("E1");
    hdiff->GetXaxis()->SetRangeUser( 0.00, 0.16 );
    hdiff->GetYaxis()->SetRangeUser( 0.00, 1 );
    c1.Print( "output/km2_comp_scat_rel_diff.pdf", "pdf" );
}

void total_plot()
{
    gStyle->SetOptStat(0);
    TFile tfin{ "data/km2_both_scat.root" };

    std::cerr << "Loading scat stacks ..." << std::endl;
    THStack * hs_noscat = get_thing<THStack>( tfin, "noscat/hnu_stack" );
    THStack * hs_scat = get_thing<THStack>( tfin, "scat/hnu_stack" );

    std::cerr << "Creating canvas ..." << std::endl;
    TCanvas c1( "c", "c", 600, 600 );
    c1.SetGrid();
    c1.SetLogy();


    std::cerr << "Drawing stack ..." << std::endl;
    //hs_noscat->Draw();
    //std::cerr << "Setting title ..." << std::endl;
    //hs_noscat->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c )" );
    //hs_noscat->SetMinimum(100);
    //hs_noscat->SetMaximum(1000000);
    //hs_noscat->GetXaxis()->SetRangeUser( 0, 0.16 );


    TH1 * h_noscat = static_cast<TH1*>( hs_noscat->GetStack()->Last() );
    TH1 * hscat = static_cast<TH1*>( hs_scat->GetStack()->Last() );
    TH1 * h_diff = static_cast<TH1*>( hscat->Clone( "hdiff" ));

    h_noscat->SetFillStyle(0);
    h_noscat->SetLineStyle(2);
    h_noscat->SetLineColor(kBlack);
    h_noscat->SetLineWidth(2);
    h_noscat->GetXaxis()->SetRangeUser( -0.049, 0.15 );
    h_noscat->GetXaxis()->SetNdivisions(5 );
    h_noscat->GetXaxis()->SetTitleOffset( 1.3 );
    h_noscat->GetYaxis()->SetRangeUser( 500, 1e7);
    h_noscat->GetYaxis()->SetTitle("");
    h_noscat->SetTitle("");
    h_noscat->Draw();


    std::cerr << "Drawing scat ..." << std::endl;
    hscat->SetFillStyle(0);
    hscat->SetLineColor(kRed + 2);
    hscat->SetLineWidth(2);
    hscat->Draw("same" );

    std::cerr << "Building legend ..." << std::endl;
    TLegend legd( 0.62, 0.65, 0.83, 0.83);

    legd.AddEntry( hscat, "MC (scat)", "l" );
    legd.AddEntry( h_noscat, "MC (no scat)", "l" );
   // legd.AddEntry( gl( hs_noscat , "km2_pos") ,"K^{+} #rightarrow #mu #nu_{#mu}", "f" );
   // legd.AddEntry( gl( hs_noscat , "k2pig_pos") ,"K^{+} #rightarrow #pi^{+} #pi^{0}", "f" );
   // legd.AddEntry( gl( hs_noscat , "k3pi_pos") ,"K^{+} #rightarrow #pi^{+} #pi^{+} #pi^{0}", "f" );
   // legd.AddEntry( gl( hs_noscat , "km3_pos") ,"K^{+} #rightarrow #mu^{+} #pi^{0} #nu", "f" );
    legd.Draw("same");

    c1.Print( "output/km2_scatter_effect.pdf", "pdf" );

    std::cerr << "Loading no stack ..." << std::endl;

    h_diff->Rebin(2);
    h_noscat->Rebin(2);

    h_diff->Add( h_noscat, -1 );
    h_diff->Sumw2();
    h_diff->Divide( h_noscat );

    TCanvas c2( "c", "c", 600, 400 );

    c2.SetGrid();
    c2.SetLogy(0);
    c2.SetLeftMargin( 0.13 );
    h_diff->SetBinContent(h_diff->FindBin(0.149), 0 );
    h_diff->SetBinError(h_diff->FindBin(0.149), 0 );

    for ( int i = 1; i <= h_diff->GetNbinsX(); ++i )
    {
        h_diff->SetBinContent( i, fabs( h_diff->GetBinContent(i ) ) );
    }

    h_diff->GetXaxis()->SetRangeUser( 0.07, 0.16 );
    h_diff->GetYaxis()->SetRangeUser( -0.00, 0.06 );
    h_diff->GetYaxis()->SetTitle( "Fractional error" );
    h_diff->GetYaxis()->CenterTitle( "Fractional error" );
    h_diff->GetYaxis()->SetTitleOffset(1.4);
    h_diff->GetXaxis()->SetTitleOffset(1.3);
    h_diff->SetLineWidth(2);

    h_diff->SetLineColor( kBlack );
    h_diff->SetTitle("");

    h_diff->SetFillStyle(0);
    h_diff->Draw("HIST");
    c2.Print( "output/km2_scatter_effect_rel.pdf", "pdf" );
}

void km2_effect()
{
    total_plot();
}
