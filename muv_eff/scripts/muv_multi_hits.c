{
    TFile tf( "data/p5.data.q11t.v3_muv_hits_muv_hits.root" );

    TCanvas c( "c", "c", 400, 400 );
    gStyle->SetOptStat(0);

    std::vector<int> colors;
    colors.push_back( 12);
    colors.push_back( 2);
    colors.push_back( 3);
    colors.push_back( 4);
    colors.push_back( 5);
    colors.push_back( 6);
    colors.push_back( 7);
    colors.push_back( 8);
    colors.push_back( 9);
    colors.push_back( kOrange);
    colors.push_back( 29);

    for ( int c = 0 ; c != colors.size() ; ++c )
    {
        gROOT->GetColor( colors[c] )->SetAlpha(0.8);
    }

    for ( int i = 23 ; i != 34 ; ++ i )
    {
        TH2D * h  = 0;
        TString name = Form("p5.data.q11t.v3/muv_pmt_hits/MUVALL/muv_all_%d", i );
        std::cout << i << " " << name << " " << colors[i-23] << std::endl;
        tf.GetObject( name , h );
        if ( !h )
        {
            std::cout  << "Can't find " << name << std::endl;
            return(0);
        }
        h->SetMarkerStyle(7);
        h->SetMarkerColor(  colors[ i - 23 ] );
        h->Draw("same");
    }
    c.Print(Form("output/hits/multi_muv2_a.png" ), "png" );

    TCanvas c2( "c2", "c2", 400, 400 );

    for ( int i = 34 ; i != 45 ; ++ i )
    {
        TH2D * h  = 0;
        TString name = Form("p5.data.q11t.v3/muv_pmt_hits/MUVALL/muv_all_%d", i );
        std::cout << i << " " << name << " " << colors[i-34] << std::endl;
        tf.GetObject( name , h );
        if ( !h )
        {
            std::cout  << "Can't find " << name << std::endl;
            return(0);
        }
        h->SetMarkerStyle(7);
        h->SetMarkerColor(  colors[ i - 34] );
        h->Draw("same");
    }
    c2.Print(Form("output/hits/multi_muv2_b.png" ), "png" );
}
