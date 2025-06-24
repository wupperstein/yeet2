#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>
#include <iostream>
using namespace std;

void analysis::Loop()
{
    TH2 *wireCorrHisto1 = new TH2D("Abstandsdifferenz gegen Abstandssumme","Abstandsdifferenz gegen Abstandssumme;Ort1-Ort2 [mm]; Ort1+Ort2 [mm]; Trefferanzahl", 60, -(8.5+8.5/(250*2.5)*2.5/2.), 8.5+8.5/(250*2.5)*2.5/2., 60, -8.5/(250*2.5)*2.5/2., 17.0+8.5/(250*2.5)*2.5/2.);
    TFile::Open("odb.root");
    TH1* dzh = static_cast<TH1*>(gDirectory->FindObjectAny("Orts-Driftzeit-Beziehung"));
    // Double_t time=200.0;
    // Double_t ort = dzh->GetBinContent(dzh->FindBin(time));
    if (fChain == 0) return;
    double szi_distance =120.5;
    double vertical_distance = sqrt(pow(17.0,2)-pow(8.5,2)); // vertical distance between wires in mm
    double horizontal_distance = 8.5; // horizontal distance between wires in mm
    double B =0.0;
    double A =0.0;
    int di =0;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    UInt_t range_up = 48; // upper limit for wire numbers
    UInt_t range_down = 0; // lower limit for wire numbers
    double angle_down = -20.0; // lower limit for angle in degrees
    double angle_up = 20.0; // upper limit for angle in degrees
    #ifdef TENDEGREES
        angle_down = -10.0; // lower limit for angle in degrees
        angle_up = 10.0; // upper limit for angle in degrees
    #endif
    #ifdef FIVEDEGREES
        angle_down = -5.0; // lower limit for angle in degrees
        angle_up = 5.0; // upper limit for angle in degrees
    #endif
    #ifdef FORTYFIVEDEGREES
        angle_down = -45.0; // lower limit for angle in degrees
        angle_up = 45.0; // upper limit for angle in degrees
    #endif
    #ifdef SIXTYDEGREES
        angle_down = -60.0; // lower limit for angle in degrees
        angle_up = 60.0; // upper limit for angle in degrees
    #endif
    #ifdef NINTYDEGREES
        angle_down = -90.0; // lower limit for angle in degrees
        angle_up = 90.0; // upper limit for angle in degrees
    #endif
    #ifdef TENTWENTY
        angle_down = 10.0; // lower limit for angle in degrees
        angle_up = 20.0; // upper limit for angle in degrees
    #endif
    #ifdef TWENTYTHIRTY
        angle_down = 20.0; // lower limit for angle in degrees
        angle_up = 30.0; // upper limit for angle in degrees
    #endif
    #ifdef THIRTYFORTY
        angle_down = 30.0; // lower limit for angle in degrees
        angle_up = 40.0; // upper limit for angle in degrees
    #endif
    #ifdef FORTYSIXTY
        angle_down = 40.0; // lower limit for angle in degrees
        angle_up = 60.0; // upper limit for angle in degrees
    #endif
    #ifdef SIXTYNINTY
        angle_down = 60.0; // lower limit for angle in degrees
        angle_up = 90.0; // upper limit for angle in degrees
    #endif

    for (Long64_t jentry=0; jentry < nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        for(UInt_t hit=0; hit < nhits_le; hit++)
        {
            Double_t time1=time_le[hit]*2.5; 
            Double_t timeot=tot[hit]*2.5;   // time over total
            if (timeot < 100.0)       // filter out hits with time over total < 100 ns
            {
                continue;
            }
            #ifdef WIREDISC
                if ((wire_le[hit] > range_up) || (wire_le[hit] < range_down))
                {
                    continue;
                }
            #endif
            if (wire_le[hit] % 2 == 0) // only odd wire numbers
            {
                continue;
            }
            #ifndef WIREDISC
            if (wire_le[hit] % 2 != 0)
            {
                B=szi_distance * 1.0;
                di= static_cast<int>(wire_le[hit])-7;
                A=horizontal_distance*(static_cast<double>(di));
                
            }
            else
            {  
                B=(vertical_distance + szi_distance) * 1.0;
                di = static_cast<int>(wire_le[hit]) - 9;
                A = horizontal_distance * static_cast<double>(di);
                
            }
            double theta = atan(A/B);
            // cout << "theta: " << theta* 180.0/M_PI << endl;
            if ((theta* 180.0/M_PI < angle_down) || (theta* 180.0/M_PI > angle_up))
            {
                continue;
            }
            #endif
            for (UInt_t j=0; j<nhits_le; j++)
            {
                // if (!(((wire_le[hit] % 2== 0) && (wire_le[j] % 2!= 0)) || ((wire_le[hit] % 2 != 0) && (wire_le[j] % 2== 0))))
                // {
                //     continue;
                // }
                // if (!((((wire_le[hit] % 2== 0) && (wire_le[hit] == wire_le[j]+1)) || ((wire_le[hit] % 2 != 0) && (static_cast<int>(wire_le[hit]) == static_cast<int>(wire_le[j])-1))) || (((wire_le[hit] % 2== 0) && (wire_le[hit] == wire_le[j]+3)) || ((wire_le[hit] % 2 != 0) && (static_cast<int>(wire_le[hit]) == static_cast<int>(wire_le[j])-3)))))
                // {
                //     continue;
                // }
                if (!((wire_le[j] == wire_le[hit]+1) || (wire_le[j] == wire_le[hit]+3)))
                {
                    continue;
                }
                #ifdef WIREDISC
                if ((wire_le[j] > range_up) || (wire_le[j] < range_down))
                {
                    continue;
                }
                #endif
                #ifndef WIREDISC
                if (wire_le[j] % 2 != 0)
                {
                    B=szi_distance * 1.0;
                    di= static_cast<int>(wire_le[j])-7;
                    A=horizontal_distance*(static_cast<double>(di));
                    
                }
                else
                {  
                    B=(vertical_distance + szi_distance) * 1.0;
                    di = static_cast<int>(wire_le[j]) - 9;
                    A = horizontal_distance * static_cast<double>(di);
                    
                }
                double theta = atan(A/B);
                if ((theta* 180.0/M_PI < angle_down) || (theta* 180.0/M_PI > angle_up))
                {
                    continue;
                }
                #endif
                Double_t timeot2=tot[j]*2.5;
                if (timeot2 < 100.0)
                {
                    continue;
                }
                Double_t time2 = time_le[j]*2.5;
                Double_t ort1 = dzh->GetBinContent(dzh->FindBin(time1));
                Double_t ort2 = dzh->GetBinContent(dzh->FindBin(time2));
                wireCorrHisto1->Fill(ort1-ort2,ort1+ort2);
            }
        }         
        // if (Cut(ientry) < 0) continue;
    }
    gStyle->SetPalette(kRainBow);
    wireCorrHisto1->SetStats(0);
    wireCorrHisto1->SetContour(1000);
    gStyle->SetNumberContours(500);
    gStyle->SetOptStat(0);
    wireCorrHisto1->Draw("COLZ");
}

int main(int argc, char** argv) {
    TROOT root("app","app");
    Int_t dargc=1;
    char** dargv = &argv[0];
    TRint *app = new TRint("app", &dargc, dargv);
    //TRint *app = new TRint("app", 0, NULL);
    TCanvas *c1 = new TCanvas("c", "c", 800, 600);
    TFile *f=new TFile(argv[1]);
    TTree *tree=(TTree*)f->FindObjectAny("t");
    //tree->Dump();
    analysis* ana = new analysis(tree);
    ana->Loop();

    app->Run(kTRUE);
}
