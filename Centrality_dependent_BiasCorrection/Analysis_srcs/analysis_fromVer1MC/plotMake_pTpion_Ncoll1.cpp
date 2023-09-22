/*************************************************
* pion0's invariant yield *

** Reference yield: no categorization
				    by centrality

* Ncoll = 1 events are used as pp yield for RpAu

	* Event number not scaled
	* binwidth not scaled

*************************************************/

void plotMake_pTpion_Ncoll1()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_Ncoll1.root", "read");
	TH2D* h2pTcent = (TH2D*)input -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");
	
	//pp(Ncoll = 1) yield(not scaled)
	TH1D* pp = (TH1D*)h2pTcent -> ProjectionY("ppYield");
	
	//scale factor: eventN, binwidth
	double scalar1 = 1./(pp -> GetBinWidth(1) * h2ncollcent -> Integral() );
	
	//Invariat yield
	pp -> Scale(scalar1);
		
	//Draw histogram
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1F *htmp = (TH1F*)gPad -> DrawFrame(0, 0, 7, 8);

		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
		htmp -> GetXaxis() -> SetTitleSize(0.05);
		htmp -> GetXaxis() -> SetLabelSize(0.04);
		htmp -> GetXaxis() -> SetTitleOffset(1.1);
		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
		htmp -> GetYaxis() -> SetTitleSize(0.05);
		htmp -> GetYaxis() -> SetLabelSize(0.04);	

		pp -> SetMarkerStyle(20);
		pp -> SetMarkerColor(1);
		pp -> SetLineColor(1);
		pp -> Draw("p same");

		//adding legend
		TLegend* leg1 = new TLegend(0.53, 0.63, 0.83, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.04);
		leg1 -> AddEntry("", "PYTHIA8", "h");
		leg1 -> AddEntry("", "p+Au 200 GeV", "h");
		leg1 -> AddEntry("", "option = 3(No diffraction)", "h");
		leg1 -> AddEntry("", "N_{coll}=1 event", "h");
		leg1 -> AddEntry("", "|#eta|<1", "h");
		leg1 -> AddEntry(pp, "#pi^{0}", "p");
		leg1 -> Draw();

	
		
	}

}

