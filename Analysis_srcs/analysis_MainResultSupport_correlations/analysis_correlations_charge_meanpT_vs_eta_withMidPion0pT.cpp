#include "../headerFiles/configurable.h"

void analysis_correlations_charge_meanpT_vs_eta_withMidPion0pT()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withPion0_TH3DpTetaMidPion0pT_charge.root", "read");
		
	TH3D *charge_correlated = (TH3D*)input1 -> Get("charge_correlated_midPion0");
	TH2D *numEvent_midPion0pT = (TH2D*)input1 -> Get("numEvent_midPion0pT");

    //Analysis1. Get Particle eta dist. by pTClass and centClass
	//Rebin for eta -> binwidth 0.1 -> 0.5
    //----------------------------------------------------------
	TH3D *pT_vs_eta_vs_midPion0pT_charge[pTBinNum];
	TH2D *pT_vs_eta_charge[pTBinNum];
	TProfile *meanpT_vs_eta_charge[pTBinNum];

	double widthFactor = charge_correlated -> GetYaxis() -> GetBinWidth(1);

    for(int pi0pT=0; pi0pT< pTBinNum; pi0pT++)
    {
		pT_vs_eta_vs_midPion0pT_charge[pi0pT] = (TH3D*)charge_correlated -> Clone(Form("TH3D_correlated_withMidPion0pTClass%d", pi0pT+1));
		pT_vs_eta_vs_midPion0pT_charge[pi0pT] -> GetZaxis() -> SetRange((int)(pTBin[pi0pT]*1./widthFactor)+1, (int)(pTBin[pi0pT+1]*1./widthFactor));	//Set mid-pion0 pTClass
		pT_vs_eta_vs_midPion0pT_charge[pi0pT] -> GetYaxis() -> SetRange(21, 200);	//Set charge's pTCut: only high pT

		pT_vs_eta_charge[pi0pT] = (TH2D*)pT_vs_eta_vs_midPion0pT_charge[pi0pT] -> Project3D("yx");

		meanpT_vs_eta_charge[pi0pT] = (TProfile*)pT_vs_eta_charge[pi0pT] -> ProfileX(Form("meanpT_vs_eta_charge_withMidPion0pTClass%d", pi0pT+1));
	}
	
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_meanpT_vs_eta_withPion0_ofpTClass.root", "recreate");

	output -> cd();

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		meanpT_vs_eta_charge[pi0pT] -> Write(); 
   	}

    output -> Close();

}
