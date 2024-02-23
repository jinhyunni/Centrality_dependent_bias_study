#include "../headerFiles/configurable_correlations.h"

void analysis_correlations_withPion0_charge_ratioOfCentClass()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303_ver2_option3_correlations_withPion0_charge_bypTClass_byCentClass.root", "read");

	TH1D *charge_corWithPion0[pTClass_edge][centClass_edge];
	for(int pT=0; pT<pTClass_edge; pT++)
	{
		for(int cent=0; cent<centClass_edge; cent++)
		{
			TString inputName = Form("charge_eta_corWithPion0_pTClass%d_centClass%d_scaled", pT+1, cent+1);
			charge_corWithPion0[pT][cent] = (TH1D*)input -> Get(inputName);
		}
	}

	//Analysis1. Take ratio
	//---------------------
	
	int ratioClass = centClass_edge - 1;

	TH1D *charge_ratioBetweenCent[pTClass_edge][ratioClass];
	TH1D *charge_etaOfCent1;

	for(int pT=0; pT<pTClass_edge; pT++)
	{		
		charge_etaOfCent1 = charge_corWithPion0[pT][0];

		for(int ratio=0; ratio<ratioClass; ratio++)
		{
			TString outputname = Form("charge_etaRatio_pTClass%d_Cent1toCent%d", pT+1, ratio+2);
			int centClass = ratio+1;

			charge_ratioBetweenCent[pT][ratio] = (TH1D*)charge_corWithPion0[pT][centClass] -> Clone(outputname);
			charge_ratioBetweenCent[pT][ratio] -> Divide(charge_etaOfCent1);
		}
	}

	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_withPion0_charge_ratioOfCentClass.root", "recreate");
	outfile -> cd();
	for(int pT=0; pT<pTClass_edge; pT++)
	{
		for(int cent=0; cent<centClass_edge-1; cent++)
		{
			charge_ratioBetweenCent[pT][cent] -> Write();
		}
	}
	outfile -> Close();

}

