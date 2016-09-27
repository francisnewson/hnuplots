void set_bg_extra_err( TH1D * hbg, double extra_err )
{
    int nbins = hbg->GetXaxis()->GetNbins();

    for ( int i = 1 ; i <= nbins ;  ++i )
    {
        double val = hbg->GetBinContent( i );
        double err = hbg->GetBinError( i );

        double extra_err_val = val * extra_err;
        hbg->SetBinError( i, std::hypot( err, extra_err_val ) );
    }
}

std::pair<double, TH1D*>  optimize_errors( TH1D * hdt, TH1D * hbg )
{
    double extra_err = 0;
    TH1D * hthisbg = 0;
    TH1D * hrat = 0;

    while( true )
    {
        //set extra err
        hthisbg = static_cast<TH1D*>(hbg->Clone( "h" ) );
        hthisbg->SetDirectory(0);
        set_bg_extra_err( hthisbg, extra_err );

        //determine chi2
        TF1 my_fit{ "my_fit", "[0]", hdt->GetXaxis()->GetXmin(), hdt->GetYaxis()->GetXmax() };

        hrat = static_cast<TH1D*>( hdt->Clone( "hrat" ) );
        hrat->SetDirectory(0);
        hrat->Divide( hthisbg );
        hrat->Fit( &my_fit, "Q" );
        double chi2ndf = my_fit.GetChisquare() / my_fit.GetNDF();
        std::cout << extra_err << " " << my_fit.GetChisquare() << " " << my_fit.GetNDF() << " "  << my_fit.GetParameter(0) <<  std::endl;

        //break if good enough
        if ( chi2ndf < 1 ){ break; }
        else {
            extra_err += 0.05;
            delete hthisbg;
            delete hrat;
        };
    }

    delete hthisbg;

    return std::make_pair( extra_err, hrat );
};

void plot()
{
    gStyle->SetOptStat(0);
    //std::string version = "2015-09-03pm/full_merge";
    //std::string version = "2015-09-05am";
    std::string version = "2015-09-12";

    //TFile tf {Form("data/%s/all.merge_plots_breakdown.root", version.c_str()) };
    TFile tf {Form("data/%s/all.breakdown_plots.root", version.c_str()) };

    std::vector<std::pair<std::string, std::string>> folders
    {
        //{"upper", "upper_signal_alt_check" },
        //{"lower", "lower_signal_check" },
        //{"all", "signal_check" }

        {"pos_check_upper" , "pos_check_upper"} ,
            {"neg_check_upper" , "neg_check_upper"} ,
            {"both_check_upper" , "both_check_upper"} ,
            {"pos_check_lower" , "pos_check_lower"} ,
            {"neg_check_lower" , "neg_check_lower"} ,
            {"both_check_lower" , "both_check_lower"} ,
            {"pos_check_full" , "pos_check_full"} ,
            {"neg_check_full" , "neg_check_full"} ,
            {"both_check_full" , "both_check_full"}
    };

    std::vector<std::tuple<std::string, double, double>> plots
    {
        { "h_z", -2000, 10000 },
            { "h_p", 0, 60 },
            { "h_t", 0, 0.015 },
            { "h_cda", 0, 10 },
            { "h_m2m_kmu", 0.03, 0.16 }
    };

    TCanvas c{"c","c", 400, 400 };

    for ( auto folder : folders )
    {
        for ( auto plot : plots )
        {
            auto * hbg = get_thing<TH1D>( tf,
                    Form( "%s/%s/hbg_err", folder.second.c_str() , std::get<0>(plot).c_str() ) );

            auto * hdt = get_thing<TH1D>( tf,
                    Form( "%s/%s/hdata", folder.second.c_str() , std::get<0>(plot).c_str() ) );

            hbg->SetTitle("");
            hbg->Draw("E1");
            hbg->GetYaxis()->SetTitle("");
            hbg->SetLineWidth(2);
            hbg->GetXaxis()->SetRangeUser( std::get<1>( plot ), std::get<2>( plot ));
            hdt->Draw("E1, same");
            hdt->SetLineWidth(2);

            TLegend tl{ 0.2, 0.6, 0.4, 0.8 };
            tl.AddEntry( hdt, "K^{+} data", "pel" );
            tl.AddEntry( hbg, "K^{-} data", "pel" );
            tl.Draw("same");
            c.SetGrid();

            gSystem->MakeDirectory( Form("output/%s/%s", version.c_str(), folder.first.c_str() ) );


            c.Print( Form("output/%s/%s/%s.pdf", version.c_str(),
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );

            auto * hrat = get_thing<TH1D>( tf,
                    Form( "%s/%s/h_err_ratio", folder.second.c_str(), std::get<0>(plot).c_str() ) ) ;

            hrat->Draw("E1");
            hrat->GetXaxis()->SetRangeUser( std::get<1>( plot ), std::get<2>( plot ));
            hrat->GetYaxis()->SetRangeUser( 0, 2.5 );

            c.Print( Form("output/%s/%s/%s_rat.pdf", version.c_str(),
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );

            TF1 my_fit{ "my_fit", "[0]", hrat->GetXaxis()->GetXmin(), hrat->GetYaxis()->GetXmax() };
            hrat->Fit( &my_fit, "Q" );
            TLatex  t( 0.2, 0.8, Form( "#chi^{2} = %.2f / %d", my_fit.GetChisquare() , my_fit.GetNDF() ) );
            t.SetNDC();
            t.Draw("same");
            c.Print( Form("output/%s/%s/%s_rat_fit.pdf", version.c_str(),
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );
            std::cout << "val: " << my_fit.GetParameter(0) << "chi2: " << my_fit.GetChisquare() <<  " ndf: " << my_fit.GetNDF() << std::endl;

            std::pair<double, TH1D * > opt = optimize_errors( hdt, hbg );
            opt.second->Fit( &my_fit, "Q" );
            opt.second->GetXaxis()->SetRangeUser(  std::get<1>( plot ), std::get<2>( plot ) );
            opt.second->GetYaxis()->SetRangeUser( 0, 2.5 );
            opt.second->Draw("E1");
            TLatex  opt_t( 0.2, 0.8, Form( "#chi^{2} = %.2f / %d", my_fit.GetChisquare() , my_fit.GetNDF() ) );
            opt_t.SetNDC();
            opt_t.Draw("same");
            TLatex  opterr( 0.2, 0.6, Form( "errscale = %.2f", opt.first ) );
            opterr.SetNDC();
            opterr.Draw("same");
            c.Print( Form("output/%s/%s/%s_rat_fit_opt.pdf", version.c_str(),
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );
        }
    }
}

void merge_check()
{
    plot();
}
