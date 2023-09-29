void analysis_ratio_dNdpT_cent2mb()
{
    //input
    //-----
    TFile *cent = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *mb = new TFile("pAu200GeV_p8303ver3_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");
    
    TH1D *scaled_pion0_cent[5];
    TH1D *scaled_dir_cent[5];
    
    //scaled yield by centrality
    for(int i=0; i<5; i++)
    {   
        TString scaled_pion0 = Form("YavgNcollPion0pT_cent%d", i+1);
        TString scaled_dir = Form("YavgNcollDirpT_cent%d", i+1);

        scaled_pion0_cent[i] = (TH1D*)cent ->Get(scaled_pion0);
        scaled_dir_cent[i] = (TH1D*)cent ->Get(scaled_dir);
    }
    
    //scaled yield of MB
    TH1D *scaled_pion0_mb = (TH1D*)mb -> Get("YavgNcollPion0pT_mb");
    TH1D *scaled_dir_mb = (TH1D*)mb -> Get("YavgNcollDirpT_mb");
    
    //Analysis1. Get scaled yield Ratio
    //---------------------------------
    TH1D *scaled_ratio_pion0_cent[5];
    TH1D *scaled_ratio_dir_cent[5];
    
    for(int i=0; i<5; i++)
    {
        TString pion0_output = Form("ratio_scaledYield_pion0cent%d", i+1);
        TString dir_output = Form("ratio_scaledYield_dircent%d", i+1);
        
        //ratio of scaled pion0 yield: cent/mb
        scaled_ratio_pion0_cent[i] = (TH1D*)scaled_pion0_cent[i] -> Clone(pion0_output);
        scaled_ratio_pion0_cent[i] -> Divide(scaled_pion0_mb);
        
        //ratio of scaled dir yield: cent/mb
        scaled_ratio_dir_cent[i] = (TH1D*)scaled_dir_cent[i] -> Clone(dir_output);
        scaled_ratio_dir_cent[i] -> Divide(scaled_dir_mb);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver3_option3_ratio_scaled-dNdpt.root", "recreate");

    for(int i=0; i<5; i++)
    {
        scaled_ratio_pion0_cent[i] -> Write();
        scaled_ratio_dir_cent[i] -> Write();
    }

    output -> Close();


}
