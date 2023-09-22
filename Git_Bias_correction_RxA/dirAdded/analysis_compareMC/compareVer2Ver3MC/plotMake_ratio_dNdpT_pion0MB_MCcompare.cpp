void plotMake_ratio_dNdpT_pion0MB_MCcompare()
{
	TFile *input1 = new TFile("pAu200GeV_option3_ratio_dNdpT_MCcompare.root", "read");
  
    //dndeta in MB events
    
    TH1D *ver2npl_8303_externalOn = (TH1D*)input1 -> Get("pion0_pTratio_ver2npl_8303_externalOn");
    TH1D *ver3kiaf_8307_externalOff = (TH1D*)input1 -> Get("pion0_pTratio_ver3kiaf_8307_externalOff");
    TH1D *ver3npl_8303_externalOff = (TH1D*)input1 -> Get("pion0_pTratio_ver3npl_8303_externalOff");
    TH1D *ver3kiaf_8303_externalOff = (TH1D*)input1 -> Get("pion0_pTratio_ver3kiaf_8303_externalOff");

   	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);
    
        //mid-rapidity
	//	TH1D *htmp = (TH1D*)gPad -> DrawFrame(-1.5, 2.6, 1.5, 5);

        //full-rapidity
		TH1D *htmp = (TH1D*)gPad -> DrawFrame(0, 0.8, 15, 2.0);

		htmp -> GetXaxis() -> SetTitle("p_{T}");
		htmp -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}})_{target MC} / (#frac{1}{N_{event}} #frac{dN^{#pi^{0}}}{dp_{T}})_{reference MC}");
    
        ver2npl_8303_externalOn -> SetMarkerStyle(25);
        ver2npl_8303_externalOn -> SetMarkerColor(kCyan+1);
        ver2npl_8303_externalOn -> SetLineColor(kCyan+1);
        ver2npl_8303_externalOn -> Draw("p same");
       
        ver3kiaf_8307_externalOff -> SetMarkerStyle(29);
        ver3kiaf_8307_externalOff -> SetMarkerColor(kRed+1);
        ver3kiaf_8307_externalOff -> SetLineColor(kRed+1);
        ver3kiaf_8307_externalOff -> Draw("p same");

        ver3npl_8303_externalOff -> SetMarkerStyle(20);
        ver3npl_8303_externalOff -> SetMarkerColor(kCyan+1);
        ver3npl_8303_externalOff -> SetLineColor(kCyan+1);
        ver3npl_8303_externalOff -> Draw("p same");
    
        ver3kiaf_8303_externalOff -> SetMarkerStyle(28);
        ver3kiaf_8303_externalOff -> SetMarkerColor(kRed+1);
        ver3kiaf_8303_externalOff -> SetLineColor(kRed+1);
        ver3kiaf_8303_externalOff -> Draw("p same");


        TLegend *leg1 = new TLegend(0.2, 0.60, 0.5, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
		leg1 -> AddEntry("","MB events", "h");
		leg1 -> AddEntry("","reference MC : ver3, pythia8303, external package attatcged, NPL", "h");
        leg1 -> AddEntry(ver2npl_8303_externalOn, "target: ver2, pythia8303, external package attatched, NPL", "p");
        leg1 -> AddEntry(ver3kiaf_8307_externalOff, "target: ver3, pythia8307, root only,KIAF", "p");
        leg1 -> AddEntry(ver3npl_8303_externalOff, "target: ver3, pythia8303, root only, NPL", "p");
        leg1 -> AddEntry(ver3kiaf_8303_externalOff, "target: ver3, pythia8303, root only, KIAF", "p");

        
		leg1 -> Draw();


	}


}
