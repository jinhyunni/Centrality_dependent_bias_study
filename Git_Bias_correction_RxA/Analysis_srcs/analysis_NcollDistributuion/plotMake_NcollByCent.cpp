void plotMake_NcollByCent()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver3_option3_NcollByCent.root", "read");
    TFile *input2 = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_Ncoll_MBevents.root", "read");
    
    TH1D *ncollcent[5];

    ncollcent[0] = (TH1D*)input1 -> Get("ncoll_cent1");
    ncollcent[1] = (TH1D*)input1 -> Get("ncoll_cent2");
    ncollcent[2] = (TH1D*)input1 -> Get("ncoll_cent3");
    ncollcent[3] = (TH1D*)input1 -> Get("ncoll_cent4");
    ncollcent[4] = (TH1D*)input1 -> Get("ncoll_cent5");
    
    for(int i=0; i<5; i++)
    {
        ncollcent[i] -> Scale(1./(ncollcent[i]->Integral()));
        ncollcent[i] -> Fit("gaus", "", 0, 30);
    }

    TH1D *ncollmb = (TH1D*)input2 -> Get("ncoll_mb");
    ncollmb -> Scale(1./(ncollmb -> Integral()));

 //    //make fit
 //    TH1F *fit_cent1 = new TH1F("gaus", "", 0, 25);  fit_cent1 -> SetLineColor(kRed+1);
 //    TH1F *fit_cent2 = new TH1F("gaus", "", 0, 25);  fit_cent2 -> SetLineColor(kTeal+1);
 //    TH1F *fit_cent3 = new TH1F("gaus", "", 0, 25);  fit_cent3 -> SetLineColor(kCyan+1);
 //    TH1F *fit_cent4 = new TH1F("gaus", "", 0, 25);  fit_cent4 -> SetLineColor(kAzure+9);
 //    TH1F *fit_cent5 = new TH1F("gaus", "", 0, 25);  fit_cent5 -> SetLineColor(kBlue+4);
 //
 //    TH1F *fit_mb = new TH1F("gaus", "", 0, 25);     fit_mb -> SetLineColor(1);

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);

        TH1D *htmp = (TH1D*)gPad -> DrawFrame(1, 0, 25, 0.3);

        htmp -> GetXaxis() -> SetTitle("Ncoll");
        htmp -> GetYaxis() -> SetTitle("# of event");

        ncollmb -> SetMarkerStyle(21);
        ncollmb -> SetMarkerColor(1);
        ncollmb -> SetLineColor(1);
        ncollmb -> Draw("p same");
    
        ncollcent[0] -> SetMarkerStyle(47);
        ncollcent[0] -> SetMarkerColor(kRed+1);
        ncollcent[0] -> SetLineColor(kRed+1);
        ncollcent[0] -> Draw("p same");

        ncollcent[1] -> SetMarkerStyle(34);
        ncollcent[1] -> SetMarkerColor(kTeal+1);
        ncollcent[1] -> SetLineColor(kTeal+1);
        ncollcent[1] -> Draw("p same");

        ncollcent[2] -> SetMarkerStyle(28);
        ncollcent[2] -> SetMarkerColor(kCyan+1);
        ncollcent[2] -> SetLineColor(kCyan+1);
        ncollcent[2] -> Draw("p same");
    
        ncollcent[3] -> SetMarkerStyle(22);
        ncollcent[3] -> SetMarkerColor(kAzure+9);
        ncollcent[3] -> SetLineColor(kAzure+9);
        ncollcent[3] -> Draw("p same");

        ncollcent[4] -> SetMarkerStyle(24);
        ncollcent[4] -> SetMarkerColor(kBlue+4);
        ncollcent[4] -> SetLineColor(kBlue+4);
        ncollcent[4] -> Draw("p same");


        TLegend *leg1 = new TLegend(0.45, 0.6, 0.85, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
        leg1 -> AddEntry("", "PYTHIA8", "h");
        leg1 -> AddEntry("", "pAu200GeV, option3", "h");

        leg1 -> AddEntry(ncollmb, "all inelastic events(MB), #LTN_{coll}#GT: 5.085", "p");
        leg1 -> AddEntry(ncollcent[0], "centrality: 0~10%, #LTN_{coll}#GT: 9.52", "p");
        leg1 -> AddEntry(ncollcent[1], "centrality: 10~20%, #LTN_{coll}#GT: 8.193", "p");
        leg1 -> AddEntry(ncollcent[2], "centrality: 20~40%, #LTN_{coll}#GT: 7.023", "p");
        leg1 -> AddEntry(ncollcent[3], "centrality: 40~60%, #LTN_{coll}#GT: 5.545", "p");
        leg1 -> AddEntry(ncollcent[4], "centrality: 60~80%, #LTN_{coll}#GT: 3.955", "p");

        leg1 -> Draw();

    }

}
