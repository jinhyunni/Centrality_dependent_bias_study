#include "../headerFiles/configurable.h"

void analysis_pion0_dNdpT_allEvents()
{
    //input
    //-----
    TFile *pion = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_TH2DpTCent_pion0.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_avgNcollCent.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_pion0_dNdpT_allEvents.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2centPion0 = (TH2D*)pion -> Get("centPion0");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
	TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Projection to get Yield by pT
    //CentClass
    //centclass1: 0~10%
    //centclass2: 10~20%
    //centclass3: 20~40%
    //centclass4: 40~60%
    //centclass5: 60~80%
    //----------------------------------------
    TH1D *numPion0pT_cent[centBinNum];
    
    numPion0pT_cent[0] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion01", 1, 1);       //centClass1: 0~10%
    numPion0pT_cent[1] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion02", 2, 2);       //centClass2: 10~20%
    numPion0pT_cent[2] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion03", 3, 4);       //centClass3: 20~40%
    numPion0pT_cent[3] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion04", 5, 6);       //centClass4: 40~60%
    numPion0pT_cent[4] = (TH1D*)h2centPion0 -> ProjectionY("centClassPion05", 7, 8);       //centClass5: 60~80%
       
    //Event number scaling
    TH1D *yieldPion0pT_cent[centBinNum];

    TH1D *nEventCent=(TH1D*)h2NcollCent -> ProjectionX("nEventByCent");
	TH1D *eventN = (TH1D*)nEventCent -> Rebin(centBinNum, "nEventByCent", centBin);

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString hisname_pion0 = Form("yieldPion0pT_cent%d", cent+1);

        yieldPion0pT_cent[cent] = (TH1D*)numPion0pT_cent[cent] -> Clone(hisname_pion0);
        yieldPion0pT_cent[cent] -> Scale(1./eventN -> GetBinContent(cent+1));

    }

    //Analysis2. Rebin for pT
    //-----------------------

    TH1D *dNdpT_pion0_cent[centBinNum];

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString target_pion0 = Form("dNdpT_pion0_cent%d", cent+1);

        dNdpT_pion0_cent[cent] = (TH1D*)yieldPion0pT_cent[cent] -> Rebin(pTBinNum, target_pion0, pTBin);
    }
    
   //Analysis3. Dividing pT bin Width
   // 1/Nevent dN/dpT: binwidth not cancled
   // 1/avgNcoll     : binwidth not cancled
   //--------------------------------------
    for(int cent=0; cent<centBinNum; cent++)
    {
        for(int pT=0; pT<pTBinNum; pT++)
        {
            double binwidth = dNdpT_pion0_cent[cent] -> GetBinWidth(pT+1);
			
			//scale variable binwidth
            dNdpT_pion0_cent[cent] -> SetBinContent(pT+1, dNdpT_pion0_cent[cent]->GetBinContent(pT+1)/binwidth);
            dNdpT_pion0_cent[cent] -> SetBinError(pT+1, dNdpT_pion0_cent[cent] -> GetBinError(pT+1)/binwidth);
			
        }
    }   
   

    //Analysis4. Get Yield/<Ncoll> vs pT, by centrality
    //-------------------------------------------------
    TH1D *YavgNcollPion0[centBinNum];

    TProfile *avgNcollCent = (TProfile*)avgNcoll -> Rebin(centBinNum, "avgNcollCent", centBin);

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString pion0 = Form("YavgNcollPion0pT_cent%d", cent+1);

        YavgNcollPion0[cent] = (TH1D*)dNdpT_pion0_cent[cent] -> Clone(pion0);
        YavgNcollPion0[cent] -> Scale(1./avgNcollCent -> GetBinContent(cent+1));
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
        //pion0
        yieldPion0pT_cent[i] -> Write();        // yield of pion0 vs pT (not rebinned)
        dNdpT_pion0_cent[i] -> Write();         // dNdpT_pion0
        YavgNcollPion0[i] -> Write();           // scaled_dNdpT_pion0
    
    }
    
    //Close files
    //-----------
    pion -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

    //disallocation
    delete pion;
    delete input_Ncoll;
    delete input_avgNcoll;
    delete output;
        
}
