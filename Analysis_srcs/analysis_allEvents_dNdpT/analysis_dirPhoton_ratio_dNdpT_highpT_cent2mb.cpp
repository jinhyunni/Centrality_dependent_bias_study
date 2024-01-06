void analysis_dirPhoton_ratio_dNdpT_highpT_cent2mb()
{
    //input
    //-----
    TFile *cent = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_allEvents_grp0to4.root", "read");
    TFile *mb = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_MBevents_grp0to4.root", "read");
    
    TH1D *scaled_dir_cent[5];
    
    //scaled yield by centrality
    for(int i=0; i<5; i++)
    {   
        TString scaled_dir = Form("YavgNcollDirpT_cent%d", i+1);
        scaled_dir_cent[i] = (TH1D*)cent ->Get(scaled_dir);
    }
    
    //scaled yield of MB
    TH1D *scaled_dir_mb = (TH1D*)mb -> Get("YavgNcollDirpT_mb");
    
    //Analysis1. Get scaled yield Ratio
    //---------------------------------
    TH1D *scaled_ratio_dir_cent[5];
    
    for(int i=0; i<5; i++)
    {
        TString dir_output = Form("ratio_scaledYield_dircent%d", i+1);
        
        //ratio of scaled dir yield: cent/mb
        scaled_ratio_dir_cent[i] = (TH1D*)scaled_dir_cent[i] -> Clone(dir_output);
        scaled_ratio_dir_cent[i] -> Divide(scaled_dir_mb);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_ratio_scaled-dNdpT_highpT_grp0to4.root", "recreate");

    for(int i=0; i<5; i++)
    {
        scaled_ratio_dir_cent[i] -> Write();
    }

    output -> Close();


}
