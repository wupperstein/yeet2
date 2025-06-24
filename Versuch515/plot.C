{
	UInt_t messungen = 4;
	TString histogrammName = "Driftzeiten";
	TString dateien[4] = {"2800Vthr90ddc1E.root", "2800Vthr10ddc23.root", "2700Vthr10ddc23.root", "2800Vthr90ddc23.root"};
	TString titel[4] = {"2800V THR 90 DDC 1E", "2800V THR 10 DDC 23", "2700V THR 10 DDC 23", "2800V THR 90 DDC 23"};

	TLegend* leg = new TLegend(0.6, 0.5, 0.9, 0.7);
	leg->SetHeader("Spannungen");

	Bool_t first=true;
	UInt_t num = messungen;
	do {
		--num;
		TFile::Open(dateien[num]);
		TH1* plot = static_cast<TH1*>(gDirectory->FindObjectAny(histogrammName));
		plot->SetLineColor(num+1);
		if (first) {
			plot->Draw();
			first=false;
		} else {
			plot->Draw("same");
		}
		leg->AddEntry(plot, titel[num], "lep");
	} while (num != 0);

	leg->Draw("SAME");
}
