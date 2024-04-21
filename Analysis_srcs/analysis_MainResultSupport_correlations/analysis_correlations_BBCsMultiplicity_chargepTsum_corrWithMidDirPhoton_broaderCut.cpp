#include "../headerFiles/configurable.h"

void analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidDirPhoton_broaderCut(TString version)
{
	//Input
	//=====
	TFile *input = new TFile(Form("../pre_processed/pAu200GeV_p8303_%s_option3_correlations_withDirPhoton_BBCsMultiplicity_chargepTsum.root", version.Data()), "read");
	TH2D *BBCspTsum_vs_maxDirPhotonpT = (TH2D*)input -> Get("BBCsMultiplicity_charge_corrMidDirPhotonpT");

	//Anlaysis 1. Get BBCs pTsum distribution by mid-pion0 pTsum and scale
	//====================================================================
	TObjArray *Hlist_raw = new TObjArray(0);
	TObjArray *Hlist_rebinned = new TObjArray(0);
	TH1D *BBCspTsum_midDirPhotonpTsum[pTBinBroaderNum];
	TH1D *BBCspTsum_midDirPhotonpTsum_rebinned[pTBinBroaderNum];

	for(int dirpT=0; dirpT<pTBinBroaderNum; dirpT++)
	{
 		double binwidth = BBCspTsum_vs_maxDirPhotonpT -> GetYaxis() -> GetBinWidth(1);
		int binNum_cutStart = BBCspTsum_vs_maxDirPhotonpT -> GetYaxis() -> FindBin(pTBinBroader[dirpT]);
		int binNum_cutFinish = BBCspTsum_vs_maxDirPhotonpT -> GetYaxis() -> FindBin(pTBinBroader[dirpT+1] - binwidth);
//*			int binNum_cutStart = (int)(pTBin[pi0pT]*1./binwidth)+1;
 //*		int binNum_cutFinish = (int)(pTBin[pi0pT+1]*1./binwidth);

		cout << "Cut Start Bin: " << binNum_cutStart << endl;
		cout << "Cut Finish Bin: " << binNum_cutFinish << endl;
		cout << "***************" << endl;

		BBCspTsum_midDirPhotonpTsum[dirpT] = (TH1D*)BBCspTsum_vs_maxDirPhotonpT -> ProjectionX(Form("BBCspTsum_midPion0pTClass%d", dirpT+1), binNum_cutStart, binNum_cutFinish);
		BBCspTsum_midDirPhotonpTsum_rebinned[dirpT]=(TH1D*)BBCspTsum_midDirPhotonpTsum[dirpT] -> Rebin(pTsumBinNum, Form("BBCspTsum_midPion0pTClass%d_rebinned", dirpT+1), pTsumBin);
		BBCspTsum_midDirPhotonpTsum_rebinned[dirpT] -> Scale(1./BBCspTsum_midDirPhotonpTsum_rebinned[dirpT] -> Integral(), "width");

		//Add to hlist
		Hlist_raw -> Add(BBCspTsum_midDirPhotonpTsum[dirpT]);
		Hlist_rebinned -> Add(BBCspTsum_midDirPhotonpTsum_rebinned[dirpT]);
	}



	//Analysis done.
	//==============
	TFile *output = new TFile(Form("pAu200GeV_p8303_%s_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0_broaderCut.root", version.Data()), "recreate");
	output -> cd();
	Hlist_raw -> Write();
	Hlist_rebinned -> Write();
	output -> Close();
}
