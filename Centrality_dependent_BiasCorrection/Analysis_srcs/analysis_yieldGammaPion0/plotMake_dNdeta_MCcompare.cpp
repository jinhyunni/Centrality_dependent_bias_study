void plotMake_dNdeta_MCcompare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_MBevents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_kiaf_option3_yieldOfgammaApion0_MBevents.root", "read");
  
    //dndeta in MB events
    TH1D *pion0_old = (TH1D*)input1 -> Get("dndeta_pion0_mb");
    TH1D *dir_old = (TH1D*)input1 -> Get("dndeta_dir_mb");

    TH1D *pion0_new = (TH1D*)input2 -> Get("dndeta_pion0_mb");
    TH1D *dir_new = (TH1D*)input2 -> Get("dndeta_dir_mb");
   

   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 8);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        pion0_old -> SetMarkerStyle(34);
        pion0_old -> SetMarkerColor(9);
        pion0_old -> SetLineColor(9);
        pion0_old -> Draw("p same");
       
    
        dir_old -> SetMarkerStyle(21);
        dir_old -> SetMarkerColor(9);
        dir_old -> SetLineColor(9);
        //dir_old -> Draw("p same");

        pion0_new -> SetMarkerStyle(28);
        pion0_new -> SetMarkerColor(6);
        pion0_new -> SetLineColor(6);
        pion0_new -> Draw("p same");
       
    
        dir_new -> SetMarkerStyle(25);
        dir_new -> SetMarkerColor(6);
        dir_new -> SetLineColor(6);
        //dir_new -> Draw("p same");
        

        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","MB events", "h");
        leg1 -> AddEntry(pion0_old, "#pi^{0} in Old-MC(ver.2)", "p");
        //leg1 -> AddEntry(dir_old, "#gamma^{dir} in Old-MC(ver.2)", "p");
        leg1 -> AddEntry(pion0_new, "#pi^{0} in New-MC(ver.3)", "p");
        //leg1 -> AddEntry(dir_new, "#gamma^{dir} in New-MC(ver.3)", "p");
        
		leg1 -> Draw();

        TLegend *leg2 = new TLegend(0.5, 0.80, 0.8, 0.93);
        leg2 -> SetFillStyle(0);
        leg2 -> SetBorderSize(0);
        leg2 -> SetTextSize(0.03);
        leg2 -> AddEntry("", "ver.2: 3 #times 10^{7} events", "h");
        leg2 -> AddEntry("", "ver.3: 10^{9} events", "h");

        leg2 -> Draw();

	}


}
