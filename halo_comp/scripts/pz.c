TH1 * get_hist( TFile& tf, std::string name )
{
    TH1 * h = 0;
    tf.GetObject( name.c_str(), h );
    if( !h )
    {
        throw std::runtime_error( "Can't find " + name );
    }
    h->SetDirectory(0);
    return h;
}

void loose_pz(TFile& tf, std::string channel, std::string name )
{
    TH1 * h = get_hist( tf, (channel + "/halo_loose/h_pz").c_str() );
    TCanvas c1("c1" , "c1", 400, 400 );
    h->GetXaxis()->SetRangeUser( 0, 70 );
    h->Draw("colz");
    c1.Print( ( "output/" + name).c_str(), "pdf" );
}
