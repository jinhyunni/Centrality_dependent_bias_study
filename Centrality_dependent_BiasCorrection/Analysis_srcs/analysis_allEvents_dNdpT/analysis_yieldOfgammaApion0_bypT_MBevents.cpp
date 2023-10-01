void analysis_yieldOfgammaApion0_bypT_MBevents()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_TH2DpTeta_midrapidity_MBevents.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_Ncoll_MBevents.root", "read");
    TFile *input3 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcoll_MBevents.root", "read");
        
    TH2D *h2pTetaPion0 = (TH2D*)input1 -> Get("pTetaPion0_mb");
    TH2D *h2pTetaDir = (TH2D*)input1 -> Get("pTetaDir_mb");
    TH1D *h1ncoll = (TH1D*)input2 -> Get("ncoll_mb");

	TProfile *avgNcoll = (TProfile*)input3 -> Get("avgNcoll_mb");

    //Analysis1-1. Project to y to get number of particle by pT
    //----------------------------------------------------------
    TH1D *numPion0pT = (TH1D*)h2pTetaPion0 -> ProjectionY("numPion0pT");
    TH1D *numDirpT = (TH1D*)h2pTetaDir -> ProjectionY("numDirpT");
    
    //Analysis1-2. Scale event number
    //-------------------------------
    TH1D *numPion0pT_perEvent = (TH1D*)numPion0pT -> Clone("yieldPion0pT_mb");
    TH1D *numDirpT_perEvent = (TH1D*)numDirpT -> Clone("yieldDirpT_mb");

    numPion0pT_perEvent -> Scale(1./h1ncoll -> Integral());
    numDirpT_perEvent -> Scale(1./h1ncoll -> Integral());
    
    //Analysis2. Rebin for pT, divde binwidht to get dndpt
    //------------------------------------------------------
    //double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0};
    double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.0, 9.0, 11.0, 15.0, 20.0};   //11 binning

    TH1D *dndpt_pion0_mb = (TH1D*)numPion0pT_perEvent -> Rebin(11, "dNdpt_pion0_mb", pTrange);
    TH1D *dndpt_dir_mb = (TH1D*)numDirpT_perEvent -> Rebin(11, "dNdpt_dir_mb", pTrange);
	
    //scaling binwidth to get dNdpt
    for(int i=0; i<11; i++)
    {
        double binwidth = dndpt_pion0_mb -> GetBinWidth(i+1);
		
		//set bin content
        dndpt_pion0_mb -> SetBinContent(i+1, dndpt_pion0_mb -> GetBinContent(i+1)/binwidth);
        dndpt_pion0_mb -> SetBinError(i+1, dndpt_pion0_mb -> GetBinError(i+1)/binwidth);
		
		//set bin error
        dndpt_dir_mb -> SetBinContent(i+1, dndpt_dir_mb -> GetBinContent(i+1)/binwidth);
        dndpt_dir_mb -> SetBinError(i+1, dndpt_dir_mb -> GetBinError(i+1)/binwidth);
    }

    
    //Analysis3. average Ncoll Scaling
    //--------------------------------
    TH1D *YavgNcollpT_pion0 = (TH1D*)dndpt_pion0_mb -> Clone("YavgNcollPion0pT_mb");
    YavgNcollpT_pion0 -> Scale(1./avgNcoll -> GetBinContent(1));

    TH1D *YavgNcollpT_dir = (TH1D*)dndpt_dir_mb -> Clone("YavgNcollDirpT_mb");
    YavgNcollpT_dir -> Scale(1./avgNcoll -> GetBinContent(1));

    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_MBevents.root", "recreate");
    
	numPion0pT_perEvent -> Write();
	dndpt_pion0_mb -> Write();
	YavgNcollpT_pion0 -> Write();
	
	numDirpT_perEvent -> Write();
	dndpt_dir_mb -> Write();
	YavgNcollpT_dir -> Write();
   
    output -> Close();





}
