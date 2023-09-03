void plotMake_directPhoton()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_PIDcheck_testForNewMC.root", "read");

    TH2D *dirPhoton = (TH2D*)input1 -> Get("directPhoton_check");

    gStyle -> SetOptStat(0);
    gStyle -> SetPalette("colz");
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetBottomMargin(0.05);
        gPad -> SetTopMargin(0.12);

        TH2D *htmp = (TH2D*)gPad -> DrawFrame(15, 0, 25, 10000);

        htmp -> GetXaxis() -> SetTitle("p_mom_id");
        htmp -> GetYaxis() -> SetTitle("p_gmom_id");

        dirPhoton -> SetMarkerStyle(20);
        dirPhoton -> SetMarkerColor(1);
        dirPhoton -> SetLineColor(1);
        dirPhoton -> Draw("p same");

    }
    


}
