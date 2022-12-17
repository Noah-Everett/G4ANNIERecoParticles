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

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "RunAction.hh"

#include "ParameterParser.hh"

class G4LogicalVolume;

/// Stepping action class
///

namespace ANNIERecoParticles
{

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction, RunAction* runAction, ParameterParser* t_parameterParser );
    ~SteppingAction() override;

    // method from the base class
    void UserSteppingAction(const G4Step*) override;
    
  private:
    EventAction* m_eventAction = nullptr;
    RunAction* m_runAction = nullptr;
    ParameterParser* m_parameterParser = nullptr;
    G4double prev_boundary_energy = 0;
    G4double prev_boundary_len = 0;
    G4double prev_len = 0;
    G4double prev_ke = 0;
    G4String prev_particle;
    bool first_step = true;
};
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
