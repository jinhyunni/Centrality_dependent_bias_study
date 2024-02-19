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
	double binMB[] = {0, 110};
	TH1D *DirMB_pT[5];
    
    numDirCent_pT[0] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir1", 201, 400);		DirMB_pT[0] = (TH1D*)numDirCent_pT[0] -> Rebin(1, "DirMB_pTClass1", binMB);	//pT bin width: 2          
    numDirCent_pT[1] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir2", 401, 700);		DirMB_pT[1] = (TH1D*)numDirCent_pT[1] -> Rebin(1, "DirMB_pTClass2", binMB);	//pT bin width: 3
    numDirCent_pT[2] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir3", 701, 1000); 	DirMB_pT[2] = (TH1D*)numDirCent_pT[2] -> Rebin(1, "DirMB_pTClass3", binMB);	//pT bin width: 3
    numDirCent_pT[3] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir4", 1001, 1500);	DirMB_pT[3] = (TH1D*)numDirCent_pT[3] -> Rebin(1, "DirMB_pTClass4", binMB);	//pT bin width: 5           
    numDirCent_pT[4] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir5", 1501, 2000);	DirMB_pT[4] = (TH1D*)numDirCent_pT[4] -> Rebin(1, "DirMB_pTClass5", binMB); //pT bin width: 5  
   
    //Event number scaling
	for(int i=0; i<5; i++)
	{
		DirMB_pT[i] -> Scale(1./nEventMB -> Integral());
	}
	
	cout << "Event Num scaling" << endl;

	//pT binwidth scaling
	double pTbinEdge[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	int pTbinNum = 5;
	TH1D *pTbin = new TH1D("pTbins", "", pTbinNum, pTbinEdge);

	for(int i=0; i < pTbinNum; i++)
	{
		DirMB_pT[i] -> Scale(1./pTbin -> GetBinWidth(i+1));
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
    TH1D *DirMB_avgNcollScaled_pT[5];

    for(int i=0; i<pTbinNum; i++)
    {
        TString histname = Form("DirMB_avgNcollScaled_pTClass%d", i+1);
        DirMB_avgNcollScaled_pT[i] = (TH1D*)DirMB_pT[i] -> Clone(histname);

		DirMB_avgNcollScaled_pT[i] -> Scale(1./avgNcollMB -> GetBinContent(1));
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
