TH1D * get_ratio( TFile * tf )
{ 
    TH1D * hnum;
    tf->GetObject( "hdata", hnum );
    hnum->Sumw2();

    TH1D * hdenom;
    tf->GetObject( "hbg", hdenom );
    hdenom->Sumw2();

    hnum->Divide( hdenom );
    hnum->SetName( "ratio" );
    hnum->SetDirectory(0);
    return hnum;
}

TH1D * get_ratio( std::string s )
{
    TFile tf( s.c_str() );
    return get_ratio( &tf );
}

struct hres
{
    TH1D * h_uc;
    TH1D * h_corr;
    TH1D * h_corr_w;
    TLegend * leg;
};

void prep_hist( TH1D * h , int color )
{
    h->SetLineColor( color );
    h->SetMarkerColor( color );
    h->SetLineWidth( 2 );
}

hres get_ratios()
{
    hres r;
    r.h_uc = get_ratio( "data/uc.root" );
    r.h_corr = get_ratio( "data/corr.root" );
    r.h_corr_w = get_ratio( "data/corr_weighted.root" );

    prep_hist( r.h_uc, kRed +2 );
    prep_hist( r.h_corr, kOrange +2 );
    prep_hist( r.h_corr_w, kGreen +2 );

    r.leg = new TLegend( 0.1, 0.7, 0.48, 0.9 );
    r.leg->AddEntry( r.h_uc, "Uncorrected" );
    r.leg->AddEntry( r.h_corr, "Beta correction" );
    r.leg->AddEntry( r.h_corr_w, "Beta correction and weights" );

    return r;
}

void plot_all_ratios()
{
    hres r = get_ratios();
    r.h_uc->Draw("E1");
    r.h_corr->Draw("E1,same");
    r.h_corr_w->Draw("E1,same");
    r.leg->Draw("same");
}
