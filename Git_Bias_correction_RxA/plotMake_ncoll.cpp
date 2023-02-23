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
	avgNcoll1 = totNcoll1/(h1CentClass1 -> Integral());
	h1avgNcoll -> Fill(1, avgNcoll1);
	cout << avgNcoll1 << endl;
	
	//class2
	for(int i = 1; i <= nbins; i++){
		totNcoll2 += (i-1)*(h1CentClass2 -> GetBinContent(i));
	}	
	avgNcoll2 = totNcoll2/(h1CentClass2 -> Integral());
	h1avgNcoll -> Fill(2, avgNcoll2);
	cout << avgNcoll2 << endl;

	//class3
	for(int i = 1; i <= nbins; i++){
		totNcoll3 += (i-1)*(h1CentClass3 -> GetBinContent(i));
	}	
	avgNcoll3 = totNcoll3/(h1CentClass3 -> Integral());
	h1avgNcoll -> Fill(3, avgNcoll3);
	cout << avgNcoll3 << endl;
	
	//class4
	for(int i = 1; i <= nbins; i++){
		totNcoll4 += (i-1)*(h1CentClass4 -> GetBinContent(i));
	}	
	avgNcoll4 = totNcoll4/(h1CentClass4 -> Integral());
	h1avgNcoll -> Fill(4, avgNcoll4);
	cout << avgNcoll4 << endl;
	
	//class5
	for(int i = 1; i <= nbins; i++){
		totNcoll5 += (i-1)*(h1CentClass5 -> GetBinContent(i));
	}
	avgNcoll5 = totNcoll5/(h1CentClass5 -> Integral());
	h1avgNcoll -> Fill(5, avgNcoll5);
	cout << avgNcoll5 << endl;

	h1avgNcoll -> Draw();

 //	//Draw histogram
 //	gStyle -> SetOptStat(0);
 //	TCanvas *c1 = new TCanvas("", "", 800, 600);
 //	{
 //		c1 -> cd();
 //
 //		gPad -> SetTicks();
 //		gPad -> SetLeftMargin(0.15);
 //		gPad -> SetRightMargin(0.15);
 //		gPad -> SetTopMargin(0.05);
 //		gPad -> SetBottomMargin(0.12);
 //
 //		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 7, 100);
 //
 //		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
 //		htmp -> GetXaxis() -> SetTitleSize(0.05);
 //		htmp -> GetXaxis() -> SetLabelSize(0.04);
 //		htmp -> GetXaxis() -> SetTitleOffset(1.1);
 //		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
 //		htmp -> GetYaxis() -> SetTitleSize(0.05);
 //		htmp -> GetYaxis() -> SetLabelSize(0.04);	
 //
 //		pTclass5 -> SetMarkerStyle(21);
 //		pTclass5 -> SetMarkerColor(38);
 //		pTclass5 -> SetLineColor(38);
 //		pTclass5 -> Draw("p same");
 //
 //		//adding legend
 //		TLegend *leg = new TLegend(0.53, 0.63, 0.83, 0.93);
 //		leg -> SetFillStyle(0);
 //		leg -> SetBorderSize(0);
 //		leg -> SetTextSize(0.04);
 //		leg -> AddEntry("", "PYTHIA8", "h");
 //		leg -> AddEntry("", "p+Au 200 GeV", "h");
 //		leg -> AddEntry("", "option = 3(No diffraction)", "h");
 //		leg -> AddEntry("", "100,000 events", "h");
 //		leg -> AddEntry("", "centrality 60~80%", "h");	
 //		leg -> Draw();
 //		
 //	}
}

