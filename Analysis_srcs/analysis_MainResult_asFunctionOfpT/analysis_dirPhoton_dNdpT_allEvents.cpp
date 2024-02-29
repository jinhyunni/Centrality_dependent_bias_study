#include "../headerFiles/configurable.h"

void analysis_dirPhoton_dNdpT_allEvents()
{
    //input
    //-----
    TFile *dir = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_TH2DpTCent_dirPhoton.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_NcollCent.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_avgNcollCent.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_allEvents.root", "recreate");

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
    TH1D *yieldDirpT_cent[centBinNum];

    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");
	TH1D *eventN = (TH1D*)nEventCent -> Rebin(centBinNum, "nEventByCent", centBin);

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString hisname_dir = Form("yieldDirpT_cent%d", cent+1);

        yieldDirpT_cent[cent] = (TH1D*)numDirpT_cent[cent] -> Clone(hisname_dir);
        yieldDirpT_cent[cent] -> Scale(1./eventN -> GetBinContent(cent+1));

    }

    //Analysis2. Rebin for pT
    //-----------------------
    TH1D *dNdpT_dir_cent[centBinNum];
	
	//loop over particle yields by cent and rebin
    for(int cent=0; cent<centBinNum; cent++)
    {
        TString target_dir = Form("dNdpT_dir_cent%d", cent+1);
        dNdpT_dir_cent[cent] = (TH1D*)yieldDirpT_cent[cent] ->Rebin(pTBinNum, target_dir, pTBin);
    }
    
   //Analysis3. Dividing pT bin Width
   // 1/Nevent dN/dpT: binwidth not cancled
   // 1/avgNcoll     : binwidth not cancled
   //--------------------------------------
    for(int cent=0; cent<centBinNum; cent++)
    {
        for(int pT=0; pT<pTBinNum; pT++)
        {
            double binwidth = dNdpT_dir_cent[cent] -> GetBinWidth(pT+1);
			
			//scale variable binwidth
            dNdpT_dir_cent[cent] -> SetBinContent(pT+1, dNdpT_dir_cent[cent]->GetBinContent(pT+1)/binwidth);
            dNdpT_dir_cent[cent] -> SetBinError(pT+1, dNdpT_dir_cent[cent] -> GetBinError(pT+1)/binwidth);
        }
    }   
   

    //Analysis4. Get Yield/<Ncoll> vs pT, by centrality
    //-------------------------------------------------
    TH1D *YavgNcollDir[centBinNum];
    
    TProfile *avgNcollCent = (TProfile*)avgNcoll -> Rebin(centBinNum, "avgNcollCent", centBin);

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString dir = Form("YavgNcollDirpT_cent%d", cent+1);

        YavgNcollDir[cent] = (TH1D*)dNdpT_dir_cent[cent] -> Clone(dir);
        YavgNcollDir[cent] -> Scale(1./avgNcollCent -> GetBinContent(cent+1));
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
