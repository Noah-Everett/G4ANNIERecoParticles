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
/// \file SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include"G4SystemOfUnits.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction, RunAction* runAction)
: fEventAction(eventAction), fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction( const G4Step *step )
{
  if( step->GetTrack()->GetParentID() != 0 ) {
    G4cout << "SECONDARY!!!!!!" << G4endl; // this message should 
                                           // never be seen as all secondaries 
                                           // should already be killed.
    step->GetTrack()->SetTrackStatus( fKillTrackAndSecondaries );
    return;
  }
  else if( step->GetPostStepPoint()->GetStepStatus() != 1 ) return;

  // Save info
  G4double cur_energy = step->GetTrack()->GetKineticEnergy()/MeV;
  G4double cur_len    = step->GetTrack()->GetTrackLength()  /cm;
  if( first_step ) first_step = false;
  else {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn( 0, 0, cur_energy );                // current energy
    analysisManager->FillNtupleDColumn( 0, 1, cur_energy - prev_energy );  // delta energy
    analysisManager->FillNtupleDColumn( 0, 2, cur_len );                   // current track length
    analysisManager->FillNtupleDColumn( 0, 3, cur_len - prev_len );        // delta track length
    analysisManager->FillNtupleDColumn( 0, 4, ( cur_energy - prev_energy ) // dEdX
                                              / ( cur_len - prev_len ) );    
    analysisManager->AddNtupleRow();
  }

  prev_energy = cur_energy;
  prev_len    = cur_len;
}

}
