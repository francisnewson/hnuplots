TH1 *  gl( const THStack* hs, std::string s )
{
    TObject * res = hs->GetHists()->FindObject( s.c_str() ) ;
    if ( ! res )
    {
        throw std::runtime_error( "Can't find " + s + " in " + hs->GetName() );
    }
    return static_cast<TH1*>(res);
}

void plot_spectrum( std::string input, std::string output )
{
    gStyle->SetOptStat(0);
    TFile tf{ "data/2015-09-22/all.merge_plots.root"};

    TCanvas c{ "c", "c", 600, 500 };
    c.SetGrid();


    //BG stack
    {
        auto bgstack = get_thing<THStack>( tf, Form( "final_hc%s/full_mvis/hstack", input.c_str() ) );
        bgstack->Draw();
        bgstack->GetXaxis()->SetRangeUser( -0.02, 0.16 );
        bgstack->GetXaxis()->SetTitle("m^{2}_{miss} GeV^{2} /c^{4}");
        bgstack->SetMaximum( 600 );

        TLegend tl{ 0.45, 0.65, 0.85, 0.85 };
        tl.SetNColumns(2);
        tl.AddEntry( gl( bgstack , "km2_pos") ,"K^{+} #rightarrow #mu #nu_{#mu}", "f" );
        tl.AddEntry( gl( bgstack , "k2pi_pos") ,"K^{+} #rightarrow #pi^{+} #pi^{0}", "f" );
        tl.AddEntry( gl( bgstack , "k3pi_pos") ,"K^{+} #rightarrow #pi^{+} #pi^{+} #pi^{-}", "f" );
        tl.AddEntry( gl( bgstack , "k3pi0_pos") ,"K^{+} #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f" );
        tl.AddEntry( gl( bgstack , "km3_pos") ,"K^{+} #rightarrow #mu^{+} #pi^{0} #nu", "f" );
        tl.AddEntry( gl( bgstack, "halo_pos" ), "halo", "f" );

        tl.Draw("same" );
        c.Print( Form("output/2015-09-14_%s/stack.pdf", output.c_str()), "pdf" );


        TCanvas d( "d", "d", 100, 100 );
        TFile tfhnu( "data/2015-09-22/heavy_acc.root" );
        std::vector<int> masses { 270, 290, 310, 330, 350, 370 };
        TH1D * hwgt = new TH1D( "hwgt", "hwgt", 1, 0, 100000 );

        TH1D * hbg = (TH1D*)(bgstack->GetStack()->Last()->Clone() );
        hbg->Print();

        for(  auto mass : masses )
        {
            d.cd();
            auto  * w = get_thing<TTree>( tfhnu,  Form( "mc.p5.hnu.%03d.nodk.pos/sample_burst_count/bursts", mass ) );
            hwgt->Reset();
            w->Draw("events>>hwgt", "weight", "Q" );

            double total_weight = hwgt->GetSumOfWeights();
            auto * hup = get_thing<TH1D>( tfhnu, Form("mc.p5.hnu.%03d.nodk.pos/signal_upper_plots/h_m2m_kmu", mass) );
            auto * hdn = get_thing<TH1D>( tfhnu, Form("mc.p5.hnu.%03d.nodk.pos/signal_lower_plots/h_m2m_kmu", mass) );

            hup->Add( hdn );

            hup->Scale( 6e7 / total_weight * 1e-4 );
            hup->Rebin( 5 );

            //c.cd();
            //hup->Draw("same" );
            hup->SetLineColor( kBlack );
            hup->SetLineWidth(2);
            hup->SetFillColor( kMagenta );
            //hup->SetFillStyle( 1 );
            bgstack->Add( hup );
        }

        TCanvas c_log{ "c", "c", 800, 500 };
        c_log.SetGrid();
        c_log.SetLogy();


        TLegend tl2{ 0.45, 0.58, 0.80, 0.65 };
        tl2.SetLineWidth(0);
        tl2.AddEntry( gl( bgstack, "h_m2m_kmu" ), "Heavy neutrino signals with BR = 1x10^{-4}", "f" );
        //tl.Draw("same" );
        //tl2.Draw("same" );

        std::cout << "About to draw bgstack" << std::endl;
        bgstack->Draw();
        std::cout << "Drew bgstack" << std::endl;
        bgstack->SetMaximum( 590000 );
        bgstack->SetMinimum( 60 );
        bgstack->GetXaxis()->SetRangeUser( -0.02, 0.16 );
        bgstack->GetXaxis()->SetTitle("m^{2}_{miss} GeV^{2}/c^{4}");
        bgstack->GetYaxis()->SetRangeUser( 60, 70000000);
        std::cout << "About to draw bgstack again" << std::endl;
        bgstack->Draw();
        std::cout << "Drew bgstack again" << std::endl;

        hbg->SetLineColor( kBlue +2  );
        hbg->SetLineWidth( 2  );
        hbg->SetFillColor( kBlue + 2 );
        hbg->Draw("same");

        c_log.Print( Form("output/2015-09-14_%s/log_stack.pdf", output.c_str()), "pdf" );
        c_log.Print( Form("output/2015-09-14_%s/log_stack.eps", output.c_str()), "eps" );
        c_log.Print( Form("output/2015-09-14_%s/log_stack.png", output.c_str()), "png" );

    }


    //BG DT comp
    {
        auto hbgerr = get_thing<TH1D> ( tf, Form( "final_hc%s/full_mvis/hbg_err", input.c_str() ) );
        auto hdt = get_thing<TH1D> ( tf, Form( "final_hc%s/full_mvis/hdata", input.c_str() ) );

        hbgerr->SetTitle("");
        hbgerr->SetFillColor( kViolet + 5 );
        hbgerr->SetMarkerColor( kViolet + 6 );
        gROOT->GetColor( kViolet + 5 )->SetAlpha(0.3 );
        hbgerr->SetFillStyle( 1001 );
        hbgerr->Draw("E2");

        hbgerr->GetXaxis()->SetRangeUser( 0.06, 0.16 );
        hbgerr->GetYaxis()->SetRangeUser( 0, 400 );
        hbgerr->GetYaxis()->SetTitle("");

        hdt->SetLineColor( kBlack );
        hdt->Draw("E1,same");

        TLegend tl{ 0.15, 0.15, 0.4, 0.4 };
        tl.AddEntry( hbgerr, "Background", "f" );
        tl.AddEntry( hdt, "Data", "pel" );
        tl.Draw("same");
        c.Print( Form( "output/2015-09-14_%s/bgcomp.pdf", output.c_str() ), "pdf" );

        tl.SetX1NDC( 0.6 );
        tl.SetX2NDC( 0.85 );
        tl.SetY1NDC( 0.6 );
        tl.SetY2NDC( 0.85 );
        hdt->SetLineWidth(1);
        hdt->SetMarkerSize(0.5);
        hbgerr->GetXaxis()->SetRangeUser( 0.00, 0.16 );
        hbgerr->GetYaxis()->SetRangeUser( 10, 1e6 );
        hbgerr->Draw("E2");
        hdt->Draw("E1,same");
        tl.Draw("same");
        c.SetLogy();
        gPad->Update();
        c.Print( Form( "output/2015-09-14_%s/bgcomp_log.pdf", output.c_str() ), "pdf" );


    }

    //BG DT ratio
    {
        c.SetLogy(0);
        auto hrat = get_thing<TH1D>( tf, Form( "final_hc%s/full_mvis/h_err_ratio", input.c_str() ) );
        hrat->Draw("E1");
        hrat->GetXaxis()->SetRangeUser( 0.06, 0.16 );
        hrat->GetYaxis()->SetRangeUser( 0, 2 );

        hrat->SetTitle("");
        hrat->GetYaxis()->SetTitle("data / background estimate" );

        c.Print( Form( "output/2015-09-14_%s/rat.pdf", output.c_str() ), "pdf" );
    }

}

void spectrum()
{
    plot_spectrum( "", "loose" );
    plot_spectrum( "_tgt", "tgt" );
}
