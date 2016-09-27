void de_zero_hist( TH1& h )
{
    int nBins = h.GetNbinsX();

    for ( int ibin = 0 ; ibin != nBins +1 ; ++ ibin )
    {
        double value = h.GetBinContent( ibin );
        if ( value < 0 ){ h.SetBinContent( ibin, 0 );
        }
    }
}
void do_halo_stack()
{
    TFile tf {"data/2015-09-12/all.shuffle_plots.root" };

    //std::string skey = "_loose";
    //std::string sname = "loose";
    std::string skey = "";
    std::string sname = "tgt";

    auto key = skey.c_str();
    auto name = sname.c_str();

    auto hup_pos = get_thing<TH1D>( tf, Form("signal_hc/upper%s/pos/h_m2m_kmu_vis/hnu_stack_hists/halo_pos", key  ) );
    auto hup_neg = get_thing<TH1D>( tf, Form("signal_hc/upper%s/neg/h_m2m_kmu_vis/hnu_stack_hists/halo_neg", key  ) );

    auto hdn_pos = get_thing<TH1D>( tf, Form("signal_hc/lower%s/pos/h_m2m_kmu_vis/hnu_stack_hists/halo_pos", key  ) );
    auto hdn_neg = get_thing<TH1D>( tf, Form("signal_hc/lower%s/neg/h_m2m_kmu_vis/hnu_stack_hists/halo_neg", key  ) );

    hdn_pos->SetFillColor( kGray + 2 );
    hdn_neg->SetFillColor( kGray + 2 );
    hdn_pos->SetLineColor( kGray + 2 );
    hdn_neg->SetLineColor( kGray + 2 );

    de_zero_hist( *hup_pos );
    de_zero_hist( *hup_neg );
    de_zero_hist( *hdn_pos );
    de_zero_hist( *hdn_neg );

    THStack hs;
    hs.Add( hdn_pos );
    hs.Add( hdn_neg );
    hs.Add( hup_pos );
    hs.Add( hup_neg );

    TCanvas c( "c", "c", 700, 400 );
    c.SetGrid();
    hs.Draw();
    hs.GetXaxis()->SetRangeUser( -0.1, 0.16 );
    hs.GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c^{4})");
    hs.GetXaxis()->SetTitleOffset(1.2);
    hs.SetMaximum( 800 );

    TLegend tl( 0.55, 0.55, 0.8, 0.8 );
    tl.AddEntry( hup_pos,"Upper region", "f" );
    tl.AddEntry( hdn_pos,"Lower region", "f" );
    tl.Draw("same");

    TArrow arrow( 0.078, 250, 0.14, 250, 0.03,  "|->" );
    arrow.SetLineColor( kRed );
    arrow.SetLineWidth( 2 );
    arrow.SetFillColor( kRed );
    arrow.SetFillStyle( 1001 );
    arrow.Draw();

    TText tt( 0.078, 310, "Signal region" );
    tt.SetTextColor( kRed );
    tt.Draw("same");

    c.Print( Form("output/halo_stack_%s.pdf", name ), "pdf" );
}

void plot_halo_stack()
{
    do_halo_stack();
}
