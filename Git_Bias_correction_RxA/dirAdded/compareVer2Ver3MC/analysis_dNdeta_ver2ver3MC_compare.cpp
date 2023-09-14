void analysis_dNdeta_ver2ver3MC_compare()
{
    //input
    //-----
    //TFile *ver2_yield = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_MBevents.root", "read");
    TFile *ver2_yield = new TFile("pAu200GeV_option3_TH2DpTeta_MBevents_fix1.root", "read");
    TFile *ver2_nEvent = new TFile("pAu200GeV_option3_dirAdded_decayOn_Ncoll_MBevents.root", "read");

    TFile *ver3_yield = new TFile("pAu200GeV_kiaf_option3_TH2DpTeta_MBevents.root", "read");
    TFile *ver3_nEvent = new TFile("pAu200GeV_kiaf_option3_Ncoll_MBevents.root", "read");

    //TH2D pTeta of pion0/dirphoton
    TH2D *h2pTeta_pion0_ver2 = (TH2D*)ver2_yield -> Get("pTetaPion0_mb");
    TH2D *h2pTeta_dir_ver2 = (TH2D*)ver2_yield -> Get("pTetaDir_mb");

    TH2D *h2pTeta_pion0_ver3 = (TH2D*)ver3_yield -> Get("pTetaPion0_mb");
    TH2D *h2pTeta_dir_ver3 = (TH2D*)ver3_yield -> Get("pTetaDir_mb");
    
    //TH1D ncoll
    TH1D *ncoll_ver2 = (TH1D*)ver2_nEvent -> Get("ncoll_mb");
    TH1D *ncoll_ver3 = (TH1D*)ver3_nEvent -> Get("ncoll_mb");
    
    //anlysis1. projection to get eta yield
    //projectionX -> num of particle by eta
    //--------------------------------------
    TH1D *h1eta_pion0_ver2 = (TH1D*)h2pTeta_pion0_ver2 -> ProjectionX("h1eta_pion0_ver2");
    TH1D *h1eta_pion0_ver3 = (TH1D*)h2pTeta_pion0_ver3 -> ProjectionX("h1eta_pion0_ver3");

    TH1D *h1eta_dir_ver2 = (TH1D*)h2pTeta_dir_ver2 -> ProjectionX("h1eta_dir_ver2");
    TH1D *h1eta_dir_ver3 = (TH1D*)h2pTeta_dir_ver3 -> ProjectionX("h1eta_dir_ver3");
    
    //analysis2. scailing
    // a. event Num Scaling
    // b. binwidth scaling
    //--------------------
    double nevent_ver2 = ncoll_ver2 -> Integral();
    double nevent_ver3 = ncoll_ver3 -> Integral();
    double binwidth = h1eta_pion0_ver2 -> GetBinWidth(1);

    double scalar_ver2 = (1./(nevent_ver2 * binwidth));
    double scalar_ver3 = (1./(nevent_ver3 * binwidth));

    h1eta_pion0_ver2 -> Scale(scalar_ver2);
    h1eta_dir_ver2 -> Scale(scalar_ver2);
    h1eta_pion0_ver3 -> Scale(scalar_ver3);
    h1eta_dir_ver3 -> Scale(scalar_ver3);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_option3_dNdeta_ver2ver3MC_compare_fix1.root", "recreate");

    h1eta_pion0_ver2 -> Write();
    h1eta_dir_ver2 -> Write();
    h1eta_pion0_ver3 -> Write();
    h1eta_dir_ver3 -> Write();

    output -> Close();




}
