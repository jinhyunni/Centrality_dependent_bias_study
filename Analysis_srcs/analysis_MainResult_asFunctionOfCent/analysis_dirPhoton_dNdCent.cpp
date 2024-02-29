#include "../headerFiles/configurable.h"

void analysis_dirPhoton_dNdCent()
{
    //input
    //-----
    TFile *dir = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_TH2DpTCent_dirPhoton.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_NcollCent.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_avgNcollCent.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dNdCent_scaled_dirPhoton.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2pTCent_dir = (TH2D*)dir -> Get("centDir");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
	TProfile *avgNcollCent = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Get number of direct photon by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numDirCent_pT[pTBinNum];
   
	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname = Form("pTClassDir%d", pT+1);
		numDirCent_pT[pT] = (TH1D*)h2pTCent_dir -> ProjectionX(outputname, (int)(pTBin[pT]*100)+1, (int)(pTBin[pT+1]*100));
	}

    //Event number scaling
	//scaling must be done by each centrality bin
    TH1D *yieldDirCent_pT[pTBinNum];
    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");

	for(int pT=0; pT<pTBinNum; pT++)
	{
    	TString hisname_dir = Form("yieldDirCent_pTclass%d", pT+1);
		yieldDirCent_pT[pT] = new TH1D(hisname_dir, "", centBin_defaultNum, centBin_default);

    	for(int cent=0; cent<nEventCent -> GetNbinsX(); cent++)
   		 {
			double numEvent = nEventCent -> GetBinContent(cent+1);

        	yieldDirCent_pT[pT] -> SetBinContent(cent+1, numDirCent_pT[pT] -> GetBinContent(cent+1)/numEvent);
        	yieldDirCent_pT[pT] -> SetBinError(cent+1, numDirCent_pT[pT] -> GetBinError(cent+1)/numEvent);

			cout << "pT class: " << pT+1 << " cent class: " << cent+1 << " value: " << yieldDirCent_pT[pT] -> GetBinContent(cent+1) <<" Error: "<< yieldDirCent_pT[pT]->GetBinError(cent+1) <<endl;
    	}
		cout << "" << endl;
	}

	//pT binwidth scaling
	TH1D *pTbin = new TH1D("pTbins", "", pTBinNum, pTBin);

	for(int pT=0; pT<pTBinNum; pT++)
	{
		yieldDirCent_pT[pT] -> Scale(1./pTbin -> GetBinWidth(pT+1));
	}
 
   //Analysis2. Dividing Cent bin Width
   // xAxis: centrality with inter 10%
   //----------------------------------
	
	TH1D *dNdCent_dir_pT[pTBinNum];
	for(int pT=0; pT<pTBinNum; pT++)
	{	
		TString histname = Form("dNdCent_pTClass%d", pT+1);
		dNdCent_dir_pT[pT] = (TH1D*)yieldDirCent_pT[pT] -> Clone(histname);
		
		//scaling centrality binwidth
		dNdCent_dir_pT[pT] -> Scale(1./10);
	}
	

    //Analysis4. Get Yield/<Ncoll> vs centrality, by pT class
    //-------------------------------------------------------
    TH1D *avgNcoll_scaled_dNdCent_dir_pT[pTBinNum];

    for(int pT=0; pT<pTBinNum; pT++)
    {
        TString histname = Form("dNdCent_avgNcollScaled_pTClass%d", pT+1);
        avgNcoll_scaled_dNdCent_dir_pT[pT] = (TH1D*)dNdCent_dir_pT[pT] -> Clone(histname);

		for(int cent=0; cent < avgNcollCent -> GetNbinsX(); cent++)
		{
			double avgNcollByCent = avgNcollCent -> GetBinContent(cent+1);
        	avgNcoll_scaled_dNdCent_dir_pT[pT] -> SetBinContent(cent+1, avgNcoll_scaled_dNdCent_dir_pT[pT] -> GetBinContent(cent+1)/avgNcollByCent);
			avgNcoll_scaled_dNdCent_dir_pT[pT] -> SetBinError(cent+1, avgNcoll_scaled_dNdCent_dir_pT[pT] -> GetBinError(cent+1)/avgNcollByCent);
		}
    }

    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)

	output -> cd();
    for(int i=0; i<5; i++)
    {
        //dirPhoto
        dNdCent_dir_pT[i] -> Write();           				// dNdCenet_dirPhoton
        avgNcoll_scaled_dNdCent_dir_pT[i] -> Write();           //scaled_dNdCent_dirPhoton
        
    }
    
     //Close files
    //-----------
    dir -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

 //*    //disallocation
 //* 	delete dir;
 //* 	delete input_Ncoll;
 //* 	delete input_avgNcoll;
 //* 	delete output;
        
}
