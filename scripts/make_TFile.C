void make_TFile( string t_fileName ) {
    string root = ".root";
    if (t_fileName.length() >= root.length() && t_fileName.compare(t_fileName.length() - root.length(), root.length(), root) == 0)
        t_fileName += root;
    else if (t_fileName.length() <= root.length() )
        t_fileName += root;
    TFile* file = new TFile(t_fileName.c_str(), "RECREATE");
    file->Close();
}