void analysis_pTsuminBackward_inMidJetEvents()
{   
    //input
    //-----
    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_TH2DpTsumTriggerpT_inMidJetEvents.root", "read");
    TH2D *h2pTsumPion0pT = (TH2D*)input -> Get("pTsumTriggerpT");

    //Analysis1: Get the number of event by pTsum
    // h2: x: target pion0's low-edge pT, y: pTsum of such events
    //-----------------------------------------------------------
    TH1D *pTsum[21];
    for(int i=0; i<21; i++)
    {
        TString outputname = Form("pTsum_midpion_%dto%dGeV", i, i+1);
        pTsum[i] = (TH1D*)h2pTsumPion0pT -> ProjectionY(outputname, i+1, i+1);
    }

    //Analysis2: Scale to get # of event per pTsum
    // 1: event number scaling
    // 2: binwidth scaling
    double pTsumEdge[]={0, 0.341, 0.754, 1.161, 1.589, 2.049, 2.554, 3.134, 3.851, 4.909, 25};

    //eventnumber scaling
    for(int i=0; i<21; i++)
    {
        pTsum[i] -> Scale(1./pTsum[i] -> Integral());
    }

    //rebinning to fit centrality pTsum range
    TH1D *pTsum_rebinned[21];
    for(int i=0; i<21; i++)
    {   
        TString outputname = Form("pTsum_rebinned_midpion0_%dto%dGeV", i, i+1);
        pTsum_rebinned[i] = (TH1D*)pTsum[i] -> Rebin(10, outputname, pTsumEdge);
    }

    //dividing binwidth
    for(int i=0; i<21; i++)
    {
        for(int j=0; j<10; j++)
        {

            double scalar = pTsum_rebinned[i] -> GetBinWidth(j+1);
            double bincontent = pTsum_rebinned[i] -> GetBinContent(j+1);
            double binerror = pTsum_rebinned[i] -> GetBinError(j+1);

            pTsum_rebinned[i] -> SetBinContent(j+1, bincontent/scalar);
            pTsum_rebinned[i] -> SetBinError(j+1, binerror/scalar);

        }//dividing

    }

    //Output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver4_option3_pTsuminBackward_inMidJetEvents.root", "recreate");
    for(int i=0; i<21; i++)
    {
        pTsum_rebinned[i] -> Write();
    }
    output -> Close();

}
