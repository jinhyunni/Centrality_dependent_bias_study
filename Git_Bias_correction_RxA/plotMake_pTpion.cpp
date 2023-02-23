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

void plotMake_pTpion()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5.root", "read");
	TH2D* h2pTcent = (TH2D*)input -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");
	
	//pion0's pT in centrality 0~10%
	TH1D* pTclass = (TH1D*)h2pTcent -> ProjectionY("pTclass", 1, 1);

	//# of event in centrality 0~10%
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent");
	double numclass = h1cent -> GetBinContent(1);

	//invariant yield, fixed bin width
	double factor = 1./(numclass*pTclass -> GetBinWidth(1));
	pTclass -> Scale(factor);
	pTclass -> Sumw2();

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

		pTclass -> SetMarkerStyle(21);
		pTclass -> SetMarkerColor(38);
		pTclass -> SetLineColor(38);
		pTclass -> Draw("p same");

		//adding legend
		TLegend *leg = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8", "h");
		leg -> AddEntry("", "p+Au 200 GeV", "h");
		leg -> AddEntry("", "option = 3(No diffraction)", "h");
		leg -> AddEntry("", "100,000 events", "h");
		leg -> AddEntry("", "centrality 60~80%", "h");	
		leg -> Draw();
		
	}
}

