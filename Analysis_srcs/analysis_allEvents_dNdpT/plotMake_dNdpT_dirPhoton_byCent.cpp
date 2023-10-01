void plotMake_dNdpT_dirPhoton_byCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");

    TH1D *dNdpT_dir_cent1 = (TH1D*)input1 -> Get("dNdpT_dir_cent1");
    TH1D *dNdpT_dir_cent2 = (TH1D*)input1 -> Get("dNdpT_dir_cent2");
    TH1D *dNdpT_dir_cent3 = (TH1D*)input1 -> Get("dNdpT_dir_cent3");
    TH1D *dNdpT_dir_cent4 = (TH1D*)input1 -> Get("dNdpT_dir_cent4");
    TH1D *dNdpT_dir_cent5 = (TH1D*)input1 -> Get("dNdpT_dir_cent5");

    TH1D *dNdpT_dir_MB = (TH1D*)input2 -> Get("dNdpt_dir_mb");

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

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.0000000001, 20, 0.01);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{event}} #frac{dN^{#gamma^{dir}}}{dp_{T}}");

        dNdpT_dir_MB -> SetMarkerStyle(29);
        dNdpT_dir_MB -> SetMarkerColor(1);
        dNdpT_dir_MB -> SetLineColor(1);
        dNdpT_dir_MB -> Draw("p same");
    
        dNdpT_dir_cent1 -> SetMarkerStyle(34);
        dNdpT_dir_cent1 -> SetMarkerColor(kGreen+1);
        dNdpT_dir_cent1 -> SetLineColor(kGreen+1);
        dNdpT_dir_cent1 -> Draw("p same");

        dNdpT_dir_cent2 -> SetMarkerStyle(34);
        dNdpT_dir_cent2 -> SetMarkerColor(kTeal+1);
        dNdpT_dir_cent2 -> SetLineColor(kTeal+1);
        dNdpT_dir_cent2 -> Draw("p same");

        dNdpT_dir_cent3 -> SetMarkerStyle(28);
        dNdpT_dir_cent3 -> SetMarkerColor(kCyan+1);
        dNdpT_dir_cent3 -> SetLineColor(kCyan+1);
        dNdpT_dir_cent3 -> Draw("p same");
    
        dNdpT_dir_cent4 -> SetMarkerStyle(47);
        dNdpT_dir_cent4 -> SetMarkerColor(kAzure);
        dNdpT_dir_cent4 -> SetLineColor(kAzure);
        dNdpT_dir_cent4 -> Draw("p same");

        dNdpT_dir_cent5 -> SetMarkerStyle(28);
        dNdpT_dir_cent5 -> SetMarkerColor(kBlue);
        dNdpT_dir_cent5 -> SetLineColor(kBlue);
        dNdpT_dir_cent5 -> Draw("p same");


        TLegend *leg1 = new TLegend(0.4, 0.65, 0.8, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#gamma^{dir} in |#eta|<1", "h");

        leg1 -> AddEntry(dNdpT_dir_MB, "all inelastic events(MB)", "p");
        leg1 -> AddEntry(dNdpT_dir_cent1, "centrality: 0~10%", "p");
        leg1 -> AddEntry(dNdpT_dir_cent2, "centrality: 10~20%", "p");
        leg1 -> AddEntry(dNdpT_dir_cent3, "centrality: 20~40%", "p");
        leg1 -> AddEntry(dNdpT_dir_cent4, "centrality: 40~60%", "p");
        leg1 -> AddEntry(dNdpT_dir_cent5, "centrality: 60~80%", "p");

        leg1 -> Draw();

    }

}
