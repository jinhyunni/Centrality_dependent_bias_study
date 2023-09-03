void plotMake_centCheck()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_centCheck_testForNewMC.root", "read");
    
    TH2D *h2ncollCent = (TH2D*)input1 -> Get("ncollCent");
    TH1D *h1eventCent = (TH1D*)h2ncollCent -> ProjectionX();
    

    h1eventCent -> SetBinContent(10, h1eventCent->GetBinContent(10) + h1eventCent -> GetBinContent(11));  


    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 100, 1e7);

        htmp -> GetXaxis() -> SetTitle("centrality(%)");
        htmp -> GetYaxis() -> SetTitle("# of events");

        h1eventCent -> SetMarkerStyle(20);
        h1eventCent -> SetMarkerColor(1);
        h1eventCent -> SetLineColor(1);
        h1eventCent -> Draw("p same");

        TLegend *leg1 = new TLegend(0.4, 0.65, 0.65, 0.93);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.04);
        leg1 -> AddEntry("", "PYTHIA8, option3", "h");
        leg1 -> AddEntry("", "p+Au, 200 GeV", "h");
        leg1 -> AddEntry("", "Cent categotization of new MC test", "h");
        leg1 -> Draw();


    }

}
