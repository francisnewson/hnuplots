void run()
{
    gStyle->SetPalette(57);
    gStyle->SetOptStat(0);

    {
        TFile tf( "data/shuffle_k3pi_mom.root" );

        TH1 * hk3pi = get_hist( tf, "k2pi_p/hnu_stack_hists/k3pi_pos" );
        TH1 * hdata = get_hist( tf, "k2pi_p/hdata" );

        TCanvas c( "c", "c", 350, 350 );
        c.SetGrid();

        hk3pi->Draw();
        hk3pi->SetTitle("");
        hk3pi->GetXaxis()->SetTitle( "momentum (GeV/c)" );
        hk3pi->GetYaxis()->SetTitle( "" );
        hdata->Draw("E1,same" );

        c.SetLogy();
        c.Print( "output/k3pi_p5_log.pdf", "pdf" );

        c.SetLogy(0);
        hk3pi->SetMinimum(0);
        hk3pi->SetMaximum(1000);
        c.Print( "output/k3pi_p5.pdf", "pdf" );
    }

    {
        TFile tf( "data/all.k3pi.root" );

        {
            TH1 * hp6_kless =
                get_hist( tf, "p6.data.kless.k3pi.v4.pos/k3pi_plots/h_p" );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            hp6_kless->Rebin(10);
            hp6_kless->Draw();

            hp6_kless->SetTitle("");
            hp6_kless->GetXaxis()->SetTitle( "momentum (GeV/c)" );
            hp6_kless->GetYaxis()->SetTitle( "" );

            hp6_kless->SetLineWidth(2);
            hp6_kless->SetLineColor(kGray+3);

            c.Print( "output/k3pi_p5_kless.pdf", "pdf" );
        }

        {
            TH1 * hp6_km =
                get_hist( tf, "p6.data.km.k3pi.v4.pos/k3pi_plots/h_p" );

            TCanvas c( "c", "c", 350, 350 );
            c.SetGrid();

            hp6_km->Rebin(10);
            hp6_km->Draw();

            hp6_km->SetTitle("");
            hp6_km->GetXaxis()->SetTitle( "momentum (GeV/c)" );
            hp6_km->GetYaxis()->SetTitle( "" );

            hp6_km->SetLineWidth(2);
            hp6_km->SetLineColor(kGray+3);

            c.Print( "output/k3pi_p5_km.pdf", "pdf" );
        }
    }
}

void plot(){ run(); }
