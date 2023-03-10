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
	TFile* pAuYield = new TFile("pAu200GeV_option3_pion0Analysis_etacut_INEL_1e5.root", "read");
	TFile* refYield = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5.root", "read");

	//Invariant yield for class 1
	TH2D* h2pTcent = (TH2D*)pAuYield -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)pAuYield -> Get("ncoll_cent");

	TH1D* pAuClass1 = (TH1D*)h2pTcent -> ProjectionY("pAuClass1", 1, 1);
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent");

	double scalar1 = 1./(pAuClass1 -> GetBinWidth(1)*h1cent -> GetBinContent(1));
	pAuClass1 -> Scale(scalar1);

	//


}
