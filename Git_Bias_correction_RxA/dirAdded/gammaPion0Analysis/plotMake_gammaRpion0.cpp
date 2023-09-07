void plotMake_gammaRpion0()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "read");
    TFile *input2 = new TFile("pAu200GeV_kiaf_option3_yieldOfgammaApion0_bypT.root", "read");

    //From nplserver
    TH1D *ratio1[5];
    for(int i=0; i<5; i++)
    {   
        TString input = Form("gammaRpion0_cent%d", i+1);
        ratio1[i] = (TH1D*)input1 -> Get(input);
    }
    
    //From KIAF
    TH1D *ratio2[5];
    for(int i=0; i<5; i++)
    {
        TString input = Form("gammaRpion0_cent%d", i+1);
        ratio2[i] = (TH1D*)input2 -> Get(input);
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

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0, 20, 0.1);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
		htmp -> GetYaxis() -> SetTitle("#gamma^{dir}/#pi^{0}");
    
        ratio1[4] -> SetMarkerStyle(21);
        ratio1[4] -> SetMarkerColor(1);
        ratio1[4] -> SetLineColor(1);
        ratio1[4] -> Draw("p same");

        ratio2[4] -> SetMarkerStyle(25);
        ratio2[4] -> SetMarkerColor(1);
        ratio2[4] -> SetLineColor(1);
        ratio2[4] -> Draw("p same");
        
 //        ratio1[1] -> SetMarkerStyle(41);
 //        ratio1[1] -> SetMarkerColor(2);
 //        ratio1[1] -> SetLineColor(2);
 //        ratio1[1] -> Draw("p same");
 //         
 //        ratio1[2] -> SetMarkerStyle(47);
 //        ratio1[2] -> SetMarkerColor(8);
 //        ratio1[2] -> SetLineColor(8);
 //        ratio1[2] -> Draw("p same");
 //
 //        ratio1[3] -> SetMarkerStyle(48);
 //        ratio1[3] -> SetMarkerColor(4);
 //        ratio1[3] -> SetLineColor(4);
 //        ratio1[3] -> Draw("p same");
 //
 //        ratio1[4] -> SetMarkerStyle(49);
 //        ratio1[4] -> SetMarkerColor(6);
 //        ratio1[4] -> SetLineColor(6);
 //        ratio1[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.43, 0.60, 0.73, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","#pi^{0}, #gamma^{dir} in |#eta|#LT1", "h");
 //        leg1 -> AddEntry(ratio[0], "cent: 0~10%", "p");
 //        leg1 -> AddEntry(ratio[1], "cent: 10~20%", "p");
 //        leg1 -> AddEntry(ratio[2], "cent: 20~40%", "p");
 //        leg1 -> AddEntry(ratio[3], "cent: 40~60%", "p");
 //        leg1 -> AddEntry(ratio[4], "cent: 60~80%", "p");
        leg1 -> AddEntry(ratio1[4], "cent: 60~80%, Old-MC", "p");
        leg1 -> AddEntry(ratio2[4], "cent: 60~80%, New-MC", "p");

		leg1 -> Draw();

	}


}
