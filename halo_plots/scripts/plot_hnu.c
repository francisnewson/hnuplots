void prep( TH1 * h) 
{
    h->SetTitle("");
}

TH1 * get_plot( TFile& tf, int mass, std::string name )
{
    TH1 * res = get_thing<TH1>( tf, 
            Form("mc.p5.hnu.%d.nodk.neg/pre_pre_plots/%s", mass, name.c_str() ) );

    if( mass < 300 ){
        res->SetMarkerColor( kBlue + 2 );
        res->SetFillColor( kBlue + 2 );
    }
    else { 
        res->SetMarkerColor( kGreen + 2 );
        res->SetFillColor( kGreen + 2 );
    }

    res->GetYaxis()->CenterTitle();
    res->SetTitle( "" ) ;

    return res;
}

void run()
{
    gStyle->SetPalette(57);
    gStyle->SetOptStat(0);
    gROOT->GetColor( kBlue + 2 )->SetAlpha(0.1);
    gROOT->GetColor( kGreen + 2 )->SetAlpha(0.1);

    TFile tf( "data/all.full.root" );

    TCanvas c( "c", "c", 700, 700 );
    c.SetGrid();

    {
        std::cout << "Drawing h_zt plots" << std::endl;


        TH1 * h_zt_250 = get_plot( tf, 250, "h_z_t" );
        h_zt_250->Draw();
        h_zt_250->GetYaxis()->SetTitle( "#theta (rad)" );
        TH1 * h_zt_350 = get_plot( tf, 350, "h_z_t" );
        h_zt_350->Draw("same");


        std::cout << "Drawing h_zt legend" << std::endl;

        TLegend leg{ 0.5, 0.5, 0.8, 0.8 };
        leg.AddEntry( h_zt_250, "250 MeV", "f" );
        leg.AddEntry( h_zt_350, "350 MeV", "f" );
        leg.Draw("same" );

        c.SaveAs( "output/signal/h_zt.png");
    }

    {
        std::cout << "Drawing h_p_cda plots" << std::endl;

        TH1 * h_pcda_250 = get_plot( tf, 250, "h_p_cda" );
        h_pcda_250->Draw();
        TH1 * h_pcda_350 = get_plot( tf, 350, "h_p_cda" );
        h_pcda_350->Draw("same");

        std::cout << "Drawing h_p_cda legend" << std::endl;

        TLegend leg{ 0.5, 0.5, 0.8, 0.8 };
        leg.AddEntry( h_pcda_250, "250 MeV", "f" );
        leg.AddEntry( h_pcda_350, "350 MeV", "f" );
        leg.Draw("same" );

        c.SaveAs( "output/signal/h_pcda.png");
    }

    {
        std::cout << "Drawing h_t_phi plots" << std::endl;

        TH1 * h_t_phi_250 = get_plot( tf, 250, "h_t_phi" );
        h_t_phi_250->GetYaxis()->SetTitle( "#theta (rad)" );
        h_t_phi_250->GetXaxis()->SetTitle( "#phi (rad)" );
        h_t_phi_250->Draw();
        TH1 * h_t_phi_350 = get_plot( tf, 350, "h_t_phi" );
        h_t_phi_350->Draw("same");

        std::cout << "Drawing h_t_phi legend" << std::endl;

        TLegend leg{ 0.5, 0.5, 0.8, 0.8 };
        leg.AddEntry( h_t_phi_250, "250 MeV", "f" );
        leg.AddEntry( h_t_phi_350, "350 MeV", "f" );
        leg.Draw("same" );

        c.SaveAs( "output/signal/h_tphi.png");
    }

    {
        std::cout << "Drawing h_p_z plots" << std::endl;

        TH1 * h_p_z_250 = get_plot( tf, 250, "h_p_z" );
        h_p_z_250->Draw();
        TH1 * h_p_z_350 = get_plot( tf, 350, "h_p_z" );
        h_p_z_350->Draw("same");

        std::cout << "Drawing h_t_phi legend" << std::endl;

        TLegend leg{ 0.5, 0.5, 0.8, 0.8 };
        leg.AddEntry( h_p_z_250, "250 MeV", "f" );
        leg.AddEntry( h_p_z_350, "350 MeV", "f" );
        leg.Draw("same" );

        c.SaveAs( "output/signal/h_pz.png");
    }
}


void plot_hnu() { run(); }
