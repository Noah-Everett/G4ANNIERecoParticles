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
   ~ParameterParser();
    
    void SetNewValue( G4UIcommand* command, G4String newValue );

    G4String get_material                (){ return m_material                ; }
    G4bool   get_make_tuple_dEdX         (){ return m_make_tuple_dEdX         ; }
    G4bool   get_make_tuple_emission     (){ return m_make_tuple_emission     ; }
    G4bool   get_make_tuple_transmittance(){ return m_make_tuple_transmittance; }
    G4bool   get_make_hist_dEdX          (){ return m_make_hist_dEdX          ; }
    G4bool   get_make_hist_emission      (){ return m_make_hist_emission      ; }
    G4bool   get_make_hist_transmittance (){ return m_make_hist_transmittance ; }

    G4bool get_record_dEdX         (){ return m_make_tuple_dEdX          || m_make_hist_dEdX         ; }
    G4bool get_record_emission     (){ return m_make_tuple_emission      || m_make_hist_emission     ; }
    G4bool get_record_transmittance(){ return m_make_tuple_transmittance || m_make_hist_transmittance; }

    void set_material                ( G4String& t_material              ){ m_material                 = t_material                ; }
    void set_make_tuple_dEdX         ( G4bool t_make_tuple_dEdX          ){ m_make_tuple_dEdX          = t_make_tuple_dEdX         ; }
    void set_make_tuple_emission     ( G4bool t_make_tuple_emission      ){ m_make_tuple_emission      = t_make_tuple_emission     ; }
    void set_make_tuple_transmittance( G4bool t_make_tuple_transmittance ){ m_make_tuple_transmittance = t_make_tuple_transmittance; }
    void set_make_hist_dEdX          ( G4bool t_make_hist_dEdX           ){ m_make_hist_dEdX           = t_make_hist_dEdX          ; }
    void set_make_hist_emission      ( G4bool t_make_hist_emission       ){ m_make_hist_emission       = t_make_hist_emission      ; }
    void set_make_hist_transmittance ( G4bool t_make_hist_transmittance  ){ m_make_hist_transmittance  = t_make_hist_transmittance ; }

  protected:
    G4UIcmdWithAString* m_parameter_material                { nullptr };
    G4UIcmdWithABool  * m_parameter_make_tuple_dEdX         { nullptr };
    G4UIcmdWithABool  * m_parameter_make_tuple_emission     { nullptr };
    G4UIcmdWithABool  * m_parameter_make_tuple_transmittance{ nullptr };
    G4UIcmdWithABool  * m_parameter_make_hist_dEdX          { nullptr };
    G4UIcmdWithABool  * m_parameter_make_hist_emission      { nullptr };
    G4UIcmdWithABool  * m_parameter_make_hist_transmittance { nullptr };

    G4String m_material                { "water" };
    G4bool   m_make_tuple_dEdX         { false   };
    G4bool   m_make_tuple_emission     { false   };
    G4bool   m_make_tuple_transmittance{ false   };
    G4bool   m_make_hist_dEdX          { false   };
    G4bool   m_make_hist_emission      { false   };
    G4bool   m_make_hist_transmittance { false   };
};

}

#endif