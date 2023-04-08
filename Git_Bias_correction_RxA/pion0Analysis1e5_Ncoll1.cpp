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
	int ncoll1 = 0;
	TH1D* pTpion0 = new TH1D("pTpion0", "", 28, 0, 14);
	
	for(int i = 0; i < opt3 -> GetEntries(); i++){
		opt3 -> GetEntry(i);

		//store inelastic events only, Ncoll = 1 evnets only, at mid-rapidity
		if(i_nAbsProj == 1 and i_nAbsTarg == 1){
			
				ncoll1 += 1;

			for(int j = 0; j < np; j++){
				if(p_id[j] == 111 and p_eta[j]>-1 and p_eta[j]<1){
					pTpion0 -> Fill(p_pt[j]);
				}
			}
		}//j, particle
	}//i, event

	cout << ncoll1 << endl;

	double scalar = 1./(pTpion0 -> GetBinWidth(1)*ncoll1);
	pTpion0 -> Scale(scalar);

 //	//save histogram as root file
 //	TFile *file = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5_rebined.root", "recreate");
 //	pTpion0 -> Write();
 //	file -> Close();

}
