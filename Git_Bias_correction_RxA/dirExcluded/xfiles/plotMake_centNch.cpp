/**************************************************
* Histogram for centrality categorization checking*

* Used N_ch for centrality calculation
-> substituted with pTsum of N_ch
   in BBCS acceptance
**************************************************/

void plotMake_centNch()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_centrality_e5.root", "read");
	TH1D* h1Cent = (TH1D*)input -> Get("centrality");
	
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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 6e3, 100, 2.5e4);

		htmp -> GetXaxis() -> SetTitle("centrality");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("# of events");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		h1Cent -> SetMarkerStyle(21);
		h1Cent -> SetMarkerColor(38);
		h1Cent -> SetLineColor(38);
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
		leg -> AddEntry("", "Based on summed charge", "h");
		leg -> AddEntry("", "centrality categorization check", "h");	
		leg -> Draw();
		
	}
}

