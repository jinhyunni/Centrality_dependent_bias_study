void analysis_numEventCheck()
{

    TFile *input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_highpT.root", "read");
    TFile *input3 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_lowpT.root", "read");

    TH2D *h2ncollcent_integ = (TH2D*)input1 -> Get("ncollCentPion0");
    TH2D *h2ncollcent_high = (TH2D*)input2 -> Get("ncollCentPion0");
    TH2D *h2ncollcent_low = (TH2D*)input3 -> Get("ncollCentPion0");

    TH1D *h1numEvent_integ = (TH1D*)h2ncollcent_integ -> ProjectionX();
    TH1D *h1numEvent_high = (TH1D*)h2ncollcent_high -> ProjectionX();
    TH1D *h1numEvent_low = (TH1D*)h2ncollcent_low -> ProjectionX();
    
    TH1D *h1numEvent_sum = (TH1D*)h1numEvent_high -> Clone("h1nunEvent_sum");

    h1numEvent_sum -> Add(h1numEvent_low);
 //    h1numEvent_sum -> Draw();

    h1numEvent_integ -> Draw();

 //    input1 -> Close();
 //    input2 -> Close();
 //    input3 -> Close();
 //
 //    delete input1;
 //    delete input2;
 //    delete input3;

}
