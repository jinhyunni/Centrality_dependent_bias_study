void plotMake_avgpTsumInBackward_inMidJetEvents()
{   
    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgpTsumInBackward_inMidJetEvents.root", "read");

    TProfile *avgpTsum = (TProfile *)input -> Get("avgpTsum_midpion0_trigger");

    //Draw
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    gStyle -> SetOptStat();
    {   
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 1.8, 20, 3.5);
        htmp -> GetXaxis() -> SetTitle("#pi^{0}'s p_{T} at |#eta|<1");
        htmp -> GetYaxis() -> SetTitle("#LT#sumpT#GT");

        avgpTsum -> SetMarkerStyle(34);
        avgpTsum -> SetMarkerColor(6);
        avgpTsum -> SetLineColor(6);
        avgpTsum -> Draw("p same");

        TLegend *leg1 = new TLegend(0.4, 0.7, 0.65, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "Pythia8, p+Au 200 GeV", "h");
        leg1 -> AddEntry("", "Angantyr: option3(ND only)", "h");
        leg1 -> AddEntry("", "#LT#sump_{T}#GT of charged paticles in -3.9 < #eta < -3.0", "h");
        leg1 -> Draw("p same");

    }



}
