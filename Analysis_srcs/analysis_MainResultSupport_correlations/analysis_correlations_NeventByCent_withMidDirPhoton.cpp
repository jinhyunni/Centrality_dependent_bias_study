#include "../headerFiles/configurable.h"

void analysis_correlations_NeventByCent_withMidDirPhoton()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withDirPhoton_TH3DpTetaCent_charge.root", "read");
	TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_NcollCent.root", "read");
    
	TH2D *ncollCent_MB = (TH2D*)input2 -> Get("ncollCent");
	TH3D *ncollCent_pTClass = (TH3D*)input1 -> Get("ncollCent_pTClass");

    //Analysis1. Get Event # by centrality,  by pTClass
    //-------------------------------------------------
    TH1D *Nevent_corWithMidDirPhoton_ofpTClass[pTBinNum];
	TH1D *Nevent_MB = (TH1D*)ncollCent_MB -> ProjectionX("Nevent_MB");

    for(int pT=0; pT< pTBinNum; pT++)
    {  
		TString outputname  = Form("NeventByCent_corWithMidDirPhoton_ofpTClass%d", pT+1);
		Nevent_corWithMidDirPhoton_ofpTClass[pT] = (TH1D*)ncollCent_pTClass -> ProjectionX(outputname, 1, 110, pT+1, pT+1);
			
		cout << "**pTClass " << pT+1 << " analyze finished**\n" << endl;
    }// pT loop finished


	//Analysis2. Rebin centrality class
	//---------------------------------
	TH1D *Nevent_corWithMidDirPhoton_ofpTClass_scaled[pTBinNum];

	//# of events by centrality in MB events
	TH1D *Nevent_MB_cent = (TH1D*)Nevent_MB -> Rebin(centBinNum, "# of event, cent class rebinned", centBin);
	Nevent_MB_cent -> Scale(1./Nevent_MB_cent -> Integral());

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname= Form("NeventByCent_corWithMidDirPhoton_ofpTClass%d_scaled", pT+1);
		
		//Total Event # scaling
		Nevent_corWithMidDirPhoton_ofpTClass_scaled[pT] = (TH1D*)Nevent_corWithMidDirPhoton_ofpTClass[pT] -> Rebin(centBinNum, outputname, centBin);
		Nevent_corWithMidDirPhoton_ofpTClass_scaled[pT] -> Scale(1./Nevent_corWithMidDirPhoton_ofpTClass_scaled[pT] -> Integral());	
	}
	
	//Analysis3. Get ratio of # event - pTClass to MB
	//-----------------------------------------------

	TH1D *Nevent_ratio_pTClass2MB[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString output = Form("Nevent_ratio_pTClass%dtoMB", pT+1);

		Nevent_ratio_pTClass2MB[pT] = (TH1D*)Nevent_corWithMidDirPhoton_ofpTClass_scaled[pT] -> Clone(output);
		Nevent_ratio_pTClass2MB[pT] -> Divide(Nevent_MB_cent);
	}

       
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_correlations_NeventByCent_withDirPhoton_ofpTClass.root", "recreate");

	output -> cd();


	for(int pT=0; pT<pTBinNum; pT++)
	{
		Nevent_ratio_pTClass2MB[pT] -> Write();
	}

    output -> Close();

}
