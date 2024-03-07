#include "../headerFiles/configurable.h"

#define NcollClass 6

void analysis_NcollTagging_pion0_pTeta_byNcoll_byCent()
{
	TFile *input = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_NcollTagging_ncollCentClass_particleDistribution.root", "read");
	
	TH3D *nEvents = (TH3D*)input -> Get("nEvent");
	TH3D *pion0_pTetaCent[NcollClass];
	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		pion0_pTetaCent[ncoll] = (TH3D*)input -> Get(Form("pTetaCent_pion0_ncollClass%d", ncoll+1));
	}

	//Analysis1. Divide events with Ncoll class and centrality class
	// Ncoll class
	// 1. 0~5, 2. 5~10, 3. 10~15, 4. 15~20, 5. 20~25, 6. 25~
	//==============================================================
	TH3D *pion0_pTetaCent_rangeSet[NcollClass];
	TH2D *pion0_pTeta[NcollClass][centBinNum];
	int zaxis_cut[] = {1, 1, 2, 2, 3, 4, 5, 6, 7, 8};

	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		for(int cent=0; cent<centBinNum; cent++)
		{
			pion0_pTetaCent[ncoll] -> GetZaxis() -> SetRange(zaxis_cut[2*cent], zaxis_cut[2*cent+1]);
			pion0_pTeta[ncoll][cent] = (TH2D*)pion0_pTetaCent[ncoll] -> Project3D("yx");
			pion0_pTeta[ncoll][cent] -> SetName(Form("pTeta_pion0_ncollClass%d_centClass%d", ncoll+1, cent+1));
		}
	}

	//Analysis2. Scale Event #
	//========================
	TH1D *numEvent_ncollClass[NcollClass];

	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		numEvent_ncollClass[ncoll] = (TH1D*)nEvents -> ProjectionX(Form("numEvent_vs_cent_ncollClass%d", ncoll+1),  0, 50, ncoll+1, ncoll+1);
	}

	TH2D *pion0_pTeta_scaled[NcollClass][centBinNum];
	for(int ncoll=0; ncoll<NcollClass; ncoll++)
	{
		numEvent_ncollClass[ncoll] -> Rebin(centBinNum, "nEvent_centBinned", centBin);
		for(int cent=0; cent<centBinNum; cent++)
		{
			pion0_pTeta_scaled[ncoll][cent] = (TH2D*)pion0_pTeta[ncoll][cent] -> Clone(Form("pTeta_pion0_ncollClass%d_centClass%d_scaled", ncoll+1, cent+1));
			pion0_pTeta_scaled[ncoll][cent] -> Scale(1./numEvent_ncollClass[ncoll] -> GetBinContent(cent+1));
			pion0_pTeta_scaled[ncoll][cent] -> Scale(1./pion0_pTeta_scaled[ncoll][cent]->GetYaxis()->GetBinWidth(1));		//scale pT bin width
			pion0_pTeta_scaled[ncoll][cent] -> Scale(1./pion0_pTeta_scaled[ncoll][cent]->GetXaxis()->GetBinWidth(1));		//scale pT bin width
		}
	}

	//Analysis Done
	//=============
	TFile *output = new TFile("pAu200GeV_p8303_ver2_option3_NcollTagging_pion0_byNcoll_byCent.root", "recreate");
	
	output -> cd();
	for(int ncoll=0; ncoll<6; ncoll++)
	{
		for(int cent=0; cent<5; cent++)
		{
			pion0_pTeta[ncoll][cent] -> Write();
		}
	}

	for(int ncoll=0; ncoll<6; ncoll++)
	{
		for(int cent=0; cent<5; cent++)
		{
			pion0_pTeta_scaled[ncoll][cent] -> Write();
		}
	}
	output -> Close();
}
