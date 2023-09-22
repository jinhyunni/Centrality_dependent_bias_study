void plotMake_avgNcollCent()
{

    //Inputs

   	TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");

    TProfile *avgNcoll = (TProfile*)input1 -> Get("avgNcollCent"); 
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollR = (TProfile*)avgNcoll -> Rebin(5, "avgNcollR", binX);
    
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 3, 80, 10);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");
    
        avgNcollR -> SetMarkerStyle(29);
        avgNcollR -> SetMarkerColor(2);
        avgNcollR -> SetLineColor(2);
        avgNcollR -> Draw("p same");

		TLegend *leg1 = new TLegend(0.5, 0.83, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
	    leg1 -> Draw();
        
        TLegend *leg2 = new TLegend(0.5, 0.63, 0.8, 0.83);
        leg2 -> SetFillStyle(0);
        leg2 -> SetBorderSize(0);
        leg2 -> SetTextSize(0.03);
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{0~10%} = 9.0202 #pm 0.0002(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{10~20%} = 7.6929 #pm 0.0002(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{20~40%} = 6.5233 #pm 0.0001(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{40~60%} = 5.0445 #pm 0.0001(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{60~80%} = 3.4553 #pm 0.0001(stat)", "h");
        leg2 -> Draw();

	}


}
