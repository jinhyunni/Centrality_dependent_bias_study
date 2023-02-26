/*************************************************
* pion0's invariant yield  by centrality *
	
	class1 0~10%
	class2 10~20%
	class3 20~40%
	class4 40~60%
	class5 60~80%

	* h2pTcent: 
		x: cent
		y: pion0's pT

		-> projectionX(centralirty -# of events)
		-> projectionY(pT-# ofpion0 )
	
***********************************************/

void plotMake_ncoll()
{
	//Read in TFile
	TFile* input = new TFile("pAu200GeV_option3_pion0Analysis_1e5.root", "read");
	TH2D* h2ncollcent = (TH2D*)input -> Get("ncoll_cent");

	//# of event by centrality
	TH1D* h1NeventCent = (TH1D*)h2ncollcent -> ProjectionX("h1NeventCent");
	
	//centrality class
	TH1D* h1NcollClass1 = (TH1D*)h2ncollcent -> ProjectionY("h1NcollClass1", 1, 1);
	TH1D* h1NcollClass2 = (TH1D*)h2ncollcent -> ProjectionY("h1NcollClass2", 2, 2);
	TH1D* h1NcollClass3 = (TH1D*)h2ncollcent -> ProjectionY("h1NcollClass3", 3, 4);
	TH1D* h1NcollClass4 = (TH1D*)h2ncollcent -> ProjectionY("h1NcollClass4", 5, 6);
	TH1D* h1NcollClass5 = (TH1D*)h2ncollcent -> ProjectionY("h1NcollClass5", 7, 8);
	
	//calculating total sum
	
	//Class1
	int sum1 = 0;
	float ncollC1 = 0.;
	for(int i = 0; i < h1NcollClass1 -> GetNbinsX(); i++){
		sum1 += (i-1)*h1NcollClass1 -> GetBinContent(i);
	}
	
	ncollC1 = sum1/(h1NeventCent -> GetBinContent(1));
	cout<<ncollC1<<endl;

	//Class2
	int sum2 = 0;
	float ncollC2 = 0.;
	for(int i = 0; i < h1NcollClass2 -> GetNbinsX(); i++){
		sum2 += (i-1)*h1NcollClass2 -> GetBinContent(i);
	}
	
	ncollC2 = sum2/(h1NeventCent -> GetBinContent(2));
	cout<<ncollC2<<endl;

	//Class3
	int sum3 = 0;
	float ncollC3 = 0.;
	for(int i = 0; i < h1NcollClass3 -> GetNbinsX(); i++){
		sum3 += (i-1)*h1NcollClass3 -> GetBinContent(i);
	}
	
	ncollC3 = sum3/(h1NeventCent -> GetBinContent(3) + h1NeventCent -> GetBinContent(4));
	cout<<ncollC3<<endl;

	//Class4
	int sum4 = 0;
	float ncollC4 = 0.;
	for(int i = 0; i < h1NcollClass4 -> GetNbinsX(); i++){
		sum4 += (i-1)*h1NcollClass4 -> GetBinContent(i);
	}
	
	ncollC4 = sum4/(h1NeventCent -> GetBinContent(5) + h1NeventCent -> GetBinContent(6));
	cout<<ncollC4<<endl;

	//Class5
	int sum5 = 0;
	float ncollC5 = 0.;
	for(int i = 0; i < h1NcollClass5 -> GetNbinsX(); i++){
		sum5 += (i-1)*h1NcollClass1 -> GetBinContent(i);
	}
	
	ncollC5 = sum5/(h1NeventCent -> GetBinContent(7) + h1NeventCent -> GetBinContent(8));
	cout<<ncollC5<<endl;

	//ncoll
	TH1D* avgNcoll = new TH1D("avgNcoll", "", 5, 1, 6);
	avgNcoll -> Fill(1, ncollC1);
	avgNcoll -> Fill(2, ncollC2);
	avgNcoll -> Fill(3, ncollC3);
	avgNcoll -> Fill(4, ncollC4);
	avgNcoll -> Fill(5, ncollC5);
	
	avgNcoll -> Sumw2();
	avgNcoll -> Draw();


 //	//Draw histogram
 //	gStyle -> SetOptStat(0);
 //	TCanvas *c1 = new TCanvas("", "", 800, 600);
 //	{
 //		c1 -> cd();
 //
 //		gPad -> SetTicks();
 //		gPad -> SetLeftMargin(0.15);
 //		gPad -> SetRightMargin(0.15);
 //		gPad -> SetTopMargin(0.05);
 //		gPad -> SetBottomMargin(0.12);
 //
 //		TH1F *htmp = (TH1F*)gPad -> DrawFrame(1, 0, 6, 10);
 //
 //		htmp -> GetXaxis() -> SetTitle("p_{T}(GeV)");
 //		htmp -> GetXaxis() -> SetTitleSize(0.05);
 //		htmp -> GetXaxis() -> SetLabelSize(0.04);
 //		htmp -> GetXaxis() -> SetTitleOffset(1.1);
 //		htmp -> GetYaxis() -> SetTitle("#frac{1}{N_{evt}} #frac{dN}{dp_{T}}");
 //		htmp -> GetYaxis() -> SetTitleSize(0.05);
 //		htmp -> GetYaxis() -> SetLabelSize(0.04);	
 //
 //		h1avgNcoll -> SetMarkerStyle(21);
 //		h1avgNcoll -> SetMarkerColor(38);
 //		h1avgNcoll -> SetLineColor(38);
 //		h1avgNcoll -> Draw("p same");
 //
 //		//adding legend
 //		TLegend *leg = new TLegend(0.53, 0.63, 0.83, 0.93);
 //		leg -> SetFillStyle(0);
 //		leg -> SetBorderSize(0);
 //		leg -> SetTextSize(0.04);
 //		leg -> AddEntry("", "PYTHIA8", "h");
 //		leg -> AddEntry("", "p+Au 200 GeV", "h");
 //		leg -> AddEntry("", "option = 3(No diffraction)", "h");
 //		leg -> AddEntry("", "100,000 events", "h");
 //		leg -> AddEntry("", "#LTNcoll#GT", "h");	
 //		leg -> Draw();
 //		
 //	}
}

