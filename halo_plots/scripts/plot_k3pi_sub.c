void do_k3pi_plots()
{

    //./build_bham/apps/shuffle -m input/shuffle/thesis/halo/halo_k3pi_crosstalk.yaml -o tdata/staging/k3pi_crosstalk/all.shuffle_plots.root
    //./build_bham/apps/halo_subtract -m input/halo_sub/hsub.full.yaml -o tdata/staging/full/halo_sub.root -l tdata/staging/full/log_halo_sub.root

    /*
     *  ____  _             _            _       _
     * / ___|| |_ __ _  ___| | __  _ __ | | ___ | |_ ___
     * \___ \| __/ _` |/ __| |/ / | '_ \| |/ _ \| __/ __|
     *  ___) | || (_| | (__|   <  | |_) | | (_) | |_\__ \
     * |____/ \__\__,_|\___|_|\_\ | .__/|_|\___/ \__|___/
     *                            |_|
     *
     */

    //std::string selection = "signal_loose";
    std::string selection = "signal";
    auto sel = selection.c_str();

    //std::string outfolder = "k3pi_sub";
    std::string outfolder = "k3pi_sub_tgt";
    auto fol = outfolder.c_str();

    //std::string selkey = "loose_";
    std::string selkey = "";
    auto key = selkey.c_str();

    {
        TFile tf{ "data/k3pi_sub/all.shuffle_plots.root" };

        TCanvas c{ "c", "c", 400, 400 };
        c.SetGrid();

        //Bad P5
        {
            auto hstack  = get_thing<THStack>( tf, Form("p5km2kp/neg/%s_upper_plots/hm2m/hnu_stack", sel) );
            auto hdata = get_thing<TH1D>( tf, Form("p5km2kp/neg/%s_upper_plots/hm2m/hdata", sel ) );
            hstack->Draw();
            hstack->GetXaxis()->SetRangeUser( -0.1999, 0.2 );
            hstack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}");
            hstack->SetMaximum( 4500 );
            gPad->Update();
            hdata->SetLineColor( kBlack );
            hdata->SetLineWidth( 2 );
            hdata->Draw("same, E1" );
            TLegend tl{0.2, 0.5, 0.5, 0.7};
            tl.AddEntry( hdata, "K^{+} data", "pel" );
            tl.AddEntry( hstack->GetHists()->At(0), "K_{less} data", "f" );
            tl.AddEntry( hstack->GetHists()->At(1), "K^{+} #rightarrow #pi^{+} #pi^{+} #pi^{-}", "f" );
            tl.Draw("same");
            c.Print( Form("output/%s/bad_p5.pdf", fol), "pdf" );
        }

        //Good P5
        {
            auto hstack  = get_thing<THStack>( tf, Form("p5k3pikp/neg/%s_upper_plots/hm2m/hnu_stack", sel) );
            auto hdata = get_thing<TH1D>( tf, Form("p5k3pikp/neg/%s_upper_plots/hm2m/hdata", sel ) );
            hstack->Draw();
            hstack->GetXaxis()->SetRangeUser( -0.1999, 0.2 );
            hstack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}");
            hstack->SetMaximum( 4500 );
            gPad->Update();
            hdata->SetLineColor( kBlack );
            hdata->SetLineWidth( 2 );
            hdata->Draw("same, E1" );
            TLegend tl{0.2, 0.5, 0.5, 0.7};
            tl.AddEntry( hdata, "K^{+} data", "pel" );
            tl.AddEntry( hstack->GetHists()->At(0), "K_{less} data", "f" );
            tl.AddEntry( hstack->GetHists()->At(1), "K^{+} #rightarrow #pi^{+} #pi^{+} #pi^{-}", "f" );
            tl.Draw("same");
            c.Print( Form("output/%s/good_p5.pdf", fol ), "pdf" );
        }

        //Good P6 upper
        {
            auto hstack  = get_thing<THStack>( tf, Form("p6k3pikp/pos/%s_upper_plots/hm2m/hnu_stack", sel ) );
            auto hdata = get_thing<TH1D>( tf, Form("p6k3pikp/pos/%s_upper_plots/hm2m/hdata", sel) );
            hstack->Draw();
            hstack->GetXaxis()->SetRangeUser( -0.1999, 0.2 );
            hstack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}");
            hstack->SetMaximum( 350 );
            gPad->Update();
            hdata->SetLineColor( kBlack );
            hdata->SetLineWidth( 2 );
            hdata->Draw("same, E1" );
            TLegend tl{0.15, 0.55, 0.45, 0.75};
            tl.AddEntry( hdata, "K^{-} data", "pel" );
            tl.AddEntry( hstack->GetHists()->At(0), "K_{less} data", "f" );
            tl.AddEntry( hstack->GetHists()->At(1), "K^{-} #rightarrow #pi^{-} #pi^{-} #pi^{+}", "f" );
            tl.Draw("same");
            c.Print( Form("output/%s/good_p6_upper.pdf", fol), "pdf" );
        }
        //Good P6 lower
        {
            auto hstack  = get_thing<THStack>( tf, Form("p6k3pikp/pos/%s_lower_plots/hm2m/hnu_stack", sel) );
            auto hdata = get_thing<TH1D>( tf, Form("p6k3pikp/pos/%s_lower_plots/hm2m/hdata", sel) );
            hstack->Draw();
            hstack->GetXaxis()->SetRangeUser( -0.1999, 0.2 );
            hstack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}");
            hstack->SetMaximum( 150 );
            gPad->Update();
            hdata->SetLineColor( kBlack );
            hdata->SetLineWidth( 2 );
            hdata->Draw("same, E1" );
            TLegend tl{0.15, 0.55, 0.45, 0.75};
            tl.AddEntry( hdata, "K^{-} data", "pel" );
            tl.AddEntry( hstack->GetHists()->At(0), "K_{less} data", "f" );
            tl.AddEntry( hstack->GetHists()->At(1), "K^{-} #rightarrow #pi^{-} #pi^{-} #pi^{+}", "f" );
            tl.Draw("same");
            c.Print( Form("output/%s/good_p6_lower.pdf", fol), "pdf" );
        }
    }

    //--------------------------------------------------

