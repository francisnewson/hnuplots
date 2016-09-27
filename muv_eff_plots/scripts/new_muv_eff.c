void plot()
{
    gStyle->SetOptStat(0);
    TFile tf { "data/test_muv_eff.root"};


    auto hraw_data_xy = get_thing<TH2D>( tf, "clean/dt_xy_eff" );
    hraw_data_xy->Rebin2D(2, 2);
    hraw_data_xy->Scale( 0.25 );

    {
        TCanvas c{ "c", "c", 500, 500 };

        c.SetGrid();
        hraw_data_xy->GetXaxis()->CenterTitle();
        hraw_data_xy->GetYaxis()->CenterTitle();
        hraw_data_xy->GetZaxis()->SetNdivisions(5);

        hraw_data_xy->Draw("colz");
        hraw_data_xy->GetZaxis()->SetRangeUser( 0.95, 1.00);
        hraw_data_xy->SetTitle("");
        c.SetLeftMargin( 0.15);
        c.SetRightMargin( 0.15);

        c.Print( "output/new_muv_eff/hraw_data_xy.pdf", "pdf" );
    }

    auto hhp_data_xy = get_thing<TH2D>( tf, "hpxyp/dt_xy_eff" );
    hhp_data_xy->Rebin2D(2, 2);
    hhp_data_xy->Scale( 0.25 );
    {
        TCanvas c{ "c", "c", 500, 500 };

        c.SetGrid();
        hhp_data_xy->GetXaxis()->CenterTitle();
        hhp_data_xy->GetYaxis()->CenterTitle();
        hhp_data_xy->GetZaxis()->SetNdivisions(5);

        hhp_data_xy->Draw("colz");
        hhp_data_xy->GetZaxis()->SetRangeUser( 0.95, 1.00);
        hhp_data_xy->SetTitle("");
        c.SetLeftMargin( 0.15);
        c.SetRightMargin( 0.15);

        c.Print( "output/new_muv_eff/hhpxycut_data_xy.pdf", "pdf" );
    }

    auto hhp = get_thing<TH2D>( tf, "hp/dt_xy_eff" );
    hhp->Rebin2D(1, 1);
    hhp->Scale( 0.25 );
    {
        TCanvas c{ "c", "c", 500, 500 };
        c.SetGrid();

        hhp->GetXaxis()->CenterTitle();
        hhp->GetYaxis()->CenterTitle();
        hhp->Draw("col");
        hhp->GetZaxis()->SetRangeUser( 0, 1000 );
        hhp->SetTitle( "" );
        c.Print( "output/new_muv_eff/hhp_data_xy.pdf", "pdf" );
    }

    auto hfull_dt_p_eff = get_thing<TEfficiency>( tf, "test/dt_p_eff");
    {
        TCanvas c{ "c", "c", 500, 500 };
        c.SetGrid();

        hfull_dt_p_eff->Draw();
        gPad->Update();
        hfull_dt_p_eff->GetPaintedGraph()->GetXaxis()->SetRangeUser(0, 68);
        hfull_dt_p_eff->GetPaintedGraph()->GetYaxis()->SetRangeUser(0.95, 1.0);
        hfull_dt_p_eff->GetPaintedGraph()->GetYaxis()->SetNdivisions( 5  );
        hfull_dt_p_eff->GetPaintedGraph()->GetYaxis()->SetTitle( "Efficiency"  );
        hfull_dt_p_eff->SetTitle(";p(GeV);Efficiency");

        c.Print( "output/new_muv_eff/hdt_full_p.pdf", "pdf" );
    }

    auto cut_dt_p = get_thing<TEfficiency>( tf, "xycut/dt_p_eff" );
    auto cut_mc_p = get_thing<TEfficiency>( tf, "xycut/mc_p_eff_rew_hpxy" );

    {
        TCanvas c{ "c", "c", 500, 500 };
        c.SetGrid();
        cut_dt_p->Draw();
        gPad->Update();
        cut_dt_p->SetTitle(";p(GeV);Efficiency");
        cut_dt_p->GetPaintedGraph()->GetXaxis()->SetRangeUser(0, 68);
        cut_dt_p->GetPaintedGraph()->GetYaxis()->SetRangeUser( 0.95, 1.00 );
        cut_dt_p->GetPaintedGraph()->GetYaxis()->SetNdivisions( 5  );

        cut_dt_p->SetLineColor( kBlue + 2);
        cut_dt_p->SetMarkerStyle( 22);
        cut_dt_p->SetMarkerSize( 0.8);
        cut_dt_p->SetMarkerColor( kBlue + 2);

        cut_mc_p->SetLineColor( kRed + 2);
        cut_mc_p->SetMarkerColor( kRed + 2);
        cut_mc_p->SetMarkerStyle( 20);
        cut_mc_p->SetMarkerSize( 0.6);
        cut_mc_p->Draw("same");

        TLegend leg( 0.70, 0.70, 0.85, 0.85 );
        leg.AddEntry( cut_mc_p, "MC", "lep" );
        leg.AddEntry( cut_dt_p, "data", "lep" );
        leg.Draw( "same" );
        c.Print( "output/new_muv_eff/xycut_peff_comp.pdf", "pdf" );
    }

    hpeff_corr_norm = get_thing<TH1D>( tf, "xycut/p_eff_corr_norm" );

    {
        TCanvas c{ "c", "c", 500, 500 };
        c.SetGrid();
        c.SetLeftMargin( 0.15);
        c.SetRightMargin( 0.05);
        hpeff_corr_norm->Draw("P");
        hpeff_corr_norm->SetMarkerStyle( 21 );
        gPad->Update();
        hpeff_corr_norm->SetTitle(";p(GeV);MC Efficiency correction");
        hpeff_corr_norm->GetXaxis()->SetRangeUser(0, 68);
        hpeff_corr_norm->GetYaxis()->SetRangeUser( 0.97, 1.00 );
        hpeff_corr_norm->GetYaxis()->CenterTitle();
        hpeff_corr_norm->GetYaxis()->SetNdivisions( 7  );
        hpeff_corr_norm->GetYaxis()->SetTitleOffset( 1.8  );
        c.Print( "output/new_muv_eff/mc_p_corr.pdf", "pdf" );
    }

    hfinal_xy = get_thing<TH2D>( tf, "test/mc_xy_eff" );
    hfinal_xy->Rebin2D(2, 2);
    hfinal_xy->Scale( 0.25 );
    {
        TCanvas c{ "c", "c", 500, 500 };
        c.SetGrid();
        hfinal_xy->GetXaxis()->CenterTitle();
        hfinal_xy->GetYaxis()->CenterTitle();
        hfinal_xy->GetZaxis()->SetNdivisions(5);

        hfinal_xy->Draw("colz");
        hfinal_xy->GetZaxis()->SetRangeUser( 0.95, 1.00);
        hfinal_xy->SetTitle("");
        c.SetLeftMargin( 0.15);
        c.SetRightMargin( 0.15);

        c.Print( "output/new_muv_eff/final_xy_corr.pdf", "pdf" );
    }


}

void new_muv_eff()
{
    plot();
}
