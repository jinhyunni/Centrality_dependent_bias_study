void plotMake_correlations_ratioOfRatioPtClass2MB_pion0toDirPhoton()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioOfRatioPtClass2MB_pion0toDirPhoton.root", "read");

    TH1D *ratio_1 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass1");
    TH1D *ratio_2 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass2");
    TH1D *ratio_3 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass3");
    TH1D *ratio_4 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass4");
    TH1D *ratio_5 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass5");
    TH1D *ratio_6 = (TH1D*)input1 -> Get("ratio_chargeEtaRatio_pi0toDir_pTClass6");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0.95, 5, 1.06);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("(#eta bias of charge)_{corr with mid #pi^{0}} / (#eta bias of charge)_{corr woth mid #gamma^{dir}}");

        ratio_1 -> SetMarkerStyle(34);
        ratio_1 -> SetMarkerColor(kOrange);
        ratio_1 -> SetLineColor(kOrange);
        //ratio_1 -> Draw("p same");

        ratio_2 -> SetMarkerStyle(34);
        ratio_2 -> SetMarkerColor(kMagenta);
        ratio_2 -> SetLineColor(kMagenta);
        ratio_2 -> Draw("p same");

        ratio_3 -> SetMarkerStyle(28);
        ratio_3 -> SetMarkerColor(kViolet);
        ratio_3 -> SetLineColor(kViolet);
        ratio_3 -> Draw("p same");
    
        ratio_4 -> SetMarkerStyle(47);
        ratio_4 -> SetMarkerColor(kAzure);
        ratio_4 -> SetLineColor(kAzure);
        ratio_4 -> Draw("p same");
		
		ratio_5 -> SetMarkerStyle(22);
        ratio_5 -> SetMarkerColor(kTeal);
        ratio_5 -> SetLineColor(kTeal);
        ratio_5 -> Draw("p same");

		ratio_6 -> SetMarkerStyle(23);
        ratio_6 -> SetMarkerColor(kSpring);
        ratio_6 -> SetLineColor(kSpring);
        //ratio_6 -> Draw("p same");

		TLine *one = new TLine(-5, 1, 5, 1);
		one -> Draw();

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(ratio_1, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 2 GeV", "p");
        leg1 -> AddEntry(ratio_2, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 2 GeV #leq p_{T} 4 GeV", "p");
        leg1 -> AddEntry(ratio_3, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 4 GeV #leq p_{T} 7 GeV", "p");
        leg1 -> AddEntry(ratio_4, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 7 GeV #leq p_{T} 10 GeV", "p");
        leg1 -> AddEntry(ratio_5, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 10 GeV #leq p_{T} 15 GeV", "p");
        leg1 -> AddEntry(ratio_6, "Events with #pi^{0}, #gamma^{dir} in |#eta|<1 of 15 GeV #leq p_{T} 20 GeV", "p");

        leg1 -> Draw();

    }

}
