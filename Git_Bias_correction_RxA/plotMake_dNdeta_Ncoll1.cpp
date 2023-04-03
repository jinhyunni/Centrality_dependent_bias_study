#include <iostream>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"

void plotMake_dNdeta_Ncoll1()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_dNchdeta_Ncoll1.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1.root");

	//historams
	TH1D* dNdeta = (TH1D*)input1 -> Get("dNdeta");
	TH2D* eventN = (TH2D*)input2 -> Get("ncoll_cent");

	//Rebin binedges
	double xbins[]={-6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0};	

	//Rebin
	TH1D* ppR = (TH1D*)dNdeta -> Rebin(24, "ppR", xbins);

	//scalar
	double scalar1 = 1./(eventN -> Integral() * ppR -> GetBinWidth(1));

	ppR -> Scale(scalar1);

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

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 5.0);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("dN/d#eta");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

		ppR -> SetMarkerStyle(20);
		ppR -> SetMarkerColor(1);
		ppR -> SetLineColor(1);
		ppR -> Draw("p_same");

	
		//addig legend
		TLegend* leg1 = new TLegend(0.53, 0.57, 0.83, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option3(No diffraction)", "h");
		leg1 -> AddEntry("", "#pi^{#pm}, K^{#pm}, p", "h");
		leg1 -> AddEntry("", "Ncoll = 1 event: 15,181", "h");
		//leg1 -> AddEntry("", "", "");
		leg1 -> Draw();

	}

}
