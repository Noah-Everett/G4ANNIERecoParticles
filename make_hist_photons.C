#include <vector>
#include <string>
#include <cmath>
using std::to_string;
    
int particle = 1; // 0 = muon, 1 = electron
double c = 2.998e10; // cm/s
double n_water = 1.333; //
double n_sci   = 1.500; //
double m = 105.7; // MeV/c^2
int nBins = 500;
int nParticles = 1000;

struct gamma {
    double Primary_E;
    double Primary_X;
    double Photon_theta;
    double Photon_E;
    int    CreationProcess; // == 24720245 for Cerenkov
};

double get_cherAngle( double n, double k )
{
  double b = sqrt( 1 - pow( m / ( k + m ), 2 ) );
  if( 1/n > b ){
    return 0;
  }
  double theta = acos( 1 / ( n * b ) );
  return theta * 180 / M_PI;
}

double fitFunction( double* x, double* par )
{
    return x[0]*par[0] + x[1]*par[0];
}

void addBoarder( TCanvas*& canvas )
{
    canvas->SetTopMargin   (0.17);
    canvas->SetBottomMargin(0.17);
    canvas->SetRightMargin (0.17);
    canvas->SetLeftMargin  (0.17);
    // canvas->SetWindowSize( 1000 + (1000-canvas->GetWw()), 1000 + (1000-canvas->GetWh()));
    // canvas->Resize();
    canvas->SetWindowSize(1200,1200);
}

