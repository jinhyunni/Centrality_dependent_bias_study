void plotMake_correlations_withMidPion0_chargeEta_pTClassAndMB()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withPion0_ofpTClass.root", "read");
	TFile *input2 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidPion0.root", "read");

    TH1D *dNdeta_1 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass1_scaled");
    TH1D *dNdeta_2 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass2_scaled");
    TH1D *dNdeta_3 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass3_scaled");
    TH1D *dNdeta_4 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass4_scaled");
    TH1D *dNdeta_5 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass5_scaled");
    TH1D *dNdeta_6 = (TH1D*)input1 -> Get("charge_eta_corWithPion0_ofpTClass6_scaled");

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


        //TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 20);
        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 25);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");

        dNdeta_1 -> SetMarkerStyle(25);
        dNdeta_1 -> SetMarkerColor(kOrange+10);
        dNdeta_1 -> SetLineColor(kOrange+10);
        dNdeta_1 -> Draw("p same");

		dNdeta_2 -> SetMarkerStyle(34);
        dNdeta_2 -> SetMarkerColor(kOrange);
        dNdeta_2 -> SetLineColor(kOrange);
        dNdeta_2 -> Draw("p same");

        dNdeta_3 -> SetMarkerStyle(34);
        dNdeta_3 -> SetMarkerColor(kRed);
        dNdeta_3 -> SetLineColor(kRed);
        dNdeta_3 -> Draw("p same");

        dNdeta_4 -> SetMarkerStyle(28);
        dNdeta_4 -> SetMarkerColor(kPink);
        dNdeta_4 -> SetLineColor(kPink);
        dNdeta_4 -> Draw("p same");
    
        dNdeta_5 -> SetMarkerStyle(47);
        dNdeta_5 -> SetMarkerColor(kMagenta);
        dNdeta_5 -> SetLineColor(kMagenta);
        dNdeta_5 -> Draw("p same");

		dNdeta_6 -> SetMarkerStyle(25);
        dNdeta_6 -> SetMarkerColor(kViolet);
        dNdeta_6 -> SetLineColor(kViolet);
        dNdeta_6 -> Draw("p same");

		// for 2024 spring kps
		dNdeta_MB -> SetMarkerStyle(34);
        dNdeta_MB -> SetMarkerColor(1);
        dNdeta_MB -> SetLineColor(1);
        dNdeta_MB -> Draw("p same");

 //*		dNdeta_2 -> SetMarkerStyle(20);
 //*		dNdeta_2 -> SetMarkerColor(kOrange+6);
 //*		dNdeta_2 -> SetLineColor(kOrange+6);
 //*		dNdeta_2 -> Draw("p same");
 //*
 //*		dNdeta_4 -> SetMarkerStyle(21);
 //*		dNdeta_4 -> SetMarkerColor(kPink);
 //*		dNdeta_4 -> SetLineColor(kPink);
 //*		dNdeta_4 -> Draw("p same");
 //*
 //*		dNdeta_6 -> SetMarkerStyle(22);
 //*		dNdeta_6 -> SetMarkerColor(kViolet);
 //*		dNdeta_6 -> SetLineColor(kViolet);
 //*		dNdeta_6 -> Draw("p same");
		
		
        TLegend *leg1 = new TLegend(0.15, 0.65, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, p+Au 200GeV with option3", "h");
        
        leg1 -> AddEntry(dNdeta_1, "Events with p_{T} #LT 2 GeV #pi^{0} at |#eta|<1", "p");
		leg1 -> AddEntry(dNdeta_2, "Events with 2 GeV #leq p_{T} #LT 4 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_3, "Events with 4 GeV #leq p_{T} #LT 7 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_4, "Events with 7 GeV #leq p_{T} #LT 10 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_5, "Events with 10 GeV #leq p_{T} #LT 15 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_6, "Events with 15 GeV #leq p_{T} #LT 20 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(dNdeta_MB, "MB events", "p");
 //*		leg1 -> AddEntry(dNdeta_2, "Events with 2 GeV #leq p_{T} #LT 4 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(dNdeta_4, "Events with 7 GeV #leq p_{T} #LT 10 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(dNdeta_6, "Events with 15 GeV #leq p_{T} #LT 20 GeV #pi^{0} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
