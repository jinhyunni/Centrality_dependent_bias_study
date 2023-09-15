void plotMake_dNdpT_MCcompare()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dNdpT_ver2ver3MC_compare.root", "read");
    
    TH1D *pion0_ver2 = (TH1D*)input1 -> Get("h1pT_pion0_ver2R");
    TH1D *pion0_ver3 = (TH1D*)input1 -> Get("h1pT_pion0_ver3R");
    TH1D *pion0_ver3_test = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_test");

    TH1D *dir_ver2 = (TH1D*)input1 -> Get("h1pT_dir_ver2R");
    TH1D *dir_ver3 = (TH1D*)input1 -> Get("h1pT_dir_ver3R");
    TH1D *dir_ver3_test = (TH1D*)input1 -> Get("h1pT_dir_ver3R_test");
    

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLogy(1);
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.000000001, 15, 1e4);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("1/N_{event} dN^{#pi^{0}, #gamma^{dir}}/dp_{T}");

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


        dir_ver2 -> SetMarkerStyle(25);
        dir_ver2 -> SetMarkerColor(kBlue);
        dir_ver2 -> SetLineColor(kBlue);
        dir_ver2 -> Draw("p same");
        
        dir_ver3 -> SetMarkerStyle(34);
        dir_ver3 -> SetMarkerColor(kBlue+4);
        dir_ver3 -> SetLineColor(kBlue+4);
        dir_ver3 -> Draw("p same");

        dir_ver3_test -> SetMarkerStyle(20);
        dir_ver3_test -> SetMarkerColor(kCyan+2);
        dir_ver3_test -> SetLineColor(kCyan+2);
        dir_ver3_test -> Draw("p same");

        TLegend *leg1 = new TLegend(0.5, 0.53, 0.8, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry("", "MB events", "h");
        leg1 -> AddEntry(pion0_ver2, "#pi^{0}, ver2. MC sets", "p");
        leg1 -> AddEntry(pion0_ver3, "#pi^{0}, ver3. MC sets", "p");
        leg1 -> AddEntry(pion0_ver3_test,"#pi^{0}, ve3. test MC sets", "p");
        leg1 -> AddEntry(dir_ver2, "#gamma^{dir}, ver2.  MC sets", "p");
        leg1 -> AddEntry(dir_ver3, "#gamma^{dir}, ver3.  MC sets", "p");
        leg1 -> AddEntry(dir_ver3_test, "#gamma^{dir}, ver3. test MC sets", "p");
        leg1 -> Draw();


    }

}
