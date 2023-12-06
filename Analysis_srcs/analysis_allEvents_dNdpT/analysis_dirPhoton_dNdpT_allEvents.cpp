void analysis_dirPhoton_dNdpT_allEvents()
{
    //input
    //-----
    TFile *dir = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_TH2DdirCent_allEvents.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303ver3_option3_dirPhoton_dNdpT_allEvents.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2centDir = (TH2D*)dir -> Get("centDir");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
    TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Get number of direct photon by centrality per event
    //CentClass
    //centclass1: 0~10%
    //centclass2: 10~20%
    //centclass3: 20~40%
    //centclass4: 40~60%
    //centclass5: 60~80%
    //--------------------------------------------------------------
    TH1D *numDirpT_cent[5];
    
    numDirpT_cent[0] = (TH1D*)h2centDir -> ProjectionY("centClassDir1", 1, 1);             //centClass1: 0~10%
    numDirpT_cent[1] = (TH1D*)h2centDir -> ProjectionY("centClassDir2", 2, 2);             //centClass2: 10~20%
    numDirpT_cent[2] = (TH1D*)h2centDir -> ProjectionY("centClassDir3", 3, 4);             //centClass3: 20~40%
    numDirpT_cent[3] = (TH1D*)h2centDir -> ProjectionY("centClassDir4", 5, 6);             //centClass4: 40~60%
    numDirpT_cent[4] = (TH1D*)h2centDir -> ProjectionY("centClassDir5", 7, 8);             //centClass5: 60~80%
    
    //Event number scaling
    TH1D *yieldDirpT_cent[5];

    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");
	double centRange[] = {0, 10, 20, 40, 60, 80};
	TH1D *eventN = (TH1D*)nEventCent -> Rebin(5, "nEventByCent", centRange);

    for(int i=0; i<5; i++)
    {
        TString hisname_dir = Form("yieldDirpT_cent%d", i+1);

        yieldDirpT_cent[i] = (TH1D*)numDirpT_cent[i] -> Clone(hisname_dir);

        yieldDirpT_cent[i] -> Scale(1./eventN -> GetBinContent(i+1));

        //cout << eventN -> GetBinContent(i+1) << endl;
                
    }

    //Analysis2. Rebin for pT
    //-----------------------
    //double binEdge[]={0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0};   //11 binning   
    double binEdge[]={0, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.0, 9.0, 11.0, 15.0, 20.0};   //11 binning   
    
    TH1D *dNdpT_dir_cent[5];

    for(int i=0; i<5; i++)
    {
        TString target_dir = Form("dNdpT_dir_cent%d", i+1);
        dNdpT_dir_cent[i] = (TH1D*)yieldDirpT_cent[i] ->Rebin(11, target_dir, binEdge);
    }
    
   //Analysis3. Dividing pT bin Width
   // 1/Nevent dN/dpT: binwidth not cancled
   // 1/avgNcoll     : binwidth not cancled
   //--------------------------------------
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<11; j++)
        {
            double binwidth = dNdpT_dir_cent[i] -> GetBinWidth(j+1);
			
			//scale variable binwidth
            dNdpT_dir_cent[i] -> SetBinContent(j+1, dNdpT_dir_cent[i]->GetBinContent(j+1)/binwidth);
            dNdpT_dir_cent[i] -> SetBinError(j+1, dNdpT_dir_cent[i] -> GetBinError(j+1)/binwidth);
        }
    }   
   

    //Analysis4. Get Yield/<Ncoll> vs pT, by centrality
    //-------------------------------------------------
    TH1D *YavgNcollDir[5];
    
    double centclass[] = {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollCent = (TProfile*)avgNcoll -> Rebin(5, "avgNcollCent", centclass);

    for(int i=0; i<5; i++)
    {
        TString dir = Form("YavgNcollDirpT_cent%d", i+1);

        YavgNcollDir[i] = (TH1D*)dNdpT_dir_cent[i] -> Clone(dir);

        YavgNcollDir[i] -> Scale(1./avgNcollCent -> GetBinContent(i+1));
    }
    
 //*    //Analysis5. Get ratio of direct photon and pion0 yield
 //*    //Divide pT rebinned direct photon yield with pion0
 //*    //<Ncoll> scaling cancels with ratio
 //*    //|eta|<1 scaling cacels with ratio
 //*    //-----------------------------------------------------
 //*    TH1D *gammaRpion0[5];
 //*
 //*    for(int i=0; i<5; i++)
 //*    {
 //*        TString ratio = Form("gammaRpion0_cent%d", i+1);
 //*
 //*        gammaRpion0[i] = (TH1D*)dNdpT_dir_cent[i] -> Clone(ratio);
 //*        gammaRpion0[i] -> Divide(dNdpT_pion0_cent[i]);
 //*    }


    //Write outputs in outputfile
    //---------------------------
    //Write yield of pion0 vs pT(not rebinned)
    for(int i=0; i<5; i++)
    {
        //dirPhoton
        yieldDirpT_cent[i] -> Write();          // yield of direct photon vs pT(not rebinned)
        dNdpT_dir_cent[i] -> Write();           // dNdpT_dirPhoton
        YavgNcollDir[i] -> Write();             //scaled_dNdpT_dirPhoton
        
    }
    
     //Close files
    //-----------
    dir -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

    //disallocation
    delete dir;
    delete input_Ncoll;
    delete input_avgNcoll;
    delete output;
        
}
