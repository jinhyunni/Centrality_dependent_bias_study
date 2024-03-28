#include "../headerFiles/configurable.h"

void plotMake_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver5_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton.root", "read");

    TH1D *BBCs_chpTsum_1 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass1");
    TH1D *BBCs_chpTsum_2 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass2");
    TH1D *BBCs_chpTsum_3 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass3");
    TH1D *BBCs_chpTsum_4 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass4");
    TH1D *BBCs_chpTsum_5 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass5");
    TH1D *BBCs_chpTsum_6 = (TH1D*)input1 -> Get("BBCspTsum_midDirPhotonpTClass6");

	TH1D *BBCs_chpTsum_origin[6];
	TH1D *BBCs_chpTsum_rebin[6];
	for(int dirpT=0; dirpT<pTBinNum; dirpT++)
	{
		BBCs_chpTsum_origin[dirpT] = (TH1D*)input1 -> Get(Form("BBCspTsum_midDirPhotonpTClass%d", dirpT+1));
		BBCs_chpTsum_rebin[dirpT]=(TH1D*)BBCs_chpTsum_origin[dirpT] -> Rebin(pTsumBinNum, Form("BBCspTsum_midPion0pTClass%d_rebinned", dirpT+1), pTsumBin);
	}

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);
		

        //TH1D *htmp = (TH1D*)gPad -> DrawFrame(1e-5, 0, 15, 0.05);
        //TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 15, 0.05);
        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 15, 0.2);

        htmp -> GetXaxis() -> SetTitle("#sum p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("");

        BBCs_chpTsum_rebin[0] -> SetMarkerStyle(25);
        BBCs_chpTsum_rebin[0] -> SetMarkerColor(kViolet-1);
        BBCs_chpTsum_rebin[0] -> SetLineColor(kViolet-1);
        BBCs_chpTsum_rebin[0] -> Draw("p same");

		BBCs_chpTsum_rebin[1] -> SetMarkerStyle(34);
        BBCs_chpTsum_rebin[1] -> SetMarkerColor(kGreen+1);
        BBCs_chpTsum_rebin[1] -> SetLineColor(kGreen+1);
        BBCs_chpTsum_rebin[1] -> Draw("p same");

        BBCs_chpTsum_rebin[2] -> SetMarkerStyle(34);
        BBCs_chpTsum_rebin[2] -> SetMarkerColor(kTeal+1);
        BBCs_chpTsum_rebin[2] -> SetLineColor(kTeal+1);
        BBCs_chpTsum_rebin[2] -> Draw("p same");

        BBCs_chpTsum_rebin[3] -> SetMarkerStyle(28);
        BBCs_chpTsum_rebin[3] -> SetMarkerColor(kCyan+1);
        BBCs_chpTsum_rebin[3] -> SetLineColor(kCyan+1);
        BBCs_chpTsum_rebin[3] -> Draw("p same");
    
        BBCs_chpTsum_rebin[4] -> SetMarkerStyle(47);
        BBCs_chpTsum_rebin[4] -> SetMarkerColor(kAzure);
        BBCs_chpTsum_rebin[4] -> SetLineColor(kAzure);
        BBCs_chpTsum_rebin[4] -> Draw("p same");

		BBCs_chpTsum_rebin[5] -> SetMarkerStyle(25);
        BBCs_chpTsum_rebin[5] -> SetMarkerColor(kBlue+1);
        BBCs_chpTsum_rebin[5] -> SetLineColor(kBlue+1);
        BBCs_chpTsum_rebin[5] -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(BBCs_chpTsum_rebin[0], "Events with p_{T} #LT 2 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum_rebin[1], "Events with 2 GeV #leq p_{T} #LT 4 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum_rebin[2], "Events with 4 GeV #leq p_{T} #LT 7 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum_rebin[3], "Events with 7 GeV #leq p_{T} #LT 10 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum_rebin[4], "Events with 10 GeV #leq p_{T} #LT 15 GeV #gamma^{dir} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum_rebin[5], "Events with 15 GeV #leq p_{T} #LT 20 GeV #gamma^{dir} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
