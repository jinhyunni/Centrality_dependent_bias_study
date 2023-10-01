void plotMake_dNdeta_forCheck()
{
	TFile *input1 = new TFile("../../analysis_allEvents_dNdeta/pAu200GeV_p8303ver2_option3_dNdetaCharge_MBevents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdeta_MBevents.root", "read");
    
    //dndeta in new MC
    //----------------
    TH1D *dndeta_new = (TH1D*)input1 -> Get("dndeta_mbevents");

    //dndeta in MB events_previous MC
    //-------------------
    TH1D *pionCh_inMB = (TH1D*)input2 -> Get("dndeta_pionCh_mb");
    TH1D *kaonCh_inMB = (TH1D*)input2 -> Get("dndeta_kaonCh_mb");
    TH1D *protonCh_inMB = (TH1D*)input2 -> Get("dndeta_protonCh_mb");
    TH1D *nEvents_inMB = (TH1D*)input2 -> Get("ncoll_mb");

    TH1D *dndeta_charge_inMB = (TH1D*)pionCh_inMB -> Clone("dndeta_charge_inMB");
    dndeta_charge_inMB -> Add(kaonCh_inMB);
    dndeta_charge_inMB -> Add(protonCh_inMB);
    dndeta_charge_inMB -> Scale(1./nEvents_inMB -> Integral());
    dndeta_charge_inMB -> Scale(2);     //divide binwidth

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
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
       
        dndeta_charge_inMB -> SetMarkerStyle(29);
        dndeta_charge_inMB -> SetMarkerColor(2);
        dndeta_charge_inMB -> SetLineColor(2);
        dndeta_charge_inMB -> Draw("p same");

        dndeta_new -> SetMarkerStyle(90);
        dndeta_new -> SetMarkerColor(1);
        dndeta_new -> SetLineColor(1);
        dndeta_new -> Draw("p same");
        

 //        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
 //		leg1 -> SetFillStyle(0);
 //		leg1 -> SetBorderSize(0);
 //		leg1 -> SetTextSize(0.03);
 //		leg1 -> AddEntry("","PYTHIA8, option3", "h");
 //		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
 //		leg1 -> AddEntry("","charged particles: #pi^{#pm}, k^{#pm}, p^{#pm}", "h");
 //        leg1 -> AddEntry(dndeta_charge_indir, "charged particles in event including #gamma^{dir} in |#eta|<1", "p");
 //        
 //		leg1 -> Draw();

	}


}
