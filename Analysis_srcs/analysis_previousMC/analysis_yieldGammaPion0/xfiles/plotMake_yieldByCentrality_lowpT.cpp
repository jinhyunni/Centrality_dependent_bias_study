void plotMake_yieldByCentrality_lowpT()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_lowpT.root", "read");

    TH1D *highPion0 = (TH1D*)input1 -> Get("Ypion0");
    TH1D *highdir = (TH1D*)input1 -> Get("Ydir");
    TH1D *highPion0avgNcoll = (TH1D*)input1 -> Get("Ypion0avgNcoll");

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 80, 5);

		htmp -> GetXaxis() -> SetTitle("centrality(%)");
		htmp -> GetYaxis() -> SetTitle("Y^{#pi^{0}}/#LTN_{coll}#GT");
    
 //        highPion0 -> SetMarkerStyle(48);
 //        highPion0 -> SetMarkerColor(2);
 //        highPion0 -> SetLineColor(2);
 //        highPion0 -> Draw("p same");
 //
 //        highdir -> SetMarkerStyle(49);
 //        highdir -> SetMarkerColor(4);
 //        highdir -> SetLineColor(4);
 //        highdir -> Draw("p same");

        highPion0avgNcoll -> SetMarkerStyle(48);
        highPion0avgNcoll -> SetMarkerColor(1);
        highPion0avgNcoll -> SetLineColor(1);
        highPion0avgNcoll -> Draw("p same");
        
		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","p_{T} #leq 2 GeV, |#eta| #LT 1", "h");
 //        leg1 -> AddEntry(highPion0,"#pi^{0}", "p");
 //        leg1 -> AddEntry(highdir,"#gamma^{dir}", "p");
        leg1 -> AddEntry("", "present analysis method applied", "h");

		leg1 -> Draw();

	}


}
