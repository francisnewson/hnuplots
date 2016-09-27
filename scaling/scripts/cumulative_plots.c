void do_plot()
{
    gStyle->SetOptStat(0);
    TFile tfin{ "data/all.merge_plots.root" };
    auto hstack = get_thing<THStack>( tfin, "final/rk/full_mvis/hstack" );
    auto hdt = get_thing<TH1D>( tfin, "final/rk/full_mvis/hdata" );

    {
        TCanvas c{ "c", "c", 400, 400  };
        c.SetLogy();
        c.SetGrid();

        hstack->Draw();
        hstack->GetXaxis()->SetRangeUser( -0.05, 0.05 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c^{4})");
        hstack->GetYaxis()->SetNdivisions( 202 );
        hdt->SetLineColor( kGray + 3 );
        hdt->Draw("same,P");
        hdt->SetMarkerSize( 0.4);
        hdt->SetMarkerStyle( 21);

        TArrow rh_arrow( 0.015, 1e5, 0.015, 0.7e4, 0.03, "|>" );
        TArrow lh_arrow( -0.015, 1e5, -0.015, 0.7e4, 0.03, "|>" );
        rh_arrow.SetAngle(40);
        rh_arrow.SetLineWidth(2);

        lh_arrow.SetAngle(40);
        lh_arrow.SetLineWidth(2);

        rh_arrow.Draw("" );
        lh_arrow.Draw("" );

        TList * hlist = hstack->GetHists();

        TLegend leg( 0.6, 0.6, 0.8, 0.8 );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos" ) ), "K^{+} #rightarrow #mu^{+} #nu", "f" );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos" ) ), "Halo", "f"  );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pi_pos" ) ), "K^{+} #rightarrow #pi^{+} #pi^{0}", "f" );
        leg.AddEntry( hdt, "data", "p" );

        leg.Draw("same");


        c.Print( "output/rk_full_stack.pdf", "pdf" );

    }

    {
        auto hrat = get_thing<TH1D>(tfin, "final/rk/full_mvis/h_err_ratio" );
        TCanvas c{ "c", "c", 400, 400  };
        c.SetGrid();
        c.SetTitle("");
        hrat->SetTitle("");
        hrat->GetYaxis()->SetTitle("Data/MC ratio");
        hrat->Draw();
        hrat->GetXaxis()->SetRangeUser( -0.05, 0.05 );
        hrat->GetYaxis()->SetRangeUser( 0.6, 1.6 );
        c.Print( "output/rk_rat.pdf", "pdf" );

    }

#if 0
    {
        auto hstack = get_thing<THStack>( tfin, "km2_rk_mvis_neg/hstack" );
        auto hdt = get_thing<TH1D>(tfin,  "km2_rk_mvis_neg/hdata" );

        TCanvas c{ "c", "c", 400, 400  };
        c.SetLogy();
        c.SetGrid();

        hstack->Draw();
        hstack->GetXaxis()->SetRangeUser( -0.05, 0.05 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c^{4})");
        hstack->GetYaxis()->SetNdivisions( 8 );
        hdt->SetLineColor( kGray + 3 );
        hdt->Draw("same,E");

        TList * hlist = hstack->GetHists();

        TLegend leg( 0.6, 0.6, 0.8, 0.8 );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_neg" ) ), "K^{+} #rightarrow #mu^{+} #nu", "f" );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_neg" ) ), "Halo" , "f" );
        leg.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pi_neg" ) ), "K^{+} #rightarrow #pi^{+} #pi^0", "f" );
        leg.AddEntry( hdt, "data", "pel" );

        leg.Draw("same");

        c.Print( "output/rk_neg_stack.pdf", "pdf" );
    }
#endif
    {
        auto hcumrk = get_thing<TH1>( tfin, "final/rk/neg/h_cum_rat" );
        auto hcumfull = get_thing<TH1>( tfin, "final/km2_full/neg/h_cum_rat" );
        hcumrk->SetLineColor( kBlack );
        hcumfull->SetLineWidth( 2 );
        hcumrk->SetLineWidth( 2 );
        hcumfull->SetLineColor( kCyan );
        TCanvas c{ "c", "c", 400, 400  };
        c.SetLeftMargin( 0.15 );
        c.SetGrid();
        hcumrk->Draw();
        hcumfull->Draw("same");
        c.SetTitle( "");
        hcumrk->SetTitle("");
        hcumrk->GetXaxis()->SetRangeUser( 0.000001 , 0.05 );
        hcumrk->GetXaxis()->SetTitle( "peak half-width (GeV^{2}/c^{4})");
        hcumrk->GetXaxis()->SetTitleOffset(1.1 );
        hcumrk->GetYaxis()->SetTitle("Integrated peak Data/MC ratio");
        hcumrk->GetYaxis()->SetTitleOffset(1.8 );
        hcumrk->GetXaxis()->SetNdivisions( 6 );
        hcumrk->GetYaxis()->SetNdivisions( 6 );
        hcumrk->SetMinimum( 0.99);
        hcumrk->SetMaximum( 1.05 );

        TLegend leg( 0.16, 0.7, 0.29, 0.89 );
        leg.AddEntry( hcumfull, "Signal", "pel" );
        leg.AddEntry( hcumrk, "Loose", "pel" );
        leg.SetLineColor( 0 );
        leg.Draw();

        c.cd();

        std::vector<double> xs = { 0.01, 0.02, 0.02, 0.01, 0.01 };
        std::vector<double> ys = { 0.996, 0.996, 1.004, 1.004, 0.996 };
        TGraph g{ 5, xs.data(), ys.data() };
        g.SetLineColor( kRed );
        g.Draw("same");

        TPad p( "inset", "inset", 0.35, 0.35, 0.89, 0.89 );
        p.Draw();
        p.cd();
        p.SetGrid();

        TH1 *  hcumrk2 = static_cast<TH1*>( hcumrk->Clone( "crk" ) );
        TH1 *  hcumfull2 = static_cast<TH1*>( hcumfull->Clone( "cfull" ) );

        hcumrk2->GetXaxis()->SetRangeUser( 0.010001, 0.02 );
        hcumrk2->GetXaxis()->SetAxisColor(kGray + 2);
        hcumrk2->GetXaxis()->SetNdivisions(5, kTRUE);
        hcumrk2->GetXaxis()->SetTitle("");
        hcumrk2->GetYaxis()->SetAxisColor(kGray + 2);
        hcumrk2->GetYaxis()->SetRangeUser( 0.996, 1.004 );
        hcumrk2->GetXaxis()->SetNdivisions(5, kTRUE);
        hcumrk2->GetYaxis()->SetTitle("");
        hcumrk2->Draw();
        hcumfull2->Draw("same");
        p.Draw();
        c.Update();

        c.Print( "output/neg_cum_rat.pdf", "pdf" );
    }
    {
        auto hcumrk = get_thing<TH1>( tfin, "final/rk/pos/h_cum_rat" );
        auto hcumfull = get_thing<TH1>( tfin, "final/km2_full/pos/h_cum_rat" );
        hcumrk->SetLineColor( kBlack );
        hcumfull->SetLineColor( kCyan );
        hcumfull->SetLineWidth( 2 );
        hcumrk->SetLineWidth( 2 );
        TCanvas c{ "c", "c", 400, 400  };
        c.SetLeftMargin( 0.15 );
        c.SetGrid();
        hcumrk->Draw();
        hcumfull->Draw("same");
        c.SetTitle( "");
        hcumrk->SetTitle("");
        hcumrk->GetXaxis()->SetRangeUser( 0.000001 , 0.05 );
        hcumrk->GetXaxis()->SetTitle( "peak half-width (GeV^{2}/c^{4})");
        hcumrk->GetXaxis()->SetTitleOffset(1.1 );
        hcumrk->GetYaxis()->SetTitle("Integrated peak Data/MC ratio");
        hcumrk->GetYaxis()->SetTitleOffset(1.8 );
        hcumrk->GetXaxis()->SetNdivisions( 6 );
        hcumrk->GetYaxis()->SetNdivisions( 6 );
        hcumrk->SetMinimum( 0.99);
        hcumrk->SetMaximum( 1.05 );
        c.cd();

        TLegend leg( 0.16, 0.7, 0.29, 0.89 );
        leg.AddEntry( hcumfull, "Signal", "pel" );
        leg.AddEntry( hcumrk, "Loose", "pel" );
        leg.SetLineColor( 0 );
        leg.Draw();

        std::vector<double> xs = { 0.01, 0.02, 0.02, 0.01, 0.01 };
        std::vector<double> ys = { 0.997, 0.997, 1.001, 1.001, 0.996 };
        TGraph g{ 5, xs.data(), ys.data() };
        g.SetLineColor( kRed );
        g.Draw("same");

        TPad p( "inset", "inset", 0.35, 0.35, 0.89, 0.89 );
        p.Draw();
        p.cd();
        p.SetGrid();

        TH1 *  hcumrk2 = static_cast<TH1*>( hcumrk->Clone( "crk" ) );
        TH1 *  hcumfull2 = static_cast<TH1*>( hcumfull->Clone( "cfull" ) );

        hcumrk2->GetXaxis()->SetRangeUser( 0.010001, 0.02 );
        hcumrk2->GetXaxis()->SetAxisColor(kGray + 2);
        hcumrk2->GetXaxis()->SetNdivisions(5, kTRUE);
        hcumrk2->GetXaxis()->SetTitle("");
        hcumrk2->GetYaxis()->SetAxisColor(kGray + 2);
        hcumrk2->GetYaxis()->SetRangeUser( 0.997, 1.001 );
        hcumrk2->GetXaxis()->SetNdivisions(5, kTRUE);
        hcumrk2->GetYaxis()->SetTitle("");
        hcumrk2->Draw();
        hcumfull2->Draw("same");
        p.Draw();
        c.Update();

        c.Print( "output/pos_cum_rat.pdf", "pdf" );
    }
}

void cumulative_plots()
{
    do_plot();
}
