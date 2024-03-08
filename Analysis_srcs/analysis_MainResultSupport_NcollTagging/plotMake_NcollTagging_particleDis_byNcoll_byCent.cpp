#include "../headerFiles/configurable.h"

#define NcollClass 6
#define NCOLLPLOT 2

void plotMake_NcollTagging_particleDis_byNcoll_byCent()
{
    TFile *input_charge = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_charge_byNcoll_byCent.root", "read");
    TFile *input_pion0 = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_pion0_byNcoll_byCent.root", "read");
    TFile *input_dirPhoton = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_dirPhoton_byNcoll_byCent.root", "read");

	TH2D *charge_pTeta[NcollClass][centBinNum];
	TH2D *pion0_pTeta[NcollClass][centBinNum];
	TH2D *dirPhoton_pTeta[NcollClass][centBinNum];

	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		for(int cent=0; cent<centBinNum; cent++)
		{
			charge_pTeta[ncoll][cent] = (TH2D*)input_charge -> Get(Form("pTeta_charge_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
			pion0_pTeta[ncoll][cent] = (TH2D*)input_pion0 -> Get(Form("pTeta_pion0_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
			dirPhoton_pTeta[ncoll][cent] = (TH2D*)input_dirPhoton -> Get(Form("pTeta_dirPhoton_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
		}
	}

    TCanvas *c1 = new TCanvas("", "", 1500, 1000);
	c1 -> Divide(5, 3);
	gStyle -> SetOptStat(0);
	gStyle -> SetOptTitle(0);

	TString ncollClassInfo[NcollClass];
	TString centClassInfo[centBinNum];

	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		ncollClassInfo[ncoll] = Form("%d #leq Ncoll #LT %d", 5*ncoll, 5*(ncoll+1));
	}

	for(int cent=0; cent<centBinNum; cent++)
	{
		centClassInfo[cent] = Form("centrality: %d%%~%d%%", (int)centBin[cent], (int)centBin[cent+1]);
	}

	//Drawing plots
	for(int cent=0; cent<centBinNum; cent++)
	{
		//charged particle
		{
			c1 -> cd(cent+1);

			gPad -> SetTicks();
			gPad -> SetLeftMargin(0.12);
			gPad -> SetRightMargin(0.12);
			gPad -> SetTopMargin(0.05);
			gPad -> SetBottomMargin(0.12);

			TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 20);

			htmp -> GetXaxis() -> SetTitle("#eta");
			htmp -> GetYaxis() -> SetTitle("p_{T}");
			
			charge_pTeta[NCOLLPLOT][cent] -> Draw("colz");

			TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
			leg1 -> SetFillStyle(0);
			leg1 -> SetBorderSize(0);
			leg1 -> SetTextSize(0.03);
			leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
			
			leg1 -> AddEntry("", ncollClassInfo[NCOLLPLOT], "h");
			leg1 -> AddEntry("", centClassInfo[cent], "h");
			leg1 -> AddEntry("", "#pi^{#pm}, k^{pm}, p^{pm}", "h");

			leg1 -> Draw();
		}
		
		//pion0
		{
			c1 -> cd(cent+1+5);

			gPad -> SetTicks();
			gPad -> SetLeftMargin(0.12);
			gPad -> SetRightMargin(0.12);
			gPad -> SetTopMargin(0.05);
			gPad -> SetBottomMargin(0.12);

			TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 20);

			htmp -> GetXaxis() -> SetTitle("#eta");
			htmp -> GetYaxis() -> SetTitle("p_{T}");
			
			pion0_pTeta[NCOLLPLOT][cent] -> Draw("colz");

			TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
			leg1 -> SetFillStyle(0);
			leg1 -> SetBorderSize(0);
			leg1 -> SetTextSize(0.03);
			leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
			
			leg1 -> AddEntry("", ncollClassInfo[NCOLLPLOT], "h");
			leg1 -> AddEntry("", centClassInfo[cent], "h");
			leg1 -> AddEntry("", "#pi^{0}", "h");

			leg1 -> Draw();
		}
		
		//dirPhoton
		{
			c1 -> cd(cent+1+5+5);

			gPad -> SetTicks();
			gPad -> SetLeftMargin(0.12);
			gPad -> SetRightMargin(0.12);
			gPad -> SetTopMargin(0.05);
			gPad -> SetBottomMargin(0.12);

			TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 20);

			htmp -> GetXaxis() -> SetTitle("#eta");
			htmp -> GetYaxis() -> SetTitle("p_{T}");
			
			dirPhoton_pTeta[NCOLLPLOT][cent] -> Draw("colz");

			TLegend *leg1 = new TLegend(0.15, 0.7, 0.51, 0.9);
			leg1 -> SetFillStyle(0);
			leg1 -> SetBorderSize(0);
			leg1 -> SetTextSize(0.03);
			leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
			
			leg1 -> AddEntry("", ncollClassInfo[NCOLLPLOT], "h");
			leg1 -> AddEntry("", centClassInfo[cent], "h");
			leg1 -> AddEntry("", "#gamma^{dir}", "h");

			leg1 -> Draw();
		}

	}//end canvas loop

}
