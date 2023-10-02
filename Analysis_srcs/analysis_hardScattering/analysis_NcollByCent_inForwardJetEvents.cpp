void analysis_NcollByCent_inForwardJetEvents()
{
    //input
    //-----
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH3DncollCent_inForwardJetEvents.root", "read");
    
    //ncoll by cent, by mid-jet event
    TH3D *event = (TH3D*)input2 -> Get("ncollCent_inForwardJetEvent");

    //Analysis1. Get Ncoll By cent,  by each case
    // Get Event number by mid-jet event class -> First index
    // Get Event number by centrality class -> Second index
    // TH3D -> x: cent y: ncoll z: event-type
    //-------------------------------------------------------
    TH1D *ncoll_forwardCharge_cent[5][5];

    for(int i=0; i<5; i++)
    {
        TString outputname1 = Form("ncoll_forwardCharge_%dGeV_cent1", 2*i+3);
        TString outputname2 = Form("ncoll_forwardCharge_%dGeV_cent2", 2*i+3);
        TString outputname3 = Form("ncoll_forwardCharge_%dGeV_cent3", 2*i+3);
        TString outputname4 = Form("ncoll_forwardCharge_%dGeV_cent4", 2*i+3);
        TString outputname5 = Form("ncoll_forwardCharge_%dGeV_cent5", 2*i+3);
        
        //                                                                       [cent]  [type]
        ncoll_forwardCharge_cent[i][0] = (TH1D*)event -> ProjectionY(outputname1, 1, 1, i+1, i+1);
        ncoll_forwardCharge_cent[i][1] = (TH1D*)event -> ProjectionY(outputname2, 2, 2, i+1, i+1);
        ncoll_forwardCharge_cent[i][2] = (TH1D*)event -> ProjectionY(outputname3, 3, 4, i+1, i+1);
        ncoll_forwardCharge_cent[i][3] = (TH1D*)event -> ProjectionY(outputname4, 5, 6, i+1, i+1);
        ncoll_forwardCharge_cent[i][4] = (TH1D*)event -> ProjectionY(outputname5, 7, 8, i+1, i+1);
    }

  
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_NcollByCent_inForwardJetEvents.root", "recreate");
    for(int i=0; i<5; i++)
    {       
        for(int j=0; j<5; j++)
        {
            ncoll_forwardCharge_cent[i][j] -> Write();
        }
    }
    output -> Close();

}
