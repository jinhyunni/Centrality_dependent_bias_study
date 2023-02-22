/*******************************************
* Depend Centrality in 100,000 p+Au events *

1.Analyze with pT sum of each events
*******************************************/


void centRef_pTSum()
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
	
	int nevt = opt3 -> GetEntries();
	float pTsum = 0;

	//Analysis
	////BBCS acepance: -3.9<eta<-3.0
	TH1F* ref1 = new TH1F("centRef_pTe3" ,"", 1000, 0, 100);
	TH1F* ref2 = new TH1F("centRef_pTe4", "", 10000, 0, 100);
	TH1F* ref3 = new TH1F("centRef_pTe5", "", 100000, 0, 100);
	TH1F* ref4 = new TH1F("centRef_pTe6", "", 1000000, 0, 100);

	for(int i = 0; i < nevt; i++){
		opt3 -> GetEntry(i);
			for(int j = 0; j < np; j++){
				if(-3.9<p_eta[j] and p_eta[j]<-3.0 and p_id[j] != 111){
						pTsum = pTsum + p_pt[j];
			}//BBCS
		}//j

		ref1 -> Fill(pTsum);
		ref2 -> Fill(pTsum);
		ref3 -> Fill(pTsum);
		ref4 -> Fill(pTsum);		
		//cout<<"In "<< event+1 << "event, the pT sum in BBC acceptance is: " << pTsum <<endl;

		pTsum = 0;

	}//i
	
	ref1 -> Sumw2();
	ref2 -> Sumw2();
	ref3 -> Sumw2();
	
	//save histogram as root file
	TFile *file = new TFile("pAu200GeV_option3_pTcent_refhis_v1.root", "recreate");
	ref1 -> Write();
	ref2 -> Write();
	ref3 -> Write();
	ref4 -> Write();
	file -> Close(); 

	delete opt3;
	delete ref1;
	delete ref2;
	delete ref3;
	delete ref4;
	delete file;
	

}
