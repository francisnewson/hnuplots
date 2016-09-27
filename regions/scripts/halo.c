void do_plots()
{
    TFile tfin { "data/all.halo_control.root" };
    TCanvas c{ "c", "c",  600, 850 };
    c.Divide( 4,5 );

    std::vector<std::string> dists
    {
        "h_xy_coll", "h_txty", "h_xy_DCH1", "h_xy_DCH4"
    };

    std::vector<std::string> channels {
        "p5.data.q11t.v3.pos",
            "p5.data.q11t.v3.neg",
            "p6.data.km.q11t.v2.pos",
            "p6.data.km.q11t.v2.neg",
            "p6.data.kless.q11t.v2.pos" 
    };

    std::string sel = "ctrl_upper_plots";

    int pad = 1;

    for ( auto chan : channels )
    {
        std::cout << chan << std::endl;

        for ( auto dist: dists )
        {
            c.cd( pad );
            gPad->SetGrid();
            ++pad;

            auto * h = get_thing<TH1>( tfin, chan  + "/" + sel + "/" + dist );
            //h->Draw("colz" );
            static_cast<TH2D*>( h)->ProjectionX((dist+chan).c_str())->Draw();
        } 
    }

    //c.Print( "output/halo/halo.pdf", "pdf" );
    c.Print( "output/halo/halo_x.pdf", "pdf" );
}

void halo(){ do_plots() ; }
