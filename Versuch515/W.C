#define analysis_cxx
#define _USE_MATH_DEFINES
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>
#include <cmath>
#include <TF1.h>

void analysis::Loop()
{
    TH1D* winkelverteilung = new TH1D("Winkelverteilung", "Winkelverteilung; Winkel [°];Trefferanzahl", 10000, -40., 80.);
    TH1D* gradewinkelverteilung = new TH1D("Winkelverteilung untere Reihe", "Winkelverteilung untere Reihe; Winkel [°];Trefferanzahl", 200, -40., 80.);
    TH1D* ungradewinkelverteilung = new TH1D("Winkelverteilung obere Reihe", "Winkelverteilung obere Reihe; Winkel [°];Trefferanzahl", 200, -40., 80.);
    TFile::Open("odb.root");
    TH1* dzh = static_cast<TH1*>(gDirectory->FindObjectAny("Orts-Driftzeit-Beziehung"));

    TF1 *winkel=new TF1("winkel","[0]*pow(cos(0.0174533*x),2)",-40,80);
    TF1 *winkel2=new TF1("winkel2","[0]*pow(cos(atan(x/[1])),2)",-80,340);
    // winkel->SetParameter(1, 0.0174533); // 0.0174533 is pi/180 to convert degrees to radians
    
    winkel->SetParameter(0, 1400.0);
    double szi_distance =121.6;
    double vertical_distance = sqrt(pow(17.0,2)-pow(8.5,2)); // vertical distance between wires in mm
    double horizontal_distance = 8.5; // horizontal distance between wires in mm
    double B =0.0;
    double A =0.0;
    int di =0;
    

    // Double_t ort = dzh->GetBinContent(dzh->FindBin(time));
    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    // printf("%lf",M_PI);
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
            if (wire_le[hit] % 2 == 0)
            {
                B=(vertical_distance + szi_distance) * 1.0;
                di = static_cast<int>(wire_le[hit]) - 9;
                A = horizontal_distance * static_cast<double>(di);
                double theta1 = atan(A/B);
                gradewinkelverteilung->Fill(theta1* 180.0/M_PI);
                // gradewinkelverteilung->Fill(A);
            }
            else
            {
                B=szi_distance * 1.0;
                di= static_cast<int>(wire_le[hit])-7;
                A=horizontal_distance*(static_cast<double>(di))+0.01;
                double theta1 = atan(A/B);
                ungradewinkelverteilung->Fill(theta1* 180.0/M_PI);
                // ungradewinkelverteilung->Fill(A);
            }
            double theta1 = atan(A/B);
            // wireCorrHisto1->Fill(ort1-ort2,ort1+ort2);
            // printf("%d \t %lf \n",di,A);
            winkelverteilung->Fill(theta1* 180.0/M_PI);
            // winkelverteilung->Fill(A);
            
        }         
        // if (Cut(ientry) < 0) continue;
    }
    // gStyle->SetPalette(kRainBow);
    // gStyle->SetOptStat(0);
    winkelverteilung->Draw();

    winkelverteilung->Fit("winkel","R");
    #ifdef UNGRADE
    winkel2->SetParameter(0, 1413.0);
    winkel2->SetParameter(1, szi_distance);
    ungradewinkelverteilung->Draw();
    ungradewinkelverteilung->Fit("winkel","R");
    #endif
    #ifdef GRADE
    winkel2->SetParameter(0, 1070.0);
    winkel2->SetParameter(1, vertical_distance+szi_distance);
    gradewinkelverteilung->Draw();
    gradewinkelverteilung->Fit("winkel","R");
    #endif
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