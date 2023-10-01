void analysis_dNdetaCharge_MBevents()
{   
    //input
    //-----
    TFile *input_particle = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_TH3DpTetaCharge_allEvents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver2_option3_NcollCent_allEvents.root", "read");

    TH3D *pTetaCharge = (TH3D*)input_particle -> Get("pTetaCharge_allEvents");
    TH1D *ncollcent_allEvents = (TH1D*)input_ncoll -> Get("ncollCent");

    //Analysis1. Get # of charged particle per eta
    //--------------------------------------------
    TH1D *h1etaCharge = (TH1D*)pTetaCharge -> ProjectionX("h1etaCharage_MBevents");

    //Analysis2. Scaling to get dNdeta
    // 1. eventNum -> Get # of all Events
    // 2. binwidht
    //-----------------------------------
    TH1D *dndeta_charge_MB = (TH1D*)h1etaCharge -> Clone("dndeta_mbevents");

    double nevent = ncollcent_allEvents -> Integral();
    double binwidth = dndeta_charge_MB -> GetBinWidth(1);
    double scalar = 1./(nevent * binwidth);

    dndeta_charge_MB -> Scale(scalar);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_dNdetaCharge_MBevents.root", "recreate");
    dndeta_charge_MB -> Write();
    output -> Close();

}
