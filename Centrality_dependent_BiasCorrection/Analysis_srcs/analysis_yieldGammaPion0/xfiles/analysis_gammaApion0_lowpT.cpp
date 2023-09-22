#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>



void analysis_gammaApion0_lowpT()
{
    //input
    //-------------------------
    TFile *pion1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2Dpion0Cent.root", "read");
    TFile *dir1 = new TFile("pAu200GeV_option3_dirAdded_decayOn_TH2DdirCent.root", "read");

    TFile *pion2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentPion0_lowpT.root", "read");
    TFile *dir2 = new TFile("pAu200GeV_option3_dirAdded_decayOn_NcollCentDir_highpT.root", "read");

    TFile *avgPion0Low = new TFile("pAu200GeV_option3_dirAdded_decayOn_avgNcollCentPion0_lowpT.root", "read");

    //output
    //-------------------------
    TFile *output = new TFile("pAu200GeV_option3_dirAdded_decayOn_gammaApion0_lowpT.root", "recreate");

    //Input histograms
    //--------------------------
    TH2D *h2centPion0 = (TH2D*)pion1 -> Get("centPion0");
    TH2D *h2centDir = (TH2D*)dir1 -> Get("centDir");

    TH2D *h2NcollCentPion0 = (TH2D*)pion2 -> Get("ncollCentPion0");
    TH2D *h2NcollCentDir = (TH2D*)dir2 -> Get("ncollCentDir");

    TH1D *avgNcollPion0 = (TH1D*)avgPion0Low -> Get("avgNcollCentPion0");

    //Analysis1. Projection to get Yield
    //In high pT region: more than 2 GeV
    //pT binning: 0~14 GeV, 1400 binning
    //--------------------------
    TH1D *Ypion0Cent = (TH1D*)h2centPion0 -> ProjectionX("pion0Projection", 1, 200);
    TH1D *YdirCent = (TH1D*)h2centDir -> ProjectionX("dirProjection", 1, 200);
    TH1D *nEvntCentP = (TH1D*)h2NcollCentPion0 -> ProjectionX("nEvntCentP");
    TH1D *nEvntCentD = (TH1D*)h2NcollCentDir -> ProjectionX("nEvntCentD");
    
    //Analysis2. Rebin to fit cent Class
    //0~10%
    //10~20e
    //20~40%
    //40~60%
    //60~80%
    //--------------------------
    double binEdge[]={0, 10, 20, 40, 60, 80};

    TH1D *Ypion0CentR = (TH1D*)Ypion0Cent -> Rebin(5, "Ypion0CentR", binEdge);
    TH1D *YdirCentR = (TH1D*)YdirCent -> Rebin(5, "YdirCentR", binEdge);
    TH1D *nEventCentPR = (TH1D*)nEvntCentP -> Rebin(5, "nEventCentPR", binEdge);
    TH1D *nEventCentDR = (TH1D*)nEvntCentD -> Rebin(5, "nEventCentDR", binEdge);
    TH1D *avgNcollPion0R = (TH1D*)avgNcollPion0 -> Rebin(5, "avgNcollPion0R", binEdge);
    


    //Analysis3. Get cent vs pion0(Direct photon)
    //No need to divide centrality width -> Cancel in ratio
    //--------------------------
    TH1D *Ypion0 = (TH1D*)Ypion0CentR -> Clone("Ypion0");
    Ypion0 -> Divide(nEventCentPR);
    Ypion0 -> SetTitle("yield_of_pion0");
    Ypion0 -> GetXaxis() -> SetTitle("Centrality");
    Ypion0 -> GetYaxis() -> SetTitle("Yield #pi^{0}");

    TH1D *Ydir = (TH1D*)YdirCentR -> Clone("Ydir");
    Ydir -> Divide(nEventCentDR);
    Ydir -> SetTitle("yield_of_dir");
    Ydir -> GetXaxis() -> SetTitle("Centrality");
    Ydir -> GetYaxis() -> SetTitle("yield #gamma^{dir}");

    //Analysis4. divide yield above wiht avgNcoll, pion0 only for test
    TH1D *Ypion0avgNcoll = (TH1D*)Ypion0 -> Clone("Ypion0avgNcoll");
    Ypion0avgNcoll -> Divide(avgNcollPion0R);
    Ypion0avgNcoll -> SetTitle("YavgNcoll_pion0_lowpT");

 //    //gamma/pion0 ratio by centrality
 //    TH1D *gammaOverPion0 = (TH1D*)Ydir -> Clone("gammaOverPion0");
 //    gammaOverPion0 -> Divide(Ypion0);

    //Write outputs in outputfile
    Ypion0 -> Write();
    Ydir -> Write();
    Ypion0avgNcoll -> Write();
    //gammaOverPion0 -> Write();
    
    //Close files
    pion1 -> Close();
    pion2 -> Close();
    dir1 -> Close();
    dir2 -> Close();
    output -> Close();

 //    //disallocation
 //    delete pion1;
 //    delete pion2;
 //    delete dir1;
 //    delete dir2;
 //    delete output;
    
   
    
}
