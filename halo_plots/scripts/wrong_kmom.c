void plot_kmom()
{
    gStyle->SetOptStat(0);

    TFile tf{"data/wrong_kmom.root" };
    TCanvas c{ "c", "c", 400, 400 };
    c.SetGrid();

    TH2D * h_50  = get_thing<TH2D>( tf,  "h_m2m_p_50" );
    TH2D * h_80  = get_thing<TH2D>( tf,  "h_m2m_p_80" );

    TLatex tl50( 0.02, 55, "50 GeV/c kaons");
    TLatex tl80( -0.09, 84, "80 GeV/c kaons");

    h_50->Draw();
    h_50->SetTitle("");
    h_50->GetXaxis()->SetRangeUser( -0.1, 0.1 );
    h_50->GetXaxis()->SetNdivisions(7, true );
    h_50->GetYaxis()->SetNdivisions(7, true );
    h_50->GetYaxis()->SetTitle("muon momentum (GeV/c)");
    h_50->GetYaxis()->CenterTitle();
    h_80->Draw("same");

    tl50.Draw("same");
    tl80.Draw("same");

    c.Print( "output/wrong_kmom.pdf" , "pdf" );
}

void wrong_kmom()
{
    plot_kmom();
}
