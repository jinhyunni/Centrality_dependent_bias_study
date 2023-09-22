void plotMake_numOfParticleByCent_pion0()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");

    TH2D *h2pTcent = (TH2D*)input1 -> Get("centPion0");

    double binEdge[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    TH1D *num_low = (TH1D*)h2pTcent -> ProjectionX("num_low", 1, 200);
    TH1D *num_high = (TH1D*)h2pTcent -> ProjectionX("num_high", 201, 1400);

    num_low -> SetBinContent(10, num_low -> GetBinContent(10) + num_low -> GetBinContent(11));
    num_high -> SetBinContent(10, num_high -> GetBinContent(10) + num_high -> GetBinContent(11));

    TH1D *num_lowR = (TH1D*)num_low -> Rebin(10, "num_lowR", binEdge);
    TH1D *num_highR = (TH1D*)num_high -> Rebin(10, "num_highR", binEdge);


	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 100, 1e5);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("# of #pi^{0}");
    
        num_highR -> SetMarkerStyle(24);
        num_highR -> SetMarkerColor(2);
        num_highR -> SetLineColor(2);
        num_highR -> Draw("p same");

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
