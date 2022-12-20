#include <vector>
#include <string>
#include <cmath>
using std::to_string;

int nBins = 100;
int nParticles = 100;
    
struct gamma {
    double Primary_X;
    double Photon_theta;
};

void make_dTdXHist( string file_in, string file_out )
{
    gStyle->SetOptStat(0);

    TChain* tree = new TChain( "G4ANNIERecoParticles;2" );
    tree->Add( file_in.c_str() );

    vector< gamma > gammas;
    gamma temp;

    // Used to determine hist limits
    double max_Primary_X = -9999   ;
    double min_Primary_X =  9999   ;
    double max_Photon_theta = -9999;
    double min_Photon_theta =  9999;

    tree->SetBranchAddress( "Primary_X"      , &temp.Primary_X       );
    tree->SetBranchAddress( "Photon_theta"   , &temp.Photon_theta    );
 
    for( Int_t i = 0; i < tree->GetEntries(); i++ ) {
        tree->GetEntry( i );
        gammas.push_back(temp);
        
        if( temp.Primary_X    > max_Primary_X                           ) max_Primary_X    = temp.Primary_X   ;
        if( temp.Primary_X    < min_Primary_X                           ) min_Primary_X    = temp.Primary_X   ;
        if( temp.Photon_theta > max_Photon_theta                        ) max_Photon_theta = temp.Photon_theta;
        if( temp.Photon_theta < min_Photon_theta                        ) min_Photon_theta = temp.Photon_theta;
    } 

    cout << "Primary X = [" << min_Primary_X << ", " << max_Primary_X << "]" << endl;
    cout << "Photon theta = [" << min_Photon_theta << ", " << max_Photon_theta << "]" << endl;

    // TCanvas* canvas_c1 = new TCanvas( "c1", "", 1000, 1000 );
    TH2D* hist_primaryEnergyVsPhotonThetaNormalized = new TH2D( "", "Primary Lepton Energy vs All Photon Angles Normalized;" "X [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryEnergyVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
    hist_primaryEnergyVsPhotonThetaNormalized->Scale(1/double(nParticles));
    // hist_primaryEnergyVsPhotonThetaNormalized->Draw("COLZ");
    cout << "Making `" << file_out << "`" << endl;
    hist_primaryEnergyVsPhotonThetaNormalized->SaveAs( file_out.c_str() );
}
