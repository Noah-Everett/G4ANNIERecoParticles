#include "ParameterParser.hh"

namespace ANNIERecoParticles 
{

ParameterParser::ParameterParser() {
  m_parameter_material = new G4UIcmdWithAString( "/ANNIERecoParticles/material", this );
  m_parameter_material->SetDefaultValue( "water" );
  m_parameter_material->SetCandidates( "water water_basic water_doped WbLS tankSteel MRDIron" );

  m_parameter_record_dEdX = new G4UIcmdWithABool( "/ANNIERecoParticles/record/dEdX", this );
  m_parameter_record_dEdX->SetDefaultValue( false );

  m_parameter_record_gammas = new G4UIcmdWithABool( "/ANNIERecoParticles/record/gammas", this );
  m_parameter_record_gammas->SetDefaultValue( true );
}

void ParameterParser::SetNewValue( G4UIcommand* command, G4String newValue ) {
    if( command == m_parameter_material ) {
        set_material( newValue );
        G4cout << "Setting `material' to " << newValue << G4endl;
    } else if( command == m_parameter_record_dEdX ) {
        set_record_dEdX( m_parameter_record_dEdX->GetNewBoolValue( newValue ) );
        G4cout << "Setting `record_dEdX' to " << newValue << G4endl;
    } else if( command == m_parameter_record_gammas ) {
        set_record_gammas( m_parameter_record_gammas->GetNewBoolValue( newValue ) );
        G4cout << "Setting `record_gammas' to " << newValue << G4endl;
    }
}

}