void plotMake_dNdeta_dirMB_MCcompare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dNdeta_ver2ver3MC_compare.root", "read");
  
    //dndeta in MB events
    TH1D *dir_ver2 = (TH1D*)input1 -> Get("h1eta_dir_ver2");
    TH1D *dir_ver3 = (TH1D*)input1 -> Get("h1eta_dir_ver3");
    TH1D *dir_ver3_test = (TH1D*)input1 -> Get("h1eta_dir_ver3_test");
    TH1D *dir_ver3_3e7 = (TH1D*)input1 -> Get("h1eta_dir_ver3_3e7events");
       
   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 0.0008);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        dir_ver2 -> SetMarkerStyle(20);
        dir_ver2 -> SetMarkerColor(kBlue);
        dir_ver2 -> SetLineColor(kBlue);
        dir_ver2 -> Draw("p same");

        dir_ver3 -> SetMarkerStyle(20);
        dir_ver3 -> SetMarkerColor(kBlue+4);
        dir_ver3 -> SetLineColor(kBlue+4);
        dir_ver3 -> Draw("p same");

        dir_ver3_test -> SetMarkerStyle(20);
        dir_ver3_test -> SetMarkerColor(kBlue-10);
        dir_ver3_test -> SetLineColor(kBlue-10);
        dir_ver3_test -> Draw("p same");

        dir_ver3_3e7 -> SetMarkerStyle(20);
        dir_ver3_3e7 -> SetMarkerColor(kBlue-2);
        dir_ver3_3e7 -> SetLineColor(kBlue-2);
        dir_ver3_3e7 -> Draw("p same");


        
        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","MB events", "h");
        leg1 -> AddEntry(dir_ver2, "#gamma^{dir} in ver2. MC", "p");
        leg1 -> AddEntry(dir_ver3, "#gamma^{dir} in ver3. MC", "p");
        leg1 -> AddEntry(dir_ver3_test, "#gamma^{dir} in ver3. test MC", "p");
        leg1 -> AddEntry(dir_ver3_3e7, "#gamma^{dir} in ver3. MC, 3e7 Events", "p");
        
		leg1 -> Draw();

        TLegend *leg2 = new TLegend(0.5, 0.80, 0.8, 0.93);
        leg2 -> SetFillStyle(0);
        leg2 -> SetBorderSize(0);
        leg2 -> SetTextSize(0.03);
        leg2 -> AddEntry("", "ver.2: 3 #times 10^{7} events", "h");
        leg2 -> AddEntry("", "ver.3: 10^{9} events", "h");
        leg2 -> AddEntry("", "vet.3: 3 #times 10^{7} events", "h");

        leg2 -> Draw();

	}


}
