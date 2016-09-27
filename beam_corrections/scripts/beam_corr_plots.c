TH1 * get_hrat_uw( TFile& tf )
{
    TH1D * hdt = static_cast<TH1D*>(get_hist( tf, "loose_lkr_m2m/hdata" ) );
    TH1D * hbg = static_cast<TH1D*>(get_hist( tf, "loose_lkr_m2m/hbg" ) ) ;

    double dtw = integral( *hdt, -0.0055, 0.0055 );
    double bgw = integral( *hbg, -0.0055, 0.0055 );

    double rat = dtw/ bgw;
    std::cout << "Rat: " << rat << std::endl;
    hbg->Sumw2();
    hdt->Sumw2();
    hbg->Scale( rat );
    hdt->Divide( hbg );
    return hdt;
}


void do_plots()
{
    gStyle->SetOptStat(0);

    //Km2 peak ratio
    TFile tf_uw( "data/st_uw_shuffle.root" );
    TFile tf_wgt( "data/st_weighted_shuffle.root" );

    //TH1 * hrat_uw = get_hist( tf_uw, "loose_lkr_m2m/hratio" );
    TH1 * hrat_uw = get_hrat_uw( tf_uw );
    TH1 * hrat_wgt = get_hist( tf_wgt, "loose_lkr_m2m/hratio" );

    TCanvas c( "c", "c", 400, 400 );

    c.SetGridx();
    c.SetGridy();

    hrat_uw->SetTitle("");
    hrat_wgt->SetTitle("");
    hrat_uw->GetYaxis()->SetTitle( "Data / MC ratio" );
    hrat_uw->GetYaxis()->SetTitleOffset( 1.3);
    hrat_uw->GetXaxis()->SetTitleOffset( 1.1);
    hrat_wgt->GetYaxis()->SetTitle( "" );

    hrat_uw->Draw("E1");
    hrat_uw->SetLineColor( kRed -6 );
    hrat_uw->SetMarkerColor( kRed -6 );
    hrat_uw->SetMarkerStyle(22);
    hrat_uw->SetMarkerSize(0.5);
    
    hrat_uw->GetYaxis()->SetRangeUser(0.9, 1.6 );
    hrat_uw->GetXaxis()->SetRangeUser(-0.022, 0.022);
    hrat_uw->GetXaxis()->SetNdivisions(407, kTRUE );

    hrat_wgt->SetLineColor( kGreen -5 );
    hrat_wgt->SetMarkerColor( kGreen -5 );
    hrat_wgt->SetMarkerStyle(21);
    hrat_wgt->SetMarkerSize(0.5);

    hrat_wgt->Draw("E1,same");

    TLegend leg( 0.7, 0.75, 0.87, 0.87, "" );
    leg.AddEntry( hrat_uw, "unweighted", "lp" );
    leg.AddEntry( hrat_wgt, "weighted", "lp" );

    leg.Draw("same");

    c.SaveAs( "output/wgt_ratio.pdf" , "pdf" );

    //km2 peak stack
    TCanvas d( "d", "d", 400, 400 );
    d.SetGridx();
    d.SetGridy();
    d.SetLogy();

    std::cout << "Extracting hdata" << std::endl;
    TH1 * hdata = get_hist( tf_wgt, "loose_lkr_m2m/hdata" );
    hdata->SetMarkerColor( kBlack );
    hdata->SetMarkerStyle( 21 );
    hdata->SetMarkerSize( 0.3 );
    hdata->SetLineColor( kBlack );

    THStack * hstack = 0;

    std::cout << "Extracting hstack" << std::endl;
    tf_wgt.GetObject( "loose_lkr_m2m/hnu_stack", hstack );
    if  (hstack == 0 )
    {
        std::cout << "Couldn't find hnu_stack" << std::endl;
        return 168;
    }

    std::cout << "Setting range" << std::endl;
    hstack->Draw();
    hstack->GetHistogram()->GetXaxis()->SetRangeUser(-0.022, 0.022 );
    hstack->GetHistogram()->GetXaxis()->SetNdivisions(407, kTRUE );
    hstack->GetHistogram()->GetXaxis()->SetTitle("m^{2}_{miss} (GeV^{2} / c^{4})");
    hstack->GetHistogram()->GetXaxis()->SetTitleOffset( 1.1);

    hstack->Draw();
    hdata->Draw("E1, same" );

    TLegend legd( 0.12, 0.60, 0.3, 0.87, "" );
    legd.SetTextFont( 133 );
    legd.SetTextSize( 14 );
    TList * hlist = hstack->GetHists();
    legd.AddEntry(hdata , "data", "lp"  );
    legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos") ) , "K_{#mu2}", "f"  );
    legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
    legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos") ) , "Halo", "f"  );

    legd.Draw("same");
    d.SaveAs( "output/wgt_comp.pdf" , "pdf" );
}

void beam_corr_plots()
{
    do_plots();
}
