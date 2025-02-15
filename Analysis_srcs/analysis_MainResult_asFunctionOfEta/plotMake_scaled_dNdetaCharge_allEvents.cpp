void plotMake_scaled_dNdetaCharge_allEvents()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver2_option3_scaled_dNdetaCharge_byCent_allEvents.root", "read");
    TFile *input2 = new TFile("pAu200GeV_p8303ver2_option3_scaled_dNdetaCharge_MBevents.root", "read");
    
    TH1D *dndeta_allEvents[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("scaled_dndeta_allEvents_cent%d", i+1);
        dndeta_allEvents[i] = (TH1D*)input1 -> Get(inputname);
    }

    TH1D *dndeta_mb = (TH1D*)input2 -> Get("scaled_dndeta_mbevents");


    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);

    const int dndeta_centclass = 4;

    TLegend *leg[5];
    for(int i=0; i<5; i++)
    {
        leg[i] = new TLegend(0.15, 0.6, 0.55, 0.9);
        leg[i] -> SetFillStyle(0);
        leg[i] -> SetBorderSize(0);
        leg[i] -> SetTextSize(0.05);

        leg[i] -> AddEntry("", "PYTHIA8, p+Au 200 GeV with option3", "h");
        leg[i] -> AddEntry("", "#pi^{#pm}, k^{#pm}, p^{#pm}, integrated p_{T}", "h");
        
        TString legname[5];
        legname[0] = "cent: 0~10%";
        legname[1] = "cent: 10~20%";
        legname[2] = "cent: 20~40%";
        legname[3] = "cent: 40~60%";
        legname[4] = "cent: 60~80%";

        leg[i] -> AddEntry(dndeta_allEvents[i], legname[i], "p");
        leg[i] -> AddEntry(dndeta_mb, "MB events(all inelastic)", "p");
    }
    

    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.12);
        gPad -> SetRightMargin(0.12);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-5, 0, 5, 4.0);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("#frac{1}{#LT N_{coll} #GT} #frac{1}{N_{event}} #frac{dN^{ch}}{d#eta}");
        
        dndeta_mb -> SetMarkerStyle(28);
        dndeta_mb -> SetMarkerColor(1);
        dndeta_mb -> SetLineColor(1);
        dndeta_mb -> Draw("p same");

        dndeta_allEvents[dndeta_centclass] -> SetMarkerStyle(34);
        dndeta_allEvents[dndeta_centclass] -> SetMarkerColor(kGreen+1);
        dndeta_allEvents[dndeta_centclass] -> SetLineColor(kGreen+1);
        dndeta_allEvents[dndeta_centclass] -> Draw("p same");

 //        TLine *backward_low = new TLine(-3.9, 0, -3.9, 2.0);
 //        backward_low -> SetLineStyle(9);
 //        backward_low -> SetLineColor(2);
 //        backward_low -> Draw("p same");
 //
 //        TLine *backward_high = new TLine(-3.0, 0, -3.0, 2.0);
 //        backward_high -> SetLineStyle(9);
 //        backward_high -> SetLineColor(2);
 //        backward_high -> Draw("p same");
 //
 //        TLine *mid_low= new TLine(-1, 0, -1, 1.5);
 //        mid_low -> SetLineStyle(9);
 //        mid_low -> SetLineColor(2);
 //        mid_low -> Draw("p same");
 //
 //        TLine *mid_high= new TLine(1, 0, 1, 1.5);
 //        mid_high -> SetLineStyle(9);
 //        mid_high -> SetLineColor(2);
 //        mid_high -> Draw("p same");


            
        leg[dndeta_centclass] -> Draw("p same");
       
    }

}
