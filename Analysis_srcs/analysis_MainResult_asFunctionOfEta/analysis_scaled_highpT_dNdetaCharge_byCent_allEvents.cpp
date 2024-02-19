void analysis_scaled_highpT_dNdetaCharge_byCent_allEvents()
{
    TFile *input_dndeta = new TFile("pAu200GeV_p8303ver2_option3_highpT_dNdetaCharge_byCent_allEvents.root", "read");
    TFile *input_ncoll = new TFile("../pre_processed/pAu200GeV_p8303ver3_option3_avgNcollCent_allEvents.root", "read");

    TH1D *dndeta_highpTch_cent[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("highpT_dndeta_allEvents_cent%d", i+1);
        dndeta_highpTch_cent[i] = (TH1D*)input_dndeta -> Get(inputname);
    }
    
    double centrange[]= {0, 10, 20, 40, 60, 80};
    TProfile *avgNcollCent = (TProfile*)input_ncoll -> Get("avgNcollCent");
    TProfile *avgNcollCentR = (TProfile*)avgNcollCent -> Rebin(5, "avgNcollCentR", centrange);

    TH1D *scaled_highpTch_cent[5];
    for(int i=0; i<5; i++)
    {
        TString outputname = Form("scaled_dndeta_highpTch_cent%d", i+1);
        scaled_highpTch_cent[i] = (TH1D*)dndeta_highpTch_cent[i] -> Clone(outputname);

        scaled_highpTch_cent[i] -> Scale(1./avgNcollCentR -> GetBinContent(i+1));
    }
    
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_scaled_highpT_dNdetaCharge_byCent_allEvents.root", "recreate");
    for(int i=0; i<5; i++)
    {
        scaled_highpTch_cent[i] -> Write();
    }
    output -> Close();
}
