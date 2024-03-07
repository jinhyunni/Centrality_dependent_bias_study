#include "../headerFiles/configurable.h"

void analysis_NcollTagging_dirPhoton_pTeta_byNcoll_byCent()
{
	TFile *input = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_NcollTagging_ncollCentClass_particleDistribution.root", "read");
	
	TH3D *charge_pTetaCent[6];
	for(int ncoll=0; ncoll<6; ncoll++)
	{
		charge_pTetaCent[ncoll] = (TH3D*)input -> Get(Form("pTetaCent_dirPhoton_ncollClass%d", ncoll+1));
	}

	//Analysis1. Divide events with Ncoll class and centrality class
	// Ncoll class
	// 1. 0~5, 2. 5~10, 3. 10~15, 4. 15~20, 5. 20~25, 6. 25~
	//==============================================================
	TH3D *charge_pTetaCent_rangeSet[6];
	TH2D *charge_pTeta[6][5];
	int zaxis_cut[] = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8};

	for(int ncoll=0; ncoll<6; ncoll++)
	{
		for(int cent=0; cent<5; cent++)
		{
			charge_pTetaCent[ncoll] -> GetZaxis() -> SetRange(zaxis_cut[2*cent], zaxis_cut[2*cent+1]);
			charge_pTeta[ncoll][cent] = (TH2D*)charge_pTetaCent[ncoll] -> Project3D("yx");
			charge_pTeta[ncoll][cent] -> SetName(Form("pTeta_dirPhoton_ncollClass%d_centClass%d", ncoll+1, cent+1));
		}
	}
	
	//Analysis Done
	//=============
	TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_dirPhoton_byNcoll_byCent.root", "recreate");
	
	output -> cd();
	for(int ncoll=0; ncoll<6; ncoll++)
	{
		for(int cent=0; cent<5; cent++)
		{
			charge_pTeta[ncoll][cent] -> Write();
		}
	}
	output -> Close();
}
