void plotMake_YavgNcollByCent_dir_highpT()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_byCent.root", "read");
    TFile *input2 = new TFile("pAu200GeV_kiaf_option3_yieldOfgammaApion0_byCent.root", "read");

    TH1D *YavgNcollDir_highpT_old = (TH1D*)input1 -> Get("YavgNcollDir_highpT"); 
    TH1D *YavgNcollDir_highpT_new = (TH1D*)input2 -> Get("YavgNcollDir_highpT"); 
    

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.8, 80, 0.00001);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("Y^{#gamma^{dir}}/#LTN_{coll}#GT");
    
        YavgNcollDir_highpT_old -> SetMarkerStyle(21);
        YavgNcollDir_highpT_old -> SetMarkerColor(1);
        YavgNcollDir_highpT_old -> SetLineColor(1);
        YavgNcollDir_highpT_old -> Draw("p same");

        YavgNcollDir_highpT_new -> SetMarkerStyle(25);
        YavgNcollDir_highpT_new -> SetMarkerColor(1);
        YavgNcollDir_highpT_new -> SetLineColor(1);
        YavgNcollDir_highpT_new -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200GeV", "h");
		leg1 -> AddEntry("","p_{T} #geq 2 GeV, |#eta|#LT1", "h");
        leg1 -> AddEntry(YavgNcollDir_highpT_new, "New-MC", "p");
        leg1 -> AddEntry(YavgNcollDir_highpT_old, "Old-MC", "p");

		leg1 -> Draw();

	}


}
