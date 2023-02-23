/*************************************************
* pion0's invariant yield  by centrality *
	
	class1 0~10%
	class2 10~20%
	class3 20~40%
	class4 40~60%
	class5 60~80%

	* h2pTcent: 
		x: cent
		y: pion0's pT

		-> projectionX(centralirty -# of events)
		-> projectionY(pT-# ofpion0 )
	
***********************************************/

void plotMake_ncoll()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5.root", "read");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");

	//# of event in centrality 0~10%
	TH1D* h1CentClass1 = (TH1D*)h2ncollcent -> ProjectionY("h1cent", 1, 1);
	TH1D* h1CentClass2 = (TH1D*)h2ncollcent -> ProjectionY("h1cent", 2, 2);
	TH1D* h1CentClass3 = (TH1D*)h2ncollcent -> ProjectionY("h1cent", 3, 4);
	TH1D* h1CentClass4 = (TH1D*)h2ncollcent -> ProjectionY("h1cent", 5, 6);
	TH1D* h1CentClass5 = (TH1D*)h2ncollcent -> ProjectionY("h1cent", 7, 8);


	//calculating ncoll in class 1

	int nbins = h1CentClass1 -> GetNbinsX();
	int totNcoll1 = 0;
	int totNcoll2 = 0;
	int totNcoll3 = 0;
	int totNcoll4 = 0;
	int totNcoll5 = 0;
	double avgNcoll1 = 0.;
	double avgNcoll2 = 0.;
	double avgNcoll3 = 0.;
	double avgNcoll4 = 0.;
	double avgNcoll5 = 0.;

	TH2D* h1avgNcoll = new TH2D("avgNcollCent", "", 5, 1, 6, 100, 0, 100);

	//class1
	for(int i = 1; i <= nbins; i++){
		totNcoll1 += (i-1)*(h1CentClass1 -> GetBinContent(i));
	}
	cout << "In class 1" << endl;
	cout << totNcoll1 << endl;
	cout << h1CentClass1 -> Integral() << endl;

	//class2
	for(int i = 1; i <= nbins; i++){
		totNcoll2 += (i-1)*(h1CentClass2 -> GetBinContent(i));
	}	
	cout << "In class 2" << endl;
	cout << totNcoll2 << endl;
	cout << h1CentClass2 -> Integral() << endl;
	

	//class3
	for(int i = 1; i <= nbins; i++){
		totNcoll3 += (i-1)*(h1CentClass3 -> GetBinContent(i));
	}	
	cout << "In class 3" << endl;
	cout << totNcoll3 << endl;
	cout << h1CentClass3 -> Integral() << endl;
	
	//class4
	for(int i = 1; i <= nbins; i++){
		totNcoll4 += (i-1)*(h1CentClass4 -> GetBinContent(i));
	}	
	cout << "In class 4" << endl;
	cout << totNcoll4 << endl;
	cout << h1CentClass4 -> Integral() << endl;
	
	//class5
	for(int i = 1; i <= nbins; i++){
		totNcoll5 += (i-1)*(h1CentClass5 -> GetBinContent(i));
	}
	cout << "In class 5" << endl;
	cout << totNcoll5 << endl;
	cout << h1CentClass5 -> Integral() << endl;

 //	h1avgNcoll -> Draw();

	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(1, 0, 6, 10);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		h1avgNcoll -> SetMarkerStyle(21);
		h1avgNcoll -> SetMarkerColor(38);
		h1avgNcoll -> SetLineColor(38);
		h1avgNcoll -> Draw("p same");

		//adding legend
		TLegend *leg = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8", "h");
		leg -> AddEntry("", "p+Au 200 GeV", "h");
		leg -> AddEntry("", "option = 3(No diffraction)", "h");
		leg -> AddEntry("", "100,000 events", "h");
		leg -> AddEntry("", "#LTNcoll#GT", "h");	
		leg -> Draw();
		
	}
}

