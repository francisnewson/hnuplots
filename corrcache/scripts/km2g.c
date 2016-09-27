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

void prep( TH1& h, int color, TLegend & leg, std::string name )
{
        h.SetLineWidth( 2 );
        h.GetYaxis()->SetTitle("") ;
        h.SetLineColor(color);
        h.Rebin(10);
        leg.AddEntry( &h, name.c_str(), "l" );
}

void km2g_sub()
{
    gStyle->SetOptStat(0);
    TFile tf{ "data/log_km2_sub.root" };

    TLegend leg( 0.15,0.3, 0.4,0.7);

    //full signal data set
    {
        auto hraw = sum( tf, "km2_sub/p5.km2.full.{pol}/signal_{reg}_plots/h_m2m_kmu/hraw" );
        prep( *hraw, kBlack, leg, "IB" );
        auto hintp = sum( tf, "km2_sub/p5.km2.full.{pol}/signal_{reg}_plots/h_m2m_kmu/hintp" );
        prep( *hintp, kRed, leg, "INT+" );
        auto hintm = sum( tf, "km2_sub/p5.km2.full.{pol}/signal_{reg}_plots/h_m2m_kmu/hintm" );
        prep( *hintm, kBlue, leg, "INTM" );
        auto hsdp = sum( tf, "km2_sub/p5.km2.full.{pol}/signal_{reg}_plots/h_m2m_kmu/hsdp" );
        prep( *hsdp, kGreen + 2, leg, "SDP");
        auto hsdm = sum( tf, "km2_sub/p5.km2.full.{pol}/signal_{reg}_plots/h_m2m_kmu/hsdm" );
        prep( *hsdm, kOrange + 2, leg, "SDM" );

        TCanvas c( "c", "c", 400, 800 );
        c.SetGrid();
        hraw->Draw();
        hraw->SetMaximum(450);
        hraw->SetMinimum(-50);
        hraw->GetXaxis()->SetRangeUser(0, 0.2);
        hintp->Draw("same");
        hintm->Draw("same");
        hsdp->Draw("same");
        hsdm->Draw("same");

        leg.Draw("same");

        c.Print( "output/km2_sub.pdf");
    }
}

void km2g(){ km2g_sub(); }
