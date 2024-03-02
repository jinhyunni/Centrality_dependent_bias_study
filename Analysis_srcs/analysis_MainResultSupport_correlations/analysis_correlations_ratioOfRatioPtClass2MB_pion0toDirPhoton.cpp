#include "../headerFiles/configurable.h"


void analysis_correlations_ratioOfRatioPtClass2MB_pion0toDirPhoton()
{
	//input
	//-----
	TFile *input_pion0 = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidPion0.root", "read");
	TFile *input_dir   = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidDirPhoton.root", "read");
	
	TH1D *ratio_pion0_correlated_charge[pTBinNum];
	TH1D *ratio_dirPhoton_correlated_charge[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{
		ratio_pion0_correlated_charge[pT] = (TH1D*)input_pion0 -> Get(Form("charge_etaRatio_pT%dtoMB", pT+1));
		ratio_dirPhoton_correlated_charge[pT] = (TH1D*)input_dir -> Get(Form("charge_etaRatio_pT%dtoMB", pT+1));
	}

	//Analysis1. Take ratio
	//---------------------
	TH1D *ratio_chargeEta_pion0toDir[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{	
		ratio_chargeEta_pion0toDir[pT] = (TH1D*)ratio_pion0_correlated_charge[pT] -> Clone(Form("ratio_chargeEtaRatio_pi0toDir_pTClass%d", pT+1));
		ratio_chargeEta_pion0toDir[pT] -> Divide(ratio_dirPhoton_correlated_charge[pT]);
	}
	
	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioOfRatioPtClass2MB_pion0toDirPhoton.root", "recreate");
	outfile -> cd();

	for(int pT=0; pT<pTBinNum; pT++)
	{	
		ratio_chargeEta_pion0toDir[pT] -> Write();
	}
	outfile -> Close();

}

