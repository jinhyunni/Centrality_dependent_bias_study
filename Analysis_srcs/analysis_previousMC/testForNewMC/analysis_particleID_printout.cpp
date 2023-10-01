

void analysis_particleID_printout()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_PIDcheck_testForNewMC.root", "read");

	TH1D *hisPid = (TH1D*)input1 -> Get("pid_check");

	for(int i=0; i<10000; i++)
	{
		if(hisPid -> GetBinContent(i+1))
		{
			cout << "PID: " << -5000+i <<" # of particle: " << hisPid -> GetBinContent(i+1) << endl;
		}
	}



}
