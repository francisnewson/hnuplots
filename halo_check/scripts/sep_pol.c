void plot()
{
    TFile tf {"data/all.mass_plots.root" };

    std::vector<std::pair<std::string, std::string>> folders
    {
        {"pos_upper", "ctrl/pos/alt_upper_sig_muv_check" },
        {"neg_upper", "ctrl/neg/alt_upper_sig_muv_check" },
        {"pos_lower", "ctrl/pos/lower_sig_muv_check" },
        {"neg_lower", "ctrl/neg/lower_sig_muv_check" }
    };

    std::vector<std::tuple<std::string, double, double>> plots
    {
        { "h_z", -2000, 10000 },
            { "h_p", 0, 60 },
            { "h_t", 0, 0.015 },
            { "h_cda", 0, 8 },
        { "h_m2m_kmu", 0.03, 0.16 }
    };

    TCanvas c{"c","c", 400, 400 };

    for ( auto folder : folders )
    {
        for ( auto plot : plots )
        {
            auto * hbg = get_thing<TH1>( tf,
                    Form( "%s/%s/hbg_err", folder.second.c_str() , std::get<0>(plot).c_str() ) );

            auto * hdt = get_thing<TH1>( tf,
                    Form( "%s/%s/hdata", folder.second.c_str() , std::get<0>(plot).c_str() ) );

            hbg->Draw("E1");
            hbg->GetXaxis()->SetRangeUser( std::get<1>( plot ), std::get<2>( plot ));
            hdt->Draw("E1, same");
            c.SetGrid();

            c.Print( Form("output/merge/%s/%s.pdf", 
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );

            auto * hrat = get_thing<TH1>( tf,
                    Form( "%s/%s/h_err_ratio", folder.second.c_str(), std::get<0>(plot).c_str() ) ) ;

            hrat->Draw("E1");
            hrat->GetXaxis()->SetRangeUser( std::get<1>( plot ), std::get<2>( plot ));
            hrat->GetYaxis()->SetRangeUser( 0, 2.5 );

            c.Print( Form("output/merge/%s/%s_rat.pdf", 
                        folder.first.c_str(), std::get<0>(plot).c_str() ), "pdf" );
        }
    }
}

void merge_check()
{
    plot();
}
