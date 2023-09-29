void plotMake_gammaRpion0BypT()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "read");
    
    TH1D *yieldBypT_pion0[5];
    TH1D *yieldBypT_dir[5];
    for(int i=0; i<5; i++)
    {   
        TString input_pion0 = Form("Ypion0pT_cent%dR", i+1);
        TString input_dir = Form("YdirpT_cent%dR", i+1);

        yieldBypT_pion0[i]=(TH1D*)input1 -> Get(input_pion0);
        yieldBypT_dir[i] = (TH1D*)input1 -> Get(input_dir);
    }

    TH1D *gammaRpion0[5];
    for(int i=0; i<5; i++)
    {
        TString name = Form("gammRpion0_centclass%d", i+1);

        gammaRpion0[i]=(TH1D*)yieldBypT_dir[i] -> Clone(name);
        gammaRpion0[i] -> Divide(yieldBypT_pion0[i]);
    }
    
    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0, 5, 0.01);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("Y^{#gamma^{dir}}/Y^{#pi^{0}}");

        gammaRpion0[0] -> SetMarkerStyle(20);
        gammaRpion0[0] -> SetMarkerColor(1);
        gammaRpion0[0] -> SetLineColor(1);
        gammaRpion0[0] -> Draw("p same");

        gammaRpion0[1] -> SetMarkerStyle(21);
        gammaRpion0[1] -> SetMarkerColor(2);
        gammaRpion0[1] -> SetLineColor(2);
        gammaRpion0[1] -> Draw("p same");

        gammaRpion0[2] -> SetMarkerStyle(22);
        gammaRpion0[2] -> SetMarkerColor(8);
        gammaRpion0[2] -> SetLineColor(8);
        gammaRpion0[2] -> Draw("p same");
    
        gammaRpion0[3] -> SetMarkerStyle(23);
        gammaRpion0[3] -> SetMarkerColor(4);
        gammaRpion0[3] -> SetLineColor(4);
        gammaRpion0[3] -> Draw("p same");

        gammaRpion0[4] -> SetMarkerStyle(34);
        gammaRpion0[4] -> SetMarkerColor(6);
        gammaRpion0[4] -> SetLineColor(6);
        gammaRpion0[4] -> Draw("p same");

      

        TLegend *leg1 = new TLegend(0.5, 0.53, 0.8, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry(gammaRpion0[0], "cent: 0~10%", "p");
        leg1 -> AddEntry(gammaRpion0[1], "cent: 10~20%", "p");
        leg1 -> AddEntry(gammaRpion0[2], "cent: 20~40%", "p");
        leg1 -> AddEntry(gammaRpion0[3], "cent: 40~60%", "p");
        leg1 -> AddEntry(gammaRpion0[4], "cent: 60~80%", "p");
        leg1 -> Draw();


    }

}
