void plotMake_ratio_avgncollcent_target2all()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver4_option3_ratio_avgncollcent_target2all.root", "read");

    TH1D *target2all[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("target2all_midpion0_over%dGeV", 2*i+3);
        target2all[i] = (TH1D*)input1 -> Get(inputname);
    }
    
    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.9, 80, 1.6);

        htmp -> GetXaxis() -> SetTitle("centrality(%)");
        htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT_{target} / #LTN_{coll}#GT_{allEvents}");
        
        target2all[0] -> SetMarkerStyle(34);
        target2all[0]-> SetMarkerColor(kOrange);
        target2all[0] -> SetLineColor(kOrange);
        target2all[0] -> Draw("p same");

        target2all[1] -> SetMarkerStyle(34);
        target2all[1] -> SetMarkerColor(kRed);
        target2all[1] -> SetLineColor(kRed);
        target2all[1] -> Draw("p same");

        target2all[2] -> SetMarkerStyle(28);
        target2all[2] -> SetMarkerColor(kPink);
        target2all[2] -> SetLineColor(kPink);
        target2all[2] -> Draw("p same");
    
        target2all[3] -> SetMarkerStyle(47);
        target2all[3] -> SetMarkerColor(kMagenta);
        target2all[3] -> SetLineColor(kMagenta);
        target2all[3] -> Draw("p same");

        target2all[4] -> SetMarkerStyle(28);
        target2all[4] -> SetMarkerColor(kViolet);
        target2all[4] -> SetLineColor(kViolet);
        target2all[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.4, 0.65, 0.8, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(target2all[0], "Target: events with #pi^{0} > 3 GeV in |#eta|<1", "p");
        leg1 -> AddEntry(target2all[1], "Target: events with #pi^{0} > 5 GeV in |#eta|<1", "p");
        leg1 -> AddEntry(target2all[2], "Target: events with #pi^{0} > 7 GeV in |#eta|<1", "p");
        leg1 -> AddEntry(target2all[3], "Target: events with #pi^{0} > 9 GeV in |#eta|<1", "p");
        leg1 -> AddEntry(target2all[4], "Target: events with #pi^{0} > 11 GeV in |#eta|<1", "p");

        leg1 -> Draw();

    }

}
