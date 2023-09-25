void plotMake_avgNcollCent()
{

    //Inputs

   	TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");
   	TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcollCent_allEvents.root", "read");

    TProfile *avgNcoll_ver3 = (TProfile*)input1 -> Get("avgNcollCent"); 
    TProfile *avgNcoll_ver4 = (TProfile*)input2 -> Get("avgNcollCent"); 
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollver3 = (TProfile*)avgNcoll_ver3 -> Rebin(5, "avgNcollR", binX);
    TProfile *avgNcollver4 = (TProfile*)avgNcoll_ver4 -> Rebin(5, "avgNcollR", binX);
    
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
    
 //        avgNcollver3 -> SetMarkerStyle(29);
 //        avgNcollver3 -> SetMarkerColor(2);
 //        avgNcollver3 -> SetLineColor(2);
 //        avgNcollver3 -> Draw("p same");
    
        avgNcollver4 -> SetMarkerStyle(25);
        avgNcollver4 -> SetMarkerColor(2);
        avgNcollver4 -> SetLineColor(2);
        avgNcollver4 -> Draw("p same");

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
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{0~10%} = 9.02056 #pm 7.45 #times 10^{-5}(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{10~20%} = 7.69286 #pm 7.26 #times 10^{-5}(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{20~40%} = 6.52323 #pm 5.29 #times 10^{-5} (stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{40~60%} = 5.04424 #pm 5.34 #times 10^{-5}(stat)", "h");
        leg2 -> AddEntry("", "#LTN_{coll}#GT_{60~80%} = 3.45525 #pm 4.88 #times 10^{-5}(stat)", "h");
        leg2 -> Draw();

	}


}
