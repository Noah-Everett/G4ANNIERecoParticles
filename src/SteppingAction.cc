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
/// \brief Implementation of the ANNIERecoParticles::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "Maps.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include"G4SystemOfUnits.hh"

#include<cmath>

namespace ANNIERecoParticles
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction, RunAction* runAction, ParameterParser* t_parameterParser )
: m_eventAction(eventAction), m_runAction(runAction), m_parameterParser{ t_parameterParser }
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction( const G4Step *step )
{
    G4Track* track = step->GetTrack();
    G4StepPoint* stepPoint_pre  = step->GetPreStepPoint();
    G4StepPoint* stepPoint_post = step->GetPostStepPoint();

    if( !m_parameterParser->get_record_gammas() && track->GetParticleDefinition()->GetParticleSubType() == "photon" ) {
        track->SetTrackStatus( fKillTrackAndSecondaries );
    }

    // if primary
    if( m_parameterParser->get_record_gammas() && track->GetParentID() == 0 ) {
        if( track->GetTrackLength() < prev_len )
            isFirstStep = true;
        prev_len = track->GetTrackLength()/cm;
        prev_ke  = track->GetKineticEnergy()/MeV;
    }
    // if not photon
    if( m_parameterParser->get_record_gammas() && track->GetParticleDefinition()->GetParticleSubType() != "photon" ) {
        prev_particle = track->GetParticleDefinition()->GetParticleSubType();
        prev_x = track->GetPosition().x()/cm;
        prev_y = track->GetPosition().y()/cm;
        prev_z = track->GetPosition().z()/cm;
    }
    // if photon
    else if( m_parameterParser->get_record_gammas() ) {
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn( 1, 0, prev_ke );
        analysisManager->FillNtupleDColumn( 1, 1, prev_len );
        analysisManager->FillNtupleDColumn( 1, 2, acos( track->GetMomentumDirection().x()/cm / ( track->GetMomentumDirection().mag()/cm ) ) / M_PI * 180 );
        analysisManager->FillNtupleDColumn( 1, 3, track->GetTotalEnergy()/MeV );
        if( map_process.find( track->GetCreatorProcess()->GetProcessName() ) != map_process.end() )
            analysisManager->FillNtupleIColumn( 1, 4, map_process.at( track->GetCreatorProcess()->GetProcessName() ) );
        else {
            G4cout << "Not in map_process: " << track->GetCreatorProcess()->GetProcessName() << G4endl;
            analysisManager->FillNtupleIColumn( 1, 4, -999999 );
        }
        if( map_particle.find( prev_particle ) != map_particle.end() )
            analysisManager->FillNtupleIColumn( 1, 5, map_particle.at( prev_particle ) );
        else {
            G4cout << "Not in map_particle: " << prev_particle << G4endl;
            analysisManager->FillNtupleIColumn( 1, 5, -999999 );
        }
        analysisManager->FillNtupleDColumn( 1, 6, prev_x );
        analysisManager->FillNtupleDColumn( 1, 7, prev_y );
        analysisManager->FillNtupleDColumn( 1, 8, prev_z );
        if( isFirstStep )
            analysisManager->FillNtupleIColumn( 1, 9, true );
        else 
            analysisManager->FillNtupleIColumn( 1, 9, false );
        isFirstStep = false;
        analysisManager->AddNtupleRow( 1 );
        track->SetTrackStatus( fKillTrackAndSecondaries );
    }
        
    // if primary particle and crossing boundary
    if( m_parameterParser->get_record_dEdX() && track->GetParentID() == 0 && stepPoint_post->GetStepStatus() == 1 ) {
        if( first_step ) first_step = false;
        else {
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillNtupleDColumn( 0, 0, track->GetKineticEnergy()/MeV );                         // current energy
            analysisManager->FillNtupleDColumn( 0, 1, track->GetKineticEnergy()/MeV - prev_boundary_energy );  // delta energy
            analysisManager->FillNtupleDColumn( 0, 2, track->GetTrackLength()/cm );                            // current track length
            analysisManager->FillNtupleDColumn( 0, 3, track->GetTrackLength()/cm - prev_boundary_len );        // delta track length
            analysisManager->FillNtupleDColumn( 0, 4, ( track->GetKineticEnergy()/MeV - prev_boundary_energy ) // dEdX
                                                        / ( track->GetTrackLength()/cm - prev_boundary_len ) );    
            analysisManager->AddNtupleRow( 0 );
        }
        prev_boundary_energy = track->GetKineticEnergy()/MeV;
        prev_boundary_len    = track->GetTrackLength()/cm;
    } 
    // if neutrino
    else if( track->GetParticleDefinition()->GetPDGEncoding() ==  12 ||
             track->GetParticleDefinition()->GetPDGEncoding() == -12 ||
             track->GetParticleDefinition()->GetPDGEncoding() ==  14 ||
             track->GetParticleDefinition()->GetPDGEncoding() == -14 ||
             track->GetParticleDefinition()->GetPDGEncoding() ==  16 ||
             track->GetParticleDefinition()->GetPDGEncoding() == -16 ||
             track->GetParticleDefinition()->GetPDGEncoding() ==  18 ||
             track->GetParticleDefinition()->GetPDGEncoding() == -18 ) {
        track->SetTrackStatus( fKillTrackAndSecondaries );
    }
}

};
