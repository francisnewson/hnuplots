void prep( TH1 * h) 
{
    h->SetTitle("");
}
void run()
{
    gStyle->SetPalette(57);
    gStyle->SetOptStat(0);

#if 0
    {
        TFile tf( "data/halo_kless_ka+_halo_control_halo_ctrl_plots.root" );

        TH1 * h = get_hist( tf, "halo_kless_ka+/pre_plots/h_p_z" );

        TCanvas c( "c", "c", 350, 350 );
        c.SetRightMargin(0.2);
        h->Draw("colz");
        h->GetXaxis()->SetRangeUser(0, 70 );
        h->GetYaxis()->SetRangeUser(-3000, 9000 );
        c.SetGrid();
        h->SetTitle("");
        h->GetXaxis()->SetTitle( "p (GeV/c)" );
        h->GetYaxis()->SetTitle( "Z (cm)");
        h->GetYaxis()->SetTitleOffset(1.4);
        h->GetYaxis()->CenterTitle();
        c.Print( "output/halo_sim_pz.pdf", "pdf" );
    }
#endif 

    {
        TFile tf( "data/all.halo_control.root" );

        TH1 * h_p_up_neg = get_hist( tf, "p6.data.km.q1.v2.neg/pre_upper_plots/h_p" );
        TH1 * h_p_up_pos = get_hist( tf, "p6.data.km.q1.v2.pos/pre_upper_plots/h_p" );

        h_p_up_pos->Divide( h_p_up_neg );

        {
            TCanvas c( "c", "c", 350, 350 );
            h_p_up_pos->Draw( "E2");
            c.Print( "output/halo_pos_neg_ratio_p.pdf", "pdf");
        }


        auto all_halo_plot = [&tf] ( std::string plot_name )
        {
            TH1 * h_pp_kless_pos = get_hist( tf, ("p6.data.kless.q11t.v2.pos/pre_plots/" + plot_name ).c_str() );
            TH1 * h_pp_km_neg = get_hist( tf, ( "p6.data.km.q11t.v2.neg/pre_plots/" + plot_name ).c_str() );
            TH1 * h_pp_km_pos = get_hist( tf, ( "p6.data.km.q11t.v2.pos/pre_plots/" + plot_name ).c_str()) ;

            h_pp_kless_pos->Add( h_pp_km_neg );
            h_pp_kless_pos->Add( h_pp_km_pos );

            TH1 * hpz = static_cast<TH2D*>(h_pp_kless_pos);
            return hpz;
        };


        //PZ
        {
            auto hpz = all_halo_plot( "h_p_z" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.2);
            prep( hpz);
            hpz->GetXaxis()->SetRangeUser(0, 70 );
            hpz->GetYaxis()->SetRangeUser(-3000, 9000  );
            hpz->GetXaxis()->SetTitle( "p (GeV/c)" );
            hpz->GetYaxis()->SetTitle( "Z (cm)");
            hpz->GetYaxis()->SetTitleOffset(1.4);
            hpz->GetYaxis()->CenterTitle();
            hpz->Draw("colz");
            c.Print(  "output/halo_pz_pre_all.pdf", "pdf" );
            c.SetLogz();
            c.Print(  "output/halo_pz_pre_all_logy.pdf", "pdf" );
        }

        //ZT
        {
            auto hzt = all_halo_plot( "h_z_t" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.2);
            prep( hzt);
            hzt->GetXaxis()->SetRangeUser(-3000, 9000 );
            hzt->GetYaxis()->SetRangeUser( 0, 0.025  );
            hzt->GetYaxis()->SetTitle( "#theta (rad)" );
            hzt->GetXaxis()->SetTitle( "Z (cm)");
            hzt->GetYaxis()->SetTitleOffset(1.4);
            hzt->GetYaxis()->CenterTitle();
            hzt->Draw("colz");
            c.Print( "output/halo_zt_pre_all.pdf", "pdf" );
            c.SetLogz();
            c.Print( "output/halo_zt_pre_all_logy.pdf", "pdf" );
            Double_t z[4] = {-500, 2000, 4000, 8000};
            Double_t t[4] = { 0.012, 0.005, 0.003, 0.001};

            TGraph tg( 4, z, t );
            TGraph th( 4, z, t );
            th.SetLineColor(kBlack);
            th.SetMarkerColor(kBlack);
            th.SetMarkerSize(1);
            th.SetLineWidth(2);
            th.Draw("same,P,L");
            TText tup( 5000, 0.012, "upper" );
            tup.SetTextSize(0.07);
            TText tdn( -2000, 0.003, "lower" );
            tdn.SetTextSize(0.07);
            tup.Draw("same");
            tdn.Draw("same");
            c.Print( "output/halo_zt_pre_all_logy_regions.pdf", "pdf" );
        }



        auto all_halo_region_plot = [&tf] ( std::string region, std::string plot_name )
        {
            TH1 * h_pp_kless_pos = get_hist( tf, ("p6.data.kless.q11t.v2.pos/" + region + "/" + plot_name ).c_str() );
            TH1 * h_pp_km_neg = get_hist( tf, ( "p6.data.km.q11t.v2.neg/" + region + "/" + plot_name ).c_str() );
            TH1 * h_pp_km_pos = get_hist( tf, ( "p6.data.km.q11t.v2.pos/" + region + "/" + plot_name ).c_str() ) ;

            h_pp_kless_pos->Add( h_pp_km_neg );
            h_pp_kless_pos->Add( h_pp_km_pos );

            TH1 * h = static_cast<TH2D*>(h_pp_kless_pos);
            return h;
        };

        //Upper ZT
        {
            auto u_hzt = all_halo_region_plot( "pre_upper_plots", "h_z_t" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.2);
            //c.SetLogz();
            prep( u_hzt);
            u_hzt->GetXaxis()->SetRangeUser(-3000, 9000 );
            u_hzt->GetYaxis()->SetRangeUser( 0, 0.025  );
            u_hzt->GetYaxis()->SetTitle( "#theta (rad)" );
            u_hzt->GetXaxis()->SetTitle( "Z (cm)");
            u_hzt->GetYaxis()->SetTitleOffset(1.4);
            u_hzt->GetYaxis()->CenterTitle();

            u_hzt->Draw("colz");


            u_hzt->Draw("colz");

            Double_t z[9] =  {8000 , 8000 ,  7000 , 5000 ,
                3500 , 2000 , 0 ,  0 , 8000 };

            Double_t t[9] = { 0.000 , 0.004 , 0.0045 , 0.006 ,
                0.008 , 0.010 , 0.010 ,  0.000 , 0.000 };

            TGraph th( 9, z, t );

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");


            TLegend leg{ 0.23, 0.7, 0.43, 0.8 };
            //leg.AddEntry( &nth, "Scaling region", "lp" );
            leg.AddEntry( &th, "Signal region", "lp" );
            leg.Draw( "same" );

            c.Print( "output/halo_zt_pre_upper.pdf", "pdf" );
        }

        //Upper PZ
        {
            auto u_hpz = all_halo_region_plot( "pre_upper_plots", "h_p_z" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.2);
            //c.SetLogz();
            prep( u_hpz);
            u_hpz->GetXaxis()->SetRangeUser( 0, 70 );
            u_hpz->GetYaxis()->SetRangeUser(-3000, 9000 );
            u_hpz->GetXaxis()->SetTitle( "p (GeV/c)" );
            u_hpz->GetYaxis()->SetTitle( "Z (cm)");
            u_hpz->GetYaxis()->SetTitleOffset(1.4);
            u_hpz->GetYaxis()->CenterTitle();

            u_hpz->Draw("colz");


            u_hpz->Draw("colz");

            Double_t z[5] =  {10, 10 , 25 ,  25 , 100  };

            Double_t t[5] = { -5000, 4000 , 6500 , 8000 , 8000  };

            TGraph th( 5, z, t );

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");
            c.Print( "output/halo_pz_pre_upper.pdf", "pdf" );
        }
        
        //Lower ZT
        {
            auto u_hzt = all_halo_region_plot( "pre_lower_plots", "h_z_t" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.2);
            //c.SetLogz();
            prep( u_hzt);
            u_hzt->GetXaxis()->SetRangeUser(-3000, 9000 );
            u_hzt->GetYaxis()->SetRangeUser( 0, 0.025  );
            u_hzt->GetYaxis()->SetTitle( "#theta (rad)" );
            u_hzt->GetXaxis()->SetTitle( "Z (cm)");
            u_hzt->GetYaxis()->SetTitleOffset(1.4);
            u_hzt->GetYaxis()->CenterTitle();

            u_hzt->Draw("colz");
            c.SetLogz();
            u_hzt->Draw("colz");


            Double_t z[12] =  {  -950 , -950 , -825 , -325 , 500 ,
                1500 , 2575 , 2900 , 3000 , 10000 ,
                10000 , -950 };

            Double_t t[12] = { 0.0150 , 0.0110 , 0.0085 , 0.0060 , 0.0040 ,
                0.0030 , 0.0025 , 0.0016 , 0.0000 , 0.0000 , 
                0.0150 , 0.0150 };

            TGraph th( 12, z, t );

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");


            TLegend leg{ 0.23, 0.65, 0.43, 0.8 };
            leg.AddEntry( &th, "Signal region", "lp" );
            //leg.AddEntry( &nth, "Scaling region", "lp" );
            leg.Draw( "same" );

            c.Print( "output/halo_zt_pre_lower.pdf", "pdf" );
        }

        //PCDA
        {
            auto h_lower_pcda = all_halo_region_plot( "pre_lower_plots", "h_p_cda" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.16);
            prep( h_lower_pcda);
            h_lower_pcda->Draw("colz");
            h_lower_pcda->GetXaxis()->SetRangeUser(0, 70 );
            h_lower_pcda->GetYaxis()->SetRangeUser( 0, 10  );
            h_lower_pcda->GetYaxis()->SetTitle( "CDA (cm)" );
            h_lower_pcda->GetXaxis()->SetTitle( "P (GeV/c)");
            h_lower_pcda->GetYaxis()->CenterTitle();
            c.Print( "output/halo_p_cda_pre_lower.pdf", "pdf" );

            Double_t p[2] =  { 0, 70 };
            Double_t cda[2] = { 3.0, 3.0 };
            TGraph th( 2, p, cda );

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");
            c.Print( "output/halo_p_cda_pre_lower_cut.pdf", "pdf" );
        }
        {
            auto h_upper_pcda = all_halo_region_plot( "pre_upper_plots", "h_p_cda" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.16);
            prep( h_upper_pcda);
            h_upper_pcda->Draw("colz");
            h_upper_pcda->GetXaxis()->SetRangeUser(0, 70 );
            h_upper_pcda->GetYaxis()->SetRangeUser( 0, 10  );
            h_upper_pcda->GetYaxis()->SetTitle( "CDA (cm)" );
            h_upper_pcda->GetXaxis()->SetTitle( "P (GeV/c)");
            h_upper_pcda->GetYaxis()->CenterTitle();
            c.Print( "output/halo_p_cda_pre_upper.pdf", "pdf" );

            Double_t p[2] =  { 0, 70 };
            Double_t cda[2] = { 3.0, 3.0 };
            TGraph th( 2, p, cda );

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");
            c.Print( "output/halo_p_cda_pre_upper_cut.pdf", "pdf" );
        }

        //Pm2m
        {
            auto h_m2_t = all_halo_region_plot( "pre_plots", "h_m2_t" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.13);
            c.SetLeftMargin(0.13);
            prep( h_m2_t);
            h_m2_t->GetYaxis()->SetTitle( "#theta (rad)" );
            h_m2_t->Draw("colz");
            h_m2_t->GetXaxis()->SetTitleOffset(1.2 );
            h_m2_t->GetYaxis()->SetTitleOffset(1.3 );
            h_m2_t->GetYaxis()->CenterTitle();
            h_m2_t->GetXaxis()->SetRangeUser( -0.6, 0.2  );
            c.Print( "output/halo_m2_t.pdf", "pdf" );
        }

        //PT
        {
            auto h_lower_pt = all_halo_region_plot( "pre_lower_plots", "h_p_t" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetLogz();
            c.SetGrid();
            c.SetRightMargin(0.13);
            c.SetLeftMargin(0.13);
            prep( h_lower_pt);
            h_lower_pt->Draw("colz");
            h_lower_pt->GetYaxis()->SetTitleOffset(1.9 );
            h_lower_pt->GetXaxis()->SetRangeUser(0, 30 );
            h_lower_pt->GetYaxis()->SetRangeUser( 0, 0.015  );
            h_lower_pt->GetYaxis()->SetTitle( "#theta (rad)" );
            h_lower_pt->GetXaxis()->SetTitle( "P (GeV/c)");
            h_lower_pt->GetYaxis()->CenterTitle();

            Double_t t[6] = {  30.00 , 0.00, 12.0, 30, 30, 0 };

            Double_t phi[6] = { 0.10, 0.015, 0.00, 0.0, 0.015, 0.015 };

            TGraph th( 6, t, phi);

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");
            c.Print( "output/halo_p_t_pre_lower.pdf", "pdf" );
        }

        {
            auto h_upper_txty = all_halo_region_plot( "pre_upper_plots", "h_txty" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.16);
            prep( h_upper_txty);
            h_upper_txty->Draw("colz");
            h_upper_txty->GetYaxis()->SetTitle( "#theta_{y}" );
            h_upper_txty->GetXaxis()->SetTitle( "#theta_{x}" );
            h_upper_txty->GetYaxis()->CenterTitle();
            c.Print( "output/halo_txty_pre_upper.pdf", "pdf" );
        }

        {
            auto h_upper_tphi = all_halo_region_plot( "pre_upper_plots", "h_t_phi" );
            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetRightMargin(0.16);
            prep( h_upper_tphi);
            h_upper_tphi->Draw("colz");
            h_upper_tphi->GetXaxis()->SetTitle( "#theta" );
            h_upper_tphi->GetYaxis()->SetTitle( "#phi" );
            h_upper_tphi->GetYaxis()->CenterTitle();
            static_cast<TH2D*>(h_upper_tphi)->Rebin2D(2, 2);
            c.Print( "output/halo_tphi_pre_upper.pdf", "pdf" );

            Double_t t[17] = {  0.000  ,
                 0.020  ,  0.020  ,  0.012  ,  0.009  ,
                 0.006  ,  0.005  ,  0.004  ,  0.004  ,
                 0.005  ,  0.006  ,  0.009  ,  0.012  ,
                 0.020  ,  0.020  ,  0.000  ,  0.000  };

            Double_t phi[17] = { -0.001 ,
                 0.00  ,  0.73  ,  0.90  ,  1.51  ,
                 2.30  ,  2.60  ,  3.20  ,  3.40  ,
                 4.00  ,  4.30  ,  4.77  ,  5.38  ,
                 5.55  ,  6.40  ,  6.40  ,  -0.001  };

            TGraph th( 17, t, phi);

            th.SetLineColor(kPink);
            th.SetMarkerColor(kPink);
            th.SetMarkerSize(0.6);
            th.SetLineWidth(2);
            th.Draw("same,P,L");

            c.Print( "output/halo_tphi_pre_upper_cuts.pdf", "pdf" );
        }
    }

    {
        TFile tf( "data/halo_upper.q11t.root" );

        {
            auto hm2m_data = get_hist( tf, "halo_upper_m2m/hdata" );
            auto hm2m_stack = get_thing<THStack>( tf, "halo_upper_m2m/hnu_stack" );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            hm2m_stack->Draw();

            hm2m_stack->GetXaxis()->SetRangeUser( -0.5, 0.2 );
            hm2m_stack->SetMinimum( 1 );
            hm2m_stack->SetMaximum( 5000 );

            hm2m_stack->GetXaxis()->SetTitle( "m^{2}_{miss} GeV^{2}/c^{4}" );
            hm2m_stack->GetYaxis()->SetTitle( "" );

            hm2m_data->Draw("same, E1" );

            c.SetLogy();

            TList * hlist = hm2m_stack->GetHists();

            TLegend legd( 0.15, 0.57, 0.30, 0.87 );
            legd.SetTextFont( 133 );
            legd.SetTextSize( 14 );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos") ) , "K_{#mu2}", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos") ) , "halo", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K_{3#pi0}", "f"  );

            legd.Draw("same");

            c.Print( "output/halo_upper_ctrl_m2m.pdf", "pdf");
        }

        {
            auto hp_data = get_hist( tf, "halo_upper_p/hdata" );
            auto hp_stack = get_thing<THStack>( tf, "halo_upper_p/hnu_stack" );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            hp_stack->Draw();

            hp_stack->GetXaxis()->SetRangeUser( 0, 50 );
            hp_stack->SetMinimum( 0 );
            hp_stack->SetMaximum( 14000 );

            hp_stack->GetXaxis()->SetTitle( "Muon momentum (GeV/c)" );
            hp_stack->GetYaxis()->SetTitle( "" );

            hp_data->Draw("same, E1" );

            TList * hlist = hp_stack->GetHists();

            TLegend legd( 0.70, 0.57, 0.85, 0.87 );
            legd.SetTextFont( 133 );
            legd.SetTextSize( 14 );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos") ) , "K_{#mu2}", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos") ) , "halo", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "k3pi0_pos") ) , "K_{3#pi0}", "f"  );

            legd.Draw("same");

            c.Print( "output/halo_upper_ctrl_p.pdf", "pdf");
        }
    }

    {
        TFile tf( "data/halo_lower.q11t.root" );

        {
            auto hz_data = get_hist( tf, "halo_lower_neg_m2m_z/hdata" );
            auto hz_stack = get_thing<THStack>( tf, "halo_lower_neg_m2m_z/hnu_stack" );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();
            c.SetLogy();

            hz_stack->Draw();
            hz_stack->GetXaxis()->SetRangeUser( -2000, 2000 );
            hz_stack->SetMinimum( 1 );
            hz_stack->SetMaximum( 2e5 );

            hz_stack->GetXaxis()->SetTitle( "reconstructed vertex z (cm)" );
            hz_stack->GetYaxis()->SetTitle( "" );

            hz_data->Draw("same, E1" );

            TList * hlist = hz_stack->GetHists();

            TLegend legd( 0.70, 0.72, 0.85, 0.87 );
            legd.SetTextFont( 133 );
            legd.SetTextSize( 14 );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos") ) , "K_{#mu2}", "f"  );
            legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos") ) , "halo", "f"  );
            legd.Draw("same");

            c.Print( "output/halo_lower_ctrl_z.pdf", "pdf");

        }

        auto hp_data = get_hist( tf, "halo_lower_neg_m2m_p/hdata" );
        auto hp_stack = get_thing<THStack>( tf, "halo_lower_neg_m2m_p/hnu_stack" );

        TCanvas c( "c", "c", 350, 350 );
        c.SetGrid();

        hp_stack->Draw();

        hp_stack->GetXaxis()->SetRangeUser( 25, 55 );

        hp_stack->SetMinimum( 0 );
        hp_stack->SetMaximum( 40000 );

        hp_stack->GetXaxis()->SetTitle( "Muon momentum (GeV/c)" );
        hp_stack->GetYaxis()->SetTitle( "" );

        hp_data->Draw("same, E1" );



        TList * hlist = hp_stack->GetHists();

        TLegend legd( 0.15, 0.72, 0.30, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "km2_pos") ) , "K_{#mu2}", "f"  );
        legd.AddEntry( static_cast<TH1*>( hlist->FindObject( "halo_pos") ) , "halo", "f"  );

        legd.Draw("same");

        c.Print( "output/halo_lower_ctrl_p.pdf", "pdf");
    }

    {
        TFile tfl( "data/halo_lower.q11t.root" );
        TFile tfu( "data/halo_upper.q11t.root" );

        {
            TH1 * hl_neg = get_hist( tfl, "halo_signal_lower_zt/hnu_stack_hists/halo_neg" );
            TH1 * hl_pos = get_hist( tfl, "halo_signal_lower_zt/hnu_stack_hists/halo_pos" );
            TH2 * hl = static_cast<TH2*>(hl_neg);
            hl->Add( hl_pos );

            TH1 * hu_neg = get_hist( tfu, "halo_signal_upper_zt/hnu_stack_hists/halo_neg" );
            TH1 * hu_pos = get_hist( tfu, "halo_signal_upper_zt/hnu_stack_hists/halo_pos" );
            TH2 * hu = static_cast<TH2*>(hu_neg);
            hu->Add( hu_pos );

            hl->GetXaxis()->SetRangeUser(-2000, 8000 );
            hl->GetYaxis()->SetRangeUser( 0, 0.015  );
            hl->GetYaxis()->SetTitle( "#theta (rad)" );
            hl->GetXaxis()->SetTitle( "Z (cm)");
            hl->GetYaxis()->SetTitleOffset(2.2);
            hl->GetYaxis()->CenterTitle();
            hl->GetXaxis()->SetNdivisions( 7 );
            hl->GetYaxis()->SetNdivisions( 9 );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            c.SetLeftMargin(0.18);

            hl->SetMarkerColor( kCyan-8 );
            hu->SetMarkerColor( kGreen+4 );

            hl->SetFillColor( kCyan-8 );
            hu->SetFillColor( kGreen+4 );

            hl->SetMarkerStyle( 21 );
            hu->SetMarkerStyle( 21 );
            hl->SetMarkerSize( 0.2 );
            hu->SetMarkerSize( 0.2 );

            hl->SetTitle( "" );
            hu->SetTitle( "" );

            hl->Draw();
            hu->Draw("same");

            TLegend legd( 0.55, 0.72, 0.85, 0.87 );
            legd.SetTextFont( 133 );
            legd.SetTextSize( 14 );
            legd.AddEntry( static_cast<TH1*>( hu ) , "upper region", "f"  );
            legd.AddEntry( static_cast<TH1*>( hl) , "lower region", "f"  );

            legd.Draw("same");

            c.Print( "output/halo_sig_zt.pdf", "pdf");
        }

        {
            TH1 * hl_neg = get_hist( tfl, "halo_signal_lower_m2m/hnu_stack_hists/halo_neg" );
            TH1 * hl_pos = get_hist( tfl, "halo_signal_lower_m2m/hnu_stack_hists/halo_pos" );
            TH1 * hl = static_cast<TH2*>(hl_neg);
            hl->Add( hl_pos );
            hl->SetFillColor( kCyan-8);
            hl->SetLineColor( kCyan-8);

            TH1 * hu_neg = get_hist( tfu, "halo_signal_upper_m2m/hnu_stack_hists/halo_neg" );
            TH1 * hu_pos = get_hist( tfu, "halo_signal_upper_m2m/hnu_stack_hists/halo_pos" );
            TH1 * hu = static_cast<TH2*>(hu_neg);
            hu->Add( hu_pos );

            hu->SetFillColor(kGreen+4);
            hu->SetLineColor(kGreen+4);

            hl->GetXaxis()->SetTitle("m^{2}_{miss} (GeV^{2}/c^{4} )");

            THStack hstack_m2m;
            hstack_m2m.Add( hl );
            hstack_m2m.Add( hu );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            hstack_m2m.Draw();

            hstack_m2m.GetXaxis()->SetTitle("m^{2}_{miss} (GeV^{2}/c^{4} )");
            hstack_m2m.GetXaxis()->SetRangeUser( -0.2, 0.2);


            hu->SetTitle("");


            hu->GetXaxis()->SetRangeUser(-0.19, 0.19 );
            hu->GetYaxis()->SetRangeUser( 0, 700 );
            hu->GetYaxis()->SetTitle( "" );

            hstack_m2m.Draw();
            c.Print( "output/halo_sig_m2m.pdf", "pdf");
        }
    }

    {
        TFile tf ( "data/halo_k3pi.q11t.root" );

        TH1 * h_up_kless = get_hist( tf, "halo_sig_upper_m2m/hnu_stack_hists/halo_kless_pos" );
        TH1 * h_low_kless = get_hist( tf, "halo_sig_lower_m2m/hnu_stack_hists/halo_kless_pos" );

        TH1 * h_kless = h_up_kless;
        h_kless->Add( h_low_kless );

        TH1 * h_up_k3pi = get_hist( tf, "halo_sig_upper_m2m/hnu_stack_hists/k3pi_pos" );
        TH1 * h_low_k3pi = get_hist( tf, "halo_sig_lower_m2m/hnu_stack_hists/k3pi_pos" );

        TH1 * h_k3pi = h_up_k3pi;
        h_k3pi->Add( h_low_k3pi );

        TH1 * h_up_data = get_hist( tf, "halo_sig_upper_m2m/hdata" );
        TH1 * h_low_data = get_hist( tf, "halo_sig_lower_m2m/hdata" );

        TH1 * h_data = h_up_data;
        h_up_data->Add( h_low_data );

        TCanvas c( "c", "c", 350, 350 );
        c.SetGrid();

        h_kless->GetXaxis()->SetTitle("m^{2}_{miss} (GeV^{2}/c^{4} )");
        h_kless->GetXaxis()->SetRangeUser( -0.2, 0.2);

        THStack hstack;
        hstack.Add( h_kless );
        hstack.Add( h_k3pi );

        hstack.Draw();

        hstack.GetXaxis()->SetTitle("m^{2}_{miss} (GeV^{2}/c^{4} )");
        hstack.GetXaxis()->SetRangeUser( -0.2, 0.2);

        hstack.Draw();

        h_data->SetMarkerColor( kBlack );
        h_data->SetLineWidth( 2 );
        h_data->SetLineColor( kBlack );
        h_data->Draw("same,E1" );

        TLegend legd( 0.15, 0.60, 0.40, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );
        legd.AddEntry( h_k3pi , "K_{3#pi}", "f"  );
        legd.AddEntry( h_kless , "halo (Kless)", "f"  );
        legd.AddEntry( h_data, "halo (K^{-})", "lep"  );

        legd.Draw("same");
        c.Print( "output/halo_kless_vs_km.pdf", "pdf");
    }

    {
        TFile tf{"data/shuffle.halo_signal.q11t.root" };

        THStack * h_upper = get_thing<THStack>( tf, "halo_sig_muv_upper_m2m/hnu_stack" );
        THStack * h_lower = get_thing<THStack>( tf, "halo_sig_muv_lower_m2m/hnu_stack" );

        TList * h_up_l = h_upper->GetHists();
        TList * h_lw_l = h_lower->GetHists();


        THStack hstack;

        for ( int i = 0 ; i != h_up_l->GetSize() ; ++i  )
        {
            TH1 * h_up = static_cast<TH1*>( h_up_l->At( i ) );
            TH1 * h_lw = static_cast<TH1*>( h_lw_l->At(i) );

            hstack.Add( h_up );
            hstack.Add( h_lw );
        }

        TH1 * h_dt_upper = get_thing<TH1>( tf, "halo_sig_muv_upper_m2m/hdata" );
        TH1 * h_dt_lower = get_thing<TH1>( tf, "halo_sig_muv_lower_m2m/hdata" );

        TH1 * h_dt = h_dt_upper;
        h_dt->Add( h_dt_lower );

        TLegend legd( 0.65, 0.53, 0.85, 0.87 );
        legd.SetTextFont( 133 );
        legd.SetTextSize( 14 );

        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "km2_pos") )   , "K_{#mu2}", "f"  );
        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "km3_pos") )   , "K_{#mu3}", "f"  );
        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "k2pig_pos") ) , "K_{2#pi}", "f"  );
        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "k3pi0_pos") ) , "K_{3#pi0}", "f" );
        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "k3pi_pos") )  , "K_{3#pi}", "f"  );
        legd.AddEntry( static_cast<TH1*>( h_up_l->FindObject( "halo_pos") )  , "halo",     "f"  );
        legd.AddEntry( h_dt, "data", "lep");

        TCanvas c( "c", "c", 350, 350 );
        c.SetGrid();

        hstack.Draw();

        hstack.GetXaxis()->SetRangeUser( -0.1, 0.2 );
        hstack.GetXaxis()->SetTitle( "m^{2}_{miss} (GeV^{2}/c^{4})");
        hstack.GetYaxis()->SetRangeUser( 0,  1000 );

        hstack.SetMinimum( 0 );
        hstack.SetMaximum( 1000 );

        hstack.Draw();

        h_dt->SetLineColor(kBlack );
        h_dt->SetLineWidth(2);
        h_dt->Draw("same, E1" );

        legd.Draw("same" );

        c.Print( "output/halo_full_muv_pos.pdf" , "pdf" );

        hstack.SetMinimum( 100 );
        hstack.SetMaximum( 2000000 );

        hstack.Draw();
        c.SetLogy();
        h_dt->Draw("same, E1" );
        legd.Draw("same" );
        c.Print( "output/halo_full_muv_pos_log.pdf" , "pdf" );



    }
}

void plot()
{
    run();
}
