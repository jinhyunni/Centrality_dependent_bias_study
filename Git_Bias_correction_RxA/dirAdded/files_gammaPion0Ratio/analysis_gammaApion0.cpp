void analysis_gammaApion0()
{
    //input
    //-------------------------

    TFile *pion1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");
    TFile *pion2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0.root", "read");
    TFile *dir2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentDir.root", "read");

    //output
    //-------------------------
    TFile* output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0.root", "recreate");

    //histograms
    //--------------------------
    TH2D *h2centPion0 = (TH2D*)pion1 -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir1 -> Get("centDir");
    TH2D *h2NcollCentPion0 = (TH2D*)pion2 -> Get("ncollCentPion0");
    TH2D *h2NcollCentDir = (TH2D*)dir2 -> Get("ncollCentDir");

    //Projection to get Yield
    //--------------------------
    TH1D *Ypion0Cent = (TH1D*)h2centPion0 -> ProjectionX();
    TH1D *YdirCent = (TH1D*)h2centDir -> ProjectionX();
    TH1D *nEvntCentP = (TH1D*)h2NcollCentPion0 -> ProjectionX();
    TH1D *nEvntCentD = (TH1D*)h2NcollCentDir -> ProjectionX();

    //Rebin to fit cent Class
    //0~10%
    //10~20%
    //20~40%
    //40~60%
    //60~80%
    //--------------------------
    double binEdge[]={0, 10, 20, 40, 60, 80};

    TH1D *Ypion0CentR = (TH1D*)Ypion0Cent -> Rebin(5, "Ypion0CentR", binEdge);
    TH1D *YdirCentR = (TH1D*)YdirCent -> Rebin(5, "YdirCentR", binEdge);
    TH1D *nEvntCentPR = (TH1D*)nEvntCentP -> Rebin(5, "nEvntCentPR", binEdge);
    TH1D *nEvntCentDR = (TH1D*)nEvntCentD -> Rebin(5, "nEvntCentDR", binEdge);


    //Get cent vs pion0(Direct photon)
    //No need to divide centrality width -> Cancle in double ratio
    TH1D *Ypion0 = new TH1D("Ypion0", "", 5, 0, 80);
    (*Ypion0) = (*Ypion0CentR)/(*nEvntCentPR);
    
 //  Ypion0 -> Draw();

    TH1D *Ydir = new TH1D("Ydir", "", 5, 0, 80);
    (*Ydir)=(*YdirCentR)/(*nEvntCentDR);
    
    Ydir -> Draw();

    //gamma/pion0 ratio by centrality
    TH1D *gammaOverPion0 = new TH1D("gammaOverPion0", "", 5, 0, 80);
    (*gammaOverPion0) = (*Ydir)/(*Ypion0);

        


}
