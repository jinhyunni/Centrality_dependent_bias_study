void plotMake_dirInEx_kaondNdeta()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_dNdeta_1e5events.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_dirExcluded_dNdeta_1e5events.root", "read");

	TFile *input3 = new TFile("pAu200GeV_option3_eventNwithNch.root", "read");

	TH1D *new_pionEta = (TH1D*)input1 -> Get("dirAdded_kaonEta");
	TH1D *old_pionEta = (TH1D*)input2 -> Get("dirEx_kaonEta");

	TProfile *eventNnew = (TProfile*)input3 -> Get("new_eventN_00000");
	TProfile *eventNold = (TProfile*)input3 -> Get("old_eventN");


	new_pionEta -> Scale(1./(eventNnew -> GetBinContent(321) * new_pionEta -> GetBinWidth(1)));
	old_pionEta -> Scale(1./(eventNold -> GetBinContent(321) * old_pionEta -> GetBinWidth(1)));

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 2);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{evt} dN^{k^{#pm}}/d#eta");

		new_pionEta -> SetMarkerStyle(28);
		new_pionEta -> SetMarkerColor(2);
		new_pionEta -> SetLineColor(2);
		new_pionEta -> Draw("p same");

		old_pionEta -> SetMarkerStyle(28);
		old_pionEta -> SetMarkerColor(4);
		old_pionEta -> SetLineColor(4);
		old_pionEta -> Draw("p same");

		TLegend *leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","k^{#pm}", "h");
		leg1 -> AddEntry(old_pionEta, "#gamma excluded file", "p");
		leg1 -> AddEntry(new_pionEta, "#gamma included file", "p");

		leg1 -> Draw();

	}


}
