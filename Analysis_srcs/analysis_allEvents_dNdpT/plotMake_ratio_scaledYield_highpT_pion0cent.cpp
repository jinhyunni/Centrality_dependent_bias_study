void plotMake_ratio_scaledYield_highpT_pion0cent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver5_option3_ratio_scaled-dNdpT_highpT.root", "read");

    TH1D *ratio_scaled[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("ratio_scaledYield_pion0cent%d", i+1);

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

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0, 20, 2.5);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("(#frac{1}{#LT N_{coll} #GT} #frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}})_{cent} / (#frac{1}{#LT N_{coll} #GT} #frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}})_{MB} ");
                   
        ratio_scaled[0] -> SetMarkerStyle(34);
        ratio_scaled[0]-> SetMarkerColor(kOrange);
        ratio_scaled[0] -> SetLineColor(kOrange);
        ratio_scaled[0] -> Draw("p same");

        ratio_scaled[1] -> SetMarkerStyle(34);
        ratio_scaled[1] -> SetMarkerColor(kRed);
        ratio_scaled[1] -> SetLineColor(kRed);
        ratio_scaled[1] -> Draw("p same");

        ratio_scaled[2] -> SetMarkerStyle(28);
        ratio_scaled[2] -> SetMarkerColor(kPink);
        ratio_scaled[2] -> SetLineColor(kPink);
        ratio_scaled[2] -> Draw("p same");
    
        ratio_scaled[3] -> SetMarkerStyle(47);
        ratio_scaled[3] -> SetMarkerColor(kMagenta);
        ratio_scaled[3] -> SetLineColor(kMagenta);
        ratio_scaled[3] -> Draw("p same");

        ratio_scaled[4] -> SetMarkerStyle(28);
        ratio_scaled[4] -> SetMarkerColor(kViolet);
        ratio_scaled[4] -> SetLineColor(kViolet);
        ratio_scaled[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.14, 0.6, 0.56, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#pi^{0} in |#eta|<1", "h");

        leg1 -> AddEntry(ratio_scaled[0], "centrality: 0~10%", "p");
        leg1 -> AddEntry(ratio_scaled[1], "centrality: 10~20%", "p");
        leg1 -> AddEntry(ratio_scaled[2], "centrality: 20~40%", "p");
        leg1 -> AddEntry(ratio_scaled[3], "centrality: 40~60%", "p");
        leg1 -> AddEntry(ratio_scaled[4], "centrality: 60~80%", "p");

        leg1 -> Draw();

    }

}
