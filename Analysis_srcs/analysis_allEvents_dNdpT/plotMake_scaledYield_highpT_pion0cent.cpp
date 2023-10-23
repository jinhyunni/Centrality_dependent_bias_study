void plotMake_scaledYield_highpT_pion0cent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");

    TH1D *scaled_cent[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("YavgNcollPion0pT_cent%d", i+1);

        scaled_cent[i] = (TH1D*)input1 -> Get(inputname);
    }
    
    TH1D *scaled_mb = (TH1D*)input2 -> Get("YavgNcollPion0pT_mb");

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

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0.0000000001, 20, 0.01);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{#LT N_{coll} #GT_{cent}} #frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}} ");
        
        scaled_mb -> SetMarkerStyle(34);
        scaled_mb -> SetMarkerColor(1);
        scaled_mb -> SetLineColor(1);
        scaled_mb -> Draw("p same");
            
        scaled_cent[0] -> SetMarkerStyle(34);
        scaled_cent[0]-> SetMarkerColor(kOrange);
        scaled_cent[0] -> SetLineColor(kOrange);
        scaled_cent[0] -> Draw("p same");

        scaled_cent[1] -> SetMarkerStyle(34);
        scaled_cent[1] -> SetMarkerColor(kRed);
        scaled_cent[1] -> SetLineColor(kRed);
        scaled_cent[1] -> Draw("p same");

        scaled_cent[2] -> SetMarkerStyle(28);
        scaled_cent[2] -> SetMarkerColor(kPink);
        scaled_cent[2] -> SetLineColor(kPink);
        scaled_cent[2] -> Draw("p same");
    
        scaled_cent[3] -> SetMarkerStyle(46);
        scaled_cent[3] -> SetMarkerColor(kMagenta);
        scaled_cent[3] -> SetLineColor(kMagenta);
        scaled_cent[3] -> Draw("p same");

        scaled_cent[4] -> SetMarkerStyle(28);
        scaled_cent[4] -> SetMarkerColor(kViolet);
        scaled_cent[4] -> SetLineColor(kViolet);
        scaled_cent[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.4, 0.6, 0.8, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#pi^{0} in |#eta|<1", "h");
        
        leg1 -> AddEntry(scaled_mb, "inelastic events(MB)", "p");
        leg1 -> AddEntry(scaled_cent[0], "centrality: 0~10%", "p");
        leg1 -> AddEntry(scaled_cent[1], "centrality: 10~20%", "p");
        leg1 -> AddEntry(scaled_cent[2], "centrality: 20~40%", "p");
        leg1 -> AddEntry(scaled_cent[3], "centrality: 40~60%", "p");
        leg1 -> AddEntry(scaled_cent[4], "centrality: 60~80%", "p");

        leg1 -> Draw();

    }

}
