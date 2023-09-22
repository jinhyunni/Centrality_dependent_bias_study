/*
	Analysis code for calculating Ncoll spectrum by centrality class and MB
	
	x axis: Ncoll	yaxis: # of event
	
	centrality class
	
		cent1: 0~10%
		cent2: 10~20%
		cent3: 20~40%
		cent4: 40~60%
		cent5: 60~80%

	MB events: all inelastic events
*/

void analysis_NcollByCent()
{
    //Input
    //-----
    TString prep_data = "../pre_processed";

    TString cent_input = TString::Format("%s/pAu200GeV_p8303ver3_option3_NcollCent_allEvents.root", prep_data.Data());
    TFile *input_cent = new TFile(cent_input, "read");

    //Get pre-processed histogram
    TH2D *h2ncollcent = (TH2D*)input_cent -> Get("ncollCent");

    //Analysis1. Projection Y to get Ncoll by centrality
    //--------------------------------------------------
    TH1D *ncoll_cent1 = (TH1D*)h2ncollcent -> ProjectionY("ncoll_cent1", 1, 1);
    TH1D *ncoll_cent2 = (TH1D*)h2ncollcent -> ProjectionY("ncoll_cent2", 2, 2);
    TH1D *ncoll_cent3 = (TH1D*)h2ncollcent -> ProjectionY("ncoll_cent3", 3, 4);
    TH1D *ncoll_cent4 = (TH1D*)h2ncollcent -> ProjectionY("ncoll_cent4", 5, 6);
    TH1D *ncoll_cent5 = (TH1D*)h2ncollcent -> ProjectionY("ncoll_cent5", 7, 8);

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver3_option3_NcollByCent.root", "recreate");

    ncoll_cent1 -> Write();
    ncoll_cent2 -> Write();
    ncoll_cent3 -> Write();
    ncoll_cent4 -> Write();
    ncoll_cent5 -> Write();

    output -> Close();


}
