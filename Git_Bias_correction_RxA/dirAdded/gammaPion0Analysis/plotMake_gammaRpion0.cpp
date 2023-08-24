void plotMake_gammaRpion0()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_byCent.root", "read");
    TH1D *ratio = (TH1D*)input1 -> Get("gammaOverPion0"); 
    

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 0.5);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("#gamma^{dir}/#pi^{0}");
    
        ratio -> SetMarkerStyle(67);
        ratio -> SetMarkerColor(51);
        ratio -> SetLineColor(51);
        ratio -> Draw("p same");

		TLegend *leg1 = new TLegend(0.43, 0.63, 0.73, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","New 3e7 MC events including #gamma^{dir}", "h");
		leg1 -> AddEntry("","integrated p_{T}, |#eta|#LT1", "h");

		leg1 -> Draw();

	}


}
