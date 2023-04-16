void A_pidCheck()
{
	//Read in files
	TFile *input1 = new TFile("pAu200GeV_option3_particleID.root", "read");

	//Get Histogram
	TH1F *pid = (TH1F*)input1 -> Get("pid");

	//Get pid
	for(int i = 1; i <= 6000; i++)
	{
		if(pid -> GetBinContent(i) != 0)
			cout << "particle ID is : " << -(pid -> GetNbinsX()/2)+i-1 << endl;
		
	}
}
