#include <vector>
#include <string>
#include <cmath>
using std::to_string;

int nBins = 100;
int nParticles = 1;
    
struct gamma {
    double Primary_E;
    double Primary_X;
    double Photon_theta;
    double Photon_E;
    int    CreationProcess; // == 24720245 for Cerenkov
};

void make_dTdXHist( vector< string > files )
{
    gStyle->SetOptStat(0);

    TChain* tree = new TChain( "G4ANNIERecoParticles;2" );
    for( string file : files )
      tree->Add( file.c_str() );

    vector< gamma > gammas;
    gamma temp;

    // Used to determine hist limits
    double max_Primary_E = -9999   ;
    double min_Primary_E =  9999   ;
    double max_Primary_X = -9999   ;
    double min_Primary_X =  9999   ;
    double max_Photon_theta = -9999;
    double min_Photon_theta =  9999;
    double max_Photon_E  = -9999   ;
    double min_Photon_E  =  9999   ;

    tree->SetBranchAddress( "Primary_E"      , &temp.Primary_E       );
    tree->SetBranchAddress( "Primary_X"      , &temp.Primary_X       );
    tree->SetBranchAddress( "Photon_theta"   , &temp.Photon_theta    );
    tree->SetBranchAddress( "Photon_E"       , &temp.Photon_E        );
    tree->SetBranchAddress( "CreationProcess", &temp.CreationProcess );
 
    for( Int_t i = 0; i < tree->GetEntries(); i++ ) {
        tree->GetEntry( i );
        temp.Photon_theta*=180/M_PI;
        gammas.push_back(temp);
        
        if( temp.Primary_E    > max_Primary_E                           ) max_Primary_E    = temp.Primary_E   ;
        if( temp.Primary_E    < min_Primary_E                           ) min_Primary_E    = temp.Primary_E   ;
        if( temp.Primary_X    > max_Primary_X                           ) max_Primary_X    = temp.Primary_X   ;
        if( temp.Primary_X    < min_Primary_X                           ) min_Primary_X    = temp.Primary_X   ;
        if( temp.Photon_theta > max_Photon_theta                        ) max_Photon_theta = temp.Photon_theta;
        if( temp.Photon_theta < min_Photon_theta                        ) min_Photon_theta = temp.Photon_theta;
        if( temp.Photon_E     > max_Photon_E && temp.Photon_E < 0.00001 ) max_Photon_E     = temp.Photon_E    ;
        if( temp.Photon_E     < min_Photon_E                            ) min_Photon_E     = temp.Photon_E    ;
    } 

    cout << "Primary E = [" << min_Primary_E << ", " << max_Primary_E << "]" << endl;
    cout << "Primary X = [" << min_Primary_X << ", " << max_Primary_X << "]" << endl;
    cout << "Photon theta = [" << min_Photon_theta << ", " << max_Photon_theta << "]" << endl;
    cout << "Photon E = [" << min_Photon_E << ", " << max_Photon_E << "]" << endl;

    TCanvas* canvas_c1 = new TCanvas( "c1", "", 1000, 1000 );
  
    TH2D* hist_primaryEnergyVsPhotonThetaNormalized = new TH2D( "", "Primary Lepton Energy vs All Photon Angles Normalized;" "X [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryEnergyVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
    hist_primaryEnergyVsPhotonThetaNormalized->Scale(1/double(nParticles));
    hist_primaryEnergyVsPhotonThetaNormalized->Draw("COLZ");
    hist_primaryEnergyVsPhotonThetaNormalized->SaveAs("hist.root");
}
