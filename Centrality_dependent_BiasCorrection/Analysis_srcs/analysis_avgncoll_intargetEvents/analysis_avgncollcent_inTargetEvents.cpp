void analysis_avgncollcent_inTargetEvents()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303ver4_option3_avgNcollCent_inTargerEvents", "read");
	
	TProfile *avgncollcent_midpion0[5];
	for(int i=0; i<5; i++)
	{	
		TString inputname = Form("avgncollcent_midpion0_over%dGeV", 2*i+3);	
		avgncollcent_midpion0[i] = (TProfile*)input -> Get(inputname);
	}	

	//set centrality range
	//--------------------
	double centrange[] = {0, 10, 20, 40, 60, 80};
	for(int i=0; i<5; i++)
	{		
		TString outputname = Form("avgncollcent_midpion0R_over%dGeV", 2*i+3);
		avgncollcent_midpion0[i] -> Rebin(5, outputname, centrange);
	}	
		
	//Draw plot
	//---------
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	gStyle -> SetOptStat(0);
	{
		c1 -> cd();
		
		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetBottonMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 10);
		
		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");
		
		TString *markerColor[] = {"kGreen+1", "kTeal+1", "kCyan+1", "kAzure+1", "kViolet"};
		
		for(int i=0; i<5; i++)
		{
			avgncollcent_midpion0[i] -> SetMarkerStyle(34);
			avgncollcent_midpion0[i] -> SetMarkerColor(markerColor[i]);
			avgncollcent_midpion0[i] -> SetLineColor(markerColor[i]);
			avgncollcent_midpion0[i] -> Draw("p same");
		}

		TLegend *l1 = new TLegend(0.4, 0.6, 0.8, 0.9);
		l1 -> SetFillStyle(0);
		l1 -> SetBorderSize(0);
		l1 -> SetTextSize(0.03);

		l1 -> AddEntry(avgncollcent[0], "#LTN_{coll}#GT in event with #pi^{0} > 3 GeV in |#eta|<1", "p");
		l1 -> AddEntry(avgncollcent[1], "#LTN_{coll}#GT in event with #pi^{0} > 5 GeV in |#eta|<1", "p");
		l1 -> AddEntry(avgncollcent[2], "#LTN_{coll}#GT in event with #pi^{0} > 7 GeV in |#eta|<1", "p");
		l1 -> AddEntry(avgncollcent[3], "#LTN_{coll}#GT in event with #pi^{0} > 9 GeV in |#eta|<1", "p");
		l1 -> AddEntry(avgncollcent[4], "#LTN_{coll}#GT in event with #pi^{0} > 11 GeV in |#eta|<1", "p");

		l1 -> Draw();
	}	

}
