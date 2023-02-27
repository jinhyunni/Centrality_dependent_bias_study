/***************************************
* pion0 Analysis

* Store pT of pion0 with Ncoll =1 events
* pTpion0 - centrality -> TH2D

* will be used as reference histo
* in calculation of RpAu

* 100,000 events
***************************************/

void pion0Analysis1e5_Ncoll1()
{
	//read files
	TChain *opt3 = new TChain("T");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00000.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00001.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00002.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00003.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00004.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00005.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00006.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00007.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00008.root");
	opt3 -> Add("outfile_pAu200GeV_set00_grp000_00009.root");
	
	//centrality reference his
	TFile* input = new TFile("pAu200GeV_option3_pTcent_refhis_v1.root", "read");
	TH1F* refhis = (TH1F*)input -> Get("centRef_pTe5");

	//set variables to hold information
	int np = 5000;
	int p_id[np];
	float p_eta[np];
	float p_pt[np];

	int i_nAbsProj;
	int i_nDiffProj;
	int i_nAbsTarg;
	int i_nDiffTarg;

	//link branch address
	opt3 -> SetBranchAddress("np", &np);
	opt3 -> SetBranchAddress("p_id", &p_id);
	opt3 -> SetBranchAddress("p_eta", &p_eta);
	opt3 -> SetBranchAddress("p_pt", &p_pt);
	opt3 -> SetBranchAddress("i_nAbsProj", &i_nAbsProj);
	opt3 -> SetBranchAddress("i_nDiffProj", &i_nDiffProj);
	opt3 -> SetBranchAddress("i_nAbsTarg", &i_nAbsTarg);
	opt3 -> SetBranchAddress("i_nDiffTarg", &i_nDiffTarg);
	
	cout << opt3 -> GetEntries() << endl;

	//Analysis

	float pTsum = 0.;
	float centrality = 0.;
	int ncoll = 0;

	TH2D* pTpion0_cent = new TH2D("pTpion0_cent", "cent_pTpion0", 11, 0, 110, 1000, 0, 14);

	for(int i = 0; i < opt3 -> GetEntries(); i++){
		opt3 -> GetEntry(i);
		
		//pT summation for centrality calculation
		for(int j = 0; j < np; j++){
			if(p_eta[j]>-3.9 and p_eta[j]<-3.0 and p_id[j] != 111){
				pTsum = pTsum + p_pt[j];
			}
		}//j, particle
		
		//centrality calculation
		centrality = 100*((refhis -> Integral((refhis -> FindBin(pTsum)), 1e5))/(refhis -> Integral(1, 1e5)));

		//store pion0's pT by centrality, in event with Ncoll = 1;
		//ncoll = i_nAbsTarg + i_nAbsProj, all events are i_nAbsProj = 1(proton)
		//ncoll = 1 -> i_nAbsTarg = 1
		if(i_nAbsTarg == 1){
			for(int j = 0; j < np; j++){
				if(p_id[j] == 111){
					//store pion0's pT by centrality
					pTpion0_cent -> Fill(centrality, p_pt[j]);
				}
			}//j, storing
		}//sorting ncoll = 1 event


		pTsum = 0.;
	}//i, event
	
	//save histogram as root file
	TFile *file = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_1e5.root", "recreate");
	pTpion0_cent -> Write();
	file -> Close();

}
