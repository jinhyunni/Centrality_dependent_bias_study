#include "../headerFiles/configurable_correlations.h"

void analysis_correlations_withPion0_charge()
{
    //input
    //-----
    TFile *input1 = new TFile("../pre_processed/pAu200GeV_p8303_ver2_option3_correlations_withPion0_TH3DpTetaCent_charge.root", "read");
    
    TH3D *charge_corWithPion0[5];
    for(int i=0; i<5; i++)
    {
        TString inputname = Form("charge_corWithPion0_pTClass%d", i+1);
        charge_corWithPion0[i] = (TH3D*)input1 -> Get(inputname);
    }


    //Analysis1. Get Particle eta dist. by pTClass and centClass
    //----------------------------------------------------------
    TH1D *charge_corWithPion0_pTClass_centClass[pTClass_edge][centClass_edge];

    for(int i=0; i < pTClass_edge; i++)
    {  //i: pT Class loop 
		int pTClass_start = 2*i;
		int pTClass_finish = 2*i + 1;
		
		cout << "**pTClass " << i+1 << " analyze start**\n" << endl;

		for(int j=0; j<centClass_edge; j++)
		{
			//j: cent class loop
			int centClass_start = 2*j;
			int centClass_finish = 2*j+1;

			cout << "\tcentClass " << j+1 << "start" << endl;

	        TString outputname  = Form("charge_eta_corWithPion0_pTClass%d_centClass%d", i+1, j+1);
			charge_corWithPion0_pTClass_centClass[i][j] = (TH1D*)charge_corWithPion0[i] -> ProjectionX(outputname, pTClass_start, pTClass_finish, centClass_start, centClass_finish);
			
			cout << "\tcentClass " << j+1 << "finished\n" << endl;

		}//cent loop finished

		cout << "**pTClass " << i+1 << " analyze finished**\n" << endl;
    }// pT loop finished

        
    //output
    //------
    TFile *output = new TFile("pAu200GeV_p8303ver2_option3_correlations_withPion0_charge_bypTClass_byCentClass.root", "recreate");

	output -> cd();
    for(int i=0; i<pTClass_edge; i++)
    {       
        for(int j=0; j<centClass_edge; j++)
        {
            charge_corWithPion0_pTClass_centClass[i][j] -> Write();
        }
    }
    output -> Close();

}