#if 0
    /*
     *  ____        _             _       _
     * / ___| _   _| |__    _ __ | | ___ | |_ ___
     * \___ \| | | | '_ \  | '_ \| |/ _ \| __/ __|
     *  ___) | |_| | |_) | | |_) | | (_) | |_\__ \
     * |____/ \__,_|_.__/  | .__/|_|\___/ \__|___/
     *                     |_|
     *
     */
#endif

    {
        TFile tf{ "data/k3pi_sub/log_halo_sub.root" };

        TCanvas c{ "c", "c", 400, 400 };
        c.SetGrid();
        gStyle->SetOptStat(0);

        std::vector<std::pair<std::string, std::string>>  plots {
            { Form("p6.halo.q11t.pos/signal_upper_%splots/h_m2m_kmu", key) , "k3pi_sub_upper_pos" },
                { Form("p6.halo.q11t.neg/signal_upper_%splots/h_m2m_kmu", key) , "k3pi_sub_upper_neg" },
                { Form("p6.halo.q11t.pos/signal_lower_%splots/h_m2m_kmu", key) , "k3pi_sub_lower_pos" },
                { Form("p6.halo.q11t.neg/signal_lower_%splots/h_m2m_kmu", key) , "k3pi_sub_lower_neg" }
        };

        std::vector<TH1D*> hraws;
        std::vector<TH1D*> hcorrs;

        for ( auto plot :  plots )
        {
            auto hraw = get_thing<TH1D>( tf, Form( "%s/hraw", plot.first.c_str() ) );
            auto hcorr = get_thing<TH1D>( tf, Form( "%s/hcorr", plot.first.c_str() ) );


            hraw->Rebin(20);
            hcorr->Rebin(20);

            hraw->SetTitle( "" );
            hraw->GetYaxis()->SetTitle( "" );
            hraw->SetLineColor( kGray  );
            //hraw->SetLineStyle( kDashed );
            hraw->SetLineWidth( 6 );
            hraw->Draw();
            hraw->GetXaxis()->SetRangeUser( -0.1, 0.2 );
            hraw->GetYaxis()->SetRangeUser( -10, 60 ); 

            hcorr->SetMarkerColor( kBlack );
            hcorr->SetLineColor( kBlack );
            hcorr->SetLineWidth( 2 );
            hcorr->Draw("same, E1");

            c.Print( Form("output/%s/corr_%s.pdf", fol, plot.second.c_str() ), "pdf" );

            hraws.push_back( static_cast<TH1D*>(hraw->Clone() ) );
            hcorrs.push_back( static_cast<TH1D*>(hcorr->Clone() ) );
        }

        std::cout << hraws.size() <<  std::endl;

        auto * hrawtotal = hraws[0];
        auto * hcorrtotal = hcorrs[0];
        for ( int i = 1; i != 4 ; ++i )
        {
            hrawtotal->Add( hraws[i] );
            hcorrtotal->Add( hcorrs[i] );
        }

        hrawtotal->Draw();
        hrawtotal->GetYaxis()->SetRangeUser( 0, 200 );
        hcorrtotal->Draw("same, E1");
        TLegend tl{ 0.50, 0.65, 0.85, 0.83 };
        tl.AddEntry( hrawtotal, "Raw K^{-} data", "f" );
        tl.AddEntry( hcorrtotal, "K^{-} after MC subtraction", "pel" );
        tl.Draw("same");
        c.Print(Form("output/%s/corr_all.pdf", fol ), "pdf" );

        hrawtotal->SetLineWidth(1);
        hrawtotal->GetXaxis()->SetRangeUser(-0.2, 0.2);
        hrawtotal->GetYaxis()->SetRangeUser(0, 180);
        hrawtotal->SetLineColor(kBlack);
        hrawtotal->Draw();
        c.Print( Form("output/%s/raw_all.pdf", fol ), "pdf" );
    }

}

void plot_k3pi_sub()
{
    do_k3pi_plots();
}
