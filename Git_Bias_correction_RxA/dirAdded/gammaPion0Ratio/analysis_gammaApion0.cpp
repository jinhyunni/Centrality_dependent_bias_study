void analysis_gammaApion0()
{
    //input
    //-------------------------

    TFile *pion1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");
    TFile *pion2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_allEvents.root", "read");
    TFile *dir2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentDir_integrated.root", "read");

    //output
    //-------------------------
    TFile* output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0.root", "recreate");

    //Input histograms
    //--------------------------
    TH2D *h2centPion0 = (TH2D*)pion1 -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir1 -> Get("centDir");
    TH2D *h2NcollCentPion0 = (TH2D*)pion2 -> Get("ncollCentPion0");
    TH2D *h2NcollCentDir = (TH2D*)dir2 -> Get("ncollCentDir");

    //Analysis1. Projection to get Yield
    //--------------------------
    TH1D *Ypion0Cent = (TH1D*)h2centPion0 -> ProjectionX("pion0_integrated");
    TH1D *Ypion0Cent_highpT = (TH1D*)h2centPion0 -> ProjectionX("pion0_highpT", 201, 1400);
    TH1D *Ypion0Cent_lowpT = (TH1D*)h2centPion0 -> ProjectionX("pino0_lowpT", 1, 200);

    TH1D *YdirCent = (TH1D*)h2centDir -> ProjectionX("dir_integrated");
    TH1D *YdirCent_highpT = (TH1D*)h2centDir -> ProjectionX("dir_highpT", 201, 1400);
    TH1D *YdirCent_lowpT = (TH1D*)h2centDir -> ProjectionX("dir_lowpT", 1, 200);

    TH1D *nEvntCentP = (TH1D*)h2NcollCentPion0 -> ProjectionX();
    TH1D *nEvntCentD = (TH1D*)h2NcollCentDir -> ProjectionX();

    //Analysis2. Rebin to fit cent Class
    //0~10%
    //10~20%
    //20~40%
    //40~60%
    //60~80%
    //--------------------------
    double binEdge[]={0, 10, 20, 40, 60, 80};

    TH1D *Ypion0CentR = (TH1D*)Ypion0Cent -> Rebin(5, "Ypion0CentR", binEdge);
    TH1D *Ypion0Cent_highpTR = (TH1D*)Ypion0Cent_highpT -> Rebin(5, "Ypion0Cent_highpTR", binEdge);
    TH1D *Ypion0Cent_lowpTR = (TH1D*)Ypion0Cent_lowpT -> Rebin(5, "Ypion0Cent_lowpTR", binEdge);

    TH1D *YdirCentR = (TH1D*)YdirCent -> Rebin(5, "YdirCentR", binEdge);
    TH1D *YdirCent_highpTR = (TH1D*)YdirCent_highpT -> Rebin(5, "YdirCent_highpTR", binEdge);
    TH1D *YdirCent_lowpTR = (TH1D*)YdirCent_lowpT -> Rebin(5, "YdirCent_lowpTR", binEdge);


    TH1D *nEventCentPR = (TH1D*)nEvntCentP -> Rebin(5, "nEvntCentPR", binEdge);
    TH1D *nEventCentDR = (TH1D*)nEvntCentD -> Rebin(5, "nEvntCentDR", binEdge);


    //Analysis3. Get cent vs pion0(Direct photon)
    //No need to divide centrality width -> Cancel in ratio
    //--------------------------
    TH1D *Ypion0 = (TH1D*)Ypion0CentR -> Clone("Ypion0");
    Ypion0 -> Divide(nEventCentPR);

    TH1D *Ypion0_high = (TH1D*)Ypion0Cent_highpTR -> Clone("Ypion0_high");
    Ypion0_high -> Divide(nEventCentPR);
    
    TH1D *Ypion0_low = (TH1D*)Ypion0Cent_lowpTR -> Clone("Ypion0_low");
    Ypion0_low -> Divide(nEventCentPR);



    TH1D *Ydir = (TH1D*)YdirCentR -> Clone("Ydir");
    Ydir -> Divide(nEventCentDR);

    TH1D *Ydir_high = (TH1D*)YdirCent_highpTR -> Clone("Ydir_high");
    Ydir_high -> Divide(nEventCentDR);

    TH1D *Ydir_low = (TH1D*)YdirCent_lowpTR -> Clone("Ydir_low");
    Ydir_low -> Divide(nEventCentDR);

    //Analysis4. Get Yield/<Ncoll> vs centrality


 //    //gamma/pion0 ratio by centrality
 //    TH1D *gammaOverPion0 = (TH1D*)Ydir -> Clone("gammaOverPion0");
 //    gammaOverPion0 -> Divide(Ypion0);

    //Write outputs in outputfile
    Ypion0 -> Write();
    Ypion0_high -> Write();
    Ypion0_low -> Write();
    Ydir -> Write();
    Ydir_high -> Write();
    Ydir_low -> Write();
 //    gammaOverPion0 -> Write();

    //Close files
    pion1 -> Close();
    pion2 -> Close();
    dir1 -> Close();
    dir2 -> Close();
    output -> Close();

    //disallocation
    delete pion1;
    delete pion2;
    delete dir1;
    delete dir2;
    delete output;


        
}
