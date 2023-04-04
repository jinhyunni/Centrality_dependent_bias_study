#include <iostream>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"

void plotMake_YieldN_ratio()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option1_pion0Analysis.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option1_avgNcoll.root", "read");
	
	//historams

	////pAu
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");

	////avgNcoll
	TProfile* avgNcoll = (TProfile*)input2 -> Get("avgNcoll");

	//Rebin binedges
 //	double xbins[]={0, 0.5, 1, 2, 3, 4, 5, 6, 7, 8};	

	//pAu yield
	TH1D* pAu1R = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);
	TH1D* pAu2R = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);
	TH1D* pAu3R = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);
	TH1D* pAu4R = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);
	TH1D* pAu5R = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);

 //	//Rebin pAu yield
 //	TH1D* pAu1R = (TH1D*)pAu1 -> Rebin(9, "pAuR1", xbins);
 //	TH1D* pAu2R = (TH1D*)pAu2 -> Rebin(9, "pAuR2", xbins);
 //	TH1D* pAu3R = (TH1D*)pAu3 -> Rebin(9, "pAuR3", xbins);
 //	TH1D* pAu4R = (TH1D*)pAu4 -> Rebin(9, "pAuR4", xbins);
 //	TH1D* pAu5R = (TH1D*)pAu5 -> Rebin(9, "pAuR5", xbins);

	//scaling pAu yield
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");

	double num1 = h1cent -> GetBinContent(1);
	double num2 = h1cent -> GetBinContent(2);
	double num3 = h1cent -> GetBinContent(3) + h1cent -> GetBinContent(4);
	double num4 = h1cent -> GetBinContent(5) + h1cent -> GetBinContent(6);
	double num5 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);

	double scalar11 = 1./(pAu1R -> GetBinWidth(1) * num1 * avgNcoll -> GetBinContent(1));
	double scalar12 = 1./(pAu2R -> GetBinWidth(1) * num2 * avgNcoll -> GetBinContent(2));
	double scalar13 = 1./(pAu3R -> GetBinWidth(1) * num3 * avgNcoll -> GetBinContent(3));
	double scalar14 = 1./(pAu4R -> GetBinWidth(1) * num4 * avgNcoll -> GetBinContent(4));
	double scalar15 = 1./(pAu5R -> GetBinWidth(1) * num5 * avgNcoll -> GetBinContent(5));

	//<Ncoll> scailing
	pAu1R -> Scale(scalar11);
	pAu2R -> Scale(scalar12);
	pAu3R -> Scale(scalar13);
	pAu4R -> Scale(scalar14);
	pAu5R -> Scale(scalar15);



	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas* c1 = new TCanvas("", "", 800, 600);
	{
		
		c1 -> cd();
		
		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);
		gPad -> SetLogx();

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(0, 0, 10, 8.0);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("Y_{pAu}/#LTN_{coll}#GT");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

		pAu1R -> SetMarkerStyle(20);
		pAu1R -> SetMarkerColor(1);
		pAu1R -> SetLineColor(1);
		pAu1R -> Draw("p_same");

		pAu2R -> SetMarkerStyle(21);
		pAu2R -> SetMarkerColor(2);
		pAu2R -> SetLineColor(2);
		pAu2R -> Draw("p_same");

		pAu3R -> SetMarkerStyle(22);
		pAu3R -> SetMarkerColor(3);
		pAu3R -> SetLineColor(3);
		pAu3R -> Draw("p_same");

		pAu4R -> SetMarkerStyle(23);
		pAu4R -> SetMarkerColor(4);
		pAu4R -> SetLineColor(4);
		pAu4R -> Draw("p_same");

		pAu5R -> SetMarkerStyle(28);
		pAu5R -> SetMarkerColor(6);
		pAu5R -> SetLineColor(6);
		pAu5R -> Draw("p_same");

		//addig legend
		TLegend* leg1 = new TLegend(0.53, 0.57, 0.83, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option1(Fluctuation O)", "h");
		leg1 -> AddEntry("", "#pi^{0}, |#eta|<1", "h");
		//leg1 -> AddEntry("", "", "");
		leg1 -> AddEntry(pAu1R, "0~10%", "p");
		leg1 -> AddEntry(pAu2R, "10~20%", "p");
		leg1 -> AddEntry(pAu3R, "20~40%", "p");
		leg1 -> AddEntry(pAu4R, "40~60%", "p");
		leg1 -> AddEntry(pAu5R, "60~80%", "p");
		leg1 -> Draw();

	}

}
