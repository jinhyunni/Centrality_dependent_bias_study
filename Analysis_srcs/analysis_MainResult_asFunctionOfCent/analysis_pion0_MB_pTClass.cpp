#include "../headerFiles/configurable.h"

void analysis_pion0_MB_pTClass()
{
    //input
    //-----
    TFile *pion0 = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_TH2DpTCent_pion0.root", "read");
    TFile *input_NcollMB = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_Ncoll_MBevents.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_avgNcoll_MBevents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303ver5_option3_MB_pTClass_pion0.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2pTCent_pion0 = (TH2D*)pion0 -> Get("centPion0");
    TH1D *nEventMB = (TH1D*)input_NcollMB -> Get("ncoll_mb");
	TProfile *avgNcollMB = (TProfile*)input_avgNcoll -> Get("avgNcoll_mb");

    //Analysis1. Get number of pion0 by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numPion0Cent_pT[pTBinNum];
	TH1D *Pion0MB_pT[pTBinNum];
    
	//Get yield of pion0 by pTClass, in total events
	for(int pT=0; pT<pTBinNum; pT++)
	{
		TString outputname1 = Form("pTClassPion0_class%d", pT+1);
		TString outputname2 = Form("Pion0MB_pTClass%d", pT+1);
		
		cout << "pT hist start: " << (int)(pTBin[pT]*100)+1 << endl;
		cout << "pT hist finish: " << (int)(pTBin[pT+1]*100) << endl;

		numPion0Cent_pT[pT] = (TH1D*)h2pTCent_pion0 -> ProjectionX(outputname1, (int)(pTBin[pT]*100)+1, (int)(pTBin[pT+1]*100));
		Pion0MB_pT[pT] = (TH1D*)numPion0Cent_pT[pT] -> Rebin(centBin_MergedNum, outputname2, centBin_Merged);
	}

    //Event number scaling
	for(int pT=0; pT<pTBinNum; pT++)
	{
		Pion0MB_pT[pT] -> Scale(1./nEventMB -> Integral());
	}
	
	cout << "Event Num scaling" << endl;

	//pT binwidth scaling
	TH1D *pTbin = new TH1D("pTbins", "", pTBinNum, pTBin);

	for(int pT=0; pT < pTBinNum; pT++)
	{
		Pion0MB_pT[pT] -> Scale(1./pTbin -> GetBinWidth(pT+1));
	}

	cout << "pT scaling"<<endl;
 
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
    TH1D *Pion0MB_avgNcollScaled_pT[pTBinNum];

    for(int pT=0; pT<pTBinNum; pT++)
    {
        TString histname = Form("Pion0MB_avgNcollScaled_pTClass%d", pT+1);
        Pion0MB_avgNcollScaled_pT[pT] = (TH1D*)Pion0MB_pT[pT] -> Clone(histname);

		Pion0MB_avgNcollScaled_pT[pT] -> Scale(1./avgNcollMB -> GetBinContent(1));
    }

	cout << "avgNcoll scaling" << endl;

    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)

	output -> cd();
    for(int i=0; i<5; i++)
    {
       Pion0MB_pT[i] -> Write(); 
    }

	for(int i=0; i<5; i++)
	{
		Pion0MB_avgNcollScaled_pT[i] -> Write();
	}
    
     //Close files
    //-----------
    pion0 -> Close();
    input_NcollMB -> Close();
    input_avgNcoll -> Close();
    output -> Close();

 //*    //disallocation
 //* 	delete dir;
 //* 	delete input_Ncoll;
 //* 	delete input_avgNcoll;
 //* 	delete output;
        
}
