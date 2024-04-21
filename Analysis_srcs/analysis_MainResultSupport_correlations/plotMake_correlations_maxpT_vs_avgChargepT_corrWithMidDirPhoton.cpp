#include "../headerFiles/configurable.h"

void plotMake_correlations_maxpT_vs_avgChargepT_corrWithMidDirPhoton()
{
    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_correlations_withDirPhoton_TProfileNcollMaxpT.root", "read");
	
	TProfile *maxpT_vs_avgpT = (TProfile*)input -> Get("maxpT_vs_avgNcoll_corrWithMidDirPhoton");

	TProfile *maxpT_vs_avgpT_rebinned = (TProfile*)maxpT_vs_avgpT -> Rebin(pTBinNum, "maxpT_vs_avgpT_rebinned", pTBin);

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 20, 10);

        htmp -> GetXaxis() -> SetTitle("Max pion0's pT");
        htmp -> GetYaxis() -> SetTitle("#LTp^{ch}_T#GT");

        maxpT_vs_avgpT_rebinned -> SetMarkerStyle(21);
        maxpT_vs_avgpT_rebinned -> SetMarkerColor(1);
        maxpT_vs_avgpT_rebinned -> SetLineColor(1);
        maxpT_vs_avgpT_rebinned -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
 //*        leg1 -> AddEntry(BBCs_chpTsum[0], "Events with p_{T} #LT 2 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[1], "Events with 2 GeV #leq p_{T} #LT 4 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[2], "Events with 4 GeV #leq p_{T} #LT 7 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[3], "Events with 7 GeV #leq p_{T} #LT 10 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[4], "Events with 10 GeV #leq p_{T} #LT 15 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[5], "Events with 15 GeV #leq p_{T} #LT 20 GeV #pi^{0} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
