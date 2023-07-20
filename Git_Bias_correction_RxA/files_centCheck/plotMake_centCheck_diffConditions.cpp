/**************************************************
* Histogram for centrality categorization checking*
**************************************************/

void plotMake_centCheck_diffConditions()
{
	//Read in TFile
	TFile* input1 = new TFile("pAu200GeV_option3_dirAdded_np0Excluded_centCheckAll.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_dirAdded_oldRef_centCheckAll.root", "read");

	TH1D *dirAdded_newRef = (TH1D*)input1 -> Get("centralityCheck1");
	TH1D *dirAdded_oldRef = (TH1D*)input2 -> Get("centralityCheck2");

	//overflow bin control
	dirAdded_newRef -> SetBinContent(10, dirAdded_newRef -> GetBinContent(10) + dirAdded_newRef -> GetBinContent(11));

	dirAdded_oldRef -> SetBinContent(10, dirAdded_oldRef -> GetBinContent(10) + dirAdded_oldRef -> GetBinContent(11));


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

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 100, 1.7e5);

		htmp -> GetXaxis() -> SetTitle("centrality");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("# of events");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		dirAdded_newRef -> SetMarkerStyle(33);
		dirAdded_newRef -> SetMarkerColor(8);
		dirAdded_newRef -> SetLineColor(8);
		dirAdded_newRef -> Draw("p same");

		dirAdded_oldRef -> SetMarkerStyle(33);
		dirAdded_oldRef -> SetMarkerColor(1);
		dirAdded_oldRef -> SetLineColor(1);
		dirAdded_oldRef -> Draw("p same");



		//adding legend
		TLegend *leg = new TLegend(0.19, 0.6, 0.45, 0.9);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.03);
		leg -> AddEntry("", "PYTHIA8, p+Au 200 GeV, option3", "h");
		leg -> AddEntry("", "Analyze:  #gamma included, 30 million events", "h");
 //		leg -> AddEntry("", "Non-fixed raddi and cross-section", "h");
 //		leg -> AddEntry("", "centrality categorization check", "h");
		leg -> AddEntry("", "random 600,000 events", "h");

		leg -> AddEntry(dirAdded_newRef, "Refed with 30 million #gamma  included MC sims", "p");
		leg -> AddEntry(dirAdded_oldRef, "Refed with 100 thousand #gamma  excluded MC sims", "p");
		leg -> Draw();
		
	}
}

