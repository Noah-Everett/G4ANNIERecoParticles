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

#ifndef SteppingAction_h
#define SteppingAction_h

#include "G4Step.hh"

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "RunAction.hh"
#include "ParameterParser.hh"
#include "PrimaryGeneratorAction.hh"

class G4LogicalVolume;

/// Stepping action class
///

namespace ANNIERecoParticles
{

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction* eventAction, RunAction* runAction, ParameterParser* t_parameterParser, PrimaryGeneratorAction* t_primaryGeneratorAction );
   ~SteppingAction() override;

    // method from the base class
    void UserSteppingAction( const G4Step* ) override;
    
    inline bool kill_neutrino();
    inline bool kill_photon  ();

    inline bool is_newPrimary();

    inline void make_tuple_dEdX         ();
    inline void make_tuple_emission     ();
    inline void make_tuple_transmittance();
    inline void make_hist_dEdX          ();
    inline void make_hist_emission      ();
    inline void make_hist_transmittance ();
    
private:
    EventAction           * m_eventAction           { nullptr };
    RunAction             * m_runAction             { nullptr };
    ParameterParser       * m_parameterParser       { nullptr };
    PrimaryGeneratorAction* m_primaryGeneratorAction{ nullptr };
    G4AnalysisManager     * m_analysisManager       { G4AnalysisManager::Instance() };

    G4Track    * m_track         { nullptr };
    G4StepPoint* m_stepPoint_prev{ nullptr };
    G4StepPoint* m_stepPoint_post{ nullptr };

    // dEdX
    G4bool   m_dEdX_newPrimary      { true };
    G4double m_dEdX_energy_curr     { 0 };
    G4double m_dEdX_energy_prev     { 0 };
    G4double m_dEdX_trackLength_curr{ 0 };
    G4double m_dEdX_trackLength_prev{ 0 };
    G4double m_dEdX_dE              { 0 };
    G4double m_dEdX_dX              { 0 };
    G4double m_dEdX_dEdX            { 0 };

    // emission
    G4double      m_emission_prevPrimary_energy             { 0 };
    G4double      m_emission_prevPrimary_trackLength        { 0 };
    G4ThreeVector m_emission_prevPrimary_momentumThreeVector{ 0 };
    G4ThreeVector m_emission_prevPrimary_positionThreeVector{ 0 };
    G4double      m_emission_angle                          { 0 };
    G4double      m_emission_energy                         { 0 };

    // transmittance
    G4double m_transmittance_trackLength{ 99999 };
    G4int    m_transmittance_parentID   { 0     };
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
