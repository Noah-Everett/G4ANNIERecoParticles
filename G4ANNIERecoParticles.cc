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

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"

#include "QBBC.hh"
#include "G4OpticalPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "CmdLnArgParser.hpp"
#include "Messenger.hpp"

using namespace Base;
using Base::CmdLnArgParser::parser;
using Base::Messenger::Verbosity::fatal_int;
using Base::Messenger::messenger_c;

using namespace ANNIERecoParticles;

const string k_welcome = "#==========================================#\n"
                         "#========== G4ANNIERecoParticles ==========#\n"
                         "#==========================================#\n";
const string k_help    = "PROGRAM HELP/USAGE STATEMENT HERE";

namespace Base::Messenger {
messenger messenger_c( cout, k_welcome, LOCATION );
}

// Possible arguments
vector< string > optsWArg_req{ "--mac_run"      };
vector< string > optsWArg_opt{ "--mac_detector" };
vector< string > optsNArg_req{                        };
vector< string > optsNArg_opt{ "-h", "--help"         };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
    parser parser( argc, argv, optsWArg_req, optsWArg_opt, optsNArg_req, optsNArg_opt );

    if( parser.hasOpt( "-h" ) || parser.hasOpt( "--help" ) ) {
        messenger_c( fatal_int, LOCATION ) << '\n' << k_help;
        return 0;
    }


    G4SteppingVerbose::UseBestUnit( 4 );

    ParameterParser* parameterParser = new ParameterParser();

    G4UIExecutive* ui{ nullptr };
    if ( argc == 1 ) ui = new G4UIExecutive(argc, argv);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    auto* runManager = G4RunManagerFactory::CreateRunManager( G4RunManagerType::Default );

    runManager->SetUserInitialization( new DetectorConstruction( parameterParser ) );

    G4VModularPhysicsList* physicsList = new QBBC;
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    physicsList->RegisterPhysics( opticalPhysics );
    physicsList->SetVerboseLevel( 1 );
    runManager->SetUserInitialization( physicsList );

    runManager->SetUserInitialization( new ActionInitialization( parameterParser ) );

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    if( !ui ) {
        G4String command = "/control/execute ";
        G4String fileName = argv[ 1 ];
        UImanager->ApplyCommand( command + fileName );
    } else {
        UImanager->ApplyCommand( "/control/execute init_vis.mac" );
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
