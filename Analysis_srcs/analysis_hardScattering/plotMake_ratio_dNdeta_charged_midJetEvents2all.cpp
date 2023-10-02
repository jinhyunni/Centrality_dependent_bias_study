void plotMake_ratio_dNdeta_charged_midJetEvents2all()
{

    //input
    //-----
    TFile *input_MBevents = new TFile("../analysis_allEvents_dNdeta/pAu200GeV_p8303ver2_option3_dNdetaCharge_MBevents.root", "read");
    TFile *input_allEvents = new TFile("../analysis_allEvents_dNdeta/pAu200GeV_p8303ver2_option3_dNdetaCharge_byCent_allEvents.root", "read");
       
    TFile *input_midJetEvents = new TFile("pAu200GeV_p8303ver2_option3_dNdetaCharge_byCent_inMidJetEvents.root", "read");

    TFile *input_highpT_midJetEvents = new TFile("pAu200GeV_p8303ver2_option3_dNdetaCharge_highpT_byCent_inMidJetEvents.root", "read");
    
    //set dndeta charged in mb events
    TH1D *dndetaCh_allEvents_mb = (TH1D*)input_MBevents -> Get("dndeta_mbevents");
    TH1D *dndetaCh_allEvents_byCent[5];
    TH1D *dndetaCh_midJetEvents_byCent[5][5];
    TH1D *dndetaCh_midJetEvents_highpT_byCent[5][5];
    
    for(int i=0; i<5; i++)
    {   
        //set dndeta charged by centrality in all events
        TString inputname_allEvents = Form("dndeta_allEvents_cent%d", i+1);
        dndetaCh_allEvents_byCent[i] = (TH1D*)input_allEvents -> Get(inputname_allEvents);
        
        for(int j=0; j<5; j++)
        {
            //set dndeta charged by centrality in events with mid-jet
            TString inputname_midJetEvents = Form("dndeta_midpion0_%dGeV_cent%d", 2*i+3, j+1);
            TString inputname_highpT_midJetEvents = Form("dndeta_midpion0_highpT_%dGeV_cent%d", 2*i+3, j+1);
            dndetaCh_midJetEvents_byCent[i][j] = (TH1D*)input_midJetEvents -> Get(inputname_midJetEvents);
            dndetaCh_midJetEvents_highpT_byCent[i][j] = (TH1D*)input_highpT_midJetEvents -> Get(inputname_highpT_midJetEvents);
        }
    }


    //Get ratio of dNdeta, midJetEvents2all

    TH1D *ratio_dNdeta_midJet2all[5][5];

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            TString outputname = Form("ratio_dNdeta_mid%dGeV2all_cent%d", 2*i+3, j+1);
            ratio_dNdeta_midJet2all[i][j] = (TH1D*)dndetaCh_midJetEvents_byCent[i][j] -> Clone(outputname);
            ratio_dNdeta_midJet2all[i][j] -> Divide(dndetaCh_allEvents_byCent[j]);
        }
    }

    
    //Draw plot
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    //c1 -> Divide(2, 3);
    {
        TH1D *htmp[5];
        TLegend *leg[5];
        
       
        //set legend
        for(int i=0; i<5; i++)
        {
           
                TString input_midJetEvents_byCent1 = Form("events with #pi^{0} > %d, in |#eta|<1: centClass1", 2*i+3);
                TString input_midJetEvents_byCent2 = Form("events with #pi^{0} > %d, in |#eta|<1: centClass2", 2*i+3);
                TString input_midJetEvents_byCent3 = Form("events with #pi^{0} > %d, in |#eta|<1: centClass3", 2*i+3);
                TString input_midJetEvents_byCent4 = Form("events with #pi^{0} > %d, in |#eta|<1: centClass4", 2*i+3);
                TString input_midJetEvents_byCent5 = Form("events with #pi^{0} > %d, in |#eta|<1: centClass5", 2*i+3);
                //set legend
                leg[i] = new TLegend(0.4, 0.7, 0.8, 0.9);
                leg[i] -> SetFillStyle(0);
                leg[i] -> SetBorderSize(0);
                leg[i] -> SetTextSize(0.03);

                leg[i] -> AddEntry(ratio_dNdeta_midJet2all[i][0], input_midJetEvents_byCent1, "p");
                leg[i] -> AddEntry(ratio_dNdeta_midJet2all[i][1], input_midJetEvents_byCent2, "p");
                leg[i] -> AddEntry(ratio_dNdeta_midJet2all[i][2], input_midJetEvents_byCent3, "p");
                leg[i] -> AddEntry(ratio_dNdeta_midJet2all[i][3], input_midJetEvents_byCent4, "p");
                leg[i] -> AddEntry(ratio_dNdeta_midJet2all[i][4], input_midJetEvents_byCent5, "p");
         }

            const int midJetIndex = 2;  //0~4


            //cent: 0~10%
            c1 -> cd(1);
           
            {
                gPad -> SetTicks();
                gPad -> SetLeftMargin(0.15);
                gPad -> SetRightMargin(0.15);
                gPad -> SetBottomMargin(0.12);

                htmp[0] = (TH1D*)gPad -> DrawFrame(-3.9, 0.9, -3.0, 1.3);
                htmp[0] -> GetXaxis() -> SetTitle("#eta");
                htmp[0] -> GetYaxis() -> SetTitle("#frac{dN^{ch}}{d#eta}_{midJet} / #frac{dN^{ch}}{d#eta}_{allEvents}");

                leg[midJetIndex] -> Draw();

                ratio_dNdeta_midJet2all[midJetIndex][0] -> SetMarkerStyle(34);
                ratio_dNdeta_midJet2all[midJetIndex][0] -> SetMarkerColor(kOrange);
                ratio_dNdeta_midJet2all[midJetIndex][0] -> SetLineColor(kOrange);
                ratio_dNdeta_midJet2all[midJetIndex][0] -> Draw("p same");

                ratio_dNdeta_midJet2all[midJetIndex][1] -> SetMarkerStyle(34);
                ratio_dNdeta_midJet2all[midJetIndex][1] -> SetMarkerColor(kRed);
                ratio_dNdeta_midJet2all[midJetIndex][1] -> SetLineColor(kRed);
                ratio_dNdeta_midJet2all[midJetIndex][1] -> Draw("p same");

                ratio_dNdeta_midJet2all[midJetIndex][2] -> SetMarkerStyle(28);
                ratio_dNdeta_midJet2all[midJetIndex][2] -> SetMarkerColor(kPink);
                ratio_dNdeta_midJet2all[midJetIndex][2] -> SetLineColor(kPink);
                ratio_dNdeta_midJet2all[midJetIndex][2] -> Draw("p same");

                ratio_dNdeta_midJet2all[midJetIndex][3] -> SetMarkerStyle(47);
                ratio_dNdeta_midJet2all[midJetIndex][3] -> SetMarkerColor(kMagenta);
                ratio_dNdeta_midJet2all[midJetIndex][3] -> SetLineColor(kMagenta);
                ratio_dNdeta_midJet2all[midJetIndex][3] -> Draw("p same");

                ratio_dNdeta_midJet2all[midJetIndex][4] -> SetMarkerStyle(28);
                ratio_dNdeta_midJet2all[midJetIndex][4] -> SetMarkerColor(kViolet);
                ratio_dNdeta_midJet2all[midJetIndex][4] -> SetLineColor(kViolet);
                ratio_dNdeta_midJet2all[midJetIndex][4] -> Draw("p same");
           }
    }
            

}

