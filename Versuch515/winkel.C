{
    TCanvas *c1 = new TCanvas("c", "c", 800, 600);
    TFile::Open("odb.root");
    TH1* dzh = static_cast<TH1*>(gDirectory->FindObjectAny("Orts-Driftzeit-Beziehung"));
    Double_t time=200.0;
    Double_t ort = dzh->GetBinContent(dzh->FindBin(time));

}