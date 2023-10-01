/*
    Take ratio of yields between different MC yields

    denominator: pythia8303, external package On, ver3 MC 

*/   
   
void analysis_ratio_dNdpT_MCcompare()
{
    //input
    //-----
    TFile *input1 = new TFile("pAu200GeV_option3_dNdpT_ver2ver3MC_compare.root" ,"read");

    TH1D *dir_8303_ver2npl_externalOn = (TH1D*)input1 -> Get("h1pT_dir_ver2R");
    TH1D *dir_8303_ver3npl_externalOn = (TH1D*)input1 -> Get("h1pT_dir_ver3R_test");    //denominator
    TH1D *dir_8307_ver3kiaf_externalOff = (TH1D*)input1 -> Get("h1pT_dir_ver3R");
    TH1D *dir_8303_ver3npl_externalOff = (TH1D*)input1 -> Get("h1pT_dir_ver3R_nplRootOnly");
    TH1D *dir_8303_ver3kiaf_externalOff = (TH1D*)input1 -> Get("h1pT_dir_ver3R_p8303");

    TH1D *pion0_8303_ver2npl_externalOn = (TH1D*)input1 -> Get("h1pT_pion0_ver2R");
    TH1D *pion0_8303_ver3npl_externalOn = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_test");    //denominator
    TH1D *pion0_8307_ver3kiaf_externalOff = (TH1D*)input1 -> Get("h1pT_pion0_ver3R");
    TH1D *pion0_8303_ver3npl_externalOff = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_nplRootOnly");
    TH1D *pion0_8303_ver3kiaf_externalOff = (TH1D*)input1 -> Get("h1pT_pion0_ver3R_p8303");


    //Take ratio
    //----------
    
    //dir ratio
    TH1D *ratio_dir[4];

    TH1D *dir_ratio_ver2npl_8303_externalOn = (TH1D*)dir_8303_ver2npl_externalOn -> Clone("dir_pTratio_ver2npl_8303_externalOn");
    TH1D *dir_ratio_ver3kiaf_8307_externalOff = (TH1D*)dir_8307_ver3kiaf_externalOff -> Clone("dir_pTratio_ver3kiaf_8307_externalOff");
    TH1D *dir_ratio_ver3npl_8303_externalOff = (TH1D*)dir_8303_ver3npl_externalOff -> Clone("dir_pTratio_ver3npl_8303_externalOff");
    TH1D *dir_ratio_ver3kiaf_8303_externalOff = (TH1D*)dir_8303_ver3kiaf_externalOff -> Clone("dir_pTratio_ver3kiaf_8303_externalOff");
    
    ratio_dir[0] = dir_ratio_ver2npl_8303_externalOn;
    ratio_dir[1] = dir_ratio_ver3kiaf_8307_externalOff;
    ratio_dir[2] = dir_ratio_ver3npl_8303_externalOff;
    ratio_dir[3] = dir_ratio_ver3kiaf_8303_externalOff;

    for(int i=0; i<4; i++)
    {
        ratio_dir[i] -> Divide(dir_8303_ver3npl_externalOn);
    }

    //pin0 ratio
    TH1D *ratio_pion0[4];

    TH1D *pion0_ratio_ver2npl_8303_externalOn = (TH1D*)pion0_8303_ver2npl_externalOn -> Clone("pion0_pTratio_ver2npl_8303_externalOn");
    TH1D *pion0_ratio_ver3kiaf_8307_externalOff = (TH1D*)pion0_8307_ver3kiaf_externalOff -> Clone("pion0_pTratio_ver3kiaf_8307_externalOff");
    TH1D *pion0_ratio_ver3npl_8303_externalOff = (TH1D*)pion0_8303_ver3npl_externalOff -> Clone("pion0_pTratio_ver3npl_8303_externalOff");
    TH1D *pion0_ratio_ver3kiaf_8303_externalOff = (TH1D*)pion0_8303_ver3kiaf_externalOff -> Clone("pion0_pTratio_ver3kiaf_8303_externalOff");
    
    ratio_pion0[0] = pion0_ratio_ver2npl_8303_externalOn;
    ratio_pion0[1] = pion0_ratio_ver3kiaf_8307_externalOff;
    ratio_pion0[2] = pion0_ratio_ver3npl_8303_externalOff;
    ratio_pion0[3] = pion0_ratio_ver3kiaf_8303_externalOff;

    for(int i=0; i<4; i++)
    {
        ratio_pion0[i] -> Divide(pion0_8303_ver3npl_externalOn);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_option3_ratio_dNdpT_MCcompare.root", "recreate");

    for(int i=0; i<4; i++)
    {
        ratio_dir[i] -> Write();
        ratio_pion0[i] -> Write();
    }

    output -> Close();



}
