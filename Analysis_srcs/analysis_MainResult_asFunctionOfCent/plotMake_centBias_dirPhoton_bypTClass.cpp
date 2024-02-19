void plotMake_centBias_dirPhoton_bypTClass()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_centBias_centBiasRatio_pion0toDir.root", "read");

    TH1D *dNdpT_dir_cent1 = (TH1D*)input1 -> Get("dir_centBias_pTClass1");
    TH1D *dNdpT_dir_cent2 = (TH1D*)input1 -> Get("dir_centBias_pTClass2");
    TH1D *dNdpT_dir_cent3 = (TH1D*)input1 -> Get("dir_centBias_pTClass3");
    TH1D *dNdpT_dir_cent4 = (TH1D*)input1 -> Get("dir_centBias_pTClass4");
    TH1D *dNdpT_dir_cent5 = (TH1D*)input1 -> Get("dir_centBias_pTClass5");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.05, 80, 0.18);

        htmp -> GetXaxis() -> SetTitle("centrality(%)");
        htmp -> GetYaxis() -> SetTitle("#gamma^{dir} centrality bias");
           
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


        TLegend *leg1 = new TLegend(0.15, 0.6, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#gamma^{dir} in |#eta|<1", "h");

        leg1 -> AddEntry(dNdpT_dir_cent1, "p_{T}: 2~4 GeV/c", "p");
        leg1 -> AddEntry(dNdpT_dir_cent2, "p_{T}: 4~7 GeV/c", "p");
        leg1 -> AddEntry(dNdpT_dir_cent3, "p_{T}: 7~10 GeV/c", "p");
        leg1 -> AddEntry(dNdpT_dir_cent4, "p_{T}: 10~15 GeV/c", "p");
        leg1 -> AddEntry(dNdpT_dir_cent5, "p_{T}: 15~20 GeV/c", "p");

        leg1 -> Draw();

    }

}
