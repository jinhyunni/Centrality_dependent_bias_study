#include "../headerFiles/configurable.h"

void analysis_correlations_charge_bypTClass_withMidPion0()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withPion0_TH3DpTetaMidPion0pT_charge.root", "read");
		
	TH3D *charge_correlated = (TH3D*)input1 -> Get("charge_correlated_midPion0");
	TH2D *numEvent_midPion0pT = (TH2D*)input1 -> Get("numEvent_midPion0pT");

    //Analysis1. Get Particle eta dist. by pTClass and centClass
	//Rebin for eta -> binwidth 0.1 -> 0.5
    //----------------------------------------------------------
    TH1D *charge_bypTClass_corWithPion0_ofpTClass[pTBinNum][pTBinNum];
	TH1D *charge_bypTClass_corWithPion0_ofpTClass_etaRebinned[pTBinNum][pTBinNum];

	double widthFactor = charge_correlated -> GetYaxis() -> GetBinWidth(1);
	
	cout << charge_correlated -> GetNbinsY() << endl;
	cout << charge_correlated -> GetNbinsZ() << endl;

    for(int pi0pT=0; pi0pT< pTBinNum; pi0pT++)
    {  
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			TString outputname1 = Form("chargeEta_ofpTClass%d_corWithPion0_ofpTClas%d", chpT+1, pi0pT+1);
			TString outputname2 = Form("chargeEta_ofpTClass%d_corWithPion0_ofpTClas%d_etaRebinned", chpT+1, pi0pT+1);
			
			int pTcut_start_ch = (int)(pTBin[chpT]*1./widthFactor)+1;
			int pTcut_finish_ch = (int)(pTBin[chpT+1]*1./widthFactor);
			int pTcut_start_pi0 = (int)(pTBin[pi0pT]*1./widthFactor)+1;
			int pTcut_finish_pi0 = (int)(pTBin[pi0pT+1]*1./widthFactor);

			cout << "pTcut_start_ch: " <<pTcut_start_ch << endl;
			cout << "pTcut_finish_ch: " <<pTcut_finish_ch << endl;
			cout << "pTcut_start_pi0: " <<pTcut_start_pi0 << endl;
			cout << "pTcut_finish_pi0: " <<pTcut_finish_pi0 << endl;
			cout << "" << endl;

			charge_bypTClass_corWithPion0_ofpTClass[pi0pT][chpT] = (TH1D*)charge_correlated -> ProjectionX(outputname1, pTcut_start_ch, pTcut_finish_ch, pTcut_start_pi0, pTcut_finish_pi0);
			charge_bypTClass_corWithPion0_ofpTClass_etaRebinned[pi0pT][chpT] = (TH1D*)charge_bypTClass_corWithPion0_ofpTClass[pi0pT][chpT] -> Rebin(etaBinNum, outputname2, etaBin);

		}
		cout << "**pTClass " << pi0pT+1 << " analyze finished**" << endl;
    }
	

	//Analysis2. Scale Event number & eta binwidth
	//--------------------------------------------
	TH1D *charge_bypTClass_corWithPion0_ofpTClass_scaled[pTBinNum][pTBinNum];

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		int pTcut_start_pi0 = (int)(pTBin[pi0pT]*1./widthFactor)+1;
		int pTcut_finish_pi0 = (int)(pTBin[pi0pT+1]*1./widthFactor);

		TH1D *numEvent_pTClass = (TH1D*)numEvent_midPion0pT -> ProjectionY(Form("pTClass%d", pi0pT+1), pTcut_start_pi0, pTcut_finish_pi0);
		double numEvent = numEvent_pTClass -> Integral();

		cout << "# of event of pi0 in pTClass" << pi0pT+1 << ": " << numEvent << endl;
		
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			TString outputname1 = Form("chargeEta_ofpTClass%d_corWithPion0_ofpTClass%d_scaled", chpT+1, pi0pT+1);
		
			charge_bypTClass_corWithPion0_ofpTClass_scaled[pi0pT][chpT] = (TH1D*)charge_bypTClass_corWithPion0_ofpTClass_etaRebinned[pi0pT][chpT] -> Clone(outputname1);
			charge_bypTClass_corWithPion0_ofpTClass_scaled[pi0pT][chpT] -> Scale(1./numEvent);
			charge_bypTClass_corWithPion0_ofpTClass_scaled[pi0pT][chpT] -> Scale(1./charge_bypTClass_corWithPion0_ofpTClass_scaled[pi0pT][chpT] -> GetBinWidth(1));
		}
	}

       
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_bypTClass_withPion0_ofpTClass.root", "recreate");

	output -> cd();

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
   	{
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			charge_bypTClass_corWithPion0_ofpTClass_scaled[pi0pT][chpT] -> Write();
		}
   	}

    output -> Close();

}
