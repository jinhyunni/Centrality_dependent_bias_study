void analysis_YieldByCentrality()
{
    TFile *input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_nEventCent_InEtaRange_Pion0.root", "read");

    
    //Target particle: pion0(111)
    TH2D *h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
    TH2D *h2ncollcent = (TH2D*)input2 -> Get("ncoll_cent");

    //projections
    TH1D *h1yieldCent = (TH1D*)h2pTcent -> ProjectionX();
    TH1D *h1nEventCent = (TH1D*)h2ncollcent -> ProjectionX();


    //Rebin to fit centrality class
    //0~10%
    //10~20%
    //20~40%
    //40~60%
    //60~80%

    double binX[]={0, 10, 20, 40, 60, 80};

    TH1D *h1yieldCentR = (TH1D*)h1yieldCent -> Rebin(5 ,"h1yieldCentR", binX);
    TH1D *h1nEventCentR = (TH1D*)h1nEventCent -> Rebin(5 ,"h1yieldCentR", binX);


    //dive two to get yield of pion0 by centrality
    TH1D *yield = (TH1D*)h1yieldCentR->Clone("yield");
    yield -> Divide(h1nEventCentR);

    TFile *output = new TFile("pAu200GeV_option3_pion0YieldCent_newest.root", "recreate");
    yield -> Write();
    output -> Close();
    
    input1 -> Close();
    input2 -> Close();

    delete output;
    delete input1;
    delete input2;
}
