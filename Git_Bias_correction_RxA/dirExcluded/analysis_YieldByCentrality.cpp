void analysis_YieldByCentrality()
{
    TFile *input = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
    
    //Target particle: pion0(111)

    TH2D *h2pTcent = (TH2D*)input -> Get("pTpion0_cent");
    TH2D *h2ncollcent = (TH2D*)input -> Get("ncoll_cent");

    //projections
    TH1D *h1yieldCent = (TH1D*)h2pTcent -> ProjectionX();
    TH1D *h1nEventCent = (TH1D*)h2ncollcent -> ProjectionX();

    //dive two to get yield of pion0 by centrality
    TH1D *yield = (TH1D*)h1yieldCent->Clone("yield");
    yield -> Divide(h1nEventCent);

    TFile *output = new TFile("pAu200GeV_option3_pion0YieldCent", "recreate");

    yield -> Write();

    delete output;
}
