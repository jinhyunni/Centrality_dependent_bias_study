void plotMake_YavgNcollR()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	
	//historams

	////pAu
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");
	////avgNcoll
	TProfile* avgNcoll = (TProfile*)input2 -> Get("avgNcoll");


	//Rebin binedges
	double pTbins[]={0, 0.5, 1, 1.5, 2, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0};	


	//pAu yield
	TH1D* pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);	//pion0 pT in event cent 0~10%
	TH1D* pAu2 = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);	//pion0 pT in event cent 10~20%
	TH1D* pAu3 = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);	//pino0 pT in event cent 20~40%
	TH1D* pAu4 = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);	//pion0 pT in event cent 40~60%
	TH1D* pAu5 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);	//pion0 pT in event cent 60~80%

	//Rebin pAu yield
	TH1D* pAu1R = (TH1D*)pAu1 -> Rebin(22, "pAuR1", pTbins);
	TH1D* pAu2R = (TH1D*)pAu2 -> Rebin(22, "pAuR1", pTbins);
	TH1D* pAu3R = (TH1D*)pAu3 -> Rebin(22, "pAuR1", pTbins);
	TH1D* pAu4R = (TH1D*)pAu4 -> Rebin(22, "pAuR1", pTbins);
	TH1D* pAu5R = (TH1D*)pAu5 -> Rebin(22, "pAuR1", pTbins);

	//scailing to get dN/dpT
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");

	double num1 = h1cent -> GetBinContent(1);
	double num2 = h1cent -> GetBinContent(2);
	double num3 = h1cent -> GetBinContent(3) + h1cent -> GetBinContent(4);
	double num4 = h1cent -> GetBinContent(5) + h1cent -> GetBinContent(6);
	double num5 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);

	double scalar11 = 1./(pAu1R -> GetBinWidth(1) * num1);
	double scalar12 = 1./(pAu2R -> GetBinWidth(1) * num2);
	double scalar13 = 1./(pAu3R -> GetBinWidth(1) * num3);
	double scalar14 = 1./(pAu4R -> GetBinWidth(1) * num4);
	double scalar15 = 1./(pAu5R -> GetBinWidth(1) * num5);
	
	pAu1R -> Scale(scalar11);
	pAu2R -> Scale(scalar12);
	pAu3R -> Scale(scalar13);
	pAu4R -> Scale(scalar14);
	pAu5R -> Scale(scalar15);

	//Yield/<Ncoll>, more than 0, under 2 GeV, Y(pTclass)(centClass)
	double Y11 = pAu1R -> Integral(1, 4)/(avgNcoll -> GetBinContent(1) * 2);
	double Y12 = pAu2R -> Integral(1, 4)/(avgNcoll -> GetBinContent(2) * 2);
	double Y13 = pAu3R -> Integral(1, 4)/(avgNcoll -> GetBinContent(3) * 2);
	double Y14 = pAu4R -> Integral(1, 4)/(avgNcoll -> GetBinContent(4) * 2);
	double Y15 = pAu5R -> Integral(1, 4)/(avgNcoll -> GetBinContent(5) * 2);

	//Yield/<Ncoll>, more than 2, under 5 GeV, Y(pTclass)(centClass)
	double Y21 = pAu1R -> Integral(5, 10)/(avgNcoll -> GetBinContent(1) * 2);
	double Y22 = pAu2R -> Integral(5, 10)/(avgNcoll -> GetBinContent(2) * 2);
	double Y23 = pAu3R -> Integral(5, 10)/(avgNcoll -> GetBinContent(3) * 2);
	double Y24 = pAu4R -> Integral(5, 10)/(avgNcoll -> GetBinContent(4) * 2);
	double Y25 = pAu5R -> Integral(5, 10)/(avgNcoll -> GetBinContent(5) * 2);

	//Yield/<Ncoll>, more than 2, under 5 GeV, Y(pTclass)(centClass)
	double Y31 = pAu1R -> Integral(10, 22)/(avgNcoll -> GetBinContent(1) * 2);
	double Y32 = pAu2R -> Integral(10, 22)/(avgNcoll -> GetBinContent(2) * 2);
	double Y33 = pAu3R -> Integral(10, 22)/(avgNcoll -> GetBinContent(3) * 2);
	double Y34 = pAu4R -> Integral(10, 22)/(avgNcoll -> GetBinContent(4) * 2);
	double Y35 = pAu5R -> Integral(10, 22)/(avgNcoll -> GetBinContent(5) * 2);

 //	cout<< Y11 << endl;
 //	cout<< Y12 << endl;
 //	cout<< Y13 << endl;
 //	cout<< Y14 << endl;
 //	cout<< Y15 << endl;
 //	cout<<"*****"<<endl;
 //
 //	cout<< Y21 << endl;
 //	cout<< Y22 << endl;
 //	cout<< Y23 << endl;
 //	cout<< Y24 << endl;
 //	cout<< Y25 << endl;
 //	cout<<"*****"<<endl;
 //	
 //	cout<< Y31 << endl;
 //	cout<< Y32 << endl;
 //	cout<< Y33 << endl;
 //	cout<< Y34 << endl;
 //	cout<< Y35 << endl;
 //	cout<<"*****"<<endl;

	//Y/<Ncoll> vs Centrality
	TH1D *plot1 = new TH1D("Y and ratio1", "0~2GeV", 5, 0, 80);
	TH1D *plot2 = new TH1D("Y and ratio2", "2~5GeV", 5, 0, 80);
	TH1D *plot3 = new TH1D("Y and ratio3", "5~ GeV", 5, 0, 80);
	double bins[]={0, 10, 20, 40, 60, 80};

	plot1 -> GetXaxis() -> Set(5, bins);
	plot2 -> GetXaxis() -> Set(5, bins);
	plot3 -> GetXaxis() -> Set(5, bins);

	plot1 -> Sumw2();
	plot2 -> Sumw2();
	plot3 -> Sumw2();
	
	//Ratio
	//0~2 GeV	
	plot1 -> SetBinContent(1, Y11);
	plot1 -> SetBinContent(2, Y12);
	plot1 -> SetBinContent(3, Y13);
	plot1 -> SetBinContent(4, Y14);
	plot1 -> SetBinContent(5, Y15);

	//2~5GeV
	plot2 -> SetBinContent(1, Y21);
	plot2 -> SetBinContent(2, Y22);
	plot2 -> SetBinContent(3, Y23);
	plot2 -> SetBinContent(4, Y24);
	plot2 -> SetBinContent(5, Y25);

	//5~ GeV
	plot3 -> SetBinContent(1, Y31);
	plot3 -> SetBinContent(2, Y32);
	plot3 -> SetBinContent(3, Y33);
	plot3 -> SetBinContent(4, Y34);
	plot3 -> SetBinContent(5, Y35);

 //	//set false error	
 //	//0~2GeV
 //    plot1 -> SetBinError(1, 1./sqrt(num1));
 //    plot1 -> SetBinError(2, 1./sqrt(num2));
 //    plot1 -> SetBinError(3, 1./sqrt(num3));
 // 	plot1 -> SetBinError(4, 1./sqrt(num4));
 // 	plot1 -> SetBinError(5, 1./sqrt(num5));
 //	
 //	//2~5GeV
 //	plot2 -> SetBinError(1, 1./sqrt(num1));
 //	plot2 -> SetBinError(2, 1./sqrt(num2));
 //	plot2 -> SetBinError(3, 1./sqrt(num3));
 //	plot2 -> SetBinError(4, 1./sqrt(num4));
 //	plot2 -> SetBinError(5, 1./sqrt(num5));
 //	
 //	//5~GeV
 //	plot3 -> SetBinError(1, 1./sqrt(num1));
 //	plot3 -> SetBinError(2, 1./sqrt(num2));
 //	plot3 -> SetBinError(3, 1./sqrt(num3));
 //	plot3 -> SetBinError(4, 1./sqrt(num4));
 //	plot3 -> SetBinError(5, 1./sqrt(num5));


 //	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas* c1 = new TCanvas("", "", 800, 600);
	{
		
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 0.0001);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("Y_{pAu}/#LTN_{coll}#GT");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

		plot3 -> SetMarkerStyle(28);
		plot3 -> SetMarkerColor(6);
		plot3 -> SetLineColor(6);
		plot3 -> Draw("p_same");

		//addig legend
		TLegend* leg1 = new TLegend(0.6, 0.57, 0.9, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option3(Default)", "h");
		leg1 -> AddEntry("", "#pi^{0}, |#eta|<1", "h");
		leg1 -> AddEntry("", "5 #leqp_{T}", "h");
		//leg1 -> AddEntry("", "", "");
		leg1 -> Draw();

	}

}
