/**************************************************
* Histogram for centrality categorization checking*
**************************************************/

void plotMake_centcheck()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5_elastic.root", "read");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");

	//# of event
	TH1D* h1Cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent");
	h1Cent -> SetBinContent(10, (h1Cent -> GetBinContent(10))+(h1Cent -> GetBinContent(11)));
	h1Cent -> Sumw2();

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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 100, 1.5e4);

		htmp -> GetXaxis() -> SetTitle("centrality");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("# of events");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		h1Cent -> SetMarkerStyle(34);
		h1Cent -> SetMarkerColor(1);
		h1Cent -> SetLineColor(1);
		h1Cent -> Draw("p same");

		//adding legend
		TLegend *leg = new TLegend(0.47, 0.63, 0.73, 0.93);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8", "h");
		leg -> AddEntry("", "p+Au 200 GeV", "h");
		leg -> AddEntry("", "option = 3(No diffraction)", "h");
		leg -> AddEntry("", "100,000 events", "h");
		leg -> AddEntry("", "centrality categorization check", "h");
		leg -> AddEntry("", "Elastic events", "h");
		leg -> Draw();
		
	}
}

