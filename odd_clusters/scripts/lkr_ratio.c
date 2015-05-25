TH2D * run( std::string pol, int rebin = 1)
{
    TFile * tfin = new TFile( "data/all.rk_selection.raw.root" );

    TH2D * hk2pi = 0;
    tfin->GetObject( Form("p5.k2pig.v2.%s/k2pi_problem_clusters/"
            "h_xy_bad", pol.c_str() ), hk2pi );

    if ( hk2pi == 0 )
    {
        std::cout << "Can't find k2pi!" << std::endl;
        return 0;
    }

    TH2D * hdt = 0;
    tfin->GetObject( Form("p5.data.q11t.v3.%s/k2pi_problem_clusters/"
            "h_xy_bad", pol.c_str() ), hdt );

    if ( hdt == 0 )
    {
        std::cout << "Can't find data!" << std::endl;
        return 0;
    }

    hk2pi->Rebin2D( rebin, rebin );
    hdt->Rebin2D( rebin, rebin );

    hdt->Divide( hk2pi );
    hdt->Draw("colz");

    return hdt;
}


TH2D * run_both( int rebin = 1)
{
    TFile * tfin = new TFile( "data/all.rk_selection.raw.root" );

    TH2D * hk2pi_pos = 0;
    tfin->GetObject( Form("p5.k2pig.v2.%s/k2pi_problem_clusters/" "h_xy_bad", "pos"), hk2pi_pos );
    if ( hk2pi_pos == 0 ) { std::cout << "Can't find k2pi pos!" << std::endl; return 0; }

    TH2D * hk2pi_neg = 0;
    tfin->GetObject( Form("p5.k2pig.v2.%s/k2pi_problem_clusters/" "h_xy_bad", "neg"), hk2pi_neg );
    if ( hk2pi_neg == 0 ) { std::cout << "Can't find k2pi neg!" << std::endl; return 0; }

    TH2D * hdt_pos = 0;
    tfin->GetObject( Form("p5.data.q11t.v3.%s/k2pi_problem_clusters/" "h_xy_bad", "pos" ), hdt_pos ); 
    if ( hdt_pos == 0 ) { std::cout << "Can't find data pos!" << std::endl; return 0; }

    TH2D * hdt_neg = 0;
    tfin->GetObject( Form("p5.data.q11t.v3.%s/k2pi_problem_clusters/" "h_xy_bad", "neg" ), hdt_neg ); 
    if ( hdt_neg == 0 ) { std::cout << "Can't find data neg!" << std::endl; return 0; }

    hk2pi_pos->Add( hk2pi_neg );
    hdt_pos->Add( hdt_neg );

    TH2D * hk2pi = hk2pi_pos;
    TH2D * hdt = hdt_pos;

    hk2pi->Rebin2D( rebin, rebin );
    hdt->Rebin2D( rebin, rebin );

    hdt->Divide( hk2pi );
    hdt->Draw("colz");

    return hdt;
}
