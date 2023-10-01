void plotMake_pTsum_distribution()
{

    //Inputs
   	TFile *input1 = new TFile("pAu200GeV_kiaf_option3_pTsum_distribution.root", "read");
    
    TH1D *inElastic = (TH1D*)input1 -> Get("pTsum_inelastic");
    TH1D *inPion0 = (TH1D*)input1 -> Get("pTsum_inPion0");
    TH1D *inDir = (TH1D*)input1 -> Get("pTsum_inDir");
   
    inElastic -> Scale(1./inElastic -> Integral());
    inPion0 -> Scale(1./inPion0 -> Integral());
    inDir -> Scale(1./inDir -> Integral());
    
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.15);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0.1, 0, 20, 0.03);

        htmp -> GetXaxis() -> SetTitle("p_{T} sum (GeV)");
		htmp -> GetYaxis() -> SetTitle("P(p_{T} sum)");
    
        inElastic -> SetMarkerStyle(20);
        inElastic -> SetMarkerColor(6);
        inElastic -> SetLineColor(6);
        inElastic -> Draw("p same");

        inPion0 -> SetMarkerStyle(46);
        inPion0 -> SetMarkerColor(8);
        inPion0 -> SetLineColor(8);
        inPion0 -> Draw("p same");

        inDir -> SetMarkerStyle(34);
        inDir -> SetMarkerColor(9);
        inDir -> SetLineColor(9);
        inDir -> Draw("p same");

		TLegend *leg1 = new TLegend(0.41, 0.53, 0.81, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
        leg1 -> AddEntry("" ,"p_{T} sum of #pi^{#pm}, k^{#pm}, p^{#pm} in -3.9<#eta<-3.0", "h");
        leg1 -> AddEntry(inElastic, "inelastic events", "p");
        leg1 -> AddEntry(inPion0, "events #pi^{0} produced in |#eta|<1", "p");
        leg1 -> AddEntry(inDir, "events #gamma^{dir} produced in |#eta|<1", "p");
		
        leg1 -> Draw();

	}


}
