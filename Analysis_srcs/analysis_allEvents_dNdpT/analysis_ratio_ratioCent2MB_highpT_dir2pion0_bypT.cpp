void analysis_ratio_ratioCent2MB_highpT_dir2pion0_bypT()
{
    //input
    //-----
    TFile *input = new TFile("pAu200GeV_p8303ver5_option3_ratio_scaled-dNdpT_highpT.root", "read");
    
    TH1D *ratio_scaled_pion0_cent[5];
    TH1D *ratio_scaled_dir_cent[5];
    
    //ratio of scaled yield by cent, pion0 and dir
    for(int i=0; i<5; i++)
    {   
        TString ratio_scaled_pion0 = Form("ratio_scaledYield_pion0cent%d", i+1);
        TString ratio_scaled_dir = Form("ratio_scaledYield_dircent%d", i+1);

        ratio_scaled_pion0_cent[i] = (TH1D*)input ->Get(ratio_scaled_pion0);
        ratio_scaled_dir_cent[i] = (TH1D*)input ->Get(ratio_scaled_dir);
    }
    
    //Analysis1. Get scaled yield Ratio
    //---------------------------------
    TH1D *centBias_bypT_dir2pion0[5];
    
    for(int i=0; i<5; i++)
    {
        TString outputname = Form("centBias_bypT_pion0toDir_cent%d", i+1);
        
        //centBias by pT, dirPhoton/pion0
        centBias_bypT_dir2pion0[i] = (TH1D*)ratio_scaled_pion0_cent[i] -> Clone(outputname);
        centBias_bypT_dir2pion0[i] -> Divide(ratio_scaled_dir_cent[i]);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver5_option3_ratio_ratioCent2MB_highpT_pion0toDir_bypT.root", "recreate");

    for(int i=0; i<5; i++)
    {
        centBias_bypT_dir2pion0[i] -> Write();
    }

    output -> Close();


}
