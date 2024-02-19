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

    //Analysis1. Get number of direct photon by pT as function of centrality  per event
    //pTClass
    //pTClass1: 2~4 GeV
    //pTClass2: 4~7 GeV
    //pTClass3: 7~10 GeV
    //pTClass4: 10~15 GeV
    //pTClass5: 15~20GeV
    //---------------------------------------------------------------------------------
    TH1D *numPion0Cent_pT[5];
    
    numPion0Cent_pT[0] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class1", 201, 400);  	//pT bin width: 2          
    numPion0Cent_pT[1] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class2", 401, 700);	 	//pT bin width: 3
    numPion0Cent_pT[2] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class3", 701, 1000); 	//pT bin width: 3
    numPion0Cent_pT[3] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class4", 1001, 1500);	//pT bin width: 5           
    numPion0Cent_pT[4] = (TH1D*)h2pTCent_pion0 -> ProjectionX("pTClassPion0_class5", 1501, 2000);	//pT bin width: 5  
   

    //Event number scaling
	//scaling must be done by each centrality bin
    TH1D *yieldPion0Cent_pT[5];
    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");

	for(int i=0; i<5; i++)
	{
    	TString hisname_pion0 = Form("yieldPion0Cent_pTclass%d", i+1);
		yieldPion0Cent_pT[i] = new TH1D(hisname_pion0, "", 11, 0, 110);

    	for(int j=0; j<nEventCent -> GetNbinsX(); j++)
   		 {
			double numEvent = nEventCent -> GetBinContent(j+1);

        	yieldPion0Cent_pT[i] -> SetBinContent(j+1, numPion0Cent_pT[i] -> GetBinContent(j+1)/numEvent);
        	yieldPion0Cent_pT[i] -> SetBinError(j+1, numPion0Cent_pT[i] -> GetBinError(j+1)/numEvent);

			cout << "pT class: " << i+1 << " cent class: " << j+1 << " value: " << yieldPion0Cent_pT[i] -> GetBinContent(j+1) <<" Error: "<< yieldPion0Cent_pT[i]->GetBinError(j+1) <<endl;
    	}
		cout << "" << endl;
	}

	//pT binwidth scaling
	double pTbinEdge[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	int pTbinNum = 5;
	TH1D *pTbin = new TH1D("pTbins", "", pTbinNum, pTbinEdge);

	for(int i=0; i < pTbinNum; i++)
	{
		yieldPion0Cent_pT[i] -> Scale(1./pTbin -> GetBinWidth(i+1));
	}
 
   //Analysis2. Dividing Cent bin Width
   // xAxis: centrality with inter 10%
   //----------------------------------
	
	TH1D *dNdCent_pion0_pT[5];
	for(int i=0; i<pTbinNum; i++)
	{	
		TString histname = Form("dNdCent_pTClass%d", i+1);
		dNdCent_pion0_pT[i] = (TH1D*)yieldPion0Cent_pT[i] -> Clone(histname);
		
		//scaling centrality binwidth
		dNdCent_pion0_pT[i] -> Scale(1./10);
	}
	

    //Analysis4. Get Yield/<Ncoll> vs centrality, by pT class
    //-------------------------------------------------------
    TH1D *avgNcoll_scaled_dNdCent_pion0_pT[5];

    for(int i=0; i<pTbinNum; i++)
    {
        TString histname = Form("dNdCent_avgNcollScaled_pTClass%d", i+1);
        avgNcoll_scaled_dNdCent_pion0_pT[i] = (TH1D*)dNdCent_pion0_pT[i] -> Clone(histname);

		for(int j=0; j < avgNcollCent -> GetNbinsX(); j++)
		{
			double avgNcollByCent = avgNcollCent -> GetBinContent(j+1);
        	avgNcoll_scaled_dNdCent_pion0_pT[i] -> SetBinContent(j+1, avgNcoll_scaled_dNdCent_pion0_pT[i] -> GetBinContent(j+1)/avgNcollByCent);
			avgNcoll_scaled_dNdCent_pion0_pT[i] -> SetBinError(j+1, avgNcoll_scaled_dNdCent_pion0_pT[i] -> GetBinError(j+1)/avgNcollByCent);
		}
    }

    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)

	output -> cd();
    for(int i=0; i<5; i++)
    {
        //dirPhoto
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
