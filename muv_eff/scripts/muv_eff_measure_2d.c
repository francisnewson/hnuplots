TEfficiency *  plot( int rebin = 1 )
{

    TFile * data = new TFile( "data/muv_data.root" );

    TEfficiency * eff = 0;
    data->GetObject( "p5.data.q11t.v3.pos/muv_and_full/muv_eff_xy", eff );

    if ( !eff )
    {
        std::cout << "can't find eff" << std::endl;
        return 0;
    }

     TH2D * hpassed = static_cast< TH2D*>( 
             eff->GetPassedHistogram()->Clone( "hpassed" ) );

     TH2D * htotal = static_cast< TH2D*>( 
             eff->GetTotalHistogram()->Clone( "htotal" ) );

    hpassed->Rebin2D( rebin, rebin );
    htotal->Rebin2D( rebin, rebin );

    TEfficiency * new_eff = new TEfficiency( *hpassed, *htotal );
    new_eff->Draw("E");
    return new_eff;
}
