void plotMake_dNdetaDirphoton_inTargetEvents_compareMC()
{
	TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_dNdeta_inTargetEvents_testForNewMC.root", "read");

    TString oldMC = Form("/Users/jinhyunpark/npl/gitHub/git_share/Git_Bias_correction_RxA/dirAdded/gammaPion0Analysis/%s", "pAu200GeV_option3_dirAdded_decayOn_dNdeta_inTargetEvents.root");
    TFile *input2 = new TFile(oldMC, "read");
    
    //dndeta_new MC
    TH1D *new_dir_inpion0 = (TH1D*)input1 -> Get("dndeta_dir_pion0");
    TH1D *new_dir_indir = (TH1D*)input1 -> Get("dndeta_dir_dir");   
    TH1D *new_nEvents = (TH1D*)input1 -> Get("nEvents");

    TH1D *new_dndeta_dir_inpion0 = (TH1D*)new_dir_inpion0 -> Clone("new_dndeta_pion0_inpion0");
    new_dndeta_dir_inpion0 -> Scale(1./new_nEvents -> GetBinContent(111));

    TH1D *new_dndeta_dir_indir = (TH1D*)new_dir_indir -> Clone("new_dndeta_pion0_dir");
    new_dndeta_dir_indir -> Scale(1./new_nEvents -> GetBinContent(22));
    
    //dndeta_old MC
    TH1D *old_dir_inpion0 = (TH1D*)input2 -> Get("dndeta_dir_pion0");
    TH1D *old_dir_indir = (TH1D*)input2 -> Get("dndeta_dir_dir");
    TH1D *old_nEvents = (TH1D*)input2 -> Get("nEvents");

    TH1D *old_dndeta_dir_inpion0 = (TH1D*)old_dir_inpion0 -> Clone("old_dndeta_dir_inpion0");
    old_dndeta_dir_inpion0 -> Scale(1./old_nEvents -> GetBinContent(111));

    TH1D *old_dndeta_dir_indir = (TH1D*)old_dir_indir -> Clone("old_dndeta_dir_indir");
    old_dndeta_dir_indir -> Scale(1./old_nEvents -> GetBinContent(22));
       
   
   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 1);

		htmp -> GetXaxis() -> SetTitle("#eta");
		htmp -> GetYaxis() -> SetTitle("1/N_{event} dN^{#gamma^{dir}}/d#eta");
        
        new_dndeta_dir_inpion0 -> SetMarkerStyle(29);
        new_dndeta_dir_inpion0 -> SetMarkerColor(1);
        new_dndeta_dir_inpion0 -> SetLineColor(1);
        new_dndeta_dir_inpion0 -> Draw("p same");
        
        old_dndeta_dir_inpion0 -> SetMarkerStyle(25);
        old_dndeta_dir_inpion0 -> SetMarkerColor(1);
        old_dndeta_dir_inpion0 -> SetLineColor(1);
        old_dndeta_dir_inpion0 -> Draw("p same");
        
 //        new_dndeta_dir_indir -> SetMarkerStyle(29);
 //        new_dndeta_dir_indir -> SetMarkerColor(2);
 //        new_dndeta_dir_indir -> SetLineColor(2);
 //        new_dndeta_dir_indir -> Draw("p same");
 //        
 //    
 //        old_dndeta_dir_indir -> SetMarkerStyle(25);
 //        old_dndeta_dir_indir -> SetMarkerColor(2);
 //        old_dndeta_dir_indir -> SetLineColor(2);
 //        old_dndeta_dir_indir -> Draw("p same");
 //
        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
        leg1 -> AddEntry(new_dndeta_dir_inpion0, "#gamma^{dir}, #pi^{0} in mid-rapidity, New-MC sets", "p");
        leg1 -> AddEntry(old_dndeta_dir_inpion0, "#gamma^{dir}, #pi^{0} in mid-rapidity, Old-MC sets", "p");
 //        leg1 -> AddEntry(new_dndeta_dir_indir, "#gamma^{dir}, #gamma^{dir} in mid-rapidity, Ver3. test MC sets", "p");
 //        leg1 -> AddEntry(old_dndeta_dir_indir, "#gamma^{dir}, #gamma^{dir} in mid-rapidity, Ver2. MC sets", "p");
 //        
		leg1 -> Draw();

	}


}
