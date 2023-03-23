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

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessTable.hh"

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

void SteppingAction::UserSteppingAction( const G4Step* t_step )
{
    m_track          = t_step->GetTrack        ();
    m_stepPoint_prev = t_step->GetPreStepPoint ();
    m_stepPoint_post = t_step->GetPostStepPoint();

    if( kill_neutrino() ) return;
    if( ( !m_parameterParser->get_record_emission() 
       && !m_parameterParser->get_record_transmittance() ) 
       && kill_photon() )
        return;

    if( m_parameterParser->get_record_dEdX() ) {
        if( is_newPrimary() ) m_dEdX_newPrimary = true;
        m_dEdX_energy_curr      = m_track->GetKineticEnergy();
        m_dEdX_trackLength_curr = m_track->GetTrackLength  ();

        if( !m_dEdX_newPrimary && m_track->GetParentID() == 0 && m_stepPoint_post->GetStepStatus() == fGeomBoundary ) {
            m_dEdX_dE   = m_dEdX_energy_curr      - m_dEdX_energy_prev     ;
            m_dEdX_dX   = m_dEdX_trackLength_curr - m_dEdX_trackLength_prev;
            m_dEdX_dEdX = m_dEdX_dE               / m_dEdX_dX              ;

            if( m_parameterParser->get_make_tuple_dEdX() ) make_tuple_dEdX();
            if( m_parameterParser->get_make_hist_dEdX () ) make_hist_dEdX ();
        }

        m_dEdX_newPrimary       = false                  ;
        m_dEdX_energy_prev      = m_dEdX_energy_curr     ;
        m_dEdX_trackLength_prev = m_dEdX_trackLength_curr;
    }

    if( m_parameterParser->get_record_emission() ) {
        if( m_track->GetParentID() == 0 ) {
            m_emission_prevPrimary_energy              = m_track->GetTotalEnergy      ();
            m_emission_prevPrimary_trackLength         = m_track->GetTrackLength      ();
            m_emission_prevPrimary_momentumThreeVector = m_track->GetMomentumDirection();
        }
        if( abs( m_track->GetParticleDefinition()->GetPDGEncoding() ) != 22 )
            m_emission_prevPrimary_positionThreeVector = m_track->GetPosition();
        else {
            m_emission_angle  = m_track->GetMomentumDirection().angle( m_emission_prevPrimary_momentumThreeVector );
            m_emission_energy = m_track->GetTotalEnergy() / eV;
            if( m_parameterParser->get_make_tuple_emission() ) make_tuple_emission();
            if( m_parameterParser->get_make_hist_emission () ) make_hist_emission ();
            m_track->SetTrackStatus( fKillTrackAndSecondaries );
        }
    }

    if( m_parameterParser->get_record_transmittance() &&
        m_track->GetParentID() == 0 && abs( m_track->GetParticleDefinition()->GetPDGEncoding() ) == 22 ) {
        if( is_newPrimary() ) {
            m_transmittance_initEnergy = m_track->GetTotalEnergy();
            if( m_parameterParser->get_make_hist_transmittance () ) make_hist_transmittance ();
        }
        m_transmittance_trackLength = m_track->GetTrackLength();
        if( m_parameterParser->get_make_tuple_transmittance() ) make_tuple_transmittance();
    }
}

inline void SteppingAction::make_tuple_dEdX() {
    m_analysisManager->FillNtupleDColumn( 0, 0, m_dEdX_energy_curr      );
    m_analysisManager->FillNtupleDColumn( 0, 1, m_dEdX_dE               );
    m_analysisManager->FillNtupleDColumn( 0, 2, m_dEdX_trackLength_curr );
    m_analysisManager->FillNtupleDColumn( 0, 3, m_dEdX_dX               );
    m_analysisManager->FillNtupleDColumn( 0, 4, m_dEdX_dEdX             );
    m_analysisManager->AddNtupleRow( 0 );
}

inline void SteppingAction::make_hist_dEdX() {
    m_analysisManager->FillH1( 0, m_dEdX_energy_prev, m_dEdX_dEdX );
    m_runAction->incrament_hist_dEdX_nEnteries();
}

inline void SteppingAction::make_tuple_emission() {
    m_analysisManager->FillNtupleDColumn( 1, 0, m_emission_prevPrimary_energy                      );
    m_analysisManager->FillNtupleDColumn( 1, 1, m_emission_prevPrimary_trackLength                 );
    m_analysisManager->FillNtupleDColumn( 1, 2, m_emission_angle                                   );
    m_analysisManager->FillNtupleDColumn( 1, 3, m_track->GetTotalEnergy()                          );
    m_analysisManager->FillNtupleIColumn( 1, 4, m_track->GetDefinition()->GetProcessManager()->GetProcessIndex( const_cast< G4VProcess* >( m_track->GetCreatorProcess() ) ) );
    m_analysisManager->FillNtupleIColumn( 1, 5, m_track->GetParticleDefinition()->GetPDGEncoding() );
    m_analysisManager->FillNtupleDColumn( 1, 6, m_emission_prevPrimary_positionThreeVector.x()     );
    m_analysisManager->FillNtupleDColumn( 1, 7, m_emission_prevPrimary_positionThreeVector.y()     );
    m_analysisManager->FillNtupleDColumn( 1, 8, m_emission_prevPrimary_positionThreeVector.z()     );
    m_analysisManager->AddNtupleRow( 1 );
}

inline void SteppingAction::make_hist_emission() {
    m_analysisManager->FillH2( 0, m_emission_prevPrimary_trackLength, m_emission_angle, 1                 );
    if( m_emission_energy > 200 ) {
        G4cout << "Warning: Large emission energy of " << m_emission_energy << " eV" << G4endl;
        m_emission_energy = 0;
    } else
        m_runAction->incrament_hist_emission_energies_nEnteries();
    m_analysisManager->FillH2( 1, m_emission_prevPrimary_trackLength, m_emission_angle, m_emission_energy );
}

inline void SteppingAction::make_tuple_transmittance() {
    m_analysisManager->FillNtupleDColumn( 2, 0, m_transmittance_trackLength );
    m_analysisManager->FillNtupleDColumn( 2, 1, m_track->GetTotalEnergy()   );
}

inline void SteppingAction::make_hist_transmittance() {
    m_analysisManager->FillH1( 1, m_transmittance_trackLength, 1 );
}

inline bool SteppingAction::kill_neutrino() {
    if( m_track->GetParticleDefinition()->GetPDGEncoding() ==  12 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() == -12 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() ==  14 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() == -14 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() ==  16 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() == -16 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() ==  18 ||
        m_track->GetParticleDefinition()->GetPDGEncoding() == -18   ) {
        m_track->SetTrackStatus( fKillTrackAndSecondaries );
        return true;
    }
    return false;
}

inline bool SteppingAction::kill_photon() {
    if( abs( m_track->GetParticleDefinition()->GetPDGEncoding() ) == 22 ) {
        m_track->SetTrackStatus( fKillTrackAndSecondaries );
        return true;
    }
    return false;
}

inline bool SteppingAction::is_newPrimary() {
    if( m_parameterParser->get_record_dEdX() ) {
        if( m_track->GetParentID() == 0 && m_track->GetTrackLength() < m_dEdX_trackLength_prev )
            return true;
        return false;
    } else if( m_parameterParser->get_record_transmittance() ) {
        if( m_track->GetParentID() == 0 && m_track->GetTrackLength() < m_transmittance_trackLength )
            return true;
        return false;
    } else
        return false;
}

}