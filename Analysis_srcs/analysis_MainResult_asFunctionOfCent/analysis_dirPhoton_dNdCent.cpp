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
    TH1D *numDirCent_pT[5];
    
    numDirCent_pT[0] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir1", 201, 400);  	//pT bin width: 2          
    numDirCent_pT[1] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir2", 401, 700);	 	//pT bin width: 3
    numDirCent_pT[2] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir3", 701, 1000); 	//pT bin width: 3
    numDirCent_pT[3] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir4", 1001, 1500);	//pT bin width: 5           
    numDirCent_pT[4] = (TH1D*)h2pTCent_dir -> ProjectionX("pTClassDir5", 1501, 2000);	//pT bin width: 5  
   

    //Event number scaling
	//scaling must be done by each centrality bin
    TH1D *yieldDirCent_pT[5];
    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");

	for(int i=0; i<5; i++)
	{
    	TString hisname_dir = Form("yieldDirCent_pTclass%d", i+1);
		yieldDirCent_pT[i] = new TH1D(hisname_dir, "", 11, 0, 110);

    	for(int j=0; j<nEventCent -> GetNbinsX(); j++)
   		 {
			double numEvent = nEventCent -> GetBinContent(j+1);

        	yieldDirCent_pT[i] -> SetBinContent(j+1, numDirCent_pT[i] -> GetBinContent(j+1)/numEvent);
        	yieldDirCent_pT[i] -> SetBinError(j+1, numDirCent_pT[i] -> GetBinError(j+1)/numEvent);

			cout << "pT class: " << i+1 << " cent class: " << j+1 << " value: " << yieldDirCent_pT[i] -> GetBinContent(j+1) <<" Error: "<< yieldDirCent_pT[i]->GetBinError(j+1) <<endl;
    	}
		cout << "" << endl;
	}

	//pT binwidth scaling
	double pTbinEdge[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	int pTbinNum = 5;
	TH1D *pTbin = new TH1D("pTbins", "", pTbinNum, pTbinEdge);

	for(int i=0; i < pTbinNum; i++)
	{
		yieldDirCent_pT[i] -> Scale(1./pTbin -> GetBinWidth(i+1));
	}
 
   //Analysis2. Dividing Cent bin Width
   // xAxis: centrality with inter 10%
   //----------------------------------
	
	TH1D *dNdCent_dir_pT[5];
	for(int i=0; i<pTbinNum; i++)
	{	
		TString histname = Form("dNdCent_pTClass%d", i+1);
		dNdCent_dir_pT[i] = (TH1D*)yieldDirCent_pT[i] -> Clone(histname);
		
		//scaling centrality binwidth
		dNdCent_dir_pT[i] -> Scale(1./10);
	}
	

    //Analysis4. Get Yield/<Ncoll> vs centrality, by pT class
    //-------------------------------------------------------
    TH1D *avgNcoll_scaled_dNdCent_dir_pT[5];

    for(int i=0; i<pTbinNum; i++)
    {
        TString histname = Form("dNdCent_avgNcollScaled_pTClass%d", i+1);
        avgNcoll_scaled_dNdCent_dir_pT[i] = (TH1D*)dNdCent_dir_pT[i] -> Clone(histname);

		for(int j=0; j < avgNcollCent -> GetNbinsX(); j++)
		{
			double avgNcollByCent = avgNcollCent -> GetBinContent(j+1);
        	avgNcoll_scaled_dNdCent_dir_pT[i] -> SetBinContent(j+1, avgNcoll_scaled_dNdCent_dir_pT[i] -> GetBinContent(j+1)/avgNcollByCent);
			avgNcoll_scaled_dNdCent_dir_pT[i] -> SetBinError(j+1, avgNcoll_scaled_dNdCent_dir_pT[i] -> GetBinError(j+1)/avgNcollByCent);
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
