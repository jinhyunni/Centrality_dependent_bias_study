void plotMake_ratio_ratioCent2MB_highpT_dir2pion0_byCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_onlyDirPhotonUsed_option3_ratio_ratioCent2MB_highpT_pion0toDir_bypT.root", "read");

    TH1D *ratio_scaled[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("centBias_bypT_pion0toDir_cent%d", i+1);

        ratio_scaled[i] = (TH1D*)input1 -> Get(inputname);
    }
    

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0.7, 20, 1.5);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        //htmp -> GetYaxis() -> SetTitle("Centrality Bias on #pi^{0} / Centrality Bias on #gamma^{dir}");
        htmp -> GetYaxis() -> SetTitle("(Y^{#pi^{0}}/Y^{#gamma^{dir}})_{cent} / (Y^{#pi^{0}}/Y^{#gamma^{dir}})_{MB}");
                   
        ratio_scaled[0] -> SetMarkerStyle(34);
        ratio_scaled[0]-> SetMarkerColor(kViolet);
        ratio_scaled[0] -> SetLineColor(kViolet);
        ratio_scaled[0] -> Draw("p same");

        ratio_scaled[1] -> SetMarkerStyle(49);
        ratio_scaled[1] -> SetMarkerColor(kBlue);
        ratio_scaled[1] -> SetLineColor(kBlue);
        ratio_scaled[1] -> Draw("p same");

        ratio_scaled[2] -> SetMarkerStyle(28);
        ratio_scaled[2] -> SetMarkerColor(kGreen+1);
        ratio_scaled[2] -> SetLineColor(kGreen+1);
        ratio_scaled[2] -> Draw("p same");
    
        ratio_scaled[3] -> SetMarkerStyle(48);
        ratio_scaled[3] -> SetMarkerColor(kOrange);
        ratio_scaled[3] -> SetLineColor(kOrange);
        ratio_scaled[3] -> Draw("p same");

        ratio_scaled[4] -> SetMarkerStyle(47);
        ratio_scaled[4] -> SetMarkerColor(kRed);
        ratio_scaled[4] -> SetLineColor(kRed);
        ratio_scaled[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.14, 0.57, 0.58, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#gamma^{dir}, #pi^{0} in |#eta|<1", "h");

        leg1 -> AddEntry(ratio_scaled[0], "centrality: 0~10%", "p");
        leg1 -> AddEntry(ratio_scaled[1], "centrality: 10~20%", "p");
        leg1 -> AddEntry(ratio_scaled[2], "centrality: 20~40%", "p");
        leg1 -> AddEntry(ratio_scaled[3], "centrality: 40~60%", "p");
        leg1 -> AddEntry(ratio_scaled[4], "centrality: 60~80%", "p");

        leg1 -> Draw();

    }

}
