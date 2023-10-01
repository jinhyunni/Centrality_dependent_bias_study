void analysis_YavgNcollR_remade()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_highpT.root", "read");
    TFile *input3 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_lowpT.root", "read");
    TFile *input4 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentPion0_highpT.root", "read");
    TFile *input5 = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentPion0_lowpT.root", "read");

	//historams

	////pAu
	TH2D *h2pTcent = (TH2D*)input1 -> Get("centPion0");
	TH2D *h2ncollcent_high = (TH2D*)input2 -> Get("ncollCentPion0");
    TH2D *h2ncollcent_low = (TH2D*)input3 -> Get("ncollCentPion0");

	////avgNcoll
 	TProfile* avgNcoll_high = (TProfile*)input4 -> Get("avgNcollCentPion0");
 	TProfile* avgNcoll_low = (TProfile*)input5 -> Get("avgNcollCentPion0");


	//pAu yield vs pT(0~14 GeV)
	TH1D *pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);	//pion0 pT in event cent 0~10%
	TH1D *pAu2 = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);	//pion0 pT in event cent 10~20%
	TH1D *pAu3 = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);	//pino0 pT in event cent 20~40%
	TH1D *pAu4 = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);	//pion0 pT in event cent 40~60%
	TH1D *pAu5 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);	//pion0 pT in event cent 60~80%


	//scailing factor to get yield per event in each centrality class
	TH1D *h1cent_high = (TH1D*)h2ncollcent_high -> ProjectionX("h1cent_high");
    TH1D *h1cent_low = (TH1D*)h2ncollcent_low -> ProjectionX("h1cent_low");
    
    //in low pT region
	double num_low_1 = h1cent_low -> GetBinContent(1);                                          // # of event in cent class1
	double num_low_2 = h1cent_low -> GetBinContent(2);                                          // # of event in cent class2
	double num_low_3 = h1cent_low -> GetBinContent(3) + h1cent_low -> GetBinContent(4);         // # of event in cent class3
	double num_low_4 = h1cent_low -> GetBinContent(5) + h1cent_low -> GetBinContent(6);         // # of event in cent class4
	double num_low_5 = h1cent_low -> GetBinContent(7) + h1cent_low -> GetBinContent(8);         // # of event in cent class5
    
    //in high pT region
    double num_high_1 = h1cent_high -> GetBinContent(1);                                        // # of event in cent class1
	double num_high_2 = h1cent_high -> GetBinContent(2);                                        // # of event in cent class2
	double num_high_3 = h1cent_high -> GetBinContent(3) + h1cent_high -> GetBinContent(4);      // # of event in cent class3
	double num_high_4 = h1cent_high -> GetBinContent(5) + h1cent_high -> GetBinContent(6);      // # of event in cent class4
	double num_high_5 = h1cent_high -> GetBinContent(7) + h1cent_high -> GetBinContent(8);      // # of event in cent class5
      
    //Cloning histogram
    TH1D *pAu1_low = (TH1D*)pAu1 -> Clone("pAu1_low");
    TH1D *pAu2_low = (TH1D*)pAu2 -> Clone("pAu2_low");
    TH1D *pAu3_low = (TH1D*)pAu3 -> Clone("pAu3_low");
    TH1D *pAu4_low = (TH1D*)pAu4 -> Clone("pAu4_low");
    TH1D *pAu5_low = (TH1D*)pAu5 -> Clone("pAu5_low");
  
    TH1D *pAu1_high = (TH1D*)pAu1 -> Clone("pAu1_high");
    TH1D *pAu2_high = (TH1D*)pAu2 -> Clone("pAu2_high");
    TH1D *pAu3_high = (TH1D*)pAu3 -> Clone("pAu3_high");
    TH1D *pAu4_high = (TH1D*)pAu4 -> Clone("pAu4_high");
    TH1D *pAu5_high = (TH1D*)pAu5 -> Clone("pAu5_high");

    //dividing event num
    pAu1_low -> Scale(1./num_low_1);
    pAu2_low -> Scale(1./num_low_2);
    pAu3_low -> Scale(1./num_low_3);
    pAu4_low -> Scale(1./num_low_4);
    pAu5_low -> Scale(1./num_low_5);

    pAu1_high -> Scale(1./num_high_1);
    pAu2_high -> Scale(1./num_high_2);
    pAu3_high -> Scale(1./num_high_3);
    pAu4_high -> Scale(1./num_high_4);
    pAu5_high -> Scale(1./num_high_5);


    

	//Yield/<Ncoll>, more than 0, under 2 GeV, Y(pTclass)(centClass)
	double Y11 = pAu1_low -> Integral(1, 200)/(avgNcoll_low -> GetBinContent(1));
	double Y12 = pAu2_low -> Integral(1, 200)/(avgNcoll_low -> GetBinContent(2));
	double Y13 = pAu3_low -> Integral(1, 200)/(avgNcoll_low -> GetBinContent(3));
	double Y14 = pAu4_low -> Integral(1, 200)/(avgNcoll_low -> GetBinContent(4));
	double Y15 = pAu5_low -> Integral(1, 200)/(avgNcoll_low -> GetBinContent(5));

	//Yield/<Ncoll>, more than 2, under 14 GeV, Y(pTclass)(centClass)
    double Y21 = pAu1_high -> Integral(201, 1400)/(avgNcoll_high -> GetBinContent(1));
	double Y22 = pAu2_high -> Integral(201, 1400)/(avgNcoll_high -> GetBinContent(2));
	double Y23 = pAu3_high -> Integral(201, 1400)/(avgNcoll_high -> GetBinContent(3));
	double Y24 = pAu4_high -> Integral(201, 1400)/(avgNcoll_high -> GetBinContent(4));
	double Y25 = pAu5_high -> Integral(201, 1400)/(avgNcoll_high -> GetBinContent(5));


 //    double Y21 = pAu1_high -> Integral(200, 1400);
 //	double Y22 = pAu2_high -> Integral(200, 1400);
 //	double Y23 = pAu3_high -> Integral(200, 1400);
 //	double Y24 = pAu4_high -> Integral(200, 1400);
 //	double Y25 = pAu5_high -> Integral(200, 1400);

 
	//Y/<Ncoll> vs Centrality
	TH1D *plot1 = new TH1D("YavgNcollR1", "0~2GeV", 5, 0, 80);
	TH1D *plot2 = new TH1D("YavgNcollR2", "2~5GeV", 5, 0, 80);
	double bins[]={0, 10, 20, 40, 60, 80};
    
    plot1 -> SetTitle("YavgNcoll_0to2GeV");
    plot2 -> SetTitle("YavgNcoll_over2GeV");

	plot1 -> GetXaxis() -> Set(5, bins);
	plot2 -> GetXaxis() -> Set(5, bins);

	
	//Ratio
	//0~2 GeV	
	plot1 -> SetBinContent(1, Y11);
	plot1 -> SetBinContent(2, Y12);
	plot1 -> SetBinContent(3, Y13);
	plot1 -> SetBinContent(4, Y14);
	plot1 -> SetBinContent(5, Y15);

	//2~5GeV
	plot2 -> SetBinContent(1, Y21);
	plot2 -> SetBinContent(2, Y22);
	plot2 -> SetBinContent(3, Y23);
	plot2 -> SetBinContent(4, Y24);
	plot2 -> SetBinContent(5, Y25);

 
 //	TFile *outfile = new TFile("pAu200GeV_option3_YavgNcollR_old.root", "recreate");
 //
 //	plot1 -> Write();
 //	plot2 -> Write();
 //	plot3 -> Write();
 //
 //	outfile -> Close();
    
 //    TFile *output = new TFile("pAu200GeV_option3_YavgNcoll_remade.root", "recreate");
 //	plot1 -> Write();
 //    output -> Close();

    plot2 -> Draw();

}
