#include "DetectorConstruction.hh"

namespace ANNIERecoParticles {

void DetectorConstruction::ConstructMaterials() {
    ConstructMaterials_water();
    ConstructMaterials_water_basic();
    ConstructMaterials_water_doped();
}

void DetectorConstruction::ConstructMaterials_water() {
    m_water = new G4Material( "water", 1.00*CLHEP::g/CLHEP::cm3, 2 );
    m_water->AddElement( m_element_H, 2 );
    m_water->AddElement( m_element_O, 1 );

    if( !m_water_mpt->ConstPropertyExists( "RINDEX" ) ) 
        m_water_mpt->AddProperty( "RINDEX"   , m_water_mpt_energies, m_water_mpt_rindices  , m_size_mpt_water );
    if( !m_water_mpt->ConstPropertyExists( "ABSLENGTH" ) ) 
        m_water_mpt->AddProperty( "ABSLENGTH", m_water_mpt_energies, m_water_mpt_absorption, m_size_mpt_water );
    if( !m_water_mpt->ConstPropertyExists( "RAYLEIGH" ) ) 
        m_water_mpt->AddProperty( "RAYLEIGH" , m_water_mpt_energies, m_water_mpt_rayleigh  , m_size_mpt_water );
    m_water->SetMaterialPropertiesTable( m_water_mpt );
}

void DetectorConstruction::ConstructMaterials_water_basic() {
    m_water_basic = m_nist->FindOrBuildMaterial( "G4_WATER" );
    m_water_basic->SetName( "water_basic" );

    m_water_basic_mpt = new G4MaterialPropertiesTable();
    m_water_basic_mpt->AddProperty( "RINDEX", m_water_mpt_energies, m_water_mpt_rindices, 4 );
    m_water_basic->SetMaterialPropertiesTable( m_water_basic_mpt );
}

void DetectorConstruction::ConstructMaterials_water_doped() {
    m_element_Gd_complete->AddIsotope( m_isotope_Gd152,  0.2 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd154,  2.2 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd155, 14.9 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd156, 20.6 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd157, 15.7 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd158, 24.7 * perCent );
    m_element_Gd_complete->AddIsotope( m_isotope_Gd160, 21.7 * perCent );

    m_water_doped = new G4Material( "water_doped", 1.00 * CLHEP::g / CLHEP::cm3, 2 );
    m_water_doped->AddMaterial( m_water     , 99.9 * CLHEP::perCent );
    m_water_doped->AddElement ( m_element_Gd, 0.1  * CLHEP::perCent );
    
    if( !m_water_mpt->ConstPropertyExists( "RINDEX" ) ) 
        m_water_mpt->AddProperty( "RINDEX"   , m_water_mpt_energies, m_water_mpt_rindices  , m_size_mpt_water );
    if( !m_water_mpt->ConstPropertyExists( "ABSLENGTH" ) ) 
        m_water_mpt->AddProperty( "ABSLENGTH", m_water_mpt_energies, m_water_mpt_absorption, m_size_mpt_water );
    if( !m_water_mpt->ConstPropertyExists( "RAYLEIGH" ) ) 
        m_water_mpt->AddProperty( "RAYLEIGH" , m_water_mpt_energies, m_water_mpt_rayleigh  , m_size_mpt_water );
    m_water_doped->SetMaterialPropertiesTable( m_water_mpt );
}

void DetectorConstruction::ConstructMaterials_steel() {
    m_steel = new G4Material( "Steel", 7.8 * CLHEP::g / CLHEP::cm3, 2 );
    m_steel->AddElement( m_element_C , 1.  * CLHEP::perCent );
    m_steel->AddElement( m_element_Fe, 99. * CLHEP::perCent );
}

void DetectorConstruction::ConstructMaterials_stainlessSteel() {
    m_stainlessSteel = new G4Material( "StainlessSteel", 7.81 * CLHEP::g / CLHEP::cm3, 8 );
    m_stainlessSteel->AddElement( m_element_Fe, 70.44 * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_Cr, 18    * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_C , 0.08  * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_Ni, 8     * CLHEP::perCent ); 
    m_stainlessSteel->AddElement( m_element_P , 0.45  * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_Si, 1     * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_Mn, 2     * CLHEP::perCent );
    m_stainlessSteel->AddElement( m_element_S , 0.03  * CLHEP::perCent );
}

void DetectorConstruction::ConstructMaterials_aluminum() {
  m_aluminum = new G4Material( "Aluminum", 2.7 * CLHEP::g / CLHEP::cm3, 1 );
  m_aluminum->AddElement( m_element_Al, 1 );
}

}