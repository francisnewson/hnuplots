void do_plots()
{
    std::vector<std::string> channels {
        "p5.data.q11t.v3.pos"
            , "p5.km2.v2.pos"
            , "p6.data.km.q11t.v2.pos"
    };

    std::vector<std::string> selections { 
        "pre_plots"
            //, "ctrl_upper_plots"
            //, "ctrl_lower_full_m2m_plots"
            //, "ctrl_lower_neg_m2m_plots"
            //, "ctrl_lower_plots"
            //, "signal_upper_muv_plots"
            //, "signal_lower_muv_plots"
            //, "pre_upper_high_m2m_plots"
            //, "pre_lower_high_m2m_plots" 
            //, "signal_upper_check_plots"
            , "pre_upper_plots"
    };

    std::vector<std::string> distributions 
    { "h_m2m_kmu", "h_p_m2m_kmu", "h_p", "h_z", "h_t", "h_p_z", "h_p_t", "h_z_t",
        "h_cda", "h_t_phi", "h_xy_MUV1", "h_m2_t", "h_m2_z" , "h_p_cda", "h_z_cda",
    };

    TFile tfin { "data/all.halo_control.root" };

    for ( auto chan : channels )
    {
        std::cout << chan << std::endl;

        for ( auto sel : selections )
        {

            TCanvas c{ "c", "c",  600, 850 };
            c.Divide( 3,5 );

            int pad = 1;

            for ( auto dist : distributions )
            {
                c.cd( pad );
                ++pad;

                auto * h = get_thing<TH1>( tfin, chan  + "/" + sel + "/" + dist );
                h->Draw("colz");
            }

            c.cd(0);
            TPaveText t( 0.1, 0.79, 0.4, 0.82);
            t.AddText(Form( "%s:%s", chan.c_str(), sel.c_str() ) );
            t.Draw("same");

            c.Print( ("output/regions/" + chan + "_" + sel +".pdf").c_str() , "pdf" );
        }
    }
}

void regions(){ do_plots() ; }
