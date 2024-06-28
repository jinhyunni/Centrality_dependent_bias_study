#include "../headerFiles/configurable.h"

#define NCOLLCLASSNUM 6		// Fixed ToTal # of class, when we divide events by Ncoll of interval 55
#define NCOLLCLASS 0		// Seleceted Ncoll class of event
#define CENT 4				// Selected centrality of event

void plotMake_NcollTagging_particleDis_byNcoll_byCent_frameByFrame()
{
    TFile *input_charge = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_charge_byNcoll_byCent.root", "read");
    TFile *input_pion0 = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_pion0_byNcoll_byCent.root", "read");
    TFile *input_dirPhoton = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_dirPhoton_byNcoll_byCent.root", "read");

	TH2D *charge_pTeta[NCOLLCLASSNUM][centBinNum];
	TH2D *pion0_pTeta[NCOLLCLASSNUM][centBinNum];
	TH2D *dirPhoton_pTeta[NCOLLCLASSNUM][centBinNum];

	for(int ncoll=0; ncoll<NCOLLCLASSNUM; ncoll++)
	{
		for(int cent=0; cent<centBinNum; cent++)
		{
			charge_pTeta[ncoll][cent] = (TH2D*)input_charge -> Get(Form("pTeta_charge_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
			pion0_pTeta[ncoll][cent] = (TH2D*)input_pion0 -> Get(Form("pTeta_pion0_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
			dirPhoton_pTeta[ncoll][cent] = (TH2D*)input_dirPhoton -> Get(Form("pTeta_dirPhoton_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
		}
	}

    TCanvas *c1 = new TCanvas("", "", 2000, 800);
	c1 -> Divide(2, 1);
	gStyle -> SetOptStat(0);
	gStyle -> SetOptTitle(0);

	TString ncollClassInfo[NCOLLCLASSNUM];
	TString centClassInfo[centBinNum];

	for(int ncoll=0; ncoll<NCOLLCLASSNUM; ncoll++)
	{
		ncollClassInfo[ncoll] = Form("%d #leq Ncoll #LT %d", 5*ncoll, 5*(ncoll+1));
	}

	for(int cent=0; cent<centBinNum; cent++)
	{
		centClassInfo[cent] = Form("centrality: %d%%~%d%%", (int)centBin[cent], (int)centBin[cent+1]);
	}

	//Histogram Drawing

	{
		c1 -> cd(1);
		
		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.15);
		gPad -> SetLogz();

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 30);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("p_{T}");
		htmp -> GetYaxis() -> SetTitleOffset(1.3020833333333333);
		
		charge_pTeta[NCOLLCLASS][0] -> Draw("p same colz");

		TLegend *leg1 = new TLegend(0.18, 0.71, 0.54, 0.91);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("", "PYTHIA8 with Angantyr option3", "h");
		leg1 -> AddEntry("", "p+Au 200GeV", "h");
		leg1 -> AddEntry("", ncollClassInfo[NCOLLCLASS], "h");
		leg1 -> AddEntry("", centClassInfo[0], "h");
		leg1 -> AddEntry("", "#pi^{#pm}, k^{#pm}, p^{#pm}", "h");

		leg1 -> Draw();

		TLegend *leg2 = new TLegend(0.76, 0.79, 0.96, 0.99);
		leg2 -> SetFillStyle(0);
		leg2 -> SetBorderSize(0);
		leg2 -> SetTextSize(0.04);
		leg2 -> AddEntry("", "(a)", "h");
		leg2 -> Draw();
	}

	{
		c1 -> cd(2);
		
		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.15);
		gPad -> SetLogz();

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 30);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("p_{T}");
		htmp -> GetYaxis() -> SetTitleOffset(1.3020833333333333);
		
		charge_pTeta[NCOLLCLASS][4] -> Draw("p same colz");

		TLegend *leg1 = new TLegend(0.18, 0.71, 0.54, 0.91);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("", "PYTHIA8 with Angantyr option3", "h");
		leg1 -> AddEntry("", "p+Au 200GeV", "h");
		leg1 -> AddEntry("", ncollClassInfo[NCOLLCLASS], "h");
		leg1 -> AddEntry("", centClassInfo[4], "h");
		leg1 -> AddEntry("", "#pi^{#pm}, k^{#pm}, p^{#pm}", "h");

		leg1 -> Draw();

		TLegend *leg2 = new TLegend(0.76, 0.79, 0.96, 0.99);
		leg2 -> SetFillStyle(0);
		leg2 -> SetBorderSize(0);
		leg2 -> SetTextSize(0.04);
		leg2 -> AddEntry("", "(b)", "h");
		leg2 -> Draw();
	}

	

}
