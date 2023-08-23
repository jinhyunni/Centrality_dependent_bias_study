
#define DIREX_PATH "/Users/jinhyunpark/npl/gitHub/xloadFromServer/Git_Bias_correction_RxA/dirExcluded"

void plotMake_avgNcollCentPion0()
{

    //Inputs
   	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentPion0.root", "read");
    TFile *input2 = new TFile(Form("%s/pAu200GeV_option3_avgNcoll.root", DIREX_PATH), "read");
    TFile *input3 = new TFile(Form("%s/pAu200GeV_option3_avgNcoll_newest.root", DIREX_PATH), "read");

 //    TFile *input2 = new TFile("DIREX_PATH/pAu200GeV_option3_avgNcoll.root", "read");
 //    TFile *input3 = new TFile("DIREX_PATo/pAu200GeV_option3_avgNcoll_newest.root", "read");

    TProfile *avgNcoll_new = (TProfile*)input1 -> Get("avgNcollCentPion0"); 
    TProfile *avgNcoll_old = (TProfile*)input2 -> Get("avgNcoll"); //already rebinned
    //Event selection condition added in old-MC to calculate <Ncoll>
    TProfile *avgNcoll_old_modif = (TProfile*)input3 -> Get("avgNcoll");
    
    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollR_new = (TProfile*)avgNcoll_new -> Rebin(5, "avgNcollR", binX);
    
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
    
        avgNcollR_new -> SetMarkerStyle(20);
        avgNcollR_new -> SetMarkerColor(2);
        avgNcollR_new -> SetLineColor(2);
        avgNcollR_new -> Draw("p same");
        
        avgNcoll_old -> SetMarkerStyle(20);
        avgNcoll_old -> SetMarkerColor(4);
        avgNcoll_old -> SetLineColor(4);
        avgNcoll_old -> Draw("p same");
    
        avgNcoll_old_modif -> SetMarkerStyle(25);
        avgNcoll_old_modif -> SetMarkerColor(4);
        avgNcoll_old_modif -> SetLineColor(4);
        avgNcoll_old_modif -> Draw("p same");


		TLegend *leg1 = new TLegend(0.38, 0.63, 0.68, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200GeV", "h");
        leg1 -> AddEntry(avgNcollR_new,"New MC 3e7 Events, integrated p_{T}, |#eta|<1", "p");
        leg1 -> AddEntry(avgNcoll_old_modif,"Old MC 1e5 Events, integrated p_{T}, |#eta|<1", "p");
        leg1 -> AddEntry(avgNcoll_old,"Old MC 1e5 Events, inelastic events", "p");
		
        leg1 -> Draw();

	}


}
