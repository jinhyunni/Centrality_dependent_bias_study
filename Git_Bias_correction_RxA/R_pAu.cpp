void R_pAu()
{
	//read in files

	//avgNcoll
	TFile* avgNcollFile = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "read");
	//Get TProfile value
	TProfile* avgNcoll = (TProfile*)avgNcollFile -> Get("avgNcoll");

	//pAu yield
	TFile* pAuYield = new TFile("pAu200GeV_option3_pTpion_invarY1e5.root", "read");

	//reference yield
	TFile* refYield = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5.root", "read");
	TH1D* reference = (TH1D*)refYield -> Get("pTpion0");

	
	////Get p+Au Invariant yield
	TH1D* pAuClass1 = (TH1D*)pAuYield -> Get("pTclass1");
	
	//Rebin -> binwidth 0.5
	TH1D* pA = new TH1D("pA", "", 28, 0, 14);
	TH1D* pp = new TH1D("pp", "", 28, 0, 14);

	//21 bins
	double rebinEdge[]={0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10};


	for(int i = 0; i < pAuClass1 -> GetNbinsX(); i++){
		pAuClass1 -> Rebin(20, "pA", rebinEdge);
		reference -> Rebin(20, "pp", rebinEdge);
	}

	pA -> Draw();
	
	

}
