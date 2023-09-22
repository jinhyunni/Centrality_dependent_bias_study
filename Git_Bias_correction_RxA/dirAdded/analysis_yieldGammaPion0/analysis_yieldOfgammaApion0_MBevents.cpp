void analysis_yieldOfgammaApion0_MBevents()
{
    //input
    //-----
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_MBevents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_Ncoll_MBevents.root", "read");
    TFile *input3 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCent_allEvents.root", "read");
        
    TH2D *h2pTetaPion0 = (TH2D*)input1 -> Get("pTetaPion0_mb");
    TH2D *h2pTetaDir = (TH2D*)input1 -> Get("pTetaDir_mb");
    TH1D *h1ncoll = (TH1D*)input2 -> Get("ncoll_mb");

    //Analysis1-11. Project to y to get number of particle by pT
    //----------------------------------------------------------
    TH1D *numPion0pT = (TH1D*)h2pTetaPion0 -> ProjectionY("numPion0pT");
    TH1D *numDirpT = (TH1D*)h2pTetaDir -> ProjectionY("numDirpT");
    
    //Analysis1-2. Scale event number
    //-------------------------------
    TH1D *numPion0pT_perEvent = (TH1D*)numPion0pT -> Clone("numPion0pT_perEvent");
    TH1D *numDirpT_perEvent = (TH1D*)numDirpT -> Clone("numDirpT_perEvent");

    numPion0pT_perEvent -> Scale(1./h1ncoll -> Integral());
    numDirpT_perEvent -> Scale(1./h1ncoll -> Integral());
    
    //Analysis1-3. Rebin for pT, divde binwidht to get dndpt
    //------------------------------------------------------
    double pTrange[] = {0, 0.5, 1, 1.5, 2, 3, 4.0, 5.0, 7.0, 10.0, 15.0};   //10 binning

    TH1D *dndpt_pion0_mb = (TH1D*)numPion0pT_perEvent -> Rebin(10, "dndpt_pion0_mb", pTrange);
    TH1D *dndpt_dir_mb = (TH1D*)numDirpT_perEvent -> Rebin(10, "dndpt_dir_mb", pTrange);
    
    //scaling binwidth to get dNdpt
    for(int i=0; i<10; i++)
    {
        double binwidth = dndpt_pion0_mb -> GetBinWidth(i+1);

        dndpt_pion0_mb -> SetBinContent(i+1, dndpt_pion0_mb -> GetBinContent(i+1)/binwidth);
        dndpt_pion0_mb -> SetBinError(i+1, dndpt_pion0_mb -> GetBinError(i+1)/binwidth);

        dndpt_dir_mb -> SetBinContent(i+1, dndpt_dir_mb -> GetBinContent(i+1)/binwidth);
        dndpt_dir_mb -> SetBinError(i+1, dndpt_dir_mb -> GetBinError(i+1)/binwidth);
    }


    //Analysis2-1. Project to x to get the number of particle by eta
    //--------------------------------------------------------------
    TH1D *numPion0eta = (TH1D*)h2pTetaPion0 -> ProjectionX("numPion0eta");
    TH1D *numDireta = (TH1D*)h2pTetaDir -> ProjectionX("numDireta");

    //Analysis2-2. Scale event number
    //-------------------------------
    TH1D *numPion0eta_perEvent = (TH1D*)numPion0eta -> Clone("numPion0eta_perEvent");
    TH1D *numDireta_perEvent = (TH1D*)numDireta -> Clone("numDireta_perEvent");

    numPion0eta_perEvent -> Scale(1./h1ncoll -> Integral());
    numDireta_perEvent -> Scale(1./h1ncoll -> Integral());

    //Analsysis2-3. Divide eta-binwidh
    //24-bins, -6~6
    //binwidth = 0.5
    //---------------------------------
    TH1D *dndeta_pion0_mb = (TH1D*)numPion0eta_perEvent -> Clone("dndeta_pion0_mb");
    TH1D *dndeta_dir_mb = (TH1D*)numDireta_perEvent -> Clone("dndeta_dir_mb");
    
    dndeta_pion0_mb -> Scale(2);
    dndeta_dir_mb -> Scale(2);
    
    //Analysis3. average Ncoll Scaling
    //--------------------------------
    double allEvents[] = {0, 110};
    TProfile *avgNcollCent = (TProfile*)input3 -> Get("avgNcollCent");
    TProfile *avgNcoll = (TProfile*)avgNcollCent -> Rebin(1, "avgNcoll_mb", allEvents);

    //Y/<Ncoll> vs pT in MB
    TH1D *YavgNcollpT_pion0 = (TH1D*)dndpt_pion0_mb -> Clone("YavgNcollpT_pion0_mb");
    YavgNcollpT_pion0 -> Scale(1./avgNcoll -> GetBinContent(1));

    TH1D *YavgNcollpT_dir = (TH1D*)dndpt_dir_mb -> Clone("YavgNcollpT_dir_mb");
    YavgNcollpT_dir -> Scale(1./avgNcoll -> GetBinContent(1));

    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_MBevents.root", "recreate");
    
    dndpt_pion0_mb -> Write();
    dndpt_dir_mb -> Write();
    dndeta_pion0_mb -> Write();
    dndeta_dir_mb -> Write();
    YavgNcollpT_pion0 -> Write();
    YavgNcollpT_dir -> Write();
    numPion0eta -> Write();
    numDireta -> Write();

    output -> Close();





}
