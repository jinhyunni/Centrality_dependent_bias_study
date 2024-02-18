void analysis_pion0_dNdpT_MBevents()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_TH2DpTeta_midrapidity_MBevents.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver5_option3_Ncoll_MBevents.root", "read");
    TFile *input3 = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_avgNcoll.root", "read");
        
    TH2D *h2pTetaPion0 = (TH2D*)input1 -> Get("pTetaPion0_mb");
    TH1D *h1ncoll = (TH1D*)input2 -> Get("ncoll_mb");

	TProfile *avgNcoll = (TProfile*)input3 -> Get("avgNcoll_mb");

    //Analysis1. Project to y to get number of particle by pT
    //----------------------------------------------------------
    TH1D *numPion0pT = (TH1D*)h2pTetaPion0 -> ProjectionY("numPion0pT");
    
    //Analysis2. Scale event number
    //-------------------------------
    TH1D *numPion0pT_perEvent = (TH1D*)numPion0pT -> Clone("yieldPion0pT_mb");
    numPion0pT_perEvent -> Scale(1./h1ncoll -> Integral());
    
    //Analysis3. Rebin for pT, divde binwidht to get dndpT
    //------------------------------------------------------
    //double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0};
    double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.0, 9.0, 11.0, 15.0, 20.0};   //11 binning

    TH1D *dndpt_pion0_mb = (TH1D*)numPion0pT_perEvent -> Rebin(11, "dNdpt_pion0_mb", pTrange);
	
    //scaling binwidth to get dNdpT
    for(int i=0; i<11; i++)
    {
        double binwidth = dndpt_pion0_mb -> GetBinWidth(i+1);
		
		//scale variable binwidth
        dndpt_pion0_mb -> SetBinContent(i+1, dndpt_pion0_mb -> GetBinContent(i+1)/binwidth);
        dndpt_pion0_mb -> SetBinError(i+1, dndpt_pion0_mb -> GetBinError(i+1)/binwidth);		   
	}

    
    //Analysis4. average Ncoll Scaling
    //--------------------------------
    TH1D *YavgNcollpT_pion0 = (TH1D*)dndpt_pion0_mb -> Clone("YavgNcollPion0pT_mb");
    YavgNcollpT_pion0 -> Scale(1./avgNcoll -> GetBinContent(1));

    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_pion0_dNdpT_MBevents.root", "recreate");
    
	numPion0pT_perEvent -> Write();
	dndpt_pion0_mb -> Write();
	YavgNcollpT_pion0 -> Write();
   
    output -> Close();





}
