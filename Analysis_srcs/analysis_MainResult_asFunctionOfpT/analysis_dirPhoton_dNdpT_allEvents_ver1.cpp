#include "../headerFiles/configurable.h"

void analysis_dirPhoton_dNdpT_allEvents_ver1()
{
    //input
    //-----
    TFile *dir = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_TH2DpTCent_dirPhoton.root", "read");
    TFile *input_Ncoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_NcollCent.root", "read");
    TFile *input_avgNcoll = new TFile("../pre_processed/pAu200GeV_p8303_onlyDirPhoton_option3_centDivided_avgNcollCent.root", "read");

    //output
    //------
    TFile* output = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_dirPhoton_dNdpT_allEvents_ver1.root", "recreate");
	TObjArray *rawDirPhoton = new TObjArray(0);
	TObjArray *dNdpT_dirPhoton_centClass = new TObjArray(0);
	TObjArray *Ncoll_scaled_dNdpT_centClass = new TObjArray(0);

    //Input histograms
    //----------------
    TH2D *h2centDir = (TH2D*)dir -> Get("centDir");
    TH2D *h2NcollCent = (TH2D*)input_Ncoll -> Get("ncollCent");
	TProfile *avgNcoll = (TProfile*)input_avgNcoll -> Get("avgNcollCent");

    //Analysis1. Get number of direct photon by centrality per event
    //CentClass
    //centclass1: 0~10%
    //centclass2: 10~20%
    //centclass3: 20~40%
    //centclass4: 40~60%
    //centclass5: 60~80%
    //--------------------------------------------------------------

	// pT binning of dirPhoton by event centrality
    TH1D *numDirpT_cent[5];
    
    numDirpT_cent[0] = (TH1D*)h2centDir -> ProjectionY("centClassDir1", 1, 1);             //centClass1: 0~10%
    numDirpT_cent[1] = (TH1D*)h2centDir -> ProjectionY("centClassDir2", 2, 2);             //centClass2: 10~20%
    numDirpT_cent[2] = (TH1D*)h2centDir -> ProjectionY("centClassDir3", 3, 4);             //centClass3: 20~40%
    numDirpT_cent[3] = (TH1D*)h2centDir -> ProjectionY("centClassDir4", 5, 6);             //centClass4: 40~60%
    numDirpT_cent[4] = (TH1D*)h2centDir -> ProjectionY("centClassDir5", 7, 8);             //centClass5: 60~80%

	for(int i=0; i<5; i++)
	{
		rawDirPhoton -> Add(numDirpT_cent[i]);
	}
   	
	// Analysis2. Get dNdpT of dirPhoton by centrality class
	// * setting variable binwidth for pT spectrum
	//------------------------------------------------------

	//Getting dirPhoton pT spectrum by centrality class
	TH1D *numDirpT_varBin_cent[5];
	for(int cent=0; cent<centBinNum; cent++)
	{
		TString outputname = Form("numDirpT_varBin_cent%d", cent+1);
		numDirpT_varBin_cent[cent] = (TH1D*)numDirpT_cent[0] -> Rebin(pTBinNum, outputname, pTBin);
	}

	// scaling event # and variable bin width for each centrality bin
	TH1D *dNdpT_dirPhoton_cent[5];
	TH1D *eventN = (TH1D*)((TH1D*)h2NcollCent -> ProjectionX("nEventByCent")) -> Rebin(centBinNum, "nEventByCentClass", centBin);
	for(int cent=0; cent<centBinNum; cent++)
	{
		TString outputname = Form("dNdpT_dirPhoton_cent%d", cent+1);

		double norm = 1./eventN -> GetBinContent(cent+1);
		dNdpT_dirPhoton_cent[cent] = (TH1D*)numDirpT_varBin_cent[cent] -> Clone(outputname);
		dNdpT_dirPhoton_cent[cent] -> Scale(norm, "width");
		
		dNdpT_dirPhoton_centClass -> Add(dNdpT_dirPhoton_cent[cent]);
	}

    //Analysis3. Get Yield/<Ncoll> vs pT, by centrality
    //-------------------------------------------------
    TH1D *YavgNcollDir[centBinNum];
    TProfile *avgNcollCent = (TProfile*)avgNcoll -> Rebin(centBinNum, "avgNcollCent", centBin);

    for(int cent=0; cent<centBinNum; cent++)
    {
        TString dir = Form("YavgNcollDirpT_cent%d", cent+1);

        YavgNcollDir[cent] = (TH1D*)dNdpT_dirPhoton_cent[cent] -> Clone(dir);
        YavgNcollDir[cent] -> Scale(1./avgNcollCent -> GetBinContent(cent+1));
		
		Ncoll_scaled_dNdpT_centClass -> Add(YavgNcollDir[cent]);
    }
   
    //Write outputs in outputfile
    //---------------------------
	rawDirPhoton -> Write();
	dNdpT_dirPhoton_centClass -> Write();
	Ncoll_scaled_dNdpT_centClass -> Write();

    //Close files
    //-----------
    dir -> Close();
    input_Ncoll -> Close();
    input_avgNcoll -> Close();
    output -> Close();

    //disallocation
 	delete dir;
 	delete input_Ncoll;
 	delete input_avgNcoll;
 	delete output;
        
}
