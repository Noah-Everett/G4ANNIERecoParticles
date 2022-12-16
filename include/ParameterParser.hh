#ifndef ParameterParser_h
#define ParameterParser_h

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImessenger.hh"

namespace ANNIERecoParticles
{

class ParameterParser : public G4UImessenger
{
  public:
    ParameterParser();
   ~ParameterParser(){ delete m_parameter_material;
                       delete m_parameter_record_dEdX;
                       delete m_parameter_record_gammas; };

    G4String get_material(){ return m_material; };
    void set_material( G4String t_material ){ m_material = t_material; };

    G4bool get_record_dEdX(){ return m_record_dEdX; };
    void set_record_dEdX( G4bool t_record_dEdX ){ m_record_dEdX = t_record_dEdX; };

    G4bool get_record_gammas(){ return m_record_gammas; };
    void set_record_gammas( G4bool t_record_gammas ){ m_record_gammas = t_record_gammas; };

    void SetNewValue( G4UIcommand* command, G4String newValue );

  protected:
    G4UIcmdWithAString* m_parameter_material      = nullptr;
    G4UIcmdWithABool  * m_parameter_record_dEdX   = nullptr;
    G4UIcmdWithABool  * m_parameter_record_gammas = nullptr;

    G4String m_material      = "water";
    G4bool   m_record_dEdX   = 0;
    G4bool   m_record_gammas = 1;
};

}

#endif