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

		-> projectionY(): pion0's pT spectrum in
						  each centrality bin
	
	* h2NcollCent
		x: cent
		y: ncoll

		-> ProjectionX() : number of events in
						   each centrality bin
	
*************************************************/

void plotMake_pTpion()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5.root", "read");
	TH2D* h2pTcent = (TH2D*)input -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");
	
	//pion0's pT in centrality
	TH1D* pTclass1 = (TH1D*)h2pTcent -> ProjectionY("pTclass1", 1, 1);
	TH1D* pTclass2 = (TH1D*)h2pTcent -> ProjectionY("pTclass2", 2, 2);
	TH1D* pTclass3 = (TH1D*)h2pTcent -> ProjectionY("pTclass3", 3, 4);
	TH1D* pTclass4 = (TH1D*)h2pTcent -> ProjectionY("pTclass4", 5, 6);
	TH1D* pTclass5 = (TH1D*)h2pTcent -> ProjectionY("pTclass5", 7, 8);

	//# of event in centrality 0~10%
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent");
	double numclass1 = h1cent -> GetBinContent(1); 								   //0~10%
	double numclass2 = h1cent -> GetBinContent(2); 							       //10~20%
	double numclass3 = (h1cent -> GetBinContent(3))+ (h1cent -> GetBinContent(4)); //20~40%
	double numclass4 = (h1cent -> GetBinContent(5))+ (h1cent -> GetBinContent(6)); //40~60%
	double numclass5 = (h1cent -> GetBinContent(7))+ (h1cent -> GetBinContent(8)); //60~80%

	//scale for invariant yield
	double scalar1 = 1./(pTclass1 -> GetBinWidth(1)*numclass1);
	double scalar2 = 1./(pTclass2 -> GetBinWidth(1)*numclass2);
	double scalar3 = 1./(pTclass3 -> GetBinWidth(1)*numclass3);
	double scalar4 = 1./(pTclass4 -> GetBinWidth(1)*numclass4);
	double scalar5 = 1./(pTclass5 -> GetBinWidth(1)*numclass5);

	//invariant yield
	pTclass1 -> Scale(scalar1);
	pTclass2 -> Scale(scalar2);
	pTclass3 -> Scale(scalar3);
	pTclass4 -> Scale(scalar4);
	pTclass5 -> Scale(scalar5);

	//Store invariant yield
	TFile* output = new TFile("pAu200GeV_option3_pTpion_invarY1e5.root", "recreate");
	
	pTclass1 -> Write();
	pTclass2 -> Write();
	pTclass3 -> Write();
	pTclass4 -> Write();
	pTclass5 -> Write();

	output -> Close();
		
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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 7, 100);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		pTclass1 -> SetMarkerStyle(20);
		pTclass1 -> SetMarkerColor(1);
		pTclass1 -> SetLineColor(1);
		pTclass1 -> Draw("p same");

		pTclass2 -> SetMarkerStyle(21);
		pTclass2 -> SetMarkerColor(2);
		pTclass2 -> SetLineColor(2);
		pTclass2 -> Draw("p same");

		pTclass3 -> SetMarkerStyle(22);
		pTclass3 -> SetMarkerColor(3);
		pTclass3 -> SetLineColor(3);
		pTclass3 -> Draw("p same");

		pTclass4 -> SetMarkerStyle(23);
		pTclass4 -> SetMarkerColor(4);
		pTclass4 -> SetLineColor(4);
		pTclass4 -> Draw("p same");

		pTclass5 -> SetMarkerStyle(34);
		pTclass5 -> SetMarkerColor(6);
		pTclass5 -> SetLineColor(6);
		pTclass5 -> Draw("p same");

		//adding legend
		TLegend* leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option = 3(No diffraction)", "h");
		leg1 -> AddEntry("", "100,000 events", "h");
 //		leg1 -> AddEntry("", "first correction", "h");
		leg1 -> Draw();

		TLegend* leg2 = new TLegend(0.53, 0.33, 0.83, 0.63);
		leg2 -> SetFillStyle(0);
		leg2 -> SetBorderSize(0);
		leg2 -> AddEntry(pTclass1, "centrality 0~10%", "p");
		leg2 -> AddEntry(pTclass2, "centrality 10~20%", "p");
		leg2 -> AddEntry(pTclass3, "centrality 20~40%", "p");
		leg2 -> AddEntry(pTclass4, "centrality 40~60%", "p");
		leg2 -> AddEntry(pTclass5, "centrality 60~80%", "p");
		leg2 -> Draw();

 //		TLegend* leg3 = new TLegend(0.53, 0.33, 0.83, 0.63);
 //		leg3 -> SetFillStyle(0);
 //		leg3 -> SetBorderSize(0);
 //		leg3 -> AddEntry("", "#LTN_{coll}#GT", "");
 //		leg3 -> AddEntry(pTclass1, "8.9884", "p");
 //		leg3 -> AddEntry(pTclass2, "7.6395", "p");
 //		leg3 -> AddEntry(pTclass3, "6.4322", "p");
 //		leg3 -> AddEntry(pTclass4, "4.8946", "p");
 //		leg3 -> AddEntry(pTclass5, "4.4911", "p");
 //		leg3 -> Draw();
		
	}

}

