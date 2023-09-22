void analysis_yieldOfgammaApion0_byCent()
{
    //input
    //-----
    TFile *pion = new TFile("pAu200GeV_kiaf_option3_TH2Dpion0Cent.root", "read");
    TFile *dir = new TFile("pAu200GeV_kiaf_option3_TH2DdirCent.root", "read");
    TFile *input_Ncoll = new TFile("pAu200GeV_kiaf_option3_NcollCent_allEvents.root", "read");
    TFile *input_avgNcoll = new TFile("pAu200GeV_kiaf_option3_avgNcollCent_allEvents.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_kiaf_option3_yieldOfgammaApion0_byCent.root", "recreate");

    //Input histograms
    //----------------
    TH2D *h2centPion0 = (TH2D*)pion -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir -> Get("centDir");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
    TH1D *avgNcoll = (TH1D*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Projection to get Yield
    //----------------------------------
    TH1D *npion0Cent = (TH1D*)h2centPion0 -> ProjectionX("pion0_integrated");
    TH1D *npion0Cent_highpT = (TH1D*)h2centPion0 -> ProjectionX("pion0_highpT", 201, 2000);
    TH1D *npion0Cent_lowpT = (TH1D*)h2centPion0 -> ProjectionX("pino0_lowpT", 1, 200);

    TH1D *ndirCent = (TH1D*)h2centDir -> ProjectionX("dir_integrated");
    TH1D *ndirCent_highpT = (TH1D*)h2centDir -> ProjectionX("dir_highpT", 201, 2000);
    TH1D *ndirCent_lowpT = (TH1D*)h2centDir -> ProjectionX("dir_lowpT", 1, 200);

    TH1D *nEvntCent = (TH1D*)h2NcollCent -> ProjectionX();

    //Analysis2. Rebin to fit cent Class
    //0~10%
    //10~20%
    //20~40%
    //40~60%
    //60~80%
    //----------------------------------
    double binEdge[]={0, 10, 20, 40, 60, 80};

    TH1D *npion0CentR = (TH1D*)npion0Cent -> Rebin(5, "npion0CentR", binEdge);
    TH1D *npion0Cent_highpTR = (TH1D*)npion0Cent_highpT -> Rebin(5, "npion0Cent_highpTR", binEdge);
    TH1D *npion0Cent_lowpTR = (TH1D*)npion0Cent_lowpT -> Rebin(5, "npion0Cent_lowpTR", binEdge);

    TH1D *ndirCentR = (TH1D*)ndirCent -> Rebin(5, "ndirCentR", binEdge);
    TH1D *ndirCent_highpTR = (TH1D*)ndirCent_highpT -> Rebin(5, "ndirCent_highpTR", binEdge);
    TH1D *ndirCent_lowpTR = (TH1D*)ndirCent_lowpT -> Rebin(5, "ndirCent_lowpTR", binEdge);

    TH1D *nEventCentR = (TH1D*)nEvntCent -> Rebin(5, "nEvntCentR", binEdge);
    TH1D *avgNcollR = (TH1D*)avgNcoll -> Rebin(5, "avgNcollR", binEdge);

    //Analysis3. Get cent vs pion0(Direct photon)
    //No need to divide centrality width -> Cancel in ratio
    //-----------------------------------------------------
    TH1D *Ypion0 = (TH1D*)npion0CentR -> Clone("Ypion0");
    Ypion0 -> Divide(nEventCentR);

    TH1D *Ypion0_high = (TH1D*)npion0Cent_highpTR -> Clone("Ypion0_highpT");
    Ypion0_high -> Divide(nEventCentR);
    
    TH1D *Ypion0_low = (TH1D*)npion0Cent_lowpTR -> Clone("Ypion0_lowpT");
    Ypion0_low -> Divide(nEventCentR);

    TH1D *Ydir = (TH1D*)ndirCentR -> Clone("Ydir");
    Ydir -> Divide(nEventCentR);

    TH1D *Ydir_high = (TH1D*)ndirCent_highpTR -> Clone("Ydir_highpT");
    Ydir_high -> Divide(nEventCentR);

    TH1D *Ydir_low = (TH1D*)ndirCent_lowpTR -> Clone("Ydir_lowpT");
    Ydir_low -> Divide(nEventCentR);

    //Analysis4. Get Yield/<Ncoll> vs centrality
    //------------------------------------------
    TH1D *YavgNcollPion0 = (TH1D*)Ypion0 -> Clone("YavgNcollPion0_integrated");
    YavgNcollPion0 -> Divide(avgNcollR);

    TH1D *YavgNcollPion0_high = (TH1D*)Ypion0_high -> Clone("YavgNcollPion0_highpT");
    YavgNcollPion0_high -> Divide(avgNcollR);

    TH1D *YavgNcollPion0_low = (TH1D*)Ypion0_low -> Clone("YavgNcollPion0_lowpT");
    YavgNcollPion0_low -> Divide(avgNcollR);


    TH1D *YavgNcollDir = (TH1D*)Ydir -> Clone("YavgNcollDir_integrated");
    YavgNcollDir -> Divide(avgNcollR);

    TH1D *YavgNcollDir_high = (TH1D*)Ydir_high -> Clone("YavgNcollDir_highpT");
    YavgNcollDir_high -> Divide(avgNcollR);

    TH1D *YavgNcollDir_low = (TH1D*)Ydir_low -> Clone("YavgNcollDir_lowpT");
    YavgNcollDir_low -> Divide(avgNcollR);

    //Analysis5. Get gamma and pion0 ratio
    //------------------------------------
    TH1D *gammaOverPion0 = (TH1D*)YavgNcollDir -> Clone("gammaOverPion0_integrated");
    gammaOverPion0 -> Divide(YavgNcollPion0);

    TH1D *gammaOverPion0_high = (TH1D*)YavgNcollDir_high -> Clone("gammaOverPion0_highpT");
    gammaOverPion0_high -> Divide(YavgNcollPion0_high);

    TH1D *gammaOverPion0_low = (TH1D*)YavgNcollDir_low-> Clone("gammaOverPion0_lowpT");
    gammaOverPion0_low -> Divide(YavgNcollPion0_low);


    //Write outputs in outputfile
    //---------------------------
    Ypion0 -> Write();
    Ypion0_high -> Write();
    Ypion0_low -> Write();

    Ydir -> Write();
    Ydir_high -> Write();
    Ydir_low -> Write();

    YavgNcollPion0 -> Write();
    YavgNcollPion0_high -> Write();
    YavgNcollPion0_low -> Write();

    YavgNcollDir -> Write();
    YavgNcollDir_high -> Write();
    YavgNcollDir_low -> Write();

    gammaOverPion0 -> Write();
    gammaOverPion0_high -> Write();
    gammaOverPion0_low -> Write();

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
