#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TRint.h>

void analysis::Loop()
{
  TH1D* driftTimesHisto = new TH1D("Driftzeiten", "Driftzeiten; Driftzeit [ns]; Trefferanzahl ", 251, -2.5/2., 250*2.5+2.5/2.);
  #ifndef WIRECORRSTART
    TH2 *wireCorrHisto1 = new TH2D("Drahtkorrelationen","Drahtkorrelationen;Draht nr; Draht nr; Trefferanzahl",48,0.5,48.5, 48, 0.5, 48.5);
  #endif
  TH2 *wireCorrHistoUnfiltered = new TH2D("Drahtkorrelationen des Rauschens","Drahtkorrelationen des Rauschens;Draht nr; Draht nr; Trefferanzahl",48,0.5,48.5, 48, 0.5, 48.5);
  TH2 *evenwireCorrHisto = new TH2D("Drahtkorrelationen grade","Drahtkorrelationen grade;grade Draht nr; Draht nr; Trefferanzahl",24,0.5,48.5, 48, 0.5, 48.5);
  TH2 *unevenwireCorrHisto = new TH2D("Drahtkorrelationen ungrade","Drahtkorrelationen ungrade;ungrade Draht nr; Draht nr; Trefferanzahl",24,0.5,48.5, 48, 0.5, 48.5);
  TH1D* neighborwireCorrHisto = new TH1D("Draht nr-differenz + 48", "Draht nr-differenz + 48; Differenz + 48; Trefferanzahl",48*2-1,0.5,95.5);
  TH1D* neighboreven = new TH1D("grade Draht nr-differenz + 48", " grade Draht nr-differenz + 48; Differenz + 48; Trefferanzahl",48*2-1,0.5,95.5);
  TH1D* neighboruneven = new TH1D("ungrade Draht nr-differenz + 48", " ungrade Draht nr-differenz + 48; Differenz + 48; Trefferanzahl",48*2-1,0.5,95.5);
  TH2 *neighboreven2d = new TH2D("wireCorrelation","wire correlations;Draht nr; Driftzeit; Entries",48*2-1,0.5,95.5, 251, -2.5/2., 250*2.5+2.5/2.);
  TH2 *neighboruneven2d = new TH2D("wireCorrelation","wire correlations;Draht nr; Driftzeit; Entries",48*2-1,0.5,95.5, 251, -2.5/2., 250*2.5+2.5/2.);
  #ifdef WIRECORRSTART
    TH2 *wireCorrHisto1 = new TH2D("Drahtkorrelationen","Drahtkorrelationen;Draht nr; Draht nr; Trefferanzahl",15,0.5,15.5, 15, 0.5, 15.5);
  #endif

  if (fChain == 0) return;  

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  neighborwireCorrHisto->Fill(48);
  neighboreven->Fill(48);
  neighboruneven->Fill(48);
  for (Long64_t jentry=0; jentry < nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    for(UInt_t hit=0; hit < nhits_le; hit++)
    {
      Double_t time=time_le[hit]*2.5; 
      driftTimesHisto->Fill(time);

      Double_t timeot=tot[hit]*2.5;   // time over total
      #ifndef UNFILTERED
      if (timeot < 100.0)       // filter out hits with time over total < 100 ns
      {
        continue;
      }
      #endif
      #ifdef WIRECORRSTART
        if (wire_le[hit] > 15)
        {
          continue;
        }
      #endif
      for (UInt_t j=0; j<nhits_le; j++)
      {
        if (wire_le[hit]==wire_le[j])
        {
          continue;
        }
        #ifdef UNFILTERED
          Double_t timeot2=tot[j]*2.5;
          if ((timeot2 < 100.0)&&(timeot < 100.0))
          {
            wireCorrHistoUnfiltered->Fill(wire_le[hit],wire_le[j]);
            continue;
          }
        #endif
        #ifdef WIRECORRSTART
          if (wire_le[j] > 15)
          {
            continue;
          }
        #endif
        wireCorrHisto1->Fill(wire_le[hit],wire_le[j]);
        neighborwireCorrHisto->Fill((wire_le[hit]-wire_le[j])+48);

        if (wire_le[j] % 2 == 0)
        {
          evenwireCorrHisto->Fill(wire_le[j],wire_le[hit]);
        }
        else
        {
          unevenwireCorrHisto->Fill(wire_le[j],wire_le[hit]);
        }
        if (wire_le[hit] % 2 == 0)
        {
          Double_t time_even = time_le[j]*2.5;
          neighboreven->Fill((wire_le[hit]-wire_le[j])+48);
          neighboreven2d->Fill((wire_le[hit]-wire_le[j])+48,time_even);
        }
        else
        {
          Double_t time_uneven = time_le[j]*2.5;
          neighboruneven->Fill((wire_le[hit]-wire_le[j])+48);
          neighboruneven2d->Fill((wire_le[hit]-wire_le[j])+48,time_uneven);
        }
      }
    }         
    // if (Cut(ientry) < 0) continue;
  }
  gStyle->SetPalette(kRainBow);
  wireCorrHisto1->SetStats(0);
  wireCorrHisto1->SetContour(1000);
  wireCorrHistoUnfiltered->SetStats(0);
  wireCorrHistoUnfiltered->SetContour(1000);
  evenwireCorrHisto->SetStats(0);
  evenwireCorrHisto->SetContour(1000);
  unevenwireCorrHisto->SetStats(0);
  unevenwireCorrHisto->SetContour(1000);
  driftTimesHisto->GetXaxis()->SetTitle("Zeit / ns");
  driftTimesHisto->GetYaxis()->SetTitle("Trefferanzahl");
  gStyle->SetOptStat(0);
  driftTimesHisto->Draw();
  #ifdef UNFILTERED
  wireCorrHistoUnfiltered->Draw("COLZ");
  #endif
  #ifdef WIRECORR
  wireCorrHisto1->Draw("COLZ");
  #endif
  #ifdef EVENWIRECORR
  evenwireCorrHisto->Draw("COLZ");
  #endif
  #ifdef UNEVENWIRECORR
  unevenwireCorrHisto->Draw("COLZ");
  #endif
  #ifdef NEIGHBORWIRECORR
  neighborwireCorrHisto->Draw();
  #endif
  #ifdef NEIGHBOREVEN
  neighboreven->Draw();
  #endif
  #ifdef NEIGHBORUNEVEN
  neighboruneven->Draw();
  #endif
  #ifdef NEIGHBOREVEN2D
  neighboreven2d->Draw("COLZ");
  #endif
  #ifdef NEIGHBORUNEVEN2D
  neighboruneven2d->Draw("COLZ");
  #endif
  #ifdef WIRECORRSTART
  // This is for the first 15 wires only
  wireCorrHisto1->Draw("COLZ");
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
  #ifdef WIRECORR
  // c1->Print("wireCorr.png");
  #endif
  #ifdef EVENWIRECORR
  // c1->Print("even.png");
  #endif
  #ifdef UNEVENWIRECORR
  // c1->Print("uneven.png");
  #endif
  #ifdef NEIGHBORWIRECORR
  // c1->Print("neighbor.png");
  #endif
  #ifdef NEIGHBOREVEN
  // c1->Print("neighboreven.png");
  #endif
  #ifdef NEIGHBORUNEVEN
  // c1->Print("neighboruneven.png");
  #endif
  #ifdef WIRECORRSTART
  // c1->Print("wireCorrStart.png");
  #endif
 
  app->Run(kTRUE);
}
