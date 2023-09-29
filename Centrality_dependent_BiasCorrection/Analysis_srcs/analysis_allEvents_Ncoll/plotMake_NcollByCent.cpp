void plotMake_NcollByCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver4_option3_NcollByCent.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_Ncoll_MBevents.root", "read");
    
    TH1D *ncollcent[5];

    ncollcent[0] = (TH1D*)input1 -> Get("ncoll_cent1");
    ncollcent[1] = (TH1D*)input1 -> Get("ncoll_cent2");
    ncollcent[2] = (TH1D*)input1 -> Get("ncoll_cent3");
    ncollcent[3] = (TH1D*)input1 -> Get("ncoll_cent4");
    ncollcent[4] = (TH1D*)input1 -> Get("ncoll_cent5");
    
    for(int i=0; i<5; i++)
    {
        ncollcent[i] -> Scale(1./(ncollcent[i]->Integral()));
        //ncollcent[i] -> Fit("gaus", "", 0, 30);
    }

    TH1D *ncollmb = (TH1D*)input2 -> Get("ncoll_mb");
    ncollmb -> Scale(1./(ncollmb -> Integral()));

    
    //set TGraph for connecting lines between markers
    //-----------------------------------------------


    //For MB events
    TGraph *ncollmbG = new TGraph();
    for(int i=0; i<ncollmb -> GetNbinsX(); i++)
    {
        if(ncollmb-> GetBinContent(i+1) != 0)
        {
            ncollmbG -> SetPoint(ncollmbG -> GetN(), ncollmb -> GetBinCenter(i+1), ncollmb -> GetBinContent(i+1));
        }

    }
    

    //For event by centraluty
    TGraph *ncollcentG[5];

    for(int i=0; i<5; i++)
    {
        ncollcentG[i] = new TGraph();

        for(int j=0; j<ncollcent[i] -> GetNbinsX(); j++)
        {
            if(ncollcent[i] -> GetBinContent(j+1) != 0)
            {
                ncollcentG[i] -> SetPoint(ncollcentG[i] -> GetN(), ncollcent[i] -> GetBinCenter(j+1), ncollcent[i] -> GetBinContent(j+1));
            }
        }//stting TGraph

    }//5 centrality class



    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(1, 0, 25, 0.25);

        htmp -> GetXaxis() -> SetTitle("Ncoll");
        htmp -> GetYaxis() -> SetTitle("P(N_{coll})_{MB, cent}");

        ncollmbG -> SetMarkerStyle(21);
        ncollmbG -> SetMarkerColor(1);
        ncollmbG -> SetLineColor(1);
        ncollmbG -> Draw("p L same");
    
        ncollcentG[0] -> SetMarkerStyle(47);
        ncollcentG[0] -> SetMarkerColor(kRed+1);
        ncollcentG[0] -> SetLineColor(kRed+1);
        ncollcentG[0] -> Draw("p L same");

        ncollcentG[1] -> SetMarkerStyle(34);
        ncollcentG[1] -> SetMarkerColor(kTeal+1);
        ncollcentG[1] -> SetLineColor(kTeal+1);
        ncollcentG[1] -> Draw("p L same");

        ncollcentG[2] -> SetMarkerStyle(28);
        ncollcentG[2] -> SetMarkerColor(kCyan+1);
        ncollcentG[2] -> SetLineColor(kCyan+1);
        ncollcentG[2] -> Draw("p L same");
    
        ncollcentG[3] -> SetMarkerStyle(22);
        ncollcentG[3] -> SetMarkerColor(kAzure+9);
        ncollcentG[3] -> SetLineColor(kAzure+9);
        ncollcentG[3] -> Draw("p L same");

        ncollcentG[4] -> SetMarkerStyle(24);
        ncollcentG[4] -> SetMarkerColor(kBlue+4);
        ncollcentG[4] -> SetLineColor(kBlue+4);
        ncollcentG[4] -> Draw("p L same");


        TLegend *leg1 = new TLegend(0.47, 0.6, 0.87, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8", "h");
        leg1 -> AddEntry("", "pAu200GeV, option3", "h");

        leg1 -> AddEntry(ncollmbG, "all inelastic events(MB), #LTN_{coll}#GT: 5.085", "p");
        leg1 -> AddEntry(ncollcentG[0], "centrality: 0~10%, #LTN_{coll}#GT: 9.02", "p");
        leg1 -> AddEntry(ncollcentG[1], "centrality: 10~20%, #LTN_{coll}#GT: 7.69", "p");
        leg1 -> AddEntry(ncollcentG[2], "centrality: 20~40%, #LTN_{coll}#GT: 6.52", "p");
        leg1 -> AddEntry(ncollcentG[3], "centrality: 40~60%, #LTN_{coll}#GT: 5.04", "p");
        leg1 -> AddEntry(ncollcentG[4], "centrality: 60~80%, #LTN_{coll}#GT: 3.45", "p");

        leg1 -> Draw();

    }

}
