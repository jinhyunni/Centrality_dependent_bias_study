void analysis_scaled_dNdetaCharge_byCent_allEvents()
{   
    //input
    //-----
    TFile *input_particle = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH3DpTetaCharge_allEvents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");
    TFile *input_avgncoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");

    TH3D *pTetaCharge = (TH3D*)input_particle -> Get("pTetaCharge_allEvents");
    TH2D *ncollcent_allEvents = (TH2D*)input_ncoll -> Get("ncollCent");
    TProfile *avgNcollCent = (TProfile*)input_avgncoll -> Get("avgNcollCent");

    //Analysis1. Get # of charged particle per eta
    // x: eta y: pT z: centrality
    //--------------------------------------------

    TH1D *h1etaCharge[5];

    h1etaCharge[0] = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharge_cent1", 1, 2000, 1, 1);
    h1etaCharge[1] = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharge_cent2", 1, 2000, 2, 2);
    h1etaCharge[2] = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharge_cent3", 1, 2000, 3, 4);
    h1etaCharge[3] = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharge_cent4", 1, 2000, 5, 6);
    h1etaCharge[4] = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharge_cent5", 1, 2000, 7, 8);

    TH1D *scaled_dndeta_charge_cent[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("scaled_dndeta_allEvents_cent%d", i+1);
        scaled_dndeta_charge_cent[i] = (TH1D*)h1etaCharge[i] -> Clone(inputname);
    }


    //Analysis2. Scaling to get dNdeta
    // 1. eventNum -> Get # of events per centrality
    // 2. binwidth
    // x: centrality y: ncoll
    //-----------------------------------
    
    double centrange[] = {0, 10, 20, 40, 60, 80};

    TH1D *ncollcent = (TH1D*)ncollcent_allEvents -> ProjectionX("eventNum_byCent"); 
    TH1D *ncollcentR = (TH1D*)ncollcent -> Rebin(5, "ncollcentR", centrange);

    TProfile *avgncollcentR = (TProfile*)avgNcollCent -> Rebin(5, "avgNcollCentR", centrange);

    for(int i=0; i<5; i++)
    {   
        //scaling factor to get dNdeta by cent
        double eventNum = ncollcentR -> GetBinContent(i+1);
        double binwidth = scaled_dndeta_charge_cent[i] -> GetBinWidth(1);

        //scaling factor of <Ncoll>
        double avgNcollbyCent = avgncollcentR -> GetBinContent(i+1);

        double scalar = 1./(eventNum * binwidth * avgNcollbyCent);

        scaled_dndeta_charge_cent[i] -> Scale(scalar);

    }

   

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_scaled_dNdetaCharge_byCent_allEvents.root", "recreate");

   for(int i=0; i<5; i++)
   {
        scaled_dndeta_charge_cent[i] -> Write();
   }

    output -> Close();

}
