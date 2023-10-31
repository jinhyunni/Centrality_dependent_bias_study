void plotMake_dNdpT_highpT_pion0_byCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver4_option3_dNdpT_allEvents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver4_option3_dNdpT_MBevents.root", "read");

    TH1D *dNdpT_pion0_cent1 = (TH1D*)input1 -> Get("dNdpT_pion0_cent1");
    TH1D *dNdpT_pion0_cent2 = (TH1D*)input1 -> Get("dNdpT_pion0_cent2");
    TH1D *dNdpT_pion0_cent3 = (TH1D*)input1 -> Get("dNdpT_pion0_cent3");
    TH1D *dNdpT_pion0_cent4 = (TH1D*)input1 -> Get("dNdpT_pion0_cent4");
    TH1D *dNdpT_pion0_cent5 = (TH1D*)input1 -> Get("dNdpT_pion0_cent5");

    TH1D *dNdpT_pion0_MB = (TH1D*)input2 -> Get("dNdpt_pion0_mb");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        gPad -> SetLogy();

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 0.000000005, 20, 1e-1);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}}");

        dNdpT_pion0_MB -> SetMarkerStyle(34);
        dNdpT_pion0_MB -> SetMarkerColor(1);
        dNdpT_pion0_MB -> SetLineColor(1);
        dNdpT_pion0_MB -> Draw("p same");
    
        dNdpT_pion0_cent1 -> SetMarkerStyle(34);
        dNdpT_pion0_cent1 -> SetMarkerColor(kOrange);
        dNdpT_pion0_cent1 -> SetLineColor(kOrange);
        dNdpT_pion0_cent1 -> Draw("p same");

        dNdpT_pion0_cent2 -> SetMarkerStyle(34);
        dNdpT_pion0_cent2 -> SetMarkerColor(kRed);
        dNdpT_pion0_cent2 -> SetLineColor(kRed);
        dNdpT_pion0_cent2 -> Draw("p same");

        dNdpT_pion0_cent3 -> SetMarkerStyle(28);
        dNdpT_pion0_cent3 -> SetMarkerColor(kPink);
        dNdpT_pion0_cent3 -> SetLineColor(kPink);
        dNdpT_pion0_cent3 -> Draw("p same");
    
        dNdpT_pion0_cent4 -> SetMarkerStyle(47);
        dNdpT_pion0_cent4 -> SetMarkerColor(kMagenta);
        dNdpT_pion0_cent4 -> SetLineColor(kMagenta);
        dNdpT_pion0_cent4 -> Draw("p same");

        dNdpT_pion0_cent5 -> SetMarkerStyle(28);
        dNdpT_pion0_cent5 -> SetMarkerColor(kViolet);
        dNdpT_pion0_cent5 -> SetLineColor(kViolet);
        dNdpT_pion0_cent5 -> Draw("p same");


        TLegend *leg1 = new TLegend(0.31, 0.6, 0.71, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#pi^{0} in |#eta|<1", "h");
        
        leg1 -> AddEntry(dNdpT_pion0_MB, "all inelastic(MB)", "p");
        leg1 -> AddEntry(dNdpT_pion0_cent1, "cent: 0~10%", "p");
        leg1 -> AddEntry(dNdpT_pion0_cent2, "cent: 10~20%", "p");
        leg1 -> AddEntry(dNdpT_pion0_cent3, "cent: 20~40%", "p");
        leg1 -> AddEntry(dNdpT_pion0_cent4, "cent: 40~60%", "p");
        leg1 -> AddEntry(dNdpT_pion0_cent5, "cent: 60~80%", "p");

        leg1 -> Draw();

    }

}
