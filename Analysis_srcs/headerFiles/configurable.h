#ifndef CONFIG
#define CONFIG

//Histogram bin edges for cent, pT class

//double pTBin[]={2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	const int pTBinNum=5;
double pTBin[]={0.0, 2.0, 4.0, 7.0, 10.0, 15.0, 20.0};	const int pTBinNum=6;
//double pTBin[]={2.0, 4.0, 7.0, 10.0, 20.0};	const int pTBinNum=4;
//double pTBin[]={0, 10.0, 20.0};	const int pTBinNum=3;
//double pTBin[]={0, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.0, 9.0, 11.0, 15.0, 20.0}; const int pTBinNum = 11;
//double pTrange[] = {0, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0}; const int pTBinNum = 11;

double centBin[]={0., 10., 20., 40., 60., 80.}; const int centBinNum = 5;
double centBin_default[]={0., 10., 20., 30., 40., 50., 60., 70., 80., 90., 100., 110.}; const int centBin_defaultNum = 11;
double centBin_Merged[]={0, 110}; const int centBin_MergedNum = 1;

double etaBin[]={-5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0., 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};	const int etaBinNum = 20;
//double etaBin[]={-5.0, -4.0, -3.0, -2.0, -1.0, 0., 1.0, 2.0, 3.0, 4.0, 5.0};	const int etaBinNum = 10;

 //*//Bin index information
 //*int pTClassIndex[]={201, 400, 401, 700, 701, 1000, 1001, 1500, 1501, 2000};
 //*int centClassIndex[]={1, 10, 11, 20, 21, 40, 41, 60, 61, 80};

#endif
