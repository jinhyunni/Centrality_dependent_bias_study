#include "../headerFiles/configurable.h"

void analysis_correlations_charge_withMidPion0()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withPion0_TH3DpTetaMidPion0pT_charge.root", "read");
		
	TH3D *charge_correlated = (TH3D*)input1 -> Get("charge_correlated_midPion0");
	TH2D *numEvent_midPion0pT = (TH2D*)input1 -> Get("numEvent_midPion0pT");

    //Analysis1. Get Particle eta dist. by pTClass and centClass
	//Rebin for eta -> binwidth 0.1 -> 0.5
    //----------------------------------------------------------
    TH1D *charge_corWithPion0_ofpTClass[pTBinNum];
	TH1D *charge_corWithPion0_ofpTClass_etaRebinned[pTBinNum];

	double widthFactor = charge_correlated -> GetYaxis() -> GetBinWidth(1);

	//Not rebinned
    for(int pT=0; pT< pTBinNum; pT++)
    {  
		TString outputname1 = Form("charge_eta_corWithPion0_ofpTClass%d", pT+1);
		TString outputname2 = Form("charge_eta_corWithPion0_ofpTClass%d_etaRebinned", pT+1);

		//charge_corWithPion0_ofpTClass[pT] = (TH1D*)charge_corWithPion0[pT] -> ProjectionX(outputname1, 1, 2000, 1, 110);
		charge_corWithPion0_ofpTClass[pT] = (TH1D*)charge_correlated -> ProjectionX(outputname1, 1, 200, (int)(pTBin[pT]*1./widthFactor)+1, (int)(pTBin[pT+1]*1./widthFactor));
		charge_corWithPion0_ofpTClass_etaRebinned[pT] = (TH1D*)charge_corWithPion0_ofpTClass[pT] -> Rebin(etaBinNum, outputname2, etaBin);
			
		cout << "**pTClass " << pT+1 << " analyze finished**" << endl;
    }
	

	//Analysis2. Scale Event number & eta binwidth
	//-----------------------------
	TH1D *charge_corWithPion0_ofpTClass_scaled[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TH1D *numEvent_pTClass = (TH1D*)numEvent_midPion0pT -> ProjectionY(Form("pTClass%d", pT+1), (int)(pTBin[pT]*1./widthFactor)+1, (int)(pTBin[pT+1]*1./widthFactor));
		double numEvent = numEvent_pTClass -> Integral();

		TString outputname1 = Form("charge_eta_corWithPion0_ofpTClass%d_scaled", pT+1);
		
		charge_corWithPion0_ofpTClass_scaled[pT] = (TH1D*)charge_corWithPion0_ofpTClass_etaRebinned[pT] -> Clone(outputname1);
		charge_corWithPion0_ofpTClass_scaled[pT] -> Scale(1./numEvent);
		charge_corWithPion0_ofpTClass_scaled[pT] -> Scale(1./charge_corWithPion0_ofpTClass_scaled[pT] -> GetBinWidth(1));
	}

       
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withPion0_ofpTClass.root", "recreate");

	output -> cd();

    for(int pT=0; pT<pTBinNum; pT++)
	{
		charge_corWithPion0_ofpTClass[pT] -> Write();
    }

	for(int pT=0; pT<pTBinNum; pT++)
	{
		charge_corWithPion0_ofpTClass_scaled[pT] -> Write();
	}

    output -> Close();

}
