#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <ostream>
using std::to_string;
using std::string;
using std::map;
using std::cout;
using std::endl;

const double c      { 2.998e10 }; // cm/s
const double c2     { pow( c, 2 ) }; // (cm/s)^2
const double n_water{ 1.333 }; //
const double n_sci  { 1.500 }; //
const double m_mu   { 105.7 }; // MeV/c^2
const double m_e    { 0.511 }; // MeV/c^2

int particle  { 0 }; // 0 = muon, 1 = electron
int nBins     { 200 };
int nParticles{ 1000 };
double n      { n_water };
double m{ ( particle == 0 ) ? m_mu : m_e };
string particle_string{ ( particle == 0 ) ? "Muon" : "Electron" };


const map< string, int > map_process  = { { "Cerenkov"            , 0 },
                                          { "eBrem"               , 1 },
                                          { "muMinusCaptureAtRest", 2 },
                                          { "neutronInelastic"    , 3 },
                                          { "nCapture"            , 4 } };
const map< string, int > map_particle = { { "mu"                  , 0 },
                                          { "e"                   , 1 },
                                          { "generic"             , 2 },
                                          { "static"              , 3 },
                                          { "nucleon"             , 4 } };
    
struct gamma {
    double Primary_E;
    double Primary_S;
    double Photon_theta;
    double Photon_E;
    int    CreationProcess;
    int    ParentParticle;
    double Parent_X;
    double Parent_Y;
    double Parent_Z;
    int    IsFirstStep;
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
  double b = sqrt( 1 - pow( m / ( k + m ), 2 ) );
  if( 1 / n > b ){
    return -99999;
    cout << "Under Cerenkov limit. k = " << k << endl;
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

void redrawBorder()
{
   gPad->Update();
   gPad->RedrawAxis();
   TLine l;
   l.DrawLine(gPad->GetUxmin(), gPad->GetUymax(), gPad->GetUxmax(), gPad->GetUymax());
   l.DrawLine(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax());
}

void make_hists( vector< string > files )
{
    cout << "#========== SETTINGS ==========#" << endl;
    cout << "  Using mass: " << m << endl;
    cout << "  Using n: " << n << endl;
    cout << "  Using nBins: " << nBins << endl;
    cout << "  Using nParticles: " << nParticles << endl;
    cout << "#==============================#" << endl;
    cout << endl;

    gStyle->SetOptStat(0);
    // Int_t palette[5];
    // palette[1] = 20;
    // palette[2] = 23;
    // palette[3] = 30;
    // palette[4] = 32;
    // palette[5] = 0;
    // gStyle->SetPalette(5,palette);
    // gStyle->SetPalette( 57 ); //55
                              
    const Int_t NRGBs = 5;
    const Int_t NCont = 50;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    Int_t colors[ NCont + 2 ];
    for( int i{ 0 }; i < NCont; i++ )
        colors[ i + 1 ] = gStyle->GetColorPalette( i );
    colors[ 0         ] = kWhite;
    colors[ NCont + 1 ] = kBlack;
    gStyle->SetNumberContours( NCont + 2 );
    gStyle->SetPalette( NCont + 2, colors );


    //TChain* tree_dEdX   = new TChain( "G4VtxRecoParticles;1" );
    //TChain* tree_gammas = new TChain( "G4VtxRecoParticles;2" );
    TChain* tree_dEdX   = new TChain( "G4ANNIERecoParticles;1" );
    TChain* tree_gammas = new TChain( "G4ANNIERecoParticles;2" );
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
    string title;

    // Used to determine hist limits
    double max_X           { -9999 };
    double min_X           {  9999 };
    double max_dEdX        { -9999 };
    double min_dEdX        {  9999 };
    double max_E           { -9999 };
    double min_E           {  9999 };
    double max_Primary_E   { -9999 };
    double min_Primary_E   {  9999 };
    double max_Primary_S   { -9999 };
    double min_Primary_S   {  9999 };
    double max_Photon_theta{ -9999 };
    double min_Photon_theta{  9999 };
    double max_Photon_E    { -9999 };
    double min_Photon_E    {  9999 };
    double max_Parent_X    { -9999 };
    double min_Parent_X    {  9999 };
    double max_Parent_Y    { -9999 };
    double min_Parent_Y    {  9999 };
    double max_Parent_Z    { -9999 };
    double min_Parent_Z    {  9999 };

    tree_dEdX  ->SetBranchAddress( "X"              , &temp_step.X                );
    tree_dEdX  ->SetBranchAddress( "dX"             , &temp_step.dX               );
    tree_dEdX  ->SetBranchAddress( "E"              , &temp_step.E                );
    tree_dEdX  ->SetBranchAddress( "dE"             , &temp_step.dE               );
    tree_dEdX  ->SetBranchAddress( "dEdX"           , &temp_step.dEdX             );
    tree_gammas->SetBranchAddress( "Primary_E"      , &temp_gamma.Primary_E       );
    tree_gammas->SetBranchAddress( "Primary_S"      , &temp_gamma.Primary_S       );
    tree_gammas->SetBranchAddress( "Photon_theta"   , &temp_gamma.Photon_theta    );
    tree_gammas->SetBranchAddress( "Photon_E"       , &temp_gamma.Photon_E        );
    tree_gammas->SetBranchAddress( "CreationProcess", &temp_gamma.CreationProcess );
    tree_gammas->SetBranchAddress( "ParentParticle" , &temp_gamma.ParentParticle  );
    tree_gammas->SetBranchAddress( "Parent_X"       , &temp_gamma.Parent_X       );
    tree_gammas->SetBranchAddress( "Parent_Y"       , &temp_gamma.Parent_Y       );
    tree_gammas->SetBranchAddress( "Parent_Z"       , &temp_gamma.Parent_Z       );
    tree_gammas->SetBranchAddress( "IsFirstStep"    , &temp_gamma.IsFirstStep    );
 
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
        // temp_gamma.Photon_theta*=180/M_PI;
        gammas.push_back(temp_gamma);
        
        if( temp_gamma.Primary_E    > max_Primary_E                                 ) max_Primary_E    = temp_gamma.Primary_E   ;
        if( temp_gamma.Primary_E    < min_Primary_E                                 ) min_Primary_E    = temp_gamma.Primary_E   ;
        if( temp_gamma.Primary_S    > max_Primary_S                                 ) max_Primary_S    = temp_gamma.Primary_S   ;
        if( temp_gamma.Primary_S    < min_Primary_S                                 ) min_Primary_S    = temp_gamma.Primary_S   ;
        if( temp_gamma.Photon_theta > max_Photon_theta                              ) max_Photon_theta = temp_gamma.Photon_theta;
        if( temp_gamma.Photon_theta < min_Photon_theta                              ) min_Photon_theta = temp_gamma.Photon_theta;
        if( temp_gamma.Photon_E     > max_Photon_E && temp_gamma.Photon_E < 0.00001 ) max_Photon_E     = temp_gamma.Photon_E    ;
        if( temp_gamma.Photon_E     < min_Photon_E                                  ) min_Photon_E     = temp_gamma.Photon_E    ;
        if( temp_gamma.Parent_X     > max_Parent_X                                  ) max_Parent_X     = temp_gamma.Parent_X    ;
        if( temp_gamma.Parent_X     < min_Parent_X                                  ) min_Parent_X     = temp_gamma.Parent_X    ;
        if( temp_gamma.Parent_Y     > max_Parent_Y                                  ) max_Parent_Y     = temp_gamma.Parent_Y    ;
        if( temp_gamma.Parent_Y     < min_Parent_Y                                  ) min_Parent_Y     = temp_gamma.Parent_Y    ;
        if( temp_gamma.Parent_Z     > max_Parent_Z                                  ) max_Parent_Z     = temp_gamma.Parent_Z    ;
        if( temp_gamma.Parent_Z     < min_Parent_Z                                  ) min_Parent_Z     = temp_gamma.Parent_Z    ;
    } 

    cout << "#========== VARIABLES MIN AND MAX ==========#" << endl;
    cout << "  Primary E = [" << min_Primary_E << ", " << max_Primary_E << "]" << endl;
    cout << "  Primary S = [" << min_Primary_S << ", " << max_Primary_S << "]" << endl;
    cout << "  Parent X = [" << min_Parent_X << ", " << max_Parent_X << "]" << endl;
    cout << "  Parent Y = [" << min_Parent_Y << ", " << max_Parent_Y << "]" << endl;
    cout << "  Parent Z = [" << min_Parent_Z << ", " << max_Parent_Z << "]" << endl;
    cout << "  Photon theta = [" << min_Photon_theta << ", " << max_Photon_theta << "]" << endl;
    cout << "  Photon E = [" << min_Photon_E << ", " << max_Photon_E << "]" << endl;
    cout << "  X = [" << min_X << ", " << max_X << "]" << endl;
    cout << "  dEdX = [" << min_dEdX << ", " << max_dEdX << "]" << endl;
    cout << "  E = [" << min_E << ", " << max_E << "]" << endl;
    cout << "#===========================================#" << endl;
    cout << endl;

    ////////////////////////////////////////////////////
    //// c1 /// E vs Theta /// All /// Normailized /////
    ////////////////////////////////////////////////////
    TGraph* graph_cher = new TGraph( 10 / 0.01 + max_Primary_E / 10 - 1 );
    TLegend* legend_cher = new TLegend();
    if( present_gammas ){
        TCanvas* canvas_c1 = new TCanvas( "c1", "", 1000, 1000 );
        canvas_c1->SetLogz();

        title = "Primary " + particle_string + " Energy vs All Photon Angles Normalized;" "E [MeV];" "#theta [Deg]";
        TH2D* hist_primaryEnergyVsPhotonThetaNormalized = new TH2D( "", title.c_str() , nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
        for( int i = 0; i < gammas.size(); i++ ) 
            hist_primaryEnergyVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
        hist_primaryEnergyVsPhotonThetaNormalized->Scale(1/double(nParticles));
        hist_primaryEnergyVsPhotonThetaNormalized->Draw("COLZ");
        //hist_primaryEnergyVsPhotonThetaNormalized->SaveAs("hist.root");
        hist_primaryEnergyVsPhotonThetaNormalized->SetAxisRange( 0, 90, "Y" );
        addBoarder( canvas_c1 );
      
        int i = 0;
        double point;
        for( double x = 0; x < max_Primary_E; x += 0.1 ){
            point = get_cherAngle( m, n, x );
            if( point >= 0 ) graph_cher->SetPoint( i++, x, point );
        }
        graph_cher->SetMarkerStyle( 8 );
        graph_cher->SetLineWidth  ( 3 );
        graph_cher->SetLineColor  ( kMagenta );//kRed
        graph_cher->SetMarkerColor( kMagenta );//kRed
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

        title = "Primary " + particle_string + " Energy vs All Photon Angles;" "E [MeV];" "#theta [Deg]";
        TH2D* hist_primaryEnergyVsPhotonThetaNotNormalized = new TH2D( "", title.c_str(), nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
        for( int i = 0; i < gammas.size(); i++ ) 
            hist_primaryEnergyVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
        hist_primaryEnergyVsPhotonThetaNotNormalized->Draw("COLZ");
        addBoarder( canvas_c2 );

        graph_cher->SetMarkerStyle( 8 );
        graph_cher->SetLineWidth  ( 3 );
        graph_cher->SetLineColor  ( kMagenta );
        graph_cher->SetMarkerColor( kMagenta );
        graph_cher->Draw( "Same" );
        legend_cher->Draw("same");
    }
    
    /////////////////////////////////////////
    //// c3 /// E vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    if( present_gammas ){
        TCanvas* canvas_c3 = new TCanvas( "c3", "", 1000, 1000 );
        canvas_c3->SetLogz();
        title = "Primary " + particle_string + " Energy vs nonCerenkov Photon Angles;" "E [MeV];" "#theta [Deg]";
        TH2D* hist_primaryEnergyVsPhotonNotThetaC = new TH2D( "", title.c_str(), nBins, min_Primary_E, max_Primary_E, nBins, min_Photon_theta, max_Photon_theta );
        for( int i = 0; i < gammas.size(); i++ ) 
            if( gammas[ i ].CreationProcess != map_process.at( "Cerenkov" ) )
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
      title = "Primary " + particle_string + " Track Length vs All Photon Angles Normalized;" "x [cm];" "#theta [Deg]";
      TH2D* hist_primaryPositionVsPhotonThetaNormalized = new TH2D( "", title.c_str(), nBins, min_Primary_S, max_Primary_S, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonThetaNormalized->Fill( gammas[ i ].Primary_S, gammas[ i ].Photon_theta );
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
      title = "Primary " + particle_string + " Track Length vs Cerenkov Photon Angles Normalized;" "x [cm];" "#theta [Deg]";
      TH2D* hist_primaryPositionVsPhotonThetaCNormalized = new TH2D( "", title.c_str(), nBins, min_Primary_S, max_Primary_S, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess == map_process.at( "Cerenkov" ) )
          hist_primaryPositionVsPhotonThetaCNormalized->Fill( gammas[ i ].Primary_S, gammas[ i ].Photon_theta );
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
      title = "Primary " + particle_string + " Track Length vs All Photon Angles;" "x [cm];" "#theta [Deg]";
      TH2D* hist_primaryPositionVsPhotonThetaNotNormalized = new TH2D( "", title.c_str(), nBins, min_Primary_S, max_Primary_S, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonThetaNotNormalized->Fill( gammas[ i ].Primary_S, gammas[ i ].Photon_theta );
      hist_primaryPositionVsPhotonThetaNotNormalized->Draw("COLZ");
      addBoarder( canvas_c6 );
    }
    
    /////////////////////////////////////////
    //// c7 /// X vs Theta /// !Cerenkov ////
    /////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c7 = new TCanvas( "c7", "", 1000, 1000 );
      canvas_c7->SetLogz();
      title = "Primary " + particle_string + " Track Length vs nonCerenkov Photon Angles;" "x [cm];" "#theta [Deg]";
      TH2D* hist_primaryPositionVsPhotonNotThetaC = new TH2D( "", title.c_str(), nBins, min_Primary_S, max_Primary_S, nBins, min_Photon_theta, max_Photon_theta );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess != map_process.at( "Cerenkov" ) )
          hist_primaryPositionVsPhotonNotThetaC->Fill( gammas[ i ].Primary_S, gammas[ i ].Photon_theta );
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
      title = "Primary " + particle_string + " Track Length vs All Photon Energies Normalized;" "x [cm];" "E [MeV]";
      TH2D* hist_primaryPositionVsPhotonEnergyNormalized = new TH2D( "", title.c_str(), nBins, min_Primary_S, max_Primary_S, nBins, min_Photon_E, max_Photon_E );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_primaryPositionVsPhotonEnergyNormalized->Fill( gammas[ i ].Primary_S, gammas[ i ].Photon_E );
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
      title = "Primary " + particle_string + " Track Length vs dEdX;" "x [cm];" "dEdX [MeV/cm]";
      TH2D* hist_XVsdEdX = new TH2D( "", title.c_str(), nBins, min_X, max_X, nBins, min_dEdX, max_dEdX );
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
      title = "Primary " + particle_string + " Energy vs dEdX;" "E [MeV];" "dEdX [MeV/cm]";
      TH2D* hist_EVsdEdX = new TH2D( "", title.c_str(), nBins, min_E, max_E, nBins, min_dEdX, max_dEdX );
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
      title = "Cerenkov Photon Angles Normalized vs Primary " + particle_string + " Track Length;" "cos(#theta);" "x [cm]";
      TH2D* hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat = new TH2D( "", title.c_str(), nBins/2, 0, 1, nBins/2/2/2, 0, 133 );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess == map_process.at( "Cerenkov" ) )
          hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Fill( cos(gammas[ i ].Photon_theta/180*M_PI), gammas[ i ].Primary_S );
      hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Scale(1/double(nParticles));
      hist_primaryPositionVsPhotonThetaCNormalized_MiniBooNEFormat->Draw("COLZ");
      addBoarder( canvas_c11 );
    }
    
    ///////////////////////////
    //// c12 /// X vs dEdX ////
    ///////////////////////////
    if( present_steps ){
      TCanvas* canvas_c12 = new TCanvas( "c12", "", 1000, 1000 );
      title = "Primary " + particle_string + " Track Length vs dEdX Normalized;" "x [cm];" "dEdX [MeV/cm]";
      TH2D* hist_XVsdEdX_normalized = new TH2D( "", title.c_str(), nBins, min_X, max_X, nBins, min_dEdX, max_dEdX );
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
      title = "Primary " + particle_string + " Energy vs dEdX Normalized;" "E [cm];" "dEdX [MeV/cm]";
      TH2D* hist_EVsdEdX_normalized = new TH2D( "", title.c_str(), nBins, min_E, max_E, nBins, min_dEdX, max_dEdX );
      for( int i = 0; i < gammas.size(); i++ ) 
        hist_EVsdEdX_normalized->Fill( steps[ i ].E, steps[ i ].dEdX );
      hist_EVsdEdX_normalized->Draw("COLZ");
      hist_EVsdEdX_normalized->Scale(1/double(nParticles));
      addBoarder( canvas_c13 );
    }
    
    ///////////////////////////////////////////////////////////////
    //// c14 /// X vs Theta /// Cerenkov /// mu /// Normalized ////
    ///////////////////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c14 = new TCanvas( "c14", "", 1000, 1000 );
      //canvas_c14->SetLogz();
      title = "Cerenkov #mu Photon Angles Normalized vs Primary " + particle_string + " Track Length;" "cos(#theta);" "x [cm]";
      TH2D* hist_primaryPositionVsMuPhotonThetaCNormalized_MiniBooNEFormat = new TH2D( "", title.c_str(), nBins/2, 0, 1, nBins/2/2, 0, 133 );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].CreationProcess == map_process.at( "Cerenkov" ) && gammas[ i ].ParentParticle == map_particle.at( "mu" ) )
          hist_primaryPositionVsMuPhotonThetaCNormalized_MiniBooNEFormat->Fill( cos(gammas[ i ].Photon_theta/180*M_PI), gammas[ i ].Primary_S );
      hist_primaryPositionVsMuPhotonThetaCNormalized_MiniBooNEFormat->Scale(1/double(nParticles));
      hist_primaryPositionVsMuPhotonThetaCNormalized_MiniBooNEFormat->Draw("COLZ");
      addBoarder( canvas_c14 );
    }
    /////////////////////////////////////////////////
    //// c15 /// X vs Theta /// e /// Normalized ////
    /////////////////////////////////////////////////
    if( present_gammas ){
      TCanvas* canvas_c15 = new TCanvas( "c15", "", 1000, 1000 );
      //canvas_c15->SetLogz();
      title = "All e^{-} Photon Angles Normalized vs Primary " + particle_string + " Track Length;" "cos(#theta);" "x [cm]";
      TH2D* hist_primaryPositionVsEPhotonThetaNormalized_MiniBooNEFormat = new TH2D( "", title.c_str(), nBins/2, 0, 1, nBins/2/2, 0, 133 );
      for( int i = 0; i < gammas.size(); i++ ) 
        if( gammas[ i ].ParentParticle == map_particle.at( "e" ) )
          hist_primaryPositionVsEPhotonThetaNormalized_MiniBooNEFormat->Fill( cos(gammas[ i ].Photon_theta/180*M_PI), gammas[ i ].Primary_S );
      hist_primaryPositionVsEPhotonThetaNormalized_MiniBooNEFormat->Scale(1/double(nParticles));
      hist_primaryPositionVsEPhotonThetaNormalized_MiniBooNEFormat->Draw("COLZ");
      addBoarder( canvas_c15 );
    }
    
    //////////////////////////////////////////
    //// c16 /// Possition /// Normalized ////
    //////////////////////////////////////////
    if( present_gammas && nParticles == 1 ){
        gStyle->SetPalette( kBird );
        gStyle->SetLabelSize(.050, "xyz");
        gStyle->SetLabelOffset(.005, "xyz");
        gStyle->SetTitleSize(.05, "xyz");
        gStyle->SetTitleOffset(0.99, "x");
        // gStyle->SetTitleOffset(0.50, "y");
        gStyle->SetTitleOffset(0.79, "y");

        TCanvas* canvas_c16 = new TCanvas( "c16", "", 1000, 1000 );
        //canvas_c16->SetLogz();
        title = "Primary " + particle_string + " Position;" "x [cm];" "y [cm]";
        // TH2D* hist_primaryPosition = new TH2D( "", title.c_str(), 19, 0, 475, 10, -4.5, 8.5 );
        TH2D* hist_primaryPosition = new TH2D( "", title.c_str(), 20, 0, 340, 20, 0, 340 );

        vector< vector< double >* > pos_e_x = { new vector< double > };
        vector< vector< double >* > pos_e_y = { new vector< double > };
        vector< double >            pos_mu_x;
        vector< double >            pos_mu_y;
        int nElectron = 0;

        int nParticle{ 0 };
        for( int i = 0; i < gammas.size(); i++ ) {
            hist_primaryPosition->Fill( gammas[ i ].Parent_X, gammas[ i ].Parent_Y );
            // if( gammas[ i ].IsFirstStep == 1 )
            //     ++nParticle;
            if( nParticle == 0 && gammas[ i ].ParentParticle == map_particle.at( "e" ) ) {
                pos_e_x[ nElectron ]->push_back( gammas[ i ].Parent_X );
                pos_e_y[ nElectron ]->push_back( gammas[ i ].Parent_Y );
            }
            else if( nParticle == 0 && gammas[ i ].ParentParticle == map_particle.at( "mu" ) ) {
                pos_mu_x.push_back( gammas[ i ].Parent_X );
                pos_mu_y.push_back( gammas[ i ].Parent_Y );
                if( !pos_e_x[ nElectron ]->empty() ) {
                    pos_e_x.push_back( new vector< double > );
                    pos_e_y.push_back( new vector< double > );
                    ++nElectron;
                }
            }
        }

        vector< TGraph* > graphs;
        graphs.push_back( new TGraph( pos_mu_x.size(), &pos_mu_x[ 0 ], &pos_mu_y[ 0 ] ) );
        for( int i{ 0 }; i < pos_e_x.size(); i++ )
            if( pos_e_x[ i ]->size() != 0 )
                graphs.push_back( new TGraph( pos_e_x[ i ]->size(), &pos_e_x[ i ]->at( 0 ), &pos_e_y[ i ]->at( 0 ) ) );

        for( auto vec : pos_e_x )
            delete vec;
        for( auto vec : pos_e_y )
            delete vec;

        //hist_primaryPosition->Scale(1/double(nParticles));
        hist_primaryPosition->Draw("COLZ");
        hist_primaryPosition->GetZaxis()->SetMaxDigits(3);
        for( auto i : graphs ){
            i->Draw( "same" );
            i->SetMarkerStyle( 8 );
            i->SetLineWidth  ( 2 );
            i->SetLineColor  ( kBlack );
            i->SetMarkerColor( kBlack );
        }
        graphs[ 0 ]->SetLineColor  ( kRed );
        graphs[ 0 ]->SetMarkerColor( kRed );
        addBoarder( canvas_c16 );
        
        gStyle->SetNumberContours( NCont + 2 );
        gStyle->SetPalette( NCont + 2, colors );
    }

    /////////////////////////////////////////////////////
    //// c17 /// E vs Theta /// All /// Normailized /////
    /////////////////////////////////////////////////////
    if( present_gammas ){
        gStyle->SetLabelSize(.050, "xyz");
        gStyle->SetLabelOffset(.005, "xyz");
        gStyle->SetTitleSize(.05, "xyz");
        gStyle->SetTitleOffset(0.99, "x");
        gStyle->SetTitleOffset(0.60, "y");

        TCanvas* canvas_c17 = new TCanvas( "c17", "", 1000, 1000 );
        canvas_c17->SetLogz();

        title = "Primary " + particle_string + " Energy vs All Photon Angles;" "E [MeV];" "#theta [Deg]";
        TH2D* hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat = new TH2D( "", title.c_str(), nBins/2, min_Primary_E, max_Primary_E, nBins/2, min_Photon_theta, max_Photon_theta );
        for( int i = 0; i < gammas.size(); i++ ) 
            hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->Fill( gammas[ i ].Primary_E, gammas[ i ].Photon_theta );
        hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->Scale(1/double(nParticles));
        hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->SetAxisRange( 0, 90, "Y" );
        if( particle == 0 )
            hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->SetAxisRange( 49, 300, "X" );
        else
            hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->SetAxisRange( 0, 300, "X" );
        hist_primaryEnergyVsPhotonThetaNormalized_GoldwaterFormat->Draw("COLZ");
        addBoarder( canvas_c17 );

        graph_cher->SetMarkerStyle( 8 );
        graph_cher->SetLineWidth  ( 3 );
        graph_cher->SetLineColor  ( kMagenta );
        graph_cher->SetMarkerColor( kMagenta );
        graph_cher->Draw( "Same" );
        legend_cher->Draw("same");
        redrawBorder();
    }
}
