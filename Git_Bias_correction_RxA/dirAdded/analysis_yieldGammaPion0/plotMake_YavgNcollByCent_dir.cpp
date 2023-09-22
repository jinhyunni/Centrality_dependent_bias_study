void plotMake_YavgNcollByCent_dir()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_byCent.root", "read");
    TFile *input2 = new TFile("pAu200GeV_kiaf_option3_yieldOfgammaApion0_byCent.root", "read");

    TH1D *YavgNcollDir_old = (TH1D*)input1 -> Get("YavgNcollDir_integrated"); 
    TH1D *YavgNcollDir_new = (TH1D*)input2 -> Get("YavgNcollDir_integrated");

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
    
        YavgNcollDir_old -> SetMarkerStyle(34);
        YavgNcollDir_old -> SetMarkerColor(4);
        YavgNcollDir_old -> SetLineColor(4);
        YavgNcollDir_old -> Draw("p same");

        YavgNcollDir_new -> SetMarkerStyle(28);
        YavgNcollDir_new -> SetMarkerColor(4);
        YavgNcollDir_new -> SetLineColor(4);
        YavgNcollDir_new -> Draw("p same");


		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200GeV", "h");
		leg1 -> AddEntry("","integrated p_{T}, |#eta|#LT1", "h");
        leg1 -> AddEntry(YavgNcollDir_new, "New-MC", "p");
        leg1 -> AddEntry(YavgNcollDir_old, "Old-MC", "p");

		leg1 -> Draw();

	}


}
