void print( int rebin, std::string output )
{

    TFile fdata( "data/all.muv_measure.root");

    TH2D * h_pos_passed;
    TH2D * h_pos_total;

    TH2D * h_neg_passed;
    TH2D * h_neg_total;

    fdata.GetObject( "p5.data.q11t.v3.pos/muv_and_full/h_xy_passed", h_pos_passed );
    fdata.GetObject( "p5.data.q11t.v3.pos/muv_and_full/h_xy_total", h_pos_total );

    fdata.GetObject( "p5.data.q11t.v3.neg/muv_and_full/h_xy_passed", h_neg_passed );
    fdata.GetObject( "p5.data.q11t.v3.neg/muv_and_full/h_xy_total", h_neg_total );

    if ( ! h_pos_passed ){ std::cout << "No pos_passed" << std::endl; return; }
    if ( ! h_pos_total ){ std::cout << "No pos_passed" << std::endl; return; }
    if ( ! h_neg_passed ){ std::cout << "No neg_passed" << std::endl; return; }
    if ( ! h_neg_total ){ std::cout << "No neg_passed" << std::endl; return; }

    h_pos_passed->Rebin2D( rebin , rebin );
    h_neg_passed->Rebin2D( rebin , rebin );
    h_pos_total->Rebin2D( rebin , rebin );
    h_neg_total->Rebin2D( rebin , rebin );

    h_pos_passed->Add( h_neg_passed );
    h_pos_total->Add( h_neg_total );

    TEfficiency eff_xy( *h_pos_passed, *h_pos_total );

    std::ofstream fout( output.c_str() );

    fout 
        << std::setw(10) << "global_bin"
        << std::setw(10) << "x"
        << std::setw(10) << "y"
        << std::setw(10) << "minx"
        << std::setw(10) << "maxx"
        << std::setw(10) << "miny"
        << std::setw(10) << "maxy"
        << std::setw(10) << "eff"
        << std::setw(10) << "loweff"
        << std::setw(10) << "higheff"
        << std::endl;

    TAxis * tx = h_pos_passed->GetXaxis();
    TAxis * ty = h_pos_passed->GetYaxis();

    int nXBins = h_pos_passed->GetNbinsX();
    int nYBins = h_pos_passed->GetNbinsY();

    for ( int iy = 1 ; iy != nYBins + 1 ; ++ iy )
    {
        for ( int ix = 1 ; ix != nXBins + 1 ; ++ ix )
        {
            double x = tx->GetBinCenter( ix );
            double y = tx->GetBinCenter( iy );

            double minx = tx->GetBinLowEdge( ix );
            double maxx = minx + tx->GetBinWidth( ix );

            double miny = ty->GetBinLowEdge( iy );
            double maxy = miny + ty->GetBinWidth( iy );

            int global_bin =  h_pos_passed->GetBin(ix, iy);

            double eff = eff_xy.GetEfficiency( global_bin);
            double loweff = eff_xy.GetEfficiencyErrorLow( global_bin);
            double higheff = eff_xy.GetEfficiencyErrorUp( global_bin);

            if ( true )
            {
                std::size_t prec = fout.precision(5 );

                fout 
                    << std::setw(10) << global_bin
                    << std::setw(10) << x
                    << std::setw(10) << y
                    << std::setw(10) << minx
                    << std::setw(10) << maxx
                    << std::setw(10) << miny
                    << std::setw(10) << maxy
                    << std::setw(10) << eff
                    << std::setw(10) << loweff
                    << std::setw(10) << higheff
                    << std::endl;

                fout.precision( prec );
            }
        }
    }

}
