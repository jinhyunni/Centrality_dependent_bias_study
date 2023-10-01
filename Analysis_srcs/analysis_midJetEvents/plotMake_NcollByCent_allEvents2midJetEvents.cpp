void plotMake_NcollByCent_allEvents2midJetEvents()
{
    TFile *input_midjet = new TFile("pAu200GeV_p8303ver2_option3_NcollByCent_inMidJetEvents.root", "read");
    TFile *input_all = new TFile("../analysis_allEvents_Ncoll/pAu200GeV_p8303ver2_option3_NcollByCent.root", "read");
    
    //ncoll of events with jet-midrapidity by centrality
    //--------------------------------------------------
    TH1D *ncollcent_midjet[5][5];
    
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            TString inputname = Form("ncoll_midpion0_%dGeV_cent%d", 2*i+3, j+1);
            ncollcent_midjet[i][j] = (TH1D*)input_midjet -> Get(inputname);
        }
    }
    
    //ncoll of all events by centrality
    //---------------------------------
    TH1D *ncollcent_all[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("ncoll_cent%d", i+1);
        ncollcent_all[i] = (TH1D*)input_all -> Get(inputname);
    }


    
    //set TGraph for connecting lines between markers
    //-----------------------------------------------

    //For events with mid-jets
    TGraph *ncollcentG_midjet[5][5];

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            ncollcentG_midjet[i][j] = new TGraph();

            for(int k=0; k<ncollcent_midjet[i][j] -> GetNbinsX(); k++)
            {
                if(ncollcent_midjet[i][j] -> GetBinContent(k+1) != 0)
                {
                    ncollcentG_midjet[i][j] -> SetPoint(ncollcentG_midjet[i][j] -> GetN(), ncollcent_midjet[i][j] -> GetBinCenter(k+1), ncollcent_midjet[i][j] -> GetBinContent(k+1));
                }

            }//set Tgraph

        }//j: centrality

    }//i : event type


    //For all events
    TGraph *ncollcentG_all[5];

    for(int i=0; i<5; i++)
    {
        ncollcentG_all[i] = new TGraph();

        for(int j=0; j<ncollcent_all[i] -> GetNbinsX(); j++)
        {
            if(ncollcent_all[i] -> GetBinContent(j+1) != 0)
            {
                ncollcentG_all[i] -> SetPoint(ncollcentG_all[i] -> GetN(), ncollcent_all[i] -> GetBinCenter(j+1), ncollcent_all[i] -> GetBinContent(j+1));
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

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(1, 0, 25, 1e3);

        htmp -> GetXaxis() -> SetTitle("Ncoll");
        htmp -> GetYaxis() -> SetTitle("# of events");
        
        //all events
        ncollcentG_all[0] -> SetMarkerStyle(47);
        ncollcentG_all[0] -> SetMarkerColor(kRed+1);
        ncollcentG_all[0] -> SetLineColor(kRed+1);
        ncollcentG_all[0] -> Draw("p L same");

        ncollcentG_all[1] -> SetMarkerStyle(25);
        ncollcentG_all[1] -> SetMarkerColor(kRed+1);
        ncollcentG_all[1] -> SetLineColor(kRed+1);
        ncollcentG_all[1] -> Draw("p L same");

        ncollcentG_all[2] -> SetMarkerStyle(28);
        ncollcentG_all[2] -> SetMarkerColor(kRed+1);
        ncollcentG_all[2] -> SetLineColor(kRed+1);
        ncollcentG_all[2] -> Draw("p L same");
    
        ncollcentG_all[3] -> SetMarkerStyle(22);
        ncollcentG_all[3] -> SetMarkerColor(kRed+1);
        ncollcentG_all[3] -> SetLineColor(kRed+1);
        ncollcentG_all[3] -> Draw("p L same");

        ncollcentG_all[4] -> SetMarkerStyle(24);
        ncollcentG_all[4] -> SetMarkerColor(kRed+1);
        ncollcentG_all[4] -> SetLineColor(kRed+1);
        ncollcentG_all[4] -> Draw("p L same");
    
        //with mid-jet, pion0 > 5 GeV
        ncollcentG_midjet[1][0] -> SetMarkerStyle(47);
        ncollcentG_midjet[1][0] -> SetMarkerColor(kBlue);
        ncollcentG_midjet[1][0] -> SetLineColor(kBlue);
        ncollcentG_midjet[1][0] -> Draw("p L same");

        ncollcentG_midjet[1][1] -> SetMarkerStyle(25);
        ncollcentG_midjet[1][1] -> SetMarkerColor(kBlue);
        ncollcentG_midjet[1][1] -> SetLineColor(kBlue);
        ncollcentG_midjet[1][1] -> Draw("p L same");

        ncollcentG_midjet[1][2] -> SetMarkerStyle(28);
        ncollcentG_midjet[1][2] -> SetMarkerColor(kBlue);
        ncollcentG_midjet[1][2] -> SetLineColor(kBlue);
        ncollcentG_midjet[1][2] -> Draw("p L same");
    
        ncollcentG_midjet[1][3] -> SetMarkerStyle(22);
        ncollcentG_midjet[1][3] -> SetMarkerColor(kBlue);
        ncollcentG_midjet[1][3] -> SetLineColor(kBlue);
        ncollcentG_midjet[1][3] -> Draw("p L same");

        ncollcentG_midjet[1][4] -> SetMarkerStyle(24);
        ncollcentG_midjet[1][4] -> SetMarkerColor(kBlue);
        ncollcentG_midjet[1][4] -> SetLineColor(kBlue);
        ncollcentG_midjet[1][4] -> Draw("p L same");

        TLegend *leg1 = new TLegend(0.47, 0.6, 0.87, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8", "h");
        leg1 -> AddEntry("", "pAu200GeV, option3", "h");

        leg1 -> AddEntry(ncollcentG_all[0], "centrality: 0~10%, #LTN_{coll}#GT: 9.02", "p");
        leg1 -> AddEntry(ncollcentG_all[1], "centrality: 10~20%, #LTN_{coll}#GT: 7.69", "p");
        leg1 -> AddEntry(ncollcentG_all[2], "centrality: 20~40%, #LTN_{coll}#GT: 6.52", "p");
        leg1 -> AddEntry(ncollcentG_all[3], "centrality: 40~60%, #LTN_{coll}#GT: 5.04", "p");
        leg1 -> AddEntry(ncollcentG_all[4], "centrality: 60~80%, #LTN_{coll}#GT: 3.45", "p");

        leg1 -> Draw();

    }

}
