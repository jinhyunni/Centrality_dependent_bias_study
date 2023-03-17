void plotMake_RpAu()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis_etacut_INEL_1e5_rebined.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5_rebined.root", "read");
	TFile* input3 = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "read");
	
	//historams
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	TH1D* pp = (TH1D*)input2 -> Get("pTpion0");

	TProfile* avgNcoll = (TProfile*)input3 -> Get("avgNcoll");

	//pAu yield
	TH1D* pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);
	TH1D* pAu2 = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);
	TH1D* pAu3 = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);
	TH1D* pAu4 = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);
	TH1D* pAu5 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");

	double num1 = h1cent -> GetBinContent(1);
	double num2 = h1cent -> GetBinContent(2);
	double num3 = h1cent -> GetBinContent(3) + h1cent -> GetBinContent(4);
	double num4 = h1cent -> GetBinContent(5) + h1cent -> GetBinContent(6);
	double num5 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);

	double scalar11 = 1./(pAu1 -> GetBinWidth(1) * num1);
	double scalar12 = 1./(pAu2 -> GetBinWidth(1) * num2);
	double scalar13 = 1./(pAu3 -> GetBinWidth(1) * num3);
	double scalar14 = 1./(pAu4 -> GetBinWidth(1) * num4);
	double scalar15 = 1./(pAu5 -> GetBinWidth(1) * num5);
	
	pAu1 -> Scale(scalar11);
	pAu2 -> Scale(scalar12);
	pAu3 -> Scale(scalar13);
	pAu4 -> Scale(scalar14);
	pAu5 -> Scale(scalar15);

	//R_pAu
	//// YpA/Ypp
	TH1D* R_pAu1 = new TH1D();
	TH1D* R_pAu2 = new TH1D();
	TH1D* R_pAu3 = new TH1D();
	TH1D* R_pAu4 = new TH1D();
	TH1D* R_pAu5 = new TH1D();

	*R_pAu1 = (*pAu1)/(*pp);
	*R_pAu2 = (*pAu2)/(*pp);
	*R_pAu3 = (*pAu3)/(*pp);
	*R_pAu4 = (*pAu4)/(*pp);
	*R_pAu5 = (*pAu5)/(*pp);
	
	////<Ncoll> scailing
	double scalar21 = 1./(avgNcoll -> GetBinContent(1));
	double scalar22 = 1./(avgNcoll -> GetBinContent(2));
	double scalar23 = 1./(avgNcoll -> GetBinContent(3));
	double scalar24 = 1./(avgNcoll -> GetBinContent(4));
	double scalar25 = 1./(avgNcoll -> GetBinContent(5));

	R_pAu1 -> Scale(scalar21);
	R_pAu2 -> Scale(scalar22);
	R_pAu3 -> Scale(scalar23);
	R_pAu4 -> Scale(scalar24);
	R_pAu5 -> Scale(scalar25);

	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas* c1 = new TCanvas("", "", 800, 600);
	{
		
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(0, 0, 5, 2.0);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("R_{pAu}");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

		R_pAu1 -> SetMarkerStyle(20);
		R_pAu1 -> SetMarkerColor(1);
		R_pAu1 -> SetLineColor(1);
		R_pAu1 -> Draw("p_same");

		R_pAu2 -> SetMarkerStyle(21);
		R_pAu2 -> SetMarkerColor(2);
		R_pAu2 -> SetLineColor(2);
		R_pAu2 -> Draw("p_same");

		R_pAu3 -> SetMarkerStyle(22);
		R_pAu3 -> SetMarkerColor(3);
		R_pAu3 -> SetLineColor(3);
		R_pAu3 -> Draw("p_same");

		R_pAu4 -> SetMarkerStyle(23);
		R_pAu4 -> SetMarkerColor(4);
		R_pAu4 -> SetLineColor(4);
		R_pAu4 -> Draw("p_same");

		R_pAu5 -> SetMarkerStyle(28);
		R_pAu5 -> SetMarkerColor(6);
		R_pAu5 -> SetLineColor(6);
		R_pAu5 -> Draw("p_same");

		//addig legend
		TLegend* leg1 = new TLegend(0.53, 0.57, 0.83, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option3(no diffraction)", "h");
		leg1 -> AddEntry("", "#pi^{0}, |#eta|<1", "h");
		//leg1 -> AddEntry("", "", "");
		leg1 -> AddEntry(R_pAu1, "0~10%", "p");
		leg1 -> AddEntry(R_pAu2, "10~20%", "p");
		leg1 -> AddEntry(R_pAu3, "20~40%", "p");
		leg1 -> AddEntry(R_pAu4, "40~60%", "p");
		leg1 -> AddEntry(R_pAu5, "60~80%", "p");
		leg1 -> Draw();

	}

}
