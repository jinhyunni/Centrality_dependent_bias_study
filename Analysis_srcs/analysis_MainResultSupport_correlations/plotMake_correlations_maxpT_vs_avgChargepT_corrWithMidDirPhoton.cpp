#include "../headerFiles/configurable.h"

void plotMake_correlations_maxpT_vs_avgChargepT_corrWithMidDirPhoton()
{
    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303_ver5_option3_correlations_withDirPhoton_TProfile_avgpTSumCh_vs_maxpT.root", "read");	
	TProfile *maxpT_vs_avgpT = (TProfile*)input -> Get("maxpT_vs_avgChpT_corrWithMidDirPhoton");

	double bin[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};

	TProfile *maxpT_vs_avgpT_rebinned = (TProfile*)maxpT_vs_avgpT -> Rebin(5, "maxpT_vs_avgpT_rebinned", bin);

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(2, 1, 20, 5);

        htmp -> GetXaxis() -> SetTitle("Max p_{T} of #gamma^{dir} at |#eta|<1 (GeV/c)");
        htmp -> GetYaxis() -> SetTitle("#LT #sump^{ch}_{T} #GT at -3.9 < #eta < -3.0 (GeV/c)");

        maxpT_vs_avgpT_rebinned -> SetMarkerStyle(25);
        maxpT_vs_avgpT_rebinned -> SetMarkerColor(kBlue+1);
        maxpT_vs_avgpT_rebinned -> SetLineColor(kBlue+1);
        maxpT_vs_avgpT_rebinned -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, Angnatyr option 3", "h");
		leg1 -> AddEntry("", "p+Au, #sqrt{s_{NN}} = 200 GeV/c", "h");
        
 //*        leg1 -> AddEntry(BBCs_chpTsum[0], "Events with p_{T} #LT 2 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[1], "Events with 2 GeV #leq p_{T} #LT 4 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[2], "Events with 4 GeV #leq p_{T} #LT 7 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[3], "Events with 7 GeV #leq p_{T} #LT 10 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[4], "Events with 10 GeV #leq p_{T} #LT 15 GeV #pi^{0} at |#eta|<1", "p");
 //*        leg1 -> AddEntry(BBCs_chpTsum[5], "Events with 15 GeV #leq p_{T} #LT 20 GeV #pi^{0} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
