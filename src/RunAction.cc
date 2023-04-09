//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file RunAction.cc
/// \brief Implementation of the ANNIERecoParticles::RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"
#include "Maps.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <map>
#include <cmath>

namespace ANNIERecoParticles
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
    m_analysisManager->SetDefaultFileType("root");
    m_analysisManager->SetVerboseLevel(1);
    m_analysisManager->SetFileName("G4ANNIERecoParticles");

    m_analysisManager->SetNtupleMerging(true);
    m_analysisManager->OpenFile();

    // new G4UnitDefinition( "MeV/m", "MeV/m", "Energy/Length", MeV/m );

    hist_dEdX_nBins              = 1000; hist_dEdX_min              = 0; hist_dEdX_max              = 1200;
    hist_emission_distance_nBins = 1000; hist_emission_distance_min = 0; hist_emission_distance_max = 10  ; hist_emission_angle_nBins = 1000; hist_emission_angle_min = 0; hist_emission_angle_max = 2*M_PI;
    hist_transmittance_nBins     = 1000; hist_transmittance_min     = 0; hist_transmittance_max     = 1000;

    m_analysisManager->CreateH1("hist_dEdX_dEdX"        , "hist_dEdX_dEdX"        , hist_dEdX_nBins             , hist_dEdX_min             , hist_dEdX_max                                                                                           );//, "MeV/m"        );
    m_analysisManager->CreateH1("hist_dEdX_counts"      , "hist_dEdX_counts"      , hist_dEdX_nBins             , hist_dEdX_min             , hist_dEdX_max                                                                                           );//                 );
    m_analysisManager->CreateH2("hist_emission_counts"  , "hist_emission_counts"  , hist_emission_distance_nBins, hist_emission_distance_min, hist_emission_distance_max, hist_emission_angle_nBins, hist_emission_angle_min, hist_emission_angle_max );//, "m"    , "rad" );
    m_analysisManager->CreateH2("hist_emission_energies", "hist_emission_energies", hist_emission_distance_nBins, hist_emission_distance_min, hist_emission_distance_max, hist_emission_angle_nBins, hist_emission_angle_min, hist_emission_angle_max );//, "m"    , "rad" );
    m_analysisManager->CreateH1("hist_transmittance"    , "hist_transmittance"    , hist_transmittance_nBins    , hist_transmittance_min    , hist_transmittance_max                                                                                  );//, "m"            );

    m_analysisManager->CreateNtuple("tuple_dEdX", "tuple_dEdX");
    m_analysisManager->CreateNtupleDColumn("E");
    m_analysisManager->CreateNtupleDColumn("dE");
    m_analysisManager->CreateNtupleDColumn("X");
    m_analysisManager->CreateNtupleDColumn("dX");
    m_analysisManager->CreateNtupleDColumn("dEdX");
    m_analysisManager->FinishNtuple();

    m_analysisManager->CreateNtuple("tuple_emission", "tuple_emission");
    m_analysisManager->CreateNtupleDColumn("Primary_E");
    m_analysisManager->CreateNtupleDColumn("Primary_S");
    m_analysisManager->CreateNtupleDColumn("Photon_theta");
    m_analysisManager->CreateNtupleDColumn("Photon_E");
    m_analysisManager->CreateNtupleIColumn("CreationProcess");
    m_analysisManager->CreateNtupleIColumn("ParentParticle");
    m_analysisManager->CreateNtupleDColumn("Parent_X");
    m_analysisManager->CreateNtupleDColumn("Parent_Y");
    m_analysisManager->CreateNtupleDColumn("Parent_Z");
    m_analysisManager->FinishNtuple();

    m_analysisManager->CreateNtuple("tuple_transmittance", "tuple_transmittance");
    m_analysisManager->CreateNtupleDColumn("TrackLength");
    m_analysisManager->CreateNtupleDColumn("Energy");
    m_analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto m_analysisManager = G4AnalysisManager::Instance();

    // Doesnt work becuse of multithreaded hist merge
    // if( m_hist_dEdX_nEnteries              > 0 ) m_analysisManager->ScaleH1( 0, 1 / m_hist_dEdX_nEnteries              );
    // if( m_hist_emission_energies_nEnteries > 0 ) m_analysisManager->ScaleH2( 1, 1 / m_hist_emission_energies_nEnteries );
    // if( m_hist_transmittance_nEnergies     > 0 ) m_analysisManager->ScaleH1( 1, 1 / m_hist_transmittance_nEnergies     );

    m_analysisManager->SetH1Title     ( 0, "Stopping Power (dEdX) dEdX"       );
    m_analysisManager->SetH1XAxisTitle( 0, "E [MeV]"                          );
    m_analysisManager->SetH1YAxisTitle( 0, "$\\langle dEdX \\rangle$ [MeV/m]" );
    
    m_analysisManager->SetH1Title     ( 1, "Stopping Power (dEdX) counts" );
    m_analysisManager->SetH1XAxisTitle( 1, "E [MeV]"                      );
    m_analysisManager->SetH1YAxisTitle( 1, "Counts"                       );

    m_analysisManager->SetH2Title     ( 0, "Emission Counts"       );
    m_analysisManager->SetH2XAxisTitle( 0, "s [m]"                 );
    m_analysisManager->SetH2YAxisTitle( 0, "#theta_{#gamma} [rad]" );
    m_analysisManager->SetH2ZAxisTitle( 0, "Counts"                );

    m_analysisManager->SetH2Title     ( 1, "Average Emission Energies" );
    m_analysisManager->SetH2XAxisTitle( 1, "s [m]"                     );
    m_analysisManager->SetH2YAxisTitle( 1, "#theta_{#gamma} [rad]"     );
    m_analysisManager->SetH2ZAxisTitle( 1, "Counts"                    );

    m_analysisManager->SetH1Title     ( 2, "Transmittance" );
    m_analysisManager->SetH1XAxisTitle( 2, "s [m]"         );
    m_analysisManager->SetH1YAxisTitle( 2, "Counts"        );

    m_analysisManager->Write();
    m_analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}
