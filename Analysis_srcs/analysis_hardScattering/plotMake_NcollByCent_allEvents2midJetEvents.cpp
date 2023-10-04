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
        const int midJetEvent = 0;

        TLegend *leg[5];
        for(int i=0; i<5; i++)
        {

            TString outputname = Form("Events with #pi^{0} > %d GeV in |#eta|<1", 2*i+3);
            
            leg[i] = new TLegend(0.5, 0.7, 0.9, 0.93);
            leg[i] -> SetFillStyle(0);
            leg[i] -> SetBorderSize(0);
            leg[i] -> SetTextSize(0.02);
            leg[i] -> AddEntry("", "PYTHIA8", "h");
            leg[i] -> AddEntry("", "pAu200GeV, option3", "h");

            leg[i] -> AddEntry("", outputname, "h");
            leg[i] -> AddEntry(ncollcentG_midjet[i][0], "centrality: 0~10%", "p");
            leg[i] -> AddEntry(ncollcentG_midjet[i][1], "centrality: 10~20%", "p");
            leg[i] -> AddEntry(ncollcentG_midjet[i][2], "centrality: 20~40%", "p");
            leg[i] -> AddEntry(ncollcentG_midjet[i][3], "centrality: 40~60%", "p");
            leg[i] -> AddEntry(ncollcentG_midjet[i][4], "centrality: 60~80%", "p");

            leg[i] -> AddEntry("", "all events", "h");
            leg[i] -> AddEntry(ncollcentG_all[0], "centrality: 0~10%", "p");
            leg[i] -> AddEntry(ncollcentG_all[1], "centrality: 10~20%", "p");
            leg[i] -> AddEntry(ncollcentG_all[2], "centrality: 20~40%", "p");
            leg[i] -> AddEntry(ncollcentG_all[3], "centrality: 40~60%", "p");
            leg[i] -> AddEntry(ncollcentG_all[4], "centrality: 60~80%", "p");


        }// event type


        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        gPad -> SetLogy();

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(1, 5, 25, 1e10);

        htmp -> GetXaxis() -> SetTitle("Ncoll");
        htmp -> GetYaxis() -> SetTitle("# of events");
        

        //all events
        ncollcentG_all[0] -> SetMarkerStyle(34);
        ncollcentG_all[0] -> SetMarkerColor(kGreen+1);
        ncollcentG_all[0] -> SetLineColor(kGreen+1);
        ncollcentG_all[0] -> Draw("p L same");

        ncollcentG_all[1] -> SetMarkerStyle(32);
        ncollcentG_all[1] -> SetMarkerColor(kTeal+1);
        ncollcentG_all[1] -> SetLineColor(kTeal+1);
        ncollcentG_all[1] -> Draw("p L same");

        ncollcentG_all[2] -> SetMarkerStyle(22);
        ncollcentG_all[2] -> SetMarkerColor(kCyan+1);
        ncollcentG_all[2] -> SetLineColor(kCyan+1);
        ncollcentG_all[2] -> Draw("p L same");

        ncollcentG_all[3] -> SetMarkerStyle(21);
        ncollcentG_all[3] -> SetMarkerColor(kAzure);
        ncollcentG_all[3] -> SetLineColor(kAzure);
        ncollcentG_all[3] -> Draw("p L same");

        ncollcentG_all[4] -> SetMarkerStyle(20);
        ncollcentG_all[4] -> SetMarkerColor(kBlue);
        ncollcentG_all[4] -> SetLineColor(kBlue);
        ncollcentG_all[4] -> Draw("p L same");


        //with mid-jet, pion0
        ncollcentG_midjet[midJetEvent][0] -> SetMarkerStyle(34);
        ncollcentG_midjet[midJetEvent][0] -> SetMarkerColor(kOrange);
        ncollcentG_midjet[midJetEvent][0] -> SetLineColor(kOrange);
        ncollcentG_midjet[midJetEvent][0] -> Draw("p L same ");

        ncollcentG_midjet[midJetEvent][1] -> SetMarkerStyle(34);
        ncollcentG_midjet[midJetEvent][1] -> SetMarkerColor(kRed);
        ncollcentG_midjet[midJetEvent][1] -> SetLineColor(kRed);
        ncollcentG_midjet[midJetEvent][1] -> Draw("p L same");

        ncollcentG_midjet[midJetEvent][2] -> SetMarkerStyle(28);
        ncollcentG_midjet[midJetEvent][2] -> SetMarkerColor(kPink);
        ncollcentG_midjet[midJetEvent][2] -> SetLineColor(kPink);
        ncollcentG_midjet[midJetEvent][2] -> Draw("p L same");
    
        ncollcentG_midjet[midJetEvent][3] -> SetMarkerStyle(47);
        ncollcentG_midjet[midJetEvent][3] -> SetMarkerColor(kMagenta);
        ncollcentG_midjet[midJetEvent][3] -> SetLineColor(kMagenta);
        ncollcentG_midjet[midJetEvent][3] -> Draw("p L same");

        ncollcentG_midjet[midJetEvent][4] -> SetMarkerStyle(28);
        ncollcentG_midjet[midJetEvent][4] -> SetMarkerColor(kViolet);
        ncollcentG_midjet[midJetEvent][4] -> SetLineColor(kViolet);
        ncollcentG_midjet[midJetEvent][4] -> Draw("p L same");

        leg[midJetEvent] -> Draw();

     }

}
