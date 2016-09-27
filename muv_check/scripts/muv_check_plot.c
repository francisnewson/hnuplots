struct plt
{
    TGraphAsymmErrors * dt;
    TGraphAsymmErrors * mc;
    TGraphAsymmErrors * resid;
};

plt load( TFile& tf, std::string name )
{
    std::string dts = "data/muv_eff_check/" + name;
    std::string mcs = "mc/muv_eff_check/" + name;
    std::string res = "diffs/" + name;

    plt result;
    result.dt = get_thing<TGraphAsymmErrors>(  tf, dts );
    result.mc = get_thing<TGraphAsymmErrors>(  tf, mcs );
    result.resid = get_thing<TGraphAsymmErrors>(  tf, res );
    result.dt->SetTitle("");
    result.mc->SetTitle("");
    result.resid->SetTitle("");
    return result;
}

void prep( plt p )
{
    p.dt->GetYaxis()->SetLabelSize( 0.06 );
    p.dt->GetYaxis()->SetNdivisions( 104 );
    p.dt->GetYaxis()->SetTitleSize( 0.08 );
    p.dt->GetYaxis()->CenterTitle();
    p.dt->GetYaxis()->SetTitleOffset(0.75);
    p.mc->SetMarkerColor( kCyan + 1);
    p.mc->SetMarkerStyle( 21);
    p.mc->SetMarkerSize( 0.2);
    p.resid->GetXaxis()->SetTitleSize( 0.06 );
    p.resid->GetXaxis()->SetLabelSize( 0.06 );
    p.resid->GetYaxis()->SetLabelSize( 0.06 );
    p.resid->GetYaxis()->SetNdivisions( 104 );
    p.resid->GetYaxis()->SetTitleSize( 0.08 );
    p.resid->GetYaxis()->CenterTitle();
    p.resid->GetYaxis()->SetTitleOffset(0.75);
    p.dt->GetYaxis()->SetTitle( "eff" );
    p.resid->GetYaxis()->SetTitle( "#Delta eff" );
}


void do_plots()
{
    TFile tf ( "data/muv_check.root" );


    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt m2m = load( tf, "h_m2m" );
        prep( m2m );

        //------- m2m ----------
        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        m2m.dt->Draw("ap");
        m2m.mc->Draw("same,P");

        TLegend leg( 0.5, 0.15, 0.65, 0.35 );
        leg.AddEntry( m2m.dt, "data", "pel" );
        leg.AddEntry( m2m.mc, "MC", "pel" );
        leg.Draw("same");

        gPad->SetGrid();

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        m2m.resid->SetMinimum( -0.0025 );
        m2m.resid->SetMaximum( +0.0025 );
        m2m.resid->GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c^{4})" );

        m2m.resid->Draw("ap");

        gPad->SetGrid();
        c.Print( "output/m2m.pdf", "pdf" );
    }

    //--------------------------------------------------

    //------- p ----------

    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt p = load( tf, "h_p" );
        prep( p );

        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        p.dt->Draw("ap");
        p.mc->Draw("same,P");
        gPad->SetGrid();

        TLegend leg( 0.2, 0.15, 0.35, 0.35 );
        leg.AddEntry( p.dt, "data", "pel" );
        leg.AddEntry( p.mc, "MC", "pel" );
        leg.Draw("same");

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        p.resid->GetXaxis()->SetTitle( "momentum (GeV/c)" );
        p.resid->Draw("ap");
        gPad->SetGrid();
        c.Print( "output/p.pdf", "pdf" );
    }

    //--------------------------------------------------

    //------- t ----------

    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt t = load( tf, "h_t" );
        prep( t );

        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        t.dt->Draw("ap");
        t.mc->Draw("same,P");
        gPad->SetGrid();

        TLegend leg( 0.6, 0.15, 0.75, 0.35 );
        leg.AddEntry( t.dt, "data", "pel" );
        leg.AddEntry( t.mc, "MC", "pel" );
        leg.Draw("same");

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        t.resid->SetMinimum( -0.02 );
        t.resid->SetMaximum( +0.02 );

        t.resid->GetXaxis()->SetTitle( "kaon - muon angle (rad)" );
        t.resid->Draw("ap");
        gPad->SetGrid();
        c.Print( "output/t.pdf", "pdf" );
    }

    //------- z ----------

    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt z = load( tf, "h_z" );
        prep( z );

        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        z.dt->Draw("ap");
        z.mc->Draw("same,P");
        gPad->SetGrid();

        TLegend leg( 0.6, 0.15, 0.75, 0.35 );
        leg.AddEntry( z.dt, "data", "pel" );
        leg.AddEntry( z.mc, "MC", "pel" );
        leg.Draw("same");

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        z.resid->GetXaxis()->SetTitle( " vertex z (cm)" );
        z.resid->Draw("ap");
        gPad->SetGrid();
        c.Print( "output/z.pdf", "pdf" );
    }

    //------- r ----------

    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt r = load( tf, "h_rmuv" );
        prep( r );

        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        r.dt->Draw("ap");
        r.mc->Draw("same,P");
        gPad->SetGrid();

        TLegend leg( 0.6, 0.15, 0.75, 0.35 );
        leg.AddEntry( r.dt, "data", "pel" );
        leg.AddEntry( r.mc, "MC", "pel" );
        leg.Draw("same");

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        r.resid->SetMinimum( -0.022 );
        r.resid->SetMaximum( +0.022 );

        r.resid->GetXaxis()->SetTitle( "radius at MUV 1(cm)" );
        r.resid->Draw("ap");
        gPad->SetGrid();
        c.Print( "output/r.pdf", "pdf" );
    }

    //------- r ----------

    {
        TCanvas c( "c", "c", 300, 300 );
        c.Divide( 1, 2, 0 , 0 );
        plt phi = load( tf, "h_phi" );
        prep( phi );

        c.cd(1);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        phi.dt->Draw("ap");
        phi.mc->Draw("same,P");
        gPad->SetGrid();

        TLegend leg( 0.6, 0.15, 0.75, 0.35 );
        leg.AddEntry( phi.dt, "data", "pel" );
        leg.AddEntry( phi.mc, "MC", "pel" );
        leg.Draw("same");

        c.cd(2);
        gPad->SetLeftMargin( 0.15 );
        gPad->SetRightMargin( 0.05 );
        gPad->SetBottomMargin( 0.18 );

        phi.resid->SetMinimum( -0.012 );
        phi.resid->SetMaximum( +0.012 );

        phi.resid->GetXaxis()->SetTitle( "track #phi angle (rad)" );
        phi.resid->Draw("ap");
        gPad->SetGrid();
        c.Print( "output/phi.pdf", "pdf" );
    }
}

void muv_check_plot(){ do_plots(); }
