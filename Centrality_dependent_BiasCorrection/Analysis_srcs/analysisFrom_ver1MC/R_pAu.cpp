#include <iostream>
#include "TFile.h"
#include "TH1.h"

using namespace std;

void R_pAu()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis_etacut_INEL_1e5.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1_etacut_1e5.root", "read");
	TFile* input3 = new TFile("pAu200GeV_option3_INEL_avgNcoll.root", "read");
	
	//historams
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	TH1D* pp = (TH1D*)input2 -> Get("pTpion0");

	TProfile* avgNcoll = (TProfile*)input3 -> Get("avgNcoll");

	//pAu yield in 70~80%
	TH1D* pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");
	
	//pAu and pp yield rebined
	double xbins[] = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0};
	
	TH1D* pAuR1 = (TH1D*)pAu1 -> Rebin(20, "pAuRebined", xbins);
	TH1D* ppR1 = (TH1D*)pp -> Rebin(20, "ppRebined", xbins);
	
	pAuR1 -> Draw();

	TCanvas* c1 = new TCanvas();
	c1 -> Divide(2, 1);

	c1 -> cd(1);
	pAu1 -> Draw();

	c1 -> cd(2);
	pAuR1 -> Draw();




 //	pAu1R -> Draw();

 //	//scailing
 //	double num1 = h1cent -> GetBinContent(1);
 //	double scalar1 = 1./(pAuRebined -> GetBinWidth(1) * num1);
 //	
 //	pAuRebined -> Scale(scalar1);

 //	//R_pAu 0~10%
 //	TH1D* R_pAu1 = new TH1D();
 //
 //	*R_pAu1 = (*pAuRebined)/(*ppRebined);
 //
 //	double scalar2 = 1./(avgNcoll -> GetBinContent(1));
 //
 //	R_pAu1 -> Scale(scalar2);
 //	
 //	R_pAu1 -> Draw();

}
