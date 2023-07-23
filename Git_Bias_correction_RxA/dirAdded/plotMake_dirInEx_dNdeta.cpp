void plotMake_dirInEx_dNdeta()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOff_dNdeta_1e5Events.root", "read");
	TFile *input2 = new TFile("pAu200GeV_option3_dirExcluded_dNdeta_1e5events.root", "read");

	TH1D *new_pionEta = (TH1D*)input1 -> Get("dirAdded_pionEta");
	TH1D *new_kaonEta = (TH1D*)input1 -> Get("dirAdded_kaonEta");
	TH1D *new_protonEta = (TH1D*)input1 -> Get("dirAdded_protonEta");

	TH1D *new_charged = new TH1D();
	new_charged -> Sumw2();
	(*new_charged) = (*new_pionEta) + (*new_kaonEta) + (*new_protonEta);

	TH1D *old_pionEta = (TH1D*)input2 -> Get("dirEx_pionEta");
	TH1D *old_kaonEta = (TH1D*)input2 -> Get("dirEx_kaonEta");
	TH1D *old_protonEta = (TH1D*)input2 -> Get("dirEx_protonEta");

	TH1D *old_charged = new TH1D();
	old_charged -> Sumw2();
	(*old_charged) = (*old_pionEta) + (*old_kaonEta) + (*old_protonEta);

	int eventN = 1e5;
	double binwidth = 0.5;

	double scalar = 1./(eventN * binwidth);

	new_charged -> Scale(scalar);
	old_charged -> Scale(scalar);

	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 10);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("invariant yield");

		new_charged -> SetMarkerStyle(20);
		new_charged -> SetMarkerColor(2);
		new_charged -> SetLineColor(2);
		new_charged -> Draw("p same");

		old_charged -> SetMarkerStyle(28);
		old_charged -> SetMarkerColor(4);
		old_charged -> SetLineColor(4);
		old_charged -> Draw("p same");

		TLegend *leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","#pi^{#pm}/K^{#pm}/p^{#pm}", "h");
		leg1 -> AddEntry("","100,000 events", "h");
		leg1 -> AddEntry(new_charged, "#gamma included file, decayOff", "p");
		leg1 -> AddEntry(old_charged, "#gamma excluded file", "p");

		leg1 -> Draw();

	}


}