void make_hist_photons( vector< string > files )
{
    gStyle->SetOptStat(0);

    TChain* tree = new TChain( "G4VtxRecoParticles;2" );
    for( string file : files )
        tree->Add( file.c_str() );

    vector< gamma > gammas;
    gamma temp;

    // Used to determine hist limits
    double max_Primary_E = -9999;
    double min_Primary_E =  9999;
    double max_Primary_X = -9999;
    double min_Primary_X =  9999;
    double max_Photon_theta = -9999;
    double min_Photon_theta =  9999;
    double max_Photon_E = -9999;
    double min_Photon_E =  9999;

    tree->SetBranchAddress( "Primary_E", &temp.Primary_E );
    tree->SetBranchAddress( "Primary_X", &temp.Primary_X );
    tree->SetBranchAddress( "Photon_theta", &temp.Photon_theta );
    tree->SetBranchAddress( "Photon_E", &temp.Photon_E );
    tree->SetBranchAddress( "CreationProcess_int", &temp.CreationProcess );

    for( Int_t i = 0; i < tree->GetEntries(); i++ ) {
        tree->GetEntry( i );
        temp.Photon_theta*=180/M_PI;
        gammas.push_back(temp);

        if( temp.Primary_E    > max_Primary_E                           ) max_Primary_E    = temp.Primary_E;
        if( temp.Primary_E    < min_Primary_E                           ) min_Primary_E    = temp.Primary_E;
        if( temp.Primary_X    > max_Primary_X                           ) max_Primary_X    = temp.Primary_X;
        if( temp.Primary_X    < min_Primary_X                           ) min_Primary_X    = temp.Primary_X;
        if( temp.Photon_theta > max_Photon_theta                        ) max_Photon_theta = temp.Photon_theta;
        if( temp.Photon_theta < min_Photon_theta                        ) min_Photon_theta = temp.Photon_theta;
        if( temp.Photon_E     > max_Photon_E && temp.Photon_E < 0.00001 ) max_Photon_E     = temp.Photon_E;
        if( temp.Photon_E     < min_Photon_E                            ) min_Photon_E     = temp.Photon_E;
    } 

    cout << "Primary E = [" << min_Primary_E << ", " << max_Primary_E << "]" << endl;
    cout << "Primary X = [" << min_Primary_X << ", " << max_Primary_X << "]" << endl;
    cout << "Photon theta = [" << min_Photon_theta << ", " << max_Photon_theta << "]" << endl;
    cout << "Photon E = [" << min_Photon_E << ", " << max_Photon_E << "]" << endl;

    ////////////////////////////////////////////////////
    //// c1 /// E vs Theta /// All /// Normailized /////
    ////////////////////////////////////////////////////
    TCanvas* canvas_c1 = new TCanvas( "c1", "", 1000, 1000 );
    canvas_c1->SetLogz();

    TH2D* hist_primaryEnergyVsPhotonThetaNormalized = new TH2D( "", "Primary Energy vs All Photon Angles Normalized;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      // if( gammas[ i ].CreationProcess == 24720245 )
        hist_primaryEnergyVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
    hist_primaryEnergyVsPhotonThetaNormalized->Scale(1/double(nParticles));
    hist_primaryEnergyVsPhotonThetaNormalized->Draw("COLZ");
    hist_primaryEnergyVsPhotonThetaNormalized->SaveAs("hist.root");
    addBoarder( canvas_c1 );
    
    double x_delta = 10;
    double x_start = 50;
    double x_stop  = 500;
    TGraph* graph = new TGraph( ( x_stop - x_start ) / int( x_delta ) );
    int i = 0;
    for( double x = x_start; x <= x_stop; x += x_delta )
        graph->SetPoint( i++, x, get_cherAngle( n_water, x ) );
    graph->SetMarkerStyle( 8 );
    graph->SetLineWidth  ( 3 );
    graph->SetLineColor  ( kRed );
    graph->SetMarkerColor( kRed );
    graph->Draw( "Same" );

    TLegend* legend = new TLegend();
    legend->AddEntry( graph, "#theta_{C} Analytical Prediction", "l" );
    legend->Draw("same");
    
    /////////////////////////////////////////////////////
    //// c2 /// E vs Theta /// All /// !Normailized /////
    /////////////////////////////////////////////////////
    TCanvas* canvas_c2 = new TCanvas( "c2", "", 1000, 1000 );
    canvas_c2->SetLogz();

    TH2D* hist_primaryEnergyVsPhotonThetaNotNormalized = new TH2D( "", "Primary Energy vs All Photon Angles;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      // if( gammas[ i ].CreationProcess == 24720245 )
        hist_primaryEnergyVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
    hist_primaryEnergyVsPhotonThetaNotNormalized->Draw("COLZ");
    addBoarder( canvas_c2 );
    graph->Draw( "Same" );
    legend->Draw("same");
    
    /////////////////////////////////////////
    //// c3 /// E vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    TCanvas* canvas_c3 = new TCanvas( "c3", "", 1000, 1000 );
    canvas_c3->SetLogz();
    TH2D* hist_primaryEnergyVsPhotonNotThetaC = new TH2D( "", "Primary Energy vs nonCerenkov Photon Angles;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      if( gammas[ i ].CreationProcess != 24720245 )
        hist_primaryEnergyVsPhotonNotThetaC->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
    hist_primaryEnergyVsPhotonNotThetaC->Scale(1/double(nParticles));
    hist_primaryEnergyVsPhotonNotThetaC->Draw("COLZ");
    addBoarder( canvas_c3 );

    //////////////////////////////////////////////////
    //// c4 /// X vs Theta /// All /// Normalized ////
    //////////////////////////////////////////////////
    TCanvas* canvas_c4 = new TCanvas( "c4", "", 1000, 1000 );
    canvas_c4->SetLogz();
    TH2D* hist_primaryPositionVsPhotonThetaNormalized = new TH2D( "", "Track Length vs All Photon Angles Normalized;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      hist_primaryPositionVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
    hist_primaryPositionVsPhotonThetaNormalized->Scale(1/double(nParticles));
    hist_primaryPositionVsPhotonThetaNormalized->Draw("COLZ");
    addBoarder( canvas_c4 );
    
    ///////////////////////////////////////////////////
    //// c4 /// X vs Theta /// All /// !Normalized ////
    ///////////////////////////////////////////////////
    TCanvas* canvas_c5 = new TCanvas( "c5", "", 1000, 1000 );
    canvas_c5->SetLogz();
    TH2D* hist_primaryPositionVsPhotonThetaNotNormalized = new TH2D( "", "Track Length vs All Photon Angles;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      hist_primaryPositionVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
    hist_primaryPositionVsPhotonThetaNotNormalized->Draw("COLZ");
    addBoarder( canvas_c5 );
    
    /////////////////////////////////////////
    //// c6 /// X vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    TCanvas* canvas_c6 = new TCanvas( "c6", "", 1000, 1000 );
    canvas_c6->SetLogz();
    TH2D* hist_primaryPositionVsPhotonNotThetaC = new TH2D( "", "Track Length vs nonCerenkov Photon Angles;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
    for( int i = 0; i < gammas.size(); i++ ) 
      if( gammas[ i ].CreationProcess != 24720245 )
        hist_primaryPositionVsPhotonNotThetaC->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
    hist_primaryPositionVsPhotonNotThetaC->Scale(1/double(nParticles));
    hist_primaryPositionVsPhotonNotThetaC->Draw("COLZ");
    addBoarder( canvas_c6 );
    
    ///////////////////////////////
    //// c7 /// X vs E /// All ////
    ///////////////////////////////
    TCanvas* canvas_c7 = new TCanvas( "c7", "", 1000, 1000 );
    canvas_c7->SetLogz();
    TH2D* hist_primaryPositionVsPhotonEnergyNormalized = new TH2D( "", "Track Length vs All Photon Energies Normalized;" "x [cm];" "E [eV]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_E, max_Photon_E );
    for( int i = 0; i < gammas.size(); i++ ) 
      hist_primaryPositionVsPhotonEnergyNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_E );
    hist_primaryPositionVsPhotonEnergyNormalized->Scale(1/double(nParticles));
    hist_primaryPositionVsPhotonEnergyNormalized->Draw("COLZ");
    addBoarder( canvas_c7 );
}