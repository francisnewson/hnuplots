{
    TFile tf( "data/p5.data.q11t.v3_muv_hits_muv_hits.root" );

    TCanvas c( "c", "c", 400, 400 );
    gStyle->SetOptStat(0);

    for ( int i = 0 ; i != 56 ; ++ i )
    {
        TH2D * h  = 0;
        TString name = Form("p5.data.q11t.v3/muv_pmt_hits/MUVALL/muv_all_%d", i );
        tf.GetObject( name , h );
        if ( !h )
        {
            std::cout  << "Can't find " << name << std::endl;
            return(0);
        }
        h->SetMarkerStyle(7);
        h->Draw();
        c.Print(Form("output/hits/channel_%d.pdf", i ), "pdf" );
    }
}
