/***************************************
* pion0 Analysis

* Store pT of pion0
* pTpion0 - centrality -> TH2D

* 100,000 events
***************************************/

void analysis_yield()
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
	TFile* input = new TFile("pAu200GeV_option3_pTcent_refhis_INEL_v1.root", "read");
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
	int i_nElProj;
	int i_nElTarg;

	//link branch address
	opt3 -> SetBranchAddress("np", &np);
	opt3 -> SetBranchAddress("p_id", &p_id);
	opt3 -> SetBranchAddress("p_eta", &p_eta);
	opt3 -> SetBranchAddress("p_pt", &p_pt);
	opt3 -> SetBranchAddress("i_nAbsProj", &i_nAbsProj);
	opt3 -> SetBranchAddress("i_nDiffProj", &i_nDiffProj);
	opt3 -> SetBranchAddress("i_nAbsTarg", &i_nAbsTarg);
	opt3 -> SetBranchAddress("i_nDiffTarg", &i_nDiffTarg);
	opt3 -> SetBranchAddress("i_nElProj", &i_nElProj);
	opt3 -> SetBranchAddress("i_nElTarg", &i_nElTarg);
	
	//Analysis

	float pTsum = 0.;
	float centrality = 0.;
	int ncoll = 0;
	int elevent = 0;

	TH2D* pTpion0_cent = new TH2D("pTpion0_cent", "cent_pTpion0", 11, 0, 110, 28, 0, 14);
	TH2D* ncoll_cent = new TH2D("ncoll_cent", "cent_ncoll", 11, 0, 110, 100, 0, 100);
	
	for(int i = 0; i < opt3 -> GetEntries(); i++){
		opt3 -> GetEntry(i);
		//store inelastic events only
		if(i_nAbsProj == 1 and i_nAbsTarg != 0){
			elevent += 1;
			for(int j = 0; j < np; j++){
				if(p_eta[j]>-3.9 and p_eta[j]<-3.0 and p_id[j] != 111){
					pTsum = pTsum + p_pt[j];
				}
			}//j, particle
		
			//centrality calculation
			centrality = 100*((refhis -> Integral((refhis -> FindBin(pTsum)), 1e5))/(refhis -> Integral(1, 1e5)));
			//Ncoll calculation
			ncoll = i_nAbsTarg + i_nAbsProj - 1;

			//store pion0's pT by centrality in midrapidity(|eta|<1);
			for(int j = 0; j < np; j++){
				if(p_id[j]==111 and p_eta[j] > -1 and p_eta[j] < 1){
					pTpion0_cent -> Fill(centrality, p_pt[j]);
				}
			}//j, storing

			ncoll_cent -> Fill(centrality, ncoll);

			pTsum = 0.;
		}
	}//i, event
	
	cout << elevent << endl;

	//save histogram as root file
	TFile *file = new TFile("pAu200GeV_option3_pion0Analysis.root", "recreate");

	pTpion0_cent -> Write();
	ncoll_cent -> Write();

	file -> Close();

	delete opt3, pTpion0_cent, ncoll_cent, file;

}
