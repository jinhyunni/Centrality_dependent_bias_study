/*****************************************
* Draw pion0's pT spectrum by centrality *

	centrality1: 0~10%
	centrality2: 10~20%
	centrality3: 20~40%
	centrality4: 40~60%
	centrality5: 60~80%


* Draw invariant yield
* 100,000 events
*****************************************/

void pTpion0Spectrum_1e5()
{
	//read file
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5.root", "read");
	
	//centrality vs pTpion0
	TH2D* h2pTpion0Cent = (TH2D*)input -> Get("pTpion0_cent");
	TH2D* h2ncollCent = (TH2D*)input -> Get("ncoll_cent");
	

	//number of events in each centrality
	TH1D* h1cent = (TH1D*)h2ncollCent -> ProjectionX("centrality");

	//store analysis data in TFile
	TFile* output = new TFile("pTpion0Centrality.root", "recreate");
	h1cent -> Write();
	output -> Close();

}
