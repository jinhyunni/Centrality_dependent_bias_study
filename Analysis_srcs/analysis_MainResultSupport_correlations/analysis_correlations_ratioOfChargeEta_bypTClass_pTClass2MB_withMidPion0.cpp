#include "../headerFiles/configurable.h"


void analysis_correlations_ratioOfChargeEta_bypTClass_pTClass2MB_withMidPion0()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_bypTClass_withPion0_ofpTClass.root", "read");
	
	TFile *input_mb_charge = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH2DpTetaCharge_MBevents.root", "read");
	TFile *input_mb_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");

	TH1D *charge_corWithPion0[pTBinNum][pTBinNum];
	TH1D *charge_corWithPion0_etaRebinned[pTBinNum][pTBinNum];

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			charge_corWithPion0[pi0pT][chpT] = (TH1D*)input -> Get(Form("chargeEta_ofpTClass%d_corWithPion0_ofpTClass%d_scaled", chpT+1, pi0pT+1));
		}
	}
	
	TH2D *charge_MB = (TH2D*)input_mb_charge -> Get("pTetaCharge_MBevents");
	TH2D *NeventCent_MB = (TH2D*)input_mb_ncoll -> Get("ncollCent");
	
	cout << "Input complete" << endl;

	//Analysis0. Get charge-eta distribution of MB events
	//---------------------------------------------------
	TH1D *charge_MB_bypTClass[pTBinNum];
	TH1D *charge_MB_bypTClass_etaRebinned[pTBinNum];
	double widthFactor = charge_MB -> GetYaxis() -> GetBinWidth(1);

	for(int chpT=0; chpT<pTBinNum; chpT++)
	{
		charge_MB_bypTClass[chpT] = (TH1D*)charge_MB -> ProjectionX(Form("chargeEta_ofpTClass%d_MB", chpT+1), (int)(pTBin[chpT]*1./widthFactor)+1, (int)(pTBin[chpT+1]*1./widthFactor));
		cout << (int)(pTBin[chpT]*1./widthFactor)+1 << endl;
		cout << (int)(pTBin[chpT+1]*1./widthFactor) << endl;

		charge_MB_bypTClass_etaRebinned[chpT] = (TH1D*)charge_MB_bypTClass[chpT] -> Rebin(etaBinNum, Form("chargeEta_ofpTClass%d_MB_etaRebinned", chpT+1), etaBin);
	}
	
	cout << "charge collection by pTClass completed" << endl;

	//Res
	TH1D *Nevent_cent = (TH1D*)NeventCent_MB -> ProjectionX("Nevent_cent");	
	TH1D *Nevent_MB = (TH1D*)Nevent_cent -> Rebin(centBin_MergedNum, "TotalNevent", centBin_Merged);

	for(int chpT=0; chpT<pTBinNum; chpT++)
	{
		charge_MB_bypTClass_etaRebinned[chpT] -> Scale(1./Nevent_MB -> GetBinContent(1));
		charge_MB_bypTClass_etaRebinned[chpT] -> Scale(1./charge_MB_bypTClass_etaRebinned[chpT] -> GetBinWidth(1));
	}
	
	cout << "MB eta ratio completed" << endl;

	//Analysis1. Take ratio
	//---------------------
	TH1D *charge_ratiopTMB[pTBinNum][pTBinNum];

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{	
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			charge_ratiopTMB[pi0pT][chpT] = (TH1D*)charge_corWithPion0[pi0pT][chpT] -> Clone(Form("charge_ofpTClass%d_etaRatio_pT%dtoMB", chpT+1, pi0pT+1));
			charge_ratiopTMB[pi0pT][chpT] -> Divide(charge_MB_bypTClass_etaRebinned[chpT]);
		}
	}
	
	cout << "Analysis 1 completed" << endl;

	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_bypTClass_pTClass2MB_withMidPion0.root", "recreate");
	outfile -> cd();
	
	for(int chpT=0; chpT<pTBinNum; chpT++)
	{
		charge_MB_bypTClass_etaRebinned[chpT] -> Write();
	}

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{	
		for(int chpT=0; chpT<pTBinNum; chpT++)
		{
			charge_ratiopTMB[pi0pT][chpT] -> Write();
		}
	}
	outfile -> Close();

}

