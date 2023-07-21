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

 //	/*
 //		pT binwidth and eta-range divided
 //
 //		pT binwidth: 14/1400	*pT binning ignored
 //		eta range: -1~1			*eta binning considered
 //	*/
 //
 //	double scalar1 = 1/2.;
 //	pTclass1R -> Scale(scalar1);
 //	pTclass2R -> Scale(scalar1);
 //	pTclass3R -> Scale(scalar1);


	/*
		Event number by each centrality class divided
		
		To get event# by each centrality class
		h2ncollcent -> ProjectionX()
		and rebin
	*/

	TH1D *eventCent = (TH1D*)h2ncollcent -> ProjectionX();
	TH1D *eventCentR = (TH1D*)eventCent -> Rebin(5, "eventCentR", binCent);

	*pTclass1R = (*pTclass1R) / (*eventCentR);
	*pTclass2R = (*pTclass2R) / (*eventCentR);
	*pTclass3R = (*pTclass3R) / (*eventCentR);

	printf("For checking\n\n");
	printf("# of particle per %s per %s in each centrality class\n\n", "#eta", "#event");
	printf("%lf\n", pTclass1R -> Integral(1, 5));		//0~2 GeV
	printf("%lf\n", pTclass2R -> Integral(1, 5));		//2~5 GeV
	printf("%lf\n\n", pTclass3R -> Integral(1, 5));		//5~  GeV


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
		

		double scalar2 = pTclass1R -> GetBinWidth(i+1);

		pTclass1R -> SetBinContent(i+1, pTclass1R -> GetBinContent(i+1)/scalar2);
		pTclass2R -> SetBinContent(i+1, pTclass2R -> GetBinContent(i+1)/scalar2);
		pTclass3R -> SetBinContent(i+1, pTclass3R -> GetBinContent(i+1)/scalar2);

	}
	
	/*
	    Y_pAu/<N_coll> by centrality

		avgNcoll scailing to get Y_pAu/<N_coll>
		
		To divide with (TH1D*)pTclassXR(X: 1~3)
		Make (TH1D*)avgNcollR
	*/

	TH1D *avgNcollR = new TH1D("TH1D avgNcoll", "", 5, 0, 80);
	avgNcollR -> GetXaxis() -> Set(5, binCent);

	for(int i=0; i<5; i++)
	{
		double n1 = avgNcoll -> GetBinContent(i+1);
		double e1 = avgNcoll -> GetBinError(i+1);
		
		cout<< "avgNcoll: " << n1 << endl;
		cout<< "bin error: " << e1 << "\n" << endl;

		avgNcollR -> SetBinContent(i+1, n1);
		avgNcollR -> SetBinError(i+1, e1);

	}


	*pTclass1R = (*pTclass1R)/(*avgNcollR);
	*pTclass2R = (*pTclass2R)/(*avgNcollR);
	*pTclass3R = (*pTclass3R)/(*avgNcollR);

	pTclass1R -> Sumw2();
	pTclass2R -> Sumw2();
	pTclass3R -> Sumw2();

	
	pTclass1R -> Draw();

	cout << "\nResult\n" << endl;

	for(int i=0; i<5; i++)
	{
		cout << pTclass1R -> GetBinContent(i+1) << endl;
	}
	
	TFile *outfile = new TFile("pAu200GeV_option3_YavgNcollR_new_enhanced.root", "recreate");

	pTclass1R -> Write();
	pTclass2R -> Write();
	pTclass3R -> Write();

	outfile -> Close();

}
