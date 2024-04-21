#include "../headerFiles/configurable.h"

void analysis_dirPhoton_dNdpT_MBevents_ver1()
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

	//Analysis2. Rebin particle by pT
	//-------------------------------
	TH1D *numDirpT_varBin = (TH1D*)numDirpT -> Rebin(pTBinNum, "numDirpT_varBin", pTBin);
    
    //Analysis3. Scale histogran with event # and binwidth
    //----------------------------------------------------
    TH1D *dNdpT_dirPhoton = (TH1D*)numDirpT_varBin -> Clone("dNdpT_dirpT");
    dNdpT_dirPhoton -> Scale(1./h1ncoll -> Integral(), "width");
    
    //Analysis4. average Ncoll Scaling
    //--------------------------------
    TH1D *YavgNcollpT_dir = (TH1D*)dNdpT_dirPhoton -> Clone("YavgNcollDirpT_mb");
    YavgNcollpT_dir -> Scale(1./avgNcoll -> GetBinContent(1));

    //ouput
    //-----
    TFile *output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_MBevents_ver1.root", "recreate");
    
	numDirpT -> Write();
	numDirpT_varBin -> Write();
	dNdpT_dirPhoton -> Write();
	YavgNcollpT_dir -> Write();
   
    output -> Close();
}
