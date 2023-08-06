void analysis_YieldByCentrality()
{
    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0.root", "read");

    
    //Target particle: pion0(111)

    TH2D *h2pTcent = (TH2D*)input1 -> Get("centPion0");
    TH2D *h2ncollcent = (TH2D*)input2 -> Get("ncollCentPion0");

    //projections
    TH1D *h1yieldCent = (TH1D*)h2pTcent -> ProjectionX();
    TH1D *h1nEventCent = (TH1D*)h2ncollcent -> ProjectionX();

    //dive two to get yield of pion0 by centrality
    TH1D *yield = (TH1D*)h1yieldCent->Clone("yield");
    yield -> Divide(h1nEventCent);

    TFile *output = new TFile("pAu200GeV_option3_dirAdded_decayOn_pion0YieldCent.root", "recreate");
    yield -> Write();
    output -> Close();
    
    input1 -> Close();
    input2 -> Close();

    delete output;
    delete input1;
    delete input2;
}
