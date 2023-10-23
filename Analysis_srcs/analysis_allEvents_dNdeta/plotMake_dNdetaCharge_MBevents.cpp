void plotMake_dNdetaCharge_MBevents()
{
    TFile *input1 = new TFile("pAu200GeV_p8303ver2_option3_dNdetaCharge_MBevents.root", "read");
    TH1D *dndeta_charge_mbevents = (TH1D*)input1 -> Get("dndeta_mbevents");

    gStyle -> SetOptStat(0);
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    {
        c1 -> cd();

        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.08);
        gPad -> SetRightMargin(0.08);
        gPad -> SetTopMargin(0.05);
        gPad -> SetBottomMargin(0.12);


        TH1D *htmp = (TH1D*)gPad -> DrawFrame(-3.9, 5, -3.0, 10);

        htmp -> GetXaxis() -> SetTitle("#eta");
        htmp -> GetYaxis() -> SetTitle("dN/d#eta");
        
        dndeta_charge_mbevents -> SetMarkerStyle(34);
        dndeta_charge_mbevents -> SetMarkerColor(1);
        dndeta_charge_mbevents -> SetLineColor(1);
        dndeta_charge_mbevents -> Draw("p same");
            

        TLegend *leg1 = new TLegend(0.15, 0.65, 0.45, 0.9);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.05);
        leg1 -> AddEntry("", "PYTHIA8, Angantyr option3", "h");
        leg1 -> AddEntry("", "p+Au 200 GeV", "h");
        leg1 -> AddEntry("", "particle: #pi^{#pm}, k^{#pm}, p^{#pm}", "h");
        leg1 -> AddEntry("", "N^{ch} in -3.9 < #eta < -3.0: 63.218 #pm 0.002", "h");
        leg1 -> Draw();

    }

}
