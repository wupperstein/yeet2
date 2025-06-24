#define analysis_cxx
#define _USE_MATH_DEFINES
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>
#include <cmath>
#include <iostream>
using namespace std;
void analysis::Loop()
{
    TH1D* winkelverteilung = new TH1D("winkelverteilung", "winkelverteilung", 400, -180., 180.0);
    TH2 *wireCorrHisto1 = new TH2D("wireCorre","wire corre;Draht nr; Draht nr; Entries", 90, -(8.5+8.5/(250*2.5)*2.5/2.), 8.5+8.5/(250*2.5)*2.5/2., 90, -8.5/(250*2.5)*2.5/2., 17.0+8.5/(250*2.5)*2.5/2.);
    TFile::Open("odb.root");
    TH1* dzh = static_cast<TH1*>(gDirectory->FindObjectAny("Orts-Driftzeit-Beziehung"));
    double szi_distance =125.0;
    double vertical_distance = sqrt(pow(17.0,2)-pow(8.5,2)); // vertical distance between wires in mm
    double horizontal_distance = 8.5; // horizontal distance between wires in mm
    double B =0.0;
    double A =0.0;
    double width = 10.5; // width of the scintillator in mm
    int di =0;

    // Double_t ort = dzh->GetBinContent(dzh->FindBin(time));
    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry < nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        for(UInt_t hit=0; hit < nhits_le; hit++)
        {
            if (wire_le[hit] % 2 == 0) // only odd wire numbers
            {
                continue;
            }
            double time1=time_le[hit]*2.5; 
            Double_t timeot=tot[hit]*2.5;   // time over total
            if (timeot < 100.0)       // filter out hits with time over total < 100 ns
            {
                continue;
            }
            double D_h= horizontal_distance*(static_cast<double>(static_cast<int>(wire_le[hit])-7)); 

            for (UInt_t j=0; j<nhits_le; j++)
            {
                // if (wire_le[hit]==wire_le[j])
                // {
                //     continue;
                // }
                Double_t timeot2=tot[j]*2.5;
                if (timeot2 < 100.0)
                {
                    continue;
                }
                if (wire_le[j] % 2 == 0)
                {
                    B=vertical_distance * 1.0;
                    A=horizontal_distance*(static_cast<double>(static_cast<int>(wire_le[j])-static_cast<int>(wire_le[hit])-2));
                }
                else
                {
                    continue;
                    B=0.0;
                    A=horizontal_distance*(static_cast<double>(static_cast<int>(wire_le[j])-static_cast<int>(wire_le[hit])));
                }
                double time2 = time_le[j]*2.5;
                double ort1 = static_cast<double>(dzh->GetBinContent(dzh->FindBin(time1)));
                double ort2 = static_cast<double>(dzh->GetBinContent(dzh->FindBin(time2)));
                // if(A<0.0){
                //     continue;
                // }
                double C = sqrt(pow(A,2)+pow(B,2));
                double theta1 = atan(B/A)-asin(abs(ort1-ort2)/C);
                double theta2 = atan(B/A)+asin(abs(ort1-ort2)/C);
                double theta3 = asin(B/C)+asin((ort1+ort2)/C);
                double theta4 = acos(A/C)+acos((ort1+ort2)/C)- M_PI/2.0;
                double D_h1= D_h - ort1* sin(theta1);
                double D_v1 = szi_distance + ort1* cos(theta1);
                double D_h2= D_h + ort1* sin(theta2);
                double D_v2 = szi_distance - ort1* cos(theta2);
                double D_h3= D_h + ort1* sin(theta3);
                double D_v3 = szi_distance - ort1* cos(theta3);
                double D_h4= D_h - ort1* sin(theta4);
                double D_v4 = szi_distance + ort1* cos(theta4);
                double theta_low1 = atan(D_h1/(D_v1+width));
                double theta_high1 = atan(D_h1/(D_v1-width));
                double theta_low2 = atan(D_h2/(D_v2+width));
                double theta_high2 = atan(D_h2/(D_v2-width));
                double theta_low3 = atan(D_h3/(D_v3+width));
                double theta_high3 = atan(D_h3/(D_v3-width));
                double theta_low4 = atan(D_h4/(D_v4+width));
                double theta_high4 = atan(D_h4/(D_v4-width));
                if (!((theta1 < theta_low1) || (theta1 > theta_high1))) {
                    winkelverteilung->Fill(theta1* 180.0/M_PI);
                }
                if (!((theta2 < theta_low2) || (theta2 > theta_high2))) {
                    winkelverteilung->Fill(theta2* 180.0/M_PI);
                    cout << "a" << endl;
                }
                if (!((theta3 < theta_low3) || (theta3 > theta_high3))) {
                    winkelverteilung->Fill(theta3* 180.0/M_PI);
                    cout << "b" << endl;
                }
                if (!((theta4 < theta_low4) || (theta4 > theta_high4))) {
                    winkelverteilung->Fill(theta4* 180.0/M_PI);
                    cout << "c" << endl;
                }
                // wireCorrHisto1->Fill(ort1-ort2,ort1+ort2);
                // winkelverteilung->Fill(theta1* 180.0/M_PI);
                // winkelverteilung->Fill(theta2* 180.0/M_PI);
                // winkelverteilung->Fill(theta3* 180.0/M_PI);
                // winkelverteilung->Fill(theta4* 180.0/M_PI);
            }
        }         
        // if (Cut(ientry) < 0) continue;
    }
    gStyle->SetPalette(kRainBow);
    wireCorrHisto1->SetStats(0);
    wireCorrHisto1->SetContour(1000);
    gStyle->SetOptStat(0);
    winkelverteilung->Draw();
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