#include "../headerFiles/configurable.h"

void analysis_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0(TString version)
{
	//Input
	//=====
	TFile *input = new TFile(Form("../pre_processed/pAu200GeV_p8303_%s_option3_correlations_withPion0_BBCsMultiplicity_chargepTsum.root", version.Data()), "read");
	TH2D *BBCspTsum_vs_maxPion0pT = (TH2D*)input -> Get("BBCsMultiplicity_charge_corrMidPion0pT");

	//Anlaysis 1. Get BBCs pTsum distribution by mid-pion0 pTsum and scale
	//====================================================================
	TObjArray *Hlist_raw = new TObjArray(0);
	TObjArray *Hlist_rebinned = new TObjArray(0);
	
	TH1D *BBCspTsum_midPion0pTsum[pTBinNum];
	TH1D *BBCspTsum_midPion0pTsum_rebinned[pTBinNum];

	for(int pi0pT=0; pi0pT<pTBinNum; pi0pT++)
	{
		double binwidth = BBCspTsum_vs_maxPion0pT -> GetYaxis() -> GetBinWidth(1);
		int binNum_cutStart = (int)(pTBin[pi0pT]*1./binwidth)+1;
		int binNum_cutFinish = (int)(pTBin[pi0pT+1]*1./binwidth);

		cout << "Cut Start Bin: " << binNum_cutStart << endl;
		cout << "Cut Finish Bin: " << binNum_cutFinish << endl;
		cout << "***************" << endl;

		BBCspTsum_midPion0pTsum[pi0pT] = (TH1D*)BBCspTsum_vs_maxPion0pT -> ProjectionX(Form("BBCspTsum_midPion0pTClass%d", pi0pT+1), binNum_cutStart, binNum_cutFinish);
		BBCspTsum_midPion0pTsum[pi0pT] -> Scale(1./BBCspTsum_midPion0pTsum[pi0pT] -> Integral());
		BBCspTsum_midPion0pTsum_rebinned[pi0pT]=(TH1D*)BBCspTsum_midPion0pTsum[pi0pT] -> Rebin(pTsumBinNum, Form("BBCspTsum_midPion0pTClass%d_rebinned", pi0pT+1), pTsumBin);

		//Add to hlist
		Hlist_raw -> Add(BBCspTsum_midPion0pTsum[pi0pT]);
		Hlist_rebinned -> Add(BBCspTsum_midPion0pTsum_rebinned[pi0pT]);
	}



	//Analysis done.
	//==============
	TFile *output = new TFile(Form("pAu200GeV_p8303_%s_option3_correlations_BBCsMultiplicity_chargepTsum_corrWithMidPion0.root", version.Data()), "recreate");
	output -> cd();
	Hlist_raw -> Write();
	Hlist_rebinned -> Write();
	output -> Close();
}
