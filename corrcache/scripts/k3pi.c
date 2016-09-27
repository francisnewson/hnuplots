void run()
{
    gStyle->SetOptStat( 0 );
    TFile tf{"data/all.k3pi.root"};

    TH1 * hpos = get_thing<TH1>( tf, "p5.data.q1.v4.pos/k3pi_wide_plots/h_mK");
    TH1 * hneg = get_thing<TH1>( tf, "p5.data.q1.v4.neg/k3pi_wide_plots/h_mK");

    hpos->Add( hneg );

    hpos->Rebin(2);
    hpos->SetTitle( "" );


    TCanvas c( "c", "c", 400, 400 );

    hpos->GetYaxis()->SetTitle( "" );
    hpos->GetXaxis()->SetTitle( "reconstructed m_{K} (GeV/c^{2})" );
    hpos->GetXaxis()->SetRangeUser( 0.46, 0.53 );
    hpos->SetLineColor( kBlack );
    hpos->SetLineWidth( 2 );

    hpos->Draw();
    c.SetLogy();
    c.SetGrid();

    hpos->SetMinimum( 10 );

    double mk = 0.493667;
    double mink = mk - 0.003;
    double maxk = mk + 0.003;

    TArrow lh_arrow( mink, 1e4, mink, 1e1, 0.03, "|>" );
    TArrow rh_arrow( maxk, 1e4, maxk, 1e1, 0.03, "|>" );

    lh_arrow.SetLineWidth( 2 );
    rh_arrow.SetLineWidth( 2 );

    lh_arrow.SetLineColor( kRed + 2 );
    rh_arrow.SetLineColor( kRed + 2 );

    lh_arrow.Draw();
    rh_arrow.Draw();


    c.Print( "output/k3pi_peak.pdf", "pdf" );

}

void k3pi()
{
    run();
}
