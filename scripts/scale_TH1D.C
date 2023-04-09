void scale_TH1D( std::string t_fileName, std::string t_histName_counts, std::string t_histName_dEdX ) {
  // Open the ROOT file containing the histogram
  TFile* file = TFile::Open(t_fileName.c_str(),"UPDATE");
  if (!file) {
    std::cerr << "Failed to open file!" << std::endl;
    return 1;
  }

  // Get the histogram from the file
  TH1D* counts = (TH1D*)(file->Get(t_histName_counts.c_str()));
  TH1D* dEdX   = (TH1D*)(file->Get(t_histName_dEdX.c_str()));
  if (!counts || !dEdX) {
    std::cerr << "Failed to retrieve histogram!" << std::endl;
    return 1;
  }

  // Loop over the bins and normalize their contents
  if(counts->GetNbinsX()!=dEdX->GetNbinsX()) {
    std::cerr << "Not same" << std::endl;
    return 1;
  }
  for (int i = 1; i <= counts->GetNbinsX(); ++i)
      if (counts->GetBinContent(i)!=0)
        dEdX->SetBinContent(i, dEdX->GetBinContent(i) / counts->GetBinContent(i) );

  // Close the file
  dEdX->Write("", TObject::kOverwrite);
  file->Close();

  return 0;
}