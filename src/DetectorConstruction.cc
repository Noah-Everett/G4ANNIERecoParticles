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
/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

using std::to_string;
#include<string>
using std::string;

namespace B1
{
DetectorConstruction::DetectorConstruction(){}
DetectorConstruction::~DetectorConstruction(){}
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  G4MaterialPropertiesTable* water_materialPropertiesTable = new G4MaterialPropertiesTable();
  G4double water_materialPropertiesTable_energies[4] = {2.00*eV,2.87*eV,2.90*eV,3.47*eV};
  G4double water_materialPropertiesTable_rindices[4] = {1.333,1.333,1.333,1.333};
  water_materialPropertiesTable->AddProperty("RINDEX", water_materialPropertiesTable_energies, water_materialPropertiesTable_rindices, 4 );
  water->SetMaterialPropertiesTable(water_materialPropertiesTable);


  G4bool checkOverlaps = false;// true;

  G4double size_X=10000*m, size_Y=100*m, size_Z=100*m;
  size_X=100*m;

  G4Box* solidWorld = new G4Box("World", size_X,size_Y,size_Z);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        water,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,0),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Envelope
  //
  G4double size_dX=0.00001*m;
  // G4double size_dX=size_X;
  // G4double size_dX=1*m; // fast for testing
  G4double x = -size_X/2;
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        size_dX/2, size_Y, size_Z); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        water,             //its material
                        "Envelope");         //its name

  for( int i = 0; i < size_X/size_dX;i++){
  x+=size_dX;
  string name = "Envelope_" + to_string( i );
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(x,0,0),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    name.c_str(),              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                    }

  return physWorld;
}

}
