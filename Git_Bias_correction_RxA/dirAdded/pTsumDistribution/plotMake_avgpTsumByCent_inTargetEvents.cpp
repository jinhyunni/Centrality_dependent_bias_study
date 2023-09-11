void plotMake_avgpTsumByCent_inTargetEvents()
{

    //Inputs
   	TFile *input1 = new TFile("pAu200GeV_kiaf_option3_avgpTsumCent_inTargetEvents.root", "read");
    
    TProfile *inElastic = (TProfile*)input1 -> Get("avgpTsumCent_inElastic");
    TProfile *inPion0 = (TProfile*)input1 -> Get("avgpTsumCent_inPion0");
    TProfile *inDir = (TProfile*)input1 -> Get("avgpTsumCent_inDir");
    

    //Rebin to set centrality class
    double binX[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    TProfile *inElastic_set = (TProfile*)inElastic -> Rebin(10, "inElastic_set", binX);
    TProfile *inPion0_set = (TProfile*)inPion0 -> Rebin(10, "inPion0_set", binX);
    TProfile *inDir_set = (TProfile*)inDir -> Rebin(10, "inDir_set", binX);
    
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 100, 8);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("#LTp_{T} sum#GT");
    
        inElastic_set -> SetMarkerStyle(21);
        inElastic_set -> SetMarkerColor(6);
        inElastic_set -> SetLineColor(6);
        inElastic_set -> Draw("p same");

        inPion0_set -> SetMarkerStyle(46);
        inPion0_set -> SetMarkerColor(8);
        inPion0_set -> SetLineColor(8);
        inPion0_set -> Draw("p same");

        inDir_set -> SetMarkerStyle(34);
        inDir_set -> SetMarkerColor(9);
        inDir_set -> SetLineColor(9);
        inDir_set -> Draw("p same");

		TLegend *leg1 = new TLegend(0.38, 0.63, 0.78, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
        leg1 -> AddEntry("", "mid-rapidity: |#eta|<1", "h");
        leg1 -> AddEntry("", "#LTp_{T} sum#GT of charged particles", "h");
        leg1 -> AddEntry(inElastic_set, "inelastic events", "p");
        leg1 -> AddEntry(inPion0_set, "events #pi^{0} produced in mid-rapidity", "p");
        leg1 -> AddEntry(inDir_set, "events #gamma^{dir} produced in mid-rapidity", "p");
		
        leg1 -> Draw();

	}


}
