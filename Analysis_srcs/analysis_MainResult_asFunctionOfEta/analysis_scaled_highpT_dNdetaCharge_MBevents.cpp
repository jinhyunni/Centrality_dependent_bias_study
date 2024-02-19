void analysis_scaled_highpT_dNdetaCharge_MBevents()
{   
    //input
    //-----
    TFile *input_particle = new TFile("pAu200GeV_p8303ver2_option3_highpT_dNdetaCharge_MBevents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcoll_MBevents.root", "read");

    TH1D *pTetaCharge = (TH1D*)input_particle -> Get("highpT_dndeta_mbevents");
    TProfile *ncollcent_allEvents = (TProfile*)input_ncoll -> Get("avgNcoll_mb");

    //Analysis1. Get # of charged particle per eta
    //--------------------------------------------
    TH1D *dndeta_charge_MB = (TH1D*)pTetaCharge -> Clone("scaled_dndeta_mbevents");
    dndeta_charge_MB -> Scale(1./ncollcent_allEvents -> GetBinContent(1));

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_scaled_highpT_dNdetaCharge_MBevents.root", "recreate");
    dndeta_charge_MB -> Write();
    output -> Close();

}
