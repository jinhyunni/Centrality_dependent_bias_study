void analysis_dNdetaPion0_highpT_byCent_inMidJetEvents()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH3DpTetaPion0_inMidJetEvents.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH3DncollCent_inMidJetEvents.root", "read");
    
    //particle info by mid-jet event
    TH3D *particle[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("pTetaPion0_inMidPion0%dGeV", 2*i+3);
        particle[i] = (TH3D*)input1 -> Get(inputname);
    }

    //ncoll by cent, by mid-jet event
    TH3D *event = (TH3D*)input2 -> Get("ncollCent_inMidJetEvent");

    //Analysis1. Get Particle by eta
    // chargeByeta_midpinon[i][j]
    // i -> indicates mid-jet events class
    // j -> indicates centrality class
    // TH3D -> x: eta y: pT z: centrality
    //------------------------------------
    TH1D *pion0Byeta_midpion0[5][5];

    for(int i=0; i<5; i++)
    {   
        TString outputname1  = Form("pTetaPion0_midpion0_%dGeV_cent1", 2*i+3);
        TString outputname2  = Form("pTetaPion0_midpion0_%dGeV_cent2", 2*i+3);
        TString outputname3  = Form("pTetaPion0_midpion0_%dGeV_cent3", 2*i+3);
        TString outputname4  = Form("pTetaPion0_midpion0_%dGeV_cent4", 2*i+3);
        TString outputname5  = Form("pTetaPion0_midpion0_%dGeV_cent5", 2*i+3);

        pion0Byeta_midpion0[i][0] = (TH1D*)particle[i] -> ProjectionX(outputname1, 301, 2000, 1, 1);
        pion0Byeta_midpion0[i][1] = (TH1D*)particle[i] -> ProjectionX(outputname2, 301, 2000, 2, 2);
        pion0Byeta_midpion0[i][2] = (TH1D*)particle[i] -> ProjectionX(outputname3, 301, 2000, 3, 4);
        pion0Byeta_midpion0[i][3] = (TH1D*)particle[i] -> ProjectionX(outputname4, 301, 2000, 5, 6);
        pion0Byeta_midpion0[i][4] = (TH1D*)particle[i] -> ProjectionX(outputname5, 301, 2000, 7, 8);
    }

    //Analysis2. Get Event number by each case
    // Get Event number by mid-jet event class -> First index
    // Get Event number by centrality class -> Second index
    // TH3D -> x: cent y: ncoll z: event-type
    //-------------------------------------------------------
    TH1D *ncoll_midpion0_cent[5][5];

    for(int i=0; i<5; i++)
    {
        TString outputname1 = Form("eventNum_midpion0_%dGeV_cent1", 2*i+3);
        TString outputname2 = Form("eventNum_midpion0_%dGeV_cent2", 2*i+3);
        TString outputname3 = Form("eventNum_midpion0_%dGeV_cent3", 2*i+3);
        TString outputname4 = Form("eventNum_midpion0_%dGeV_cent4", 2*i+3);
        TString outputname5 = Form("eventNum_midpion0_%dGeV_cent5", 2*i+3);
        
        //                                                                  [cent]  [type]
        ncoll_midpion0_cent[i][0] = (TH1D*)event -> ProjectionY(outputname1, 1, 1, i+1, i+1);
        ncoll_midpion0_cent[i][1] = (TH1D*)event -> ProjectionY(outputname2, 2, 2, i+1, i+1);
        ncoll_midpion0_cent[i][2] = (TH1D*)event -> ProjectionY(outputname3, 3, 4, i+1, i+1);
        ncoll_midpion0_cent[i][3] = (TH1D*)event -> ProjectionY(outputname4, 5, 6, i+1, i+1);
        ncoll_midpion0_cent[i][4] = (TH1D*)event -> ProjectionY(outputname5, 7, 8, i+1, i+1);
    }

    //Analysis3. scale to get dNdeta
    // scale1: event number
    // scale2: binwidth
    //------------------------------
    TH1D *dndeta_pion0_midpion0[5][5];

    //cloning
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            TString outputname = Form("dndeta_midpion0_highpT_%dGeV_cent%d", 2*i+3, j+1);
            dndeta_pion0_midpion0[i][j] = (TH1D*)pion0Byeta_midpion0[i][j] -> Clone(outputname);
        }//j: centrality
    }//: events with jet

    //calculating dNdeta
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            double binwidth = dndeta_pion0_midpion0[i][j] -> GetBinWidth(1);
            double eventNumber = ncoll_midpion0_cent[i][j] -> Integral();
            double scalar = 1./(binwidth * eventNumber);

            dndeta_pion0_midpion0[i][j] -> Scale(scalar);
        }//j: centrality
    }//i: events with jet
    
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_dNdetaPion0_highpT_byCent_inMidJetEvents.root", "recreate");
    for(int i=0; i<5; i++)
    {       
        for(int j=0; j<5; j++)
        {
            dndeta_pion0_midpion0[i][j] -> Write();
        }
    }
    output -> Close();

}
