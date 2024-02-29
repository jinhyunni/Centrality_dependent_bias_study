void plotMake_correlations_withMidPion0_ratioChargeEta_pTClass2MB()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidPion0.root", "read");

    TH1D *ratio_1 = (TH1D*)input1 -> Get("charge_etaRatio_pT1toMB");
    TH1D *ratio_2 = (TH1D*)input1 -> Get("charge_etaRatio_pT2toMB");
    TH1D *ratio_3 = (TH1D*)input1 -> Get("charge_etaRatio_pT3toMB");
    TH1D *ratio_4 = (TH1D*)input1 -> Get("charge_etaRatio_pT4toMB");
    TH1D *ratio_5 = (TH1D*)input1 -> Get("charge_etaRatio_pT5toMB");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0.5, 5, 2);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("(dN^{ch}/d#eta)_{pTClass} / (dN^{ch}/d#eta)_{MB}");

        ratio_1 -> SetMarkerStyle(34);
        ratio_1 -> SetMarkerColor(kOrange);
        ratio_1 -> SetLineColor(kOrange);
        ratio_1 -> Draw("p same");

        ratio_2 -> SetMarkerStyle(34);
        ratio_2 -> SetMarkerColor(kRed);
        ratio_2 -> SetLineColor(kRed);
        ratio_2 -> Draw("p same");

        ratio_3 -> SetMarkerStyle(28);
        ratio_3 -> SetMarkerColor(kPink);
        ratio_3 -> SetLineColor(kPink);
        ratio_3 -> Draw("p same");
    
        ratio_4 -> SetMarkerStyle(47);
        ratio_4 -> SetMarkerColor(kMagenta);
        ratio_4 -> SetLineColor(kMagenta);
        ratio_4 -> Draw("p same");
		
		TLine *one = new TLine(-5, 1, 5, 1);
		one -> Draw();

        TLegend *leg1 = new TLegend(0.15, 0.6, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "Events with #pi^{0} at mid-rapdity, pTClasses", "h");
        
        leg1 -> AddEntry(ratio_1, "pTClass1/MB", "p");
        leg1 -> AddEntry(ratio_2, "pTClass2/MB", "p");
        leg1 -> AddEntry(ratio_3, "pTClass3/MB", "p");
        leg1 -> AddEntry(ratio_4, "pTClass4/MB", "p");

        leg1 -> Draw();

    }

}
