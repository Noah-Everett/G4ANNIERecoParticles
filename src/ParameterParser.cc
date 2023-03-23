#include "ParameterParser.hh"

namespace ANNIERecoParticles 
{

ParameterParser::~ParameterParser() {
    if( m_parameter_material                 ) delete m_parameter_material                ;
    if( m_parameter_stepVolumeWidth          ) delete m_parameter_stepVolumeWidth         ;
    if( m_parameter_make_tuple_dEdX          ) delete m_parameter_make_tuple_dEdX         ;
    if( m_parameter_make_tuple_emission      ) delete m_parameter_make_tuple_emission     ;
    if( m_parameter_make_tuple_transmittance ) delete m_parameter_make_tuple_transmittance;
    if( m_parameter_make_hist_dEdX           ) delete m_parameter_make_hist_dEdX          ;
    if( m_parameter_make_hist_emission       ) delete m_parameter_make_hist_emission      ;
    if( m_parameter_make_hist_transmittance  ) delete m_parameter_make_hist_transmittance ;
}

ParameterParser::ParameterParser() {
    m_parameter_material                 = new G4UIcmdWithAString       ( "/ANNIERecoParticles/material"                , this );
    m_parameter_stepVolumeWidth          = new G4UIcmdWithADoubleAndUnit( "/ANNIERecoParticles/stepVolumeWidth"         , this );
    m_parameter_make_tuple_dEdX          = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/tuple/dEdX"         , this );
    m_parameter_make_tuple_emission      = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/tuple/emission"     , this );
    m_parameter_make_tuple_transmittance = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/tuple/transmittance", this );
    m_parameter_make_hist_dEdX           = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/hist/dEdX"          , this );
    m_parameter_make_hist_emission       = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/hist/emission"      , this );
    m_parameter_make_hist_transmittance  = new G4UIcmdWithABool         ( "/ANNIERecoParticles/make/hist/transmittance" , this );

    m_parameter_material                ->SetDefaultValue( "water" );
    m_parameter_stepVolumeWidth         ->SetDefaultValue( 0.01    );
    m_parameter_make_tuple_dEdX         ->SetDefaultValue( false   );
    m_parameter_make_tuple_emission     ->SetDefaultValue( false   );
    m_parameter_make_tuple_transmittance->SetDefaultValue( false   );
    m_parameter_make_hist_dEdX          ->SetDefaultValue( false   );
    m_parameter_make_hist_emission      ->SetDefaultValue( false   );
    m_parameter_make_hist_transmittance ->SetDefaultValue( false   );
    
    m_parameter_material->SetCandidates( "water water_basic water_doped WbLS_1pct tankSteel MRDIron" );
}

void ParameterParser::SetNewValue( G4UIcommand* command, G4String newValue ) {
    if( command == m_parameter_material ) {
        set_material( newValue );
        G4cout << "Setting `material' to " << newValue << G4endl;
    } else if( command == m_parameter_stepVolumeWidth ) {
        set_stepVolumeWidth( m_parameter_stepVolumeWidth->GetNewDoubleValue( newValue ) );
        G4cout << "Setting step volume width to " << newValue << " (" << m_parameter_stepVolumeWidth->GetNewDoubleValue( newValue ) << ")."  << G4endl;
    } else if( command == m_parameter_make_tuple_dEdX ) {
        set_make_tuple_dEdX( m_parameter_make_tuple_dEdX->GetNewBoolValue( newValue ) );
        if( m_make_tuple_dEdX ) G4cout << "Enabling making dEdX tuple."  << G4endl;
        else                    G4cout << "Disabling making dEdX tuple." << G4endl;
    } else if( command == m_parameter_make_tuple_emission ) {
        set_make_tuple_emission( m_parameter_make_tuple_emission->GetNewBoolValue( newValue ) );
        if( m_make_tuple_emission ) G4cout << "Enabling making emission tuple."  << G4endl;
        else                        G4cout << "Disabling making emission tuple." << G4endl;
    } else if( command == m_parameter_make_tuple_transmittance ) {
        set_make_tuple_transmittance( m_parameter_make_tuple_transmittance->GetNewBoolValue( newValue ) );
        if( m_make_tuple_transmittance ) G4cout << "Enabling making transmittance tuple."  << G4endl;
        else                             G4cout << "Disabling making transmittance tuple." << G4endl;
    } else if( command == m_parameter_make_hist_dEdX ) {
        set_make_hist_dEdX( m_parameter_make_hist_dEdX->GetNewBoolValue( newValue ) );
        if( m_make_hist_dEdX ) G4cout << "Enabling making dEdX hist."  << G4endl;
        else                   G4cout << "Disabling making dEdX hist." << G4endl;
    } else if( command == m_parameter_make_hist_emission ) {
        set_make_hist_emission( m_parameter_make_hist_emission->GetNewBoolValue( newValue ) );
        if( m_make_hist_emission ) G4cout << "Enabling making emission hist."  << G4endl;
        else                       G4cout << "Disabling making emission hist." << G4endl;
    } else if( command == m_parameter_make_hist_transmittance ) {
        set_make_hist_transmittance( m_parameter_make_hist_transmittance->GetNewBoolValue( newValue ) );
        if( m_make_hist_transmittance ) G4cout << "Enabling making transmittance hist."  << G4endl;
        else                            G4cout << "Disabling making transmittance hist." << G4endl;
    }
}
    
// G4bool ParameterParser::get_record_dEdX() {
//     if( m_make_tuple_dEdX || m_make_hist_dEdX )
//         return true;
//     return false;
// }

// G4bool ParameterParser::get_record_emission() {
//     if( m_make_tuple_emission || m_make_hist_emission )
//         return true;
//     return false;
// }

// G4bool ParameterParser::get_record_transmittance() {
//     if( m_make_tuple_transmittance || m_make_hist_transmittance )
//         return true;
//     return false;
// }

}