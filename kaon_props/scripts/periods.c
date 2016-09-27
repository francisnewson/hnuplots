#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <iomanip>

TTree * get_ttree( TFile& tf, std::string name )
{
    TTree * h = 0;
    tf.GetObject( name.c_str(), h );
    if( !h )
    {
        throw std::runtime_error( "Can't find " + name );
    }
    return h;
}

struct kaon_burst
{
    Long64_t run;
    Long64_t burst_time;
    Long64_t count;
    Double_t dxdz;
    Double_t dydz;
    Double_t xoff;
    Double_t yoff;
    Double_t pmag;
    Double_t alpha;
    Double_t beta;
    Int_t pol;
};

struct magnet_burst
{
    Long64_t run;
    Long64_t burst_time;
    Double_t poskick;
    Double_t negkick;
};

void do_plots()
{
    TFile tfin ( "data/all.kaon_props.root" );

    std::vector<std::string> channels {
        "p5.data.q11t.v3.neg",
            "p5.data.q11t.v3.pos",
            "p6.data.km.q11t.v2.neg",
            "p6.data.km.q11t.v2.pos",
            "p6.data.kless.q11t.v2.pos",
    };
    std::vector<std::string> trees{ "KPLUSTREE", "KMINUSTREE" };

    TCanvas c ( "c", "c", 500, 500 );

    for( auto chan : channels )
    {
        for (auto tree: trees )
        {

            auto t = get_ttree( tfin, chan + "/kaon_props/" + tree);

            kaon_burst kb{ 0,0,0,0,0,0,0,0,0,0,0};

            t->SetBranchAddress( "kaon_burst", &kb.run );
            Long64_t n = t->GetEntries();

            //n = 100;

            std::ofstream ofs( Form("output/data/%s_kaon_props_%s.dat", chan.c_str(), tree.c_str() ));

            ofs
                << std::setw(20) << "run"
                << std::setw(20) << "burst_time"
                << std::setw(20) << "count"
                << std::setw(20) << "dxdz"
                << std::setw(20) << "dydz"
                << std::setw(20) << "xoff"
                << std::setw(20) << "yoff"
                << std::setw(20) << "pmag"
                << std::setw(20) << "alpha"
                << std::setw(20) << "beta"
                << std::setw(20) << "pol"
                << "\n";

            for ( Long64_t e = 0  ; e != n ; ++ e )
            {
                t->GetEntry( e );
                ofs
                    << std::setw(20) << kb.run
                    << std::setw(20) << kb.burst_time
                    << std::setw(20) << kb.count
                    << std::setw(20) << kb.dxdz
                    << std::setw(20) << kb.dydz
                    << std::setw(20) << kb.xoff
                    << std::setw(20) << kb.yoff
                    << std::setw(20) << kb.pmag
                    << std::setw(20) << kb.alpha
                    << std::setw(20) << kb.beta
                    << std::setw(20) << kb.pol
                    << "\n";
            }
        }

        //mpn33
        std::string tree = "MPN33TREE";
        auto t = get_ttree( tfin, chan + "/kaon_props/" + tree);
        magnet_burst mb{ 0,0,0,0};
        t->SetBranchAddress( "mpn33_burst", &mb.run );

        Long64_t n = t->GetEntries();
        std::ofstream ofs( Form("output/data/%s_magnet_burst.dat", chan.c_str() ) );

        ofs
            << std::setw(20) << "run"
            << std::setw(20) << "burst_time"
            << std::setw(20) << "poskick"
            << std::setw(20) << "negkick"
            << "\n";

        for ( Long64_t e = 0  ; e != n ; ++ e )
        {
            t->GetEntry( e );
            ofs
                << std::setw(20) << mb.run
                << std::setw(20) << mb.burst_time
                << std::setw(20) << mb.poskick
                << std::setw(20) << mb.negkick
                << "\n";
        }

    }
}

void periods()
{
    do_plots();
}
