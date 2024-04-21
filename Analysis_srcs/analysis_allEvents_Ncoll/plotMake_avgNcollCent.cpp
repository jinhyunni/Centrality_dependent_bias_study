#include "../headerFiles/configurable.h"

void plotMake_avgNcollCent()
{

    //Inputs

   	TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");
   	TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcollCent_allEvents.root", "read");

    TProfile *avgNcoll_ver3 = (TProfile*)input1 -> Get("avgNcollCent"); 
    TProfile *avgNcoll_ver4 = (TProfile*)input2 -> Get("avgNcollCent"); 
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollver3 = (TProfile*)avgNcoll_ver3 -> Rebin(centBinNum, "avgNcollR", centBin);
    TProfile *avgNcollver4 = (TProfile*)avgNcoll_ver4 -> Rebin(centBinNum, "avgNcollR", centBin);
	TProfile *avgNcoll_MBevents = (TProfile*)avgNcoll_ver4 -> Rebin(centBin_MergedNum, "avgNcollR_merged", centBin_Merged);
    
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

 //*		avgNcoll_MBevents -> SetMarkerStyle(29);
 //*		avgNcoll_MBevents -> SetMarkerColor(1);
 //*		avgNcoll_MBevents -> SetLineColor(1);
 //*		avgNcoll_MBevents -> Draw("p same");

		TLine *avgNcoll_MB = new TLine(0, avgNcoll_MBevents -> GetBinContent(1), 80, avgNcoll_MBevents -> GetBinContent(1));

		avgNcoll_MB -> SetLineStyle(7);
		avgNcoll_MB -> Draw();
    
        avgNcollver4 -> SetMarkerStyle(25);
        avgNcollver4 -> SetMarkerColor(2);
        avgNcollver4 -> SetLineColor(2);
        avgNcollver4 -> Draw("p same");

		TLegend *leg1 = new TLegend(0.45, 0.78, 0.75, 0.9);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry(avgNcoll_MB, "#LTN_{coll}#GT of total events", "p");
	    leg1 -> Draw();
        
 //*        TLegend *leg2 = new TLegend(0.45, 0.63, 0.7, 0.83);
 //*        leg2 -> SetFillStyle(0);
 //*        leg2 -> SetBorderSize(0);
 //*        leg2 -> SetTextSize(0.03);
 //*		leg2 -> AddEntry("", "#LTN_{coll}#GT of total events", "h");
 //*        leg2 -> Draw();

	}


}
