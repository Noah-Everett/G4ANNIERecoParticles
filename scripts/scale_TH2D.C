void scale_TH2D( std::string t_fileName, std::string t_histName_counts, std::string t_histName_energies ) {
  // Open the ROOT file containing the histogram
  TFile* file = TFile::Open(t_fileName.c_str(),"UPDATE");
  if (!file) {
    std::cerr << "Failed to open file!" << std::endl;
    return 1;
  }

  // Get the histogram from the file
  TH2D* counts = (TH2D*)(file->Get(t_histName_counts.c_str()));
  TH2D* energies = (TH2D*)(file->Get(t_histName_energies.c_str()));
  if (!counts || !energies) {
    std::cerr << "Failed to retrieve histogram!" << std::endl;
    return 1;
  }

  // Loop over the bins and normalize their contents
  if(energies->GetNbinsX()!=counts->GetNbinsX() || energies->GetNbinsY()!=counts->GetNbinsY()) {
    std::cerr << "Not same" << std::endl;
    return 1;
  }
  for (int i = 1; i <= energies->GetNbinsX(); ++i)
    for (int j = 1; j <= energies->GetNbinsY(); ++j)
      if (counts->GetBinContent(i, j)!=0)
        energies->SetBinContent(i, j, energies->GetBinContent(i, j) / counts->GetBinContent(i, j) );

  // Close the file
  energies->Write("", TObject::kOverwrite);
  file->Close();

  return 0;
}