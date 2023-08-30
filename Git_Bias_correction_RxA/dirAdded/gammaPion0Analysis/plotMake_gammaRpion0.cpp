void plotMake_gammaRpion0()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "read");

    TH1D *ratio[5];
    for(int i=0; i<5; i++)
    {   
        TString input = Form("gammaRpion0_cent%d", i+1);
        ratio[i] = (TH1D*)input1 -> Get(input);
    }
    

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0, 10, 0.1);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
		htmp -> GetYaxis() -> SetTitle("#gamma^{dir}/#pi^{0}");
    
        ratio[0] -> SetMarkerStyle(39);
        ratio[0] -> SetMarkerColor(1);
        ratio[0] -> SetLineColor(1);
        ratio[0] -> Draw("p same");
        
        ratio[1] -> SetMarkerStyle(41);
        ratio[1] -> SetMarkerColor(2);
        ratio[1] -> SetLineColor(2);
        ratio[1] -> Draw("p same");
         
        ratio[2] -> SetMarkerStyle(47);
        ratio[2] -> SetMarkerColor(8);
        ratio[2] -> SetLineColor(8);
        ratio[2] -> Draw("p same");

        ratio[3] -> SetMarkerStyle(48);
        ratio[3] -> SetMarkerColor(4);
        ratio[3] -> SetLineColor(4);
        ratio[3] -> Draw("p same");

        ratio[4] -> SetMarkerStyle(49);
        ratio[4] -> SetMarkerColor(6);
        ratio[4] -> SetLineColor(6);
        ratio[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.43, 0.60, 0.73, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","#pi^{0}, #gamma^{dir} in |#eta|#LT1", "h");
        leg1 -> AddEntry(ratio[0], "cent: 0~10%", "p");
        leg1 -> AddEntry(ratio[1], "cent: 10~20%", "p");
        leg1 -> AddEntry(ratio[2], "cent: 20~40%", "p");
        leg1 -> AddEntry(ratio[3], "cent: 40~60%", "p");
        leg1 -> AddEntry(ratio[4], "cent: 60~80%", "p");

		leg1 -> Draw();

	}


}
