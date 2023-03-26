void addToTFile_TH2D( string t_fileName_output, string t_fileName_input, string t_histName ) {
    TFile* in  = TFile::Open( t_fileName_input .c_str() );
    if(!in) {
        cout << "in tfile ptr was not allocated" << endl;
        return 1;
    }
    TFile* out = TFile::Open( t_fileName_output.c_str(), "UPDATE" );
    if(!out) {
        cout << "out tfile ptr was not allocated" << endl;
        return 1;
    }

    // Get the histogram from the second file
    TH2D* hist = (TH2D*)in->Get(t_histName.c_str());
    if(!hist) {
        cout << "hist ptr was not allocated" << endl;
        return 1;
    }

    // Add the histogram to the first file
    hist->Write();

    // Clean up
    in->Close();
    out->Close();
}