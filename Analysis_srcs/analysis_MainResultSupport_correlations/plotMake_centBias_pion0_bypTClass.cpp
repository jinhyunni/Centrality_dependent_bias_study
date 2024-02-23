void plotMake_centBias_pion0_bypTClass()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_withPion0_charge_ratioOfCentClass.root", "read");

    TH1D *ratio_1 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent2");
    TH1D *ratio_2 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent3");
    TH1D *ratio_3 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent4");
    TH1D *ratio_4 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent5");

 //*	TH1D *dNdpT_pion0_cent1 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent2");
 //*    TH1D *dNdpT_pion0_cent2 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent3");
 //*    TH1D *dNdpT_pion0_cent3 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent4");
 //*    TH1D *dNdpT_pion0_cent4 = (TH1D*)input1 -> Get("charge_etaRatio_pTClass1_Cent1toCent5");

 //*	double etaBin[] = {-3.9, -3.0, -2.0, -1.0, 0., 1., 2., 3.0, 3.9};	int etaBinNum=8;
 //*
 //*	TH1D *ratio_1 = (TH1D*)dNdpT_pion0_cent1 -> Rebin(etaBinNum, "cent1cent2", etaBin);
 //*	TH1D *ratio_2 = (TH1D*)dNdpT_pion0_cent2 -> Rebin(etaBinNum, "cent1cent3", etaBin);
 //*	TH1D *ratio_3 = (TH1D*)dNdpT_pion0_cent3 -> Rebin(etaBinNum, "cent1cent4", etaBin);
 //*	TH1D *ratio_4 = (TH1D*)dNdpT_pion0_cent4 -> Rebin(etaBinNum, "cent1cent5", etaBin);

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-3.9, -1, 3.9, 5);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");

    
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


        TLegend *leg1 = new TLegend(0.15, 0.6, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "Events with #pi^{0}, 2 GeV< p_{T} < 4 GeV, at |#eta|<1", "h");
        
        leg1 -> AddEntry(ratio_1, "centClass2/centClass1", "p");
        leg1 -> AddEntry(ratio_2, "centClass3/centClass1", "p");
        leg1 -> AddEntry(ratio_3, "centClass4/centClass1", "p");
        leg1 -> AddEntry(ratio_4, "centClass5/centClass1", "p");

        leg1 -> Draw();

    }

}
