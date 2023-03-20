/*************************************************
* pion0's invariant yield  by centrality *

* Ncoll = 1 events
*************************************************/

void plotMake_pTpion_Ncoll1()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option1_pion0Analysis_Ncoll1_etacut_1e5.root", "read");
	TH1D* pTpion0Ncoll1 = (TH1D*)input -> Get("pTpion0");
		
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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 7, 8);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		pTpion0Ncoll1 -> SetMarkerStyle(20);
		pTpion0Ncoll1 -> SetMarkerColor(1);
		pTpion0Ncoll1 -> SetLineColor(1);
		pTpion0Ncoll1 -> Draw("p same");

		//adding legend
		TLegend* leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option = 1(default)", "h");
		leg1 -> AddEntry("", "N_{coll}=1 event", "h");
		leg1 -> AddEntry("", "|#eta|<1", "h");
		leg1 -> AddEntry(pTpion0Ncoll1, "#pi^{0}", "p");
		leg1 -> Draw();

	
		
	}

}

