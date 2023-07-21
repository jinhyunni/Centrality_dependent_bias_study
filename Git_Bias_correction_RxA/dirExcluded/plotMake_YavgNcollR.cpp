/*
	Draw Y_pAu/<N_coll> histogram
 */

void plotMake_YavgNcollR()
{
	//Inputfile
	TFile *input1 = new TFile("pAu200GeV_option3_YavgNcollR_old.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_YavgNcollR_new_enhanced.root", "read");
	
	//Get histogram
	TH1D *old_pTclass1 = (TH1D*)input1 -> Get("YavgNcollR1");
	TH1D *old_pTclass2 = (TH1D*)input1 -> Get("YavgNcollR2");
	TH1D *old_pTclass3 = (TH1D*)input1 -> Get("YavgNcollR3");

	TH1D *new_pTclass1 = (TH1D*)input2 -> Get("pTclass1");
	TH1D *new_pTclass2 = (TH1D*)input2 -> Get("pTclass2");
	TH1D *new_pTclass3 = (TH1D*)input2 -> Get("pTclass3");


	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas* c1 = new TCanvas("", "", 800, 600);
	{

		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.17);
		gPad -> SetRightMargin(0.17);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 0.00001);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("Y_{pAu}/#LTN_{coll}#GT");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

 //		new_pTclass1 -> SetMarkerStyle(28);
 //		new_pTclass1 -> SetMarkerColor(6);
 //		new_pTclass1 -> SetLineColor(6);
 //		new_pTclass1 -> Draw("p_same");			

 //		new_pTclass2 -> SetMarkerStyle(28);
 //		new_pTclass2 -> SetMarkerColor(9);
 //		new_pTclass2 -> SetLineColor(9);
 //		new_pTclass2 -> Draw("p_same");		

		new_pTclass3 -> SetMarkerStyle(28);
		new_pTclass3 -> SetMarkerColor(8);
		new_pTclass3 -> SetLineColor(8);
		new_pTclass3 -> Draw("p_same");		

		//addig legend
		TLegend* leg1 = new TLegend(0.6, 0.57, 0.9, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option3(Default)", "h");
		leg1 -> AddEntry("", "#pi^{0}, |#eta|<1", "h");
		leg1 -> AddEntry("", " p_{T} #GT 5", "h");
 //		leg1 -> AddEntry("", "new analysis code", "h");
		leg1 -> Draw();

	}	

}
