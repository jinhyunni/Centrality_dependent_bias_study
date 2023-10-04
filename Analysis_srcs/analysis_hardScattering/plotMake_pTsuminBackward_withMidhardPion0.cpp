void plotMake_pTsuminBackward_withMidhardPion0()
{
    //Input
    //-----

    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_TH2DpTsumTriggerpT_inMidJetEvents.root", "read");
    TH2D *h2pTsumPion0pT = (TH2D*)input -> Get("pTsumTriggerpT");

    //Get pTsum distribution with trigger pion0
    //pT range of pion0 at mid-rapidity: 2~20GeV
    //------------------------------------------
    TH1D *pTsum[21];
    for(int i=0; i<21; i++)
    {
        TString outputname = Form("pTsum_midpion0_%dto%dGeV", i, i+1);

        pTsum[i] = (TH1D*)h2pTsumPion0pT -> ProjectionY(outputname, i+1, i+1);
        pTsum[i] -> Scale(1./pTsum[i] -> Integral());
    }

    //pTsum boundary for centrality
    // high to peripheral
    //-----------------------------
    double bound[9] = {4.909, 3.851, 3.134, 2.554, 2.049, 1.589, 1.161, 0.754, 0.341};

    //Draw Plot
    //---------
    const int lowedge_targetpT = 17;

    TCanvas *c1 = new TCanvas("", "", 800, 600);
    gStyle -> SetOptStat(0);

    //Legend
    TLegend *leg[21];
    for(int i=0; i<21; i++)
    {
        leg[i] = new TLegend(0.3, 0.7, 0.7, 0.9);
        leg[i] -> SetFillStyle(0);
        leg[i] -> SetBorderSize(0);
        leg[i] -> SetTextSize(0.03);
        
        TString discript = Form("pTsum of events with #pi^{0} in mid-rapidity of %d #leq p_{T} #LT %d", i, i+1);
        leg[i] -> AddEntry("", "Pythia8, p+Au 200 GeV", "h");
        leg[i] -> AddEntry("", "Angantyr: option3(ND only)", "h");
        leg[i] -> AddEntry(pTsum[i], discript, "p");
    }
    
    //TLine for pTsum boundary
    TLine *centpTsum[9];
    for(int i=0; i<9; i++)
    {
        centpTsum[i] = new TLine(bound[i], 0, bound[i], 0.01);
        centpTsum[i] -> SetLineStyle(9);
        centpTsum[i] -> SetLineColor(2);
    }

    //Draw 
    {       
        gPad -> SetTicks();
        gPad -> SetLeftMargin(0.15);
        gPad -> SetRightMargin(0.15);
        gPad -> SetBottomMargin(0.12);
        gPad -> SetLogy();

       TH1D * htmp = (TH1D*)gPad -> DrawFrame(0, 0.000001, 25, 0.01);
        
        htmp -> GetXaxis() -> SetTitle("pTsum in backward-range of charged particles");
        htmp -> GetYaxis() -> SetTitle("# of events");
        
        leg[lowedge_targetpT] -> Draw("p same");

        pTsum[lowedge_targetpT] -> SetMarkerStyle(25);
        pTsum[lowedge_targetpT] -> SetMarkerColor(1);
        pTsum[lowedge_targetpT] -> SetLineColor(1);
        pTsum[lowedge_targetpT] -> Draw("p same");

        for(int i=0; i<9; i++)
        {
            centpTsum[i] -> Draw("p same");
        }

    }



}
