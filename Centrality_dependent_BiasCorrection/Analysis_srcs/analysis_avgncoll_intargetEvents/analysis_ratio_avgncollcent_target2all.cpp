void analysis_ratio_avgncollcent_target2all()
{
	//input
	//-----
	TFile *input = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcollCent_inTargetEvents.root", "read");
	TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcollCent_allEvents.root", "read");
	
    //avgncoll in target events
	TProfile *avgncollcent_midpion0[5];
    TH1D *h1_avgncollcent_midpion0[5];

	for(int i=0; i<5; i++)
	{	
		TString inputname = Form("avgncollcent_midpion0_over%dGeV", 2*i+3);	
        TString turn2h1 = Form("h1_avgncollcent_midpion0_over%dGeV", 2*i+3);

		avgncollcent_midpion0[i] = (TProfile*)input -> Get(inputname);
        h1_avgncollcent_midpion0[i] = new TH1D(turn2h1, "", 11, 0 ,110);

        for(int j=0; j<avgncollcent_midpion0[i] -> GetNbinsX(); j++)
        {   
            h1_avgncollcent_midpion0[i] -> SetBinContent(j+1, avgncollcent_midpion0[i] -> GetBinContent(j+1));
            h1_avgncollcent_midpion0[i] -> SetBinError(j+1, avgncollcent_midpion0[i] -> GetBinError(j+1));
        }

	}	
    //avgncoll in allevents(mb)
    TProfile *avgncollcent_all = (TProfile*)input1 -> Get("avgNcollCent");
    TH1D *h1_avgncollcent_all = new TH1D("h1_avgncollcent_all", "", 11, 0, 110);

    for(int i=0; i< avgncollcent_all -> GetNbinsX(); i++)
    {
        h1_avgncollcent_all -> SetBinContent(i+1, avgncollcent_all -> GetBinContent(i+1));
        h1_avgncollcent_all -> SetBinError(i+1, avgncollcent_all -> GetBinError(i+1));
    }


	//Analysis1. set centrality range
	//--------------------------------
	double centrange[] = {0, 10, 20, 40, 60, 80};

    //rebin all events
    TH1D *avgncollcent_mb_rebinned = (TH1D*)h1_avgncollcent_all -> Rebin(5, "avgncollcent_allevents", centrange);
    
    //rebin target events
    TH1D *avgncollcent_midpion0_rebinned[5];
	for(int i=0; i<5; i++)
	{		
		TString outputname = Form("avgncollcent_midpion0R_over%dGeV", 2*i+3);
		avgncollcent_midpion0_rebinned[i] = (TH1D*)h1_avgncollcent_midpion0[i]->Rebin(5, outputname, centrange);
	}	
		
	//Analysis2. take ratio of target2all
    //-----------------------------------
    TH1D *target2all[5];
    for(int i=0; i<5; i++)
    {
        TString outputname = Form("target2all_midpion0_over%dGeV", 2*i+3);
        
        target2all[i] = (TH1D*)avgncollcent_midpion0_rebinned[i] -> Clone(outputname);
        target2all[i] -> Divide(avgncollcent_mb_rebinned);
    }

    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver4_ratio_avgncollcent_target2all.root", "recreate");

    for(int i=0; i<5; i++)
    {
        target2all[i] -> Write();
    }

}
