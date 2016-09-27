void run()
{
    gStyle->SetOptStat(0);
    TFile tfin( "data/k2pi_shuffle.root" );

    {
        THStack * m2pip_lkr_stack = 0;

        tfin.GetObject( "raw_m2pip_lkr/hnu_stack", m2pip_lkr_stack );

        if ( ! m2pip_lkr_stack )
        { std::cout
            << "Can't find : " <<  "raw_m2pip_lkr/hnu_stack" << std::endl; }

        TCanvas c( "c", "c", 400, 400 );

        m2pip_lkr_stack->Draw();
        m2pip_lkr_stack->GetXaxis()->SetRangeUser( -0.05, 0.15 );
        m2pip_lkr_stack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}");
        m2pip_lkr_stack->GetXaxis()->SetNdivisions( 407 , kTRUE);
        m2pip_lkr_stack->SetMaximum( 2e5 );
        m2pip_lkr_stack->SetMinimum( 20 );
        c.Update();
        c.SetGrid( 1, 1);
        c.SetLogy();


        TList * hlist = m2pip_lkr_stack->GetHists();
        TLegend legd(0.60, 0.57, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K #rightarrow #mu^{+} #pi^{0} #nu_{#mu}", "f"  );

        legd.Draw("same");

        c.SaveAs( "output/raw_m2pip_lkr.pdf", "pdf" );
    }

    {
        THStack * chi2_stack = 0;
        tfin.GetObject( "no_fit_chi2/hnu_stack", chi2_stack );
        if ( ! chi2_stack )
        { std::cout
            << "Can't find : " <<  "no_fit_chi2/hnu_stack" << std::endl; }

        TCanvas c( "c", "c", 400, 400 );

        chi2_stack->Draw();
        chi2_stack->GetXaxis()->SetTitle( "#chi^{2}");
        chi2_stack->GetXaxis()->SetNdivisions( 407 , kTRUE);
        chi2_stack->SetMaximum( 3e5 );
        chi2_stack->SetMinimum( 1 );

        c.Update();
        c.SetGrid( 1, 1);
        c.SetLogy();

        TList * hlist = chi2_stack->GetHists();
        TLegend legd(0.60, 0.67, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K #rightarrow #mu^{+} #pi^{0} #nu_{#mu}", "f"  );

        legd.Draw("same");

        TArrow arrow( 0.5, 3, 0.5, 0.3, 0.03, "|>" );
        arrow.SetLineColor( kWhite );
        arrow.SetFillColor( kWhite );
        arrow.SetFillStyle(1001);
        arrow.SetLineWidth( 4 );
        arrow.Draw();

        c.SaveAs( "output/chi2.pdf", "pdf" );
    }

    {
        THStack * eop_stack = 0;
        tfin.GetObject( "no_fit_eop/hnu_stack", eop_stack );
        if ( ! eop_stack )
        { std::cout
            << "Can't find : " <<  "no_fit_eop/hnu_stack" << std::endl; }

        TCanvas c( "c", "c", 400, 400 );

        eop_stack->Draw();
        eop_stack->GetXaxis()->SetTitle( "E/(|#bf{p}|/c) for track associated to #pi^{+}");
        eop_stack->GetXaxis()->SetNdivisions( 508 , kTRUE);
        eop_stack->SetMaximum( 3e5 );
        eop_stack->SetMinimum( 10 );


        c.Update();
        c.SetGrid( 1, 1);
        c.SetLogy();

        TList * hlist = eop_stack->GetHists();
        TLegend legd(0.60, 0.67, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );

        legd.Draw("same");

        TArrow arrow( 0.9, 30, 0.9, 3, 0.03, "|>" );
        arrow.SetLineColor( kWhite );
        arrow.SetFillColor( kWhite );
        arrow.SetFillStyle(1001);
        arrow.SetLineWidth( 4 );
        arrow.Draw();

        c.SaveAs( "output/eop.pdf", "pdf" );
    }

    {
        int rebin = 5;

        THStack * m2pi0_stack = 0;
        tfin.GetObject( "fit_eop_90_dm2_pi0/hnu_stack", m2pi0_stack );
        if ( ! m2pi0_stack )
        { std::cout
            << "Can't find : " <<  "fit_eop_90_dm2_pi0/hnu_stack" << std::endl; }

        TH1D * hdata =  0;
        tfin.GetObject( "fit_eop_90_dm2_pi0/hdata", hdata );
        if ( ! hdata ) {
            std::cout << "Can't find : " <<  "fit_eop_90_dm2_pi0/hdata" << std::endl; 
        return;
        }
        hdata->Rebin(rebin);

        TCanvas c( "c", "c", 400, 400 );

        TList * hlist = m2pi0_stack->GetHists();
        TIter iter( hlist );
        for( TIter& hit = iter.Begin() ; hit != TIter::End() ; ++hit )
        {
            std::cout << (*hit)->GetName() << std::endl;
            static_cast<TH1*>( *hit )->Rebin(rebin);
        }

        m2pi0_stack->Draw();
        m2pi0_stack->GetXaxis()->SetTitle( "Reconstructed m^{2}_{miss} - m^{2}_{#pi^{0}} (GeV^{2}/c^{4})");
        m2pi0_stack->GetXaxis()->SetTitleOffset(1.2);
        m2pi0_stack->GetXaxis()->SetNdivisions( 508 , kTRUE);
        m2pi0_stack->GetXaxis()->SetRangeUser( -0.2 , 0.15);
        m2pi0_stack->SetMaximum( 3e5 );
        m2pi0_stack->SetMinimum( 1 );

        c.Update();
        c.SetGrid( 1, 1);
        c.SetLogy();

        hdata->Draw("same, E1" );


        TLegend legd(0.60, 0.57, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K #rightarrow #mu^{+} #pi^{0} #nu_{#mu}", "f"  );
        legd.AddEntry( hdata , "data", "lpe"  );

        legd.Draw("same");
        c.SaveAs( "output/m2pi0.pdf", "pdf" );
    }

    {
        int rebin = 2;

        THStack * pt_stack = 0;
        tfin.GetObject( "fit_eop_90_pt/hnu_stack", pt_stack );
        if ( ! pt_stack )
        { std::cout
            << "Can't find : " <<  "fit_eop_90_pt/hnu_stack" << std::endl; }

        TH1D * hdata =  0;
        tfin.GetObject( "fit_eop_90_pt/hdata", hdata );
        if ( ! hdata ) {
            std::cout << "Can't find : " <<  "fit_eop_90_pt/hdata" << std::endl; 
        return;
        }
        hdata->Rebin(rebin);

        TCanvas c( "c", "c", 400, 400 );

        TList * hlist = pt_stack->GetHists();
        TIter iter( hlist );
        for( TIter& hit = iter.Begin() ; hit != TIter::End() ; ++hit )
        {
            std::cout << (*hit)->GetName() << std::endl;
            static_cast<TH1*>( *hit )->Rebin(rebin);
        }

        pt_stack->Draw();
        pt_stack->GetXaxis()->SetTitle( "E/p");
        pt_stack->GetXaxis()->SetTitle( "p_{T}(#pi^{+}) (GeV/c)");
        pt_stack->GetXaxis()->SetNdivisions( 508 , kTRUE);
        pt_stack->SetMaximum( 3e5 );
        pt_stack->SetMinimum( 1 );

        c.Update();
        c.SetGrid( 1, 1);
        c.SetLogy();

        hdata->Draw("same, E1" );


        TLegend legd(0.60, 0.57, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K #rightarrow #pi^{+} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K #rightarrow e^{+} #pi^{0} #nu_{e}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K #rightarrow #pi^{+} #pi^{0} #pi^{0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K #rightarrow #mu^{+} #pi^{0} #nu_{#mu}", "f"  );
        legd.AddEntry( hdata , "data", "lpe"  );

        legd.Draw("same");
        c.SaveAs( "output/pt.pdf", "pdf" );
    }


}

void produce_plots(){ run() ; }
