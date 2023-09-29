void plotMake_YavgNcollR_new()
{
	//Read in files
	TFile *input1 = new TFile("pAu200GeV_option3_pion0Cent_modif.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	TFile *input3 = new TFile("pAu200GeV_option3_pion0Analysis.root");
	
	//Yield by centrality by different pT region
	TH1D *pTclass0 = (TH1D*)input1 -> Get("pion0_cent0");	//0~2GeV
	TH1D *pTclass1 = (TH1D*)input1 -> Get("pion0_cent1");	//2~5GeV
	TH1D *pTclass2 = (TH1D*)input1 -> Get("pion0_cent2");	//5~ GeV
	
	//avgNcoll by centrality class
	TProfile *avgNcoll = (TProfile*)input2 -> Get("avgNcoll");

	
	//Get event # by each centarlity
	//ncoll by centrality -> To get event # by each centrality
	
	double binEdge[]={0, 10, 20, 40, 60, 80};

	TH2D *h2ncollCent = (TH2D*)input3 -> Get("ncoll_cent");
	TH1D *eventNumCent = (TH1D*)h2ncollCent -> ProjectionX();

	TH1D *eventNumCentR = (TH1D*)eventNumCent ->  Rebin(5 , "rebined his",binEdge);

 //	for(int i=0; i<5; i++)
 //	{
 //		double binwidth = pTclass0 -> GetBinWidth(i+1);
 //		cout << i+1 << " bin's binwidth: " << binwidth << endl;
 //		cout << i+1 << "bin's content: " << pTclass0 -> GetBinContent(i+1) << endl;
 //
 //		pTclass0 -> GetBinContent(i+1);
 //		pTclass0 -> SetBinContent(i+1, (pTclass0 -> GetBinContent(i+1))/binwidth);
 //		
 //		cout << i+1 << "After scaled:  " << pTclass0 -> GetBinContent(i+1) << endl;
 //		cout << endl;
 //	}
 //	
 //	for(int i=0; i<5; i++)
 //	{
 //		cout << i+1 << " centrality class event num: " << eventNumCentR -> GetBinContent(i+1) << endl;
 //	}

	for(int i=0; i<5; i++)
	{
		double binwidth = pTclass0 -> GetBinWidth(i+1);

		pTclass0 -> SetBinContent(i+1, (pTclass0 -> GetBinContent(i+1))/binwidth);
		pTclass1 -> SetBinContent(i+1, (pTclass1 -> GetBinContent(i+1))/binwidth);
		pTclass2 -> SetBinContent(i+1, (pTclass2 -> GetBinContent(i+1))/binwidth);
		
	}
	

	(*pTclass1) = (*pTclass1)/(*avgNcoll);
	(*pTclass1) = (*pTclass1)/(*eventNumCentR);
	pTclass1 -> Scale(1/0.01);		//pT binwidth divide	
	pTclass1 -> Draw();


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
