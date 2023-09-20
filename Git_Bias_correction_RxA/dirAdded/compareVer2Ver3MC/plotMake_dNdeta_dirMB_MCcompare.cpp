void plotMake_dNdeta_dirMB_MCcompare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dNdeta_ver2ver3MC_compare.root", "read");
  
    //dndeta in MB events
    TH1D *dir_ver2 = (TH1D*)input1 -> Get("h1eta_dir_ver2");
    TH1D *dir_ver3 = (TH1D*)input1 -> Get("h1eta_dir_ver3");
    TH1D *dir_ver3_test = (TH1D*)input1 -> Get("h1eta_dir_ver3_test");
 //    TH1D *dir_ver3_test_2e7 = (TH1D*)input1 -> Get("h1eta_dir_ver3_test_2e7events");
 //    TH1D *dir_ver3_3e7 = (TH1D*)input1 -> Get("h1eta_dir_ver3_3e7events");
 //    TH1D *dir_ver3_tmp = (TH1D*)input1 -> Get("h1eta_dir_ver3_tmp");
 //    TH1D *dir_ver2_tmp = (TH1D*)input1 -> Get("h1eta_dir_ver2_tmp");
 //    TH1D *dir_ver3_inNPL = (TH1D*)input1 -> Get("h1eta_dir_ver3_inNPL");
    TH1D *dir_ver3_nplRootOnly = (TH1D*)input1 -> Get("h1eta_dir_ver3_nplRootOnly");
       
   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-1, 0.00026, 1, 0.00045);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN/d#eta");
    
        dir_ver2 -> SetMarkerStyle(25);
        dir_ver2 -> SetMarkerColor(kBlue);
        dir_ver2 -> SetLineColor(kBlue);
        dir_ver2 -> Draw("p same");

        dir_ver3 -> SetMarkerStyle(34);
        dir_ver3 -> SetMarkerColor(kCyan+2);
        dir_ver3 -> SetLineColor(kCyan+2);
        dir_ver3 -> Draw("p same");

        dir_ver3_test -> SetMarkerStyle(20);
        dir_ver3_test -> SetMarkerColor(kBlue);
        dir_ver3_test -> SetLineColor(kBlue);
        dir_ver3_test -> Draw("p same");

 //        dir_ver3_test_2e7 -> SetMarkerStyle(20);
 //        dir_ver3_test_2e7 -> SetMarkerColor(kAzure+9);
 //        dir_ver3_test_2e7 -> SetLineColor(kAzure+9);
 //        dir_ver3_test_2e7 -> Draw("p same");
 //
 //
 //        dir_ver3_3e7 -> SetMarkerStyle(34);
 //        dir_ver3_3e7 -> SetMarkerColor(kBlue-2);
 //        dir_ver3_3e7 -> SetLineColor(kBlue-2);
 //        dir_ver3_3e7 -> Draw("p same");
        
    
 //        dir_ver3_tmp -> SetMarkerStyle(47);
 //        dir_ver3_tmp -> SetMarkerColor(kCyan-6);
 //        dir_ver3_tmp -> SetLineColor(kCyan-6);
 //        dir_ver3_tmp -> Draw("p same");  
 //
 //        dir_ver2_tmp -> SetMarkerStyle(29);
 //        dir_ver2_tmp -> SetMarkerColor(kBlue+3);
 //        dir_ver2_tmp -> SetLineColor(kBlue+3);
 //        dir_ver2_tmp -> Draw("p same");
 //    
 //        dir_ver3_inNPL -> SetMarkerStyle(4);
 //        dir_ver3_inNPL -> SetMarkerColor(kBlue+3);
 //        dir_ver3_inNPL -> SetLineColor(kBlue+3);
 //        dir_ver3_inNPL -> Draw("p same");

        dir_ver3_nplRootOnly -> SetMarkerStyle(28);
        dir_ver3_nplRootOnly -> SetMarkerColor(kPink+7);
        dir_ver3_nplRootOnly -> SetLineColor(kPink+7);
        dir_ver3_nplRootOnly -> Draw("p same");

        TLegend *leg1 = new TLegend(0.2, 0.65, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","MB events", "h");
        leg1 -> AddEntry(dir_ver2, "#gamma^{dir} in ver2. MC", "p");
        leg1 -> AddEntry(dir_ver3, "#gamma^{dir} in ver3. MC", "p");
        leg1 -> AddEntry(dir_ver3_test, "#gamma^{dir} in ver3. test MC", "p");
        leg1 -> AddEntry(dir_ver3_nplRootOnly, "#gamma^{dir} in ver3, root Only", "p");
 //        leg1 -> AddEntry(dir_ver3_test_2e7, "#gamma^{dir} in ver3. test MC, 2e7 Events", "p");
 //        leg1 -> AddEntry(dir_ver3_3e7, "#gamma^{dir} in ver3. MC, 3e7 Events", "p");
 //        leg1 -> AddEntry(dir_ver2_tmp, "#gamma^{dir} in ver2. tmp -> in KIAF", "p");
 //        leg1 -> AddEntry(dir_ver3_inNPL, "#gamma^{dir} in ver3, 10^{7} events in NPL", "p");
        
		leg1 -> Draw();

        TLegend *leg2 = new TLegend(0.5, 0.75, 0.7, 0.93);
        leg2 -> SetFillStyle(0);
        leg2 -> SetBorderSize(0);
        leg2 -> SetTextSize(0.02);
        leg2 -> AddEntry("", "ver.2: 3 #times 10^{7} eventsn in NPL server", "h");
        leg2 -> AddEntry("", "ver.3: 10^{9} events, in KIAF server", "h");
        leg2 -> AddEntry("", "ver.3 test: 3 #times 10^{7} events, in NPL server", "h");
        //leg2 -> AddEntry("", "ver3. tmp: 10^{8} events in KIAF, used copied mainEx00a.cc from NPL", "h");
 //        leg2 -> AddEntry("", "ver2. tmp: 3 #times 10^{7} events in KIAF", "h");
 //        leg2 -> AddEntry("", "ver3. in NPL: 10^{7} events in NPL", "h");

        //leg2 -> Draw();

	}


}
