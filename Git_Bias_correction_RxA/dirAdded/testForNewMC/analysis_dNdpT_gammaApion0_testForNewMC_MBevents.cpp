void analysis_dNdpT_gammaApion0_testForNewMC_MBevents()
{
    //input
    //-----
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_testForNewMC_MBevents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_Ncoll_testForNewMC_MBevents.root", "read");
        
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


    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdpT_gammaApion0_testForNewMC_MBevents.root", "recreate");
    
    dndpt_pion0_mb -> Write();
    dndpt_dir_mb -> Write();
    
    output -> Close();





}
