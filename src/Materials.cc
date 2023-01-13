#include "DetectorConstruction.hh"

namespace ANNIERecoParticles {

void DetectorConstruction::ConstructMaterials() {
    ConstructMaterials_water         ();
    ConstructMaterials_water_basic   ();
    ConstructMaterials_water_doped   ();
    ConstructMaterials_steel         ();
    ConstructMaterials_stainlessSteel();
    ConstructMaterials_aluminum      ();
    ConstructMaterials_C15H24        ();
    ConstructMaterials_C16H26        ();
    ConstructMaterials_C17H28        ();
    ConstructMaterials_C18H30        ();
    ConstructMaterials_C19H32        ();
    ConstructMaterials_LAB           ();
    ConstructMaterials_PPO           ();
    ConstructMaterials_WbLS_1pct     ();
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

void DetectorConstruction::ConstructMaterials_C15H24() {
    m_C15H24 = new G4Material( "C15H24", 0.867 * CLHEP::g / CLHEP::cm3, 2 );
    m_C15H24->AddElement        ( m_element_C, 0.8815 );
    m_C15H24->AddElement        ( m_element_H, 0.1185 );
    m_C15H24->SetChemicalFormula( "AROMATIC"          ); 
}

void DetectorConstruction::ConstructMaterials_C16H26() {
    m_C16H26 = new G4Material( "C16H26", 0.867 * CLHEP::g / CLHEP::cm3, 2 );
    m_C16H26->AddElement        ( m_element_C, 0.8799 );
    m_C16H26->AddElement        ( m_element_H, 0.1201 );
    m_C16H26->SetChemicalFormula( "AROMATIC"          ); 
}

void DetectorConstruction::ConstructMaterials_C17H28() {
    m_C17H28 = new G4Material( "C17H28", 0.867 * CLHEP::g / CLHEP::cm3, 2 );
    m_C17H28->AddElement        ( m_element_C, 0.8785 );
    m_C17H28->AddElement        ( m_element_H, 0.1215 );
    m_C17H28->SetChemicalFormula( "AROMATIC"          ); 
}

void DetectorConstruction::ConstructMaterials_C18H30() {
    m_C18H30 = new G4Material( "C18H30", 0.867 * CLHEP::g / CLHEP::cm3, 2 );
    m_C18H30->AddElement        ( m_element_C, 0.8772 );
    m_C18H30->AddElement        ( m_element_H, 0.1228 );
    m_C18H30->SetChemicalFormula( "AROMATIC"          ); 
}

void DetectorConstruction::ConstructMaterials_C19H32() {
    m_C19H32 = new G4Material( "C19H32", 0.867 * CLHEP::g / CLHEP::cm3, 2 );
    m_C19H32->AddElement        ( m_element_C, 0.8761 );
    m_C19H32->AddElement        ( m_element_H, 0.1239 );
    m_C19H32->SetChemicalFormula( "AROMATIC"          ); 
}

void DetectorConstruction::ConstructMaterials_LAB() {
    m_LAB = new G4Material( "LAB", 0.867 * CLHEP::g / CLHEP::cm3, 5 );
    m_LAB->AddMaterial( m_C15H24, 0.012 );
    m_LAB->AddMaterial( m_C16H26, 0.204 );
    m_LAB->AddMaterial( m_C17H28, 0.432 );
    m_LAB->AddMaterial( m_C18H30, 0.334 );
    m_LAB->AddMaterial( m_C19H32, 0.018 );
}

void DetectorConstruction::ConstructMaterials_PPO() {
    // missing from RAT???
}

void DetectorConstruction::ConstructMaterials_WbLS_1pct() {
    m_WbLS_1pct = new G4Material( "WbLS_1pct", 1.0 * CLHEP::g / CLHEP::cm3, /*3*/2 );
    m_WbLS_1pct->AddMaterial( m_LAB  , /*0.00997*/0.01 );
    // m_WbLS_1pct->AddMaterial( m_PPO  , 2.3e-05 );
    m_WbLS_1pct->AddMaterial( m_water, 0.99    );

    // m_WbLS_mpt->AddConstProperty( "LIGHT_YEILD"       , m_WbLS_mpt_lightYeild                                                                                            );
    // m_WbLS_mpt->AddProperty     ( "SCINTWAVEFORM"     , m_WbLS_mpt_scintWaveform_energies     , m_WbLS_mpt_scintWaveform_values     , m_WbLS_mpt_scintWaveform_size      );
    // m_WbLS_mpt->AddConstProperty( "SCINT_RISE_TIME"   , m_WbLS_mpt_scintRiseTime                                                                                         );
    // m_WbLS_mpt->AddProperty     ( "SCINTWAVEFORMalpha", m_WbLS_mpt_scintWaveformAlpha_energies, m_WbLS_mpt_scintWaveformAlpha_values, m_WbLS_mpt_scintWaveformAlpha_size );
    // m_WbLS_mpt->AddProperty     ( "SCINTMOD"          , m_WbLS_mpt_scintMod_energies          , m_WbLS_mpt_scintMod_values          , m_WbLS_mpt_scintMod_size           );
    // m_WbLS_mpt->AddProperty     ( "SCINTMODalpha"     , m_WbLS_mpt_scintModAlpha_energies     , m_WbLS_mpt_scintModAlpha_values     , m_WbLS_mpt_scintModAlpha_size      );
    // m_WbLS_mpt->AddProperty     ( "SCINTMODneutron"   , m_WbLS_mpt_scintModNeutron_energies   , m_WbLS_mpt_scintModNeutron_values   , m_WbLS_mpt_scintModNeutron_size    );
    m_WbLS_mpt->AddProperty     ( "RINDEX"            , m_WbLS_mpt_refIndex_energies          , m_WbLS_mpt_refIndex_values          , m_WbLS_mpt_refIndex_size           );
    // m_WbLS_mpt->AddProperty     ( "SCINTILLATION"     , m_WbLS_mpt_scintillation_energies     , m_WbLS_mpt_scintillation_values     , m_WbLS_mpt_scintillation_size      );
    // m_WbLS_mpt->AddProperty     ( "SCINTILLATION_WLS" , m_WbLS_mpt_scintillationWLS_energies  , m_WbLS_mpt_scintillationWLS_values  , m_WbLS_mpt_scintillationWLS_size   );
    m_WbLS_mpt->AddProperty     ( "ABSLENGTH"         , m_WbLS_mpt_absLength_energies         , m_WbLS_mpt_absLength_values         , m_WbLS_mpt_absLength_size          );
    // m_WbLS_mpt->AddProperty     ( "RSLENGTH"          , m_WbLS_mpt_rsLength_energies          , m_WbLS_mpt_rsLength_values          , m_WbLS_mpt_rsLength_size           );
    // m_WbLS_mpt->AddProperty     ( "REEMISSION_PROB"   , m_WbLS_mpt_reemissionProb_energies    , m_WbLS_mpt_reemissionProb_values    , m_WbLS_mpt_reemissionProb_size     );
    m_WbLS_1pct->SetMaterialPropertiesTable( m_WbLS_mpt );
}

}