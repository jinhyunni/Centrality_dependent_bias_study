void plotMake_scaledYield_dircent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");

    TH1D *scaled_cent[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("YavgNcollDirpT_cent%d", i+1);

        scaled_cent[i] = (TH1D*)input1 -> Get(inputname);
    }
    
    TH1D *scaled_mb = (TH1D*)input2 -> Get("YavgNcollDirpT_mb");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        gPad -> SetLogy();

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.00000000001, 20, 0.001);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{event}} #frac{dN^{#gamma^{dir}}}{dp_{T}} ");
        
        scaled_mb -> SetMarkerStyle(34);
        scaled_mb -> SetMarkerColor(1);
        scaled_mb -> SetLineColor(1);
        scaled_mb -> Draw("p same");
            
        scaled_cent[0] -> SetMarkerStyle(34);
        scaled_cent[0]-> SetMarkerColor(kGreen+1);
        scaled_cent[0] -> SetLineColor(kGreen+1);
        scaled_cent[0] -> Draw("p same");

        scaled_cent[1] -> SetMarkerStyle(34);
        scaled_cent[1] -> SetMarkerColor(kTeal+1);
        scaled_cent[1] -> SetLineColor(kTeal+1);
        scaled_cent[1] -> Draw("p same");

        scaled_cent[2] -> SetMarkerStyle(28);
        scaled_cent[2] -> SetMarkerColor(kCyan+1);
        scaled_cent[2] -> SetLineColor(kCyan+1);
        scaled_cent[2] -> Draw("p same");
    
        scaled_cent[3] -> SetMarkerStyle(47);
        scaled_cent[3] -> SetMarkerColor(kAzure);
        scaled_cent[3] -> SetLineColor(kAzure);
        scaled_cent[3] -> Draw("p same");

        scaled_cent[4] -> SetMarkerStyle(28);
        scaled_cent[4] -> SetMarkerColor(kBlue);
        scaled_cent[4] -> SetLineColor(kBlue);
        scaled_cent[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.4, 0.65, 0.8, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#gamma^{dir} in |#eta|<1", "h");
        
        leg1 -> AddEntry(scaled_mb, "inelastic events(MB)", "p");
        leg1 -> AddEntry(scaled_cent[0], "centrality: 0~10%", "p");
        leg1 -> AddEntry(scaled_cent[1], "centrality: 10~20%", "p");
        leg1 -> AddEntry(scaled_cent[2], "centrality: 20~40%", "p");
        leg1 -> AddEntry(scaled_cent[3], "centrality: 40~60%", "p");
        leg1 -> AddEntry(scaled_cent[4], "centrality: 60~80%", "p");

        leg1 -> Draw();

    }

}
