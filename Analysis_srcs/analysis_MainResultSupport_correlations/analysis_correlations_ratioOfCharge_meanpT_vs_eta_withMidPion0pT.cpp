#include "../headerFiles/configurable.h"

void analysis_correlations_ratioOfCharge_meanpT_vs_eta_withMidPion0pT()
{
    //input
    //-----
    TFile *input_pTClass = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_meanpT_vs_eta_withPion0_ofpTClass.root", "read");
	TFile *input_MB = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH2DpTetaCharge_MBevents.root", "read");
		
	TProfile *meanpT_vs_eta_charge[pTBinNum];
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		meanpT_vs_eta_charge[pi0pT] = (TProfile*)input_pTClass -> Get(Form("meanpT_vs_eta_charge_withMidPion0pTClass%d", pi0pT+1));
	}

    //Analysis1. Get <pT> vs eta, MBevents
    //------------------------------------
	TH2D *pT_vs_eta_charge_MB = (TH2D*)input_MB -> Get("pTetaCharge_MBevents");
	TProfile *meanpT_vs_eta_MB = (TProfile*)pT_vs_eta_charge_MB -> ProfileX("meanpT_vs_eta_MB");

	//Analysis2. Get <pT> vs eta, mid-pion0 pTClass
	//---------------------------------------------
	
	TProfile *ratio_meanpT_vs_eta_pTClass2MB[pTBinNum];
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		ratio_meanpT_vs_eta_pTClass2MB[pi0pT] = (TProfile*)meanpT_vs_eta_charge[pi0pT] -> Clone(Form("ratio_meanpT_vs_eta_pTClass%dtoMB", pi0pT+1));
		ratio_meanpT_vs_eta_pTClass2MB[pi0pT] -> Divide(meanpT_vs_eta_MB);
	}


    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioOfCharge_meanpT_vs_eta_withPion0.root", "recreate");

	output -> cd();

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		ratio_meanpT_vs_eta_pTClass2MB[pi0pT] -> Write(); 
   	}

    output -> Close();

}
