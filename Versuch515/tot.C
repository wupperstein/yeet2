#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>

void analysis::Loop()
{
  TH1D* totHisto = new TH1D("Time over Threshold", "Time over Threshold;Time over Threshold;Trefferanzahl", 251, -2.5/2., 250*2.5+2.5/2.);
  TH2 *totdriftHisto = new TH2D("Time over Threshold-Driftzeit","Time over Threshold-Driftzeit; Driftzeit [ns];Time over Threshold; Trefferanzahl", 126, -2.5/2., 250*2.5+2.5/2., 126, -2.5/2., 250*2.5+2.5/2.);
  TH1D* totHistofiltered = new TH1D("Time over Threshold nach Filtern", "Time over Threshold nach Filtern;Time over Threshold;Trefferanzahl", 251, -2.5/2., 250*2.5+2.5/2.);
  TH2 *totdriftHistofiltered = new TH2D("Time over Threshold-Driftzeit nach Filtern","Time over Threshold-Driftzeit nach Filtern; Driftzeit [ns];Time over Threshold; Trefferanzahl", 126, -2.5/2., 250*2.5+2.5/2., 126, -2.5/2., 250*2.5+2.5/2.);
  TH2 *wireCorrHisto = new TH2D("Verteilung der Ansprecher nach Filtern","Verteilung der Ansprecher nach Filtern;Draht nr; Driftzeit [ns]; Trefferanzahl",48,0.5,48.5, 126, -2.5/2., 250*2.5+2.5/2.);
  TH1D* driftTimesHisto = new TH1D("Driftzeiten nach Filtern", "Driftzeiten nach Filtern; Driftzeit [ns]; Trefferanzahl ", 251, -2.5/2., 250*2.5+2.5/2.);

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
      Double_t time=time_le[hit]*2.5;
      Double_t timeot=tot[hit]*2.5;
      totdriftHisto->Fill(time,timeot);
      totHisto->Fill(timeot);
      if (timeot < 100.0)
      {
        continue;
      }
      totdriftHistofiltered->Fill(time,timeot);
      totHistofiltered->Fill(timeot);
      wireCorrHisto->Fill(wire_le[hit],time);
      driftTimesHisto->Fill(time);
    }
          
    // if (Cut(ientry) < 0) continue;
  }
  gStyle->SetPalette(kRainBow);
  totdriftHisto->SetStats(0);
  totdriftHistofiltered->SetContour(1000);
  totdriftHistofiltered->SetStats(0);
  totdriftHisto->SetContour(1000);
  wireCorrHisto->SetStats(0);
  wireCorrHisto->SetContour(1000);
  gStyle->SetOptStat(0);
  // driftTimesHisto->GetXaxis()->SetTitle("Zeit / ns");
  // driftTimesHisto->GetYaxis()->SetTitle("Trefferanzahl");
driftTimesHisto->Draw();
  #ifdef TOT_1D
    totHisto->Draw();
    #ifdef FILTERED
        totHistofiltered->Draw();
    #endif
  #endif
  #ifdef TOT_2D
    totdriftHisto->Draw("COLZ");
    #ifdef FILTERED
        totdriftHistofiltered->Draw("COLZ");
    #endif
  #endif
  #ifdef WIRECORR
    wireCorrHisto->Draw("COLZ");
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
  #ifdef TOT_1D
    // c1->Print("tot1d.png");
    #ifdef FILTERED
        // c1->Print("tot1dfiltered.png");
    #endif
  #endif
  #ifdef TOT_2D
    // c1->Print("tot2d.png");
    #ifdef FILTERED
        // c1->Print("tot2dfiltered.png");
    #endif
  #endif 
    #ifdef WIRECORR
        // c1->Print("wiredriftfiltered.png");
    #endif
  app->Run(kTRUE);
}