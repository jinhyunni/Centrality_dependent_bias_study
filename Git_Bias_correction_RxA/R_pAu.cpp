/*

   * Drawing Nuclear modification factor *

   *1/<Ncoll> times Y_pAu/Y_pAu(Ncoll =1)

   *File for each quantity
   	
   		1. <Ncoll>: pAu200GeV_option3_INEL_avgNcoll.root
		2. Y_pAu: pAu200GeV_option3_pion0Analysis_etacut_INEL_1e5.root	(Invariant X)
		3. Y_pAu(Ncoll = 1): pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5.root
	
   *For 5 centrality categories
    
    0~10%		-> pTpion0_cent -> ProjectionY("", 1, 1) / 
	10~20%
	20~40%
	40~60%
	60~80%



*/

void R_pAu()
{
	//read in files
	TFile* avgNcoll = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "read");
	TFile* pAuYield = new TFile("pAu200GeV_option3_pion0Analysis_invarY1e5.root", "read");

	TFile* refYield = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5.root", "read");
	TH1D* reference = (TH1D*)refYield -> Get("pTpion0")

	
	//R_pAu of centrality class 1(0~10%)
	////Get p+Au Invariant yield
	TH1D* pAuClass1 = (TH1D*)pAuYield -> Get("pTclass1");
	


}
