void analysis_dNdetaPion0_byCent_allEvents()
{   
    //input
    //-----
    TFile *input_particle = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_TH3DpTetaPion0_allEvents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_NcollCent_allEvents.root", "read");

    TH3D *pTetaPion0 = (TH3D*)input_particle -> Get("pTetaPion0_allEvents");
    TH2D *ncollcent_allEvents = (TH2D*)input_ncoll -> Get("ncollCent");

    //Analysis1. Get # of charged particle per eta
    // x: eta y: pT z: centrality
    //--------------------------------------------

    TH1D *h1etaPion0[5];

    h1etaPion0[0] = (TH1D*)pTetaPion0 -> ProjectionX("h1etaPion0_cent1", 1, 2000, 1, 1);
    h1etaPion0[1] = (TH1D*)pTetaPion0 -> ProjectionX("h1etaPion0_cent2", 1, 2000, 2, 2);
    h1etaPion0[2] = (TH1D*)pTetaPion0 -> ProjectionX("h1etaPion0_cent3", 1, 2000, 3, 4);
    h1etaPion0[3] = (TH1D*)pTetaPion0 -> ProjectionX("h1etaPion0_cent4", 1, 2000, 5, 6);
    h1etaPion0[4] = (TH1D*)pTetaPion0 -> ProjectionX("h1etaPion0_cent5", 1, 2000, 7, 8);

    //Analysis2. Scaling to get dNdeta
    // 1. eventNum -> Get # of events per centrality
    // 2. binwidth
    // x: centrality y: ncoll
    //-----------------------------------
    
    TH1D *dndeta_pion0_cent[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("dndeta_allEvents_cent%d", i+1);
        dndeta_pion0_cent[i] = (TH1D*)h1etaPion0[i] -> Clone(inputname);
    }

    TH1D *ncollcent = (TH1D*)ncollcent_allEvents -> ProjectionX("eventNum_byCent");    
    double eventnum_bycent[5];

    eventnum_bycent[0] = ncollcent -> GetBinContent(1);
    eventnum_bycent[1] = ncollcent -> GetBinContent(2);
    eventnum_bycent[2] = ncollcent -> GetBinContent(3) + ncollcent -> GetBinContent(4);
    eventnum_bycent[3] = ncollcent -> GetBinContent(5) + ncollcent -> GetBinContent(6);
    eventnum_bycent[4] = ncollcent -> GetBinContent(7) + ncollcent -> GetBinContent(8);

    for(int i=0; i<5; i++)
    {   
        double binwidth = dndeta_pion0_cent[i] -> GetBinWidth(1);
        double scalar = 1./(eventnum_bycent[i] * binwidth);

        dndeta_pion0_cent[i] -> Scale(scalar);

    }

   

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver3_option3_dNdetaPion0_byCent_allEvents.root", "recreate");

   for(int i=0; i<5; i++)
   {
        dndeta_pion0_cent[i] -> Write();
   }

    output -> Close();

}
