void plot()
{
    gStyle->SetOptStat(0);
    TFile tfall{"data/all.merge_plots.root" };
    TFile tfhnu358{"data/m358.root" };
    TFile tfhnu357{"data/m357.root" };

    TCanvas c{"c", "c", 400, 400 };

   std::string sname = "_mvis";
    //std::string sname = "";
    auto name = sname.c_str();


    auto hbg = get_thing<TH1D>( tfall, Form("final_hc_tgt/full%s/hbg_err", name) );
    auto hdt = get_thing<TH1D>( tfall, Form("final_hc_tgt/full%s/hdata", name ) );

    auto hm357 = get_thing<TH1D>( tfhnu357, "mc.p5.hnu.357.nodk.neg/signal_upper_plots/h_m2m_kmu" );
    auto hm357negdn = get_thing<TH1D>( tfhnu357, "mc.p5.hnu.357.nodk.neg/signal_lower_plots/h_m2m_kmu" );
    auto hm357posup = get_thing<TH1D>( tfhnu357, "mc.p5.hnu.357.nodk.pos/signal_upper_plots/h_m2m_kmu" );
    auto hm357posdn = get_thing<TH1D>( tfhnu357, "mc.p5.hnu.357.nodk.pos/signal_lower_plots/h_m2m_kmu" );

    hm357->Add( hm357negdn );
    hm357->Add( hm357posup );
    hm357->Add( hm357posdn );

    auto hm358 = get_thing<TH1D>( tfhnu358, "mc.p5.hnu.358.nodk.neg/signal_upper_plots/h_m2m_kmu" );
    auto hm358negdn = get_thing<TH1D>( tfhnu358, "mc.p5.hnu.358.nodk.neg/signal_lower_plots/h_m2m_kmu" );
    auto hm358posup = get_thing<TH1D>( tfhnu358, "mc.p5.hnu.358.nodk.pos/signal_upper_plots/h_m2m_kmu" );
    auto hm358posdn = get_thing<TH1D>( tfhnu358, "mc.p5.hnu.358.nodk.pos/signal_lower_plots/h_m2m_kmu" );

    hm358->Add( hm358negdn );
    hm358->Add( hm358posup );
    hm358->Add( hm358posdn );

    hbg->SetTitle("");
    hbg->SetFillColor( kViolet + 5 );
    hbg->SetMarkerColor( kViolet + 6 );
    gROOT->GetColor( kViolet + 5 )->SetAlpha(0.3 );
    hbg->SetFillStyle( 1001 );
    hbg->Draw("E2");
    hbg->Draw("E2");
    hbg->GetXaxis()->SetRangeUser( 0.126, 0.129 );
    hbg->GetYaxis()->SetRangeUser( 0, 300 );
    hdt->Draw("same, E1");

    //hm357->Scale(0.002);
    //hm357->Scale(0.010);
    //hm357->Draw("same");

    //hm358->Scale(0.002);
    hm358->Scale(0.005);
    hm358->Draw("same");


    c.Print( Form("output/sig%s.pdf", name ), "pdf" );

    c.SetGrid();

    hdt->Add( hbg, -1);
    hdt->GetXaxis()->SetRangeUser( 0.126, 0.129 );
    hdt->Draw("E1");
    //hm357->Draw("same");
    hm358->Draw("same");

    c.Print( Form("output/delta%s.pdf", name ), "pdf" );
}
