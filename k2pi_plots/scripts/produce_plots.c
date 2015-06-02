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
        TLegend legd(0.70, 0.57, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K_{e3}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K_{3#pi0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K_{#mu3}", "f"  );

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
        TLegend legd(0.70, 0.57, 0.87, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "ke3_pos") ) , "K_{e3}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K_{3#pi0}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km3_pos") ) , "K_{#mu3}", "f"  );

        legd.Draw("same");

        c.SaveAs( "output/chi2.pdf", "pdf" );

    }


}
