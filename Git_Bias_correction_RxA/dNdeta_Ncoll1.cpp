void dNdeta_Ncoll1()
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
	
	//for checking
	//cout<<"The number of entries: "<<opt0 -> GetEntries()<<endl;

	//set variables to hold information
	int np = 5000;
	int p_id[np];
	float p_eta[np];
	float p_pt[np];
	float p_phi[np];

	float f_b;
	int i_nAbsProj;
	int i_nDiffProj;
	int i_nAbsTarg;
	int i_nDiffTarg;

	//link branch address
	opt3 -> SetBranchAddress("np", &np);
	opt3 -> SetBranchAddress("p_id", &p_id);
	opt3 -> SetBranchAddress("p_eta", &p_eta);
	opt3 -> SetBranchAddress("p_pt", &p_pt);
	opt3 -> SetBranchAddress("p_phi", &p_phi);
	opt3 -> SetBranchAddress("f_b", &f_b);
	opt3 -> SetBranchAddress("i_nAbsProj", &i_nAbsProj);
	opt3 -> SetBranchAddress("i_nDiffProj", &i_nDiffProj);
	opt3 -> SetBranchAddress("i_nAbsTarg", &i_nAbsTarg);
	opt3 -> SetBranchAddress("i_nDiffTarg", &i_nDiffTarg);

	//Analysis_dNdeta_Ncoll = 1 events
	
	int ncoll1 = 0;

	TH1D *dNdeta = new TH1D("dNdeta", "charged pi/K/p, Integrated pT", 600, -6, 6);
	int nevt = opt3 -> GetEntries();

	for(int i = 0; i < nevt; i++){
		opt3 -> GetEntry(i);
		if(i_nDiffProj == 0 and i_nDiffTarg == 0 and i_nAbsProj == 1 and i_nAbsTarg == 1){

			ncoll1 += 1;

			for(int j = 0; j < np; j++){
				if(p_id[j] == 111){
					dNdeta -> Fill(p_eta[j]);
				}
			}//j
		}
	}//i
	
	dNdeta -> Sumw2();

	cout << ncoll1 << endl;

	//save histogram as root file
	TFile *file = new TFile("pAu200GeV_option1_dNdeta_npion_Ncoll1.root", "recreate");
	dNdeta -> Write();
	file -> Close(); 


}
