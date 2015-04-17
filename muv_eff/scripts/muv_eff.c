struct result
{
    TH2D * h_passed;
    TH2D * h_total;

    TH1D * hx_passed;
    TH1D * hy_passed;

    TH1D * hx_total;
    TH1D * hy_total;

    TEfficiency * new_eff;
    TEfficiency * xeff;
    TEfficiency * yeff;
    TEfficiency * xyineff;

    TH2D * hxy_fail;
};


result plot( int rebin = 1 )
{
    result r;
    TFile * data = new TFile( "data/muv_data.root" );
    r.h_passed = 0;
    r.h_total = 0;

    //data->GetObject( "p5.data.q11t.v3.pos/muv_and_full/h_xy_passed", r.h_passed );
    //data->GetObject( "p5.data.q11t.v3.pos/muv_and_full/h_xy_total", r.h_total );

    data->GetObject( "p5.km2.v2/muv_and_full/h_xy_passed", r.h_passed );
    data->GetObject( "p5.km2.v2/muv_and_full/h_xy_total", r.h_total );

    if ( ! r.h_passed )
    {
        std::cout << "Can't find h_passed" << std::endl;
        return r;
    }

    if ( ! r.h_total )
    {
        std::cout << "Can't find h_total" << std::endl;
        return r;
    }

    r.h_passed->Rebin2D( rebin, rebin );
    r.h_total->Rebin2D( rebin, rebin );

    r.hxy_fail = static_cast<TH2D*>( r.h_total->Clone( "hxy_fail") );
    r.hxy_fail->Add( r.h_passed, -1 );

    r.hx_passed = r.h_passed->ProjectionY( "hx_passed" );
    r.hy_passed = r.h_passed->ProjectionX( "hy_passed" );

    r.hx_total = r.h_total->ProjectionY( "hx_total" );
    r.hy_total = r.h_total->ProjectionX( "hy_total" );

    r.new_eff = new TEfficiency( *r.h_passed, *r.h_total );
    r.new_eff->Draw("colz");

    r.xeff = new TEfficiency( *r.hx_passed, *r.hx_total );
    r.yeff = new TEfficiency( *r.hy_passed, *r.hy_total );

    r.xyineff = new TEfficiency( *r.hxy_fail, *r.h_total );

    int nXBins = r.h_passed->GetNbinsX();
    int nYBins = r.h_passed->GetNbinsY();

    TAxis * tx = r.h_passed->GetXaxis();
    TAxis * ty = r.h_passed->GetYaxis();

    std::ofstream fout( "output/xyandeffs.dat" );

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

            int global_bin =  r.h_passed->GetBin(ix, iy);

            double eff = r.new_eff->GetEfficiency( global_bin);
            double loweff = r.new_eff->GetEfficiencyErrorLow( global_bin);
            double higheff = r.new_eff->GetEfficiencyErrorUp( global_bin);

            // if ( abs(x) < 100  && abs(y) < 100 && abs(x) > 20 && abs(y) > 20 )
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

    return r;
}
