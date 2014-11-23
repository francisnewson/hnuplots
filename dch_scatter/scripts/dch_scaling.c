#include <string>
void say_hello()
{
    std::cout << "Hello, world!" << std::endl;
}

double integral( TH1D& h , double min, double max )
{
    int bmin = h.GetXaxis()->FindBin( min);
    int bmax = h.GetXaxis()->FindBin( max);
    return h.Integral(bmin, bmax );
}

TH1D * get_hist( TFile& tf, std::string name )
{
    TH1D * h = 0;
    tf.GetObject( name.c_str(), h );
    if( !h )
    {
        throw std::runtime_error( "Can't find " + name );
    }
    h->SetDirectory(0);
    return h;
}

double get_scale( TFile& tfdata, TFile& tfmc, std::string hname, double min, double max )
{
    TH1D * hdata = get_hist( tfdata, hname );
    TH1D * hmc = get_hist( tfmc, hname );

    double scale = integral( *hdata, min, max)  / integral( *hmc, min, max );

    hmc->SetDirectory(0);
    hdata->SetDirectory(0);
    delete hmc;
    delete hdata;

    return scale;
}



//--------------------------------------------------
TCanvas * dch_scaling( std::string name)
{
    TFile tfdata( "data/all.p5.data.nhod.v2.pos.root"); 
    TFile tfmc( "data/all.p5.k2pig.v2.pos.root");

    std::string hname = "select_k2pi_plots/lkr_dch_cmp/" + name;

    double scale = get_scale( tfdata, tfmc, hname, -0.002, 0.002 );
    std::cout << "Scale: " << scale << std::endl;

    int rebin = 5;

    std::string plot_name = "lkr_dch_cmp/" + name;

    TH1D * hdata = get_hist( tfdata, "select_k2pi_plots/" + plot_name);

    TCanvas * c  = new TCanvas("hc", "hc", 400, 400 );
    c->cd();
    hdata->SetLineColor( kRed +2 );
    hdata->GetXaxis()->SetRange(1, 1000000);
    hdata->Rebin(rebin);
    hdata->Draw("E");
    c->SetLogy();

    for ( int i = 0 ; i != 11; ++i )
    {
        std::string plot_path = "select_k2pi_plots/scatter" 
            + std::to_string(i) + "/" + plot_name;
        TH1D * hmc = get_hist( tfmc, plot_path );
        hmc->Scale( scale );
        hmc->SetLineColor( 30 + i );
        hmc->Rebin(rebin);
        hmc->Draw("same");
    }
    hdata->Draw("E1,same");
    c->Print(("output/"+name+".pdf").c_str(), "pdf" );
    return c;
}

TCanvas * mc_dch_subtract()
{
    std::string plot_name = "lkr_dch_cmp/hdtx";
    TFile tfmc( "data/all.p5.k2pig.v2.pos.root");

    TH1D * hmc0 = get_hist( tfmc, "select_k2pi_plots/scatter0/" + plot_name);
    TH1D * hmc_diff = get_hist( tfmc, "select_k2pi_plots/scatter10/" + plot_name);
    hmc_diff->Add( hmc0, -1 );
    TCanvas * c  = new TCanvas("hc", "hc", 400, 400 );
    c->cd();
    hmc_diff->Draw();
    return c;
}

Double_t my_fit_function( Double_t * x, Double_t * par )
{
    bool reject = true;
    if ( reject && ( x[0] > -0.002) && ( x[0] < 0.001 ) )
    {
        TF1::RejectPoint();
        return 0;
    }

    return 
        par[0]*exp( -0.5 * std::pow( (x[0])/par[1], 2) );
        //+ par[2]*exp( -0.5 * std::pow( (x[0])/par[3], 2))
        //+ par[4]*exp( -0.5 * (x[0])/par[5]);
}

TCanvas * data_dch_subtract()
{
    std::string plot_name = "lkr_dch_cmp/hdp";
    TFile tfmc( "data/all.p5.k2pig.v2.pos.root");
    TFile tfdata( "data/all.p5.data.nhod.v2.pos.root"); 

    TH1D * hmc0 = get_hist( tfmc, "select_k2pi_plots/scatter0/" + plot_name);
    TH1D * hmc_diff = get_hist( tfdata, "select_k2pi_plots/" + plot_name);

    std::string hname = "select_k2pi_plots/lkr_dch_cmp/hdp";
    //double scale = get_scale( tfdata, tfmc, hname, -0.002, 0.002 );
    double scale = get_scale( tfdata, tfmc, hname, -0.01, 0.01 );

    int rebin = 5;

    hmc0->Sumw2();
    hmc0->Rebin(rebin);
    hmc_diff->Sumw2();
    hmc_diff->Rebin(rebin);

    hmc0->Scale( scale );
    hmc_diff->Add( hmc0, -1 );
    TCanvas * c  = new TCanvas("hc", "hc", 400, 400 );
    c->cd();
    hmc_diff->Draw("E1");

    //TF1 * tf1 = new TF1( "f1", my_fit_function, 0.05, 0.25, 6 );
    TF1 * tf1 = new TF1( "f1", my_fit_function, 0.05, 0.20, 2 );
    tf1->SetParLimits( 0, 1, 10000000 );
    //tf1->SetParLimits( 2, 1, 10000000 );
    //tf1->SetParLimits( 4, 1, 10000000 );
    //tf1->SetParameters( 100, 0.1, 50, 0.01, 50, 1 );
    tf1->SetParameters( 100, 0.1);

    hmc_diff->Fit( tf1, "0");
    tf1->Draw("same");

    return c;

}