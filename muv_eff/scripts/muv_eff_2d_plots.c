void plot()
{
    TFile * tfdata = new TFile ( "data/p5.data.q11t.v2.pos_rk_muveff_muv_eff.root" );

    TH2D * hall;
    TH2D * hfail;
    TH2D * hpass;

    tfdata->GetObject( "p5.data.q11t.v2.pos/muv_eff_eop_peak_1/fail/h_xy_MUV1", hfail );
    tfdata->GetObject( "p5.data.q11t.v2.pos/muv_eff_eop_peak_1/all/h_xy_MUV1", hall );
    tfdata->GetObject( "p5.data.q11t.v2.pos/muv_eff_eop_peak_1/pass/h_xy_MUV1", hpass );

    if (! hfail  )
    { 
        std::cout << "No hfail" << std::endl;
        return; 
    }

    if (! hall  )
    { 
        std::cout << "No hall" << std::endl;
        return; 
    }


    if (! hpass  )
    { 
        std::cout << "No hpass" << std::endl;
        return; 
    }


//    hfail->Rebin2D(2,2);
//    hall->Rebin2D(2,2);
//    hpass->Rebin2D(2,2);

    TH1D * h1fail = hfail->ProjectionY( "h1fail", hfail->GetXaxis()->FindBin( 20 ), hfail->GetXaxis()->FindBin( 100 ) );
    TH1D * h1all = hall->ProjectionY( "h1all", hall->GetXaxis()->FindBin( 20 ), hall->GetXaxis()->FindBin( 100 ) );
    TH1D * h1pass = hpass->ProjectionY( "h1pass", hpass->GetXaxis()->FindBin( 20 ), hpass->GetXaxis()->FindBin( 100 ) );

    TH1D * h2fail = hfail->ProjectionY( "h1fail", hfail->GetXaxis()->FindBin( -100 ), hfail->GetXaxis()->FindBin( -20 ) );
    TH1D * h2all = hall->ProjectionY( "h1all", hall->GetXaxis()->FindBin( -100 ), hall->GetXaxis()->FindBin( -20 ) );
    TH1D * h2pass = hpass->ProjectionY( "h1pass", hpass->GetXaxis()->FindBin( -100 ), hpass->GetXaxis()->FindBin( -20 ) );

    hfail->Divide( hall );
    hfail->SetContour(100);
    //hfail->Draw("colz");

    TCanvas * c2 = new TCanvas( "c2", "c2" );

    h1fail->Add( h2fail, 1 );
    h1pass->Add( h2pass, 1 );
    h1all->Add( h2all, 1 );

    TH1D * hrat = (TH1D*)h1pass->Clone("hrat");
    hrat->Divide( h1all );

    TEfficiency * teff1 = new TEfficiency( *h1pass, *h1all );
    teff1->Draw("A");

    TCanvas * c3 = new TCanvas( "c3", "c3" );

    hrat->Draw();
    teff1->Draw("same");

    TCanvas * c4 = new TCanvas( "c4", "c4");
    TH1D * hm2m_pass;
    TH1D * hm2m_all;

    tfdata->GetObject( "p5.data.q11t.v2.pos/muv_eff_eop/pass/h_m2m_kmu", hm2m_pass );
    tfdata->GetObject( "p5.data.q11t.v2.pos/muv_eff_eop/all/h_m2m_kmu", hm2m_all );

    hm2m_pass->Rebin( 50 );
    hm2m_all->Rebin( 50 );

    TEfficiency * teff_m2m  = new TEfficiency( *hm2m_pass, *hm2m_all);

    teff_m2m->Draw();
}
