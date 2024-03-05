#include "../headerFiles/configurable.h"


void analysis_correlations_ratioOfChargeEta_pTClass2MB_withMidPion0()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withPion0_ofpTClass.root", "read");
	
	TFile *input_mb_charge = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH2DpTetaCharge_MBevents.root", "read");
	TFile *input_mb_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");

	TH1D *charge_corWithPion0[pTBinNum];
	TH1D *charge_corWithPion0_etaRebinned[pTBinNum];

	TH2D *charge_MB = (TH2D*)input_mb_charge -> Get("pTetaCharge_MBevents");
	TH2D *NeventCent_MB = (TH2D*)input_mb_ncoll -> Get("ncollCent");

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString inputName = Form("charge_eta_corWithPion0_ofpTClass%d_scaled", pT+1);
		charge_corWithPion0[pT] = (TH1D*)input -> Get(inputName);
	}
	
	
	//Analysis0. Get charge-eta distribution of MB events
	//---------------------------------------------------
	TH1D *charge_eta_MB = (TH1D*)charge_MB -> ProjectionX("charge_eta_MB");
	TH1D *charge_eta_MB_etaRebinned = (TH1D*)charge_eta_MB -> Rebin(etaBinNum, "charge_eta_MB_etaRebin", etaBin);

	TH1D *Nevent_cent = (TH1D*)NeventCent_MB -> ProjectionX("Nevent_cent");
	TH1D *Nevent_MB = (TH1D*)Nevent_cent -> Rebin(centBin_MergedNum, "TotalNevent", centBin_Merged);

	//Res
	charge_eta_MB_etaRebinned -> Scale(1./Nevent_MB -> GetBinContent(1));
	charge_eta_MB_etaRebinned -> Scale(1./charge_eta_MB_etaRebinned -> GetBinWidth(1));

	//Analysis1. Take ratio
	//---------------------
	TH1D *charge_ratiopTMB[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{	
		TString outputname1 = Form("charge_etaRatio_pT%dtoMB", pT+1);

		charge_ratiopTMB[pT] = (TH1D*)charge_corWithPion0[pT] -> Clone(outputname1);
		charge_ratiopTMB[pT] -> Divide(charge_eta_MB_etaRebinned);
	}
	
	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_pTClass2MB_withMidPion0.root", "recreate");
	outfile -> cd();
	
	charge_eta_MB_etaRebinned -> Write();

	for(int pT=0; pT<pTBinNum; pT++)
	{	
		charge_ratiopTMB[pT] -> Write();
	}
	outfile -> Close();

}

