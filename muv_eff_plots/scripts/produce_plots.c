void run()
{
    //gStyle->SetPalette(54);
    gStyle->SetOptStat(0);

    TFile tfin( "data/test_extract.root");
    //Data momentum dependence
    TGraphAsymmErrors * tg_mom;

    tfin.GetObject( "geom_cut/p5.data.q11t.v3/g", tg_mom );

    TCanvas c( "c", "c", 400, 400 );

    tg_mom->SetLineWidth(2);
    tg_mom->GetYaxis()->SetTitle("");
    tg_mom->Draw("ap");
    tg_mom->GetYaxis()->SetRangeUser( 0.95, 0.99 );
    tg_mom->GetXaxis()->SetRangeUser( 0, 68 );


    c.SetGrid( 1,1 );
    c.SaveAs( "output/data_muv_eff_p.pdf", "pdf");

    //--------------------------------------------------

    TH2D * h_xy_data;
    tfin.GetObject( "pcorrp/p5.data.q11t.v3/rat", h_xy_data );

    h_xy_data->Draw("colz");
    h_xy_data->GetZaxis()->SetRangeUser( 0.961, 1.0 );

    h_xy_data->SetTitle( "");

    gPad->Update();

    TPaletteAxis *palette = (TPaletteAxis*)h_xy_data
        ->GetListOfFunctions()->FindObject("palette");

    palette->SetX1NDC(0.85);
    palette->SetX2NDC(0.90);

    c.SaveAs( "output/data_muv_eff_xy.pdf", "pdf");

    //--------------------------------------------------

    TH2D * h_xy_data_tgt_p;
    tfin.GetObject( "narrow_mom/p5.data.q11t.v3/rat", h_xy_data_tgt_p );

    h_xy_data_tgt_p->Draw("col");
    h_xy_data_tgt_p->GetZaxis()->SetRangeUser( 0.0, 1.0 );

    h_xy_data_tgt_p->SetTitle( "");

    c.SaveAs( "output/data_muv_eff_xy_tgt_p.pdf", "pdf");

    //-------------------------------------------------
    
    TH2D * h_xy_data_tgt_xy;
    tfin.GetObject( "geom_cut_xy/p5.data.q11t.v3/rat", h_xy_data_tgt_xy );

    if( ! h_xy_data_tgt_xy )
    {
        std::cout << "Can't find geom_cut_xy/p5.data.q11t.v3/rat" << std::endl;
        return;
    }

    h_xy_data_tgt_xy->Draw("colz");
    h_xy_data_tgt_xy->GetZaxis()->SetRangeUser( 0.951, 1.0 );
    h_xy_data_tgt_xy->SetTitle( "");

    gPad->Update();

    palette = (TPaletteAxis*)h_xy_data_tgt_xy
        ->GetListOfFunctions()->FindObject("palette");

    palette->SetX1NDC(0.85);
    palette->SetX2NDC(0.90);

    c.SaveAs( "output/data_muv_eff_xy_tgt_xy.pdf", "pdf");

    //-------------------------------------------------
    
    TGraphAsymmErrors * tg_data_p;
    TGraphAsymmErrors * tg_mc_p;

    tfin.GetObject( "geom_cut/p5.data.q11t.v3/g", tg_data_p );
    tfin.GetObject( "geom_cut/p5.km2.v2/g", tg_mc_p );

    tg_data_p->Draw("pa");
    tg_mc_p->Draw("same");

    tg_data_p->GetYaxis()->SetRangeUser(0.94, 0.99 );
    tg_data_p->GetYaxis()->SetTitle("");
    tg_data_p->GetXaxis()->SetRangeUser(0, 68 );

    c.SaveAs( "output/tgt_xy_p_comp.pdf", "pdf");

    //-------------------------------------------------

    TH1D * h_p_ratrat;
    tfin.GetObject( "pratio/geom_cut/ratrat", h_p_ratrat );

    h_p_ratrat->SetLineColor( kWhite  );
    h_p_ratrat->SetMarkerStyle( kFullSquare );
    h_p_ratrat->SetMarkerSize( 0.6 );
    h_p_ratrat->SetTitle("");
    h_p_ratrat->Draw("P");
    h_p_ratrat->GetYaxis()->SetRangeUser(0.965, 1.015 );
    h_p_ratrat->GetYaxis()->SetTitle("");
    h_p_ratrat->GetXaxis()->SetRangeUser(0, 68 );

    c.SaveAs( "output/data_mc_p_rat.pdf", "pdf");

    //-------------------------------------------------
    
    TH2D * h_xy_ratrat;
    tfin.GetObject( "pratio/pcorrestp/ratrat", h_xy_ratrat );

    h_xy_ratrat->Draw("colz");

    h_xy_ratrat->Draw("colz");
    h_xy_ratrat->GetZaxis()->SetRangeUser( 0.951, 1.0 );
    h_xy_ratrat->SetTitle( "");

    gPad->Update();

    palette = (TPaletteAxis*)h_xy_ratrat
        ->GetListOfFunctions()->FindObject("palette");

    palette->SetX1NDC(0.85);
    palette->SetX2NDC(0.90);

    c.SaveAs( "output/data_muv_eff_xy_ratrat.pdf", "pdf");
}

void produce_plots()
{
    run();
}

