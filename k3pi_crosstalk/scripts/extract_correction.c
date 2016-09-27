template <typename T>
double sum_variable( std::string branch, TTree* tt )
{
    Long64_t nEntries = tt->GetEntries();
    double total_weight = 0.0;
    T  weight = 0;
    Int_t check = tt->SetBranchAddress( branch.c_str(), &weight );
    if ( check != 0 )
    {
        throw std::runtime_error(
                std::string("https://root.cern.ch/root/html/"
                    "TTree.html#TTree:CheckBranchAddressType")
                + std::to_string( check ) );

    }
    tt->SetBranchStatus( "*", 0 );
    tt->SetBranchStatus( branch.c_str(), 1 );
    for ( int i = 0 ; i != nEntries ; ++i )
    {
        tt->GetEntry(i);
        total_weight += double(weight);
    }
    return  total_weight;
}

double extract_fid( TFile& tf, std::string chan )
{
    auto tree = get_thing<TTree>(tf, Form( "%s/sample_burst_count/bursts", chan.c_str() ) );
    return sum_variable<Double_t>( "weight", tree );
}

void do_correction()
{
    //std::string selection = "signal_loose";
    std::string selection = "signal";
    auto sel = selection.c_str();

    //std::string outfolder = "k3pi_sub";
    std::string outfolder = "k3pi_sub_tgt";
    auto fol = outfolder.c_str();

    //std::string selkey = "loose_";
    std::string selkey = "";
    auto key = selkey.c_str();


    TFile tf { "data/2015-09-13/all.k3pi_crosstalk.root" };
    TFile tfout{ "output/k3pi_checks.root", "RECREATE"};
    //--------------------------------------------------
    //P5 Km2 reco
    //--------------------------------------------------

    double global_p5_halo_scale = 0;
    double global_p5_rk_flux = 0;

    //actual halo scaling
    {
        //how much do we scale kless by to match km?
        auto h_p6_kless_km = get_thing<TH1D>( tf, 
                Form("p6.data.kless.q11t.km.v2.pos/"
                "km2/neg/"
                "%s_upper_nocda_plots/h_cda", sel ) );

        auto h_p5_kp_km = get_thing<TH1D>( tf, 
                Form("p5.data.q11t.km.v3.pos/"
                "km2/neg/"
                "%s_upper_nocda_plots/h_cda", sel) );

        auto halo_integral = []( TH1D& h ){ return integral( h, 5, 9 ); };

        double kless_neg = halo_integral( *h_p6_kless_km );
        double km_neg = halo_integral( *h_p5_kp_km );
        double p5_halo_scale = km_neg / kless_neg;

        global_p5_halo_scale = p5_halo_scale;

        std::cout << "p5 halo scale: " << p5_halo_scale << std::endl;

        //--------------------------------------------------

        //estimate km2 flux
        auto h_p6_kless_kp = get_thing<TH1D>( tf, 
                "p6.data.kless.q11t.v2.pos/"
                "rk/pos/rk_plots/h_m2m_kmu" );

        auto h_p5_kp_kp = get_thing<TH1D>( tf, 
                "p5.data.q11t.v3.pos/"
                "rk/pos/rk_plots/h_m2m_kmu" );

        auto rk_halo_integral = [] ( TH1D& h ){ return integral(h, -0.3, -.075 ); };
        double kless_rk_negm2m = rk_halo_integral( *h_p6_kless_kp );
        double kp_rk_negm2m = rk_halo_integral( *h_p5_kp_kp );
        double p5_rk_halo_scale = kp_rk_negm2m / kless_rk_negm2m;

        std::cout << "p5 rk halo scale: " << p5_rk_halo_scale << std::endl;

        auto h_p5_km2 = get_thing<TH1D>( tf,
                "p5.km2.v2.pos/"
                "rk/pos/rk_plots/h_m2m_kmu" );

        auto rk_peak_integral = [] ( TH1D& h ){ return integral(h, -0.015, 0.015 ); };
        auto kless_rk_peak = rk_peak_integral( *h_p6_kless_kp );
        auto kp_rk_peak = rk_peak_integral( *h_p5_kp_kp );
        auto km2_rk_peak = rk_peak_integral( *h_p5_km2 );

        double p5_rk_peak_scale = (kp_rk_peak - (kless_rk_peak * p5_rk_halo_scale)) / km2_rk_peak ;
        double p5_km2_fid = extract_fid( tf, "p5.km2.v2.pos" );

        std::cout << "p5_km2_fid: " << p5_km2_fid << std::endl;

        double p5_rk_kflux  = p5_rk_peak_scale * p5_km2_fid / 0.6355;

        std::cout << "p5 rk peak scale: " << p5_rk_peak_scale << std::endl;
        std::cout << "p5 rk kflux: " << p5_rk_kflux << std::endl;

        global_p5_rk_flux = p5_rk_kflux;

        //--------------------------------------------------
    }

    //--------------------------------------------------
    //P5 K3pi reco
    //--------------------------------------------------
    {
        //resuse halo scale
        auto p5_halo_scale = global_p5_halo_scale;

        //estimate km2 flux
        auto h_p6_kless_km = get_thing<TH1D>( tf,
                Form( "p6.data.kless.q11t.km.v2.pos/"
                "km2/neg/%s_upper_plots/h_m2m_kmu", sel ) );

        auto h_p5_kp_km = get_thing<TH1D>( tf,
                Form("p5.data.q11t.km.v3.pos/"
                "km2/neg/%s_upper_plots/h_m2m_kmu", sel ) );

        auto h_p5_k3pi_km = get_thing<TH1D>( tf,
                Form( "p5.k3pi.km.v2.pos/"
                "km2/neg/%s_upper_plots/h_m2m_kmu", sel) );

        auto k3pi_peak_integral = [](TH1D & h){ return integral( h, 0.11, 0.14 ); };

        double p5_k3pi_halo_peak = k3pi_peak_integral( *h_p6_kless_km );
        double p5_k3pi_data_peak = k3pi_peak_integral( *h_p5_kp_km );
        double p5_k3pi_peak_peak = k3pi_peak_integral( *h_p5_k3pi_km );

        double p5_k3pi_peak_scale = ( p5_k3pi_data_peak - ( p5_k3pi_halo_peak * p5_halo_scale )) / p5_k3pi_peak_peak;
        double p5_k3pi_fid = extract_fid( tf, "p5.k3pi.km.v2.pos" );
        double p5_k3pi_kflux = p5_k3pi_peak_scale * p5_k3pi_fid / 0.0559;

        std::cout << "sub: " <<  p5_k3pi_data_peak << " - " << p5_k3pi_halo_peak * p5_halo_scale  << std::endl;
        std::cout << "stack scale: " <<  ( p5_k3pi_data_peak - ( p5_k3pi_halo_peak * p5_halo_scale )) << " / "
            << p5_k3pi_peak_peak << std::endl;

        std::cout << "p5 k3pi peak scale " <<  p5_k3pi_peak_scale << std::endl;

        std::cout << "p5 k3pi kflux " <<  p5_k3pi_kflux << std::endl;

        double correction_factor = p5_k3pi_kflux / global_p5_rk_flux;

        std::cout << "Correction factor: " << correction_factor << std::endl;

        //do subtraction game
        h_p6_kless_km->Rebin( 25 );
        h_p5_kp_km->Rebin(25 );
        h_p5_k3pi_km->Rebin(25);

        h_p6_kless_km->Sumw2();
        h_p5_kp_km->Sumw2();
        h_p5_k3pi_km->Sumw2();

        auto * sub_data = tclone( *h_p5_kp_km );
        sub_data->Add( h_p6_kless_km, -1.0 * p5_halo_scale);
        sub_data->Divide( h_p5_k3pi_km );
        TF1 fit_k3pi_scale( "myfit", "pol0", 0.08, 0.14 );
        sub_data->Fit( "myfit", "", "", 0.08, 0.14 );
        tfout.cd();
        sub_data->Write( "p5_ratio" );
    }

    //--------------------------------------------------
    //P6 K3pi reco
    //--------------------------------------------------
    double global_p6_halo_scale = 0;
    double global_p6_rk_flux = 0;

    {
        //determine halo scale
        //how much do we scale kless by to match kp?
        auto h_p6_kless_kp = get_thing<TH1D>( tf, 
                Form("p6.data.kless.q11t.v2.pos/"
                "km2/pos/"
                "%s_upper_nocda_plots/h_cda", sel) );

        auto h_p6_km_kp = get_thing<TH1D>( tf, 
                Form("p6.data.km.q11t.v2.pos/"
                "km2/pos/"
                "%s_upper_nocda_plots/h_cda", sel) );

        auto halo_integral = []( TH1D& h ){ return integral( h, 5, 9 ); };

        double kless_neg = halo_integral( *h_p6_kless_kp );
        double kp_neg = halo_integral( *h_p6_km_kp );
        double p6_halo_scale = kp_neg / kless_neg;
        std::cout << "p6 halo scale: " << p6_halo_scale << std::endl;
        global_p6_halo_scale = p6_halo_scale;

        //--------------------------------------------------

        //estimate km2 flux
        auto h_p6_kless_km = get_thing<TH1D>( tf, 
                "p6.data.kless.q11t.km.v2.pos/"
                "rk/neg/rk_plots/h_m2m_kmu" );

        auto h_p6_km_km = get_thing<TH1D>( tf, 
                "p6.data.km.q11t.km.v2.pos/"
                "rk/neg/rk_plots/h_m2m_kmu" );

        auto rk_halo_integral = [] ( TH1D& h ){ return integral(h, -0.3, -.075 ); };
        double kless_rk_negm2m = rk_halo_integral( *h_p6_kless_km );
        double km_rk_negm2m = rk_halo_integral( *h_p6_km_km );
        double p6_rk_halo_scale = km_rk_negm2m / kless_rk_negm2m;

        std::cout << "p6 rk halo scale: " << p6_rk_halo_scale << std::endl;

        auto h_p6_km2 = get_thing<TH1D>( tf,
                "p6.km2.v2.pos/"
                "rk/neg/rk_plots/h_m2m_kmu" );

        auto rk_peak_integral = [] ( TH1D& h ){ return integral(h, -0.015, 0.015 ); };
        auto kless_rk_peak = rk_peak_integral( *h_p6_kless_km );
        auto km_rk_peak = rk_peak_integral( *h_p6_km_km );
        auto km2_rk_peak = rk_peak_integral( *h_p6_km2 );

        double p6_rk_peak_scale = (km_rk_peak - (kless_rk_peak * p6_rk_halo_scale)) / km2_rk_peak ;
        double p6_km2_fid = extract_fid( tf, "p6.km2.v2.pos" );

        std::cout << "p6_km2_fid: " << p6_km2_fid << std::endl;

        double p6_rk_kflux  = p6_rk_peak_scale * p6_km2_fid / 0.6355;

        std::cout << "p6 rk peak scale: " << p6_rk_peak_scale << std::endl;
        std::cout << "p6 rk kflux: " << p6_rk_kflux << std::endl;

        global_p6_rk_flux = p6_rk_kflux;

        //--------------------------------------------------

    }

    {
        p6_halo_scale = global_p6_halo_scale;

        //estimate km2 flux
        auto h_p6_kless_kp = get_thing<TH1D>( tf,
                Form("p6.data.kless.q11t.v2.pos/"
                "km2/pos/%s_lower_plots/h_m2m_kmu", sel) );

        auto h_p6_km_kp = get_thing<TH1D>( tf,
                Form("p6.data.km.q11t.v2.pos/"
                "km2/pos/%s_lower_plots/h_m2m_kmu", sel) );

        auto h_p6_k3pi_kp = get_thing<TH1D>( tf,
                Form("p6.k3pi.v2.pos/"
                "km2/pos/%s_lower_plots/h_m2m_kmu", sel) );

        auto k3pi_peak_integral = [](TH1D & h){ return integral( h, 0.11, 0.14 ); };

        double p6_k3pi_halo_peak = k3pi_peak_integral( *h_p6_kless_kp );
        double p6_k3pi_data_peak = k3pi_peak_integral( *h_p6_km_kp );
        double p6_k3pi_peak_peak = k3pi_peak_integral( *h_p6_k3pi_kp );

        double p6_k3pi_peak_scale = ( p6_k3pi_data_peak - ( p6_k3pi_halo_peak * p6_halo_scale )) / p6_k3pi_peak_peak;
        double p6_k3pi_fid = extract_fid( tf, "p6.k3pi.v2.pos" );
        double p6_k3pi_kflux = p6_k3pi_peak_scale * p6_k3pi_fid / 0.0559;

        std::cout << "sub: " <<  p6_k3pi_data_peak << " - " << p6_k3pi_halo_peak * p6_halo_scale  << std::endl;
        std::cout << "stack scale: " <<  ( p6_k3pi_data_peak - ( p6_k3pi_halo_peak * p6_halo_scale )) << " / "
            << p6_k3pi_peak_peak << std::endl;

        std::cout << "p6 k3pi peak scale " <<  p6_k3pi_peak_scale << std::endl;

        std::cout << "p6 k3pi kflux " <<  p6_k3pi_kflux << std::endl;

        //do subtraction game
        h_p6_kless_kp->Rebin( 25 );
        h_p6_km_kp->Rebin(25 );
        h_p6_k3pi_kp->Rebin(25);

        h_p6_kless_kp->Sumw2();
        h_p6_km_kp->Sumw2();
        h_p6_k3pi_kp->Sumw2();

        auto * sub_data = tclone( *h_p6_km_kp );
        sub_data->Add( h_p6_kless_kp, -1.0 * p6_halo_scale);
        sub_data->Divide( h_p6_k3pi_kp );
        TF1 fit_k3pi_scale( "myfit", "pol0", 0.08, 0.14 );
        sub_data->Fit( "myfit", "", "", 0.09, 0.14 );
        tfout.cd();
        sub_data->Write( "p6_ratio" );

        double correction_factor = p6_k3pi_kflux / global_p6_rk_flux;
        std::cout << "Correction factor: " << correction_factor << std::endl;
    }
#if 0
#endif
}

void extract_correction()
{
    do_correction();
}
