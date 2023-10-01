void analysis_pTandCentParticle()
{
	//input file
	TFile *input = new TFile("pAu200GeV_option3_pion0Analysis.root");

	TH2D *pTcent = (TH2D*)input -> Get("pTpion0_cent");

	double binEdge[]={0, 10, 20, 40, 60, 80};

	TH1D *pTclass1 = (TH1D*)pTcent -> ProjectionX("pTclass1", 1, 199);
	TH1D *pTclass2 = (TH1D*)pTcent -> ProjectionX("pTclass2", 200, 499);
	TH1D *pTclass3 = (TH1D*)pTcent -> ProjectionX("pTclass3", 500, 1400);
	
	//# of pion0 in each pT class and centrality class
	TH1D *pTclass1R = (TH1D*)pTclass1 -> Rebin(5, "pTclass1R", binEdge);
	TH1D *pTclass2R = (TH1D*)pTclass2 -> Rebin(5, "pTclass2R", binEdge);
	TH1D *pTclass3R = (TH1D*)pTclass3 -> Rebin(5, "pTclass3R", binEdge);

	
 //	cout << "\nIn pT class 1\n" << endl;
 //	cout << pTclass1R -> GetBinContent(1) << endl;
 //	cout << pTclass1R -> GetBinContent(2) << endl;
 //	cout << pTclass1R -> GetBinContent(3) << endl;
 //	cout << pTclass1R -> GetBinContent(4) << endl;
 //	cout << pTclass1R -> GetBinContent(5) << endl;
 //	cout <<"Total: " << pTclass1R -> Integral() << endl;
 //
 //
 //	cout << "\nIn pT class 2\n" << endl;
 //	cout << pTclass2R -> GetBinContent(1) << endl;
 //	cout << pTclass2R -> GetBinContent(2) << endl;
 //	cout << pTclass2R -> GetBinContent(3) << endl;
 //	cout << pTclass2R -> GetBinContent(4) << endl;
 //	cout << pTclass2R -> GetBinContent(5) << endl;
 //	cout << "Total: " << pTclass2R -> Integral() << endl;

	cout << "1/sqrt(N) of pT class3:" << endl;
	for(int i=1; i<=5; i++)
	{
		cout << 1./sqrt(pTclass3 -> GetBinContent(i)) << endl;
	}


	cout << "\nRelative error of pT class3:" << endl;
	for(int i=1; i<=5; i++)
	{
		cout << pTclass3 -> GetBinError(i)/pTclass3 -> GetBinContent(i) << endl;
	}

	
 //	cout << "\nIn pT class 3\n" << endl;
 //	cout << pTclass3R -> GetBinContent(1) << endl;
 //	cout << pTclass3R -> GetBinContent(2) << endl;
 //	cout << pTclass3R -> GetBinContent(3) << endl;
 //	cout << pTclass3R -> GetBinContent(4) << endl;
 //	cout << pTclass3R -> GetBinContent(5) << endl;
 //	cout << "Total: " << pTclass3R -> Integral() << endl;


}
