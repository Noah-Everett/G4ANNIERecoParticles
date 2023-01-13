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

#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"


#include "ParameterParser.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace ANNIERecoParticles {

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction( ParameterParser* t_parameterParser ){ m_parameterParser = t_parameterParser; }
   ~DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

protected:
    void ConstructMaterials               ();
    void ConstructMaterials_water         ();
    void ConstructMaterials_water_basic   ();
    void ConstructMaterials_water_doped   ();
    void ConstructMaterials_steel         ();
    void ConstructMaterials_stainlessSteel();
    void ConstructMaterials_aluminum      ();
    void ConstructMaterials_C15H24        ();
    void ConstructMaterials_C16H26        ();
    void ConstructMaterials_C17H28        ();
    void ConstructMaterials_C18H30        ();
    void ConstructMaterials_C19H32        ();
    void ConstructMaterials_LAB           ();
    void ConstructMaterials_PPO           ();
    void ConstructMaterials_WbLS_1pct     ();

    ParameterParser* m_parameterParser;

    G4NistManager* m_nist{ G4NistManager::Instance() };

    G4Material* m_water         { nullptr };
    G4Material* m_water_basic   { nullptr };
    G4Material* m_water_doped   { nullptr };
    G4Material* m_steel         { nullptr };
    G4Material* m_stainlessSteel{ nullptr };
    G4Material* m_aluminum      { nullptr };
    G4Material* m_C15H24        { nullptr };
    G4Material* m_C16H26        { nullptr };
    G4Material* m_C17H28        { nullptr };
    G4Material* m_C18H30        { nullptr };
    G4Material* m_C19H32        { nullptr };
    G4Material* m_LAB           { nullptr };
    G4Material* m_PPO           { nullptr };
    G4Material* m_WbLS_1pct     { nullptr };

    G4Isotope* m_isotope_Gd152{ new G4Isotope( "Gd152", 64, 152, 152.0 * g / mole ) };
    G4Isotope* m_isotope_Gd154{ new G4Isotope( "Gd154", 64, 154, 154.0 * g / mole ) };
    G4Isotope* m_isotope_Gd155{ new G4Isotope( "Gd155", 64, 155, 155.0 * g / mole ) };
    G4Isotope* m_isotope_Gd156{ new G4Isotope( "Gd156", 64, 156, 156.0 * g / mole ) };
    G4Isotope* m_isotope_Gd157{ new G4Isotope( "Gd157", 64, 157, 157.0 * g / mole ) };
    G4Isotope* m_isotope_Gd158{ new G4Isotope( "Gd158", 64, 158, 158.0 * g / mole ) };
    G4Isotope* m_isotope_Gd160{ new G4Isotope( "Gd160", 64, 160, 160.0 * g / mole ) };

    G4Element* m_element_H { new G4Element( "Hydrogen"  , "H" , 1 , 1.01    * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_O { new G4Element( "Oxygen"    , "O" , 8 , 16.00   * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Gd{ new G4Element( "Gadolinium", "Gd", 64, 157.25  * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_C { new G4Element( "Carbon"    , "C" , 6 , 12.01   * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Fe{ new G4Element( "Iron"      , "Fe", 26, 55.85   * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Cr{ new G4Element( "Chromium"  , "Cr", 24, 51.9961 * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Ni{ new G4Element( "Nickel"    , "Ni", 28, 58.6934 * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Mn{ new G4Element( "Manganese" , "Mn", 25, 54.938  * CLHEP::g / CLHEP::mole ) }; 
    G4Element* m_element_P { new G4Element( "Phosphore" , "P" , 15, 30.974  * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Si{ new G4Element( "Silicon"   , "Si", 14, 28.09   * CLHEP::g / CLHEP::mole ) }; 
    G4Element* m_element_S { new G4Element( "Sulphur"   , "S" , 16, 32.065  * CLHEP::g / CLHEP::mole ) };
    G4Element* m_element_Al{ new G4Element( "Aluminum"  , "Al", 13, 26.98   * CLHEP::g / CLHEP::mole ) };  
    G4Element* m_element_Gd_complete { new G4Element( "Gadolinium", "Gd", 7 ) };
  
    G4MaterialPropertiesTable* m_water_mpt      { new G4MaterialPropertiesTable() };
    G4MaterialPropertiesTable* m_water_basic_mpt{ new G4MaterialPropertiesTable() };
    G4MaterialPropertiesTable* m_WbLS_mpt       { new G4MaterialPropertiesTable() };
  
    static const G4int m_size_mpt_water{ 60 };
    G4double m_ABWFF{ 1.30 };
    G4double m_RAYFF{ 0.75 };
    G4double m_MIEFF{ 0.0  };
    G4double m_water_mpt_energies[ m_size_mpt_water ]{ 1.56962e-09*CLHEP::GeV, 1.58974e-09*CLHEP::GeV, 1.61039e-09*CLHEP::GeV, 1.63157e-09*CLHEP::GeV, 
                                                       1.65333e-09*CLHEP::GeV, 1.67567e-09*CLHEP::GeV, 1.69863e-09*CLHEP::GeV, 1.72222e-09*CLHEP::GeV, 
                                                       1.74647e-09*CLHEP::GeV, 1.77142e-09*CLHEP::GeV, 1.79710e-09*CLHEP::GeV, 1.82352e-09*CLHEP::GeV, 
                                                       1.85074e-09*CLHEP::GeV, 1.87878e-09*CLHEP::GeV, 1.90769e-09*CLHEP::GeV, 1.93749e-09*CLHEP::GeV, 
                                                       1.96825e-09*CLHEP::GeV, 1.99999e-09*CLHEP::GeV, 2.03278e-09*CLHEP::GeV, 2.06666e-09*CLHEP::GeV,
                                                       2.10169e-09*CLHEP::GeV, 2.13793e-09*CLHEP::GeV, 2.17543e-09*CLHEP::GeV, 2.21428e-09*CLHEP::GeV, 
                                                       2.25454e-09*CLHEP::GeV, 2.29629e-09*CLHEP::GeV, 2.33962e-09*CLHEP::GeV, 2.38461e-09*CLHEP::GeV, 
                                                       2.43137e-09*CLHEP::GeV, 2.47999e-09*CLHEP::GeV, 2.53061e-09*CLHEP::GeV, 2.58333e-09*CLHEP::GeV, 
                                                       2.63829e-09*CLHEP::GeV, 2.69565e-09*CLHEP::GeV, 2.75555e-09*CLHEP::GeV, 2.81817e-09*CLHEP::GeV, 
                                                       2.88371e-09*CLHEP::GeV, 2.95237e-09*CLHEP::GeV, 3.02438e-09*CLHEP::GeV, 3.09999e-09*CLHEP::GeV,
                                                       3.17948e-09*CLHEP::GeV, 3.26315e-09*CLHEP::GeV, 3.35134e-09*CLHEP::GeV, 3.44444e-09*CLHEP::GeV, 
                                                       3.54285e-09*CLHEP::GeV, 3.64705e-09*CLHEP::GeV, 3.75757e-09*CLHEP::GeV, 3.87499e-09*CLHEP::GeV, 
                                                       3.99999e-09*CLHEP::GeV, 4.13332e-09*CLHEP::GeV, 4.27585e-09*CLHEP::GeV, 4.42856e-09*CLHEP::GeV, 
                                                       4.59258e-09*CLHEP::GeV, 4.76922e-09*CLHEP::GeV, 4.95999e-09*CLHEP::GeV, 5.16665e-09*CLHEP::GeV, 
                                                       5.39129e-09*CLHEP::GeV, 5.63635e-09*CLHEP::GeV, 5.90475e-09*CLHEP::GeV, 6.19998e-09*CLHEP::GeV };
    G4double m_water_mpt_rindices[ m_size_mpt_water ]{ 1.32885, 1.32906, 1.32927, 1.32948, 1.3297 , 1.32992, 1.33014,
                                                       1.33037, 1.3306 , 1.33084, 1.33109, 1.33134, 1.3316 , 1.33186, 1.33213,
                                                       1.33241, 1.3327 , 1.33299, 1.33329, 1.33361, 1.33393, 1.33427, 1.33462,
                                                       1.33498, 1.33536, 1.33576, 1.33617, 1.3366 , 1.33705, 1.33753, 1.33803,
                                                       1.33855, 1.33911, 1.3397 , 1.34033, 1.341  , 1.34172, 1.34248, 1.34331,
                                                       1.34419, 1.34515, 1.3462 , 1.34733, 1.34858, 1.34994, 1.35145, 1.35312,
                                                       1.35498, 1.35707, 1.35943, 1.36211, 1.36518, 1.36872, 1.37287, 1.37776,
                                                       1.38362, 1.39074, 1.39956, 1.41075, 1.42535 };
    G4double m_water_mpt_absorption[ m_size_mpt_water ]{ 16.1419*CLHEP::cm*m_ABWFF,  18.278*CLHEP::cm*m_ABWFF, 21.0657*CLHEP::cm*m_ABWFF, 24.8568*CLHEP::cm*m_ABWFF, 30.3117*CLHEP::cm*m_ABWFF,
                                                         38.8341*CLHEP::cm*m_ABWFF, 54.0231*CLHEP::cm*m_ABWFF, 81.2306*CLHEP::cm*m_ABWFF, 120.909*CLHEP::cm*m_ABWFF, 160.238*CLHEP::cm*m_ABWFF,
                                                         193.771*CLHEP::cm*m_ABWFF, 215.017*CLHEP::cm*m_ABWFF, 227.747*CLHEP::cm*m_ABWFF,  243.85*CLHEP::cm*m_ABWFF, 294.036*CLHEP::cm*m_ABWFF,
                                                         321.647*CLHEP::cm*m_ABWFF,  342.81*CLHEP::cm*m_ABWFF, 362.827*CLHEP::cm*m_ABWFF, 378.041*CLHEP::cm*m_ABWFF, 449.378*CLHEP::cm*m_ABWFF,
                                                         739.434*CLHEP::cm*m_ABWFF, 1114.23*CLHEP::cm*m_ABWFF, 1435.56*CLHEP::cm*m_ABWFF, 1611.06*CLHEP::cm*m_ABWFF, 1764.18*CLHEP::cm*m_ABWFF,
                                                         2100.95*CLHEP::cm*m_ABWFF,  2292.9*CLHEP::cm*m_ABWFF, 2431.33*CLHEP::cm*m_ABWFF,  3053.6*CLHEP::cm*m_ABWFF, 4838.23*CLHEP::cm*m_ABWFF,
                                                         6539.65*CLHEP::cm*m_ABWFF, 7682.63*CLHEP::cm*m_ABWFF, 9137.28*CLHEP::cm*m_ABWFF, 12220.9*CLHEP::cm*m_ABWFF, 15270.7*CLHEP::cm*m_ABWFF,
                                                         19051.5*CLHEP::cm*m_ABWFF, 23671.3*CLHEP::cm*m_ABWFF, 29191.1*CLHEP::cm*m_ABWFF, 35567.9*CLHEP::cm*m_ABWFF,   42583*CLHEP::cm*m_ABWFF,
                                                         49779.6*CLHEP::cm*m_ABWFF, 56465.3*CLHEP::cm*m_ABWFF,   61830*CLHEP::cm*m_ABWFF, 65174.6*CLHEP::cm*m_ABWFF, 66143.7*CLHEP::cm*m_ABWFF,
                                                           64820*CLHEP::cm*m_ABWFF,   61635*CLHEP::cm*m_ABWFF, 57176.2*CLHEP::cm*m_ABWFF, 52012.1*CLHEP::cm*m_ABWFF, 46595.7*CLHEP::cm*m_ABWFF,
                                                         41242.1*CLHEP::cm*m_ABWFF, 36146.3*CLHEP::cm*m_ABWFF, 31415.4*CLHEP::cm*m_ABWFF, 27097.8*CLHEP::cm*m_ABWFF, 23205.7*CLHEP::cm*m_ABWFF,
                                                         19730.3*CLHEP::cm*m_ABWFF, 16651.6*CLHEP::cm*m_ABWFF, 13943.6*CLHEP::cm*m_ABWFF, 11578.1*CLHEP::cm*m_ABWFF, 9526.13*CLHEP::cm*m_ABWFF };
    G4double m_water_mpt_rayleigh[ m_size_mpt_water ]{ 386929*CLHEP::cm*m_RAYFF,  366249*CLHEP::cm*m_RAYFF,  346398*CLHEP::cm*m_RAYFF,  327355*CLHEP::cm*m_RAYFF,  309097*CLHEP::cm*m_RAYFF,
                                                       291603*CLHEP::cm*m_RAYFF,  274853*CLHEP::cm*m_RAYFF,  258825*CLHEP::cm*m_RAYFF,  243500*CLHEP::cm*m_RAYFF,  228856*CLHEP::cm*m_RAYFF,
                                                       214873*CLHEP::cm*m_RAYFF,  201533*CLHEP::cm*m_RAYFF,  188816*CLHEP::cm*m_RAYFF,  176702*CLHEP::cm*m_RAYFF,  165173*CLHEP::cm*m_RAYFF,
                                                       154210*CLHEP::cm*m_RAYFF,  143795*CLHEP::cm*m_RAYFF,  133910*CLHEP::cm*m_RAYFF,  124537*CLHEP::cm*m_RAYFF,  115659*CLHEP::cm*m_RAYFF,
                                                       107258*CLHEP::cm*m_RAYFF, 99318.2*CLHEP::cm*m_RAYFF, 91822.2*CLHEP::cm*m_RAYFF,   84754*CLHEP::cm*m_RAYFF, 78097.3*CLHEP::cm*m_RAYFF,
                                                      71836.5*CLHEP::cm*m_RAYFF,   65956*CLHEP::cm*m_RAYFF, 60440.6*CLHEP::cm*m_RAYFF, 55275.4*CLHEP::cm*m_RAYFF, 50445.6*CLHEP::cm*m_RAYFF,
                                                        45937*CLHEP::cm*m_RAYFF, 41735.2*CLHEP::cm*m_RAYFF, 37826.6*CLHEP::cm*m_RAYFF, 34197.6*CLHEP::cm*m_RAYFF, 30834.9*CLHEP::cm*m_RAYFF,
                                                      27725.4*CLHEP::cm*m_RAYFF, 24856.6*CLHEP::cm*m_RAYFF, 22215.9*CLHEP::cm*m_RAYFF, 19791.3*CLHEP::cm*m_RAYFF, 17570.9*CLHEP::cm*m_RAYFF,
                                                        15543*CLHEP::cm*m_RAYFF, 13696.6*CLHEP::cm*m_RAYFF, 12020.5*CLHEP::cm*m_RAYFF, 10504.1*CLHEP::cm*m_RAYFF, 9137.15*CLHEP::cm*m_RAYFF,
                                                      7909.45*CLHEP::cm*m_RAYFF,  6811.3*CLHEP::cm*m_RAYFF, 5833.25*CLHEP::cm*m_RAYFF,  4966.2*CLHEP::cm*m_RAYFF, 4201.36*CLHEP::cm*m_RAYFF,
                                                      3530.28*CLHEP::cm*m_RAYFF, 2944.84*CLHEP::cm*m_RAYFF, 2437.28*CLHEP::cm*m_RAYFF, 2000.18*CLHEP::cm*m_RAYFF,  1626.5*CLHEP::cm*m_RAYFF,
                                                      1309.55*CLHEP::cm*m_RAYFF, 1043.03*CLHEP::cm*m_RAYFF, 821.016*CLHEP::cm*m_RAYFF,  637.97*CLHEP::cm*m_RAYFF, 488.754*CLHEP::cm*m_RAYFF };
    G4double m_water_mpt_mie[ m_size_mpt_water ]{ 7790020*CLHEP::cm*m_MIEFF, 7403010*CLHEP::cm*m_MIEFF, 7030610*CLHEP::cm*m_MIEFF, 6672440*CLHEP::cm*m_MIEFF, 6328120*CLHEP::cm*m_MIEFF,
                                                  5997320*CLHEP::cm*m_MIEFF, 5679650*CLHEP::cm*m_MIEFF, 5374770*CLHEP::cm*m_MIEFF, 5082340*CLHEP::cm*m_MIEFF, 4802000*CLHEP::cm*m_MIEFF,
                                                  4533420*CLHEP::cm*m_MIEFF, 4276280*CLHEP::cm*m_MIEFF, 4030220*CLHEP::cm*m_MIEFF, 3794950*CLHEP::cm*m_MIEFF, 3570120*CLHEP::cm*m_MIEFF,
                                                  3355440*CLHEP::cm*m_MIEFF, 3150590*CLHEP::cm*m_MIEFF, 2955270*CLHEP::cm*m_MIEFF, 2769170*CLHEP::cm*m_MIEFF, 2592000*CLHEP::cm*m_MIEFF,
                                                  2423470*CLHEP::cm*m_MIEFF, 2263300*CLHEP::cm*m_MIEFF, 2111200*CLHEP::cm*m_MIEFF, 1966900*CLHEP::cm*m_MIEFF, 1830120*CLHEP::cm*m_MIEFF,
                                                  1700610*CLHEP::cm*m_MIEFF, 1578100*CLHEP::cm*m_MIEFF, 1462320*CLHEP::cm*m_MIEFF, 1353040*CLHEP::cm*m_MIEFF, 1250000*CLHEP::cm*m_MIEFF,
                                                  1152960*CLHEP::cm*m_MIEFF, 1061680*CLHEP::cm*m_MIEFF,  975936*CLHEP::cm*m_MIEFF,  895491*CLHEP::cm*m_MIEFF,  820125*CLHEP::cm*m_MIEFF,
                                                   749619*CLHEP::cm*m_MIEFF,  683760*CLHEP::cm*m_MIEFF,  622339*CLHEP::cm*m_MIEFF,  565152*CLHEP::cm*m_MIEFF,  512000*CLHEP::cm*m_MIEFF,
                                                   462688*CLHEP::cm*m_MIEFF,  417027*CLHEP::cm*m_MIEFF,  374832*CLHEP::cm*m_MIEFF,  335923*CLHEP::cm*m_MIEFF,  300125*CLHEP::cm*m_MIEFF,
                                                   267267*CLHEP::cm*m_MIEFF,  237184*CLHEP::cm*m_MIEFF,  209715*CLHEP::cm*m_MIEFF,  184704*CLHEP::cm*m_MIEFF,  162000*CLHEP::cm*m_MIEFF,
                                                   141456*CLHEP::cm*m_MIEFF,  122931*CLHEP::cm*m_MIEFF,  106288*CLHEP::cm*m_MIEFF, 91395.2*CLHEP::cm*m_MIEFF,   78125*CLHEP::cm*m_MIEFF, 
                                                  66355.2*CLHEP::cm*m_MIEFF, 55968.2*CLHEP::cm*m_MIEFF, 46851.2*CLHEP::cm*m_MIEFF, 38896.2*CLHEP::cm*m_MIEFF,   32000*CLHEP::cm*m_MIEFF };
    G4double m_water_basic_mpt_energies[ 4 ]{ 2.00*eV, 2.87*eV, 2.90*eV, 3.47*eV };
    G4double m_water_basic_mpt_rindices[ 4 ]{ 1.333, 1.333, 1.333, 1.333 };

    G4double m_c { 299792458       * CLHEP::m  / CLHEP::s / CLHEP::m * CLHEP::nm };
    G4double m_h { 4.135667696e-15 * CLHEP::eV * CLHEP::s };
    G4double m_hc{ m_h * m_c                              };
    G4double m_WbLS_mpt_lightYeild{ 95.00 };
    static const int m_WbLS_mpt_scintWaveform_size{ 3 };
    G4double m_WbLS_mpt_scintWaveform_energies[ m_WbLS_mpt_scintWaveform_size ]{ m_hc / -2.01, m_hc / -12.73, m_hc / -116.86 };
    G4double m_WbLS_mpt_scintWaveform_values[ m_WbLS_mpt_scintWaveform_size ]{ 0.987, 0.012, 0.001 };
    G4double m_WbLS_mpt_scintRiseTime{ 0.25 }; // units????
    static const int m_WbLS_mpt_scintWaveformAlpha_size{ 3 };
    G4double m_WbLS_mpt_scintWaveformAlpha_energies[ m_WbLS_mpt_scintWaveformAlpha_size ]{ m_hc / -2.01, m_hc / -12.73, m_hc / -116.86 };
    G4double m_WbLS_mpt_scintWaveformAlpha_values[ m_WbLS_mpt_scintWaveformAlpha_size ]{ 0.987, 0.012, 0.001 };
    static const int m_WbLS_mpt_scintMod_size{ 1 };
    G4double m_WbLS_mpt_scintMod_energies[ m_WbLS_mpt_scintMod_size ]{ 1.0 }; // units???
    G4double m_WbLS_mpt_scintMod_values[ m_WbLS_mpt_scintMod_size ]{ 0.0798 }; // units???
    static const int m_WbLS_mpt_scintModAlpha_size{ 1 };
    G4double m_WbLS_mpt_scintModAlpha_energies[ m_WbLS_mpt_scintModAlpha_size ]{ 1.0 }; // units???
    G4double m_WbLS_mpt_scintModAlpha_values[ m_WbLS_mpt_scintModAlpha_size ]{ 0.076 }; // units???
    static const int m_WbLS_mpt_scintModNeutron_size{ 1 };
    G4double m_WbLS_mpt_scintModNeutron_energies[ m_WbLS_mpt_scintModNeutron_size ]{ 1.0 }; // units???
    G4double m_WbLS_mpt_scintModNeutron_values[ m_WbLS_mpt_scintModNeutron_size ]{ 0.093 }; // units???
    static const int m_WbLS_mpt_refIndex_size{ 200 };
    G4double m_WbLS_mpt_refIndex_energies[ m_WbLS_mpt_refIndex_size ]{ m_hc / 200.0             , m_hc / 203.01507537688443, m_hc / 206.03015075376885, m_hc / 209.04522613065328, m_hc / 212.0603015075377 , 
                                                                       m_hc / 215.0753768844221 , m_hc / 218.09045226130652, m_hc / 221.10552763819095, m_hc / 224.12060301507537, m_hc / 227.1356783919598 , 
                                                                       m_hc / 230.15075376884423, m_hc / 233.16582914572865, m_hc / 236.18090452261308, m_hc / 239.1959798994975 , m_hc / 242.2110552763819 , 
                                                                       m_hc / 245.22613065326632, m_hc / 248.24120603015075, m_hc / 251.25628140703517, m_hc / 254.2713567839196 , m_hc / 257.286432160804  , 
                                                                       m_hc / 260.30150753768845, m_hc / 263.31658291457285, m_hc / 266.3316582914573 , m_hc / 269.3467336683417 , m_hc / 272.36180904522615, 
                                                                       m_hc / 275.37688442211055, m_hc / 278.391959798995  , m_hc / 281.4070351758794 , m_hc / 284.4221105527638 , m_hc / 287.43718592964825, 
                                                                       m_hc / 290.45226130653265, m_hc / 293.4673366834171 , m_hc / 296.4824120603015 , m_hc / 299.49748743718595, m_hc / 302.51256281407035, 
                                                                       m_hc / 305.5276381909548 , m_hc / 308.5427135678392 , m_hc / 311.5577889447236 , m_hc / 314.57286432160805, m_hc / 317.58793969849245, 
                                                                       m_hc / 320.6030150753769 , m_hc / 323.6180904522613 , m_hc / 326.63316582914575, m_hc / 329.64824120603015, m_hc / 332.6633165829146 , 
                                                                       m_hc / 335.678391959799  , m_hc / 338.6934673366834 , m_hc / 341.70854271356785, m_hc / 344.7236180904523 , m_hc / 347.7386934673367 , 
                                                                       m_hc / 350.7537688442211 , m_hc / 353.7688442211055 , m_hc / 356.78391959798995, m_hc / 359.7989949748744 , m_hc / 362.8140703517588 , 
                                                                       m_hc / 365.8291457286432 , m_hc / 368.84422110552765, m_hc / 371.8592964824121 , m_hc / 374.8743718592965 , m_hc / 377.8894472361809 , 
                                                                       m_hc / 380.9045226130653 , m_hc / 383.91959798994975, m_hc / 386.9346733668342 , m_hc / 389.9497487437186 , m_hc / 392.964824120603  , 
                                                                       m_hc / 395.97989949748745, m_hc / 398.9949748743719 , m_hc / 402.0100502512563 , m_hc / 405.0251256281407 , m_hc / 408.0402010050251 , 
                                                                       m_hc / 411.05527638190955, m_hc / 414.070351758794  , m_hc / 417.0854271356784 , m_hc / 420.1005025125628 , m_hc / 423.11557788944725, 
                                                                       m_hc / 426.1306532663317 , m_hc / 429.1457286432161 , m_hc / 432.1608040201005 , m_hc / 435.1758793969849 , m_hc / 438.19095477386935, 
                                                                       m_hc / 441.2060301507538 , m_hc / 444.2211055276382 , m_hc / 447.2361809045226 , m_hc / 450.25125628140705, m_hc / 453.2663316582915 , 
                                                                       m_hc / 456.2814070351759 , m_hc / 459.2964824120603 , m_hc / 462.31155778894475, m_hc / 465.32663316582915, m_hc / 468.3417085427136 , 
                                                                       m_hc / 471.356783919598  , m_hc / 474.37185929648246, m_hc / 477.38693467336685, m_hc / 480.40201005025125, m_hc / 483.4170854271357 , 
                                                                       m_hc / 486.4321608040201 , m_hc / 489.44723618090455, m_hc / 492.46231155778895, m_hc / 495.4773869346734 , m_hc / 498.4924623115578 , 
                                                                       m_hc / 501.50753768844226, m_hc / 504.52261306532665, m_hc / 507.53768844221105, m_hc / 510.5527638190955 , m_hc / 513.5678391959799 , 
                                                                       m_hc / 516.5829145728644 , m_hc / 519.5979899497488 , m_hc / 522.6130653266332 , m_hc / 525.6281407035176 , m_hc / 528.643216080402  , 
                                                                       m_hc / 531.6582914572864 , m_hc / 534.6733668341708 , m_hc / 537.6884422110553 , m_hc / 540.7035175879397 , m_hc / 543.7185929648242 , 
                                                                       m_hc / 546.7336683417086 , m_hc / 549.748743718593  , m_hc / 552.7638190954774 , m_hc / 555.7788944723618 , m_hc / 558.7939698492462 , 
                                                                       m_hc / 561.8090452261306 , m_hc / 564.8241206030151 , m_hc / 567.8391959798995 , m_hc / 570.854271356784  , m_hc / 573.8693467336684 , 
                                                                       m_hc / 576.8844221105528 , m_hc / 579.8994974874372 , m_hc / 582.9145728643216 , m_hc / 585.929648241206  , m_hc / 588.9447236180904 , 
                                                                       m_hc / 591.9597989949749 , m_hc / 594.9748743718593 , m_hc / 597.9899497487438 , m_hc / 601.0050251256282 , m_hc / 604.0201005025126 , 
                                                                       m_hc / 607.035175879397  , m_hc / 610.0502512562814 , m_hc / 613.0653266331658 , m_hc / 616.0804020100502 , m_hc / 619.0954773869347 , 
                                                                       m_hc / 622.1105527638191 , m_hc / 625.1256281407036 , m_hc / 628.140703517588  , m_hc / 631.1557788944724 , m_hc / 634.1708542713568 , 
                                                                       m_hc / 637.1859296482412 , m_hc / 640.2010050251256 , m_hc / 643.21608040201   , m_hc / 646.2311557788945 , m_hc / 649.2462311557789 , 
                                                                       m_hc / 652.2613065326634 , m_hc / 655.2763819095478 , m_hc / 658.2914572864322 , m_hc / 661.3065326633166 , m_hc / 664.321608040201  , 
                                                                       m_hc / 667.3366834170854 , m_hc / 670.3517587939698 , m_hc / 673.3668341708543 , m_hc / 676.3819095477387 , m_hc / 679.3969849246232 , 
                                                                       m_hc / 682.4120603015076 , m_hc / 685.427135678392  , m_hc / 688.4422110552764 , m_hc / 691.4572864321608 , m_hc / 694.4723618090452 , 
                                                                       m_hc / 697.4874371859296 , m_hc / 700.5025125628141 , m_hc / 703.5175879396985 , m_hc / 706.532663316583  , m_hc / 709.5477386934674 , 
                                                                       m_hc / 712.5628140703518 , m_hc / 715.5778894472362 , m_hc / 718.5929648241206 , m_hc / 721.6080402010051 , m_hc / 724.6231155778895 , 
                                                                       m_hc / 727.6381909547739 , m_hc / 730.6532663316583 , m_hc / 733.6683417085427 , m_hc / 736.6834170854272 , m_hc / 739.6984924623116 , 
                                                                       m_hc / 742.713567839196  , m_hc / 745.7286432160804 , m_hc / 748.7437185929649 , m_hc / 751.7587939698493 , m_hc / 754.7738693467337 , 
                                                                       m_hc / 757.7889447236181 , m_hc / 760.8040201005025 , m_hc / 763.819095477387  , m_hc / 766.8341708542714 , m_hc / 769.8492462311558 , 
                                                                       m_hc / 772.8643216080402 , m_hc / 775.8793969849247 , m_hc / 778.8944723618091 , m_hc / 781.9095477386935 , m_hc / 784.9246231155779 , 
                                                                       m_hc / 787.9396984924623 , m_hc / 790.9547738693468 , m_hc / 793.9698492462312 , m_hc / 796.9849246231156 , m_hc / 800.0             };
    G4double m_WbLS_mpt_refIndex_values[ m_WbLS_mpt_refIndex_size ]{ 1.432157041561935 , 1.4276687316662668, 1.4235551820651549, 1.4197708482072713, 1.4162763522646689, 
                                                                     1.4130366601715119, 1.4097527789720063, 1.4063475580105458, 1.4028732433951834, 1.3994782844786973, 
                                                                     1.3962580907506352, 1.39341612315222  , 1.390856214294925 , 1.3885151510230986, 1.386353814858455 , 
                                                                     1.3843380806909775, 1.382448809206285 , 1.3806717934518848, 1.3789936531258327, 1.3774072566233855, 
                                                                     1.3759015302225859, 1.3744731519971722, 1.373112804624899 , 1.3718183868640483, 1.370582397492454 , 
                                                                     1.3694032969324368, 1.3682748908730318, 1.3671965080477357, 1.3661620976182316, 1.365172245530425 , 
                                                                     1.3642205630054434, 1.3633084296274198, 1.3624303885496345, 1.3615872744303779, 1.3607746279837718, 
                                                                     1.3599935090222233, 1.3592391985188415, 1.3585136114100724, 1.3578119341909414, 1.357136230723279 , 
                                                                     1.3564820908011546, 1.3558513036682391, 1.3552402124428695, 1.354650143413325 , 1.3540780521042242, 
                                                                     1.3535252343386475, 1.3529884925262377, 1.3524695801276316, 1.3519654578696374, 1.3514777349316232, 
                                                                     1.3510032205515112, 1.3505435641547319, 1.3500961394775184, 1.349662679289419 , 1.3492404967651872, 
                                                                     1.3488310361425662, 1.3484316453518599, 1.3480444470227728, 1.3476662516571547, 1.3472994404446978, 
                                                                     1.3469413588821466, 1.3465932512500507, 1.346253202877785 , 1.345922708289013 , 1.3455997243845406, 
                                                                     1.3452855315594234, 1.3449783428162392, 1.3446792269164238, 1.3443863086044858, 1.344101499082996 , 
                                                                     1.3438225240060055, 1.3435507819124828, 1.3432845297000513, 1.3430249178664369, 1.3427704564245733, 
                                                                     1.34252256594245  , 1.3422795755688985, 1.3420420175492611, 1.341809479137883 , 1.3415820974049357, 
                                                                     1.341359388531878 , 1.3411415208393982, 1.3409277904396817, 1.3407189060144904, 1.3405136123312553, 
                                                                     1.340313133265056 , 1.3401163267940492, 1.3399233213869475, 1.3397342976711357, 1.339548850507053 , 
                                                                     1.3393667112516017, 1.3391881896224647, 1.3390131905547278, 1.3388412373262757, 1.338672352434634 , 
                                                                     1.3385069351151127, 1.3383440626018432, 1.3381842709624343, 1.3380272792001668, 1.3378731295638846, 
                                                                     1.3377214601966025, 1.3375726706711872, 1.3374259647311582, 1.337282288045667 , 1.3371405822855151, 
                                                                     1.337001481785079 , 1.3368643535782032, 1.336729635920183 , 1.336597061484901 , 1.336466478532865 , 
                                                                     1.336338062993469 , 1.336211470661104 , 1.336086967553359 , 1.3359643675813924, 1.3358436597696153, 
                                                                     1.3357246995876915, 1.3356072906799232, 1.3354918190488059, 1.3353780648874707, 1.3352658315665655, 
                                                                     1.3351550123545644, 1.3350459812286097, 1.3349385263648499, 1.3348324412957164, 1.3347276475230985, 
                                                                     1.3346245108989914, 1.3345224445778785, 1.3344219921651717, 1.334322720750094 , 1.3342249913577873, 
                                                                     1.3341282162610075, 1.3340325623525113, 1.333938358663152 , 1.333845221403803 , 1.3337533126185994, 
                                                                     1.3336624128183485, 1.3335726844405085, 1.333483936042065 , 1.3333963174225218, 1.3333096134592115, 
                                                                     1.3332238201700326, 1.3331392755424485, 1.3330554414526687, 1.3329727612441395, 1.3328905989345663, 
                                                                     1.3328095747966904, 1.3327293531640223, 1.3326502616781752, 1.3325715621102499, 1.3324939571648449, 
                                                                     1.3324169510493251, 1.3323409592945852, 1.3322656759175986, 1.3321910436290465, 1.332117091071828 , 
                                                                     1.3320437591442218, 1.3319713347780273, 1.3318994384774336, 1.3318282849326544, 1.3317578396586107, 
                                                                     1.331687845369654 , 1.3316185444684208, 1.331549931339431 , 1.3314818309768977, 1.3314145622070326, 
                                                                     1.3313476040071148, 1.3312813612779315, 1.3312154927093367, 1.3311502224870575, 1.3310854944383934, 
                                                                     1.3310211735254747, 1.3309575504876137, 1.3308943974154988, 1.330831648334453 , 1.330769350295062 , 
                                                                     1.3307074373612686, 1.3306459572600298, 1.330584970340216 , 1.3305245238902093, 1.3304643077465077, 
                                                                     1.33040460380199  , 1.3303455024343118, 1.3302865082073774, 1.3302281121289619, 1.3301697961336079, 
                                                                     1.3301120745316002, 1.3300547468878556, 1.329997707112959 , 1.3299410040188253, 1.329884574918669 , 
                                                                     1.3298284683907382, 1.3297727884656294, 1.3297174629809811, 1.3296623456167622, 1.3296075581387696, 
                                                                     1.3295529779275355, 1.3294987034821932, 1.3294448302733046, 1.3293912248983202, 1.3293378379090672 };
    static const int m_WbLS_mpt_scintillation_size{ 885 };
    G4double m_WbLS_mpt_scintillation_energies[ m_WbLS_mpt_scintillation_size ]{ m_hc / 222.0, m_hc / 222.4, m_hc / 222.8, m_hc / 223.2, m_hc / 223.6, m_hc / 224.0, m_hc / 224.4, m_hc / 224.8, m_hc / 225.2, m_hc / 225.6,
                                                                                 m_hc / 226.0, m_hc / 226.4, m_hc / 226.8, m_hc / 227.2, m_hc / 227.6, m_hc / 228.0, m_hc / 228.4, m_hc / 228.8, m_hc / 229.2, m_hc / 229.6, 
                                                                                 m_hc / 230.0, m_hc / 230.4, m_hc / 230.8, m_hc / 231.2, m_hc / 231.6, m_hc / 232.0, m_hc / 232.4, m_hc / 232.8, m_hc / 233.2, m_hc / 233.6,
                                                                                 m_hc / 234.0, m_hc / 234.4, m_hc / 234.8, m_hc / 235.2, m_hc / 235.6, m_hc / 236.0, m_hc / 236.4, m_hc / 236.8, m_hc / 237.2, m_hc / 237.6, 
                                                                                 m_hc / 238.0, m_hc / 238.4, m_hc / 238.8, m_hc / 239.2, m_hc / 239.6, m_hc / 240.0, m_hc / 240.4, m_hc / 240.8, m_hc / 241.2, m_hc / 241.6,
                                                                                 m_hc / 242.0, m_hc / 242.4, m_hc / 242.8, m_hc / 243.2, m_hc / 243.6, m_hc / 244.0, m_hc / 244.4, m_hc / 244.8, m_hc / 245.2, m_hc / 245.6, 
                                                                                 m_hc / 246.0, m_hc / 246.4, m_hc / 246.8, m_hc / 247.2, m_hc / 247.6, m_hc / 248.0, m_hc / 248.4, m_hc / 248.8, m_hc / 249.2, m_hc / 249.6,
                                                                                 m_hc / 250.0, m_hc / 250.4, m_hc / 250.8, m_hc / 251.2, m_hc / 251.6, m_hc / 252.0, m_hc / 252.4, m_hc / 252.8, m_hc / 253.2, m_hc / 253.6, 
                                                                                 m_hc / 254.0, m_hc / 254.4, m_hc / 254.8, m_hc / 255.2, m_hc / 255.6, m_hc / 256.0, m_hc / 256.4, m_hc / 256.8, m_hc / 257.2, m_hc / 257.6,
                                                                                 m_hc / 258.0, m_hc / 258.4, m_hc / 258.8, m_hc / 259.2, m_hc / 259.6, m_hc / 260.0, m_hc / 260.4, m_hc / 260.8, m_hc / 261.2, m_hc / 261.6, 
                                                                                 m_hc / 262.0, m_hc / 262.4, m_hc / 262.8, m_hc / 263.2, m_hc / 263.6, m_hc / 264.0, m_hc / 264.4, m_hc / 264.8, m_hc / 265.2, m_hc / 265.6,
                                                                                 m_hc / 266.0, m_hc / 266.4, m_hc / 266.8, m_hc / 267.2, m_hc / 267.6, m_hc / 268.0, m_hc / 268.4, m_hc / 268.8, m_hc / 269.2, m_hc / 269.6, 
                                                                                 m_hc / 270.0, m_hc / 270.4, m_hc / 270.8, m_hc / 271.2, m_hc / 271.6, m_hc / 272.0, m_hc / 272.4, m_hc / 272.8, m_hc / 273.2, m_hc / 273.6,
                                                                                 m_hc / 274.0, m_hc / 274.4, m_hc / 274.8, m_hc / 275.2, m_hc / 275.6, m_hc / 276.0, m_hc / 276.4, m_hc / 276.8, m_hc / 277.2, m_hc / 277.6, 
                                                                                 m_hc / 278.0, m_hc / 278.4, m_hc / 278.8, m_hc / 279.2, m_hc / 279.6, m_hc / 280.0, m_hc / 280.4, m_hc / 280.8, m_hc / 281.2, m_hc / 281.6,
                                                                                 m_hc / 282.0, m_hc / 282.4, m_hc / 282.7, m_hc / 283.1, m_hc / 283.5, m_hc / 283.9, m_hc / 284.3, m_hc / 284.7, m_hc / 285.1, m_hc / 285.5, 
                                                                                 m_hc / 285.9, m_hc / 286.3, m_hc / 286.7, m_hc / 287.1, m_hc / 287.5, m_hc / 287.9, m_hc / 288.3, m_hc / 288.7, m_hc / 289.1, m_hc / 289.5,
                                                                                 m_hc / 289.9, m_hc / 290.3, m_hc / 290.7, m_hc / 291.1, m_hc / 291.5, m_hc / 291.9, m_hc / 292.3, m_hc / 292.7, m_hc / 293.1, m_hc / 293.5, 
                                                                                 m_hc / 293.9, m_hc / 294.3, m_hc / 294.7, m_hc / 295.1, m_hc / 295.5, m_hc / 295.9, m_hc / 296.3, m_hc / 296.7, m_hc / 297.1, m_hc / 297.5,
                                                                                 m_hc / 297.9, m_hc / 298.3, m_hc / 298.7, m_hc / 299.1, m_hc / 299.5, m_hc / 299.9, m_hc / 300.3, m_hc / 300.7, m_hc / 301.1, m_hc / 301.5, 
                                                                                 m_hc / 301.9, m_hc / 302.3, m_hc / 302.7, m_hc / 303.1, m_hc / 303.5, m_hc / 303.9, m_hc / 304.3, m_hc / 304.7, m_hc / 305.1, m_hc / 305.5,
                                                                                 m_hc / 305.9, m_hc / 306.3, m_hc / 306.7, m_hc / 307.1, m_hc / 307.5, m_hc / 307.9, m_hc / 308.3, m_hc / 308.7, m_hc / 309.1, m_hc / 309.5, 
                                                                                 m_hc / 309.9, m_hc / 310.3, m_hc / 310.7, m_hc / 311.1, m_hc / 311.5, m_hc / 311.9, m_hc / 312.3, m_hc / 312.7, m_hc / 313.1, m_hc / 313.5,
                                                                                 m_hc / 313.9, m_hc / 314.3, m_hc / 314.6, m_hc / 315.0, m_hc / 315.4, m_hc / 315.8, m_hc / 316.2, m_hc / 316.6, m_hc / 317.0, m_hc / 317.4, 
                                                                                 m_hc / 317.8, m_hc / 318.2, m_hc / 318.6, m_hc / 319.0, m_hc / 319.4, m_hc / 319.8, m_hc / 320.2, m_hc / 320.6, m_hc / 321.0, m_hc / 321.4,
                                                                                 m_hc / 321.8, m_hc / 322.2, m_hc / 322.6, m_hc / 323.0, m_hc / 323.4, m_hc / 323.8, m_hc / 324.2, m_hc / 324.6, m_hc / 325.0, m_hc / 325.4, 
                                                                                 m_hc / 325.8, m_hc / 326.2, m_hc / 326.6, m_hc / 327.0, m_hc / 327.4, m_hc / 327.8, m_hc / 328.2, m_hc / 328.6, m_hc / 329.0, m_hc / 329.4,
                                                                                 m_hc / 329.8, m_hc / 330.2, m_hc / 330.6, m_hc / 331.0, m_hc / 331.4, m_hc / 331.8, m_hc / 332.2, m_hc / 332.6, m_hc / 333.0, m_hc / 333.4, 
                                                                                 m_hc / 333.8, m_hc / 334.2, m_hc / 334.6, m_hc / 335.0, m_hc / 335.4, m_hc / 335.8, m_hc / 336.1, m_hc / 336.5, m_hc / 336.9, m_hc / 337.3,
                                                                                 m_hc / 337.7, m_hc / 338.1, m_hc / 338.5, m_hc / 338.9, m_hc / 339.3, m_hc / 339.7, m_hc / 340.1, m_hc / 340.5, m_hc / 340.9, m_hc / 341.3, 
                                                                                 m_hc / 341.7, m_hc / 342.1, m_hc / 342.5, m_hc / 342.9, m_hc / 343.3, m_hc / 343.7, m_hc / 344.1, m_hc / 344.5, m_hc / 344.9, m_hc / 345.3,
                                                                                 m_hc / 345.7, m_hc / 346.1, m_hc / 346.5, m_hc / 346.9, m_hc / 347.3, m_hc / 347.7, m_hc / 348.1, m_hc / 348.5, m_hc / 348.9, m_hc / 349.3, 
                                                                                 m_hc / 349.7, m_hc / 350.1, m_hc / 350.5, m_hc / 350.9, m_hc / 351.3, m_hc / 351.7, m_hc / 352.1, m_hc / 352.5, m_hc / 352.9, m_hc / 353.2,
                                                                                 m_hc / 353.6, m_hc / 354.0, m_hc / 354.4, m_hc / 354.8, m_hc / 355.2, m_hc / 355.6, m_hc / 356.0, m_hc / 356.4, m_hc / 356.8, m_hc / 357.2, 
                                                                                 m_hc / 357.6, m_hc / 358.0, m_hc / 358.4, m_hc / 358.8, m_hc / 359.2, m_hc / 359.6, m_hc / 360.0, m_hc / 360.4, m_hc / 360.8, m_hc / 361.2,
                                                                                 m_hc / 361.6, m_hc / 362.0, m_hc / 362.4, m_hc / 362.8, m_hc / 363.2, m_hc / 363.6, m_hc / 364.0, m_hc / 364.4, m_hc / 364.8, m_hc / 365.2, 
                                                                                 m_hc / 365.6, m_hc / 366.0, m_hc / 366.4, m_hc / 366.8, m_hc / 367.2, m_hc / 367.6, m_hc / 367.9, m_hc / 368.3, m_hc / 368.7, m_hc / 369.1,
                                                                                 m_hc / 369.5, m_hc / 369.9, m_hc / 370.3, m_hc / 370.7, m_hc / 371.1, m_hc / 371.5, m_hc / 371.9, m_hc / 372.3, m_hc / 372.7, m_hc / 373.1, 
                                                                                 m_hc / 373.5, m_hc / 373.9, m_hc / 374.3, m_hc / 374.7, m_hc / 375.1, m_hc / 375.5, m_hc / 375.9, m_hc / 376.3, m_hc / 376.7, m_hc / 377.1,
                                                                                 m_hc / 377.5, m_hc / 377.9, m_hc / 378.3, m_hc / 378.7, m_hc / 379.1, m_hc / 379.5, m_hc / 379.9, m_hc / 380.3, m_hc / 380.6, m_hc / 381.0, 
                                                                                 m_hc / 381.4, m_hc / 381.8, m_hc / 382.2, m_hc / 382.6, m_hc / 383.0, m_hc / 383.4, m_hc / 383.8, m_hc / 384.2, m_hc / 384.6, m_hc / 385.0,
                                                                                 m_hc / 385.4, m_hc / 385.8, m_hc / 386.2, m_hc / 386.6, m_hc / 387.0, m_hc / 387.4, m_hc / 387.8, m_hc / 388.2, m_hc / 388.6, m_hc / 389.0, 
                                                                                 m_hc / 389.4, m_hc / 389.8, m_hc / 390.2, m_hc / 390.6, m_hc / 391.0, m_hc / 391.4, m_hc / 391.8, m_hc / 392.2, m_hc / 392.5, m_hc / 392.9,
                                                                                 m_hc / 393.3, m_hc / 393.7, m_hc / 394.1, m_hc / 394.5, m_hc / 394.9, m_hc / 395.3, m_hc / 395.7, m_hc / 396.1, m_hc / 396.5, m_hc / 396.9, 
                                                                                 m_hc / 397.3, m_hc / 397.7, m_hc / 398.1, m_hc / 398.5, m_hc / 398.9, m_hc / 399.3, m_hc / 399.7, m_hc / 400.1, m_hc / 400.5, m_hc / 400.9,
                                                                                 m_hc / 401.3, m_hc / 401.7, m_hc / 402.1, m_hc / 402.5, m_hc / 402.8, m_hc / 403.2, m_hc / 403.6, m_hc / 404.0, m_hc / 404.4, m_hc / 404.8, 
                                                                                 m_hc / 405.2, m_hc / 405.6, m_hc / 406.0, m_hc / 406.4, m_hc / 406.8, m_hc / 407.2, m_hc / 407.6, m_hc / 408.0, m_hc / 408.4, m_hc / 408.8,
                                                                                 m_hc / 409.2, m_hc / 409.6, m_hc / 410.0, m_hc / 410.4, m_hc / 410.8, m_hc / 411.2, m_hc / 411.6, m_hc / 412.0, m_hc / 412.4, m_hc / 412.7, 
                                                                                 m_hc / 413.1, m_hc / 413.5, m_hc / 413.9, m_hc / 414.3, m_hc / 414.7, m_hc / 415.1, m_hc / 415.5, m_hc / 415.9, m_hc / 416.3, m_hc / 416.7,
                                                                                 m_hc / 417.1, m_hc / 417.5, m_hc / 417.9, m_hc / 418.3, m_hc / 418.7, m_hc / 419.1, m_hc / 419.5, m_hc / 419.9, m_hc / 420.3, m_hc / 420.7, 
                                                                                 m_hc / 421.1, m_hc / 421.5, m_hc / 421.8, m_hc / 422.2, m_hc / 422.6, m_hc / 423.0, m_hc / 423.4, m_hc / 423.8, m_hc / 424.2, m_hc / 424.6,
                                                                                 m_hc / 425.0, m_hc / 425.4, m_hc / 425.8, m_hc / 426.2, m_hc / 426.6, m_hc / 427.0, m_hc / 427.4, m_hc / 427.8, m_hc / 428.2, m_hc / 428.6, 
                                                                                 m_hc / 429.0, m_hc / 429.4, m_hc / 429.8, m_hc / 430.1, m_hc / 430.5, m_hc / 430.9, m_hc / 431.3, m_hc / 431.7, m_hc / 432.1, m_hc / 432.5,
                                                                                 m_hc / 432.9, m_hc / 433.3, m_hc / 433.7, m_hc / 434.1, m_hc / 434.5, m_hc / 434.9, m_hc / 435.3, m_hc / 435.7, m_hc / 436.1, m_hc / 436.5, 
                                                                                 m_hc / 436.9, m_hc / 437.3, m_hc / 437.7, m_hc / 438.1, m_hc / 438.4, m_hc / 438.8, m_hc / 439.2, m_hc / 439.6, m_hc / 440.0, m_hc / 440.4,
                                                                                 m_hc / 440.8, m_hc / 441.2, m_hc / 441.6, m_hc / 442.0, m_hc / 442.4, m_hc / 442.8, m_hc / 443.2, m_hc / 443.6, m_hc / 444.0, m_hc / 444.4, 
                                                                                 m_hc / 444.8, m_hc / 445.2, m_hc / 445.6, m_hc / 445.9, m_hc / 446.3, m_hc / 446.7, m_hc / 447.1, m_hc / 447.5, m_hc / 447.9, m_hc / 448.3,
                                                                                 m_hc / 448.7, m_hc / 449.1, m_hc / 449.5, m_hc / 449.9, m_hc / 450.3, m_hc / 450.7, m_hc / 451.1, m_hc / 451.5, m_hc / 451.9, m_hc / 452.3, 
                                                                                 m_hc / 452.7, m_hc / 453.0, m_hc / 453.4, m_hc / 453.8, m_hc / 454.2, m_hc / 454.6, m_hc / 455.0, m_hc / 455.4, m_hc / 455.8, m_hc / 456.2,
                                                                                 m_hc / 456.6, m_hc / 457.0, m_hc / 457.4, m_hc / 457.8, m_hc / 458.2, m_hc / 458.6, m_hc / 459.0, m_hc / 459.4, m_hc / 459.8, m_hc / 460.1, 
                                                                                 m_hc / 460.5, m_hc / 460.9, m_hc / 461.3, m_hc / 461.7, m_hc / 462.1, m_hc / 462.5, m_hc / 462.9, m_hc / 463.3, m_hc / 463.7, m_hc / 464.1,
                                                                                 m_hc / 464.5, m_hc / 464.9, m_hc / 465.3, m_hc / 465.7, m_hc / 466.1, m_hc / 466.5, m_hc / 466.8, m_hc / 467.2, m_hc / 467.6, m_hc / 468.0, 
                                                                                 m_hc / 468.4, m_hc / 468.8, m_hc / 469.2, m_hc / 469.6, m_hc / 470.0, m_hc / 470.4, m_hc / 470.8, m_hc / 471.2, m_hc / 471.6, m_hc / 472.0,
                                                                                 m_hc / 472.4, m_hc / 472.8, m_hc / 473.1, m_hc / 473.5, m_hc / 473.9, m_hc / 474.3, m_hc / 474.7, m_hc / 475.1, m_hc / 475.5, m_hc / 475.9, 
                                                                                 m_hc / 476.3, m_hc / 476.7, m_hc / 477.1, m_hc / 477.5, m_hc / 477.9, m_hc / 478.3, m_hc / 478.7, m_hc / 479.1, m_hc / 479.4, m_hc / 479.8,
                                                                                 m_hc / 480.2, m_hc / 480.6, m_hc / 481.0, m_hc / 481.4, m_hc / 481.8, m_hc / 482.2, m_hc / 482.6, m_hc / 483.0, m_hc / 483.4, m_hc / 483.8, 
                                                                                 m_hc / 484.2, m_hc / 484.6, m_hc / 485.0, m_hc / 485.3, m_hc / 485.7, m_hc / 486.1, m_hc / 486.5, m_hc / 486.9, m_hc / 487.3, m_hc / 487.7,
                                                                                 m_hc / 488.1, m_hc / 488.5, m_hc / 488.9, m_hc / 489.3, m_hc / 489.7, m_hc / 490.1, m_hc / 490.5, m_hc / 490.9, m_hc / 491.2, m_hc / 491.6, 
                                                                                 m_hc / 492.0, m_hc / 492.4, m_hc / 492.8, m_hc / 493.2, m_hc / 493.6, m_hc / 494.0, m_hc / 494.4, m_hc / 494.8, m_hc / 495.2, m_hc / 495.6,
                                                                                 m_hc / 496.0, m_hc / 496.4, m_hc / 496.7, m_hc / 497.1, m_hc / 497.5, m_hc / 497.9, m_hc / 498.3, m_hc / 498.7, m_hc / 499.1, m_hc / 499.5, 
                                                                                 m_hc / 499.9, m_hc / 500.3, m_hc / 500.7, m_hc / 501.1, m_hc / 501.5, m_hc / 501.9, m_hc / 502.2, m_hc / 502.6, m_hc / 503.0, m_hc / 503.4,
                                                                                 m_hc / 503.8, m_hc / 504.2, m_hc / 504.6, m_hc / 505.0, m_hc / 505.4, m_hc / 505.8, m_hc / 506.2, m_hc / 506.6, m_hc / 507.0, m_hc / 507.3, 
                                                                                 m_hc / 507.7, m_hc / 508.1, m_hc / 508.5, m_hc / 508.9, m_hc / 509.3, m_hc / 509.7, m_hc / 510.1, m_hc / 510.5, m_hc / 510.9, m_hc / 511.3,
                                                                                 m_hc / 511.7, m_hc / 512.1, m_hc / 512.4, m_hc / 512.8, m_hc / 513.2, m_hc / 513.6, m_hc / 514.0, m_hc / 514.4, m_hc / 514.8, m_hc / 515.2, 
                                                                                 m_hc / 515.6, m_hc / 516.0, m_hc / 516.4, m_hc / 516.8, m_hc / 517.2, m_hc / 517.5, m_hc / 517.9, m_hc / 518.3, m_hc / 518.7, m_hc / 519.1,
                                                                                 m_hc / 519.5, m_hc / 519.9, m_hc / 520.3, m_hc / 520.7, m_hc / 521.1, m_hc / 521.5, m_hc / 521.9, m_hc / 522.2, m_hc / 522.6, m_hc / 523.0, 
                                                                                 m_hc / 523.4, m_hc / 523.8, m_hc / 524.2, m_hc / 524.6, m_hc / 525.0, m_hc / 525.4, m_hc / 525.8, m_hc / 526.2, m_hc / 526.6, m_hc / 526.9,
                                                                                 m_hc / 527.3, m_hc / 527.7, m_hc / 528.1, m_hc / 528.5, m_hc / 528.9, m_hc / 529.3, m_hc / 529.7, m_hc / 530.1, m_hc / 530.5, m_hc / 530.9, 
                                                                                 m_hc / 531.3, m_hc / 531.6, m_hc / 532.0, m_hc / 532.4, m_hc / 532.8, m_hc / 533.2, m_hc / 533.6, m_hc / 534.0, m_hc / 534.4, m_hc / 534.8,
                                                                                 m_hc / 535.2, m_hc / 535.6, m_hc / 535.9, m_hc / 536.3, m_hc / 536.7, m_hc / 537.1, m_hc / 537.5, m_hc / 537.9, m_hc / 538.3, m_hc / 538.7, 
                                                                                 m_hc / 539.1, m_hc / 539.5, m_hc / 539.9, m_hc / 540.3, m_hc / 540.6, m_hc / 541.0, m_hc / 541.4, m_hc / 541.8, m_hc / 542.2, m_hc / 542.6,
                                                                                 m_hc / 543.0, m_hc / 543.4, m_hc / 543.8, m_hc / 544.2, m_hc / 544.6, m_hc / 544.9, m_hc / 545.3, m_hc / 545.7, m_hc / 546.1, m_hc / 546.5, 
                                                                                 m_hc / 546.9, m_hc / 547.3, m_hc / 547.7, m_hc / 548.1, m_hc / 548.5, m_hc / 548.9, m_hc / 549.2, m_hc / 549.6, m_hc / 550.0, m_hc / 550.4,
                                                                                 m_hc / 550.8, m_hc / 551.2, m_hc / 551.6, m_hc / 552.0, m_hc / 552.4, m_hc / 552.8, m_hc / 553.1, m_hc / 553.5, m_hc / 553.9, m_hc / 554.3, 
                                                                                 m_hc / 554.7, m_hc / 555.1, m_hc / 555.5, m_hc / 555.9, m_hc / 556.3, m_hc / 556.7, m_hc / 557.1, m_hc / 557.4, m_hc / 557.8, m_hc / 558.2,
                                                                                 m_hc / 558.6, m_hc / 559.0, m_hc / 559.4, m_hc / 559.8, m_hc / 560.2, m_hc / 560.6, m_hc / 561.0, m_hc / 561.3, m_hc / 561.7, m_hc / 562.1, 
                                                                                 m_hc / 562.5, m_hc / 562.9, m_hc / 563.3, m_hc / 563.7, m_hc / 564.1, m_hc / 564.5, m_hc / 564.9, m_hc / 565.2, m_hc / 565.6, m_hc / 566.0,
                                                                                 m_hc / 566.4, m_hc / 566.8, m_hc / 567.2, m_hc / 567.6, m_hc / 568.0, m_hc / 568.4, m_hc / 568.8, m_hc / 569.1, m_hc / 569.5, m_hc / 569.9, 
                                                                                 m_hc / 570.3, m_hc / 570.7, m_hc / 571.1, m_hc / 571.5, m_hc / 571.9                                                                      };
    G4double m_WbLS_mpt_scintillation_values[ m_WbLS_mpt_scintillation_size ]{ 0.0360006124, 0.0434853417, 0.0432652238, 0.02600129  , 0.0233379271, 0.033721551 , 0.029973259 , 0.0334315864, 0.0189800738, 0.0388781665,
                                                                               0.0361808399, 0.0330346063, 0.0294763364, 0.0412574183, 0.0198393893, 0.0250410021, 0.0380327292, 0.0330001248, 0.0312274783, 0.0213405995,
                                                                               0.0327245914, 0.0291879874, 0.0225559679, 0.0286205731, 0.014180487 , 0.0120643174, 0.0321327344, 0.0208237731, 0.0223725   , 0.013792754 ,
                                                                               0.0152093082, 0.0163020561, 0.0241327549, 0.0203439666, 0.0313212988, 0.0245139201, 0.0269615847, 0.0282244522, 0.0113222609, 0.0161596889,
                                                                               0.0232753016, 0.0228552515, 0.0183123106, 0.0216272449, 0.0131731662, 0.0232426199, 0.0240558187, 0.0257491667, 0.0219355412, 0.0240633542,
                                                                               0.0163312953, 0.0224550606, 0.0228547663, 0.014236389 , 0.0183747492, 0.0210231048, 0.0172338015, 0.0166273682, 0.0108896025, 0.0124477094,
                                                                               0.0247179195, 0.0263929167, 0.0159662121, 0.0103989794, 0.018283146 , 0.0144866189, 0.0222452145, 0.0210229354, 0.0225470392, 0.0194418481,
                                                                               0.0213026891, 0.0183083924, 0.0214327231, 0.0240548904, 0.0147433231, 0.0188857478, 0.0169836542, 0.0237993246, 0.0206549179, 0.0137782022,
                                                                               0.0163379553, 0.0242911783, 0.0195608405, 0.0257604536, 0.0182903128, 0.0180349652, 0.0198893049, 0.014484403 , 0.0198167206, 0.0215331358,
                                                                               0.0233024604, 0.0146517741, 0.0239295348, 0.0209897062, 0.0223609664, 0.0226831382, 0.0216562632, 0.0210260363, 0.014865163 , 0.0198796566,
                                                                               0.0179122675, 0.0187225863, 0.0207886925, 0.0166616315, 0.0240816792, 0.0224486785, 0.0177482846, 0.0224659409, 0.0141734422, 0.0185783826,
                                                                               0.0209559457, 0.0139040009, 0.0208455066, 0.0190691629, 0.0166890369, 0.0131965532, 0.0241619006, 0.0139414681, 0.0152742189, 0.0180916587,
                                                                               0.0197939652, 0.0143165128, 0.0228917131, 0.0234829575, 0.0114395388, 0.0163371827, 0.0214205702, 0.0200038167, 0.0220641969, 0.026536909 ,
                                                                               0.0302179986, 0.0259100622, 0.0270630354, 0.0245573642, 0.0089894971, 0.0140436277, 0.0195803811, 0.0210290695, 0.0189525816, 0.0236695386,
                                                                               0.0226541104, 0.0177075159, 0.0192363511, 0.0112580631, 0.0177006811, 0.0138276028, 0.019265284 , 0.0154398335, 0.0154522575, 0.0181947386,
                                                                               0.0164047958, 0.0194974749, 0.021023487,  0.0158365291, 0.0212127014, 0.0137352298, 0.0249113733, 0.0213920859, 0.0152184158, 0.0185912525,
                                                                               0.0097033621, 0.0262373774, 0.0300488778, 0.0260733403, 0.0287036949, 0.0263613817, 0.0266374802, 0.0388163283, 0.0386846802, 0.0379349852,
                                                                               0.0349013632, 0.0337913759, 0.0351834982, 0.0386184983, 0.044793914 , 0.0422677086, 0.0445959755, 0.0484959985, 0.0449241743, 0.050563372 ,
                                                                               0.049318248 , 0.0467531781, 0.0467512793, 0.0375717736, 0.0461220933, 0.051323912 , 0.0517906142, 0.0425476385, 0.0470375561, 0.0492374519,
                                                                               0.0574973422, 0.053453636 , 0.0507549283, 0.050446487 , 0.0552257444, 0.0603178775, 0.051049074 , 0.0539921418, 0.0511432129, 0.0589777797,
                                                                               0.0616186243, 0.0520250061, 0.0575066816, 0.0620283782, 0.0501792793, 0.0553466437, 0.0517237844, 0.0502110027, 0.0486157742, 0.0535640887,
                                                                               0.053303408 , 0.0464243043, 0.059517447 , 0.0491781875, 0.0530352191, 0.0572120887, 0.0492608782, 0.0489966874, 0.0526269465, 0.0481007666,
                                                                               0.0447057803, 0.0512595219, 0.0541127714, 0.0340289297, 0.0493167802, 0.0449113139, 0.0530150699, 0.0485251143, 0.0376974381, 0.0507612738,
                                                                               0.0445686039, 0.0377243082, 0.0452034455, 0.0436844064, 0.04559641  , 0.0466746765, 0.0444242701, 0.0310253886, 0.0426471024, 0.0421788322,
                                                                               0.0402217366, 0.045456199 , 0.0397766637, 0.0361028778, 0.0380480658, 0.0384483393, 0.0364400717, 0.0312767542, 0.0311024711, 0.0435257716,
                                                                               0.03683093  , 0.0405335661, 0.0334528131, 0.0373963805, 0.034944486 , 0.042017541 , 0.0394008952, 0.0363520289, 0.0311013869, 0.030776743 ,
                                                                               0.0390879774, 0.0381611938, 0.0287443375, 0.03256074  , 0.0337064137, 0.0355538305, 0.0432971221, 0.033664207 , 0.038570888 , 0.0340192326,
                                                                               0.0369074447, 0.0290419392, 0.0354024587, 0.0394559772, 0.0337908609, 0.0410424925, 0.033504904 , 0.0357107997, 0.0359733954, 0.0451283878,
                                                                               0.0501327045, 0.0524999863, 0.0521308629, 0.0494927574, 0.0534598338, 0.0632464653, 0.0595975749, 0.074938267 , 0.0754141933, 0.084430795 ,
                                                                               0.0899022989, 0.1081005951, 0.1149026231, 0.1236461364, 0.1334740598, 0.1546893255, 0.1598302602, 0.1781296413, 0.1998283551, 0.2172820604,
                                                                               0.2389156182, 0.2477088384, 0.2680982983, 0.2922819663, 0.3007191824, 0.3300877482, 0.3447180002, 0.3457306907, 0.3732153944, 0.3899848384,
                                                                               0.4011389218, 0.3960670205, 0.4189107859, 0.4337964843, 0.4330434837, 0.445936674 , 0.4550608253, 0.4588709527, 0.4688909069, 0.4789815547,
                                                                               0.4828605842, 0.4913215965, 0.5030406546, 0.5125473278, 0.5161465683, 0.5209576778, 0.5361323243, 0.5422499718, 0.5534855153, 0.5642012995,
                                                                               0.5769714382, 0.5920372286, 0.6040697805, 0.6262202489, 0.6295577218, 0.6608218609, 0.6580608272, 0.663921311 , 0.7007231306, 0.7087308407,
                                                                               0.7229765433, 0.7381978175, 0.7687459353, 0.7793342064, 0.7908507938, 0.8140637815, 0.8417408088, 0.8516712753, 0.8679837523, 0.8828183357,
                                                                               0.8930979107, 0.9030428572, 0.9346108243, 0.9323752679, 0.9527754779, 0.9646525745, 0.9723403341, 0.9768520788, 0.9867240805, 0.9861449592,
                                                                               0.994523373 , 0.9990912473, 0.9996223694, 0.9947960399, 0.9914685243, 1.0         , 0.9971230721, 0.9892315815, 0.9933720031, 0.9691867128,
                                                                               0.9698875181, 0.9827435122, 0.9656857517, 0.9702198886, 0.9592185852, 0.9570715731, 0.9488581329, 0.9459099787, 0.936008735 , 0.9474562457,
                                                                               0.9428810243, 0.9435310304, 0.9359218564, 0.9304682477, 0.9323184782, 0.9309649534, 0.9329448316, 0.9320405378, 0.9273340817, 0.9234638318,
                                                                               0.917826846 , 0.9259217492, 0.9258602404, 0.9236182097, 0.9244385184, 0.9200411311, 0.9190830143, 0.9141197686, 0.9181235098, 0.9146539835,
                                                                               0.9050022366, 0.9023300765, 0.8976813397, 0.9041373196, 0.8937833456, 0.892265018 , 0.8812571388, 0.8828541197, 0.8815111513, 0.8738891629,
                                                                               0.8658082221, 0.8641470068, 0.8628073034, 0.8526618975, 0.8375096649, 0.8398163405, 0.8267873861, 0.82436982  , 0.8132054445, 0.8043459327,
                                                                               0.8003235561, 0.7897782196, 0.7756406548, 0.7681101206, 0.7568131997, 0.7549242457, 0.7510062406, 0.7358943241, 0.7169145023, 0.715479699 ,
                                                                               0.7040168816, 0.6973117574, 0.6960640746, 0.6898165653, 0.6648281826, 0.6660821662, 0.6628395627, 0.6483520683, 0.6374386546, 0.6353745623,
                                                                               0.625425642 , 0.6215322884, 0.6152677945, 0.6083809086, 0.5990979313, 0.5910476351, 0.5845783814, 0.5853605954, 0.581014128 , 0.5683669744,
                                                                               0.560684022 , 0.5640026034, 0.5571752137, 0.5477354028, 0.5379068167, 0.5368865026, 0.5337560785, 0.5252802934, 0.5178209258, 0.5068670253,
                                                                               0.5115104182, 0.5117480926, 0.4967845188, 0.4889767259, 0.4772044521, 0.4659356279, 0.4724784091, 0.4611603687, 0.465413017 , 0.4570219123,
                                                                               0.4505178708, 0.4458788949, 0.4375752434, 0.4247302164, 0.421817575 , 0.4269631544, 0.4160550358, 0.4043091225, 0.3976120257, 0.3955820476,
                                                                               0.3894015049, 0.3861093125, 0.3865411902, 0.3781785209, 0.3711352269, 0.3655817315, 0.3575331524, 0.3620170145, 0.3462039416, 0.3438848582,
                                                                               0.3325343719, 0.3362618452, 0.3231746685, 0.3295612233, 0.3163303566, 0.3145048699, 0.3099347783, 0.3011148859, 0.2992121499, 0.2945465356,
                                                                               0.2979482645, 0.2893462049, 0.288751991 , 0.2776902603, 0.2769782928, 0.270053876 , 0.2638554758, 0.2607599262, 0.26228501  , 0.2602310716,
                                                                               0.2575118068, 0.2433034047, 0.2497358769, 0.2323645534, 0.2382247757, 0.2331222365, 0.2261130188, 0.2300640295, 0.2290656835, 0.2135578709,
                                                                               0.2158616774, 0.202198811 , 0.2149233155, 0.2099723434, 0.201999154 , 0.2019236816, 0.2016210382, 0.1894141612, 0.1875696216, 0.1842875479,
                                                                               0.1798380819, 0.1803230913, 0.18215758  , 0.1676756043, 0.1755149933, 0.1728114946, 0.166306022 , 0.1716419149, 0.1664200988, 0.1629996234,
                                                                               0.1591386668, 0.1547539556, 0.1534158582, 0.1472522051, 0.1476032976, 0.1502208934, 0.1463197089, 0.1407015794, 0.1469707722, 0.1376181855,
                                                                               0.1382524538, 0.1382929583, 0.1367997376, 0.1315469569, 0.133061838 , 0.1388091355, 0.1268676812, 0.127658187 , 0.1242017704, 0.1234443624,
                                                                               0.1197361154, 0.1214337691, 0.1136644437, 0.115743653 , 0.1091228838, 0.114282359 , 0.1156957134, 0.1068103601, 0.1062400712, 0.0988350253,
                                                                               0.0986795957, 0.1009251881, 0.1051490229, 0.097588336 , 0.1003166691, 0.0973551787, 0.0952477819, 0.0929788811, 0.0914255232, 0.0832416   ,
                                                                               0.0904785999, 0.0856957619, 0.0880658885, 0.0902370235, 0.0850029365, 0.0790683057, 0.0751442912, 0.079545697 , 0.0797114757, 0.0753204311,
                                                                               0.07665488  , 0.0758540185, 0.0743465672, 0.0762344545, 0.0658907361, 0.0782958674, 0.067855111 , 0.0694521041, 0.0720343836, 0.0716177665,
                                                                               0.0673965299, 0.0649165171, 0.0666560861, 0.0721165377, 0.0653355425, 0.0679188832, 0.0650313447, 0.0607216803, 0.0615832144, 0.0631712951,
                                                                               0.0587815855, 0.0639004086, 0.0547899864, 0.06021428  , 0.0521647034, 0.0534495918, 0.0575515744, 0.0505102009, 0.0593629892, 0.0512456341,
                                                                               0.0555482943, 0.057869248 , 0.0516390851, 0.04277419  , 0.0474368348, 0.0470985038, 0.052444907 , 0.0522599645, 0.0474612532, 0.0464475842,
                                                                               0.0502996677, 0.0430423045, 0.0394573976, 0.0473562922, 0.0453125145, 0.0460125243, 0.044064253 , 0.0398213776, 0.0430540617, 0.0387714843,
                                                                               0.0397237325, 0.0412224381, 0.0471803936, 0.044070322 , 0.0398309745, 0.0382754766, 0.0348648732, 0.0379125387, 0.0368752998, 0.0385937167,
                                                                               0.0429918874, 0.0387665239, 0.0411653435, 0.0351864351, 0.0355541097, 0.0380412554, 0.0377865354, 0.0304718919, 0.0369081888, 0.0365826653,
                                                                               0.0306400789, 0.0294983356, 0.0300781264, 0.0338435711, 0.0297664256, 0.0338527844, 0.0324185314, 0.031595527 , 0.0281922287, 0.0335709313,
                                                                               0.0267936525, 0.0278416999, 0.0301600826, 0.0326179471, 0.0343652292, 0.0300137688, 0.0348182563, 0.0232944004, 0.029782036 ,0.0300915114 ,
                                                                               0.038316191 , 0.0346790551, 0.0229093319, 0.035083873 , 0.0254789177, 0.0214298553, 0.0174935049, 0.0297266097, 0.0202884035, 0.0236328738,
                                                                               0.0261910642, 0.0272371627, 0.0297956364, 0.0300455071, 0.0298163291, 0.0274258039, 0.0233920794, 0.0259408383, 0.0258447328, 0.0316691088,
                                                                               0.0194050721, 0.0276780071, 0.0208532237, 0.0258880481, 0.0247936698, 0.0289845206, 0.024726798 , 0.0267516057, 0.0287819728, 0.0203384343,
                                                                               0.0231706224, 0.0171479244, 0.0205267786, 0.0232786546, 0.0194167154, 0.0197471546, 0.0178183399, 0.0258777099, 0.0247455594, 0.0242515047,
                                                                               0.0221726491, 0.0226181408, 0.0226395776, 0.0226086578, 0.0210883326, 0.0227333086, 0.0147085177, 0.0223386202, 0.01983367  , 0.0206604746,
                                                                               0.0197211315, 0.0237766939, 0.0209783515, 0.011344157 , 0.0266204631, 0.0176870685, 0.0169198441, 0.0167461505, 0.0162030151, 0.0147993606,
                                                                               0.0180747595, 0.0167922577, 0.0177776729, 0.0165243168, 0.0239157121, 0.0240863509, 0.0159251222, 0.0188905835, 0.0244947291, 0.0231321293,
                                                                               0.0119905702, 0.0212746724, 0.0148101758, 0.016719771 , 0.0135072904, 0.015579234 , 0.0098323132, 0.0160834507, 0.0135100742, 0.0197536654,
                                                                               0.0179672275, 0.0204274339, 0.0143078186, 0.0247076599, 0.019387689 , 0.0217499834, 0.0219773982, 0.0089936524, 0.0125527151, 0.0167172854,
                                                                               0.008620539 , 0.018965114 , 0.0118884784, 0.0158374805, 0.0138487915, 0.011168131 , 0.0158465556, 0.0204534665, 0.0085987594, 0.0065453794,
                                                                               0.0111760053, 0.0130523387, 0.0078459892, 0.0045340041, 0.0083967659, 0.0130307312, 0.0120443823, 0.0089584743, 0.0028922184, 0.0107137702,
                                                                               0.0103779153, 0.0136523262, 0.0086425314, 0.0114911987, 0.0090998251, 0.0119477821, 0.0043828911, 0.0115003009, 0.0185970532, 0.0078177448,
                                                                               0.0056634453, 0.0048790465, 0.0124418735, 0.0079245341, 0.0088885274, 0.0080217008, 0.0072499375, 0.0122358682, 0.0093257179, 0.0078645487,
                                                                               0.0027718707, 0.0088246766, 0.0077172942, 0.0054215409, 0.0086570291, 0.0075382852, 0.0061278759, 0.0125948771, 0.0043380023, 0.0070244377,
                                                                               0.0109764825, 0.0037263349, 0.0008939922, 0.0024223096, 0.0085487449,-0.0015329133, 0.0030449618, 0.0068826451, 0.0034579629, 0.0026976342,
                                                                               0.0061291743, 0.003996367 , 0.0060033092,-0.0027928005, 0.0065211439, 0.0081595563,-0.0053815597, 0.0013933515, 0.0088098754, 0.0066956236,
                                                                              -0.0031690745, 0.0000272022, 0.005218455 , 0.0066656119, 0.0013605669, 0.000957355 , 0.0054547295, 0.0021202667, 0.0034925813, 0.0038470756,
                                                                               0.0049617874, 0.0015549816, 0.0092449042,-0.0000013512, 0.0065971599, 0.0017792874, 0.0080270312, 0.005196937 ,-0.0077396119,-0.0000036945,
                                                                              -0.007687784 , 0.0013188454, 0.0064614105,-0.002016291 , 0.0041230264,-0.0001051494, 0.0054082387, 0.0065087186,-0.0030297052, 0.0029705722,
                                                                               0.0046195152, 0.0009508076, 0.0153167156,-0.0075969086,-0.0000202224, 0.0055445437, 0.0114360936, 0.0107284115, 0.0105391049, 0.0040876097,
                                                                               0.0148011862, 0.0115497462, 0.0041960281, 0.018079972 , 0.0074604464                                                                      };
    static const int m_WbLS_mpt_scintillationWLS_size{ 885 };
    G4double m_WbLS_mpt_scintillationWLS_energies[ m_WbLS_mpt_scintillationWLS_size ]{ m_hc / 222.0, m_hc / 222.4, m_hc / 222.8, m_hc / 223.2, m_hc / 223.6, m_hc / 224.0, m_hc / 224.4, m_hc / 224.8, m_hc / 225.2, m_hc / 225.6,
                                                                                       m_hc / 226.0, m_hc / 226.4, m_hc / 226.8, m_hc / 227.2, m_hc / 227.6, m_hc / 228.0, m_hc / 228.4, m_hc / 228.8, m_hc / 229.2, m_hc / 229.6,
                                                                                       m_hc / 230.0, m_hc / 230.4, m_hc / 230.8, m_hc / 231.2, m_hc / 231.6, m_hc / 232.0, m_hc / 232.4, m_hc / 232.8, m_hc / 233.2, m_hc / 233.6,
                                                                                       m_hc / 234.0, m_hc / 234.4, m_hc / 234.8, m_hc / 235.2, m_hc / 235.6, m_hc / 236.0, m_hc / 236.4, m_hc / 236.8, m_hc / 237.2, m_hc / 237.6,
                                                                                       m_hc / 238.0, m_hc / 238.4, m_hc / 238.8, m_hc / 239.2, m_hc / 239.6, m_hc / 240.0, m_hc / 240.4, m_hc / 240.8, m_hc / 241.2, m_hc / 241.6,
                                                                                       m_hc / 242.0, m_hc / 242.4, m_hc / 242.8, m_hc / 243.2, m_hc / 243.6, m_hc / 244.0, m_hc / 244.4, m_hc / 244.8, m_hc / 245.2, m_hc / 245.6,
                                                                                       m_hc / 246.0, m_hc / 246.4, m_hc / 246.8, m_hc / 247.2, m_hc / 247.6, m_hc / 248.0, m_hc / 248.4, m_hc / 248.8, m_hc / 249.2, m_hc / 249.6,
                                                                                       m_hc / 250.0, m_hc / 250.4, m_hc / 250.8, m_hc / 251.2, m_hc / 251.6, m_hc / 252.0, m_hc / 252.4, m_hc / 252.8, m_hc / 253.2, m_hc / 253.6,
                                                                                       m_hc / 254.0, m_hc / 254.4, m_hc / 254.8, m_hc / 255.2, m_hc / 255.6, m_hc / 256.0, m_hc / 256.4, m_hc / 256.8, m_hc / 257.2, m_hc / 257.6,
                                                                                       m_hc / 258.0, m_hc / 258.4, m_hc / 258.8, m_hc / 259.2, m_hc / 259.6, m_hc / 260.0, m_hc / 260.4, m_hc / 260.8, m_hc / 261.2, m_hc / 261.6,
                                                                                       m_hc / 262.0, m_hc / 262.4, m_hc / 262.8, m_hc / 263.2, m_hc / 263.6, m_hc / 264.0, m_hc / 264.4, m_hc / 264.8, m_hc / 265.2, m_hc / 265.6,
                                                                                       m_hc / 266.0, m_hc / 266.4, m_hc / 266.8, m_hc / 267.2, m_hc / 267.6, m_hc / 268.0, m_hc / 268.4, m_hc / 268.8, m_hc / 269.2, m_hc / 269.6,
                                                                                       m_hc / 270.0, m_hc / 270.4, m_hc / 270.8, m_hc / 271.2, m_hc / 271.6, m_hc / 272.0, m_hc / 272.4, m_hc / 272.8, m_hc / 273.2, m_hc / 273.6,
                                                                                       m_hc / 274.0, m_hc / 274.4, m_hc / 274.8, m_hc / 275.2, m_hc / 275.6, m_hc / 276.0, m_hc / 276.4, m_hc / 276.8, m_hc / 277.2, m_hc / 277.6,
                                                                                       m_hc / 278.0, m_hc / 278.4, m_hc / 278.8, m_hc / 279.2, m_hc / 279.6, m_hc / 280.0, m_hc / 280.4, m_hc / 280.8, m_hc / 281.2, m_hc / 281.6,
                                                                                       m_hc / 282.0, m_hc / 282.4, m_hc / 282.7, m_hc / 283.1, m_hc / 283.5, m_hc / 283.9, m_hc / 284.3, m_hc / 284.7, m_hc / 285.1, m_hc / 285.5,
                                                                                       m_hc / 285.9, m_hc / 286.3, m_hc / 286.7, m_hc / 287.1, m_hc / 287.5, m_hc / 287.9, m_hc / 288.3, m_hc / 288.7, m_hc / 289.1, m_hc / 289.5,
                                                                                       m_hc / 289.9, m_hc / 290.3, m_hc / 290.7, m_hc / 291.1, m_hc / 291.5, m_hc / 291.9, m_hc / 292.3, m_hc / 292.7, m_hc / 293.1, m_hc / 293.5,
                                                                                       m_hc / 293.9, m_hc / 294.3, m_hc / 294.7, m_hc / 295.1, m_hc / 295.5, m_hc / 295.9, m_hc / 296.3, m_hc / 296.7, m_hc / 297.1, m_hc / 297.5,
                                                                                       m_hc / 297.9, m_hc / 298.3, m_hc / 298.7, m_hc / 299.1, m_hc / 299.5, m_hc / 299.9, m_hc / 300.3, m_hc / 300.7, m_hc / 301.1, m_hc / 301.5,
                                                                                       m_hc / 301.9, m_hc / 302.3, m_hc / 302.7, m_hc / 303.1, m_hc / 303.5, m_hc / 303.9, m_hc / 304.3, m_hc / 304.7, m_hc / 305.1, m_hc / 305.5,
                                                                                       m_hc / 305.9, m_hc / 306.3, m_hc / 306.7, m_hc / 307.1, m_hc / 307.5, m_hc / 307.9, m_hc / 308.3, m_hc / 308.7, m_hc / 309.1, m_hc / 309.5,
                                                                                       m_hc / 309.9, m_hc / 310.3, m_hc / 310.7, m_hc / 311.1, m_hc / 311.5, m_hc / 311.9, m_hc / 312.3, m_hc / 312.7, m_hc / 313.1, m_hc / 313.5,
                                                                                       m_hc / 313.9, m_hc / 314.3, m_hc / 314.6, m_hc / 315.0, m_hc / 315.4, m_hc / 315.8, m_hc / 316.2, m_hc / 316.6, m_hc / 317.0, m_hc / 317.4,
                                                                                       m_hc / 317.8, m_hc / 318.2, m_hc / 318.6, m_hc / 319.0, m_hc / 319.4, m_hc / 319.8, m_hc / 320.2, m_hc / 320.6, m_hc / 321.0, m_hc / 321.4,
                                                                                       m_hc / 321.8, m_hc / 322.2, m_hc / 322.6, m_hc / 323.0, m_hc / 323.4, m_hc / 323.8, m_hc / 324.2, m_hc / 324.6, m_hc / 325.0, m_hc / 325.4,
                                                                                       m_hc / 325.8, m_hc / 326.2, m_hc / 326.6, m_hc / 327.0, m_hc / 327.4, m_hc / 327.8, m_hc / 328.2, m_hc / 328.6, m_hc / 329.0, m_hc / 329.4,
                                                                                       m_hc / 329.8, m_hc / 330.2, m_hc / 330.6, m_hc / 331.0, m_hc / 331.4, m_hc / 331.8, m_hc / 332.2, m_hc / 332.6, m_hc / 333.0, m_hc / 333.4,
                                                                                       m_hc / 333.8, m_hc / 334.2, m_hc / 334.6, m_hc / 335.0, m_hc / 335.4, m_hc / 335.8, m_hc / 336.1, m_hc / 336.5, m_hc / 336.9, m_hc / 337.3,
                                                                                       m_hc / 337.7, m_hc / 338.1, m_hc / 338.5, m_hc / 338.9, m_hc / 339.3, m_hc / 339.7, m_hc / 340.1, m_hc / 340.5, m_hc / 340.9, m_hc / 341.3,
                                                                                       m_hc / 341.7, m_hc / 342.1, m_hc / 342.5, m_hc / 342.9, m_hc / 343.3, m_hc / 343.7, m_hc / 344.1, m_hc / 344.5, m_hc / 344.9, m_hc / 345.3,
                                                                                       m_hc / 345.7, m_hc / 346.1, m_hc / 346.5, m_hc / 346.9, m_hc / 347.3, m_hc / 347.7, m_hc / 348.1, m_hc / 348.5, m_hc / 348.9, m_hc / 349.3,
                                                                                       m_hc / 349.7, m_hc / 350.1, m_hc / 350.5, m_hc / 350.9, m_hc / 351.3, m_hc / 351.7, m_hc / 352.1, m_hc / 352.5, m_hc / 352.9, m_hc / 353.2,
                                                                                       m_hc / 353.6, m_hc / 354.0, m_hc / 354.4, m_hc / 354.8, m_hc / 355.2, m_hc / 355.6, m_hc / 356.0, m_hc / 356.4, m_hc / 356.8, m_hc / 357.2,
                                                                                       m_hc / 357.6, m_hc / 358.0, m_hc / 358.4, m_hc / 358.8, m_hc / 359.2, m_hc / 359.6, m_hc / 360.0, m_hc / 360.4, m_hc / 360.8, m_hc / 361.2,
                                                                                       m_hc / 361.6, m_hc / 362.0, m_hc / 362.4, m_hc / 362.8, m_hc / 363.2, m_hc / 363.6, m_hc / 364.0, m_hc / 364.4, m_hc / 364.8, m_hc / 365.2,
                                                                                       m_hc / 365.6, m_hc / 366.0, m_hc / 366.4, m_hc / 366.8, m_hc / 367.2, m_hc / 367.6, m_hc / 367.9, m_hc / 368.3, m_hc / 368.7, m_hc / 369.1,
                                                                                       m_hc / 369.5, m_hc / 369.9, m_hc / 370.3, m_hc / 370.7, m_hc / 371.1, m_hc / 371.5, m_hc / 371.9, m_hc / 372.3, m_hc / 372.7, m_hc / 373.1,
                                                                                       m_hc / 373.5, m_hc / 373.9, m_hc / 374.3, m_hc / 374.7, m_hc / 375.1, m_hc / 375.5, m_hc / 375.9, m_hc / 376.3, m_hc / 376.7, m_hc / 377.1,
                                                                                       m_hc / 377.5, m_hc / 377.9, m_hc / 378.3, m_hc / 378.7, m_hc / 379.1, m_hc / 379.5, m_hc / 379.9, m_hc / 380.3, m_hc / 380.6, m_hc / 381.0,
                                                                                       m_hc / 381.4, m_hc / 381.8, m_hc / 382.2, m_hc / 382.6, m_hc / 383.0, m_hc / 383.4, m_hc / 383.8, m_hc / 384.2, m_hc / 384.6, m_hc / 385.0,
                                                                                       m_hc / 385.4, m_hc / 385.8, m_hc / 386.2, m_hc / 386.6, m_hc / 387.0, m_hc / 387.4, m_hc / 387.8, m_hc / 388.2, m_hc / 388.6, m_hc / 389.0,
                                                                                       m_hc / 389.4, m_hc / 389.8, m_hc / 390.2, m_hc / 390.6, m_hc / 391.0, m_hc / 391.4, m_hc / 391.8, m_hc / 392.2, m_hc / 392.5, m_hc / 392.9,
                                                                                       m_hc / 393.3, m_hc / 393.7, m_hc / 394.1, m_hc / 394.5, m_hc / 394.9, m_hc / 395.3, m_hc / 395.7, m_hc / 396.1, m_hc / 396.5, m_hc / 396.9,
                                                                                       m_hc / 397.3, m_hc / 397.7, m_hc / 398.1, m_hc / 398.5, m_hc / 398.9, m_hc / 399.3, m_hc / 399.7, m_hc / 400.1, m_hc / 400.5, m_hc / 400.9,
                                                                                       m_hc / 401.3, m_hc / 401.7, m_hc / 402.1, m_hc / 402.5, m_hc / 402.8, m_hc / 403.2, m_hc / 403.6, m_hc / 404.0, m_hc / 404.4, m_hc / 404.8,
                                                                                       m_hc / 405.2, m_hc / 405.6, m_hc / 406.0, m_hc / 406.4, m_hc / 406.8, m_hc / 407.2, m_hc / 407.6, m_hc / 408.0, m_hc / 408.4, m_hc / 408.8,
                                                                                       m_hc / 409.2, m_hc / 409.6, m_hc / 410.0, m_hc / 410.4, m_hc / 410.8, m_hc / 411.2, m_hc / 411.6, m_hc / 412.0, m_hc / 412.4, m_hc / 412.7,
                                                                                       m_hc / 413.1, m_hc / 413.5, m_hc / 413.9, m_hc / 414.3, m_hc / 414.7, m_hc / 415.1, m_hc / 415.5, m_hc / 415.9, m_hc / 416.3, m_hc / 416.7,
                                                                                       m_hc / 417.1, m_hc / 417.5, m_hc / 417.9, m_hc / 418.3, m_hc / 418.7, m_hc / 419.1, m_hc / 419.5, m_hc / 419.9, m_hc / 420.3, m_hc / 420.7,
                                                                                       m_hc / 421.1, m_hc / 421.5, m_hc / 421.8, m_hc / 422.2, m_hc / 422.6, m_hc / 423.0, m_hc / 423.4, m_hc / 423.8, m_hc / 424.2, m_hc / 424.6,
                                                                                       m_hc / 425.0, m_hc / 425.4, m_hc / 425.8, m_hc / 426.2, m_hc / 426.6, m_hc / 427.0, m_hc / 427.4, m_hc / 427.8, m_hc / 428.2, m_hc / 428.6,
                                                                                       m_hc / 429.0, m_hc / 429.4, m_hc / 429.8, m_hc / 430.1, m_hc / 430.5, m_hc / 430.9, m_hc / 431.3, m_hc / 431.7, m_hc / 432.1, m_hc / 432.5,
                                                                                       m_hc / 432.9, m_hc / 433.3, m_hc / 433.7, m_hc / 434.1, m_hc / 434.5, m_hc / 434.9, m_hc / 435.3, m_hc / 435.7, m_hc / 436.1, m_hc / 436.5,
                                                                                       m_hc / 436.9, m_hc / 437.3, m_hc / 437.7, m_hc / 438.1, m_hc / 438.4, m_hc / 438.8, m_hc / 439.2, m_hc / 439.6, m_hc / 440.0, m_hc / 440.4,
                                                                                       m_hc / 440.8, m_hc / 441.2, m_hc / 441.6, m_hc / 442.0, m_hc / 442.4, m_hc / 442.8, m_hc / 443.2, m_hc / 443.6, m_hc / 444.0, m_hc / 444.4,
                                                                                       m_hc / 444.8, m_hc / 445.2, m_hc / 445.6, m_hc / 445.9, m_hc / 446.3, m_hc / 446.7, m_hc / 447.1, m_hc / 447.5, m_hc / 447.9, m_hc / 448.3,
                                                                                       m_hc / 448.7, m_hc / 449.1, m_hc / 449.5, m_hc / 449.9, m_hc / 450.3, m_hc / 450.7, m_hc / 451.1, m_hc / 451.5, m_hc / 451.9, m_hc / 452.3,
                                                                                       m_hc / 452.7, m_hc / 453.0, m_hc / 453.4, m_hc / 453.8, m_hc / 454.2, m_hc / 454.6, m_hc / 455.0, m_hc / 455.4, m_hc / 455.8, m_hc / 456.2,
                                                                                       m_hc / 456.6, m_hc / 457.0, m_hc / 457.4, m_hc / 457.8, m_hc / 458.2, m_hc / 458.6, m_hc / 459.0, m_hc / 459.4, m_hc / 459.8, m_hc / 460.1,
                                                                                       m_hc / 460.5, m_hc / 460.9, m_hc / 461.3, m_hc / 461.7, m_hc / 462.1, m_hc / 462.5, m_hc / 462.9, m_hc / 463.3, m_hc / 463.7, m_hc / 464.1,
                                                                                       m_hc / 464.5, m_hc / 464.9, m_hc / 465.3, m_hc / 465.7, m_hc / 466.1, m_hc / 466.5, m_hc / 466.8, m_hc / 467.2, m_hc / 467.6, m_hc / 468.0,
                                                                                       m_hc / 468.4, m_hc / 468.8, m_hc / 469.2, m_hc / 469.6, m_hc / 470.0, m_hc / 470.4, m_hc / 470.8, m_hc / 471.2, m_hc / 471.6, m_hc / 472.0,
                                                                                       m_hc / 472.4, m_hc / 472.8, m_hc / 473.1, m_hc / 473.5, m_hc / 473.9, m_hc / 474.3, m_hc / 474.7, m_hc / 475.1, m_hc / 475.5, m_hc / 475.9,
                                                                                       m_hc / 476.3, m_hc / 476.7, m_hc / 477.1, m_hc / 477.5, m_hc / 477.9, m_hc / 478.3, m_hc / 478.7, m_hc / 479.1, m_hc / 479.4, m_hc / 479.8,
                                                                                       m_hc / 480.2, m_hc / 480.6, m_hc / 481.0, m_hc / 481.4, m_hc / 481.8, m_hc / 482.2, m_hc / 482.6, m_hc / 483.0, m_hc / 483.4, m_hc / 483.8,
                                                                                       m_hc / 484.2, m_hc / 484.6, m_hc / 485.0, m_hc / 485.3, m_hc / 485.7, m_hc / 486.1, m_hc / 486.5, m_hc / 486.9, m_hc / 487.3, m_hc / 487.7,
                                                                                       m_hc / 488.1, m_hc / 488.5, m_hc / 488.9, m_hc / 489.3, m_hc / 489.7, m_hc / 490.1, m_hc / 490.5, m_hc / 490.9, m_hc / 491.2, m_hc / 491.6,
                                                                                       m_hc / 492.0, m_hc / 492.4, m_hc / 492.8, m_hc / 493.2, m_hc / 493.6, m_hc / 494.0, m_hc / 494.4, m_hc / 494.8, m_hc / 495.2, m_hc / 495.6,
                                                                                       m_hc / 496.0, m_hc / 496.4, m_hc / 496.7, m_hc / 497.1, m_hc / 497.5, m_hc / 497.9, m_hc / 498.3, m_hc / 498.7, m_hc / 499.1, m_hc / 499.5,
                                                                                       m_hc / 499.9, m_hc / 500.3, m_hc / 500.7, m_hc / 501.1, m_hc / 501.5, m_hc / 501.9, m_hc / 502.2, m_hc / 502.6, m_hc / 503.0, m_hc / 503.4,
                                                                                       m_hc / 503.8, m_hc / 504.2, m_hc / 504.6, m_hc / 505.0, m_hc / 505.4, m_hc / 505.8, m_hc / 506.2, m_hc / 506.6, m_hc / 507.0, m_hc / 507.3,
                                                                                       m_hc / 507.7, m_hc / 508.1, m_hc / 508.5, m_hc / 508.9, m_hc / 509.3, m_hc / 509.7, m_hc / 510.1, m_hc / 510.5, m_hc / 510.9, m_hc / 511.3,
                                                                                       m_hc / 511.7, m_hc / 512.1, m_hc / 512.4, m_hc / 512.8, m_hc / 513.2, m_hc / 513.6, m_hc / 514.0, m_hc / 514.4, m_hc / 514.8, m_hc / 515.2,
                                                                                       m_hc / 515.6, m_hc / 516.0, m_hc / 516.4, m_hc / 516.8, m_hc / 517.2, m_hc / 517.5, m_hc / 517.9, m_hc / 518.3, m_hc / 518.7, m_hc / 519.1,
                                                                                       m_hc / 519.5, m_hc / 519.9, m_hc / 520.3, m_hc / 520.7, m_hc / 521.1, m_hc / 521.5, m_hc / 521.9, m_hc / 522.2, m_hc / 522.6, m_hc / 523.0,
                                                                                       m_hc / 523.4, m_hc / 523.8, m_hc / 524.2, m_hc / 524.6, m_hc / 525.0, m_hc / 525.4, m_hc / 525.8, m_hc / 526.2, m_hc / 526.6, m_hc / 526.9,
                                                                                       m_hc / 527.3, m_hc / 527.7, m_hc / 528.1, m_hc / 528.5, m_hc / 528.9, m_hc / 529.3, m_hc / 529.7, m_hc / 530.1, m_hc / 530.5, m_hc / 530.9,
                                                                                       m_hc / 531.3, m_hc / 531.6, m_hc / 532.0, m_hc / 532.4, m_hc / 532.8, m_hc / 533.2, m_hc / 533.6, m_hc / 534.0, m_hc / 534.4, m_hc / 534.8,
                                                                                       m_hc / 535.2, m_hc / 535.6, m_hc / 535.9, m_hc / 536.3, m_hc / 536.7, m_hc / 537.1, m_hc / 537.5, m_hc / 537.9, m_hc / 538.3, m_hc / 538.7,
                                                                                       m_hc / 539.1, m_hc / 539.5, m_hc / 539.9, m_hc / 540.3, m_hc / 540.6, m_hc / 541.0, m_hc / 541.4, m_hc / 541.8, m_hc / 542.2, m_hc / 542.6,
                                                                                       m_hc / 543.0, m_hc / 543.4, m_hc / 543.8, m_hc / 544.2, m_hc / 544.6, m_hc / 544.9, m_hc / 545.3, m_hc / 545.7, m_hc / 546.1, m_hc / 546.5,
                                                                                       m_hc / 546.9, m_hc / 547.3, m_hc / 547.7, m_hc / 548.1, m_hc / 548.5, m_hc / 548.9, m_hc / 549.2, m_hc / 549.6, m_hc / 550.0, m_hc / 550.4,
                                                                                       m_hc / 550.8, m_hc / 551.2, m_hc / 551.6, m_hc / 552.0, m_hc / 552.4, m_hc / 552.8, m_hc / 553.1, m_hc / 553.5, m_hc / 553.9, m_hc / 554.3,
                                                                                       m_hc / 554.7, m_hc / 555.1, m_hc / 555.5, m_hc / 555.9, m_hc / 556.3, m_hc / 556.7, m_hc / 557.1, m_hc / 557.4, m_hc / 557.8, m_hc / 558.2,
                                                                                       m_hc / 558.6, m_hc / 559.0, m_hc / 559.4, m_hc / 559.8, m_hc / 560.2, m_hc / 560.6, m_hc / 561.0, m_hc / 561.3, m_hc / 561.7, m_hc / 562.1,
                                                                                       m_hc / 562.5, m_hc / 562.9, m_hc / 563.3, m_hc / 563.7, m_hc / 564.1, m_hc / 564.5, m_hc / 564.9, m_hc / 565.2, m_hc / 565.6, m_hc / 566.0,
                                                                                       m_hc / 566.4, m_hc / 566.8, m_hc / 567.2, m_hc / 567.6, m_hc / 568.0, m_hc / 568.4, m_hc / 568.8, m_hc / 569.1, m_hc / 569.5, m_hc / 569.9,
                                                                                       m_hc / 570.3, m_hc / 570.7, m_hc / 571.1, m_hc / 571.5, m_hc / 571.9 };
    G4double m_WbLS_mpt_scintillationWLS_values[ m_WbLS_mpt_scintillationWLS_size ]{ 0.0360006124, 0.0434853417, 0.0432652238, 0.02600129  , 0.0233379271, 0.033721551 , 0.029973259 , 0.0334315864, 0.0189800738, 0.0388781665,
                                                                                     0.0361808399, 0.0330346063, 0.0294763364, 0.0412574183, 0.0198393893, 0.0250410021, 0.0380327292, 0.0330001248, 0.0312274783, 0.0213405995,
                                                                                     0.0327245914, 0.0291879874, 0.0225559679, 0.0286205731, 0.014180487 , 0.0120643174, 0.0321327344, 0.0208237731, 0.0223725   , 0.013792754 ,
                                                                                     0.0152093082, 0.0163020561, 0.0241327549, 0.0203439666, 0.0313212988, 0.0245139201, 0.0269615847, 0.0282244522, 0.0113222609, 0.0161596889,
                                                                                     0.0232753016, 0.0228552515, 0.0183123106, 0.0216272449, 0.0131731662, 0.0232426199, 0.0240558187, 0.0257491667, 0.0219355412, 0.0240633542,
                                                                                     0.0163312953, 0.0224550606, 0.0228547663, 0.014236389 , 0.0183747492, 0.0210231048, 0.0172338015, 0.0166273682, 0.0108896025, 0.0124477094,
                                                                                     0.0247179195, 0.0263929167, 0.0159662121, 0.0103989794, 0.018283146 , 0.0144866189, 0.0222452145, 0.0210229354, 0.0225470392, 0.0194418481,
                                                                                     0.0213026891, 0.0183083924, 0.0214327231, 0.0240548904, 0.0147433231, 0.0188857478, 0.0169836542, 0.0237993246, 0.0206549179, 0.0137782022,
                                                                                     0.0163379553, 0.0242911783, 0.0195608405, 0.0257604536, 0.0182903128, 0.0180349652, 0.0198893049, 0.014484403 , 0.0198167206, 0.0215331358,
                                                                                     0.0233024604, 0.0146517741, 0.0239295348, 0.0209897062, 0.0223609664, 0.0226831382, 0.0216562632, 0.0210260363, 0.014865163 , 0.0198796566,
                                                                                     0.0179122675, 0.0187225863, 0.0207886925, 0.0166616315, 0.0240816792, 0.0224486785, 0.0177482846, 0.0224659409, 0.0141734422, 0.0185783826,
                                                                                     0.0209559457, 0.0139040009, 0.0208455066, 0.0190691629, 0.0166890369, 0.0131965532, 0.0241619006, 0.0139414681, 0.0152742189, 0.0180916587,
                                                                                     0.0197939652, 0.0143165128, 0.0228917131, 0.0234829575, 0.0114395388, 0.0163371827, 0.0214205702, 0.0200038167, 0.0220641969, 0.026536909 ,
                                                                                     0.0302179986, 0.0259100622, 0.0270630354, 0.0245573642, 0.0089894971, 0.0140436277, 0.0195803811, 0.0210290695, 0.0189525816, 0.0236695386,
                                                                                     0.0226541104, 0.0177075159, 0.0192363511, 0.0112580631, 0.0177006811, 0.0138276028, 0.019265284 , 0.0154398335, 0.0154522575, 0.0181947386,
                                                                                     0.0164047958, 0.0194974749, 0.021023487 , 0.0158365291, 0.0212127014, 0.0137352298, 0.0249113733, 0.0213920859, 0.0152184158, 0.0185912525,
                                                                                     0.0097033621, 0.0262373774, 0.0300488778, 0.0260733403, 0.0287036949, 0.0263613817, 0.0266374802, 0.0388163283, 0.0386846802, 0.0379349852,
                                                                                     0.0349013632, 0.0337913759, 0.0351834982, 0.0386184983, 0.044793914 , 0.0422677086, 0.0445959755, 0.0484959985, 0.0449241743, 0.050563372 ,
                                                                                     0.049318248 , 0.0467531781, 0.0467512793, 0.0375717736, 0.0461220933, 0.051323912 , 0.0517906142, 0.0425476385, 0.0470375561, 0.0492374519,
                                                                                     0.0574973422, 0.053453636 , 0.0507549283, 0.050446487 , 0.0552257444, 0.0603178775, 0.051049074 , 0.0539921418, 0.0511432129, 0.0589777797,
                                                                                     0.0616186243, 0.0520250061, 0.0575066816, 0.0620283782, 0.0501792793, 0.0553466437, 0.0517237844, 0.0502110027, 0.0486157742, 0.0535640887,
                                                                                     0.053303408 , 0.0464243043, 0.059517447 , 0.0491781875, 0.0530352191, 0.0572120887, 0.0492608782, 0.0489966874, 0.0526269465, 0.0481007666,
                                                                                     0.0447057803, 0.0512595219, 0.0541127714, 0.0340289297, 0.0493167802, 0.0449113139, 0.0530150699, 0.0485251143, 0.0376974381, 0.0507612738,
                                                                                     0.0445686039, 0.0377243082, 0.0452034455, 0.0436844064, 0.04559641  , 0.0466746765, 0.0444242701, 0.0310253886, 0.0426471024, 0.0421788322,
                                                                                     0.0402217366, 0.045456199 , 0.0397766637, 0.0361028778, 0.0380480658, 0.0384483393, 0.0364400717, 0.0312767542, 0.0311024711, 0.0435257716,
                                                                                     0.0368309   , 0.0405335661, 0.0334528131, 0.0373963805, 0.034944486 , 0.042017541 , 0.0394008952, 0.0363520289, 0.0311013869, 0.030776743 ,
                                                                                     0.0390879774, 0.0381611938, 0.0287443375, 0.03256074  , 0.0337064137, 0.0355538305, 0.0432971221, 0.033664207 , 0.038570888 , 0.0340192326,
                                                                                     0.0369074447, 0.0290419392, 0.0354024587, 0.0394559772, 0.0337908609, 0.0410424925, 0.033504904 , 0.0357107997, 0.0359733954, 0.0451283878,
                                                                                     0.0501327045, 0.0524999863, 0.0521308629, 0.0494927574, 0.0534598338, 0.0632464653, 0.0595975749, 0.074938267 , 0.0754141933, 0.084430795 ,
                                                                                     0.0899022989, 0.1081005951, 0.1149026231, 0.1236461364, 0.1334740598, 0.1546893255, 0.1598302602, 0.1781296413, 0.1998283551, 0.2172820604,
                                                                                     0.2389156182, 0.2477088384, 0.2680982983, 0.2922819663, 0.3007191824, 0.3300877482, 0.3447180002, 0.3457306907, 0.3732153944, 0.3899848384,
                                                                                     0.4011389218, 0.3960670205, 0.4189107859, 0.4337964843, 0.4330434837, 0.445936674 , 0.4550608253, 0.4588709527, 0.4688909069, 0.4789815547,
                                                                                     0.4828605842, 0.4913215965, 0.5030406546, 0.5125473278, 0.5161465683, 0.5209576778, 0.5361323243, 0.5422499718, 0.5534855153, 0.5642012995,
                                                                                     0.5769714382, 0.5920372286, 0.6040697805, 0.6262202489, 0.6295577218, 0.6608218609, 0.6580608272, 0.663921311 , 0.7007231306, 0.7087308407,
                                                                                     0.7229765433, 0.7381978175, 0.7687459353, 0.7793342064, 0.7908507938, 0.8140637815, 0.8417408088, 0.8516712753, 0.8679837523, 0.8828183357,
                                                                                     0.8930979107, 0.9030428572, 0.9346108243, 0.9323752679, 0.9527754779, 0.9646525745, 0.9723403341, 0.9768520788, 0.9867240805, 0.9861449592,
                                                                                     0.994523373 , 0.9990912473, 0.9996223694, 0.9947960399, 0.9914685243, 1.0         , 0.9971230721, 0.9892315815, 0.9933720031, 0.9691867128,0.9698875181,
                                                                                     0.9827435122, 0.9656857517, 0.9702198886, 0.9592185852, 0.9570715731, 0.9488581329, 0.9459099787, 0.936008735 , 0.9474562457, 0.9428810243,
                                                                                     0.9435310304, 0.9359218564, 0.9304682477, 0.9323184782, 0.9309649534, 0.9329448316, 0.9320405378, 0.9273340817, 0.9234638318, 0.917826846 ,
                                                                                     0.9259217492, 0.9258602404, 0.9236182097, 0.9244385184, 0.9200411311, 0.9190830143, 0.9141197686, 0.9181235098, 0.9146539835, 0.9050022366,
                                                                                     0.9023300765, 0.8976813397, 0.9041373196, 0.8937833456, 0.892265018 , 0.8812571388, 0.8828541197, 0.8815111513, 0.8738891629, 0.8658082221,
                                                                                     0.8641470068, 0.8628073034, 0.8526618975, 0.8375096649, 0.8398163405, 0.8267873861, 0.82436982  , 0.8132054445, 0.8043459327, 0.8003235561,
                                                                                     0.7897782196, 0.7756406548, 0.7681101206, 0.7568131997, 0.7549242457, 0.7510062406, 0.7358943241, 0.7169145023, 0.715479699 , 0.7040168816,
                                                                                     0.6973117574, 0.6960640746, 0.6898165653, 0.6648281826, 0.6660821662, 0.6628395627, 0.6483520683, 0.6374386546, 0.6353745623, 0.625425642 ,
                                                                                     0.6215322884, 0.6152677945, 0.6083809086, 0.5990979313, 0.5910476351, 0.5845783814, 0.5853605954, 0.581014128 , 0.5683669744, 0.560684022 ,
                                                                                     0.5640026034, 0.5571752137, 0.5477354028, 0.5379068167, 0.5368865026, 0.5337560785, 0.5252802934, 0.5178209258, 0.5068670253, 0.5115104182,
                                                                                     0.5117480926, 0.4967845188, 0.4889767259, 0.4772044521, 0.4659356279, 0.4724784091, 0.4611603687, 0.465413017 , 0.4570219123, 0.4505178708,
                                                                                     0.4458788949, 0.4375752434, 0.4247302164, 0.421817575 , 0.4269631544, 0.4160550358, 0.4043091225, 0.3976120257, 0.3955820476, 0.3894015049,
                                                                                     0.3861093125, 0.3865411902, 0.3781785209, 0.3711352269, 0.3655817315, 0.3575331524, 0.3620170145, 0.3462039416, 0.3438848582, 0.3325343719,
                                                                                     0.3362618452, 0.3231746685, 0.3295612233, 0.3163303566, 0.3145048699, 0.3099347783, 0.3011148859, 0.2992121499, 0.2945465356, 0.2979482645,
                                                                                     0.2893462049, 0.288751991 , 0.2776902603, 0.2769782928, 0.270053876 , 0.2638554758, 0.2607599262, 0.26228501  , 0.2602310716, 0.2575118068,
                                                                                     0.2433034047, 0.2497358769, 0.2323645534, 0.2382247757, 0.2331222365, 0.2261130188, 0.2300640295, 0.2290656835, 0.2135578709, 0.2158616774,
                                                                                     0.202198811 , 0.2149233155, 0.2099723434, 0.201999154 , 0.2019236816, 0.2016210382, 0.1894141612, 0.1875696216, 0.1842875479, 0.1798380819,
                                                                                     0.1803230913, 0.18215758  , 0.1676756043, 0.1755149933, 0.1728114946, 0.166306022 , 0.1716419149, 0.1664200988, 0.1629996234, 0.1591386668,
                                                                                     0.1547539556, 0.1534158582, 0.1472522051, 0.1476032976, 0.1502208934, 0.1463197089, 0.1407015794, 0.1469707722, 0.1376181855, 0.1382524538,
                                                                                     0.1382929583, 0.1367997376, 0.1315469569, 0.133061838 , 0.1388091355, 0.1268676812, 0.127658187 , 0.1242017704, 0.1234443624, 0.1197361154,
                                                                                     0.1214337691, 0.1136644437, 0.115743653 , 0.1091228838, 0.114282359 , 0.1156957134, 0.1068103601, 0.1062400712, 0.0988350253, 0.0986795957,
                                                                                     0.1009251881, 0.1051490229, 0.097588336 , 0.1003166691, 0.0973551787, 0.0952477819, 0.0929788811, 0.0914255232, 0.0832416   , 0.0904785999,
                                                                                     0.0856957619, 0.0880658885, 0.0902370235, 0.0850029365, 0.0790683057, 0.0751442912, 0.079545697 , 0.0797114757, 0.0753204311, 0.07665488  ,
                                                                                     0.0758540185, 0.0743465672, 0.0762344545, 0.0658907361, 0.0782958674, 0.067855111 , 0.0694521041, 0.0720343836, 0.0716177665, 0.0673965299,
                                                                                     0.0649165171, 0.0666560861, 0.0721165377, 0.0653355425, 0.0679188832, 0.0650313447, 0.0607216803, 0.0615832144, 0.0631712951, 0.0587815855,
                                                                                     0.0639004086, 0.0547899864, 0.06021428  , 0.0521647034, 0.0534495918, 0.0575515744, 0.0505102009, 0.0593629892, 0.0512456341, 0.0555482943,
                                                                                     0.057869248 , 0.0516390851, 0.04277419  , 0.0474368348, 0.0470985038, 0.052444907 , 0.0522599645, 0.0474612532, 0.0464475842, 0.0502996677,
                                                                                     0.0430423045, 0.0394573976, 0.0473562922, 0.0453125145, 0.0460125243, 0.044064253 , 0.0398213776, 0.0430540617, 0.0387714843, 0.0397237325,
                                                                                     0.0412224381, 0.0471803936, 0.044070322 , 0.0398309745, 0.0382754766, 0.0348648732, 0.0379125387, 0.0368752998, 0.0385937167, 0.0429918874,
                                                                                     0.0387665239, 0.0411653435, 0.0351864351, 0.0355541097, 0.0380412554, 0.0377865354, 0.0304718919, 0.0369081888, 0.0365826653, 0.0306400789,
                                                                                     0.0294983356, 0.0300781264, 0.0338435711, 0.0297664256, 0.0338527844, 0.0324185314, 0.031595527 , 0.0281922287, 0.0335709313, 0.0267936525,
                                                                                     0.0278416999, 0.0301600826, 0.0326179471, 0.0343652292, 0.0300137688, 0.0348182563, 0.0232944004, 0.029782036 , 0.0300915114, 0.038316191 ,
                                                                                     0.0346790551, 0.0229093319, 0.035083873 , 0.0254789177, 0.0214298553, 0.0174935049, 0.0297266097, 0.0202884035, 0.0236328738, 0.0261910642,
                                                                                     0.0272371627, 0.0297956364, 0.0300455071, 0.0298163291, 0.0274258039, 0.0233920794, 0.0259408383, 0.0258447328, 0.0316691088, 0.0194050721,
                                                                                     0.0276780071, 0.0208532237, 0.0258880481, 0.0247936698, 0.0289845206, 0.024726798 , 0.0267516057, 0.0287819728, 0.0203384343, 0.0231706224,
                                                                                     0.0171479244, 0.0205267786, 0.0232786546, 0.0194167154, 0.0197471546, 0.0178183399, 0.0258777099, 0.0247455594, 0.0242515047, 0.0221726491,
                                                                                     0.0226181408, 0.0226395776, 0.0226086578, 0.0210883326, 0.0227333086, 0.0147085177, 0.0223386202, 0.01983367  , 0.0206604746, 0.0197211315,
                                                                                     0.0237766939, 0.0209783515, 0.011344157 , 0.0266204631, 0.0176870685, 0.0169198441, 0.0167461505, 0.0162030151, 0.0147993606, 0.0180747595,
                                                                                     0.0167922577, 0.0177776729, 0.0165243168, 0.0239157121, 0.0240863509, 0.0159251222, 0.0188905835, 0.0244947291, 0.0231321293, 0.0119905702,
                                                                                     0.0212746724, 0.0148101758, 0.016719771 , 0.0135072904, 0.015579234 , 0.0098323132, 0.0160834507, 0.0135100742, 0.0197536654, 0.0179672275,
                                                                                     0.0204274339, 0.0143078186, 0.0247076599, 0.019387689 , 0.0217499834, 0.0219773982, 0.0089936524, 0.0125527151, 0.0167172854, 0.008620539 ,
                                                                                     0.018965114 , 0.0118884784, 0.0158374805, 0.0138487915, 0.011168131 , 0.0158465556, 0.0204534665, 0.0085987594, 0.0065453794, 0.0111760053,
                                                                                     0.0130523387, 0.0078459892, 0.0045340041, 0.0083967659, 0.0130307312, 0.0120443823, 0.0089584743, 0.0028922184, 0.0107137702, 0.0103779153,
                                                                                     0.0136523262, 0.0086425314, 0.0114911987, 0.0090998251, 0.0119477821, 0.0043828911, 0.0115003009, 0.0185970532, 0.0078177448, 0.0056634453,
                                                                                     0.0048790465, 0.0124418735, 0.0079245341, 0.0088885274, 0.0080217008, 0.0072499375, 0.0122358682, 0.0093257179, 0.0078645487, 0.0027718707,
                                                                                     0.0088246766, 0.0077172942, 0.0054215409, 0.0086570291, 0.0075382852, 0.0061278759, 0.0125948771, 0.0043380023, 0.0070244377, 0.0109764825,
                                                                                     0.0037263349, 0.0008939922, 0.0024223096, 0.0085487449,-0.0015329133, 0.0030449618, 0.0068826451, 0.0034579629, 0.0026976342, 0.0061291743,
                                                                                     0.003996367 , 0.0060033092,-0.0027928005, 0.0065211439, 0.0081595563,-0.0053815597, 0.0013933515, 0.0088098754, 0.0066956236,-0.0031690745,
                                                                                     0.0000272022, 0.005218455 , 0.0066656119, 0.0013605669, 0.000957355 , 0.0054547295, 0.0021202667, 0.0034925813, 0.0038470756, 0.0049617874,
                                                                                     0.0015549816, 0.0092449042,-0.0000013512, 0.0065971599, 0.0017792874, 0.0080270312, 0.005196937 ,-0.0077396119,-0.0000036945,-0.007687784 ,
                                                                                     0.0013188454, 0.0064614105,-0.002016291 , 0.0041230264,-0.0001051494, 0.0054082387, 0.0065087186,-0.0030297052, 0.0029705722, 0.0046195152,
                                                                                     0.0009508076, 0.0153167156,-0.0075969086,-0.0000202224, 0.0055445437, 0.0114360936, 0.0107284115, 0.0105391049, 0.0040876097, 0.0148011862,
                                                                                     0.0115497462, 0.0041960281, 0.018079972 , 0.0074604464 };
    static const int m_WbLS_mpt_absLength_size{ 151 };
    G4double m_WbLS_mpt_absLength_energies[ m_WbLS_mpt_absLength_size ]{ m_hc / 200.0, m_hc / 204.0, m_hc / 208.0, m_hc / 212.0, m_hc / 216.0, m_hc / 220.0, m_hc / 224.0, m_hc / 228.0, m_hc / 232.0, m_hc / 236.0, 
                                                                         m_hc / 240.0, m_hc / 244.0, m_hc / 248.0, m_hc / 252.0, m_hc / 256.0, m_hc / 260.0, m_hc / 264.0, m_hc / 268.0, m_hc / 272.0, m_hc / 276.0, 
                                                                         m_hc / 280.0, m_hc / 284.0, m_hc / 288.0, m_hc / 292.0, m_hc / 296.0, m_hc / 300.0, m_hc / 304.0, m_hc / 308.0, m_hc / 312.0, m_hc / 316.0, 
                                                                         m_hc / 320.0, m_hc / 324.0, m_hc / 328.0, m_hc / 332.0, m_hc / 336.0, m_hc / 340.0, m_hc / 344.0, m_hc / 348.0, m_hc / 352.0, m_hc / 356.0, 
                                                                         m_hc / 360.0, m_hc / 364.0, m_hc / 368.0, m_hc / 372.0, m_hc / 376.0, m_hc / 380.0, m_hc / 384.0, m_hc / 388.0, m_hc / 392.0, m_hc / 396.0, 
                                                                         m_hc / 400.0, m_hc / 404.0, m_hc / 408.0, m_hc / 412.0, m_hc / 416.0, m_hc / 420.0, m_hc / 424.0, m_hc / 428.0, m_hc / 432.0, m_hc / 436.0, 
                                                                         m_hc / 440.0, m_hc / 444.0, m_hc / 448.0, m_hc / 452.0, m_hc / 456.0, m_hc / 460.0, m_hc / 464.0, m_hc / 468.0, m_hc / 472.0, m_hc / 476.0, 
                                                                         m_hc / 480.0, m_hc / 484.0, m_hc / 488.0, m_hc / 492.0, m_hc / 496.0, m_hc / 500.0, m_hc / 504.0, m_hc / 508.0, m_hc / 512.0, m_hc / 516.0, 
                                                                         m_hc / 520.0, m_hc / 524.0, m_hc / 528.0, m_hc / 532.0, m_hc / 536.0, m_hc / 540.0, m_hc / 544.0, m_hc / 548.0, m_hc / 552.0, m_hc / 556.0, 
                                                                         m_hc / 560.0, m_hc / 564.0, m_hc / 568.0, m_hc / 572.0, m_hc / 576.0, m_hc / 580.0, m_hc / 584.0, m_hc / 588.0, m_hc / 592.0, m_hc / 596.0, 
                                                                         m_hc / 600.0, m_hc / 604.0, m_hc / 608.0, m_hc / 612.0, m_hc / 616.0, m_hc / 620.0, m_hc / 624.0, m_hc / 628.0, m_hc / 632.0, m_hc / 636.0, 
                                                                         m_hc / 640.0, m_hc / 644.0, m_hc / 648.0, m_hc / 652.0, m_hc / 656.0, m_hc / 660.0, m_hc / 664.0, m_hc / 668.0, m_hc / 672.0, m_hc / 676.0, 
                                                                         m_hc / 680.0, m_hc / 684.0, m_hc / 688.0, m_hc / 692.0, m_hc / 696.0, m_hc / 700.0, m_hc / 704.0, m_hc / 708.0, m_hc / 712.0, m_hc / 716.0, 
                                                                         m_hc / 720.0, m_hc / 724.0, m_hc / 728.0, m_hc / 732.0, m_hc / 736.0, m_hc / 740.0, m_hc / 744.0, m_hc / 748.0, m_hc / 752.0, m_hc / 756.0, 
                                                                         m_hc / 760.0, m_hc / 764.0, m_hc / 768.0, m_hc / 772.0, m_hc / 776.0, m_hc / 780.0, m_hc / 784.0, m_hc / 788.0, m_hc / 792.0, m_hc / 796.0, 
                                                                         m_hc / 800.0 };
    G4double m_WbLS_mpt_absLength_values[ m_WbLS_mpt_absLength_size ]{ 8.585704979500266 , 8.562805813828513 , 8.526476524818166 , 8.485809956040825 , 8.440410115387428 , 
                                                                       8.388685223597328 , 8.334769030495814 , 8.27710484094689  , 8.216829436947206 , 8.15470277733356  , 
                                                                       8.09124655788053  , 8.027746797869844 , 7.963101034712502 , 7.897584897865603 , 7.831392728456735 , 
                                                                       7.764665565750066 , 7.697896294230155 , 7.6306530396305705, 7.563457462715348 , 7.496155186750957 , 
                                                                       7.428383243394613 , 7.360807997637589 , 7.2927387779566   , 7.224829600330399 , 7.156783239229534 , 
                                                                       7.088222317419892 , 7.0193228564890875, 6.950191333328753 , 6.880880303771798 , 6.811436153621477 , 
                                                                       7.859038011526891 , 10.514727941691875, 13.01787335366654 , 14.607748590943425, 18.781125218108915, 
                                                                       75.46204426152104 , 654.3573953249909 , 2239.3655698166776, 5877.607414095322 , 13066.568388003547, 
                                                                       21960.72095047522 , 27876.028290792252, 31514.549363537262, 43628.4078220178  , 64837.8646267015  , 
                                                                       85799.98912133789 , 99694.52744095254 , 107265.11842830478, 116419.24317854586, 121852.83537327732, 
                                                                       45312.82965861025 , 175673.68885394075, 193572.22052987237, 209940.34104546517, 218138.7090694312 , 
                                                                       211933.76041696104, 202917.6900141468 , 200562.25095756445, 193740.01160543287, 176440.82520659015, 
                                                                       154187.875142152  , 135484.96067185665, 117115.26112027133, 103407.66057676624, 103484.36447334244, 
                                                                       101216.51858890736, 98606.74216354908 , 96183.3669223369  , 91773.35149631929 , 85057.7715140951  , 
                                                                       78275.33133968672 , 74508.66858900191 , 68807.63505770943 , 62580.46324172955 , 55633.200427432406, 
                                                                       49139.10060706563 , 41087.88334296449 , 34870.09287010383 , 27847.90761315929 , 25318.706199439806, 
                                                                       24594.576027276704, 24162.147657696743, 23435.7345938708  , 22633.038881595672, 22010.980253297494, 
                                                                       21240.08512472482 , 20063.468044340127, 18588.219121701197, 17159.34401939309 , 16795.228163310927, 
                                                                       16278.973813568595, 15720.100845205832, 14905.714038787679, 13910.900554222862, 12667.137031689674, 
                                                                       11265.323473951416, 9590.612309408314 , 8118.374817224639 , 6825.438418372264 , 5725.538617734483 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 5724.641483252548 , 
                                                                       5724.641483252548 };
    static const int m_WbLS_mpt_rsLength_size{ 151 };
    G4double m_WbLS_mpt_rsLength_energies[ m_WbLS_mpt_rsLength_size ]{ m_hc / 200.0, m_hc / 204.0, m_hc / 208.0, m_hc / 212.0, m_hc / 216.0, m_hc / 220.0, m_hc / 224.0, m_hc / 228.0, m_hc / 232.0, m_hc / 236.0, 
                                                                       m_hc / 240.0, m_hc / 244.0, m_hc / 248.0, m_hc / 252.0, m_hc / 256.0, m_hc / 260.0, m_hc / 264.0, m_hc / 268.0, m_hc / 272.0, m_hc / 276.0, 
                                                                       m_hc / 280.0, m_hc / 284.0, m_hc / 288.0, m_hc / 292.0, m_hc / 296.0, m_hc / 300.0, m_hc / 304.0, m_hc / 308.0, m_hc / 312.0, m_hc / 316.0, 
                                                                       m_hc / 320.0, m_hc / 324.0, m_hc / 328.0, m_hc / 332.0, m_hc / 336.0, m_hc / 340.0, m_hc / 344.0, m_hc / 348.0, m_hc / 352.0, m_hc / 356.0,
                                                                       m_hc / 360.0, m_hc / 364.0, m_hc / 368.0, m_hc / 372.0, m_hc / 376.0, m_hc / 380.0, m_hc / 384.0, m_hc / 388.0, m_hc / 392.0, m_hc / 396.0, 
                                                                       m_hc / 400.0, m_hc / 404.0, m_hc / 408.0, m_hc / 412.0, m_hc / 416.0, m_hc / 420.0, m_hc / 424.0, m_hc / 428.0, m_hc / 432.0, m_hc / 436.0, 
                                                                       m_hc / 440.0, m_hc / 444.0, m_hc / 448.0, m_hc / 452.0, m_hc / 456.0, m_hc / 460.0, m_hc / 464.0, m_hc / 468.0, m_hc / 472.0, m_hc / 476.0, 
                                                                       m_hc / 480.0, m_hc / 484.0, m_hc / 488.0, m_hc / 492.0, m_hc / 496.0, m_hc / 500.0, m_hc / 504.0, m_hc / 508.0, m_hc / 512.0, m_hc / 516.0, 
                                                                       m_hc / 520.0, m_hc / 524.0, m_hc / 528.0, m_hc / 532.0, m_hc / 536.0, m_hc / 540.0, m_hc / 544.0, m_hc / 548.0, m_hc / 552.0, m_hc / 556.0, 
                                                                       m_hc / 560.0, m_hc / 564.0, m_hc / 568.0, m_hc / 572.0, m_hc / 576.0, m_hc / 580.0, m_hc / 584.0, m_hc / 588.0, m_hc / 592.0, m_hc / 596.0, 
                                                                       m_hc / 600.0, m_hc / 604.0, m_hc / 608.0, m_hc / 612.0, m_hc / 616.0, m_hc / 620.0, m_hc / 624.0, m_hc / 628.0, m_hc / 632.0, m_hc / 636.0, 
                                                                       m_hc / 640.0, m_hc / 644.0, m_hc / 648.0, m_hc / 652.0, m_hc / 656.0, m_hc / 660.0, m_hc / 664.0, m_hc / 668.0, m_hc / 672.0, m_hc / 676.0, 
                                                                       m_hc / 680.0, m_hc / 684.0, m_hc / 688.0, m_hc / 692.0, m_hc / 696.0, m_hc / 700.0, m_hc / 704.0, m_hc / 708.0, m_hc / 712.0, m_hc / 716.0, 
                                                                       m_hc / 720.0, m_hc / 724.0, m_hc / 728.0, m_hc / 732.0, m_hc / 736.0, m_hc / 740.0, m_hc / 744.0, m_hc / 748.0, m_hc / 752.0, m_hc / 756.0, 
                                                                       m_hc / 760.0, m_hc / 764.0, m_hc / 768.0, m_hc / 772.0, m_hc / 776.0, m_hc / 780.0, m_hc / 784.0, m_hc / 788.0, m_hc / 792.0, m_hc / 796.0, 
                                                                       m_hc / 800.0 };
    G4double m_WbLS_mpt_rsLength_values[ m_WbLS_mpt_rsLength_size ]{ 937.1257327487692 , 1021.7202653768765, 1107.4543871147264, 1194.3962321913775, 1282.5891321880663, 
                                                                     1372.0557903477575, 1483.42651679736  , 1596.1700611016292, 1710.3599475186309, 1826.0451257190543, 
                                                                     1943.253590844071 , 2086.527498168214 , 2231.4324272682456, 2378.0437090118808, 2526.4176690095987, 
                                                                     2676.5822354751526, 2857.3371441979352, 3040.000902608993 , 3224.656020487314 , 3411.3589388000896, 
                                                                     3600.1465042513114, 3824.412707565994 , 4050.8905408894066, 4279.662504089579 , 4510.792356268391 , 
                                                                     4744.320483683573 , 5018.577293616327 , 5295.366318903476 , 5574.779029207857 , 5856.8792824826705, 
                                                                     6141.714594661947 , 6472.890559567197 , 6806.942511736456 , 7143.967281903358 , 7484.032408643766 , 
                                                                     7827.190741378654 , 8222.668621847599 , 8621.38942448311  , 9023.453561711898 , 9428.934041517883 , 
                                                                     9837.885478797934 , 10305.484063017446, 10776.713918056097, 11251.679012937568, 11730.457798321228, 
                                                                     12213.110216524925, 12761.103101057452, 13313.138769913325, 13869.321153458792, 14429.739494981084, 
                                                                     14994.451903859706, 15631.5831237722  , 16273.188174142257, 16919.378151730623, 17570.24415874138 , 
                                                                     18225.851443557927, 18961.29796036488 , 19701.672544504432, 20447.093457483206, 21197.65007331959 , 
                                                                     21953.416574320763, 22796.791944943307, 23645.572831154695, 24499.877466690126, 25359.805994758735, 
                                                                     26225.43077836109 , 27186.820837965755, 28154.109850423432, 29127.42855001363 , 30106.87533625349 , 
                                                                     31092.533272982593, 32182.478200820646, 33278.84403151105 , 34381.76150717969 , 35491.33802197759 , 
                                                                     36607.6566379619  , 37837.108217238405, 39073.52407664791 , 40317.036722653706, 41567.76072017582 , 
                                                                     42825.78088857041 , 44206.17566817895 , 45594.09766642544 , 46989.68652727643 , 48393.05684846406 , 
                                                                     49804.30414760269 , 51347.524123613126, 52898.85741555694 , 54458.44902340607 , 56026.41536562833 , 
                                                                     57602.857309347935, 59321.21926318083 , 61048.303809110075, 62784.2559321442  , 64529.2027908874  , 
                                                                     66283.24344866973 , 68189.53639901726 , 70105.1790083262  , 72030.32518660865 , 73965.10391079387 ,
                                                                     75410.90024338344 , 76987.61890488309 , 78542.64476932719 , 80076.4224585986  , 81589.38452623288 , 
                                                                     83081.95186412173 , 84703.17098784364 , 86300.66615143497 , 87874.95431600949 , 89426.5375310833  , 
                                                                     90955.90346837629 , 92610.39575553677 , 94239.27391719905 , 95843.12820438055 , 97422.53087071044 , 
                                                                     98978.03685319018 , 100654.80683115884, 102304.24527493515, 103927.01504268762, 105523.7577298483 , 
                                                                     107095.09451489549, 108783.12222606278, 110442.3140680083 , 112073.40266972005, 113677.09605020085, 
                                                                     115254.07864321544, 116942.53012892576, 118600.88899099625, 120229.95261759982, 121830.49047152516, 
                                                                     123403.24530203774, 125081.9910073145 , 126729.65045750854, 128347.07919321865, 129935.1016460764 , 
                                                                     131494.51253997933, 133154.13235258337, 134781.947545823  , 136378.8636885947 , 137945.75229415114, 
                                                                     139483.45240609915, 141115.52723366127, 142715.3517541178 , 144283.87252946387, 145821.99943785885, 
                                                                     147330.60743366787, 148927.6641125596 , 150492.2921931633 , 152025.4694535471 , 153528.13475400239, 
                                                                     155001.1899542359 };
    static const int m_WbLS_mpt_reemissionProb_size{ 4 };
    G4double m_WbLS_mpt_reemissionProb_energies[ m_WbLS_mpt_reemissionProb_size ]{ 200.0, 345.0, 370.0, 800.0 };
    G4double m_WbLS_mpt_reemissionProb_values[ m_WbLS_mpt_reemissionProb_size ]{ 0.8, 0.8, 0.0, 0.0 };
};

}

#endif
