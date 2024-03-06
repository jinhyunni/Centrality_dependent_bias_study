#include "../headerFiles/configurable.h"


void analysis_correlations_ratioOfChargeEta_scaleAvgNcoll_pTClass2MB_withMidDirPhoton()
{
	//input
	//-----
	TFile *input = new TFile("pAu200GeV_p8303_ver2_option3_correlations_charge_withDirPhoton_ofpTClass.root", "read");
	TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withDirPhoton_TProfileNcollMaxpT.root", "read");
	TFile *input_mb_charge = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH2DpTetaCharge_MBevents.root", "read");
	TFile *input_mb_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");

	TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("maxpT_vs_avgNcoll_corrWithMidDirPhoton");

	TH1D *charge_corWithDirPhoton[pTBinNum];
	TH1D *charge_corWithDirPhoton_etaRebinned[pTBinNum];

	TH2D *charge_MB = (TH2D*)input_mb_charge -> Get("pTetaCharge_MBevents");
	TH2D *NeventCent_MB = (TH2D*)input_mb_ncoll -> Get("ncollCent");

	for(int dirPt=0; dirPt<pTBinNum; dirPt++)
	{
		TString inputName = Form("charge_eta_corWithDirPhoton_ofpTClass%d_scaled", dirPt+1);
		charge_corWithDirPhoton[dirPt] = (TH1D*)input -> Get(inputName);
	}
	
	//Analysis0. Get charge-eta distribution of MB events
	//---------------------------------------------------
	TH1D *charge_eta_MB = (TH1D*)charge_MB -> ProjectionX("charge_eta_MB");
	TH1D *charge_eta_MB_etaRebinned = (TH1D*)charge_eta_MB -> Rebin(etaBinNum, "charge_eta_MB_etaRebin", etaBin);

	TH1D *Nevent_cent = (TH1D*)NeventCent_MB -> ProjectionX("Nevent_cent");
	TH1D *Nevent_MB = (TH1D*)Nevent_cent -> Rebin(centBin_MergedNum, "TotalNevent", centBin_Merged);
	
	//scaling-# event, binwidth
	charge_eta_MB_etaRebinned -> Scale(1./Nevent_MB -> GetBinContent(1));
	charge_eta_MB_etaRebinned -> Scale(1./charge_eta_MB_etaRebinned -> GetBinWidth(1));
	
	//avgNcoll calculaiton
	double bin[]={0, 20};
	TProfile *avgNcoll_mb = (TProfile*)avgNcoll -> Rebin(1, "avgNcoll_mb", bin);
	TProfile *avgNcoll_pTClass = (TProfile*)avgNcoll -> Rebin(pTBinNum, "avgNcoll_pTClass", pTBin);

	//Analysis1. calculte <Ncoll> sclaed dNchdeta by pTClass
	//------------------------------------------------------
	TH1D *charge_scaledEta[pTBinNum];
	
	//Events divided by pT-Class
	for(int dirPt=0; dirPt<pTBinNum; dirPt++)
	{	
		TString outputname1 = Form("charge_ncollScaledEta_pTClass%d", dirPt+1);

		charge_scaledEta[dirPt] = (TH1D*)charge_corWithDirPhoton[dirPt] -> Clone(outputname1);
		charge_scaledEta[dirPt] -> Scale(1./avgNcoll_pTClass -> GetBinContent(dirPt+1));
		
		cout << avgNcoll_mb -> GetBinContent(1) << " : " << avgNcoll_pTClass -> GetBinContent(dirPt+1) << " : " << (avgNcoll_mb -> GetBinContent(1))/(avgNcoll_pTClass -> GetBinContent(dirPt+1)) << endl;
	}

	//MB events
	TH1D *charge_eta_MB_NcollScaled = (TH1D*)charge_eta_MB_etaRebinned -> Clone("charge_ncollScaledEta_MB");
	charge_eta_MB_NcollScaled -> Scale(1./avgNcoll_mb -> GetBinContent(1));

	//Analysis2. Calculated ratio of Ncoll scaled charge eta with MB
	//--------------------------------------------------------------
	TH1D *charge_ratiopTMB[pTBinNum];
	
	for(int dirPt=0; dirPt<pTBinNum; dirPt++)
	{
		charge_ratiopTMB[dirPt] = (TH1D*)charge_scaledEta[dirPt] -> Clone(Form("charge_etaRatio_scaleAvgNcoll_pT%dtoMB", dirPt+1));
		charge_ratiopTMB[dirPt] -> Divide(charge_eta_MB_NcollScaled);
	}
	
	//output
	//-----
	TFile *outfile = new TFile("pAu200GeV_p8303_ver2_option3_correlations_ratioChargeEta_scaleAvgNcoll_pTClass2MB_withMidDirPhoton.root", "recreate");
	outfile -> cd();
	
	//MB, NcollScaled
	charge_eta_MB_NcollScaled -> Write();

	//pTClass, NcollSclaed
	for(int dirPt=0; dirPt<pTBinNum; dirPt++)
	{
		charge_scaledEta[dirPt] -> Write();
	}

	// ratio of pTClass 2 MB
	for(int dirPt=0; dirPt<pTBinNum; dirPt++)
	{	
		charge_ratiopTMB[dirPt] -> Write();
	}
	outfile -> Close();

}

