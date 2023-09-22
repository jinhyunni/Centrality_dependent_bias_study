void analysis_hardEventRatioByCent_inTargetEvents()
{
    //input
    //input1: Ncoll of target events vs cent
    //input2: Ncoll of target events with high-pT chage at forward vs cent
    //                                  * high-pT: more than 2 GeV`
    //--------------------------------------------------------------------

    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCent_inTargetEvents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_hardEvent_inTargetEvents.root", "read");

    TH2D *h2ncollcent_mb = (TH2D*)input1 -> Get("ncollCent_mb");
    TH2D *h2ncollcent_pion0 = (TH2D*)input1 -> Get("ncollCent_pion0");
    TH2D *h2ncollcent_dir = (TH2D*)input1 -> Get("ncollCent_dDir");

    TH2D *h2ncollcent_mb_hardCharge = (TH2D*)input2 -> Get("ncollCent_mb_hardCharge");
    TH2D *h2ncollcent_pion0_hardCharge = (TH2D*)input2 -> Get("ncollCent_pion0_hardCharge");
    TH2D *h2ncollcent_dir_hardCharge = (TH2D*)input2 -> Get("ncollCent_dDir_hardCharge");

    //Analysis1. Get # of event by cent by target events
    //TH2D -> ProjectionX() : # of events by centrality
    //---------------------------------------------------
    TH1D *nEventcent_mb = (TH1D*)h2ncollcent_mb -> ProjectionX();
    TH1D *nEventcent_pion0 = (TH1D*)h2ncollcent_pion0 -> ProjectionX();
    TH1D *nEventcent_dir = (TH1D*)h2ncollcent_dir -> ProjectionX();

    TH1D *hardEvent_mb = (TH1D*)h2ncollcent_mb_hardCharge -> ProjectionX();
    TH1D *hardEvent_pion0 = (TH1D*)h2ncollcent_pion0_hardCharge -> ProjectionX();
    TH1D *hardEvent_dir = (TH1D*)h2ncollcent_dir_hardCharge -> ProjectionX();
    
    //Analysis2. Get ratio of hard-events by centrality
    //hardEvent_~ -> Clone()
    //hardEvent_cloned_~ -> Divide(nEventcent_~);
    //-------------------------------------------------
    TH1D *hardRatio_mb = (TH1D*)hardEvent_mb -> Clone("hardRatio_mb");
    hardRatio_mb -> Divide(nEventcent_mb);

    TH1D *hardRatio_pion0 = (TH1D*)hardEvent_pion0 -> Clone("hardRatio_pion0");
    hardRatio_pion0 -> Divide(nEventcent_pion0);

    TH1D *hardRatio_dir = (TH1D*)hardEvent_dir -> Clone("hardRatio_dir");
    hardRatio_dir -> Divide(nEventcent_dir);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_option3_dirAdded_decayOn_hardEventRatioByCent.root", "recreate");

    hardRatio_mb -> Write();
    hardRatio_pion0 -> Write();
    hardRatio_dir -> Write();

    output -> Close();
    
    delete input1;
    delete input2;
    delete output;


}
