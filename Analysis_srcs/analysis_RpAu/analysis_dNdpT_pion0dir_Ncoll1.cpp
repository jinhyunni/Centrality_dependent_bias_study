void analysis_dNdpT_pion0dir_Ncoll1()
{
    //input
    //-----
    TFile *input1 = new TFile("pAu200GeV_p8303ver4_option3_TH2DpTeta_pion0dir_Ncoll1.root", "read");
    TFile *input_ver3num = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_Ncoll_MBevents.root", "read");

    TH2D *h2pTeta_pion0 = (TH2D*)input1 -> Get("yieldPion0");
    TH2D *h2pTeta_dir = (TH2D*)input1 -> Get("yieldDir");

    TH1D *ncoll_mb_ver3 = (TH1D*)input_ver3num -> Get("ncoll_mb");

    //Analysis1. ProjectionY to get # of pion0/dir by pT
    //--------------------------------------------------
    TH1D *h1pT_pion0 = (TH1D*)h2pTeta_pion0 -> ProjectionY();
    TH1D *h1pT_dir = (TH1D*)h2pTeta_dir -> ProjectionY();

    //Analysis2. Scale event #
    //------------------------
    h1pT_pion0 -> Scale(1./ncoll_mb_ver3 -> GetBinContent(2));
    h1pT_dir -> Scale(1./ncoll_mb_ver3 -> GetBinContent(2));

    //Analysis3. Rebin for pT range
    //           divide pT binwidth
    //-----------------------------
    double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0};

    TH1D *dndpt_pion0_ncoll1 = (TH1D*)h1pT_pion0 -> Rebin(11, "dNdpT_pion0_Ncoll1", pTrange);
    TH1D *dndpt_dir_ncoll1 = (TH1D*)h1pT_dir -> Rebin(11, "dNdpT_dir_Ncoll1", pTrange);

    for(int i=0; i<dndpt_pion0_ncoll1 -> GetNbinsX(); i++)
    {
        double binwidth = dndpt_pion0_ncoll1 -> GetBinWidth(i+1);

        //set bin content
        dndpt_pion0_ncoll1 -> SetBinContent(i+1, dndpt_pion0_ncoll1 -> GetBinContent(i+1)/binwidth);
        dndpt_dir_ncoll1 -> SetBinContent(i+1, dndpt_dir_ncoll1 -> GetBinContent(i+1)/binwidth);

        //set bin error
        dndpt_pion0_ncoll1 -> SetBinError(i+1, dndpt_pion0_ncoll1 -> GetBinContent(i+1)/binwidth);
        dndpt_dir_ncoll1 -> SetBinError(i+1, dndpt_dir_ncoll1 -> GetBinContent(i+1)/binwidth);
    }

    //output
    //-----
    TFile *output = new TFile("pAu200GeV_p8303ver4_option3_dNdpT_pion0dir_Ncoll1.root", "recreate");

    dndpt_pion0_ncoll1 -> Write();
    dndpt_dir_ncoll1 -> Write();

    output -> Close();

}
