/*************************************************
* Calculate average Ncoll in each centrality *
	
* centrality class

	class1 0~10%
	class2 10~20%
	class3 20~40%
	class4 40~60%
	class5 60~80%

? consider using arrays to store values...?

* 100,000 events
	
***********************************************/

void plotMake_avgNcoll()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "read");
	TProfile* avgNcoll = (TProfile*)input -> Get("avgNcoll");
		
	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 80, 15);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		avgNcoll -> SetMarkerStyle(21);
		avgNcoll -> SetMarkerColor(38);
		avgNcoll -> SetLineColor(38);
		avgNcoll -> Draw("p same");

		//adding legend
		TLegend *leg = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8", "h");
		leg -> AddEntry("", "p+Au 200 GeV", "h");
		leg -> AddEntry("", "option = 3(No diffraction)", "h");
		leg -> AddEntry("", "100,000 events", "h");
		leg -> AddEntry("", "inelastic #: 96,129", "h");
		leg -> Draw();
			
	}
}

