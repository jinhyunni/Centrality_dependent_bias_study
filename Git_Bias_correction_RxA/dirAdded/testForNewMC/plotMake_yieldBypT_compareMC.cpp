void plotMake_yieldBypT_compareMC()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdpT_gammaApion0_testForNewMC_MBevents.root", "read");
    TFile *input2 = new TFile("/Users/jinhyunpark/npl/gitHub/git_share/Git_Bias_correction_RxA/dirAdded/gammaPion0Analysis/pAu200GeV_option3_dirAdded_decayOn_gammaApion0_MBevents.root", "read");
    
    TH1D *new_pion0_MB = (TH1D*)input1 -> Get("dndpt_pion0_mb");
    TH1D *old_pion0_MB = (TH1D*)input2 -> Get("dndpt_pion0_mb");
    TH1D *new_dir_MB = (TH1D*)input1 -> Get("dndpt_dir_mb");
    TH1D *old_dir_MB = (TH1D*)input2 -> Get("dndpt_dir_mb");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLogy(1);
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.000000001, 14, 1000);

        htmp -> GetXaxis() -> SetTitle("p_{T}");
        htmp -> GetYaxis() -> SetTitle("1/N_{event} dN^{#pi^{0}, #gamma^{dir}}/dp_{T}");

        new_pion0_MB -> SetMarkerStyle(22);
        new_pion0_MB -> SetMarkerColor(1);
        new_pion0_MB -> SetLineColor(1);
        new_pion0_MB -> Draw("p same");
        
        old_pion0_MB -> SetMarkerStyle(25);
        old_pion0_MB -> SetMarkerColor(1);
        old_pion0_MB -> SetLineColor(1);
        old_pion0_MB -> Draw("p same");

        new_dir_MB -> SetMarkerStyle(23);
        new_dir_MB -> SetMarkerColor(2);
        new_dir_MB -> SetLineColor(2);
        new_dir_MB -> Draw("p same");
        
        old_dir_MB -> SetMarkerStyle(25);
        old_dir_MB -> SetMarkerColor(2);
        old_dir_MB -> SetLineColor(2);
        old_dir_MB -> Draw("p same");

        TLegend *leg1 = new TLegend(0.5, 0.53, 0.8, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV, |#eta|<1", "h");
        leg1 -> AddEntry("", "MB events", "h");
        leg1 -> AddEntry(new_pion0_MB, "#pi^{0}, New MC sets", "p");
        leg1 -> AddEntry(old_pion0_MB, "#pi^{0}, Old MC sets", "p");
        leg1 -> AddEntry(new_dir_MB, "#gamma^{dir}, New MC sets", "p");
        leg1 -> AddEntry(old_dir_MB, "#gamma^{dir}, New MC sets", "p");
        leg1 -> Draw();


    }

}
