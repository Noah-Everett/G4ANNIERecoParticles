#include <vector>
#include <string>
using std::to_string;

struct gamma {
    double Primary_E;
    double Primary_X;
    double Photon_theta;
    double Photon_E;
};

double fct( double x, double* par ) {
    return x * par[ 0 ];
}

void make_hist_E_theta( vector< string > files )
{
    gROOT->ForceStyle();
    // gStyle->SetOptStat(0);

    TCanvas* canvas = new TCanvas( "c1", "", 1000, 1000 );
    // canvas->SetLogy();
    canvas->SetLogz();

    TChain* tree = new TChain( "G4VtxRecoParticles;2" );
    for( string file : files )
        tree->Add( file.c_str() );
    
    vector< gamma > gammas;
    gamma temp;

    // Used to determine hist limits
    double max_Primary_E = -1;
    double min_Primary_E = -1;
    double max_Primary_X = 1;
    double min_Primary_X = 1;
    double max_Photon_theta = -1;
    double min_Photon_theta = -1;
    double min_Photon_E = 1;
    double max_Photon_E = 1;

    tree->SetBranchAddress( "Primary_E", &temp.Primary_E );
    tree->SetBranchAddress( "Primary_X", &temp.Primary_X );
    tree->SetBranchAddress( "Photon_theta", &temp.Photon_theta );
    tree->SetBranchAddress( "Photon_E", &temp.Photon_E );

    for( Int_t i = 0; i < tree->GetEntries(); i++ ) {
        tree->GetEntry( i );
        temp.Photon_theta*=180/M_PI;
        gammas.push_back(temp);

        if( temp.Primary_E    > max_Primary_E    ) max_Primary_E    = temp.Primary_E;
        if( temp.Primary_E    < min_Primary_E    ) min_Primary_E    = temp.Primary_E;
        if( temp.Primary_X    > max_Primary_X    ) max_Primary_X    = temp.Primary_X;
        if( temp.Primary_X    < min_Primary_X    ) min_Primary_X    = temp.Primary_X;
        if( temp.Photon_theta > max_Photon_theta ) max_Photon_theta = temp.Photon_theta;
        if( temp.Photon_theta < min_Photon_theta ) min_Photon_theta = temp.Photon_theta;
        if( temp.Photon_E     > max_Photon_E     ) max_Photon_E     = temp.Photon_E;
        if( temp.Photon_E     < min_Photon_E     ) min_Photon_E     = temp.Photon_E;
    } 

    TH2D* hist = new TH2D( "", ";" "E [MeV];" "#theta_{C} [Deg]", 450, 50, 500, 100, 0, 60 );
    for( int i = 0; i < gammas.size(); i++ ) hist->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );

    canvas->SetRightMargin(0.11);
    hist->Draw("COLZ");
}