void plotMake_YavgNcollBypT_pion0()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_MBevents.root", "read");
    

    TH1D *scaledYieldBypT_MB = (TH1D*)input2 -> Get("YavgNcollpT_pion0_mb");
    TH1D *scaledYieldBypT_cent[5];

    for(int i=0; i<5; i++)
    {   
        TString input = Form("YavgNcollPion0pT_cent%d", i+1);
        scaledYieldBypT_cent[i]=(TH1D*)input1 -> Get(input);
    }
    
    
    //calculate Y/<Ncoll>_cent / Y/<Ncoll>_MB
    TH1D *ratio[5];

    for(int i=0; i<5; i++)
    {
        TString cloneName = Form("ratio_class%d_mb", i+1);

        ratio[i] = (TH1D*)scaledYieldBypT_cent[i] -> Clone(cloneName);
        ratio[i] -> Divide(scaledYieldBypT_MB);
    }
    



    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 14, 3);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("#frac{Y^{#pi^{0}}/#LTN_{coll}#GT_{cent}}{Y^{#pi^{0}}/#LTN_{coll}#GT_{MB}} ");

        ratio[0] -> SetMarkerStyle(20);
        ratio[0] -> SetMarkerColor(1);
        ratio[0] -> SetLineColor(1);
        ratio[0] -> Draw("p same");

        ratio[1] -> SetMarkerStyle(25);
        ratio[1] -> SetMarkerColor(2);
        ratio[1] -> SetLineColor(2);
        ratio[1] -> Draw("p same");

        ratio[2] -> SetMarkerStyle(26);
        ratio[2] -> SetMarkerColor(8);
        ratio[2] -> SetLineColor(8);
        ratio[2] -> Draw("p same");
    
        ratio[3] -> SetMarkerStyle(32);
        ratio[3] -> SetMarkerColor(4);
        ratio[3] -> SetLineColor(4);
        ratio[3] -> Draw("p same");

        ratio[4] -> SetMarkerStyle(34);
        ratio[4] -> SetMarkerColor(6);
        ratio[4] -> SetLineColor(6);
        ratio[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.2, 0.5, 0.5, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry(ratio[0], "cent: 0~10%", "p");
        leg1 -> AddEntry(ratio[1], "cent: 10~20%", "p");
        leg1 -> AddEntry(ratio[2], "cent: 20~40%", "p");
        leg1 -> AddEntry(ratio[3], "cent: 40~60%", "p");
        leg1 -> AddEntry(ratio[4], "cent: 60~80%", "p");
        leg1 -> Draw();


    }

}
