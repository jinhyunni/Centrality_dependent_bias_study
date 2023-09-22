void analysis_dNdeta()
{		
	TFile *input1 = new TFile("pythia_pAu200GeV_option3_dirExcluded_100thousand.root", "read");

	TTree *opt3 = (TTree*)input1 -> Get("T");

	int np=5000;
	float p_eta[np];
	float p_pt[np];
	int p_id[np];

	int i_nAbsTarg;
	int i_nAbsProj;

	opt3 -> SetBranchAddress("np", &np);
	opt3 -> SetBranchAddress("p_eta", p_eta);
	opt3 -> SetBranchAddress("p_pt", p_pt);
	opt3 -> SetBranchAddress("p_id", p_id);
	opt3 -> SetBranchAddress("i_nAbsTarg", &i_nAbsTarg);
	opt3 -> SetBranchAddress("i_nAbsProj", &i_nAbsProj);

	int nevent = opt3 -> GetEntries();	

	TH1D *pionEta = new TH1D("dirEx_pionEta", "", 24, -6, 6);
	TH1D *kaonEta = new TH1D("dirEx_kaonEta", "", 24, -6, 6);
	TH1D *protonEta = new TH1D("dirEx_protonEta", "", 24, -6, 6);

	pionEta -> Sumw2();
	kaonEta -> Sumw2();
	protonEta -> Sumw2();

	int etaEventN = 0;

	/*
		PID

		-2212: 		anti-proton
		-321:		Kaon-
		-211:		pion-
		22:			photon
		111:		pion0
		211:		pion+
		321:		kaon+
		2212: 		proton
	*/

	for(int i=0; i<nevent; i++)
	{
		opt3 -> GetEntry(i);

		if(i_nAbsProj == 1 and i_nAbsTarg != 0 and np != 0)
		{
			for(int j=0; j<np; j++)
			{

				if(p_id[j] == -211 or p_id[j] == 211)

						pionEta -> Fill(p_eta[j]);

				else if(p_id[j] == -321 or p_id[j] == 321)

						kaonEta -> Fill(p_eta[j]);

				else if(p_id[j] == 2212 or p_id[j] == -2212)

						protonEta -> Fill(p_eta[j]);

			}
			
		}
		
		if(i%10000 == 0)
				cout << i <<"'th event calculated" << endl;

	}//i

	TFile *output = new TFile("pAu200GeV_option3_dirExcluded_dNdeta_1e5Events.root", "recreate");
	
	pionEta -> Write();
	kaonEta -> Write();
	protonEta -> Write();

	output -> Close();


}
