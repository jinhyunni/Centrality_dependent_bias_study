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
    //double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0}; int binNumber = 11;	//11 binning
    //double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.0, 9.0, 11.0, 15.0, 20.0};	int binNumber = 11; //11 binning
	//double pTrange[] = {2.0, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 12.0, 14.0, 16.0, 20.0}; int binNumber = 15; //12 binning
	//double pTrange[] = {2.0, 4.0, 7.0, 10.0, 15.0, 20.0}; int binNumber = 5;

    TH1D *dndpt_dir_mb = (TH1D*)numDirpT_perEvent -> Rebin(binNumber, "dNdpt_dir_mb", pTrange);
	
    //scaling binwidth to get dNdpT
    for(int i=0; i<binNumber; i++)
    {
        double binwidth = dndpt_dir_mb -> GetBinWidth(i+1);
		
		//scale variable binwidth
        dndpt_dir_mb -> SetBinContent(i+1, dndpt_dir_mb -> GetBinContent(i+1)/binwidth);
        dndpt_dir_mb -> SetBinError(i+1, dndpt_dir_mb -> GetBinError(i+1)/binwidth);
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
