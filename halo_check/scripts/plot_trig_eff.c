std::unique_ptr<TH1D> sum_list( TFile& tf, std::vector<std::string> list )
{
    auto path = list.begin();
    auto result  = static_cast<TH1D*>( get_thing<TH1D>( tf, *path )->Clone() );
    result->SetDirectory(0);
    ++path;

    while( path != list.end() )
    {
        result->Add( get_thing<TH1D>( tf, *path ) );
        ++path;
    }

    return std::unique_ptr<TH1D>( result );
}

void do_trig_plot()
{
    TFile tf{"data/2015-09-12/all.shuffle_plots.root"};
    std::vector<std::string> pass_list = 
    { "signal_hc/upper/pos/h_m2m_kmu_vis/htrig_num" ,
        "signal_hc/upper/neg/h_m2m_kmu_vis/htrig_num" ,
        "signal_hc/lower/pos/h_m2m_kmu_vis/htrig_num" ,
        "signal_hc/lower/neg/h_m2m_kmu_vis/htrig_num" };

    std::vector<std::string> all_list = 
    { "signal_hc/upper/pos/h_m2m_kmu_vis/htrig_denom" ,
        "signal_hc/upper/neg/h_m2m_kmu_vis/htrig_denom" ,
        "signal_hc/lower/pos/h_m2m_kmu_vis/htrig_denom" ,
        "signal_hc/lower/neg/h_m2m_kmu_vis/htrig_denom" };

    auto hpass = sum_list( tf, pass_list );
    auto hall  = sum_list( tf, all_list );
    hpass->GetYaxis()->SetTitle( "Measured trigger efficiency" );
    hall->GetYaxis()->SetTitle( "Measured trigger efficiency" );

    std::cerr << "About to create TEfficiency object" << std::endl;
    TEfficiency teff( *hpass, *hall );
    teff.SetConfidenceLevel( 0.68 );
    teff.SetStatisticOption( TEfficiency::kFCP );
    teff.SetMarkerColor( kBlack );
    teff.SetMarkerStyle( 21 );
   teff.SetMarkerSize( 0.6 );

    std::cerr << "About to draw" << std::endl;
    TCanvas c{ "c", "c", 600, 400 };
    c.SetGrid();
    teff.Draw();
    gPad->Update();
    teff.GetPaintedGraph()->GetXaxis()->SetRangeUser( 0.0025, 0.159 );
    teff.GetPaintedGraph()->GetYaxis()->SetRangeUser( 0.75, 1.0 );
    teff.GetPaintedGraph()->GetYaxis()->SetTitle("Measured trigger efficiency");
    gPad->Update();

    c.Print( "output/efficiency.pdf" , "pdf" );
}

void plot_trig_eff()
{
    do_trig_plot();
}
