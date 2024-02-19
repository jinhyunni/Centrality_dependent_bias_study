void analysis_centBias_asFunctionOfCent_bypTClass()
{
    //input
    //-----
	TFile *input_pion0_cent = new TFile("pAu200GeV_p8303ver5_option3_dNdCent_scaled_pion0.root", "read");
	TFile *input_pion0_MB = new TFile("pAu200GeV_p8303ver5_option3_MB_pTClass_pion0.root", "read");
	TFile *input_dirPhoton_cent = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dNdCent_scaled_dirPhoton.root", "read");
	TFile *input_dirPhoton_MB = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_MB_pTClass_dirPhoton.root", "read");
	
	TH1D *dNdCent_avgNcollScaled_pion0[5];
	TH1D *dNdCent_avgNcollScaled_dir[5];
	TH1D *Pion0MB_avgNcollScaled[5];
	TH1D *DirMB_avgNcollScaled[5];
	
	//Get histograms
	for(int i=0; i<5; i++)
	{
		TString hisname_input_pion0_cent = Form("dNdCent_avgNcollScaled_pTClass%d", i+1);
		TString hisname_input_pion0_MB = Form("Pion0MB_avgNcollScaled_pTClass%d", i+1);
		TString hisname_input_dirPhoton_cent = Form("dNdCent_avgNcollScaled_pTClass%d", i+1);
		TString hisname_input_dirPhoton_MB = Form("DirMB_avgNcollScaled_pTClass%d", i+1);

		dNdCent_avgNcollScaled_pion0[i] = (TH1D*)input_pion0_cent -> Get(hisname_input_pion0_cent);
		dNdCent_avgNcollScaled_dir[i] = (TH1D*)input_dirPhoton_cent -> Get(hisname_input_dirPhoton_cent);
		Pion0MB_avgNcollScaled[i] = (TH1D*)input_pion0_MB -> Get(hisname_input_pion0_MB);
		DirMB_avgNcollScaled[i] = (TH1D*)input_dirPhoton_MB -> Get(hisname_input_dirPhoton_MB);
	}

    
    //Analysis1. Get cent bias of pion0 and dirPhoton
	//-----------------------------------------------

	TH1D *pion0_centBias_pTClass[5];
	TH1D *dir_centBias_pTClass[5];

    for(int i=0; i<5; i++)
    {   
        TString ratio_scaled_pion0 = Form("pion0_centBias_pTClass%d", i+1);
        TString ratio_scaled_dir = Form("dir_centBias_pTClass%d", i+1);
		
		pion0_centBias_pTClass[i] = (TH1D*)dNdCent_avgNcollScaled_pion0[i] -> Clone(ratio_scaled_pion0);
		dir_centBias_pTClass[i] = (TH1D*)dNdCent_avgNcollScaled_dir[i] -> Clone(ratio_scaled_dir);
		
		pion0_centBias_pTClass[i] -> Scale(1./Pion0MB_avgNcollScaled[i] -> GetBinContent(1));
		dir_centBias_pTClass[i] -> Scale(1./DirMB_avgNcollScaled[i] -> GetBinContent(1));
    }
    
    //Analysis2. compare cent bias of dirPhoton/pion0
    //-----------------------------------------------
    TH1D *centBiasRatio_pion0toDir_pTClass[5];
    
    for(int i=0; i<5; i++)
    {
        TString outputname = Form("centBiasRatio_pion0toDir_pTClass%d", i+1);
        
		centBiasRatio_pion0toDir_pTClass[i] = (TH1D*)pion0_centBias_pTClass[i] -> Clone(outputname);
        centBiasRatio_pion0toDir_pTClass[i] -> Divide(dir_centBias_pTClass[i]);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver5_onlyDirPhotonUsed_option3_centBias_centBiasRatio_pion0toDir.root", "recreate");

    for(int i=0; i<5; i++)
	{
		pion0_centBias_pTClass[i] -> Write();
		dir_centBias_pTClass[i] -> Write();
		centBiasRatio_pion0toDir_pTClass[i] -> Write();
    }

    output -> Close();


}
