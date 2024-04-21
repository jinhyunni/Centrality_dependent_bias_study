/**************************************************
* Histogram for centrality categorization checking*
**************************************************/

void plotMake_centCheck()
{
	//Read in TFile
 	TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");
    TH2D *h2ncollcent = (TH2D*)input1 -> Get("ncollCent");

 	TH1D *nevent = (TH1D*)h2ncollcent -> ProjectionX("centCheck");

	//overflow bin control
 	nevent -> SetBinContent(10, nevent -> GetBinContent(10) + nevent -> GetBinContent(11));

	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.12);
		gPad -> SetRightMargin(0.12);
		gPad -> SetTopMargin(0.1);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0.1e8, 100, 1.5e8);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("# of events");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

 		nevent -> SetMarkerStyle(25);
 		nevent -> SetMarkerColor(2);
 		nevent -> SetLineColor(2);
 		nevent -> Draw("p same");


		//adding legend
		TLegend *leg = new TLegend(0.19, 0.6, 0.45, 0.9);
		leg -> SetFillStyle(0);
		leg -> SetBorderSize(0);
		leg -> SetTextSize(0.04);
		leg -> AddEntry("", "PYTHIA8, p+Au 200 GeV, option3", "h");
		leg -> AddEntry("", "centrality categorization check", "h");
		leg -> AddEntry("", "Events classified by using #sump^{ch}_{T} in -3.9 < #eta < -3.0", "h");

		leg -> Draw();
		
	}
}

