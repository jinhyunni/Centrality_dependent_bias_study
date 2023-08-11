void analysis_gammaApion0avgNcoll()
{
    //input
    //-------------------------

    TFile *pion1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");
    TFile *pion2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0.root", "read");
    TFile *dir2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentDir.root", "read");

    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentPion0.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentDir.root", "read");

    //output
    //-------------------------
    TFile* output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0avgNcoll.root", "recreate");

    //Input histograms
    //--------------------------
    TH2D *h2centPion0 = (TH2D*)pion1 -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir1 -> Get("centDir");
    TH2D *h2NcollCentPion0 = (TH2D*)pion2 -> Get("ncollCentPion0");
    TH2D *h2NcollCentDir = (TH2D*)dir2 -> Get("ncollCentDir");

    TProfile *avgNcollCentPion0 = (TProfile*)input1 -> Get("avgNcollCentPion0");
    TProfile *avgNcollCentDir = (TProfile*)input2 -> Get("avgNcollCentDir");

    //Analysis1. Projection to get Yield
    //--------------------------
    TH1D *Ypion0Cent = (TH1D*)h2centPion0 -> ProjectionX();
    TH1D *YdirCent = (TH1D*)h2centDir -> ProjectionX();
    TH1D *nEvntCentP = (TH1D*)h2NcollCentPion0 -> ProjectionX();
    TH1D *nEvntCentD = (TH1D*)h2NcollCentDir -> ProjectionX();

    TH1D *avgNcollPion0 = new TH1D("avgNcollPion0", "", 11, 0, 110);
    TH1D *avgNcollDir = new TH1D("avgNcollDir", "", 11, 0, 110);
    
    //Make TH1D of avgNcoll vs Centrality_pion0, dirphoton
    for(int i=0; i<11; i++)
    {
        //make TH1D of <Ncoll> vs centrality, pion0
        avgNcollPion0 -> SetBinContent(i+1, avgNcollCentPion0 -> GetBinContent(i+1));
        avgNcollPion0 -> SetBinError(i+1, avgNcollCentPion0 -> GetBinError(i+1));
        
        //make TH1D of <Ncoll> vs centrality, dir
        avgNcollDir -> SetBinContent(i+1, avgNcollCentDir -> GetBinContent(i+1));
        avgNcollPion0 -> SetBinError(i+1, avgNcollCentDir -> GetBinError(i+1));
    }

    //Analysis2. Rebin to fit cent Class
    //0~10%
    //10~20%
    //20~40%
    //40~60%
    //60~80%
    //--------------------------
    double binEdge[]={0, 10, 20, 40, 60, 80};

    TH1D *Ypion0CentR = (TH1D*)Ypion0Cent -> Rebin(5, "Ypion0CentR", binEdge);
    TH1D *YdirCentR = (TH1D*)YdirCent -> Rebin(5, "YdirCentR", binEdge);
    TH1D *nEventCentPR = (TH1D*)nEvntCentP -> Rebin(5, "nEvntCentPR", binEdge);
    TH1D *nEventCentDR = (TH1D*)nEvntCentD -> Rebin(5, "nEvntCentDR", binEdge);
    TH1D *avgNcollPion0R = (TH1D*)avgNcollPion0 -> Rebin(5, "avgNcollPion0R", binEdge);
    TH1D *avgNcollDirR = (TH1D*)avgNcollDir -> Rebin(5, "avgNcollDirR", binEdge);


    //Analysis3. Get cent vs pion0(Direct photon)
    //No need to divide centrality width -> Cancel in ratio
    //--------------------------
    TH1D *Ypion0 = (TH1D*)Ypion0CentR -> Clone("yieldAvgNcoll_pion0");
    Ypion0 -> Divide(nEventCentPR);
    Ypion0 -> Divide(avgNcollPion0R);
    Ypion0 -> GetXaxis() -> SetTitle("Centrality(%)");
    Ypion0 -> GetYaxis() -> SetTitle("Y^{#pi^{0}}/#LTN_{coll}#GT");

    TH1D *Ydir = (TH1D*)YdirCentR -> Clone("yieldAvgNcoll_dir");
    Ydir -> Divide(nEventCentDR);
    Ydir -> Divide(avgNcollDirR);
    Ydir -> GetXaxis() -> SetTitle("Centrality(%)");
    Ydir -> GetYaxis() -> SetTitle("Y^{#gamma^{dir}}/#LTN_{coll}#GT");

    //gamma/pion0 ratio by centrality
    TH1D *gammaOverPion0 = (TH1D*)Ydir -> Clone("gammaOverPion0_avgNcoll");
    gammaOverPion0 -> Divide(Ypion0);

    //Write outputs in outputfile
    Ypion0 -> Write();
    Ydir -> Write();
    gammaOverPion0 -> Write();

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
