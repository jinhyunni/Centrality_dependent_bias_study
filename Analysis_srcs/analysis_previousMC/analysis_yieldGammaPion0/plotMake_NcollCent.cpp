void plotMake_NcollCent()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCent_allEvents.root", "read");

    TH2D *h2pTcent = (TH2D*)input1 -> Get("ncollCent");

    double binEdge[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    TH1D *num = (TH1D*)h2pTcent -> ProjectionX("num");

    num -> SetBinContent(10, num -> GetBinContent(10) + num -> GetBinContent(11));

    TH1D *numR = (TH1D*)num -> Rebin(10, "num_lowR", binEdge);


	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 100, 1e7);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("# of inelastic events");
    
        numR -> SetMarkerStyle(25);
        numR -> SetMarkerColor(8);
        numR -> SetLineColor(8);
        numR -> Draw("p same");

  		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");

		leg1 -> Draw();

	}


}
