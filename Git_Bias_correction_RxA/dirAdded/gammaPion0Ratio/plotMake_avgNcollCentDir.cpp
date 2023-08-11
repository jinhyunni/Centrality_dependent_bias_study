void plotMake_avgNcollCentDir()
{

    //Inputs

   	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentDir.root", "read");

    TProfile *avgNcoll_new = (TProfile*)input1 -> Get("avgNcollCentDir"); 
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollR = (TProfile*)avgNcoll_new -> Rebin(5, "avgNcollR", binX);
    
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
		htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");
    
        avgNcollR -> SetMarkerStyle(20);
        avgNcollR -> SetMarkerColor(2);
        avgNcollR -> SetLineColor(2);
        avgNcollR -> Draw("p same");

		TLegend *leg1 = new TLegend(0.4, 0.63, 0.7, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "#LTN_{coll}#GT of target events", "h");
		//leg1 -> AddEntry("","New 3e7 MC events including #gamma^{dir}", "h");
        leg1 -> AddEntry("", "Target Events: ", "h");
		leg1 -> AddEntry("","Including #gamma^{dir}, integrated p_{T}, |#eta|#LT1", "h");
		
        leg1 -> Draw();

	}


}
