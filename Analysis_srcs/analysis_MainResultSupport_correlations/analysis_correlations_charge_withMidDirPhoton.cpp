#include "../headerFiles/configurable.h"

void analysis_correlations_charge_withMidDirPhoton()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withDirPhoton_TH3DpTetaCent_charge.root", "read");
    
	TH3D *ncollCent_pTClass = (TH3D*)input1 -> Get("ncollCent_pTClass");
	TH1D *nEvent_pTClass = (TH1D*)ncollCent_pTClass -> ProjectionZ("nEvent_pTClass");

    TH3D *charge_corWithDirPhoton[pTBinNum];
    for(int pT=0; pT<pTBinNum; pT++)
    {
        TString inputname = Form("charge_corWithMidDirPhoton_ofpTClass%d", pT+1);
        charge_corWithDirPhoton[pT] = (TH3D*)input1 -> Get(inputname);
    }


    //Analysis1. Get Particle eta dist. by pTClass and centClass
	//Rebin for eta -> binwidth 0.1 -> 0.5
    //----------------------------------------------------------
    TH1D *charge_corWithDirPhoton_ofpTClass[pTBinNum];
	TH1D *charge_corWithDirPhoton_ofpTClass_etaRebinned[pTBinNum];

	//Not rebinned
    for(int pT=0; pT< pTBinNum; pT++)
    {  
		TString outputname1 = Form("charge_eta_corWithDirPhoton_ofpTClass%d", pT+1);
		TString outputname2 = Form("charge_eta_corWithDirPhoton_ofpTClass%d_etaRebinned", pT+1);

		charge_corWithDirPhoton_ofpTClass[pT] = (TH1D*)charge_corWithDirPhoton[pT] -> ProjectionX(outputname1, 1, 2000, 1, 110);
		charge_corWithDirPhoton_ofpTClass_etaRebinned[pT] = (TH1D*)charge_corWithDirPhoton_ofpTClass[pT] -> Rebin(etaBinNum, outputname2, etaBin);
			
		cout << "**pTClass " << pT+1 << " analyze finished**\n" << endl;
    }
	

	//Analysis2. Scale Event number
	//-----------------------------
	TH1D *charge_corWithDirPhoton_ofpTClass_scaled[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname1 = Form("charge_eta_corWithDirPhoton_ofpTClass%d_scaled", pT+1);
		
		charge_corWithDirPhoton_ofpTClass_scaled[pT] = (TH1D*)charge_corWithDirPhoton_ofpTClass_etaRebinned[pT] -> Clone(outputname1);
		charge_corWithDirPhoton_ofpTClass_scaled[pT] -> Scale(1./nEvent_pTClass -> GetBinContent(pT+1));
		charge_corWithDirPhoton_ofpTClass_scaled[pT] -> Scale(1./charge_corWithDirPhoton_ofpTClass_scaled[pT] -> GetBinWidth(1));
	}

       
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withDirPhoton_ofpTClass.root", "recreate");

	output -> cd();

    for(int pT=0; pT<pTBinNum; pT++)
	{
		charge_corWithDirPhoton_ofpTClass[pT] -> Write();
    }

	for(int pT=0; pT<pTBinNum; pT++)
	{
		charge_corWithDirPhoton_ofpTClass_scaled[pT] -> Write();
	}

    output -> Close();

}
