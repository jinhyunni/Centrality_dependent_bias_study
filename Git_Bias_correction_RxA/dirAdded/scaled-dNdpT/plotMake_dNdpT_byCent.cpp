void plotMake_dNdpT_byCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");

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
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        gPad -> SetLogy();

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.000000005, 20, 100);

        htmp -> GetXaxis() -> SetTitle("p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}}");

        dNdpT_pion0_MB -> SetMarkerStyle(34);
        dNdpT_pion0_MB -> SetMarkerColor(kPink+7);
        dNdpT_pion0_MB -> SetLineColor(kPink+7);
        dNdpT_pion0_MB -> Draw("p same");
    
        dNdpT_pion0_cent1 -> SetMarkerStyle(34);
        dNdpT_pion0_cent1 -> SetMarkerColor(kRed);
        dNdpT_pion0_cent1 -> SetLineColor(kRed);
        dNdpT_pion0_cent1 -> Draw("p same");

        dNdpT_pion0_cent2 -> SetMarkerStyle(34);
        dNdpT_pion0_cent2 -> SetMarkerColor(kRed+1);
        dNdpT_pion0_cent2 -> SetLineColor(kRed+1);
        dNdpT_pion0_cent2 -> Draw("p same");

        dNdpT_pion0_cent3 -> SetMarkerStyle(34);
        dNdpT_pion0_cent3 -> SetMarkerColor(kRed+2);
        dNdpT_pion0_cent3 -> SetLineColor(kRed+2);
        dNdpT_pion0_cent3 -> Draw("p same");
    
        dNdpT_pion0_cent4 -> SetMarkerStyle(34);
        dNdpT_pion0_cent4 -> SetMarkerColor(kRed+3);
        dNdpT_pion0_cent4 -> SetLineColor(kRed+3);
        dNdpT_pion0_cent4 -> Draw("p same");

        dNdpT_pion0_cent5 -> SetMarkerStyle(34);
        dNdpT_pion0_cent5 -> SetMarkerColor(kRed+4);
        dNdpT_pion0_cent5 -> SetLineColor(kRed+4);
        dNdpT_pion0_cent5 -> Draw("p same");


        TLegend *leg1 = new TLegend(0.4, 0.65, 0.8, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", "#pi^{0} in |#eta|<1", "h");

        leg1 -> Draw();

    }

}
