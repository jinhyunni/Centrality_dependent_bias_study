void analysis_RpAu_pion0dir()
{
    //input
    //-----
    TFile *input1 = new TFile("../analysis_scaled-dNdpT/pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver4_option3_dNdpT_pion0dir_Ncoll1.root", "read");

    TH1D *scaled_dndpt_pion0_cent[5];
    TH1D *scaled_dndpt_dir_cent[5];
    
    // dNdpT/<Ncoll> by centrality
    for(int i=0; i<5; i++)
    {
        TString input_pion0 = Form("YavgNcollPion0pT_cent%d", i+1);
        TString input_dir = Form("YavgNcollDirpT_cent%d", i+1);

        scaled_dndpt_pion0_cent[i] = (TH1D*)input1 -> Get(input_pion0);
        scaled_dndpt_dir_cent[i] = (TH1D*)input1 -> Get(input_dir);
    }
    
    // dNdpT in Ncoll=1
    TH1D *dndpt_pion0_ncoll1 = (TH1D*)input2 -> Get("dNdpT_pion0_Ncoll1");
    TH1D *dndpt_dir_ncoll1 = (TH1D*)input2 -> Get("dNdpT_dir_Ncoll1");

    //Analysis1. Divide scaled-yield by centrality with Ncoll=1 yield
    //---------------------------------------------------------------

    TH1D *RpAu_pion0_cent[5];
    TH1D *RpAu_dir_cent[5];

    for(int i=0; i<5; i++)
    {
        TString output_pion0 = Form("RpAu_pion0_cent%d", i+1);
        TString output_dir = Form("RpAu_dir_cent%d", i+1);
        
        // RpAu pion0
        RpAu_pion0_cent[i] = (TH1D*)scaled_dndpt_pion0_cent[i] -> Clone(output_pion0);
        RpAu_pion0_cent[i] -> Divide(dndpt_pion0_ncoll1);
        
        // RpAu direct photon
        RpAu_dir_cent[i] = (TH1D*)scaled_dndpt_dir_cent[i] -> Clone(output_dir);
        RpAu_dir_cent[i] -> Divide(dndpt_dir_ncoll1);
    }

    //output
    //------

    TFile *output = new TFile("pAu200GeV_p8303ver4_option3_RpAu_pion0dir.root", "recreate");

    for(int i=0; i<5; i++)
    {
        RpAu_pion0_cent[i] -> Write();
        RpAu_dir_cent[i] -> Write();
    }

    output -> Close();


}
