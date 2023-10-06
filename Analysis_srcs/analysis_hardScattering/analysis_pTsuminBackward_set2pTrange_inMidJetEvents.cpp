void analysis_pTsuminBackward_set2pTrange_inMidJetEvents()
{   
    //input
    //-----
    TFile *input = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_TH1DpTsumTriggerpT_set2pTrange_limited_inMidJetEvents.root", "read");

    TH1D *pTsum[5];
    pTsum[0] = (TH1D*)input -> Get("pTsumTriggerpT_2to3GeV");
    pTsum[1] = (TH1D*)input -> Get("pTsumTriggerpT_3to5GeV");
    pTsum[2] = (TH1D*)input -> Get("pTsumTriggerpT_5to7GeV");
    pTsum[3] = (TH1D*)input -> Get("pTsumTriggerpT_7to9GeV");
    pTsum[4] = (TH1D*)input -> Get("pTsumTriggerpT_morethan9GeV");
 //    pTsum[5] = (TH1D*)input -> Get("pTsumTriggerpT_11to15GeV");
 //    pTsum[6] = (TH1D*)input -> Get("pTsumTriggerpT_15to20GeV");
    

    //Analysis1: Scale to get # of event per pTsum
    // 1: event number scaling
    // 2: binwidth scaling
    //double pTsumEdge[]={0, 0.341, 0.754, 1.161, 1.589, 2.049, 2.554, 3.134, 3.851, 4.909, 25};

    //eventnumber scaling
    for(int i=0; i<5; i++)
    {
        pTsum[i] -> Scale(1./pTsum[i] -> Integral());
    }

    //rebinning to fit centrality pTsum range
    TH1D *pTsum_rebinned[5];
    for(int i=0; i<5; i++)
    {   
        TString outputname = Form("pTsum_rebinned_midpion0_highpT%d", i+1);
        pTsum_rebinned[i] = (TH1D*)pTsum[i] -> RebinX(100, outputname);
    }

    //dividing binwidth
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<pTsum_rebinned[i] -> GetNbinsX(); j++)
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
    TFile *output = new TFile("pAu200GeV_p8303ver4_option3_pTsuminBackward_set2pTrange_limitedinMidJetEvents.root", "recreate");
    for(int i=0; i<5; i++)
    {
        pTsum_rebinned[i] -> Write();
    }
    output -> Close();

}
