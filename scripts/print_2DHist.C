void print_2DHist( std::string t_fileName, std::string t_histName ) {
  // Open the ROOT file containing the histogram
  TFile* file = TFile::Open(t_fileName.c_str());
  if (!file) {
    std::cerr << "Failed to open file!" << std::endl;
    return 1;
  }

  // Get the histogram from the file
  TH2* hist = (TH2*)(file->Get(t_histName.c_str()));
  if (!hist) {
    std::cerr << "Failed to retrieve histogram!" << std::endl;
    return 1;
  }

  // Loop over the bins and print out their contents
  for (int i = 1; i <= hist->GetNbinsX(); ++i)
    for (int j = 1; j <= hist->GetNbinsY(); ++j)
      if (hist->GetBinContent(i, j)!=0)
        std::cout << "(" << i << ", " << j << "): " << hist->GetBinContent(i, j) << endl;

  // Close the file
  file->Close();

  return 0;
}