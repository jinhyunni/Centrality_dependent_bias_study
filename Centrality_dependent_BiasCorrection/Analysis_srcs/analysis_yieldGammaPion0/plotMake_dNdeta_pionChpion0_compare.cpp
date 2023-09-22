void plotMake_dNdeta_pionChpion0_compare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdeta_MBevents.root", "read");

    TH1D *pionCh = (TH1D*)input1 -> Get("dndeta_pionCh_mb");
    TH1D *pion0 = (TH1D*)input1 -> Get("dndeta_pion0_mb");
    TH1D *nColl = (TH1D*)input1 -> Get("ncoll_mb");

    double binwidth = pionCh -> GetBinWidth(1);
    double numEvent = nColl -> Integral();
    double scalingFactor = 1./(binwidth*numEvent);

    TH1D *pionChover2 = (TH1D*)pionCh -> Clone("pionChover2");
    pionChover2 -> Scale(1./2);
    

    pionChover2 -> Scale(scalingFactor);
    pion0 -> Scale(scalingFactor);

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 5);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        pionChover2 -> SetMarkerStyle(34);
        pionChover2 -> SetMarkerColor(4);
        pionChover2 -> SetLineColor(4);
        pionChover2 -> Draw("p same");

        pion0 -> SetMarkerStyle(28);
        pion0 -> SetMarkerColor(4);
        pion0 -> SetLineColor(4);
        pion0 -> Draw("p same");


		TLegend *leg1 = new TLegend(0.5, 0.63, 0.8, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200GeV", "h");
		leg1 -> AddEntry("","integrated p_{T}, |#eta|#LT1", "h");
 //        leg1 -> AddEntry(YavgNcollDir_new, "New-MC", "p");
 //        leg1 -> AddEntry(YavgNcollDir_old, "Old-MC", "p");

		leg1 -> Draw();

	}


}
