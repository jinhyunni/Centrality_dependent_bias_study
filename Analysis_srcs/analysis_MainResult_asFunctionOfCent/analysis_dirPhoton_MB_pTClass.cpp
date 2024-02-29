#include "../headerFiles/configurable.h"

void analysis_dirPhoton_MB_pTClass()
{
    //input
    //-----
    TFile *dir = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_TH2DpTCent_dirPhoton.root", "read");
    TFile *input_NcollMB = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_Ncoll.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_avgNcoll.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_MB_pTClass_dirPhoton.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2pTCent_dir = (TH2D*)dir -> Get("centDir");
    TH1D *nEventMB = (TH1D*)input_NcollMB -> Get("nEvent");
	TProfile *avgNcollMB = (TProfile*)input_avgNcoll -> Get("avgNcoll_mb");

    //Analysis1. Get number of direct photon by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numDirCent_pT[5];
	TH1D *DirMB_pT[5];
   
	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname1 = Form("pTClassDir%d", pT+1);
		TString outputname2 = Form("DirMB_pTClass%d", pT+1);

		numDirCent_pT[pT] = (TH1D*)h2pTCent_dir -> ProjectionX(outputname1, (int)(pTBin[pT]*100)+1, (int)(pTBin[pT+1]*100));
		DirMB_pT[pT] = (TH1D*)numDirCent_pT[pT] -> Rebin(centBin_MergedNum, outputname2, centBin_Merged);
	}
   
    //Event number scaling
	for(int pT=0; pT<pTBinNum; pT++)
	{
		DirMB_pT[pT] -> Scale(1./nEventMB -> Integral());
	}
	
	cout << "Event Num scaling" << endl;

	//pT binwidth scaling
	TH1D *pTbin = new TH1D("pTbins", "", pTBinNum, pTBin);

	for(int pT=0; pT<pTBinNum; pT++)
	{
		DirMB_pT[pT] -> Scale(1./pTbin -> GetBinWidth(pT+1));
	}

 //?   //Analysis2. Dividing Cent bin Width
 //?   // xAxis: centrality with inter 110
 //?   //----------------------------------
 //?	
 //?	TH1D *DirMB_centScaled_pT[5];
 //?	for(int i=0; i<pTbinNum; i++)
 //?	{	
 //?		TString histname = Form("DirMB_centScaled_pTClass%d", i+1);
 //?		DirMB_centScaled_pT[i] = (TH1D*)DirMB_pT[i] -> Clone(histname);
 //?		
 //?		dNdCent_dir_pT[i] -> Scale(1./10);
 //?	}
	

    //Analysis2. Get Yield/<Ncoll> by pT class
    //-------------------------------------------------------
    TH1D *DirMB_avgNcollScaled_pT[pTBinNum];

    for(int pT=0; pT<pTBinNum; pT++)
    {
        TString histname = Form("DirMB_avgNcollScaled_pTClass%d", pT+1);

        DirMB_avgNcollScaled_pT[pT] = (TH1D*)DirMB_pT[pT] -> Clone(histname);
		DirMB_avgNcollScaled_pT[pT] -> Scale(1./avgNcollMB -> GetBinContent(1));
    }

    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)

	output -> cd();
    for(int i=0; i<5; i++)
    {
       DirMB_pT[i] -> Write(); 
    }

	for(int i=0; i<5; i++)
	{
		DirMB_avgNcollScaled_pT[i] -> Write();
	}
    
     //Close files
    //-----------
    dir -> Close();
    input_NcollMB -> Close();
    input_avgNcoll -> Close();
    output -> Close();

 //*    //disallocation
 //* 	delete dir;
 //* 	delete input_Ncoll;
 //* 	delete input_avgNcoll;
 //* 	delete output;
        
}
