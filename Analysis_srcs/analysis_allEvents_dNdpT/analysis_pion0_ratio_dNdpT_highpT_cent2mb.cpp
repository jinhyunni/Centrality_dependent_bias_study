void analysis_pion0_ratio_dNdpT_highpT_cent2mb()
{
    //input
    //-----
    TFile *cent = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_pion0_dNdpT_allEvents.root", "read");
    TFile *mb = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_pion0_dNdpT_MBevents.root", "read");
    
    TH1D *scaled_pion0_cent[5];
    
    //scaled yield by centrality
    for(int i=0; i<5; i++)
    {   
        TString scaled_pion0 = Form("YavgNcollPion0pT_cent%d", i+1);

        scaled_pion0_cent[i] = (TH1D*)cent ->Get(scaled_pion0);
    }
    
    //scaled yield of MB
    TH1D *scaled_pion0_mb = (TH1D*)mb -> Get("YavgNcollPion0pT_mb");
    
    //Analysis1. Get scaled yield Ratio
    //---------------------------------
    TH1D *scaled_ratio_pion0_cent[5];
    
    for(int i=0; i<5; i++)
    {
        TString pion0_output = Form("ratio_scaledYield_pion0cent%d", i+1);
        
        //ratio of scaled pion0 yield: cent/mb
        scaled_ratio_pion0_cent[i] = (TH1D*)scaled_pion0_cent[i] -> Clone(pion0_output);
        scaled_ratio_pion0_cent[i] -> Divide(scaled_pion0_mb);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_pion0_ratio_scaled-dNdpT_highpT.root", "recreate");

    for(int i=0; i<5; i++)
    {
        scaled_ratio_pion0_cent[i] -> Write();
    }

    output -> Close();


}
