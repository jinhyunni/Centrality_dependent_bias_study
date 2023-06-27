void plotMake_YavgNcollR()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	
	//pion0 analysis
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	//avgNcoll
	TProfile* avgNcoll = (TProfile*)input2 -> Get("avgNcoll");


	//Rebin binedges
	int pTbin1[]={0, 2};		//0~2GeV
	int pTbin2[]={2, 5};		//2~5GeV
	int pTbin3[]={5, 200};	//5~ GeV

	int centbins[]={0, 10, 20, 40, 60, 80};

	//TH2D histogram rebin
	h2pTcent -> GetXaxis() -> Set(5, centbins);
	
	h2pTcent -> Draw();
	

 //	//Draw histogram
 //	gStyle -> SetOptStat(0);
 //	TCanvas* c1 = new TCanvas("", "", 800, 600);
 //	{
 //		
 //		c1 -> cd();
 //
 //		gPad -> SetTicks();
 //		gPad -> SetLeftMargin(0.15);
 //		gPad -> SetRightMargin(0.15);
 //		gPad -> SetTopMargin(0.05);
 //		gPad -> SetBottomMargin(0.12);
 //
 //		TH1D* htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 0.0001);
 //
 //		htmp -> GetXaxis() -> SetTitle("centrality(%)");
 //		htmp -> GetXaxis() -> SetTitleSize(0.05);
 //		htmp -> GetXaxis() -> SetLabelSize(0.04);
 //		htmp -> GetXaxis() -> SetTitleOffset(1.1);
 //		htmp -> GetYaxis() -> SetTitle("Y_{pAu}/#LTN_{coll}#GT");
 //		htmp -> GetYaxis() -> SetTitleSize(0.05);
 //		htmp -> GetYaxis() -> SetLabelSize(0.04);
 //
 //		plot3 -> SetMarkerStyle(28);
 //		plot3 -> SetMarkerColor(6);
 //		plot3 -> SetLineColor(6);
 //		plot3 -> Draw("p_same");
 //
 //		//addig legend
 //		TLegend* leg1 = new TLegend(0.6, 0.57, 0.9, 0.93);
 //
 //		leg1 -> SetFillStyle(0);
 //		leg1 -> SetBorderSize(0);
 //		leg1 -> SetTextSize(0.04);
 //		leg1 -> AddEntry("", "PYTHIA8", "h");
 //		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
 //		leg1 -> AddEntry("", "option3(Default)", "h");
 //		leg1 -> AddEntry("", "#pi^{0}, |#eta|<1", "h");
 //		leg1 -> AddEntry("", "5 #leqp_{T}", "h");
 //		//leg1 -> AddEntry("", "", "");
 //		leg1 -> Draw();
 //
 //	}

}
