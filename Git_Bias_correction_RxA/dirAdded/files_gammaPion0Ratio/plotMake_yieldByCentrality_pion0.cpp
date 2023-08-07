void plotMake_yieldByCentrality_pion0()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0.root", "read");
    TFile *input2 = new TFile("/Users/jinhyunpark/npl/gitHub/xloadFromServer/Git_Bias_correction_RxA/dirExcluded/pAu200GeV_option3_pion0YieldCent_newest.root", "read");

    TH1D *yieldPion0_new = (TH1D*)input1 -> Get("Ypion0"); 
    TH1D *yieldPion0_old = (TH1D*)input2 -> Get("yield");
    

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 20);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("# of #pi^{0} per event");
    
        yieldPion0_new -> SetMarkerStyle(20);
        yieldPion0_new -> SetMarkerColor(2);
        yieldPion0_new -> SetLineColor(2);
        yieldPion0_new -> Draw("p same");

        yieldPion0_old -> SetMarkerStyle(20);
        yieldPion0_old -> SetMarkerStyle(4);
        yieldPion0_old -> SetMarkerColor(4);
        yieldPion0_old -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		//leg1 -> AddEntry("","New 3e7 MC events including #gamma^{dir}", "h");
		leg1 -> AddEntry("","integrated p_{T}, |#eta|#LT1", "h");
        leg1 -> AddEntry(yieldPion0_new,"MC 3e7 Events, including #gamma^{dir}", "p");
        leg1 -> AddEntry(yieldPion0_old,"MC 1e5 Events, no #gamma^{dir}", "p");

		leg1 -> Draw();

	}


}
