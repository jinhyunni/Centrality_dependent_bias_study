void plotMake_pTsuminBackward_set2pTrange_withMidhardPion0()
{
    //Input
    //-----
    TFile *input = new TFile("pAu200GeV_p8303ver4_option3_pTsuminBackward_set2pTrange_inMidJetEvents.root", "read");

    TH1D *midjet2to3GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT1");
    TH1D *midjet3to5GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT2");
    TH1D *midjet5to7GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT3");
    TH1D *midjet7to9GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT4");
    TH1D *midjet9to11GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT5");
    TH1D *midjet11to15GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT6");
    TH1D *midjet15to20GeV = (TH1D*)input -> Get("pTsum_rebinned_midpion0_highpT7");
   

    //Draw 
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    gStyle -> SetOptStat(0);

    {       
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetBottomMargin(0.12);

        TH1D * htmp = (TH1D*)gPad -> DrawFrame(0.754, 0, 10, 0.5);
        
        htmp -> GetXaxis() -> SetTitle("pTsum of charged particles in backward-range");
        htmp -> GetYaxis() -> SetTitle("d(# of events)/dp_{T}");
        
        midjet2to3GeV -> SetMarkerStyle(20);
        midjet2to3GeV -> SetMarkerColor(1);
        midjet2to3GeV -> SetLineColor(1);
        midjet2to3GeV -> Draw("p same");

        midjet3to5GeV -> SetMarkerStyle(21);
        midjet3to5GeV -> SetMarkerColor(2);
        midjet3to5GeV -> SetLineColor(2);
        midjet3to5GeV -> Draw("p same");

        midjet5to7GeV -> SetMarkerStyle(22);
        midjet5to7GeV -> SetMarkerColor(3);
        midjet5to7GeV -> SetLineColor(3);
        midjet5to7GeV -> Draw("p same");

        midjet7to9GeV -> SetMarkerStyle(23);
        midjet7to9GeV -> SetMarkerColor(4);
        midjet7to9GeV -> SetLineColor(4);
        midjet7to9GeV -> Draw("p same");

        midjet9to11GeV -> SetMarkerStyle(24);
        midjet9to11GeV -> SetMarkerColor(8);
        midjet9to11GeV -> SetLineColor(8);
        midjet9to11GeV -> Draw("p same");

        midjet11to15GeV -> SetMarkerStyle(25);
        midjet11to15GeV -> SetMarkerColor(6);
        midjet11to15GeV -> SetLineColor(6);
        //midjet11to15GeV -> Draw("p same");

        midjet15to20GeV -> SetMarkerStyle(26);
        midjet15to20GeV -> SetMarkerColor(9);
        midjet15to20GeV -> SetLineColor(9);
        //midjet15to20GeV -> Draw("p same");
    
        TLine *cent70 = new TLine(1.161, 0, 1.161, 0.4);
        TLine *cent60 = new TLine(1.589, 0, 1.589, 0.4);
        TLine *cent50 = new TLine(2.049, 0, 2.049, 0.4);
        TLine *cent40 = new TLine(2.554, 0, 2.554, 0.4);
        TLine *cent30 = new TLine(3.134, 0, 3.134, 0.4);
        TLine *cent20 = new TLine(3.851, 0, 3.851, 0.4);
        TLine *cent10 = new TLine(4.909, 0, 4.909, 0.4);

        cent70 -> SetLineStyle(9);
        cent70 -> SetLineColor(2);
        cent70 -> Draw("p same");

        cent60 -> SetLineStyle(9);
        cent60 -> SetLineColor(2);
        cent60 -> Draw("p same");
    
        cent50 -> SetLineStyle(9);
        cent50 -> SetLineColor(2);
        cent50 -> Draw("p same");
    
        cent40 -> SetLineStyle(9);
        cent40 -> SetLineColor(2);
        cent40 -> Draw("p same");
    
        cent30 -> SetLineStyle(9);
        cent30 -> SetLineColor(2);
        cent30 -> Draw("p same");

        cent20 -> SetLineStyle(9);
        cent20 -> SetLineColor(2);
        cent20 -> Draw("p same");

        cent10 -> SetLineStyle(9);
        cent10 -> SetLineColor(2);
        cent10 -> Draw("p same");



        //Legend
        TLegend *leg1 = new TLegend(0.55, 0.45, 0.75, 0.85);
        leg1 -> SetFillStyle(0);
        leg1 -> SetBorderSize(0);
        leg1 -> SetTextSize(0.03);
         
        leg1 -> AddEntry("", "Pythia8, p+Au 200 GeV", "h");
        leg1 -> AddEntry("", "Angantyr: option3(ND only)", "h");
        leg1 -> AddEntry(midjet2to3GeV, "#pi^{0}, |#eta|<1, 2 #leq p_{T} #LT 3", "p");
        leg1 -> AddEntry(midjet3to5GeV, "#pi^{0}, |#eta|<1, 3 #leq p_{T} #LT 5", "p");
        leg1 -> AddEntry(midjet5to7GeV, "#pi^{0}, |#eta|<1, 5 #leq p_{T} #LT 7", "p");
        leg1 -> AddEntry(midjet7to9GeV, "#pi^{0}, |#eta|<1, 7 #leq p_{T} #LT 9", "p");
        leg1 -> AddEntry(midjet9to11GeV, "#pi^{0}, |#eta|<1, 9 #leq p_{T} #LT 11", "p");
        //leg1 -> AddEntry(midjet11to15GeV, "#pi^{0}, |#eta|<1, 11 #leq p_{T} #LT 15", "p");
        //leg1 -> AddEntry(midjet15to20GeV, "#pi^{0}, |#eta|<1, 15 #leq p_{T} #LT 20", "p");
    
        leg1 -> Draw("p same");
    }



}
