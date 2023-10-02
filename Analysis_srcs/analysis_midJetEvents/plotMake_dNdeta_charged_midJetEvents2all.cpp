void plotMake_dNdeta_charged_midJetEvents2all()
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
    
    //Draw plot
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    //c1 -> Divide(2, 3);
    {
        TH1D *htmp[5];
        TLegend *leg[5][5];
        
       
        //set legend
        for(int i=0; i<5; i++)
        {
            for(int j=0; j<5; j++)
            {
                TString input_allEvents_byCent = Form("allEvents: centClass%d", j+1);
                TString input_midJetEvents_byCent = Form("events with #pi^{0} > %d, in |#eta|<1: centClass%d", 2*i+3, j+1);
                //set legend
                leg[i][j] = new TLegend(0.4, 0.7, 0.8, 0.9);
                leg[i][j] -> SetFillStyle(0);
                leg[i][j] -> SetBorderSize(0);
                leg[i][j] -> SetTextSize(0.03);

                leg[i][j] -> AddEntry(dndetaCh_allEvents_mb, "MB events", "p");
                leg[i][j] -> AddEntry(dndetaCh_allEvents_byCent[j], input_allEvents_byCent, "p");
                leg[i][j] -> AddEntry(dndetaCh_midJetEvents_byCent[i][j], input_midJetEvents_byCent, "p");
            }
         }

            const int midJetIndex = 2;  //0~4
            const int centClass = 0;    //0~4

            TLine *centRangeLow = new TLine(-3.9, 0, -3.9, 25);
            TLine *centRangeHigh = new TLine(-3.0, 0, -3.0, 25);

            //cent: 0~10%
            c1 -> cd(1);
           
            {
                gPad -> SetTicks();
                gPad -> SetLeftMargin(0.15);
                gPad -> SetRightMargin(0.15);
                gPad -> SetBottomMargin(0.12);

                htmp[0] = (TH1D*)gPad -> DrawFrame(-3.9, 0, -3.0, 25);
                htmp[0] -> GetXaxis() -> SetTitle("#eta");
                htmp[0] -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");

                leg[midJetIndex][centClass] -> Draw();

                dndetaCh_allEvents_mb -> SetMarkerStyle(25);
                dndetaCh_allEvents_mb -> SetMarkerColor(1);
                dndetaCh_allEvents_mb -> SetLineColor(1);
                dndetaCh_allEvents_mb -> Draw("p same");

                dndetaCh_allEvents_byCent[centClass] -> SetMarkerStyle(20);
                dndetaCh_allEvents_byCent[centClass] -> SetMarkerColor(1);
                dndetaCh_allEvents_byCent[centClass] -> SetLineColor(1);
                dndetaCh_allEvents_byCent[centClass] -> Draw("p same");

                dndetaCh_midJetEvents_byCent[midJetIndex][centClass] -> SetMarkerStyle(34);
                dndetaCh_midJetEvents_byCent[midJetIndex][centClass] -> SetMarkerColor(2);
                dndetaCh_midJetEvents_byCent[midJetIndex][centClass] -> SetLineColor(2);
                dndetaCh_midJetEvents_byCent[midJetIndex][centClass] -> Draw("p same");

                centRangeLow -> Draw();
                centRangeHigh -> Draw();

            }
            
 //            //cent: 10~20%
 //            c1 -> cd(2);
 //           
 //            {
 //                gPad -> SetTicks();
 //                gPad -> SetLeftMargin(0.15);
 //                gPad -> SetRightMargin(0.15);
 //                gPad -> SetBottomMargin(0.12);
 //
 //                htmp[1] = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 25);
 //                htmp[1] -> GetXaxis() -> SetTitle("#eta");
 //                htmp[1] -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");
 //
 //                leg[midJetIndex][1] -> Draw();
 //
 //                dndetaCh_allEvents_mb -> SetMarkerStyle(25);
 //                dndetaCh_allEvents_mb -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_mb -> SetMarkerColor(1);
 //                dndetaCh_allEvents_mb -> SetLineColor(1);
 //                dndetaCh_allEvents_mb -> Draw("p same");
 //
 //                dndetaCh_allEvents_byCent[1] -> SetMarkerStyle(20);
 //                dndetaCh_allEvents_byCent[1] -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_byCent[1] -> SetMarkerColor(1);
 //                dndetaCh_allEvents_byCent[1] -> SetLineColor(1);
 //                dndetaCh_allEvents_byCent[1] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex][1] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][1] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][1] -> SetMarkerColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][1] -> SetLineColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][1] -> Draw("p same");
 //    
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][1] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][1] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][1] -> SetMarkerColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][1] -> SetLineColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][1] -> Draw("p same");
 //
 //                centRangeLow -> Draw();
 //                centRangeHigh -> Draw();
 //            }
 //
 //
 //            //cent: 20~40%
 //            c1 -> cd(3);
 //           
 //            {
 //                gPad -> SetTicks();
 //                gPad -> SetLeftMargin(0.15);
 //                gPad -> SetRightMargin(0.15);
 //                gPad -> SetBottomMargin(0.12);
 //
 //                htmp[2] = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 25);
 //                htmp[2] -> GetXaxis() -> SetTitle("#eta");
 //                htmp[2] -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");
 //
 //                leg[midJetIndex][2] -> Draw();
 //
 //                dndetaCh_allEvents_mb -> SetMarkerStyle(25);
 //                dndetaCh_allEvents_mb -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_mb -> SetMarkerColor(1);
 //                dndetaCh_allEvents_mb -> SetLineColor(1);
 //                dndetaCh_allEvents_mb -> Draw("p same");
 //
 //                dndetaCh_allEvents_byCent[2] -> SetMarkerStyle(20);
 //                dndetaCh_allEvents_byCent[2] -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_byCent[2] -> SetMarkerColor(1);
 //                dndetaCh_allEvents_byCent[2] -> SetLineColor(1);
 //                dndetaCh_allEvents_byCent[2] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex][2] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][2] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][2] -> SetMarkerColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][2] -> SetLineColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][2] -> Draw("p same");
 //    
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][2] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][2] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][2] -> SetMarkerColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][2] -> SetLineColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][2] -> Draw("p same");
 //
 //                centRangeLow -> Draw();
 //                centRangeHigh -> Draw();
 //            }
 //
 //
 //            //cent: 40~60%
 //            c1 -> cd(4);
 //           
 //            {
 //                gPad -> SetTicks();
 //                gPad -> SetLeftMargin(0.15);
 //                gPad -> SetRightMargin(0.15);
 //                gPad -> SetBottomMargin(0.12);
 //
 //                htmp[3] = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 25);
 //                htmp[3] -> GetXaxis() -> SetTitle("#eta");
 //                htmp[3] -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");
 //
 //                leg[midJetIndex][3] -> Draw();
 //
 //                dndetaCh_allEvents_mb -> SetMarkerStyle(25);
 //                dndetaCh_allEvents_mb -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_mb -> SetMarkerColor(1);
 //                dndetaCh_allEvents_mb -> SetLineColor(1);
 //                dndetaCh_allEvents_mb -> Draw("p same");
 //
 //                dndetaCh_allEvents_byCent[3] -> SetMarkerStyle(20);
 //                dndetaCh_allEvents_byCent[3] -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_byCent[3] -> SetMarkerColor(1);
 //                dndetaCh_allEvents_byCent[3] -> SetLineColor(1);
 //                dndetaCh_allEvents_byCent[3] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex][3] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][3] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][3] -> SetMarkerColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][3] -> SetLineColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][3] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][3] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][3] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][3] -> SetMarkerColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][3] -> SetLineColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][3] -> Draw("p same");
 //
 //
 //                centRangeLow -> Draw();
 //                centRangeHigh -> Draw();
 //            }
 //
 //
 //            //cent: 60~80%
 //            c1 -> cd(5);
 //           
 //            {
 //                gPad -> SetTicks();
 //                gPad -> SetLeftMargin(0.15);
 //                gPad -> SetRightMargin(0.15);
 //                gPad -> SetBottomMargin(0.12);
 //
 //                htmp[4] = (TH1D*)gPad -> DrawFrame(-6, 0, 6, 25);
 //                htmp[4] -> GetXaxis() -> SetTitle("#eta");
 //                htmp[4] -> GetYaxis() -> SetTitle("dN^{ch}/d#eta");
 //
 //                leg[midJetIndex][4] -> Draw();
 //
 //                dndetaCh_allEvents_mb -> SetMarkerStyle(25);
 //                dndetaCh_allEvents_mb -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_mb -> SetMarkerColor(1);
 //                dndetaCh_allEvents_mb -> SetLineColor(1);
 //                dndetaCh_allEvents_mb -> Draw("p same");
 //
 //                dndetaCh_allEvents_byCent[4] -> SetMarkerStyle(20);
 //                dndetaCh_allEvents_byCent[4] -> SetMarkerSize(0.8);
 //                dndetaCh_allEvents_byCent[4] -> SetMarkerColor(1);
 //                dndetaCh_allEvents_byCent[4] -> SetLineColor(1);
 //                dndetaCh_allEvents_byCent[4] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex][4] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][4] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][4] -> SetMarkerColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][4] -> SetLineColor(2);
 //                dndetaCh_midJetEvents_byCent[midJetIndex][4] -> Draw("p same");
 //
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][4] -> SetMarkerStyle(34);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][4] -> SetMarkerSize(0.8);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][4] -> SetMarkerColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][4] -> SetLineColor(4);
 //                dndetaCh_midJetEvents_byCent[midJetIndex+1][4] -> Draw("p same");
 //
 //
 //                centRangeLow -> Draw();
 //                centRangeHigh -> Draw();
 //            }


        }

}

