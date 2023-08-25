void analysis_gammaApion0_bypT()
{
    //input
    //-----

    TFile *pion = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");
    
    TFile *input_Ncoll = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCent_allEvents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_bypT.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2centPion0 = (TH2D*)pion -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir -> Get("centDir");

    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
    TH1D *avgNcoll = (TH1D*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Projection to get Yield by pT
    //CentClass
    //centclass1: 0~10%
    //centclass2: 10~20%
    //centclass3: 20~40%
    //centclass4: 40~60%
    //centclass5: 60~80%
    //----------------------------------------

    TH1D *Ypion0pT_cent[10];
    TH1D *YdirpT_cent[10];
    for(int i=0; i<10; i++)
    {   
        TString hisname_pion0 = Form("pion0pT_cent%d", i+1);
        TString hisname_dir = Form("dirpT_cent%d", i+1);

        Ypion0pT_cent[i] = (TH1D*)h2centPion0->ProjectionY(hisname_pion0, i+1, i+1);
        YdirpT_cent[i] = (TH1D*)h2centDir->ProjectionY(hisname_dir, i+1, i+1);
    }
    

    //Event number scaling
    TH1D *yieldPion0pT_cent[10];
    TH1D *yieldDirpT_cent[10];
    TH1D *nEvntCent = (TH1D*)h2NcollCent -> ProjectionX();

    for(int i=0; i<10; i++)
    {
        TString hisname_pion0 = Form("yieldPion0pT_cent%d", i+1);
        TString hisname_dir = Form("yieldDirpT_cent%d", i+1);

        yieldPion0pT_cent[i] = (TH1D*)Ypion0pT_cent[i] -> Clone(hisname_pion0);
        yieldDirpT_cent[i] = (TH1D*)YdirpT_cent[i] -> Clone(hisname_dir);

        yieldPion0pT_cent[i] -> Scale(1./nEvntCent -> GetBinContent(i+1));
        yieldDirpT_cent[i] -> Scale(1./nEvntCent -> GetBinContent(i+1));

                
    }

    //Analysis2. Rebin for pT
    //-----------------------
    double binEdge[]={0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0};   //10 binning   
    
    TH1D *yieldPion0pT_centR[10];
    TH1D *yieldDirpT_centR[10];

    for(int i=0; i<10; i++)
    {
        TString target_pion0 = Form("Ypion0pT_cent%dR", i+1);
        TString target_dir = Form("Ypion0pT_dir%dR", i+1);

        yieldPion0pT_centR[i] = (TH1D*)yieldPion0pT_cent[i] -> Rebin(10, target_pion0, binEdge);
        yieldDirpT_centR[i] = (TH1D*)yieldDirpT_cent[i] ->Rebin(10, target_dir, binEdge);

        yieldPion0pT_centR[i] -> Write();
        yieldDirpT_centR[i] -> Write();
    }
    
   //Analysis3. Dividing pT bin Width
   // 1/Nevent dN/dpT: binwidth not cancled
   // 1/avgNcoll     : binwidth not cancled
   //--------------------------------------
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            double binwidth = yieldPion0pT_centR[i] -> GetBinWidth(j+1);

            yieldPion0pT_centR[i] -> SetBinContent(j+1, yieldPion0pT_centR[i]->GetBinContent(j+1)/binwidth);
            yieldDirpT_centR[i] -> SetBinContent(j+1, yieldDirpT_centR[i]->GetBinContent(j+1)/binwidth);
        }

        yieldPion0pT_centR[i] -> Write();
        yieldDirpT_centR[i] -> Write();
    }   
   

    //Analysis4. Get Yield/<Ncoll> vs pT, by centrality
    //------------------------------------------------
    TH1D *YavgNcollPion0[10];
    TH1D *YavgNcollDir[10];

    for(int i=0; i<10; i++)
    {
        TString pion0 = Form("YavgNcollPion0pT_cent%d", i+1);
        TString dir = Form("YavgNcollDirpT_cent%d", i+1);

        YavgNcollPion0[i] = (TH1D*)yieldPion0pT_centR[i] -> Clone(pion0);
        YavgNcollDir[i] = (TH1D*)yieldDirpT_centR[i] -> Clone(dir);

        YavgNcollPion0[i] -> Scale(1./avgNcoll->GetBinContent(i+1));
        YavgNcollDir[i] -> Scale(1./avgNcoll->GetBinContent(i+1));
    }
    

    //Write outputs in outputfile
    //---------------------------
    
    for(int i=0; i<10; i++)
    {
        YavgNcollPion0[i] -> Write();
        YavgNcollDir[i] -> Write();
    }


    //Close files
    //-----------
    pion -> Close();
    dir -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

    //disallocation
    delete pion;
    delete dir;
    delete input_Ncoll;
    delete input_avgNcoll;
    delete output;
        
}
