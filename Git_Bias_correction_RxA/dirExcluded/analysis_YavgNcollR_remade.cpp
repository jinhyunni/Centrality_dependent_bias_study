void analysis_YavgNcollR_remade()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
	TFile* input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
	
	//historams

	////pAu
	TH2D* h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
	TH2D* h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");
	////avgNcoll
	TProfile* avgNcoll = (TProfile*)input2 -> Get("avgNcoll");



	//pAu yield vs pT(0~14 GeV)
	TH1D *pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);	//pion0 pT in event cent 0~10%
	TH1D *pAu2 = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);	//pion0 pT in event cent 10~20%
	TH1D *pAu3 = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);	//pino0 pT in event cent 20~40%
	TH1D *pAu4 = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);	//pion0 pT in event cent 40~60%
	TH1D *pAu5 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);	//pion0 pT in event cent 60~80%

	//scailing factor to get yield per event in each centrality class
	TH1D* h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent1");

	double num1 = h1cent -> GetBinContent(1);                                   // # of event in cent class1
	double num2 = h1cent -> GetBinContent(2);                                   // # of event in cent class2
	double num3 = h1cent -> GetBinContent(3) + h1cent -> GetBinContent(4);      // # of event in cent class3
	double num4 = h1cent -> GetBinContent(5) + h1cent -> GetBinContent(6);      // # of event in cent class4
	double num5 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);      // # of event in cent class5
    
    //1/N_event
	double scalar11 = 1./(num1);
	double scalar12 = 1./(num2);
	double scalar13 = 1./(num3);
	double scalar14 = 1./(num4);
	double scalar15 = 1./(num5);
	
	pAu1 -> Scale(scalar11);
	pAu2 -> Scale(scalar12);
	pAu3 -> Scale(scalar13);
	pAu4 -> Scale(scalar14);
	pAu5 -> Scale(scalar15);

	
 //	/*
 //		for checking
 //		# of particle per eta per event
 //	*/
 //	
 //	double n1 = pAu1R -> Integral(1, 4) + pAu2R -> Integral(1, 4) + pAu3R -> Integral(1, 4) + pAu4R -> Integral(1, 4) + pAu5R -> Integral(1, 4);
 //
 //	double n2 = pAu1R -> Integral(5, 10) + pAu2R -> Integral(5, 10) + pAu3R -> Integral(5, 10) + pAu4R -> Integral(5, 10) + pAu5R -> Integral(5, 10);
 //
 //	double n3 = pAu1R -> Integral(11, 22) + pAu2R -> Integral(11, 22) + pAu3R -> Integral(11, 22) + pAu4R -> Integral(11, 22) + pAu5R -> Integral(11, 22);
 //
 //	cout << "# of particle per #eta per #event in each centrality class\n" << endl;
 //
 //	cout << "0~2 GeV total # of event: " << n1 << endl;
 //	cout << "2~5 GeV total # of event: " << n2 << endl;
 //	cout << "5~  GeV total # of event: " << n3 << endl;
 //
 //	cout << "************\n" << endl;



	//Yield/<Ncoll>, more than 0, under 2 GeV, Y(pTclass)(centClass)
	double Y11 = pAu1 -> Integral(1, 199)/(avgNcoll -> GetBinContent(1));
	double Y12 = pAu2 -> Integral(1, 199)/(avgNcoll -> GetBinContent(2));
	double Y13 = pAu3 -> Integral(1, 199)/(avgNcoll -> GetBinContent(3));
	double Y14 = pAu4 -> Integral(1, 199)/(avgNcoll -> GetBinContent(4));
	double Y15 = pAu5 -> Integral(1, 199)/(avgNcoll -> GetBinContent(5));

	//Yield/<Ncoll>, more than 2, under 5 GeV, Y(pTclass)(centClass)
	double Y21 = pAu1 -> Integral(200, 1400);
	double Y22 = pAu2 -> Integral(200, 1400);
	double Y23 = pAu3 -> Integral(200, 1400);
	double Y24 = pAu4 -> Integral(200, 1400);
	double Y25 = pAu5 -> Integral(200, 1400);

 //	//Yield/<Ncoll>, more than 2, under 5 GeV, Y(pTclass)(centClass)
 //	double Y31 = pAu1 -> Integral(500, 1400)/(avgNcoll -> GetBinContent(1));
 //	double Y32 = pAu2 -> Integral(500, 1400)/(avgNcoll -> GetBinContent(2));
 //	double Y33 = pAu3 -> Integral(500, 1400)/(avgNcoll -> GetBinContent(3));
 //	double Y34 = pAu4 -> Integral(500, 1400)/(avgNcoll -> GetBinContent(4));
 //	double Y35 = pAu5 -> Integral(500, 1400)/(avgNcoll -> GetBinContent(5));

 // cout<< "Y/<Ncoll> in 0~2 GeV\n" << endl; 
 //	cout<< Y11 << endl;
 //	cout<< Y12 << endl;
 //	cout<< Y13 << endl;
 //	cout<< Y14 << endl;
 //	cout<< Y15 << endl;
 //	cout<<"*****"<<endl;
 //
 //	cout<< Y21 << endl;
 //	cout<< Y22 << endl;
 //	cout<< Y23 << endl;
 //	cout<< Y24 << endl;
 //	cout<< Y25 << endl;
 //	cout<<"*****"<<endl;
 //	
 //	cout<< Y31 << endl;
 //	cout<< Y32 << endl;
 //	cout<< Y33 << endl;
 //	cout<< Y34 << endl;
 //	cout<< Y35 << endl;
 //	cout<<"*****"<<endl;

	//Y/<Ncoll> vs Centrality
	TH1D *plot1 = new TH1D("YavgNcollR1", "0~2GeV", 5, 0, 80);
	TH1D *plot2 = new TH1D("YavgNcollR2", "2~5GeV", 5, 0, 80);
	TH1D *plot3 = new TH1D("YavgNcollR3", "5~ GeV", 5, 0, 80);
	double bins[]={0, 10, 20, 40, 60, 80};

	plot1 -> GetXaxis() -> Set(5, bins);
	plot2 -> GetXaxis() -> Set(5, bins);
	plot3 -> GetXaxis() -> Set(5, bins);

	
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

 //	//5~ GeVv
 //	plot3 -> SetBinContent(1, Y31);
 //	plot3 -> SetBinContent(2, Y32);
 //	plot3 -> SetBinContent(3, Y33);
 //	plot3 -> SetBinContent(4, Y34);
 //	plot3 -> SetBinContent(5, Y35);

 //	//set false error	
 //	//0~2GeV
 // plot1 -> SetBinError(1, 1./sqrt(num1));
 // plot1 -> SetBinError(2, 1./sqrt(num2));
 // plot1 -> SetBinError(3, 1./sqrt(num3));
 // plot1 -> SetBinError(4, 1./sqrt(num4));
 // plot1 -> SetBinError(5, 1./sqrt(num5));
 //	
 //	//2~5GeV
 //	plot2 -> SetBinError(1, 1./sqrt(num1));
 //	plot2 -> SetBinError(2, 1./sqrt(num2));
 //	plot2 -> SetBinError(3, 1./sqrt(num3));
 //	plot2 -> SetBinError(4, 1./sqrt(num4));
 //	plot2 -> SetBinError(5, 1./sqrt(num5));
 //	
 //	//5~GeV
 //	plot3 -> SetBinError(1, 1./sqrt(num1));
 //	plot3 -> SetBinError(2, 1./sqrt(num2));
 //	plot3 -> SetBinError(3, 1./sqrt(num3));
 //	plot3 -> SetBinError(4, 1./sqrt(num4));
 //	plot3 -> SetBinError(5, 1./sqrt(num5));

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
