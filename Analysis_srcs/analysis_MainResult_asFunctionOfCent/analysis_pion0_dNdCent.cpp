#include "../headerFiles/configurable.h"

void analysis_pion0_dNdCent()
{
    //input
    //-----
    TFile *pion0 = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_TH2DpTCent_pion0.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_avgNcollCent_allEvents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303ver5_option3_dNdCent_scaled_pion0.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2pTCent_pion0 = (TH2D*)pion0 -> Get("centPion0");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
	TProfile *avgNcollCent = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Get number of pion0 by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numPion0Cent_pT[pTBinNum];

	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname = Form("pTClassPion0_class%d", pT+1);
		numPion0Cent_pT[pT] = (TH1D*)h2pTCent_pion0 -> ProjectionX(outputname, (int)(pTBin[pT]*100)+1, (int)(pTBin[pT+1]*100));
	}

    //Event number scaling
	//scaling must be done by each centrality bin
    TH1D *yieldPion0Cent_pT[pTBinNum];
    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");

	for(int pT=0; pT<pTBinNum; pT++)
	{
    	TString hisname_pion0 = Form("yieldPion0Cent_pTclass%d", pT+1);
		yieldPion0Cent_pT[pT] = new TH1D(hisname_pion0, "", centBin_defaultNum, centBin_default);

    	for(int cent=0; cent<nEventCent -> GetNbinsX(); cent++)
   		 {
			double numEvent = nEventCent -> GetBinContent(cent+1);

        	yieldPion0Cent_pT[pT] -> SetBinContent(cent+1, numPion0Cent_pT[pT] -> GetBinContent(cent+1)/numEvent);
        	yieldPion0Cent_pT[pT] -> SetBinError(cent+1, numPion0Cent_pT[pT] -> GetBinError(cent+1)/numEvent);

			cout << "pT class: " << pT+1 << " cent class: " << cent+1 << " value: " << yieldPion0Cent_pT[pT] -> GetBinContent(cent+1) <<" Error: "<< yieldPion0Cent_pT[pT]->GetBinError(cent+1) <<endl;
    	}
		cout << "" << endl;
	}

	//pT binwidth scaling
	TH1D *pTbin = new TH1D("pTbins", "", pTBinNum, pTBin); //empty hist for getting pT Bin width

	for(int pT=0; pT < pTBinNum; pT++)
	{
		yieldPion0Cent_pT[pT] -> Scale(1./pTbin -> GetBinWidth(pT+1));
	}
 
   //Analysis2. Dividing Cent bin Width
   // xAxis: centrality with inter 10%
   //----------------------------------
	
	TH1D *dNdCent_pion0_pT[pTBinNum];
	for(int pT=0; pT<pTBinNum; pT++)
	{	
		TString histname = Form("dNdCent_pTClass%d", pT+1);
		dNdCent_pion0_pT[pT] = (TH1D*)yieldPion0Cent_pT[pT] -> Clone(histname);
		
		//scaling centrality binwidth
		dNdCent_pion0_pT[pT] -> Scale(1./10);
	}
	

    //Analysis4. Get Yield/<Ncoll> vs centrality, by pT class
    //-------------------------------------------------------
    TH1D *avgNcoll_scaled_dNdCent_pion0_pT[pTBinNum];

    for(int pT=0; pT<pTBinNum; pT++)
    {
        TString histname = Form("dNdCent_avgNcollScaled_pTClass%d", pT+1);
        avgNcoll_scaled_dNdCent_pion0_pT[pT] = (TH1D*)dNdCent_pion0_pT[pT] -> Clone(histname);

		for(int cent=0; cent < avgNcollCent -> GetNbinsX(); cent++)
		{
			double avgNcollByCent = avgNcollCent -> GetBinContent(cent+1);
        	avgNcoll_scaled_dNdCent_pion0_pT[pT] -> SetBinContent(cent+1, avgNcoll_scaled_dNdCent_pion0_pT[pT] -> GetBinContent(cent+1)/avgNcollByCent);
			avgNcoll_scaled_dNdCent_pion0_pT[pT] -> SetBinError(cent+1, avgNcoll_scaled_dNdCent_pion0_pT[pT] -> GetBinError(cent+1)/avgNcollByCent);
		}
    }

    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)

	output -> cd();
    for(int i=0; i<5; i++)
    {
        //dirPhoton
		numPion0Cent_pT[i] -> Write();
		yieldPion0Cent_pT[i] -> Write();
        dNdCent_pion0_pT[i] -> Write();           				// dNdCenet_dirPhoton
        avgNcoll_scaled_dNdCent_pion0_pT[i] -> Write();           //scaled_dNdCent_dirPhoton
    }
    
     //Close files
    //-----------
    pion0 -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

 //*    //disallocation
 //* 	delete dir;
 //* 	delete input_Ncoll;
 //* 	delete input_avgNcoll;
 //* 	delete output;
        
}
