/*
    TestFile for MC validation check

    input1: ver2. MC
    input2: ver3. MC
    input3: ver3. testMC
*/


void analysis_dNdpT_ver2ver3MC_compare()
{
    //input
    //-----
    TFile *ver2_yield = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_MBevents.root", "read");
    TFile *ver2_nEvent = new TFile("pAu200GeV_option3_dirAdded_decayOn_Ncoll_MBevents.root", "read");

    TFile *ver3_yield = new TFile("pAu200GeV_kiaf_option3_TH2DpTeta_MBevents.root", "read");
    TFile *ver3_nEvent = new TFile("pAu200GeV_kiaf_option3_Ncoll_MBevents.root", "read");

    TFile *ver3_test_yield = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_testForNewMC_MBevents.root", "read");
    TFile *ver3_test_nEvent = new TFile("pAu200GeV_option3_dirAdded_decayOn_Ncoll_testForNewMC_MBevents.root", "read");

    TFile *ver3_nplRootOnly_yield = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DpTeta_ver3rootOnly_MBevents.root", "read");


    //TH2D pTeta of pion0/dirphoton
    TH2D *h2pTeta_pion0_ver2 = (TH2D*)ver2_yield -> Get("pTetaPion0_mb");
    TH2D *h2pTeta_dir_ver2 = (TH2D*)ver2_yield -> Get("pTetaDir_mb");

    TH2D *h2pTeta_pion0_ver3 = (TH2D*)ver3_yield -> Get("pTetaPion0_mb");
    TH2D *h2pTeta_dir_ver3 = (TH2D*)ver3_yield -> Get("pTetaDir_mb");

    TH2D *h2pTeta_pion0_ver3_test = (TH2D*)ver3_test_yield -> Get("pTetaPion0_mb");
    TH2D *h2pTeta_dir_ver3_test = (TH2D*)ver3_test_yield -> Get("pTetaDir_mb");
    
    //TH1D ncoll
    TH1D *ncoll_ver2 = (TH1D*)ver2_nEvent -> Get("ncoll_mb");
    TH1D *ncoll_ver3 = (TH1D*)ver3_nEvent -> Get("ncoll_mb");
    TH1D *ncoll_ver3_test = (TH1D*)ver3_test_nEvent -> Get("ncoll_mb");
    
    //anlysis1. projection to get pT yield
    //projectionY -> num of particle by pT
    //--------------------------------------
    TH1D *h1pT_pion0_ver2 = (TH1D*)h2pTeta_pion0_ver2 -> ProjectionY("h1pT_pion0_ver2");
    TH1D *h1pT_pion0_ver3 = (TH1D*)h2pTeta_pion0_ver3 -> ProjectionY("h1pT_pion0_ver3");
    TH1D *h1pT_pion0_ver3_test = (TH1D*)h2pTeta_pion0_ver3_test -> ProjectionY("h1pT_pion0_ver3_test");
    

    TH1D *h1pT_dir_ver2 = (TH1D*)h2pTeta_dir_ver2 -> ProjectionY("h1pT_dir_ver2");
    TH1D *h1pT_dir_ver3 = (TH1D*)h2pTeta_dir_ver3 -> ProjectionY("h1pT_dir_ver3");
    TH1D *h1pT_dir_ver3_test = (TH1D*)h2pTeta_dir_ver3_test -> ProjectionY("h1pT_dir_ver3_test");

    //analysis3. pT rebinning
    //-----------------------
    
    TH1D *yields[6];

    double pTrange[] = {0, 0.5, 1, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0}; //10 binning

    TH1D *h1pT_pion0_ver2R = (TH1D*)h1pT_pion0_ver2 -> Rebin(10, "h1pT_pion0_ver2R", pTrange);
    TH1D *h1pT_pion0_ver3R = (TH1D*)h1pT_pion0_ver3 -> Rebin(10, "h1pT_pion0_ver3R", pTrange);
    TH1D *h1pT_pion0_ver3R_test = (TH1D*)h1pT_pion0_ver3_test -> Rebin(10, "h1pT_pion0_ver3R_test", pTrange);

    TH1D *h1pT_dir_ver2R = (TH1D*)h1pT_dir_ver2 -> Rebin(10, "h1pT_dir_ver2R", pTrange);
    TH1D *h1pT_dir_ver3R = (TH1D*)h1pT_dir_ver3 -> Rebin(10, "h1pT_dir_ver3R", pTrange);
    TH1D *h1pT_dir_ver3R_test = (TH1D*)h1pT_dir_ver3_test -> Rebin(10, "h1pT_dir_ver3R_test", pTrange);

    yields[0]=h1pT_pion0_ver2R;
    yields[1]=h1pT_dir_ver2R;

    yields[2]=h1pT_pion0_ver3R;
    yields[3]=h1pT_dir_ver3R;

    yields[4]=h1pT_pion0_ver3R_test;
    yields[5]=h1pT_dir_ver3R_test;

    //analysis4. pT binwidth scaling
    //------------------------------
  
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<10; j++)
        {

            double binwidth = yields[i] -> GetBinWidth(j+1);

            yields[i] -> SetBinContent(j+1, yields[i] -> GetBinContent(j+1)/binwidth);
            yields[i] -> SetBinError(j+1, yields[i] -> GetBinError(j+1)/binwidth);

        }//binning

    }//histogram
    
    //analysis5. scailing
    //event Num Scaling
    //--------------------
    double nevent_ver2 = ncoll_ver2 -> Integral();
    double nevent_ver3 = ncoll_ver3 -> Integral();
    double nevent_ver3_test = ncoll_ver3_test -> Integral();

    double scalar_ver2 = (1./nevent_ver2);
    double scalar_ver3 = (1./nevent_ver3);
    double scalar_ver3_test = (1./nevent_ver3_test);

    yields[0] -> Scale(scalar_ver2);
    yields[1] -> Scale(scalar_ver2);

    yields[2] -> Scale(scalar_ver3);
    yields[3] -> Scale(scalar_ver3);

    yields[4] -> Scale(scalar_ver3_test);
    yields[5] -> Scale(scalar_ver3_test);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_option3_dNdpT_ver2ver3MC_compare.root", "recreate");

    for(int i=0; i<6; i++)
    {
        yields[i] -> Write();
    }

    output -> Close();




}
