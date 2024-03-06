#include "../headerFiles/configurable.h"

void plotMake_correlations_withMidPion0_chargeEta_bypTClass_pTClassAndMB()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_bypTClass_pTClass2MB_withMidPion0.root", "read");
	TH1D *ratio[pTBinNum][pTBinNum];
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			ratio[pi0pT][chpT] = (TH1D*)input1 -> Get(Form("charge_ofpTClass%d_etaRatio_pT%dtoMB", chpT+1, pi0pT+1));
		}
	}	

	
	const int charge_pTClass = 4;
	const int uppereEdge[]={3, 80, 1500, 13000};

	TString tagged_event_info[pTBinNum];
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		tagged_event_info[pi0pT] = Form("charge of %d #leq p_{T} #LT %d at mid-rapidity", (int)(pTBin[pi0pT]), (int)(pTBin[pi0pT+1]));
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


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 13000);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");

        ratio[0][charge_pTClass] -> SetMarkerStyle(25);
        ratio[0][charge_pTClass] -> SetMarkerColor(kOrange+10);
        ratio[0][charge_pTClass] -> SetLineColor(kOrange+10);
        ratio[0][charge_pTClass] -> Draw("p same");

		ratio[1][charge_pTClass] -> SetMarkerStyle(34);
        ratio[1][charge_pTClass] -> SetMarkerColor(kOrange);
        ratio[1][charge_pTClass] -> SetLineColor(kOrange);
        ratio[1][charge_pTClass] -> Draw("p same");

        ratio[2][charge_pTClass] -> SetMarkerStyle(28);
        ratio[2][charge_pTClass] -> SetMarkerColor(kPink);
        ratio[2][charge_pTClass] -> SetLineColor(kPink);
        ratio[2][charge_pTClass] -> Draw("p same");
    
        ratio[3][charge_pTClass] -> SetMarkerStyle(37);
        ratio[3][charge_pTClass] -> SetMarkerColor(kMagenta);
        ratio[3][charge_pTClass] -> SetLineColor(kMagenta);
        ratio[3][charge_pTClass] -> Draw("p same");

		ratio[4][charge_pTClass] -> SetMarkerStyle(25);
        ratio[4][charge_pTClass] -> SetMarkerColor(kViolet);
        ratio[4][charge_pTClass] -> SetLineColor(kViolet);
        ratio[4][charge_pTClass] -> Draw("p same");	

		ratio[5][charge_pTClass] -> SetMarkerStyle(25);
        ratio[5][charge_pTClass] -> SetMarkerColor(kViolet);
        ratio[5][charge_pTClass] -> SetLineColor(kViolet);
        ratio[5][charge_pTClass] -> Draw("p same");
		
        TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
        leg1 -> AddEntry("", tagged_event_info[charge_pTClass], "h");
        
        leg1 -> AddEntry(ratio[0][charge_pTClass], "Events with #pi^{0} of 0 GeV/c #leq p_{T} #LT 2 GeV/c", "p");
        leg1 -> AddEntry(ratio[1][charge_pTClass], "Events with #pi^{0} of 2 GeV/c #leq p_{T} #LT 4 GeV/c", "p");
        leg1 -> AddEntry(ratio[2][charge_pTClass], "Events with #pi^{0} of 4 GeV/c #leq p_{T} #LT 7 GeV/c", "p");
        leg1 -> AddEntry(ratio[3][charge_pTClass], "Events with #pi^{0} of 7 GeV/c #leq p_{T} #LT 10 GeV/c", "p");
        leg1 -> AddEntry(ratio[4][charge_pTClass], "Events with #pi^{0} of 10 GeV/c #leq p_{T} #LT 15 GeV/c", "p");
        leg1 -> AddEntry(ratio[5][charge_pTClass], "Events with #pi^{0} of 15 GeV/c #leq p_{T} #LT 20 GeV/c", "p");

        leg1 -> Draw();

    }

}
