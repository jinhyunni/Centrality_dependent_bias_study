#include "../headerFiles/configurable.h"

void analysis_dirPhoton_dNdpT_MBevents()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_TH2DpTeta_midDirPhoton.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_Ncoll.root", "read");
    TFile *input3 = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_MBevents_avgNcoll.root", "read");
       
    TH2D *h2pTetaDir = (TH2D*)input1 -> Get("pTetaDir_mb");
    TH1D *h1ncoll = (TH1D*)input2 -> Get("ncoll_mb");

	TProfile *avgNcoll = (TProfile*)input3 -> Get("avgNcoll_mb");

    //Analysis1. Project to y to get number of particle by pT
    //----------------------------------------------------------
    TH1D *numDirpT = (TH1D*)h2pTetaDir -> ProjectionY("numDirpT");
    
    //Analysis2. Scale event number
    //-------------------------------
    TH1D *numDirpT_perEvent = (TH1D*)numDirpT -> Clone("yieldDirpT_mb");
    numDirpT_perEvent -> Scale(1./h1ncoll -> Integral());
    
    //Analysis3. Rebin for pT, divde binwidht to get dndpT
    //------------------------------------------------------

    TH1D *dndpt_dir_mb = (TH1D*)numDirpT_perEvent -> Rebin(pTBinNum, "dNdpt_dir_mb", pTBin);
	
    //scaling binwidth to get dNdpT
    for(int pT=0; pT<pTBinNum; pT++)
    {
        double binwidth = dndpt_dir_mb -> GetBinWidth(pT+1);
		
		//scale variable binwidth
        dndpt_dir_mb -> SetBinContent(pT+1, dndpt_dir_mb -> GetBinContent(pT+1)/binwidth);
        dndpt_dir_mb -> SetBinError(pT+1, dndpt_dir_mb -> GetBinError(pT+1)/binwidth);
    }

    
    //Analysis4. average Ncoll Scaling
    //--------------------------------
    TH1D *YavgNcollpT_dir = (TH1D*)dndpt_dir_mb -> Clone("YavgNcollDirpT_mb");
    YavgNcollpT_dir -> Scale(1./avgNcoll -> GetBinContent(1));

    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_MBevents.root", "recreate");
    
	numDirpT_perEvent -> Write();
	dndpt_dir_mb -> Write();
	YavgNcollpT_dir -> Write();
   
    output -> Close();
}
