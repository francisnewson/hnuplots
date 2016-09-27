TH1 *  gl( const THStack* hs, std::string s )
{
    return static_cast<TH1*>( hs->GetHists()->FindObject( s.c_str() ) );
}

void do_plots()
{
    try {
        TFile tfin( "data/k2pi_fit.root");

        TCanvas  c("c", "c", 600, 600 );
        c.SetGrid();
        c.SetLogy();


        //dpop
        THStack * hs_dpop = get_thing<THStack>( tfin, "dpop/feop90_/hnu_stack" );
        TH1 * hdt_dpop = get_hist( tfin, "dpop/feop90_/hdata" );
        TH1 * hbg_dpop = get_hist( tfin, "dpop/feop90_s33_0000_000_08_037/hbg" );



        hs_dpop->Draw();
        hs_dpop->SetMinimum( 0.1 );
        hs_dpop->SetMaximum( 10000 );
        hs_dpop->GetXaxis()->SetRangeUser( -0.4, 0.4 );
        hs_dpop->GetXaxis()->SetTitle( "#Delta p / p ");

        hdt_dpop->Draw("same, E1" );

        hbg_dpop->SetLineColor( kMagenta );
        hbg_dpop->Draw("same" );

        TLegend legd( 0.13, 0.50, 0.33, 0.87);
        //legd.SetTextFont( 133 );
        //legd.SetTextFont( 14 );
        legd.AddEntry( hdt_dpop, "data", "lep" );
        legd.AddEntry( hbg_dpop, "MC (scat)", "l" );
        legd.AddEntry( gl( hs_dpop, "k2pig_pos")  , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( gl( hs_dpop, "ke3_pos")  , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( gl( hs_dpop, "k3pi0_pos")  , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );
        legd.AddEntry( gl( hs_dpop, "km3_pos")  , "K #rightarrow #mu^{+} #pi^{0} #nu_{#mu}", "f"  );

        legd.Draw("same");

        c.Print( "output/k2pi_dpop.pdf", "pdf" );

        //dpx
        THStack * hs_dpx = get_thing<THStack>( tfin, "dpx/feop90_/hnu_stack" );
        TH1 * hdt_dpx = get_hist( tfin, "dpx/feop90_/hdata" );
        TH1 * hbg_dpx = get_hist( tfin, "dpx/feop90_s33_0110_080_00_000/hbg" );

        hs_dpx->Draw();
        hs_dpx->SetMinimum( 0.1 );
        hs_dpx->SetMaximum( 100000 );
        hs_dpx->GetXaxis()->SetRangeUser( -0.2, 0.2 );
        hs_dpx->GetXaxis()->SetTitle("#Delta p_{x} (GeV/c)");

        hdt_dpx->Draw("same, E1" );

        hbg_dpx->SetLineColor( kMagenta );
        hbg_dpx->Draw("same" );

        legd.Draw("same");
        c.Print( "output/k2pi_dpx.pdf", "pdf" );

        //cda
        THStack * hs_cda = get_thing<THStack>( tfin, "cda/feop90_/hnu_stack" );
        TH1 * hdt_cda = get_hist( tfin, "cda/feop90_/hdata" );
        TH1 * hbg_cda = get_hist( tfin, "cda/feop90_s33_0110_080_00_000/hbg" );

        hs_cda->Draw();
        hs_cda->SetMinimum( 10 );
        hs_cda->SetMaximum( 100000 );
        hs_cda->GetXaxis()->SetRangeUser( 0, 6 );
        hs_cda->GetXaxis()->SetTitle( "cda (cm)");

        hdt_cda->Draw("same, E1" );

        hbg_cda->SetLineColor( kMagenta );
        hbg_cda->Draw("same" );

        legd.SetX1NDC( 0.65 );
        legd.SetX2NDC( 0.85 );
        legd.Draw("same");
        c.Print( "output/k2pi_cda.pdf", "pdf" );

        //dpt
        THStack * hs_dpt = get_thing<THStack>( tfin, "dpt/feop90_/hnu_stack" );
        TH1 * hdt_dpt = get_hist( tfin, "dpt/feop90_/hdata" );
        TH1 * hbg_dpt = get_hist( tfin, "dpt/feop90_s33_0000_000_08_037/hbg" );

        hs_dpt->Draw();
        hs_dpt->SetMinimum( 0.1 );
        hs_dpt->SetMaximum( 100000 );
        hs_dpt->GetXaxis()->SetRangeUser( 0, 0.5 );
        hs_dpt->GetXaxis()->SetTitle( "p_{T} (GeV/c)");

        hdt_dpt->Draw("same, E1" );

        hbg_dpt->SetLineColor( kMagenta );
        hbg_dpt->Draw("same" );

        legd.Draw("same");
        c.Print( "output/k2pi_dpt.pdf", "pdf" );

        //dm2_pi0
        THStack * hs_dm2_pi0 = get_thing<THStack>( tfin, "dm2_pi0/feop90_/hnu_stack" );
        TH1 * hdt_dm2_pi0 = get_hist( tfin, "dm2_pi0/feop90_/hdata" );
        TH1 * hbg_dm2_pi0 = get_hist( tfin, "dm2_pi0/feop90_s33_0000_000_08_037/hbg" );

        hs_dm2_pi0->Draw();
        hs_dm2_pi0->SetMinimum( 0.1 );
        hs_dm2_pi0->SetMaximum( 100000 );
        hs_dm2_pi0->GetXaxis()->SetRangeUser( 0.0  -0.05, 0.05 );
        hs_dm2_pi0->GetXaxis()->SetTitle( "( p_{K} - p^{DCH}_{#pi^{+}})^{2} - m_{#pi^{0}}  (GeV^{2}/c^{4})");

        hdt_dm2_pi0->Draw("same, E1" );

        hbg_dm2_pi0->SetLineColor( kMagenta );
        hbg_dm2_pi0->Draw("same" );

        legd.SetX1NDC( 0.13 );
        legd.SetX2NDC( 0.33 );
        legd.Draw("same");
        c.Print( "output/k2pi_dm2_pi0.pdf", "pdf" );
    }
    catch( std::exception& e )
    {
        std::cout << e.what() << std::endl;;
    }
}

void k2pi_plots()
{
    do_plots();
}
