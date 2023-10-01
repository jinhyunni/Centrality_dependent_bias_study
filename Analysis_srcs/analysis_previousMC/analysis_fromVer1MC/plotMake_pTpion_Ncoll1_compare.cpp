/*************************************************
* pion0's invariant yield  by centrality *

* Ncoll = 1 events
*************************************************/

void plotMake_pTpion_Ncoll1_compare()
{
	//Read in TFile
	TFile* input1 = new TFile("pAu200GeV_option1_pion0Analysis_Ncoll1_etacut_1e5.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option1_pion0Analysis_Ncoll1_etacut_binw_1e5.root", "read");

	TH1D* Ncoll11 = (TH1D*)input1 -> Get("pTpion0");
	TH1D* Ncoll12 = (TH1D*)input2 -> Get("pTpion0");
	
	//Rebined-edges
	double xbins[] = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0};

	//binwidth pre-divided
	TH1D* ppR1 = (TH1D*)Ncoll11 -> Rebin(16, "ppR1", xbins);
	double scalar1 = 1./(ppR1 -> GetBinWidth(1));
	ppR1 -> Scale(scalar1);

	//binwidth after divied
	TH1D* ppR2 = (TH1D*)Ncoll12 -> Rebin(16, "ppR2", xbins);
	double scalar2 = 1./(ppR2 -> GetBinWidth(1));
	ppR2 -> Scale(scalar2);


	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	c1 -> Divide(2,1); 
	{
		c1 -> cd(1);

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp1 = (TH1F*)gPad -> DrawFrame(0, 0, 7, 8);

		htmp1 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp1 -> GetXaxis() -> SetTitleSize(0.05);
		htmp1 -> GetXaxis() -> SetLabelSize(0.04);
		htmp1 -> GetXaxis() -> SetTitleOffset(1.1);
		htmp1 -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp1 -> GetYaxis() -> SetTitleSize(0.05);
		htmp1 -> GetYaxis() -> SetLabelSize(0.04);	

		ppR1 -> SetMarkerStyle(20);
		ppR1 -> SetMarkerColor(1);
		ppR1 -> SetLineColor(1);
		ppR1 -> Draw("p same");

		//adding legend
		TLegend* leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option = 1(default)", "h");
		leg1 -> AddEntry("", "N_{coll}=1 event", "h");
		leg1 -> AddEntry("", "|#eta|<1", "h");
		leg1 -> AddEntry("", "binwidth pre-divided", "h");
		leg1 -> AddEntry(ppR1, "#pi^{0}", "p");
		leg1 -> Draw();

		c1 -> cd(2);

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp2 = (TH1F*)gPad -> DrawFrame(0, 0, 7, 8);

		htmp2 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp2 -> GetXaxis() -> SetTitleSize(0.05);
		htmp2 -> GetXaxis() -> SetLabelSize(0.04);
		htmp2 -> GetXaxis() -> SetTitleOffset(1.1);
		htmp2 -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp2 -> GetYaxis() -> SetTitleSize(0.05);
		htmp2 -> GetYaxis() -> SetLabelSize(0.04);	

		ppR2 -> SetMarkerStyle(20);
		ppR2 -> SetMarkerColor(1);
		ppR2 -> SetLineColor(1);
		ppR2 -> Draw("p same");

		//adding legend
		TLegend* leg2 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg2 -> SetFillStyle(0);
		leg2 -> SetBorderSize(0);
		leg2 -> SetTextSize(0.04);
		leg2 -> AddEntry("", "PYTHIA8", "h");
		leg2 -> AddEntry("", "p+Au 200 GeV", "h");
		leg2 -> AddEntry("", "option = 1(default)", "h");
		leg2 -> AddEntry("", "N_{coll}=1 event", "h");
		leg2 -> AddEntry("", "|#eta|<1", "h");
		leg2 -> AddEntry("", "binwidth after-divided", "h");
		leg2 -> AddEntry(ppR2, "#pi^{0}", "p");
		leg2 -> Draw();
		
	}

}

