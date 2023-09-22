void plotMake_avgNcollCent()
{

    //Inputs

   	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCent_allEvents.root", "read");

    TProfile *avgNcoll_new = (TProfile*)input1 -> Get("avgNcollCent"); 
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    TProfile *avgNcollR = (TProfile*)avgNcoll_new -> Rebin(10, "avgNcollR", binX);
    
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 100, 15);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");
    
        avgNcollR -> SetMarkerStyle(21);
        avgNcollR -> SetMarkerColor(8);
        avgNcollR -> SetLineColor(8);
        avgNcollR -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
        leg1 -> AddEntry("", "#LTN_{coll}#GT of Inelastic events", "h");
		
        leg1 -> Draw();

	}


}
