void check_ratio_yieldByCent()
{
    TFile *input_cent= new TFile("pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_byCentrality.root", "read");
    TFile *input_mb= new TFile("pAu200GeV_p8303ver4_option3_yieldOfgammaApion0_bypT_MBevents.root", "read");
    TFile *input_avgNcoll_cent = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcollCent_allEvents.root", "read");
    TFile *input_avgNcoll_mb = new TFile("../pre_processed/pAu200GeV_p8303ver4_option3_avgNcoll_MBevents.root", "read");

    //avgNcoll ratio of cent 2 mb
    //----------------------------------------
    TProfile *avgncoll_cent = (TProfile*)input_avgNcoll_cent -> Get("avgNcollCent");
    TProfile *avgncoll_mb = (TProfile*)input_avgNcoll_mb -> Get("avgNcoll_mb");

    double centrange[]={0, 10, 20, 40, 60, 80};
    TProfile *avgncollrange = (TProfile*)avgncoll_cent -> Rebin(5, "avgncollrange", centrange);

    double avgncoll_cent2mb[5];
    for(int i=0; i<5; i++)
    {
        avgncoll_cent2mb[i] = (avgncollrange -> GetBinContent(i+1))/(avgncoll_mb -> GetBinContent(1));

    }
    
    //making TLine indicating avgNcoll ratio
    TLine *avgncollrate_cent2peri[5];
    for(int i=0; i<5; i++)
    {
        avgncollrate_cent2peri[i] = new TLine(2, avgncoll_cent2mb[i], 20, avgncoll_cent2mb[i]);
    }


    //Check. dndpt ratio of cent 2 mb
    //--------------------------------------------
    TH1D *dndpt_pion0_cent[5];
    TH1D *dndpt_dir_cent[5];

    for(int i=0; i<5; i++)
    {
        TString inputname_pion0 = Form("dNdpT_pion0_cent%d", i+1);
        TString inputname_dir = Form("dNdpT_dir_cent%d", i+1);

        dndpt_pion0_cent[i] = (TH1D*)input_cent -> Get(inputname_pion0);
        dndpt_dir_cent[i] = (TH1D*)input_cent -> Get(inputname_dir);
    }

    //Take ratio
    //---------
    TH1D *cent1_peripheral_pion0[5];
    TH1D *cent1_peripheral_dir[5];

    TH1D *dndpt_pion0_mb = (TH1D*)input_mb -> Get("dNdpt_pion0_mb");
    TH1D *dndpt_dir_mb = (TH1D*)input_mb -> Get("dNdpt_dir_mb");

    for(int i=0; i<5; i++)
    {
        TString outputname_pion0 = Form("cent%d_centmb_pion0", i+1);
        TString outputname_dir = Form("cent%d_centmb_dir", i+1);
        
        //pion0
        cent1_peripheral_pion0[i] = (TH1D*)dndpt_pion0_cent[i] -> Clone(outputname_pion0);
        cent1_peripheral_pion0[i] -> Divide(dndpt_pion0_mb);
        
        //direct photon
        cent1_peripheral_dir[i] = (TH1D*)dndpt_dir_cent[i] -> Clone(outputname_dir);
        cent1_peripheral_dir[i] -> Divide(dndpt_dir_mb);

    }
    
    //Draw ratio
    //----------
    TCanvas *c1 = new TCanvas("", "", 800, 600);
    c1 -> Divide(2, 3);
    {
        //cent1
        //=====
        c1 -> cd(1);
        
        TH1D *htmp0 = (TH1D*)gPad -> DrawFrame(2, 0, 20, 3);
        
        htmp0 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
        htmp0 -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{0~10%}/(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{MB} ");

        cent1_peripheral_pion0[0] -> SetMarkerStyle(34);
        cent1_peripheral_pion0[0] -> SetMarkerColor(kOrange);
        cent1_peripheral_pion0[0] -> SetLineColor(kOrange);
        cent1_peripheral_pion0[0] -> Draw("p same");
    
        cent1_peripheral_dir[0] -> SetMarkerStyle(34);
        cent1_peripheral_dir[0] -> SetMarkerColor(kGreen+1);
        cent1_peripheral_dir[0] -> SetLineColor(kGreen+1);
        cent1_peripheral_dir[0] -> Draw("p same");

        avgncollrate_cent2peri[0] -> SetLineStyle(7);
        avgncollrate_cent2peri[0] -> SetLineColor(6);
        avgncollrate_cent2peri[0] -> Draw("p same");

        TLegend *l0 = new TLegend(0.4, 0.65, 0.8, 0.9);
        l0 -> SetFillStyle(0);
        l0 -> SetBorderSize(0);
        l0 -> SetTextSize(0.05);
        l0 -> AddEntry(avgncollrate_cent2peri[0], "#LTN_{coll}#GT_{0~10%} / #LTN_{coll}#GT_{MB}", "p");
        l0 -> AddEntry(cent1_peripheral_pion0[0], "Y^{#pi^{0}}_{0~10%} / Y^{#pi^{0}}_{MB}", "p");
        l0 -> AddEntry(cent1_peripheral_dir[0], "Y^{#gamma^{dir}}_{0~10%} / Y^{#gamma^{dir}}_{MB}", "p");
        l0 -> Draw();

        //cent2
        //===============
        c1 -> cd(2);
        
        TH1D *htmp1 = (TH1D*)gPad -> DrawFrame(2, 0, 20, 3);
        
        htmp1 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
        htmp1 -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{10~20%}/(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{MB} ");

        cent1_peripheral_pion0[1] -> SetMarkerStyle(34);
        cent1_peripheral_pion0[1] -> SetMarkerColor(kRed);
        cent1_peripheral_pion0[1] -> SetLineColor(kRed);
        cent1_peripheral_pion0[1] -> Draw("p same");
    
        cent1_peripheral_dir[1] -> SetMarkerStyle(34);
        cent1_peripheral_dir[1] -> SetMarkerColor(kTeal+1);
        cent1_peripheral_dir[1] -> SetLineColor(kTeal+1);
        cent1_peripheral_dir[1] -> Draw("p same");

        avgncollrate_cent2peri[1] -> SetLineStyle(7);
        avgncollrate_cent2peri[1] -> SetLineColor(6);
        avgncollrate_cent2peri[1] -> Draw("p same");

        TLegend *l1 = new TLegend(0.4, 0.65, 0.8, 0.9);
        l1 -> SetFillStyle(0);
        l1 -> SetBorderSize(0);
        l1 -> SetTextSize(0.05);
        l1 -> AddEntry(avgncollrate_cent2peri[1], "#LTN_{coll}#GT_{10~20%} / #LTN_{coll}#GT_{MB}", "p");
        l1 -> AddEntry(cent1_peripheral_pion0[1], "Y^{#pi^{0}}_{10~20%} / Y^{#pi^{0}}_{MB}", "p");
        l1 -> AddEntry(cent1_peripheral_dir[1], "Y^{#gamma^{dir}}_{10~20%} / Y^{#gamma^{dir}}_{MB}", "p");
        l1 -> Draw();
        
        //cent3
        //===============
        c1 -> cd(3);
        TH1D *htmp2 = (TH1D*)gPad -> DrawFrame(2, 0, 20, 3);

        htmp2 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
        htmp2 -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{20~40%}/(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{MB} ");
    
        cent1_peripheral_pion0[2] -> SetMarkerStyle(47);
        cent1_peripheral_pion0[2] -> SetMarkerColor(kMagenta);
        cent1_peripheral_pion0[2] -> SetLineColor(kMagenta);
        cent1_peripheral_pion0[2] -> Draw("p same");
    
        cent1_peripheral_dir[2] -> SetMarkerStyle(28);
        cent1_peripheral_dir[2] -> SetMarkerColor(kCyan+1);
        cent1_peripheral_dir[2] -> SetLineColor(kCyan+1);
        cent1_peripheral_dir[2] -> Draw("p same");

        avgncollrate_cent2peri[2] -> SetLineStyle(7);
        avgncollrate_cent2peri[2] -> SetLineColor(6);
        avgncollrate_cent2peri[2] -> Draw("p same");
        
        TLegend *l2 = new TLegend(0.4, 0.65, 0.8, 0.9);
        l2 -> SetFillStyle(0);
        l2 -> SetBorderSize(0);
        l2 -> SetTextSize(0.05);
        l2 -> AddEntry(avgncollrate_cent2peri[2], "#LTN_{coll}#GT_{20~40%} / #LTN_{coll}#GT_{MB}", "p");
        l2 -> AddEntry(cent1_peripheral_pion0[2], "Y^{#pi^{0}}_{20~40%} / Y^{#pi^{0}}_{MB}", "p");
        l2 -> AddEntry(cent1_peripheral_dir[2], "Y^{#gamma^{dir}}_{20~40%} / Y^{#gamma^{dir}}_{MB}", "p");
        l2 -> Draw();

        //ent4
        //===============
        c1 -> cd(4);
        TH1D *htmp3 = (TH1D*)gPad -> DrawFrame(2, 0, 20, 3);

        htmp3 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
        htmp3 -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{40~60%}/(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{MB} ");
        
        cent1_peripheral_pion0[3] -> SetMarkerStyle(28);
        cent1_peripheral_pion0[3] -> SetMarkerColor(kViolet);
        cent1_peripheral_pion0[3] -> SetLineColor(kViolet);
        cent1_peripheral_pion0[3] -> Draw("p same");
    
        cent1_peripheral_dir[3] -> SetMarkerStyle(47);
        cent1_peripheral_dir[3] -> SetMarkerColor(kAzure);
        cent1_peripheral_dir[3] -> SetLineColor(kAzure);
        cent1_peripheral_dir[3] -> Draw("p same");

        avgncollrate_cent2peri[3] -> SetLineStyle(7);
        avgncollrate_cent2peri[3] -> SetLineColor(6);
        avgncollrate_cent2peri[3] -> Draw("p same");

        TLegend *l3 = new TLegend(0.4, 0.65, 0.8, 0.9);
        l3 -> SetFillStyle(0);
        l3 -> SetBorderSize(0);
        l3 -> SetTextSize(0.05);
        l3 -> AddEntry(avgncollrate_cent2peri[3], "#LTN_{coll}#GT_{40~60%} / #LTN_{coll}#GT_{MB}", "p");
        l3 -> AddEntry(cent1_peripheral_pion0[3], "Y^{#pi^{0}}_{40~60%} / Y^{#pi^{0}}_{MB}", "p");
        l3 -> AddEntry(cent1_peripheral_dir[3], "Y^{#gamma^{dir}}_{40~60%} / Y^{#gamma^{dir}}_{MB}", "p");

        l3 -> Draw();
    
        //cent5
        //===============
        c1 -> cd(5);
        TH1D *htmp4 = (TH1D*)gPad -> DrawFrame(2, 0, 20, 3);

        htmp4 -> GetXaxis() -> SetTitle("p_{T}(GeV)");
        htmp4 -> GetYaxis() -> SetTitle("(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{60~80%}/(#frac{1}{N_{event}} #frac{dN}{dp_{T}})_{MB} ");

        cent1_peripheral_pion0[4] -> SetMarkerStyle(34);
        cent1_peripheral_pion0[4] -> SetMarkerColor(6);
        cent1_peripheral_pion0[4] -> SetLineColor(6);
        cent1_peripheral_pion0[4] -> Draw("p same");
    
        cent1_peripheral_dir[4] -> SetMarkerStyle(28);
        cent1_peripheral_dir[4] -> SetMarkerColor(kBlue);
        cent1_peripheral_dir[4] -> SetLineColor(kBlue);
        cent1_peripheral_dir[4] -> Draw("p same");

        avgncollrate_cent2peri[4] -> SetLineStyle(7);
        avgncollrate_cent2peri[4] -> SetLineColor(6);
        avgncollrate_cent2peri[4] -> Draw("p same");

        TLegend *l4 = new TLegend(0.4, 0.65, 0.8, 0.9);
        l4 -> SetFillStyle(0);
        l4 -> SetBorderSize(0);
        l4 -> SetTextSize(0.05);
        l4 -> AddEntry(avgncollrate_cent2peri[3], "#LTN_{coll}#GT_{60~80%} / #LTN_{coll}#GT_{MB}", "p");
        l4 -> AddEntry(cent1_peripheral_pion0[3], "Y^{#pi^{0}}_{60~80%} / Y^{#pi^{0}}_{MB}", "p");
        l4 -> AddEntry(cent1_peripheral_dir[3], "Y^{#gamma^{dir}}_{60~80%} / Y^{#gamma^{dir}}_{MB}", "p");

        l4 -> Draw();
    }
}
