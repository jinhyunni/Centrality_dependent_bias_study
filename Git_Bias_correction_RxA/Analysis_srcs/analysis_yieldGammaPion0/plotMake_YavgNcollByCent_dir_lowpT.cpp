void plotMake_YavgNcoll_dir_lowpT()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_byCent.root", "read");
    TH1D *YavgNcollDir_lowpT = (TH1D*)input1 -> Get("YavgNcollDir_lowpT"); 
    

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.8, 80, 0.0003);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("Y^{#gamma^{dir}}/#LTN_{coll}#GT");
    
        YavgNcollDir_lowpT -> SetMarkerStyle(48);
        YavgNcollDir_lowpT -> SetMarkerColor(4);
        YavgNcollDir_lowpT -> SetLineColor(4);
        YavgNcollDir_lowpT -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200GeV", "h");
		leg1 -> AddEntry("","p_{T} #LT 2 GeV, |#eta|#LT1", "h");

		leg1 -> Draw();

	}


}
