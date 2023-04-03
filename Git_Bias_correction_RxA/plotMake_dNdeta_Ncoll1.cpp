#include <iostream>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"

void plotMake_dNdeta_Ncoll1()
{
	//Read in files
	TFile* input11 = new TFile("pAu200GeV_option0_dNchdeta_Ncoll1.root", "read");
	TFile* input12 = new TFile("pAu200GeV_option0_pion0Analysis_Ncoll1.root");

	TFile* input21 = new TFile("pAu200GeV_option1_dNchdeta_Ncoll1.root", "read");
	TFile* input22 = new TFile("pAu200GeV_option1_pion0Analysis_Ncoll1.root");

	TFile* input31 = new TFile("pAu200GeV_option3_dNchdeta_Ncoll1.root", "read");
	TFile* input32 = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1.root");

	//historams
	TH1D* dNdeta0 = (TH1D*)input11 -> Get("dNdeta");
	TH2D* eventN0 = (TH2D*)input12 -> Get("ncoll_cent");

	TH1D* dNdeta1 = (TH1D*)input21 -> Get("dNdeta");
	TH2D* eventN1 = (TH2D*)input22 -> Get("ncoll_cent");

	TH1D* dNdeta3 = (TH1D*)input31 -> Get("dNdeta");
	TH2D* eventN3 = (TH2D*)input32 -> Get("ncoll_cent");

	//Rebin binedges
	double xbins[]={-6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0};	

	//Rebin
	TH1D* ppR0 = (TH1D*)dNdeta0 -> Rebin(24, "ppR", xbins);
	TH1D* ppR1 = (TH1D*)dNdeta1 -> Rebin(24, "ppR", xbins);
	TH1D* ppR3 = (TH1D*)dNdeta3 -> Rebin(24, "ppR", xbins);

	//scalar
	double scalar0 = 1./(eventN0 -> Integral() * ppR0 -> GetBinWidth(1));
	double scalar1 = 1./(eventN1 -> Integral() * ppR1 -> GetBinWidth(1));
	double scalar3 = 1./(eventN3 -> Integral() * ppR3 -> GetBinWidth(1));

	ppR0 -> Scale(scalar0);
	ppR1 -> Scale(scalar1);
	ppR3 -> Scale(scalar3);

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

		TH1D* htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 7.0);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("dN/d#eta");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);

		ppR0 -> SetMarkerStyle(20);
		ppR0 -> SetMarkerColor(1);
		ppR0 -> SetLineColor(1);
		ppR0 -> Draw("p_same");
		
		ppR1 -> SetMarkerStyle(20);
		ppR1 -> SetMarkerColor(2);
		ppR1 -> SetLineColor(2);
		ppR1 -> Draw("p_same");

		ppR3 -> SetMarkerStyle(20);
		ppR3 -> SetMarkerColor(4);
		ppR3 -> SetLineColor(4);
		ppR3 -> Draw("p_same");

	
		//addig legend
		TLegend* leg1 = new TLegend(0.5, 0.57, 0.8, 0.93);

		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option1(Fluctuation O)", "h");
		leg1 -> AddEntry("", "#pi^{#pm}, K^{#pm}, p", "h");
		leg1 -> AddEntry(ppR1, "option1(Fluctuation O)", "p");
		leg1 -> AddEntry(ppR0, "option0(MCG)", "p");
		leg1 -> AddEntry(ppR3, "option3(No diffraction)", "p");

		//leg1 -> AddEntry("", "", "");
		leg1 -> Draw();

	}

}
