#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>

void analysis::Loop()
{
  TH1D* wireentriesHisto = new TH1D("Verteilung der Ansprecher", "Verteilung der Ansprecher;Draht nr; Trefferanzahl",48,0.5,48.5);
  TH2 *wireCorrHisto = new TH2D("Verteilung der Ansprecher-Driftzeiten","Verteilung der Ansprecher-Driftzeiten;Draht nr; Driftzeit [ns]; Trefferanzahl",48,0.5,48.5, 251, -2.5/2., 250*2.5+2.5/2.);
  

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
      wireCorrHisto->Fill(wire_le[hit],time);
      wireentriesHisto->Fill(wire_le[hit]);
    }
          
    // if (Cut(ientry) < 0) continue;
  }
  gStyle->SetPalette(kRainBow);
  wireCorrHisto->SetStats(0);
  wireCorrHisto->SetContour(1000);
  gStyle->SetOptStat(0);
  #ifdef WIRE_1D
  wireentriesHisto->Draw();
  #endif
  #ifdef WIRE_2D
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
  #ifdef WIRE_1D
  // c1->Print("wireentriesHisto.png");
  #endif
  #ifdef WIRE_2D
  // c1->Print("wireloc.png");
  #endif 
  app->Run(kTRUE);
}
