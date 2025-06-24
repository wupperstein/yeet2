{
    TCanvas *c1 = new TCanvas("c", "c", 800, 600);
    TFile::Open("drifttimesf.root");
    TH1* dzh = static_cast<TH1*>(gDirectory->FindObjectAny("Driftzeiten"));
    // Graph* obd = new TGraph();
    TH1D* odb= new TH1D("Orts-Driftzeit-Beziehung", "Orts-Driftzeit-Beziehung", 251, -2.5/2., 250*2.5+2.5/2.);
    Double_t sum = 0;
    for (UInt_t bin = 1; bin <= dzh->GetNbinsX(); ++bin)
    {
        sum += dzh->GetBinContent(bin);
        odb->SetBinContent(bin,sum);
    }
    odb->Scale(8.5/sum);
    odb->GetXaxis()->SetTitle("Driftzeit / ns");
    odb->GetYaxis()->SetTitle("Ort / mm");
    odb->Draw();

}