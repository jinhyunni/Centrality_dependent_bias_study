void plotMake_YavgNcoll_pion0_highpT()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_byCent.root", "read");

    TH1D *YavgNcollPion0_highpT = (TH1D*)input1 -> Get("YavgNcollPion0_highpT"); 

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 0.01);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("Y^{#pi^{0}}/#LTN_{coll}#GT");
    
        YavgNcollPion0_highpT -> SetMarkerStyle(48);
        YavgNcollPion0_highpT -> SetMarkerColor(2);
        YavgNcollPion0_highpT -> SetLineColor(2);
        YavgNcollPion0_highpT -> Draw("p same");

  		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		//leg1 -> AddEntry("","New 3e7 MC events including #gamma^{dir}", "h");
		leg1 -> AddEntry("","p_{T} #geq 2 GeV, |#eta|#LT1", "h");

		leg1 -> Draw();

	}


}
