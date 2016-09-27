double compute_acceptance( TFile& tf, int mass )
{
    TH1 * h_rk_total = get_thing<TH1>( tf, Form("mc.p5.hnu.%d.nodk.pos/rk_like_plots/h_m2m_kmu", mass ) );
    TH1 * h_rk_neg   = get_thing<TH1>( tf, Form("mc.p5.hnu.%d.nodk.neg/rk_like_plots/h_m2m_kmu", mass ) );

    h_rk_total->Add( h_rk_neg );

    TH1 * h_final_total = get_thing<TH1> ( tf, Form("mc.p5.hnu.%d.nodk.pos/signal_upper_plots/h_m2m_kmu", mass) );
    TH1 * h_final_pos_dn = get_thing<TH1>( tf, Form("mc.p5.hnu.%d.nodk.pos/signal_lower_plots/h_m2m_kmu", mass) );
    TH1 * h_final_neg_up = get_thing<TH1>( tf, Form("mc.p5.hnu.%d.nodk.neg/signal_upper_plots/h_m2m_kmu", mass) );
    TH1 * h_final_neg_dn = get_thing<TH1>( tf, Form("mc.p5.hnu.%d.nodk.neg/signal_lower_plots/h_m2m_kmu", mass) );

    h_final_total->Add( h_final_pos_dn );
    h_final_total->Add( h_final_neg_up );
    h_final_total->Add( h_final_neg_dn );

    double rk_integral = h_rk_total->Integral();
    double final_integral = h_final_total->Integral();

    return  final_integral / rk_integral;
}

void halo_acc()
{
    gStyle->SetOptStat(0);

    TFile tf( "data/all.plots.root" );

    TH1 * h_rk_total = get_thing<TH1>( tf, "p6.halo.q11t.pos/rk_like_plots/h_m2m_kmu" );
    TH1 * h_rk_neg = get_thing<TH1>( tf, "p6.halo.q11t.neg/rk_like_plots/h_m2m_kmu" );

    h_rk_total->Add( h_rk_neg );

    TCanvas c( "c", "c", 400, 400 );
    h_rk_total->Rebin(100);
    h_rk_total->Draw();
    c.Print( "output/halo_rk.pdf" );
    c.SetGrid();

    TH1 * h_final_total = get_thing<TH1> ( tf, "p6.halo.q11t.pos/signal_upper_plots/h_m2m_kmu" );
    TH1 * h_final_pos_dn = get_thing<TH1>( tf, "p6.halo.q11t.pos/signal_lower_plots/h_m2m_kmu" );
    TH1 * h_final_neg_up = get_thing<TH1>( tf, "p6.halo.q11t.neg/signal_upper_plots/h_m2m_kmu" );
    TH1 * h_final_neg_dn = get_thing<TH1>( tf, "p6.halo.q11t.neg/signal_lower_plots/h_m2m_kmu" );

    h_final_total->Add( h_final_pos_dn );
    h_final_total->Add( h_final_neg_up );
    h_final_total->Add( h_final_neg_dn );

    h_final_total->Rebin(100);
    h_final_total->Draw();
    c.Print( "output/halo_total.pdf" );

    h_final_total->Sumw2();
    h_rk_total->Sumw2();

    h_final_total->Divide( h_rk_total );
    h_final_total->Draw("E1");
    h_final_total->GetXaxis()->SetRangeUser( 0, 0.16 );
    h_final_total->GetYaxis()->SetTitle( "Fraction of halo remaining" );
    h_final_total->GetYaxis()->CenterTitle();
    h_final_total->GetYaxis()->SetTitleOffset(1.4);
    h_final_total->SetTitle( "" );
    h_final_total->SetMarkerColor( kBlack );
    h_final_total->SetLineColor( kBlack );
    h_final_total->SetLineWidth( 2 );
    c.Print( "output/halo_ratio.pdf" );

    double ack_250 = compute_acceptance(tf, 250 );
    double ack_300 = compute_acceptance(tf, 300 );
    double ack_325 = compute_acceptance(tf, 325 );
    double ack_350 = compute_acceptance(tf, 350 );

    std::cout << 250 << " " << ack_250 << std::endl;
    std::cout << 300 << " " << ack_300 << std::endl;
    std::cout << 325 << " " << ack_325 << std::endl;
    std::cout << 350 << " " << ack_350 << std::endl;

}
