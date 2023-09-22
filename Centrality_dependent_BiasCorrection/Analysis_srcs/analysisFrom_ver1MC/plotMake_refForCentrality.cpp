/**************************************************
* Histogram for centrality categorization checking*
**************************************************/

void plotMake_refForCentrality()
{
	//Read in TFile
	TFile* input1 = new TFile("pAu200GeV_option3_dirAdded_refForCentrality.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_dirExcluded_refForCentralitye5.root", "read");

	TH1D *newRef = (TH1D*)input1 -> Get("centRef_pTe5");
	TH1D *oldRef = (TH1D*)input2 -> Get("centRef_pTe5");

	oldRef -> Scale(100);


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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 15, 1.5e4);

		htmp -> GetXaxis() -> SetTitle("(pTsum of chaged particle) GeV");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("# of events");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		newRef -> SetMarkerStyle(33);
		newRef -> SetMarkerColor(8);
		newRef -> SetLineColor(8);
		newRef -> Draw("p same");

		oldRef -> SetMarkerStyle(33);
		oldRef -> SetMarkerColor(6);
		oldRef -> SetLineColor(6);
		oldRef -> Draw("p same");


		//adding legend
		TLegend *leg = new TLegend(0.47, 0.63, 0.73, 0.93);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8", "h");
		leg -> AddEntry("", "p+Au 200 GeV", "h");
		leg -> AddEntry("", "option = 3", "h");
 //		leg -> AddEntry("", "Non-fixed raddi and cross-section", "h");
		leg -> AddEntry("", "Total 30 million events", "h");
		leg -> AddEntry("", "used range -3.9 < #eta < -3.0 ", "h");
		leg -> AddEntry("", "RefHis for cent-categorization", "h");
		leg -> Draw();
		
	}
}

