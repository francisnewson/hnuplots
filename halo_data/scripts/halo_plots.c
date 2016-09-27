void do_plot( TFile& tfin,
        std::string folder, std::string name,
        double minx, double maxx,  
        double miny, double maxy, 
        double minraty, double maxraty,
        std::string new_name = ""
        )

{
    if ( new_name == "" )
    {
        new_name = name;
    }

    TCanvas c( "c", "c",  400, 400 );
    THStack * hs = get_thing<THStack>(tfin, name + "/hnu_stack" );
    TH1 * hdata = get_thing<TH1>( tfin, name + "/hdata");
    TH1 * hrat = get_thing<TH1>( tfin, name + "/hratio");
    hdata->Draw();
    hs->Draw();

    hs->GetXaxis()->SetTitle( hdata->GetXaxis()->GetTitle() );

    hs->Draw();
    c.SetGrid();
    hs->GetXaxis()->SetRangeUser( minx, maxx );
    hs->SetMinimum( miny);
    hs->SetMaximum( maxy);
    hs->Draw();

    hdata->SetLineColor( kRed + 2 );
    hdata->SetLineWidth( 2);
    hdata->Draw("same,E1");
    c.Print( (folder + "/" + new_name + ".pdf").c_str(), "pdf" );

    hrat->Draw();
    hrat->GetXaxis()->SetRangeUser( minx, maxx );
    hrat->GetYaxis()->SetRangeUser( minraty, maxraty );
    hrat->SetLineWidth( 2);
    hrat->Draw("E1");
    c.Print( (folder + "/" + new_name + "_rat.pdf").c_str(), "pdf" );

}

void plot( double scale , std::string inputfile, std::string outputfolder )
{
    TFile tfin( inputfile.c_str() );
    do_plot( tfin, outputfolder,  "halo_lower_z", -3000, 3000, 0, scale * 30000, 0.8, 1.6 );
    do_plot( tfin, outputfolder,  "halo_lower_p", 0, 60, 0, scale * 20000, 0.8, 1.2 );
    do_plot( tfin, outputfolder,  "halo_lower_cda", 0, 7, 0, scale * 60000, 0.8, 1.2 );
    do_plot( tfin, outputfolder,  "halo_lower_t", 0, 0.015, 0, scale * 80000, 0.0, 3 );
    do_plot( tfin, outputfolder,  "halo_lower_t", 0, 0.010, 0, scale * 20000, 0.0, 3, "halo_lower_t_zoom" );
    do_plot( tfin, outputfolder,  "halo_lower_m2m", 0.0, 0.2, 0, scale * 22000, 0.0, 3 );
    do_plot( tfin, outputfolder,  "halo_lower_m2m", 0.08, 0.16, 0, scale * 200, 0.0, 3, "halo_lower_m2m_zoom" );
};
