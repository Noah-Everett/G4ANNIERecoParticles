#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"

namespace ANNIERecoParticles 
{

void DetectorConstruction::ConstructMaterials() {
  G4Isotope* isotope_Gd152 = new G4Isotope( "Gd152", 64, 152, 152.0 * g / mole );
  G4Isotope* isotope_Gd154 = new G4Isotope( "Gd154", 64, 154, 154.0 * g / mole );
  G4Isotope* isotope_Gd155 = new G4Isotope( "Gd155", 64, 155, 155.0 * g / mole );
  G4Isotope* isotope_Gd156 = new G4Isotope( "Gd156", 64, 156, 156.0 * g / mole );
  G4Isotope* isotope_Gd157 = new G4Isotope( "Gd157", 64, 157, 157.0 * g / mole );
  G4Isotope* isotope_Gd158 = new G4Isotope( "Gd158", 64, 158, 158.0 * g / mole );
  G4Isotope* isotope_Gd160 = new G4Isotope( "Gd160", 64, 160, 160.0 * g / mole );

  G4Element* element_H  = new G4Element( "Hydrogen"  , "H" , 1 , 1.01    * CLHEP::g / CLHEP::mole );
  G4Element* element_O  = new G4Element( "Oxygen"    , "O" , 8 , 16.00   * CLHEP::g / CLHEP::mole );
  G4Element* element_Gd = new G4Element( "Gadolinium", "Gd", 64, 157.25  * CLHEP::g / CLHEP::mole );
  G4Element* element_C  = new G4Element( "Carbon"    , "C" , 6 , 12.01   * CLHEP::g / CLHEP::mole );
  G4Element* element_Fe = new G4Element( "Iron"      , "Fe", 26, 55.85   * CLHEP::g / CLHEP::mole );
  G4Element* element_Cr = new G4Element( "Chromium"  , "Cr", 24, 51.9961 * CLHEP::g / CLHEP::mole );
  G4Element* element_Ni = new G4Element( "Nickel"    , "Ni", 28, 58.6934 * CLHEP::g / CLHEP::mole );
  G4Element* element_Mn = new G4Element( "Manganese" , "Mn", 25, 54.938  * CLHEP::g / CLHEP::mole ); 
  G4Element* element_P  = new G4Element( "Phosphore" , "P" , 15, 30.974  * CLHEP::g / CLHEP::mole );
  G4Element* element_Si = new G4Element( "Silicon"   , "Si", 14, 28.09   * CLHEP::g / CLHEP::mole ); 
  G4Element* element_S  = new G4Element( "Sulphur"   , "S" , 16, 32.065  * CLHEP::g / CLHEP::mole );
  G4Element* element_Al = new G4Element( "Aluminum"  , "Al", 13, 26.98   * CLHEP::g / CLHEP::mole );  
  G4Element* element_Gd_complete = new G4Element( "Gadolinium", "Gd", 7 );
  element_Gd_complete->AddIsotope( isotope_Gd152,  0.2 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd154,  2.2 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd155, 14.9 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd156, 20.6 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd157, 15.7 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd158, 24.7 * perCent );
  element_Gd_complete->AddIsotope( isotope_Gd160, 21.7 * perCent );
  
  G4Material* water = new G4Material( "water", 1.00*CLHEP::g/CLHEP::cm3, 2 );
  water->AddElement( element_H, 2 );
  water->AddElement( element_O, 1 );

  G4Material* water_doped = new G4Material( "water_doped", 1.00 * CLHEP::g / CLHEP::cm3, 2 );
  water_doped->AddMaterial( water     , 99.9 * CLHEP::perCent );
  water_doped->AddElement ( element_Gd, 0.1  * CLHEP::perCent );

  G4Material* steel = new G4Material( "Steel", 7.8 * CLHEP::g / CLHEP::cm3, 2 );
  steel->AddElement( element_C , 1.  * CLHEP::perCent );
  steel->AddElement( element_Fe, 99. * CLHEP::perCent );
  
  G4Material* stainlessSteel = new G4Material( "StainlessSteel", 7.81 * CLHEP::g / CLHEP::cm3, 8 );
  stainlessSteel->AddElement( element_Fe, 70.44 *CLHEP::perCent );
  stainlessSteel->AddElement( element_Cr, 18    *CLHEP::perCent );
  stainlessSteel->AddElement( element_C , 0.08  *CLHEP::perCent );
  stainlessSteel->AddElement( element_Ni, 8     *CLHEP::perCent ); 
  stainlessSteel->AddElement( element_P , 0.45  *CLHEP::perCent );
  stainlessSteel->AddElement( element_Si, 1     *CLHEP::perCent );
  stainlessSteel->AddElement( element_Mn, 2     *CLHEP::perCent );
  stainlessSteel->AddElement( element_S , 0.03  *CLHEP::perCent );

  G4Material* Aluminum = new G4Material( "Aluminum", 2.7 * CLHEP::g / CLHEP::cm3, 1 );
  Aluminum->AddElement( element_Al, 1 );

  const G4int size_mpt_water = 60;

  G4double water_mpt_energies[ size_mpt_water ] = { 1.56962e-09*CLHEP::GeV, 1.58974e-09*CLHEP::GeV, 1.61039e-09*CLHEP::GeV, 1.63157e-09*CLHEP::GeV, 
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

  G4double water_mpt_rindices[ size_mpt_water ] = { 1.32885, 1.32906, 1.32927, 1.32948, 1.3297 , 1.32992, 1.33014,
                                                    1.33037, 1.3306 , 1.33084, 1.33109, 1.33134, 1.3316 , 1.33186, 1.33213,
                                                    1.33241, 1.3327 , 1.33299, 1.33329, 1.33361, 1.33393, 1.33427, 1.33462,
                                                    1.33498, 1.33536, 1.33576, 1.33617, 1.3366 , 1.33705, 1.33753, 1.33803,
                                                    1.33855, 1.33911, 1.3397 , 1.34033, 1.341  , 1.34172, 1.34248, 1.34331,
                                                    1.34419, 1.34515, 1.3462 , 1.34733, 1.34858, 1.34994, 1.35145, 1.35312,
                                                    1.35498, 1.35707, 1.35943, 1.36211, 1.36518, 1.36872, 1.37287, 1.37776,
                                                    1.38362, 1.39074, 1.39956, 1.41075, 1.42535 };

  G4double ABWFF = 1.30;
  G4double water_mpt_absorption[ size_mpt_water ] = { 16.1419*CLHEP::cm*ABWFF,  18.278*CLHEP::cm*ABWFF, 21.0657*CLHEP::cm*ABWFF, 24.8568*CLHEP::cm*ABWFF, 30.3117*CLHEP::cm*ABWFF,
                                                      38.8341*CLHEP::cm*ABWFF, 54.0231*CLHEP::cm*ABWFF, 81.2306*CLHEP::cm*ABWFF, 120.909*CLHEP::cm*ABWFF, 160.238*CLHEP::cm*ABWFF,
                                                      193.771*CLHEP::cm*ABWFF, 215.017*CLHEP::cm*ABWFF, 227.747*CLHEP::cm*ABWFF,  243.85*CLHEP::cm*ABWFF, 294.036*CLHEP::cm*ABWFF,
                                                      321.647*CLHEP::cm*ABWFF,  342.81*CLHEP::cm*ABWFF, 362.827*CLHEP::cm*ABWFF, 378.041*CLHEP::cm*ABWFF, 449.378*CLHEP::cm*ABWFF,
                                                      739.434*CLHEP::cm*ABWFF, 1114.23*CLHEP::cm*ABWFF, 1435.56*CLHEP::cm*ABWFF, 1611.06*CLHEP::cm*ABWFF, 1764.18*CLHEP::cm*ABWFF,
                                                      2100.95*CLHEP::cm*ABWFF,  2292.9*CLHEP::cm*ABWFF, 2431.33*CLHEP::cm*ABWFF,  3053.6*CLHEP::cm*ABWFF, 4838.23*CLHEP::cm*ABWFF,
                                                      6539.65*CLHEP::cm*ABWFF, 7682.63*CLHEP::cm*ABWFF, 9137.28*CLHEP::cm*ABWFF, 12220.9*CLHEP::cm*ABWFF, 15270.7*CLHEP::cm*ABWFF,
                                                      19051.5*CLHEP::cm*ABWFF, 23671.3*CLHEP::cm*ABWFF, 29191.1*CLHEP::cm*ABWFF, 35567.9*CLHEP::cm*ABWFF,   42583*CLHEP::cm*ABWFF,
                                                      49779.6*CLHEP::cm*ABWFF, 56465.3*CLHEP::cm*ABWFF,   61830*CLHEP::cm*ABWFF, 65174.6*CLHEP::cm*ABWFF, 66143.7*CLHEP::cm*ABWFF,
                                                         64820*CLHEP::cm*ABWFF,   61635*CLHEP::cm*ABWFF, 57176.2*CLHEP::cm*ABWFF, 52012.1*CLHEP::cm*ABWFF, 46595.7*CLHEP::cm*ABWFF,
                                                      41242.1*CLHEP::cm*ABWFF, 36146.3*CLHEP::cm*ABWFF, 31415.4*CLHEP::cm*ABWFF, 27097.8*CLHEP::cm*ABWFF, 23205.7*CLHEP::cm*ABWFF,
                                                      19730.3*CLHEP::cm*ABWFF, 16651.6*CLHEP::cm*ABWFF, 13943.6*CLHEP::cm*ABWFF, 11578.1*CLHEP::cm*ABWFF, 9526.13*CLHEP::cm*ABWFF };

  G4double RAYFF = 0.75;
  G4double water_mpt_rayleigh[ size_mpt_water ] = { 386929*CLHEP::cm*RAYFF,  366249*CLHEP::cm*RAYFF,  346398*CLHEP::cm*RAYFF,  327355*CLHEP::cm*RAYFF,  309097*CLHEP::cm*RAYFF,
                                                    291603*CLHEP::cm*RAYFF,  274853*CLHEP::cm*RAYFF,  258825*CLHEP::cm*RAYFF,  243500*CLHEP::cm*RAYFF,  228856*CLHEP::cm*RAYFF,
                                                    214873*CLHEP::cm*RAYFF,  201533*CLHEP::cm*RAYFF,  188816*CLHEP::cm*RAYFF,  176702*CLHEP::cm*RAYFF,  165173*CLHEP::cm*RAYFF,
                                                    154210*CLHEP::cm*RAYFF,  143795*CLHEP::cm*RAYFF,  133910*CLHEP::cm*RAYFF,  124537*CLHEP::cm*RAYFF,  115659*CLHEP::cm*RAYFF,
                                                    107258*CLHEP::cm*RAYFF, 99318.2*CLHEP::cm*RAYFF, 91822.2*CLHEP::cm*RAYFF,   84754*CLHEP::cm*RAYFF, 78097.3*CLHEP::cm*RAYFF,
                                                   71836.5*CLHEP::cm*RAYFF,   65956*CLHEP::cm*RAYFF, 60440.6*CLHEP::cm*RAYFF, 55275.4*CLHEP::cm*RAYFF, 50445.6*CLHEP::cm*RAYFF,
                                                     45937*CLHEP::cm*RAYFF, 41735.2*CLHEP::cm*RAYFF, 37826.6*CLHEP::cm*RAYFF, 34197.6*CLHEP::cm*RAYFF, 30834.9*CLHEP::cm*RAYFF,
                                                   27725.4*CLHEP::cm*RAYFF, 24856.6*CLHEP::cm*RAYFF, 22215.9*CLHEP::cm*RAYFF, 19791.3*CLHEP::cm*RAYFF, 17570.9*CLHEP::cm*RAYFF,
                                                     15543*CLHEP::cm*RAYFF, 13696.6*CLHEP::cm*RAYFF, 12020.5*CLHEP::cm*RAYFF, 10504.1*CLHEP::cm*RAYFF, 9137.15*CLHEP::cm*RAYFF,
                                                   7909.45*CLHEP::cm*RAYFF,  6811.3*CLHEP::cm*RAYFF, 5833.25*CLHEP::cm*RAYFF,  4966.2*CLHEP::cm*RAYFF, 4201.36*CLHEP::cm*RAYFF,
                                                   3530.28*CLHEP::cm*RAYFF, 2944.84*CLHEP::cm*RAYFF, 2437.28*CLHEP::cm*RAYFF, 2000.18*CLHEP::cm*RAYFF,  1626.5*CLHEP::cm*RAYFF,
                                                   1309.55*CLHEP::cm*RAYFF, 1043.03*CLHEP::cm*RAYFF, 821.016*CLHEP::cm*RAYFF,  637.97*CLHEP::cm*RAYFF, 488.754*CLHEP::cm*RAYFF };

  G4double MIEFF = 0.0;
  G4double water_mpt_mie[ size_mpt_water ] = { 7790020*CLHEP::cm*MIEFF, 7403010*CLHEP::cm*MIEFF, 7030610*CLHEP::cm*MIEFF, 6672440*CLHEP::cm*MIEFF, 6328120*CLHEP::cm*MIEFF,
                                               5997320*CLHEP::cm*MIEFF, 5679650*CLHEP::cm*MIEFF, 5374770*CLHEP::cm*MIEFF, 5082340*CLHEP::cm*MIEFF, 4802000*CLHEP::cm*MIEFF,
                                               4533420*CLHEP::cm*MIEFF, 4276280*CLHEP::cm*MIEFF, 4030220*CLHEP::cm*MIEFF, 3794950*CLHEP::cm*MIEFF, 3570120*CLHEP::cm*MIEFF,
                                               3355440*CLHEP::cm*MIEFF, 3150590*CLHEP::cm*MIEFF, 2955270*CLHEP::cm*MIEFF, 2769170*CLHEP::cm*MIEFF, 2592000*CLHEP::cm*MIEFF,
                                               2423470*CLHEP::cm*MIEFF, 2263300*CLHEP::cm*MIEFF, 2111200*CLHEP::cm*MIEFF, 1966900*CLHEP::cm*MIEFF, 1830120*CLHEP::cm*MIEFF,
                                               1700610*CLHEP::cm*MIEFF, 1578100*CLHEP::cm*MIEFF, 1462320*CLHEP::cm*MIEFF, 1353040*CLHEP::cm*MIEFF, 1250000*CLHEP::cm*MIEFF,
                                               1152960*CLHEP::cm*MIEFF, 1061680*CLHEP::cm*MIEFF,  975936*CLHEP::cm*MIEFF,  895491*CLHEP::cm*MIEFF,  820125*CLHEP::cm*MIEFF,
                                                749619*CLHEP::cm*MIEFF,  683760*CLHEP::cm*MIEFF,  622339*CLHEP::cm*MIEFF,  565152*CLHEP::cm*MIEFF,  512000*CLHEP::cm*MIEFF,
                                                462688*CLHEP::cm*MIEFF,  417027*CLHEP::cm*MIEFF,  374832*CLHEP::cm*MIEFF,  335923*CLHEP::cm*MIEFF,  300125*CLHEP::cm*MIEFF,
                                                267267*CLHEP::cm*MIEFF,  237184*CLHEP::cm*MIEFF,  209715*CLHEP::cm*MIEFF,  184704*CLHEP::cm*MIEFF,  162000*CLHEP::cm*MIEFF,
                                                141456*CLHEP::cm*MIEFF,  122931*CLHEP::cm*MIEFF,  106288*CLHEP::cm*MIEFF, 91395.2*CLHEP::cm*MIEFF,   78125*CLHEP::cm*MIEFF, 
                                               66355.2*CLHEP::cm*MIEFF, 55968.2*CLHEP::cm*MIEFF, 46851.2*CLHEP::cm*MIEFF, 38896.2*CLHEP::cm*MIEFF,   32000*CLHEP::cm*MIEFF };

  G4MaterialPropertiesTable* water_mpt = new G4MaterialPropertiesTable();
  water_mpt->AddProperty( "RINDEX"   , water_mpt_energies, water_mpt_rindices  , size_mpt_water );
  water_mpt->AddProperty( "ABSLENGTH", water_mpt_energies, water_mpt_absorption, size_mpt_water );
  water_mpt->AddProperty( "RAYLEIGH" , water_mpt_energies, water_mpt_rayleigh  , size_mpt_water );
  water      ->SetMaterialPropertiesTable( water_mpt );
  water_doped->SetMaterialPropertiesTable( water_mpt );
}

}