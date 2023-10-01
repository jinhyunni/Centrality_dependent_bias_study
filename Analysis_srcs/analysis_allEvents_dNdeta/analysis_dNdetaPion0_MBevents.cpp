void analysis_dNdetaPion0_MBevents()
{   
    //input
    //-----
    TFile *input_particle = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_TH3DpTetaPion0_allEvents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_NcollCent_allEvents.root", "read");

    TH3D *pTetaPion0 = (TH3D*)input_particle -> Get("pTetaPion0_allEvents");
    TH1D *ncollcent_allEvents = (TH1D*)input_ncoll -> Get("ncollCent");

    //Analysis1. Get # of charged particle per eta
    //--------------------------------------------
    TH1D *h1etaPion0 = (TH1D*)pTetaPion0 -> ProjectionX("h1etaCharage_MBevents");

    //Analysis2. Scaling to get dNdeta
    // 1. eventNum -> Get # of all Events
    // 2. binwidht
    //-----------------------------------
    TH1D *dndeta_pion0_MB = (TH1D*)h1etaPion0 -> Clone("dndeta_mbevents");

    double nevent = ncollcent_allEvents -> Integral();
    double binwidth = dndeta_pion0_MB -> GetBinWidth(1);
    double scalar = 1./(nevent * binwidth);

    dndeta_pion0_MB -> Scale(scalar);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver3_option3_dNdetaPion0_MBevents.root", "recreate");
    dndeta_pion0_MB -> Write();
    output -> Close();

}
