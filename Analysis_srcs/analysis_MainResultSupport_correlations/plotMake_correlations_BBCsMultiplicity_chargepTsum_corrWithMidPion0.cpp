#include "../headerFiles/configurable.h"

void plotMake_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0()
{
	TFile *input_MBevents = new TFile("pAu200GeV_p8303_ver2_option3_BBCsMultiplicity_chargepTsum_MBevents.root");
    TFile *input_ver5 = new TFile("pAu200GeV_p8303_ver5_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0.root", "read");
    TFile *input_ver2 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0.root", "read");

	TH1D *BBCs_chpTsum_MB = (TH1D*)input_MBevents -> Get("BBCsMultiplicity_chargepTsum_rebinned");
	BBCs_chpTsum_MB -> Scale(1./10);

	TH1D *BBCs_chpTsum[6];
	
	BBCs_chpTsum[0] = (TH1D*)input_ver2 -> Get("BBCspTsum_midPion0pTClass1_rebinned");

	for(int pi0pT=1; pi0pT<pTBinNum; pi0pT++)
	{
		BBCs_chpTsum[pi0pT] = (TH1D*)input_ver5 -> Get(Form("BBCspTsum_midPion0pTClass%d_rebinned", pi0pT+1));
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
        //TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 1e-8, 10, 1e10);
        TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0, 10, 0.2);

        htmp -> GetXaxis() -> SetTitle("#sum p_{T}(GeV/c)");
        htmp -> GetYaxis() -> SetTitle("");

        BBCs_chpTsum[0] -> SetMarkerStyle(21);
        BBCs_chpTsum[0] -> SetMarkerColor(1);
        BBCs_chpTsum[0] -> SetLineColor(1);
        BBCs_chpTsum[0] -> Draw("p same");

 //*		BBCs_chpTsum_MB -> SetMarkerStyle(21);
 //*        BBCs_chpTsum_MB -> SetMarkerColor(1);
 //*        BBCs_chpTsum_MB -> SetLineColor(1);
 //*        BBCs_chpTsum_MB -> Draw("p same");

		BBCs_chpTsum[1] -> SetMarkerStyle(34);
        BBCs_chpTsum[1] -> SetMarkerColor(kOrange);
        BBCs_chpTsum[1] -> SetLineColor(kOrange);
        BBCs_chpTsum[1] -> Draw("p same");

        BBCs_chpTsum[2] -> SetMarkerStyle(34);
        BBCs_chpTsum[2] -> SetMarkerColor(kRed);
        BBCs_chpTsum[2] -> SetLineColor(kRed);
        BBCs_chpTsum[2] -> Draw("p same");

        BBCs_chpTsum[3] -> SetMarkerStyle(28);
        BBCs_chpTsum[3] -> SetMarkerColor(kPink);
        BBCs_chpTsum[3] -> SetLineColor(kPink);
        BBCs_chpTsum[3] -> Draw("p same");
    
        BBCs_chpTsum[4] -> SetMarkerStyle(47);
        BBCs_chpTsum[4] -> SetMarkerColor(kMagenta);
        BBCs_chpTsum[4] -> SetLineColor(kMagenta);
        BBCs_chpTsum[4] -> Draw("p same");

		BBCs_chpTsum[5] -> SetMarkerStyle(25);
        BBCs_chpTsum[5] -> SetMarkerColor(kViolet);
        BBCs_chpTsum[5] -> SetLineColor(kViolet);
        BBCs_chpTsum[5] -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        
        leg1 -> AddEntry(BBCs_chpTsum[0], "Events with p_{T} #LT 2 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum[1], "Events with 2 GeV #leq p_{T} #LT 4 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum[2], "Events with 4 GeV #leq p_{T} #LT 7 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum[3], "Events with 7 GeV #leq p_{T} #LT 10 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum[4], "Events with 10 GeV #leq p_{T} #LT 15 GeV #pi^{0} at |#eta|<1", "p");
        leg1 -> AddEntry(BBCs_chpTsum[5], "Events with 15 GeV #leq p_{T} #LT 20 GeV #pi^{0} at |#eta|<1", "p");

        leg1 -> Draw();

    }

}
