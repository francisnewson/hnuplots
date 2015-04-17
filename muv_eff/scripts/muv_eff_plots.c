TH1 * get_hist( TFile& tf, std::string name )
{
    TH1 * h = 0;
    tf.GetObject( name.c_str(), h );
    if( !h )
    {
        throw std::runtime_error( "Can't find " + name );
    }
    h->SetDirectory(0);
    return h;
}

void muv_eff_plots()
{
    TFile tf ("data/p5.data.q11t.v2.pos_rk_muveff_muv_eff.root");

    TH1 * fail_p_m2m = get_hist( tf, 
            "p5.data.q11t.v2.pos/muv_eff_eop/fail/h_p_m2m_kmu" );

    gStyle->SetPalette( 8 );
    TCanvas c{ "c", "c", 500, 500 };
    gStyle->SetOptStat(11);
    fail_p_m2m->SetName( "FailMUV");
    fail_p_m2m->Draw();
    fail_p_m2m->GetXaxis()->SetRangeUser( -0.1, 0.15 );
    fail_p_m2m->GetYaxis()->SetRangeUser( 5, 70 );

    c.Print( "output/fail_p_m2m.pdf", "pdf" );

    TEfficiency * te_mom = 0;
    tf.GetObject( 
            "p5.data.q11t.v2.pos/muv_eff_eop_peak/eff_mom", te_mom );

    te_mom->Draw();
    c.Print( "output/eff_mom.pdf", "pdf" );

    TEfficiency * te_m2m = 0;
    tf.GetObject( 
            "p5.data.q11t.v2.pos/muv_eff_eop/eff_m2m", te_m2m );

    TH1* h = c.DrawFrame( -0.005, 0.96, 0.005, 0.99 );
    h->GetXaxis()->SetNdivisions( 5 );
    te_m2m->Draw("same");
    c.Print( "output/eff_m2m.pdf", "pdf" );

    h = c.DrawFrame( -2000,  0.96, 10000, 0.99 );
    TEfficiency * te_z = 0;
    tf.GetObject( 
            "p5.data.q11t.v2.pos/muv_eff_eop_peak/eff_z", te_z );
    te_z->Draw("same");
    c.Print( "output/eff_z.pdf", "pdf" );

    TH1 * hzpass = get_hist( tf,
            "p5.data.q11t.v2.pos/muv_eff_eop_peak/pass/h_z" );

    TH1 * hzall = get_hist( tf,
            "p5.data.q11t.v2.pos/muv_eff_eop_peak/all/h_z" );

    hzpass->Rebin(2);
    hzall->Rebin(2);

    TEfficiency te_zw( *hzpass, *hzall );
    h = c.DrawFrame( -2000,  0.96, 10000, 0.99 );
    te_zw.SetTitle( "MUV eff( z )" );
    te_zw.Draw("same");
    c.Print( "output/eff_zw.pdf", "pdf" );

    h = c.DrawFrame( 0,  0.95, 150, 1.0 );
    TEfficiency * te_rmuv = 0;
    tf.GetObject( 
            "p5.data.q11t.v2.pos/muv_eff_eop_peak/eff_rmuv1", te_rmuv );
    te_rmuv->Draw("same");
    c.Print( "output/eff_rmuv.pdf", "pdf" );
}
