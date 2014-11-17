void plot_m2p( TFile& tf, std::string channel, std::string path, std::string output_file, std::string title )
{
    std::string full_hist_path = channel + "/" + path;
    std::cerr << full_hist_path << std::endl;
    TH2D * h = 0;
    tf.GetObject( full_hist_path.c_str(), h );
    std::cerr << h << std::endl;
    h->Draw("colz");
    h->GetXaxis()->SetRangeUser( -0.7, 0.2 );
    h->GetYaxis()->SetRangeUser( 0, 80 );
    h->SetTitle( title.c_str() );
    //gPad->SetLogz();
    gPad->SetCanvasSize( 400, 400 );
    gPad->Print( output_file.c_str() );
}

void run( TFile& tf, std::string subfolder,  std::string runfile )
{
    gStyle->SetOptStat(0);
    std::ifstream ifs( runfile );
    std::string buf;
    std::string channel, output_file, title;

    while( std::getline( ifs, buf ) )
    {
        std::stringstream ss( buf );
        ss >> channel >> output_file;
        std::getline( ss, title );
        if ( channel[0] == '#' )
            continue;
        plot_m2p( tf, channel, subfolder, output_file, title );
    }
}
