#include "../headerFiles/configurable.h"

void analysis_correlations_BBCsMultiplicity_chargepTsum_MBevents(TString version="ver2")
{
	//Input
	//=====
	TFile *input = new TFile(Form("../pre_processed/pAu200GeV_p8303_%s_option3_MBevents_BBCsMultiplicity_chargepTsum.root", version.Data()), "read");
	TH1D *BBCspTsum = (TH1D*)input -> Get("BBCsMultiplicity_chargepTsum");
	TH1D *BBCspTsum_rebinned;

	//Anlaysis 1. Get BBCs pTsum distribution by mid-pion0 pTsum and scale
	//====================================================================
	BBCspTsum -> Scale(1./BBCspTsum -> Integral());
	BBCspTsum_rebinned=(TH1D*)BBCspTsum -> Rebin(pTsumBinNum, "BBCsMultiplicity_chargepTsum_rebinned", pTsumBin);
	
	//Analysis done.
	//==============
	TFile *output = new TFile(Form("pAu200GeV_p8303_%s_option3_BBCsMultiplicity_chargepTsum_MBevents.root", version.Data()), "recreate");
	output -> cd();
	BBCspTsum_rebinned -> Write();
	output -> Close();
}
