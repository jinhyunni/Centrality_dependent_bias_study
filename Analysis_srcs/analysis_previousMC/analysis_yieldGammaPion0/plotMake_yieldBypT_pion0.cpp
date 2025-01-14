void plotMake_yieldBypT_pion0()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_MBevents.root", "read");
    
    TH1D *yieldBypT[5];
    for(int i=0; i<5; i++)
    {   
        TString input = Form("Ypion0pT_cent%dR", i+1);
        yieldBypT[i]=(TH1D*)input1 -> Get(input);
    }

    TH1D *yieldClass1 = yieldBypT[0];
    TH1D *yieldClass2 = yieldBypT[1];
    TH1D *yieldClass3 = yieldBypT[2];
    TH1D *yieldClass4 = yieldBypT[3];
    TH1D *yieldClass5 = yieldBypT[4];

    TH1D *yieldMB = (TH1D*)input2 -> Get("dndpt_pion0_mb");


    for(int i=0; i<5; i++)
    {
        TString output = Form("ratio_cent2mb_%d", i+1);
        TString cloneName = Form("ratio%d", i+1);
        
        TH1D *output = (TH1D*)yieldBypT[i] -> Clone(cloneName);
        output -> Divide(yieldMB);
    }



    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLogy(1);
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.000000001, 14, 100);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("1/N_{event} dN^{#pi^{0}}/dp_{T}");

        yieldClass1 -> SetMarkerStyle(20);
        yieldClass1 -> SetMarkerColor(1);
        yieldClass1 -> SetLineColor(1);
        yieldClass1 -> Draw("p same");

        yieldClass2 -> SetMarkerStyle(25);
        yieldClass2 -> SetMarkerColor(2);
        yieldClass2 -> SetLineColor(2);
        yieldClass2 -> Draw("p same");

        yieldClass3 -> SetMarkerStyle(26);
        yieldClass3 -> SetMarkerColor(8);
        yieldClass3 -> SetLineColor(8);
        yieldClass3 -> Draw("p same");
    
        yieldClass4 -> SetMarkerStyle(32);
        yieldClass4 -> SetMarkerColor(4);
        yieldClass4 -> SetLineColor(4);
        yieldClass4 -> Draw("p same");

        yieldClass5 -> SetMarkerStyle(34);
        yieldClass5 -> SetMarkerColor(6);
        yieldClass5 -> SetLineColor(6);
        yieldClass5 -> Draw("p same");

        yieldMB -> SetMarkerStyle(8);
        yieldMB -> SetMarkerColor(9);
        yieldMB -> SetLineColor(9);
        yieldMB -> Draw("p same");


        TLegend *leg1 = new TLegend(0.5, 0.53, 0.8, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry(yieldClass1, "cent: 0~10%", "p");
        leg1 -> AddEntry(yieldClass2, "cent: 10~20%", "p");
        leg1 -> AddEntry(yieldClass3, "cent: 20~40%", "p");
        leg1 -> AddEntry(yieldClass4, "cent: 40~60%", "p");
        leg1 -> AddEntry(yieldClass5, "cent: 60~80%", "p");
        leg1 -> AddEntry(yieldMB, "MB events", "p");
        leg1 -> Draw();


    }

}
