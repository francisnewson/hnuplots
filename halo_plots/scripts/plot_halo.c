
void prep( TH1D& h )
{
    h.SetLineColor( kBlack );
    h.Rebin(10);
    h.GetXaxis()->SetRangeUser( -0.2, 0.2 );
    h.GetYaxis()->SetTitle( "" );
    h.SetTitle( "" );
}

void plot_raw_halo()
{
//   std::string skey = "loose_";
//   std::string sfolder = "loose_plots";
    std::string skey = "";
    std::string sfolder = "tgt_plots";
    auto key = skey.c_str();
    auto fol = sfolder.c_str();

    TFile tf{ "data/all.full.root" };

    gStyle->SetOptStat(0);

    TCanvas c("c","c", 400, 400);
    c.SetGrid();

    std::vector<std::pair<std::string, std::string>>  upper_plotlist{ 
        {Form("p6.data.km.q11t.v2.pos/signal_upper_%splots/h_m2m_kmu", key ) , Form("output/%s/raw_halo_up_pos.pdf", fol) },
            { Form("p6.data.km.q11t.v2.neg/signal_upper_%splots/h_m2m_kmu", key) , Form("output/%s/raw_halo_up_neg.pdf", fol) } };

    std::vector<std::pair<std::string, std::string>>  lower_plotlist{ 
        { Form("p6.data.km.q11t.v2.pos/signal_lower_%splots/h_m2m_kmu", key ) , Form("output/%s/raw_halo_dn_pos.pdf", fol ) },
            { Form("p6.data.km.q11t.v2.neg/signal_lower_%splots/h_m2m_kmu", key) , Form("output/%s/raw_halo_dn_neg.pdf", fol ) } 
    };

    std::vector<TH1D*> all_raw_halo;

    for ( const auto plot :  upper_plotlist )
    {
        auto * h = get_thing<TH1D>( tf, plot.first );
        prep( *h );
        h->Draw();
        h->SetMaximum(70);
        c.Print( plot.second.c_str() );
        all_raw_halo.push_back( h );
    }

    for ( const auto plot :  lower_plotlist )
    {
        auto * h = get_thing<TH1D>( tf, plot.first );
        prep( *h );
        h->Draw();
        h->SetMaximum(35);
        c.Print( plot.second.c_str(), "pdf" );
        all_raw_halo.push_back( h );
    }

    auto * htotal = all_raw_halo[0];
    for ( int i = 1 ; i != 4 ; ++ i )
    {
        htotal->Add( all_raw_halo[i] );
    }

    htotal->Draw();
    c.Print( Form("output/%s/raw_halo.pdf", fol ), "pdf" );

    //--------------------------------------------------

    auto hzt_up_pos = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.pos/signal_upper_%splots/h_z_t", key ));
    auto hzt_up_neg = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.neg/signal_upper_%splots/h_z_t", key ));
    auto hzt_dn_pos = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.pos/signal_lower_%splots/h_z_t", key ));
    auto hzt_dn_neg = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.neg/signal_lower_%splots/h_z_t", key ));

    hzt_up_pos->SetMarkerColor( kGray );
    hzt_up_neg->SetMarkerColor( kGray );

    hzt_dn_pos->SetMarkerColor( kGray +2 );
    hzt_dn_neg->SetMarkerColor( kGray +2 );

    hzt_up_pos->SetFillColor( kGray );
    hzt_up_neg->SetFillColor( kGray );

    hzt_dn_pos->SetFillColor( kGray +2 );
    hzt_dn_neg->SetFillColor( kGray +2 );

    gROOT->GetColor( kGray     )->SetAlpha(0.6 );
    gROOT->GetColor( kGray + 2 )->SetAlpha(0.6 );

    hzt_up_pos->SetMarkerSize( 0.5 );
    hzt_up_neg->SetMarkerSize( 0.5);
    hzt_dn_pos->SetMarkerSize( 0.5 );
    hzt_dn_neg->SetMarkerSize( 0.5 );

    hzt_up_pos->SetMarkerStyle( 21 );
    hzt_up_neg->SetMarkerStyle( 21 );
    hzt_dn_pos->SetMarkerStyle( 21 );
    hzt_dn_neg->SetMarkerStyle( 21 );

    c.SetLeftMargin( 0.15 );

    hzt_up_pos->Draw("p");
    hzt_up_pos->GetXaxis()->SetTitle("z (cm)");
    hzt_up_pos->GetYaxis()->SetTitle("#theta (rad)");
    hzt_up_pos->GetYaxis()->SetTitleOffset( 1.8);
    hzt_up_pos->GetYaxis()->CenterTitle();
    hzt_up_pos->SetTitle("");
    hzt_up_pos->GetXaxis()->SetRangeUser( -1500, 7500 );
    hzt_up_pos->GetYaxis()->SetRangeUser( 0 , 0.012 );
    hzt_up_neg->Draw("p,same");
    hzt_dn_pos->Draw("p,same");
    hzt_dn_neg->Draw("p,same");

    TLegend tl( 0.65, 0.65, 0.85, 0.85 );
    tl.AddEntry( hzt_up_pos,"Upper region", "f" );
    tl.AddEntry( hzt_dn_pos,"Lower region", "f" );
    tl.Draw("same");

    c.Print( Form("output/%s/halo_raw_zt.pdf", fol ), "pdf" ); 

    auto h_k3pi_zt_up_pos = get_thing<TH2D>( tf, Form("p6.k3pi.v2.pos/signal_upper_%splots/h_z_t",key ));
    auto h_k3pi_zt_up_neg = get_thing<TH2D>( tf, Form("p6.k3pi.v2.neg/signal_upper_%splots/h_z_t",key ));
    auto h_k3pi_zt_dn_pos = get_thing<TH2D>( tf, Form("p6.k3pi.v2.pos/signal_lower_%splots/h_z_t",key ));
    auto h_k3pi_zt_dn_neg = get_thing<TH2D>( tf, Form("p6.k3pi.v2.neg/signal_lower_%splots/h_z_t",key ));

    h_k3pi_zt_up_pos->SetMarkerColor( kOrange + 9 );
    h_k3pi_zt_up_neg->SetMarkerColor( kOrange + 9 );
    h_k3pi_zt_dn_pos->SetMarkerColor( kOrange + 9 );
    h_k3pi_zt_dn_neg->SetMarkerColor( kOrange + 9 );

    h_k3pi_zt_up_pos->SetFillColor( kOrange + 9 );
    h_k3pi_zt_up_neg->SetFillColor( kOrange + 9 );
    h_k3pi_zt_dn_pos->SetFillColor( kOrange + 9 );
    h_k3pi_zt_dn_neg->SetFillColor( kOrange + 9 );

    h_k3pi_zt_up_pos->SetMarkerSize( 0.1 );
    h_k3pi_zt_up_neg->SetMarkerSize( 0.1);
    h_k3pi_zt_dn_pos->SetMarkerSize( 0.1 );
    h_k3pi_zt_dn_neg->SetMarkerSize( 0.1 );

    h_k3pi_zt_up_pos->SetMarkerStyle( 21 );
    h_k3pi_zt_up_neg->SetMarkerStyle( 21 );
    h_k3pi_zt_dn_pos->SetMarkerStyle( 21 );
    h_k3pi_zt_dn_neg->SetMarkerStyle( 21 );


    h_k3pi_zt_up_pos->Draw("p");
    h_k3pi_zt_up_pos->GetXaxis()->SetTitle("z (cm)");
    h_k3pi_zt_up_pos->GetYaxis()->SetTitle("#theta (rad)");
    h_k3pi_zt_up_pos->GetYaxis()->SetTitleOffset( 1.8);
    h_k3pi_zt_up_pos->GetYaxis()->CenterTitle();
    h_k3pi_zt_up_pos->SetTitle("");
    h_k3pi_zt_up_pos->GetXaxis()->SetRangeUser( -1500, 7500 );
    h_k3pi_zt_up_pos->GetYaxis()->SetRangeUser( 0 , 0.012 );
    h_k3pi_zt_up_neg->Draw("p,same");
    h_k3pi_zt_dn_pos->Draw("p,same");
    h_k3pi_zt_dn_neg->Draw("p,same");

    TLegend tl2( 0.55, 0.75, 0.85, 0.85 );
    tl2.AddEntry( h_k3pi_zt_up_pos, "K^{+} #rightarrow #pi^{+} #pi^{+} #pi^{-}", "f" );
    tl2.Draw("same");


    c.Print( Form("output/%s/k3pi_raw_zt.pdf", fol ), "pdf" ); 

    auto hpm2m_up_pos = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.pos/signal_upper_%splots/h_p_m2m_kmu", key ));
    auto hpm2m_up_neg = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.neg/signal_upper_%splots/h_p_m2m_kmu", key ));
    auto hpm2m_dn_pos = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.pos/signal_lower_%splots/h_p_m2m_kmu", key ));
    auto hpm2m_dn_neg = get_thing<TH2D>( tf, Form("p6.data.km.q11t.v2.neg/signal_lower_%splots/h_p_m2m_kmu", key ));

    hpm2m_up_pos->SetMarkerSize( 0.2 );
    hpm2m_up_neg->SetMarkerSize( 0.2);
    hpm2m_dn_pos->SetMarkerSize( 0.2 );
    hpm2m_dn_neg->SetMarkerSize( 0.2 );

    hpm2m_up_pos->SetMarkerStyle( 21 );
    hpm2m_up_neg->SetMarkerStyle( 21);
    hpm2m_dn_pos->SetMarkerStyle( 21 );
    hpm2m_dn_neg->SetMarkerStyle( 21 );

    hpm2m_up_pos->Draw("p");
    hpm2m_up_pos->GetXaxis()->SetRangeUser( -0.1, 0.2 );
    hpm2m_up_pos->GetYaxis()->SetRangeUser( 0, 70 );
    hpm2m_up_pos->GetYaxis()->SetTitleOffset( 1.6 );
    hpm2m_up_pos->GetYaxis()->CenterTitle();
    hpm2m_up_pos->SetTitle( "" );
    hpm2m_up_neg->Draw("p,same");
    hpm2m_dn_pos->Draw("p,same");
    hpm2m_dn_neg->Draw("p,same");

    c.Print( Form("output/%s/raw_halo_pm2m.pdf", fol ), "pdf" ); 
}

void plot_halo()
{
    plot_raw_halo();
}

