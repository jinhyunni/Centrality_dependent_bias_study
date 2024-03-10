#include "../headerFiles/configurable.h"

void plotMake_correlations_avgNcollBypTClass()
{
    TFile *input_corrWithPion0 = new TFile("../pre_processed/pAu200GeV_p8303_ver5_option3_correlations_withPion0_TProfileNcollMaxpT.root", "read");
    TFile *input_corrWithDirPhoton = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_correlations_withDirPhoton_TProfileNcollMaxpT.root", "read");

	TProfile *avgNcoll_vs_maxpT_pion0 = (TProfile*)input_corrWithPion0 -> Get("maxpT_vs_avgNcoll_corrWithMidPion0");
	TProfile *avgNcoll_vs_maxpT_dirPhoton = (TProfile*)input_corrWithDirPhoton -> Get("maxpT_vs_avgNcoll_corrWithMidDirPhoton");

	//rebinning pTClass
	TProfile *avgNcoll_vs_maxpT_pion0_rebinned = (TProfile*)avgNcoll_vs_maxpT_pion0 -> Rebin(pTBinNum, "avgNcoll_vs_maxpT_pion0", pTBin);
	TProfile *avgNcoll_vs_maxpT_dirPhoton_rebinned = (TProfile*)avgNcoll_vs_maxpT_dirPhoton -> Rebin(pTBinNum, "avgNcoll_vs_maxpT_dirPhoton", pTBin);

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 5.8, 20, 6.8);

        htmp -> GetXaxis() -> SetTitle("max p_{T}");
        htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT");

        avgNcoll_vs_maxpT_pion0_rebinned -> SetMarkerStyle(34);
        avgNcoll_vs_maxpT_pion0_rebinned -> SetMarkerColor(kMagenta);
        avgNcoll_vs_maxpT_pion0_rebinned -> SetLineColor(kMagenta);
        avgNcoll_vs_maxpT_pion0_rebinned -> Draw("p same");

        avgNcoll_vs_maxpT_dirPhoton_rebinned -> SetMarkerStyle(28);
        avgNcoll_vs_maxpT_dirPhoton_rebinned -> SetMarkerColor(kBlue);
        avgNcoll_vs_maxpT_dirPhoton_rebinned -> SetLineColor(kBlue);
        avgNcoll_vs_maxpT_dirPhoton_rebinned -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(avgNcoll_vs_maxpT_pion0_rebinned, "Events with #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(avgNcoll_vs_maxpT_dirPhoton_rebinned, "Events with #gamma^{dir} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
