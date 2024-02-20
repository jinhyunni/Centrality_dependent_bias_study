void plotMake_MByields_bypTClass_dirphoton()
{
    TFile *input1 = new TFile("pAu200GeV_p8303_onlyDirPhoton_option3_MB_pTClass_dirPhoton.root", "read");

	TH1D *DirMB_pTClass[5];
	for(int i=0; i<5; i++)
	{	
		TString histname = Form("DirMB_avgNcollScaled_pTClass%d", i+1);
		DirMB_pTClass[i] = (TH1D*)input1 -> Get(histname); 
	}
	
	TH1D *MByields = new TH1D("", "", 5, 1, 6);
	
	for(int i=0; i<5; i++)
	{
		MByields -> SetBinContent(i+1, DirMB_pTClass[i] -> GetBinContent(1));
		MByields -> SetBinError(i+1, DirMB_pTClass[i] -> GetBinError(1));
	}

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

		gPad -> SetLogy();

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(1, 0.00000000001, 6, 0.01);

        htmp -> GetXaxis() -> SetTitle("pT Class");
        htmp -> GetYaxis() -> SetTitle("#LTN_{coll}#GT scaled MB yields by pT Class");
           
        MByields -> SetMarkerStyle(47);
        MByields -> SetMarkerColor(kAzure);
        MByields -> SetLineColor(kAzure);
        MByields -> Draw("p same");

        TLegend *leg1 = new TLegend(0.15, 0.6, 0.51, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
 //*        leg1 -> AddEntry("", "PYTHIA8, pAu200GeV with option3", "h");
 //*        leg1 -> AddEntry("", "#gamma^{dir} in |#eta|<1", "h");

 //*        leg1 -> AddEntry("", "p_{T} Class1: 2~4 GeV/c", "");
 //*        leg1 -> AddEntry("", "p_{T} Class2: 4~7 GeV/c", "");
 //*        leg1 -> AddEntry("", "p_{T} Class3: 7~10 GeV/c", "");
 //*        leg1 -> AddEntry("", "p_{T} Class4: 10~15 GeV/c", "");
 //*        leg1 -> AddEntry("", "p_{T} Class5: 15~20 GeV/c", "");

        leg1 -> Draw();

    }

}
