# G4ANNIERecoParticles

![Nice](https://github.com/Noah-Everett/G4VtxRecoParticles/blob/main/plots/G4ANNIERecoParticles_mu_100_300MeV_EvsT.png)

`<>` denotes required arguments and `[]` denotes optional arguments.

## Building `G4ANNIERecoParticles`
You will need [CMake](https://cmake.org/) and [Geant4](https://geant4.web.cern.ch). Then run the following command:
```
cd </path/to/G4ANNIERecoParticles/dir> && mkdir build && cd build && cmake .. && make -j<number of threads>
```

If you encounter CMake errors, you may need to add something like the following to your config file (`~/.bashrc`, `~/.zshrc`, etc.):
```
#===== Geant4 =====#
export Qt5Version="<Qt5 version>"
export Qt5Core_DIR=/opt/homebrew/Cellar/qt@5/${Qt5Version}/lib/cmake/Qt5Core
export Qt5Gui_DIR=/opt/homebrew/Cellar/qt@5/${Qt5Version}/lib/cmake/Qt5Gui
export Qt5Widgets_DIR=/opt/homebrew/Cellar/qt@5/${Qt5Version}/lib/cmake/Qt5Widgets
export Qt5OpenGL_DIR=/opt/homebrew/Cellar/qt@5/${Qt5Version}/lib/cmake/Qt5OpenGL
export Qt5PrintSupport_DIR=/opt/homebrew/Cellar/qt@5/${Qt5Version}/lib/cmake/Qt5PrintSupport
export Geant4_DIR="</path/to/Geant4/install/dir>"
cd ${Geant4_DIR}/bin/
source ./geant4.sh
cd - > /dev/null 2>&1
```

## `G4ANNIERecoParticles` Usage
```
G4ANNIERecoParticles </path/to/detector/macro>.mac [</path/to/run/macro>.mac]
```
### Example Usage
```
build/G4ANNIERecoParticles build/macros/detector.mac build/macros/muon.mac
```

## `make_hists.sh` Usage
```
make_hists.sh --dir_out=</path/to/ouput/dir>
              --dir_exec=</path/to/G4ANNIERecoParticles/dir> 
              --dir_script=</path/to/make_dTdXHist.C/dir> 
              --G4_particle=<'e-' || 'mu-'> 
              --G4_nParticles=<number of primary particles> 
              --G4_material=<water || water_basic || water_doped || steel || stainlessSteel || aluminum> 
              --G4_record_gammas=<0 || 1> 
              --G4_record_dEdX=<0 || 1> 
              --E_min=<minimum energy [MeV]> 
              --E_max=<maximum energy [MeV]> 
              --E_delta=<energy step delta [MeV]>
```
### Example Usage
```
make_hists.sh --dir_out=reco-data/newDir --dir_exec=build --dir_script=.  --G4_particle='mu-' --G4_nParticles=100 --G4_material=water_doped --G4_record_gammas=1 --G4_record_dEdX=0 --E_min=0 --E_max=1000 --E_delta=10
```
