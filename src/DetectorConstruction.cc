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

#include<string>
using std::to_string;
using std::string;

namespace ANNIERecoParticles
{

DetectorConstruction::~DetectorConstruction() {
    delete m_parameterParser;
    //delete m_nist; // causes error
    delete m_water;
    delete m_water_basic;
    delete m_water_doped;
    delete m_steel;
    delete m_stainlessSteel;
    delete m_aluminum;
    delete m_isotope_Gd152;
    delete m_isotope_Gd154;
    delete m_isotope_Gd155;
    delete m_isotope_Gd156;
    delete m_isotope_Gd157;
    delete m_isotope_Gd158;
    delete m_isotope_Gd160;
    delete m_element_H;
    delete m_element_O;
    delete m_element_Gd;
    delete m_element_C;
    delete m_element_Fe;
    delete m_element_Cr;
    delete m_element_Ni;
    delete m_element_Mn;
    delete m_element_P;
    delete m_element_Si;
    delete m_element_S;
    delete m_element_Al;
    delete m_element_Gd_complete;
    delete m_water_basic_mpt;
    delete m_water_mpt;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    ConstructMaterials();
    
    G4bool checkOverlaps = true;
    G4double size_X=2000*m, size_Y=200*m, size_Z=200*m;

    G4Material* material = G4Material::GetMaterial( m_parameterParser->get_material() );
    G4cout << "Using " << material->GetName() << G4endl;

    G4Box* world_s = new G4Box( "world", size_X, size_Y, size_Z );
    G4LogicalVolume  * world_lv = new G4LogicalVolume( world_s, material, "world" );
    G4VPhysicalVolume* world_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), world_lv, "world", 0, false, 0, checkOverlaps);

    G4double size_dX;
    if( m_parameterParser->get_record_dEdX() ) {
        // size_dX = 0.00001 * m; // for real runs (10um)
        // size_dX = 0.001 * m; // for real runs (10mm)
        size_dX = m_parameterParser->get_stepVolumeWidth();
    } else
        size_dX = size_X; // one volume

    G4double x = -size_X / 2;
    G4Box* material_s = new G4Box( "material", size_dX/2, size_Y, size_Z );

    G4LogicalVolume* material_lv = new G4LogicalVolume( material_s, material, "material" );

    for( int i = 0; i < 20*m / size_dX; i++, x += size_dX )
        new G4PVPlacement( 0, G4ThreeVector( x, 0, 0 ), material_lv, "material", world_lv, true, i, checkOverlaps );

    return world_pv;
}

}
