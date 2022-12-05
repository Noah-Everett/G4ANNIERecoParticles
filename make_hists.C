#include <vector>
#include <string>
#include <cmath>
using std::to_string;
    
int particle = 1; // 0 = muon, 1 = electron
double c = 2.998e10; // cm/s
double c2 = pow( c, 2 ); // (cm/s)^2
double n_water = 1.333; //
double n_sci   = 1.500; //
double m_mu = 105.7; // MeV/c^2
double m_e = 0.511; // MeV/c^2
double m = m_e;
int nBins = 500;
int nParticles = 100;

struct gamma {
    double Primary_E;
    double Primary_X;
    double Photon_theta;
    double Photon_E;
    int    CreationProcess; // == 24720245 for Cerenkov
};

struct step {
    double X;
    double dX;
    double E;
    double dE;
    double dEdX;
};

double get_cherAngle( double m, double n, double k )
{
  double b = sqrt( 1 - pow( m / ( k + m*c2 ), 2 ) );
  if( 1 / n > b ){
    return -99999;
    cout << k << endl;
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
    canvas->SetWindowSize  (1200,1200);
}

void make_hists( vector< string > files )
{
    gStyle->SetOptStat(0);

    TChain* tree_dEdX   = new TChain( "G4VtxRecoParticles;1" );
    TChain* tree_gammas = new TChain( "G4VtxRecoParticles;2" );
    for( string file : files ) {
      tree_dEdX  ->Add( file.c_str() );
      tree_gammas->Add( file.c_str() );
    }

    bool present_steps  = ( tree_dEdX  ->GetEntries() == 0 ) ? false : true;
    bool present_gammas = ( tree_gammas->GetEntries() == 0 ) ? false : true;

    vector< step >  steps;
    vector< gamma > gammas;
    step  temp_step;
    gamma temp_gamma;

    // Used to determine hist limits
    double max_X         = -9999   ;
    double min_X         =  9999   ;
    double max_dEdX      = -9999   ;
    double min_dEdX      =  9999   ;
    double max_E         = -9999   ;
    double min_E         =  9999   ;
    double max_Primary_E = -9999   ;
    double min_Primary_E =  9999   ;
    double max_Primary_X = -9999   ;
    double min_Primary_X =  9999   ;
    double max_Photon_theta = -9999;
    double min_Photon_theta =  9999;
    double max_Photon_E  = -9999   ;
    double min_Photon_E  =  9999   ;

    tree_dEdX  ->SetBranchAddress( "X",                   &temp_step.X                );
    tree_dEdX  ->SetBranchAddress( "dX",                  &temp_step.dX               );
    tree_dEdX  ->SetBranchAddress( "E",                   &temp_step.E                );
    tree_dEdX  ->SetBranchAddress( "dE",                  &temp_step.dE               );
    tree_dEdX  ->SetBranchAddress( "dEdX",                &temp_step.dEdX             );
    tree_gammas->SetBranchAddress( "Primary_E",           &temp_gamma.Primary_E       );
    tree_gammas->SetBranchAddress( "Primary_X",           &temp_gamma.Primary_X       );
    tree_gammas->SetBranchAddress( "Photon_theta",        &temp_gamma.Photon_theta    );
    tree_gammas->SetBranchAddress( "Photon_E",            &temp_gamma.Photon_E        );
    tree_gammas->SetBranchAddress( "CreationProcess_int", &temp_gamma.CreationProcess );
 
    for( Int_t i = 0; i < tree_dEdX->GetEntries(); i++ ) {
        tree_dEdX->GetEntry( i );
        steps.push_back( temp_step );

        if( temp_step.X    > max_X                             ) max_X    = temp_step.X   ;
        if( temp_step.X    < min_X                             ) min_X    = temp_step.X   ;
        if( temp_step.dEdX > max_dEdX                          ) max_dEdX = temp_step.dEdX;
        if( temp_step.dEdX < min_dEdX && temp_step.dEdX > -20  ) min_dEdX = temp_step.dEdX;
        if( temp_step.E    > max_E                             ) max_E    = temp_step.E   ;
        if( temp_step.E    < min_E                             ) min_E    = temp_step.E   ;
    } 
    for( Int_t i = 0; i < tree_gammas->GetEntries(); i++ ) {
        tree_gammas->GetEntry( i );
        temp_gamma.Photon_theta*=180/M_PI;
        gammas.push_back(temp_gamma);
        
        if( temp_gamma.Primary_E    > max_Primary_E                                 ) max_Primary_E    = temp_gamma.Primary_E   ;
        if( temp_gamma.Primary_E    < min_Primary_E                                 ) min_Primary_E    = temp_gamma.Primary_E   ;
        if( temp_gamma.Primary_X    > max_Primary_X                                 ) max_Primary_X    = temp_gamma.Primary_X   ;
        if( temp_gamma.Primary_X    < min_Primary_X                                 ) min_Primary_X    = temp_gamma.Primary_X   ;
        if( temp_gamma.Photon_theta > max_Photon_theta                              ) max_Photon_theta = temp_gamma.Photon_theta;
        if( temp_gamma.Photon_theta < min_Photon_theta                              ) min_Photon_theta = temp_gamma.Photon_theta;
        if( temp_gamma.Photon_E     > max_Photon_E && temp_gamma.Photon_E < 0.00001 ) max_Photon_E     = temp_gamma.Photon_E    ;
        if( temp_gamma.Photon_E     < min_Photon_E                                  ) min_Photon_E     = temp_gamma.Photon_E    ;
    } 

    cout << "Primary E = [" << min_Primary_E << ", " << max_Primary_E << "]" << endl;
    cout << "Primary X = [" << min_Primary_X << ", " << max_Primary_X << "]" << endl;
    cout << "Photon theta = [" << min_Photon_theta << ", " << max_Photon_theta << "]" << endl;
    cout << "Photon E = [" << min_Photon_E << ", " << max_Photon_E << "]" << endl;
    cout << "X = [" << min_X << ", " << max_X << "]" << endl;
    cout << "dEdX = [" << min_dEdX << ", " << max_dEdX << "]" << endl;
    cout << "E = [" << min_E << ", " << max_E << "]" << endl;

    ////////////////////////////////////////////////////
    //// c1 /// E vs Theta /// All /// Normailized /////
    ////////////////////////////////////////////////////
    TGraph* graph_cher = new TGraph( 10 / 0.01 + max_Primary_E / 10 - 1 );
    TLegend* legend_cher = new TLegend();
    if( present_gammas ){
      TCanvas* canvas_c1 = new TCanvas( "c1", "", 1000, 1000 );
      canvas_c1->SetLogz();

      TH2D* hist_primaryEnergyVsPhotonThetaNormalized = new TH2D( "", "Primary Lepton Energy vs All Photon Angles Normalized;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        // if( gammas[ i ].CreationProcess == 24720245 )
          hist_primaryEnergyVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
      hist_primaryEnergyVsPhotonThetaNormalized->Scale(1/double(nParticles));
      hist_primaryEnergyVsPhotonThetaNormalized->Draw("COLZ");
      hist_primaryEnergyVsPhotonThetaNormalized->SaveAs("hist.root");
      addBoarder( canvas_c1 );
      
      int i = 0;
      double point;
      for( double x = 0; x < 5; x += 0.01 ){
          point = get_cherAngle( m, n_water, x );
          if( point >= 0 ) graph_cher->SetPoint( i++, x, point );
          cout << point << " " << x << endl;
      }
      for( double x = 10; x <= max_Primary_E; x += 10 ){
          point = get_cherAngle( m, n_water, x );
          if( point >= 0 ) graph_cher->SetPoint( i++, x, point );
          cout << point << " " << x << endl;
      }
      graph_cher->SetMarkerStyle( 8 );
      graph_cher->SetLineWidth  ( 3 );
      graph_cher->SetLineColor  ( kRed );
      graph_cher->SetMarkerColor( kRed );
      graph_cher->Draw( "Same" );

      legend_cher->AddEntry( graph_cher, "#theta_{C} Analytical Prediction", "l" );
      legend_cher->Draw("same");
    }
    
    /////////////////////////////////////////////////////
    //// c2 /// E vs Theta /// All /// !Normailized /////
    /////////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c2 = new TCanvas( "c2", "", 1000, 1000 );
      canvas_c2->SetLogz();

      TH2D* hist_primaryEnergyVsPhotonThetaNotNormalized = new TH2D( "", "Primary Lepton Energy vs All Photon Angles;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
          hist_primaryEnergyVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
      hist_primaryEnergyVsPhotonThetaNotNormalized->Draw("COLZ");
      addBoarder( canvas_c2 );

      graph_cher->SetMarkerStyle( 8 );
      graph_cher->SetLineWidth  ( 3 );
      graph_cher->SetLineColor  ( kRed );
      graph_cher->SetMarkerColor( kRed );
      graph_cher->Draw( "Same" );
      legend_cher->Draw("same");
    }
    
    /////////////////////////////////////////
    //// c3 /// E vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c3 = new TCanvas( "c3", "", 1000, 1000 );
      canvas_c3->SetLogz();
      TH2D* hist_primaryEnergyVsPhotonNotThetaC = new TH2D( "", "Primary Lepton Energy vs nonCerenkov Photon Angles;" "E [MeV];" "#theta [Deg]", nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess != 24720245 )
          hist_primaryEnergyVsPhotonNotThetaC->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
      hist_primaryEnergyVsPhotonNotThetaC->Scale(1/double(nParticles));
      hist_primaryEnergyVsPhotonNotThetaC->Draw("COLZ");
      addBoarder( canvas_c3 );
    }

    //////////////////////////////////////////////////
    //// c4 /// X vs Theta /// All /// Normalized ////
    //////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c4 = new TCanvas( "c4", "", 1000, 1000 );
      canvas_c4->SetLogz();
      TH2D* hist_primaryPositionVsPhotonThetaNormalized = new TH2D( "", "Primary Lepton Track Length vs All Photon Angles Normalized;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
      hist_primaryPositionVsPhotonThetaNormalized->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonThetaNormalized->Draw("COLZ");
      addBoarder( canvas_c4 );
    }

    ///////////////////////////////////////////////////////
    //// c5 /// X vs Theta /// Cerenkov /// Normalized ////
    ///////////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c5 = new TCanvas( "c5", "", 1000, 1000 );
      canvas_c5->SetLogz();
      TH2D* hist_primaryPositionVsPhotonThetaCNormalized = new TH2D( "", "Primary Lepton Track Length vs Cerenkov Photon Angles Normalized;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess == 24720245 )
          hist_primaryPositionVsPhotonThetaCNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
      hist_primaryPositionVsPhotonThetaCNormalized->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonThetaCNormalized->Draw("COLZ");
      addBoarder( canvas_c5 );
    }
    
    ///////////////////////////////////////////////////
    //// c6 /// X vs Theta /// All /// !Normalized ////
    ///////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c6 = new TCanvas( "c6", "", 1000, 1000 );
      canvas_c6->SetLogz();
      TH2D* hist_primaryPositionVsPhotonThetaNotNormalized = new TH2D( "", "Primary Lepton Track Length vs All Photon Angles;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
      hist_primaryPositionVsPhotonThetaNotNormalized->Draw("COLZ");
      addBoarder( canvas_c6 );
    }
    
    /////////////////////////////////////////
    //// c7 /// X vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c7 = new TCanvas( "c7", "", 1000, 1000 );
      canvas_c7->SetLogz();
      TH2D* hist_primaryPositionVsPhotonNotThetaC = new TH2D( "", "Primary Lepton Track Length vs nonCerenkov Photon Angles;" "x [cm];" "#theta [Deg]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess != 24720245 )
          hist_primaryPositionVsPhotonNotThetaC->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_theta );
      hist_primaryPositionVsPhotonNotThetaC->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonNotThetaC->Draw("COLZ");
      addBoarder( canvas_c7 );
    }
    
    ///////////////////////////////
    //// c8 /// X vs E /// All ////
    ///////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c8 = new TCanvas( "c8", "", 1000, 1000 );
      canvas_c8->SetLogz();
      TH2D* hist_primaryPositionVsPhotonEnergyNormalized = new TH2D( "", "Primary Lepton Track Length vs All Photon Energies Normalized;" "x [cm];" "E [MeV]", nBins, min_Primary_X, max_Primary_X, nBins, min_Photon_E, max_Photon_E );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonEnergyNormalized->Fill( gammas[ i ].Primary_X, gammas[ i ].Photon_E );
      hist_primaryPositionVsPhotonEnergyNormalized->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonEnergyNormalized->Draw("COLZ");
      addBoarder( canvas_c8 );
    }
    
    //////////////////////////
    //// c9 /// X vs dEdX ////
    //////////////////////////
    if( present_steps ){
      TCanvas* canvas_c9 = new TCanvas( "c9", "", 1000, 1000 );
      canvas_c9->SetLogz();
      TH2D* hist_XVsdEdX = new TH2D( "", "Primary Lepton Track Length vs dEdX;" "x [cm];" "dEdX [MeV/cm]", nBins, min_X, max_X, nBins, min_dEdX, max_dEdX );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_XVsdEdX->Fill( steps[ i ].X, steps[ i ].dEdX );
      hist_XVsdEdX->Draw("COLZ");
      addBoarder( canvas_c9 );
    }
    
    //////////////////////////
    //// c10 /// X vs dEdX ////
    //////////////////////////
    if( present_steps ){
      TCanvas* canvas_c10 = new TCanvas( "c10", "", 1000, 1000 );
      canvas_c10->SetLogz();
      TH2D* hist_EVsdEdX = new TH2D( "", "Primary Lepton Energy vs dEdX;" "E [MeV];" "dEdX [MeV/cm]", nBins, min_E, max_E, nBins, min_dEdX, max_dEdX );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_EVsdEdX->Fill( steps[ i ].E, steps[ i ].dEdX );
      hist_EVsdEdX->Draw("COLZ");
      addBoarder( canvas_c10 );
    }
    
    ////////////////////////////////////////////////////////
    //// c11 /// X vs Theta /// Cerenkov /// Normalized ////
    ////////////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c11 = new TCanvas( "c11", "", 1000, 1000 );
      //canvas_c11->SetLogz();
      TH2D* hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat = new TH2D( "", "Cerenkov Photon Angles Normalized vs Primary Lepton Track Length;" "cos(#theta);" "x [cm]", nBins/2, 0, 1, nBins/2/2/2, 0, 133 );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess == 24720245 )
          hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Fill( cos(gammas[ i ].Photon_theta/180*M_PI), gammas[ i ].Primary_X );
      hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Draw("COLZ");
      addBoarder( canvas_c11 );
    }
    
    ///////////////////////////
    //// c12 /// X vs dEdX ////
    ///////////////////////////
    if( present_steps ){
      TCanvas* canvas_c12 = new TCanvas( "c12", "", 1000, 1000 );
      TH2D* hist_XVsdEdX_normalized = new TH2D( "", "Primary Lepton Track Length vs dEdX Normalized;" "x [cm];" "dEdX [MeV/cm]", nBins, min_X, max_X, nBins, min_dEdX, max_dEdX );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_XVsdEdX_normalized->Fill( steps[ i ].X, steps[ i ].dEdX );
      hist_XVsdEdX_normalized->Draw("COLZ");
      hist_XVsdEdX_normalized->Scale(1/double(nParticles));
      addBoarder( canvas_c12 );
    }
    
    ///////////////////////////
    //// c13 /// E vs dEdX ////
    ///////////////////////////
    if( present_steps ){
      TCanvas* canvas_c13 = new TCanvas( "c13", "", 1000, 1000 );
      TH2D* hist_EVsdEdX_normalized = new TH2D( "", "Primary Lepton Energy vs dEdX Normalized;" "E [cm];" "dEdX [MeV/cm]", nBins, min_E, max_E, nBins, min_dEdX, max_dEdX );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_EVsdEdX_normalized->Fill( steps[ i ].E, steps[ i ].dEdX );
      hist_EVsdEdX_normalized->Draw("COLZ");
      hist_EVsdEdX_normalized->Scale(1/double(nParticles));
      addBoarder( canvas_c13 );
    }
}
