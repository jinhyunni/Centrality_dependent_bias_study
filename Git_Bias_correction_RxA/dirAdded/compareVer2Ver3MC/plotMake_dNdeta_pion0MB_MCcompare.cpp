void plotMake_dNdeta_pion0MB_MCcompare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dNdeta_ver2ver3MC_compare.root", "read");
  
    //dndeta in MB events
    TH1D *pion0_ver2 = (TH1D*)input1 -> Get("h1eta_pion0_ver2");
    TH1D *pion0_ver3 = (TH1D*)input1 -> Get("h1eta_pion0_ver3");
    TH1D *pion0_ver3_test = (TH1D*)input1 -> Get("h1eta_pion0_ver3_test");
    TH1D *pion0_ver3_nplRootOnly = (TH1D*)input1 -> Get("h1eta_pion0_ver3_nplRootOnly");

   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-1, 2.7, 1, 4.5);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        pion0_ver2 -> SetMarkerStyle(25);
        pion0_ver2 -> SetMarkerColor(kRed);
        pion0_ver2 -> SetLineColor(kRed);
        pion0_ver2 -> Draw("p same");
       
        pion0_ver3 -> SetMarkerStyle(29);
        pion0_ver3 -> SetMarkerColor(kOrange);
        pion0_ver3 -> SetLineColor(kOrange);
        pion0_ver3 -> Draw("p same");

        pion0_ver3_test -> SetMarkerStyle(20);
        pion0_ver3_test -> SetMarkerColor(kMagenta);
        pion0_ver3_test -> SetLineColor(kMagenta);
        pion0_ver3_test -> Draw("p same");
    
        pion0_ver3_nplRootOnly -> SetMarkerStyle(28);
        pion0_ver3_nplRootOnly -> SetMarkerColor(2);
        pion0_ver3_nplRootOnly -> SetLineColor(2);
        pion0_ver3_nplRootOnly -> Draw("p same");

        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","MB events", "h");
        leg1 -> AddEntry(pion0_ver2, "#pi^{0} in ver.2 MC", "p");
        leg1 -> AddEntry(pion0_ver3, "#pi^{0} in ver.3 MC", "p");
        leg1 -> AddEntry(pion0_ver3_test, "#pi^{0} in ver.3 test  MC", "p");
        leg1 -> AddEntry(pion0_ver3_nplRootOnly, "#pi^{0} in ver.3, NPL root Only", "p");

        
		leg1 -> Draw();

        TLegend *leg2 = new TLegend(0.5, 0.80, 0.8, 0.93);
        leg2 -> SetFillStyle(0);
        leg2 -> SetBorderSize(0);
        leg2 -> SetTextSize(0.03);
        leg2 -> AddEntry("", "ver.2: 3 #times 10^{7} events", "h");
        leg2 -> AddEntry("", "ver.3: 10^{9} events", "h");
        leg2 -> AddEntry("","ver.3 test: 3 #times 10^{7} events", "h");

        //leg2 -> Draw();

	}


}
