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

    //Analysis1. Get number of direct photon by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numPion0Cent_pT[5];
	double binMB[] = {0, 110};
	TH1D *Pion0MB_pT[5];
    
    numPion0Cent_pT[0] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class1", 201, 400);		Pion0MB_pT[0] = (TH1D*)numPion0Cent_pT[0] -> Rebin(1, "Pion0MB_pTClass1", binMB);	//pT bin width: 2          
    numPion0Cent_pT[1] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class2", 401, 700);		Pion0MB_pT[1] = (TH1D*)numPion0Cent_pT[1] -> Rebin(1, "Pion0MB_pTClass2", binMB);	//pT bin width: 3
    numPion0Cent_pT[2] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class3", 701, 1000); 	Pion0MB_pT[2] = (TH1D*)numPion0Cent_pT[2] -> Rebin(1, "Pion0MB_pTClass3", binMB);	//pT bin width: 3
    numPion0Cent_pT[3] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class4", 1001, 1500);	Pion0MB_pT[3] = (TH1D*)numPion0Cent_pT[3] -> Rebin(1, "Pion0MB_pTClass4", binMB);	//pT bin width: 5           
    numPion0Cent_pT[4] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class5", 1501, 2000);	Pion0MB_pT[4] = (TH1D*)numPion0Cent_pT[4] -> Rebin(1, "Pion0MB_pTClass5", binMB); 	//pT bin width: 5  
   
	cout << "Analysis start" << endl;

    //Event number scaling
	for(int i=0; i<5; i++)
	{
		Pion0MB_pT[i] -> Scale(1./nEventMB -> Integral());
	}
	
	cout << "Event Num scaling" << endl;

	//pT binwidth scaling
	double pTbinEdge[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	int pTbinNum = 5;
	TH1D *pTbin = new TH1D("pTbins", "", pTbinNum, pTbinEdge);

	for(int i=0; i < pTbinNum; i++)
	{
		Pion0MB_pT[i] -> Scale(1./pTbin -> GetBinWidth(i+1));
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
    TH1D *Pion0MB_avgNcollScaled_pT[5];

    for(int i=0; i<pTbinNum; i++)
    {
        TString histname = Form("Pion0MB_avgNcollScaled_pTClass%d", i+1);
        Pion0MB_avgNcollScaled_pT[i] = (TH1D*)Pion0MB_pT[i] -> Clone(histname);

		Pion0MB_avgNcollScaled_pT[i] -> Scale(1./avgNcollMB -> GetBinContent(1));
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
