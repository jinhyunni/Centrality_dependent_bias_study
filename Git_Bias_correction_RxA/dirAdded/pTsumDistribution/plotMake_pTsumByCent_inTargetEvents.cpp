void plotMake_pTsumByCent_inTargetEvents()
{

    //Inputs
   	TFile *input1 = new TFile("pAu200GeV_kiaf_option3_pTsumByCent_inTargetEvents.root", "read");
    
    TH1D *inElastic[10];
    TH1D *inPion0[10];
    TH1D *inDir[10];

    for(int i=0; i<10; i++)
    {
        TString inputElastic = Form("pTsumDis_byCentClass%d_inElastic", i+1);
        TString inputPion0 = Form("pTsumDis_byCentClass%d_inPion0", i+1);
        TString inputDir = Form("pTsumDis_byCentClass%d_inDir", i+1);

        inElastic[i] = (TH1D*)input1 -> Get(inputElastic);
        inPion0[i] = (TH1D*)input1 -> Get(inputPion0);
        inDir[i] = (TH1D*)input1 -> Get(inputDir);
    
    }

    for(int i=0; i<10; i++)
    {   
        inElastic[i] -> Scale(1./inElastic[i]->Integral());
        inPion0[i] -> Scale(1./inPion0[i]->Integral());
        inDir[i] -> Scale(1./inDir[i]->Integral());
    }
    
	gStyle -> SetOptStat(0);
	TCanvas *c1 = new TCanvas("", "", 800, 600);
	{
		c1 -> cd();

		gPad -> SetTicks();
		gPad -> SetLeftMargin(0.15);
		gPad -> SetRightMargin(0.15);
		gPad -> SetTopMargin(0.05);
		gPad -> SetBottomMargin(0.12);

		TH1D *htmp = (TH1D*)gPad -> DrawFrame(4, 0, 6, 0.2);

		htmp -> GetXaxis() -> SetTitle("p_{T} sum");
		htmp -> GetYaxis() -> SetTitle("# of events");
    
        inElastic[0] -> SetMarkerStyle(33);
        inElastic[0] -> SetMarkerColor(1);
        inElastic[0] -> SetLineColor(1);
        inElastic[0] -> Draw("p same");

        inElastic[1] -> SetMarkerStyle(33);
        inElastic[1] -> SetMarkerColor(2);
        inElastic[1] -> SetLineColor(2);
        inElastic[1] -> Draw("p same");

 //        inElastic[2] -> SetMarkerStyle(31);
 //        inElastic[2] -> SetMarkerColor(3);
 //        inElastic[2] -> SetLineColor(3);
 //        inElastic[2] -> Draw("p same");
 //
 //        inElastic[3] -> SetMarkerStyle(31);
 //        inElastic[3] -> SetMarkerColor(4);
 //        inElastic[3] -> SetLineColor(4);
 //        inElastic[3] -> Draw("p same");
 //
 //        inElastic[4] -> SetMarkerStyle(31);
 //        inElastic[4] -> SetMarkerColor(5);
 //        inElastic[4] -> SetLineColor(5);
 //        inElastic[4] -> Draw("p same");
 //        
 //        inElastic[5] -> SetMarkerStyle(31);
 //        inElastic[5] -> SetMarkerColor(6);
 //        inElastic[5] -> SetLineColor(6);
 //        inElastic[5] -> Draw("p same");

        inDir[0] -> SetMarkerStyle(46);
        inDir[0] -> SetMarkerColor(1);
        inDir[0] -> SetLineColor(1);
        inDir[0] -> Draw("p same");

        inDir[1] -> SetMarkerStyle(46);
        inDir[1] -> SetMarkerColor(2);
        inDir[1] -> SetLineColor(2);
        inDir[1] -> Draw("p same");

 //        inDir[2] -> SetMarkerStyle(29);
 //        inDir[2] -> SetMarkerColor(3);
 //        inDir[2] -> SetLineColor(3);
 //        inDir[2] -> Draw("p same");
 //
 //        inDir[3] -> SetMarkerStyle(29);
 //        inDir[3] -> SetMarkerColor(4);
 //        inDir[3] -> SetLineColor(4);
 //        inDir[3] -> Draw("p same");
 //
 //        inDir[4] -> SetMarkerStyle(29);
 //        inDir[4] -> SetMarkerColor(5);
 //        inDir[4] -> SetLineColor(5);
 //        inDir[4] -> Draw("p same");
 //        
 //        inDir[5] -> SetMarkerStyle(29);
 //        inDir[5] -> SetMarkerColor(6);
 //        inDir[5] -> SetLineColor(6);
 //        inDir[5] -> Draw("p same");

        inPion0[0] -> SetMarkerStyle(4);
        inPion0[0] -> SetMarkerColor(1);
        inPion0[0] -> SetLineColor(1);
        inPion0[0] -> Draw("p same");

        inPion0[1] -> SetMarkerStyle(4);
        inPion0[1] -> SetMarkerColor(2);
        inPion0[1] -> SetLineColor(2);
        inPion0[1] -> Draw("p same");

 //        inPion0[3] -> SetMarkerStyle(4);
 //        inPion0[3] -> SetMarkerColor(4);
 //        inPion0[3] -> SetLineColor(4);
 //        inPion0[3] -> Draw("p same");
 //
 //        inPion0[4] -> SetMarkerStyle(4);
 //        inPion0[4] -> SetMarkerColor(5);
 //        inPion0[4] -> SetLineColor(5);
 //        inPion0[4] -> Draw("p same");
 //        
 //        inPion0[5] -> SetMarkerStyle(4);
 //        inPion0[5] -> SetMarkerColor(6);
 //        inPion0[5] -> SetLineColor(6);
 //        inPion0[5] -> Draw("p same");


		TLegend *leg1 = new TLegend(0.38, 0.63, 0.78, 0.93);
		leg1 -> SetFillStyle(0);
		leg1 -> SetBorderSize(0);
		leg1 -> SetTextSize(0.03);
		leg1 -> AddEntry("","PYTHIA8, option3", "h");
		leg1 -> AddEntry("","p+Au, 200 GeV", "h");
        leg1 -> AddEntry("", "mid-rapidity: |#eta|<1", "h");
        leg1 -> AddEntry("", "#LTp_{T} sum#GT of charged particles", "h");

        leg1 -> AddEntry(inElastic[0], "MB events, 0~10%", "p");
        leg1 -> AddEntry(inElastic[1], "MB events, 10~20%", "p");
        leg1 -> AddEntry(inDir[0], "Events with #gamma^{dir} in mid-rapidity, 0~10%", "p");
        leg1 -> AddEntry(inDir[1], "Events with #gamma^{dir} in mid-rapidity, 10~20%", "p");
        leg1 -> AddEntry(inPion0[0], "Events with #pi^{0} in mid-rapidity, 0~10%", "p");
        leg1 -> AddEntry(inPion0[1], "Events with #pi^{0} in mid-rapidity, 10~20%", "p");
        		
        leg1 -> Draw();

	}


}
