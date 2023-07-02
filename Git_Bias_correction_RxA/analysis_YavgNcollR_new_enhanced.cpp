void analysis_YavgNcollR_new_enhanced()
{
	//Read in files
	TFile *input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	
	//pion0's pT and centrality correlation
	TH2D *h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");

	//pion0's Ncoll and centrality correlation
	TH2D *h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	//avgNcoll by centrality class
	TProfile *avgNcoll = (TProfile*)input2 -> Get("avgNcoll");

	/*
		# of particle in each centrality class of each pT class

		pTclass: 
			1. 0~2 GeV
			2. 2~5 GeV
			3. 5~ GeV

		centrality class:
			1. 0~10%
			2. 10~20%
			3. 20~40%
			4. 40~60%
			5. 60~80%
	*/
	
	// Divide pT class
	TH1D *pTclass1 = (TH1D*)h2pTcent -> ProjectionX("pTclass1", 1, 199);	
	TH1D *pTclass2 = (TH1D*)h2pTcent -> ProjectionX("pTclass2", 200, 499);
	TH1D *pTclass3 = (TH1D*)h2pTcent -> ProjectionX("pTclass3", 500, 1400);
	
	//Get Centrality class
	double binCent[] = {0, 10, 20, 40, 60, 80};
	
	TH1D *pTclass1R = (TH1D*)pTclass1 -> Rebin(5, "pTclass1", binCent);
	TH1D *pTclass2R = (TH1D*)pTclass2 -> Rebin(5, "pTclass2", binCent);
	TH1D *pTclass3R = (TH1D*)pTclass3 -> Rebin(5, "pTclass3", binCent);

	//for checking
	cout << pTclass1R -> GetBinContent(1) << endl;
	cout << pTclass1R -> GetBinContent(2) << endl;
	cout << pTclass1R -> GetBinContent(3) << endl;
	cout << pTclass1R -> GetBinContent(4) << endl;
	cout << pTclass1R -> GetBinContent(5) << endl;
	
	/*
		pT binwidth and eta-range divided

		pT binwidth: 14/1400	*pT binning ignored
		eta range: -1~1			*eta binning considered
	*/

	double scalar1 = 1/2.;
	pTclass1R -> Scale(scalar1);
	pTclass2R -> Scale(scalar1);
	pTclass3R -> Scale(scalar1);

	/*
		Event number by each centrality class divided
		
		To get event# by each centrality class
		h2ncollcent -> ProjectionX()
		and rebin

	*/

	TH1D *eventCent = (TH1D*)h2ncollcent -> ProjectionX();
	TH1D *eventCentR = (TH1D*)eventCent -> Rebin(5, "eventCentR", binCent);
	
	(*pTclass1R) = (*pTclass1R)/(*eventCentR);
	(*pTclass2R) = (*pTclass2R)/(*eventCentR);
	(*pTclass3R) = (*pTclass3R)/(*eventCentR);
	
	/*
		Centrality binwidth divided

		binwidth of centrality classes
					
			class1 -> 10
			class2 -> 10
			class3 -> 20
			class4 -> 20
			class5 -> 20
	*/
	

	for(int i=0; i<5; i++)
	{
		
		cout << "Before scaling : " << pTclass1R -> GetBinContent(i+1) << endl;

		double scalar2 = pTclass1R -> GetBinWidth(i+1);
		
		pTclass1R -> SetBinContent(i+1, pTclass1R -> GetBinContent(i+1)/scalar2);
		pTclass2R -> SetBinContent(i+1, pTclass2R -> GetBinContent(i+1)/scalar2);
		pTclass3R -> SetBinContent(i+1, pTclass3R -> GetBinContent(i+1)/scalar2);

		cout << "After scaling : " << pTclass1R -> GetBinContent(i+1) << endl;
		cout << "\n" << endl;
	}

	pTclass1R -> Draw();
}
