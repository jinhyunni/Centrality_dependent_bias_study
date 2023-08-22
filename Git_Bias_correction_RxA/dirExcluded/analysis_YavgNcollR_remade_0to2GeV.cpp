void analysis_YavgNcollR_remade_0to2GeV()
{
	//Read in files
	TFile* input1 = new TFile("pAu200GeV_option3_pion0Analysis.root", "read");
    TFile *input2 = new TFile("pAu200GeV_option3_avgNcoll.root", "read");
   
	//historams

	////pAu
	TH2D *h2pTcent = (TH2D*)input1 -> Get("pTpion0_cent");
    TH2D *h2ncollcent = (TH2D*)input1 -> Get("ncoll_cent");   

	////avgNcoll
    TProfile *avgNcoll = (TProfile*)input2 -> Get("avgNcoll");


	//pAu yield vs pT(0~14 GeV)
	TH1D *pAu1 = (TH1D*)h2pTcent -> ProjectionY("pAu1", 1, 1);	//pion0 pT in event cent 0~10%
	TH1D *pAu2 = (TH1D*)h2pTcent -> ProjectionY("pAu2", 2, 2);	//pion0 pT in event cent 10~20%
	TH1D *pAu3 = (TH1D*)h2pTcent -> ProjectionY("pAu3", 3, 4);	//pino0 pT in event cent 20~40%
	TH1D *pAu4 = (TH1D*)h2pTcent -> ProjectionY("pAu4", 5, 6);	//pion0 pT in event cent 40~60%
	TH1D *pAu5 = (TH1D*)h2pTcent -> ProjectionY("pAu5", 7, 8);	//pion0 pT in event cent 60~80%


	//scailing factor to get yield per event in each centrality class
    TH1D *h1cent = (TH1D*)h2ncollcent -> ProjectionX("h1cent");


    double num1 = h1cent -> GetBinContent(1);
    double num2 = h1cent -> GetBinContent(2);
    double num3 = h1cent -> GetBinContent(3) + h1cent -> GetBinContent(4);
    double num4 = h1cent -> GetBinContent(5) + h1cent -> GetBinContent(6);
    double num5 = h1cent -> GetBinContent(7) + h1cent -> GetBinContent(8);

    pAu1 -> Scale(1./num1);
    pAu2 -> Scale(1./num2);
    pAu3 -> Scale(1./num3);
    pAu4 -> Scale(1./num4);
    pAu5 -> Scale(1./num5);


    double Y11 = pAu1 -> Integral(1, 199) / avgNcoll -> GetBinContent(1);
    double Y12 = pAu2 -> Integral(1, 199) / avgNcoll -> GetBinContent(2);
    double Y13 = pAu3 -> Integral(1, 199) / avgNcoll -> GetBinContent(3);
    double Y14 = pAu4 -> Integral(1, 199) / avgNcoll -> GetBinContent(4);
    double Y15 = pAu5 -> Integral(1, 199) / avgNcoll -> GetBinContent(5);
 
	//Y/<Ncoll> vs Centrality
	TH1D *plot1 = new TH1D("YavgNcollR1", "0~2GeV", 5, 0, 80);
	double bins[]={0, 10, 20, 40, 60, 80};
    
    plot1 -> SetTitle("YavgNcoll_0to2GeV");
	plot1 -> GetXaxis() -> Set(5, bins);
	
	//Ratio
	//0~2 GeV	
	plot1 -> SetBinContent(1, Y11);
	plot1 -> SetBinContent(2, Y12);
	plot1 -> SetBinContent(3, Y13);
	plot1 -> SetBinContent(4, Y14);
	plot1 -> SetBinContent(5, Y15);

 //    plot1 -> Draw();

    for(int i=0; i<5; i++)
    {
        cout << plot1 -> GetBinContent(i+1) << endl;
    }

}
