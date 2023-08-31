void plotMake_dNdeta_inTargetEvents()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdeta_inTargetEvents.root", "read");
    
    TH1D *pion0_inpion0 = (TH1D*)input1 -> Get("dndeta_pion0_pion0");
    TH1D *pion0_indir = (TH1D*)input1 -> Get("dndeta_pion0_dir");
    
    TH1D *pionCh_inpion0 = (TH1D*)input1 -> Get("dndeta_pionCh_pion0");
    TH1D *kaonCh_inpion0 = (TH1D*)input1 -> Get("dndeta_kaonCh_pion0");
    TH1D *protonCh_inpion0 = (TH1D*)input1 -> Get("dndeta_protonCh_pion0");
    
    TH1D *pionCh_indir = (TH1D*)input1 -> Get("dndeta_pionCh_dir");
    TH1D *kaonCh_indir = (TH1D*)input1 -> Get("dndeta_kaonCh_dir");
    TH1D *protonCh_indir = (TH1D*)input1 -> Get("dndeta_protonCh_dir");

    TH1D *nEvents = (TH1D*)input1 -> Get("nEvents");


    TH1D *dndeta_pion0_inpion0 = (TH1D*)pion0_inpion0 -> Clone("dndeta_pion0_inpion0");
    dndeta_pion0_inpion0 -> Scale(1./nEvents -> GetBinContent(111));

    TH1D *dndeta_pion0_indir = (TH1D*)pion0_indir -> Clone("dndeta_pion0_dir");
    dndeta_pion0_indir -> Scale(1./nEvents -> GetBinContent(22));

    TH1D *dndeta_charge_inpion0 = (TH1D*)pionCh_inpion0 -> Clone("dndeta_charge_inpion0");
    dndeta_charge_inpion0 -> Add(kaonCh_inpion0);
    dndeta_charge_inpion0 -> Add(protonCh_inpion0);
    dndeta_charge_inpion0 -> Scale(1./nEvents -> GetBinContent(111));

    TH1D* dndeta_charge_indir = (TH1D*)pionCh_indir -> Clone("dneta_charge_indir");
    dndeta_charge_indir -> Add(kaonCh_indir);
    dndeta_charge_indir -> Add(protonCh_indir);
    dndeta_charge_indir -> Scale(1./nEvents -> GetBinContent(22));

   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 12);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        dndeta_charge_inpion0 -> SetMarkerStyle(34);
        dndeta_charge_inpion0 -> SetMarkerColor(9);
        dndeta_charge_inpion0 -> SetLineColor(9);
        dndeta_charge_inpion0 -> Draw("p same");
       
    
        dndeta_charge_indir -> SetMarkerStyle(25);
        dndeta_charge_indir -> SetMarkerColor(6);
        dndeta_charge_indir -> SetLineColor(6);
        dndeta_charge_indir -> Draw("p same");
        

        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","charged particles: #pi^{#pm}, k^{#pm}, p^{#pm}", "h");
        leg1 -> AddEntry(dndeta_charge_indir, "charged particles in event including #gamma^{dir} in |#eta|<1", "p");
        leg1 -> AddEntry(dndeta_charge_inpion0, "charged particles in event including #pi^{0} in |#eta|<1", "p");
        
		leg1 -> Draw();

	}


}
