#define FMT_HEADER_ONLY
#include "scripts/format.h"

std::unique_ptr<TH1> sum( TFile & tf, std::string sel )
{
    auto hup_pos = get_thing<TH1>( tf, fmt::format( sel, fmt::arg( "pol", "pos" ), fmt::arg( "reg" , "upper" ) ) );
    auto hup_neg = get_thing<TH1>( tf, fmt::format( sel, fmt::arg( "pol", "neg" ), fmt::arg( "reg" , "upper" ) ) );
    auto hdn_pos = get_thing<TH1>( tf, fmt::format( sel, fmt::arg( "pol", "pos" ), fmt::arg( "reg" , "lower" ) ) );
    auto hdn_neg = get_thing<TH1>( tf, fmt::format( sel, fmt::arg( "pol", "neg" ), fmt::arg( "reg" , "lower" ) ) ) ;

    auto htot = (TH1*)hup_pos->Clone( "htot" );
    htot->Add( hup_neg );
    htot->Add( hdn_pos );
    htot->Add( hdn_neg );
    return std::unique_ptr<TH1>( htot );
}

void z_dist()
{
    gStyle->SetOptStat(0);
    TFile tf{ "data/all.plots.root"};

    //full signal data set
    {
        auto htot = sum( tf, "p5.data.q11t.v3.{pol}/signal_{reg}_plots/h_z" );
        htot->SetLineColor( kBlack );
        htot->SetLineWidth( 2 );
        htot->GetYaxis()->SetTitle("") ;
        TCanvas c( "c", "c", 400, 400 );
        c.SetGrid();
        htot->Draw();
        c.Print( "output/signal_z.pdf" );
    }

    //high mass signal data set
    {
        auto htot = sum( tf, "p5.data.q11t.v3.{pol}/signal_{reg}_hm2m_plots/h_z" );
        htot->SetLineColor( kBlack );
        htot->SetLineWidth( 2 );
        htot->GetYaxis()->SetTitle("") ;
        TCanvas c( "c", "c", 400, 400 );
        c.SetGrid();
        htot->Draw();
        c.Print( "output/signal_hm2m_z.pdf" );
    }

    //zt plots
    {
        TCanvas c( "c", "c", 800, 800 );
        c.SetGrid();

        auto h_km3 = sum( tf, "p5.km3.v2.{pol}/signal_{reg}_plots/h_z_t" );
        h_km3->Draw("colz");
        h_km3->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/km3_zt.png" );

        auto h_km2 = sum( tf, "p5.km2.v2.{pol}/signal_{reg}_plots/h_z_t" );
        h_km2->Draw("colz");
        h_km2->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/km2_zt.png" );

        auto h_hnu_300 = sum( tf, "mc.p5.hnu.300.nodk.{pol}/signal_{reg}_plots/h_z_t" );
        h_hnu_300->Draw("colz");
        h_hnu_300->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/hnu_300_zt.png" );

        auto h_hnu_350 = sum( tf, "mc.p5.hnu.350.nodk.{pol}/signal_{reg}_plots/h_z_t" );
        h_hnu_350->Draw("colz");
        h_hnu_350->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/hnu_350_zt.png" );
    }

    //high mass zt plots
    {
        TCanvas c( "c", "c", 800, 800 );
        c.SetGrid();

        auto h_km3 = sum( tf, "p5.km3.v2.{pol}/signal_{reg}_hm2m_plots/h_z_t" );
        h_km3->Draw("colz");
        h_km3->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/km3_zt_hm2m.png" );

        auto h_km2 = sum( tf, "p5.km2.v2.{pol}/signal_{reg}_hm2m_plots/h_z_t" );
        h_km2->Draw("colz");
        h_km2->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/km2_zt_hm2m.png" );

        auto h_hnu_300 = sum( tf, "mc.p5.hnu.300.nodk.{pol}/signal_{reg}_hm2m_plots/h_z_t" );
        h_hnu_300->Draw("colz");
        h_hnu_300->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/hnu_300_zt_hm2m.png" );

        auto h_hnu_350 = sum( tf, "mc.p5.hnu.350.nodk.{pol}/signal_{reg}_hm2m_plots/h_z_t" );
        h_hnu_350->Draw("colz");
        h_hnu_350->GetYaxis()->SetRangeUser(0, 0.015 );
        c.Print( "output/hnu_350_zt_hm2m.png" );
    }


}
