#include "../headerFiles/configurable.h"

void analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton()
{
	//Input
	//=====
	TFile *input = new TFile("../pre_processed/pAu200GeV_p8303_ver5_option3_correlations_withDirPhoton_BBCsMultiplicity_chargepTsum.root", "read");
	TH2D *BBCspTsum_vs_maxDirPhotonpT = (TH2D*)input -> Get("BBCsMultiplicity_charge_corrMidDirPhotonpT");

	//Anlaysis 1. Get BBCs pTsum distribution by mid-pion0 pTsum and scale
	//====================================================================
	TH1D *BBCspTsum_midDirPhotonpTsum[pTBinNum];
	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		double binwidth = BBCspTsum_vs_maxDirPhotonpT -> GetYaxis() -> GetBinWidth(1);
		int binNum_cutStart = (int)(pTBin[pi0pT]*1./binwidth)+1;
		int binNum_cutFinish = (int)(pTBin[pi0pT+1]*1./binwidth);

		cout << "Cut Start Bin: " << binNum_cutStart << endl;
		cout << "Cut Finish Bin: " << binNum_cutFinish << endl;
		cout << "***************" << endl;

		BBCspTsum_midDirPhotonpTsum[pi0pT] = (TH1D*)BBCspTsum_vs_maxDirPhotonpT -> ProjectionX(Form("BBCspTsum_midDirPhotonpTClass%d", pi0pT+1), binNum_cutStart, binNum_cutFinish);
		BBCspTsum_midDirPhotonpTsum[pi0pT] -> Scale(1./BBCspTsum_midDirPhotonpTsum[pi0pT] -> Integral());
	}

	//Analysis done.
	//==============
	TFile *output = new TFile("pAu200GeV_p8303_ver5_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton.root", "recreate");
	output -> cd();
	for(int i=0; i<pTBinNum; i++)	BBCspTsum_midDirPhotonpTsum[i] -> Write();
	output -> Close();
}
