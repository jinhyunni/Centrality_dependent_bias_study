void plotMake_correlations_withMidDirPhoton_chargeEta_pTClassAndMB()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withDirPhoton_ofpTClass.root", "read");
	TFile *input2 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidDirPhoton.root", "read");

    TH1D *dNdeta_1 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass1_scaled");
    TH1D *dNdeta_2 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass2_scaled");
    TH1D *dNdeta_3 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass3_scaled");
    TH1D *dNdeta_4 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass4_scaled");
    TH1D *dNdeta_5 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass5_scaled");
    TH1D *dNdeta_6 = (TH1D*)input1 -> Get("charge_eta_corWithDirPhoton_ofpTClass6_scaled");

	TH1D *dNdeta_MB = (TH1D*)input2 -> Get("charge_eta_MB_etaRebin");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 20);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");

        dNdeta_1 -> SetMarkerStyle(25);
        dNdeta_1 -> SetMarkerColor(kViolet-1);
        dNdeta_1 -> SetLineColor(kViolet-1);
        dNdeta_1 -> Draw("p same");

		dNdeta_2 -> SetMarkerStyle(34);
        dNdeta_2 -> SetMarkerColor(kGreen+1);
        dNdeta_2 -> SetLineColor(kGreen+1);
        dNdeta_2 -> Draw("p same");

        dNdeta_3 -> SetMarkerStyle(34);
        dNdeta_3 -> SetMarkerColor(kTeal+1);
        dNdeta_3 -> SetLineColor(kTeal+1);
        dNdeta_3 -> Draw("p same");

        dNdeta_4 -> SetMarkerStyle(28);
        dNdeta_4 -> SetMarkerColor(kCyan+1);
        dNdeta_4 -> SetLineColor(kCyan+1);
        dNdeta_4 -> Draw("p same");
    
        dNdeta_5 -> SetMarkerStyle(47);
        dNdeta_5 -> SetMarkerColor(kAzure);
        dNdeta_5 -> SetLineColor(kAzure);
        dNdeta_5 -> Draw("p same");

		dNdeta_6 -> SetMarkerStyle(25);
        dNdeta_6 -> SetMarkerColor(kBlue+1);
        dNdeta_6 -> SetLineColor(kBlue+1);
        dNdeta_6 -> Draw("p same");

		dNdeta_MB -> SetMarkerStyle(34);
        dNdeta_MB -> SetMarkerColor(1);
        dNdeta_MB -> SetLineColor(1);
        dNdeta_MB -> Draw("p same");
		
        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(dNdeta_1, "Events with p_{T} #LT 2 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_2, "Events with 2 GeV #leq p_{T} #LT 4 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_3, "Events with 4 GeV #leq p_{T} #LT 7 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_4, "Events with 7 GeV #leq p_{T} #LT 10 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_5, "Events with 10 GeV #leq p_{T} #LT 15 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_6, "Events with 15 GeV #leq p_{T} #LT 20 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_MB, "MB events", "p");

        leg1 -> Draw();

    }

}
