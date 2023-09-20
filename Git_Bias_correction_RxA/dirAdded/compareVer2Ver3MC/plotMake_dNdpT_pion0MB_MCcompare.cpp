void plotMake_dNdpT_pion0MB_MCcompare()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dNdpT_ver2ver3MC_compare.root", "read");
    
    TH1D *pion0_ver2 = (TH1D*)input1 -> Get("h1pT_pion0_ver2R");
    TH1D *pion0_ver3 = (TH1D*)input1 -> Get("h1pT_pion0_ver3R");
    TH1D *pion0_ver3_test = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_test");
    TH1D *pion0_ver3_nplRootOnly = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_nplRootOnly");
    TH1D *pion0_ver3_kiaf8303 = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_p8303");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLogy(1);
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);
        
        //All pT spectrum
        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.0000001, 15, 1e4);
        //High pT
        //TH1D *htmp = (TH1D*)gPad -> DrawFrame(8, 0.0000001, 15, 0.001);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("1/N_{event} dN^{#pi^{0}}/dp_{T}");
        
        //pion0
        pion0_ver2 -> SetMarkerStyle(25);
        pion0_ver2 -> SetMarkerColor(kRed);
        pion0_ver2 -> SetLineColor(kRed);
        pion0_ver2 -> Draw("p same");
        
        pion0_ver3 -> SetMarkerStyle(47);
        pion0_ver3 -> SetMarkerColor(kOrange);
        pion0_ver3 -> SetLineColor(kOrange);
        pion0_ver3 -> Draw("p same");

        pion0_ver3_test -> SetMarkerStyle(24);
        pion0_ver3_test -> SetMarkerColor(kMagenta);
        pion0_ver3_test -> SetLineColor(kMagenta);
        pion0_ver3_test -> Draw("p same");
    
        pion0_ver3_nplRootOnly -> SetMarkerStyle(32);
        pion0_ver3_nplRootOnly -> SetMarkerColor(kMagenta+2);
        pion0_ver3_nplRootOnly -> SetLineColor(kMagenta+2);
        pion0_ver3_nplRootOnly -> Draw("p same");
    
        pion0_ver3_kiaf8303 -> SetMarkerStyle(30);
        pion0_ver3_kiaf8303 -> SetMarkerColor(kBlue);
        pion0_ver3_kiaf8303 -> SetLineColor(kBlue);
        pion0_ver3_kiaf8303 -> Draw("p same");

       
        TLegend *leg1 = new TLegend(0.3, 0.53, 0.6, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry("", "MB events", "h");

        leg1 -> AddEntry(pion0_ver2, "#pi^{0}, ver2, pythia8303 in NPL, external package O", "p");
        leg1 -> AddEntry(pion0_ver3, "#pi^{0}, ver3, pythia8307 in KIAF", "p");
        leg1 -> AddEntry(pion0_ver3_test,"#pi^{0}, ver3, pythia8303 in NPL, external package O", "p");
        leg1 -> AddEntry(pion0_ver3_nplRootOnly,"#pi^{0}, ver3, pythia8303 in NPL, root Only", "p");
        leg1 -> AddEntry(pion0_ver3_kiaf8303,"#pi^{0}, ver3, pythia8303 in KIAF, root Only", "p");
               
        leg1 -> Draw();
    }

}
