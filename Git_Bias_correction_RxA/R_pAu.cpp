void R_pAu()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis_etacut_INEL_1e5_rebined.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5_rebined.root", "read");
	TFile* input3 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	
	//historams
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	TH1D* pp = (TH1D*)input2 -> Get("pTpion0");

	TProfile* avgNcoll = (TProfile*)input3 -> Get("avgNcoll");

	//pAu yield in 70~80%
	TH1D* pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");

	double num1 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);
	double scalar1 = 1./(pAu1 -> GetBinWidth(1) * num1);
	
	pAu1 -> Scale(scalar1);

	//R_pAu 0~10%
	TH1D* R_pAu1 = new TH1D();

	*R_pAu1 = (*pAu1)/(*pp);

	double scalar2 = 1./(avgNcoll -> GetBinContent(5));

	R_pAu1 -> Scale(scalar2);
	
	R_pAu1 -> Draw();

}
