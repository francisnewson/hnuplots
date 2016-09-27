void do_plot()
{
    TFile tf( "data/halo_k3pi_crosstalk.q11t.root" );

    TCanvas c( "c", "c", 600, 400 );
    c.SetGrid();

    //do p5 k3pi scaling
    {
        THStack * hstack = get_thing<THStack>( tf , "k3pi_p5/hm2m/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "k3pi_p5/hm2m/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(1600);
        hstack->GetXaxis()->SetRangeUser( -0.1, 0.2 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^2/c^4)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.2, 0.6, 0.45, 0.8 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_neg") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_neg") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{-} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p5_k3pi_scale_m2m.pdf", "pdf" );
    }

    {
        THStack * hstack = get_thing<THStack>( tf , "k3pi_p5/hp/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "k3pi_p5/hp/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(5000);
        hstack->GetXaxis()->SetRangeUser( 0, 70 );
        hstack->GetXaxis()->SetTitle( "p (GeV/c)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.2, 0.6, 0.45, 0.8 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_neg") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_neg") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{-} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p5_k3pi_scale_p.pdf", "pdf" );
    }

    //do p5 km2 scaling
    {
        THStack * hstack = get_thing<THStack>( tf , "rk_minus_p5/hm2m/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "rk_minus_p5/hm2m/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(1600);
        hstack->GetXaxis()->SetRangeUser( -0.1, 0.2 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^2/c^4)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.2, 0.6, 0.45, 0.8 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_neg") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{-} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p5_km2_scale_m2m.pdf", "pdf" );
    }

    {
        THStack * hstack = get_thing<THStack>( tf , "rk_minus_p5/hp/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "rk_minus_p5/hp/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(5000);
        hstack->GetXaxis()->SetRangeUser( 0, 70 );
        hstack->GetXaxis()->SetTitle( "p (GeV/c)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.35, 0.65, 0.60, 0.85 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_neg") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{-} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p5_km2_scale_p.pdf", "pdf" );
    }

    //do p6 k3pi scaling
    {
        THStack * hstack = get_thing<THStack>( tf , "k3pi_p6/hm2m/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "k3pi_p6/hm2m/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(420);
        hstack->GetXaxis()->SetRangeUser( -0.1, 0.2 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^2/c^4)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.35, 0.65, 0.60, 0.85 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_pos") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{+} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p6_k3pi_scale_m2m.pdf", "pdf" );
    }

    {
        THStack * hstack = get_thing<THStack>( tf , "k3pi_p6/hp/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "k3pi_p6/hp/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(1000);
        hstack->GetXaxis()->SetRangeUser( 0, 70 );
        hstack->GetXaxis()->SetTitle( "p (GeV/c)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.35, 0.65, 0.60, 0.85 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_pos") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{+} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p6_k3pi_scale_p.pdf", "pdf" );
    }

    //do p6 km2 scaling
    {
        THStack * hstack = get_thing<THStack>( tf , "rk_minus_p6/hm2m/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "rk_minus_p6/hm2m/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(420);
        hstack->GetXaxis()->SetRangeUser( -0.1, 0.2 );
        hstack->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^2/c^4)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.25, 0.65, 0.50, 0.85 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_pos") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{+} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p6_km2_scale_m2m.pdf", "pdf" );
    }

    {
        THStack * hstack = get_thing<THStack>( tf , "rk_minus_p6/hp/hnu_stack");
        TH1 * dt = get_thing<TH1>( tf , "rk_minus_p6/hp/hdata");

        hstack->Draw();
        hstack->SetMinimum(0);
        hstack->SetMaximum(1000);
        hstack->GetXaxis()->SetRangeUser( 0, 70 );
        hstack->GetXaxis()->SetTitle( "p (GeV/c)" );
        dt->SetLineColor( kBlack );
        dt->Draw( "same, E1" );

        TList * hlist = hstack->GetHists();
        hlist->Print();
        TLegend tl( 0.25, 0.65, 0.50, 0.85 );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_kless_pos") ), "Kless halo data", "f" );
        tl.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi_pos") ), "K_{3#pi}", "f" );
        tl.AddEntry( dt, "K^{+} halo data", "pel" );
        tl.Draw("same");

        c.Print( "output/p6_km2_scale_p.pdf", "pdf" );
    }
}

void plot(){ do_plot(); }
