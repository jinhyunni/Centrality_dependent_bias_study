void plotMake_yieldByCentrality_highpT()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_highpT.root", "read");

    TH1D *highPion0 = (TH1D*)input1 -> Get("Ypion0");
    TH1D *highdir = (TH1D*)input1 -> Get("Ydir");

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.6, 80, 2);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("# of #pi^{0}, #gamma^{dir} per event");
    
        highPion0 -> SetMarkerStyle(48);
        highPion0 -> SetMarkerColor(2);
        highPion0 -> SetLineColor(2);
        highPion0 -> Draw("p same");

        highdir -> SetMarkerStyle(49);
        highdir -> SetMarkerColor(4);
        highdir -> SetLineColor(4);
        highdir -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","p_{T} #geq 2 GeV, |#eta| #LT 1", "h");
        leg1 -> AddEntry(highPion0,"#pi^{0}", "p");
        leg1 -> AddEntry(highdir,"#gamma^{dir}", "p");

		leg1 -> Draw();

	}


}
