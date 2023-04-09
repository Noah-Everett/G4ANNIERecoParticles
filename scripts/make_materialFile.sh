macro_detector() {
    cat <<EOF > detector.mac
/ANNIERecoParticles/material                 ${detector_material}
/ANNIERecoParticles/stepVolumeWidth          ${detector_dX} m
/ANNIERecoParticles/make/tuple/dEdX          0
/ANNIERecoParticles/make/tuple/emission      0
/ANNIERecoParticles/make/tuple/transmittance 0
/ANNIERecoParticles/make/hist/dEdX           ${make_dEdX}
/ANNIERecoParticles/make/hist/emission       ${make_emission}
/ANNIERecoParticles/make/hist/transmittance  ${make_transmittance}
EOF
}

macro_run() {
    cat <<EOF > run.mac
/run/initialize
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/process/verbose 0
/gun/particle ${primary_type}
/gun/energy ${energy_cur_export} MeV
/gun/position 0 0 0
/gun/direction 1 0 0
/process/activate Cerenkov
/process/activate Scintillation
/process/optical/cerenkov/setTrackSecondariesFirst true
/process/optical/scintillation/setTrackSecondariesFirst true
/run/beamOn ${primary_num}
EOF
}

make_log(){
    cat <<EOF > ${dir_out}/batch.log
#==============================#
#========== settings ==========#
#==============================#
          output_dir=${output_dir}
         output_name=${output_name}
           path_exec=${path_exec}
         dir_scripts=${dir_scripts}
   detector_material=${detector_material}
         detector_dX=${detector_dX}
        primary_type=${primary_type}
         primary_num=${primary_num}
  primary_energy_min=${primary_energy_min}
  primary_energy_max=${primary_energy_max}
primary_energy_delta=${primary_energy_delta}
           gamma_num=${gamma_num}
    gamma_energy_min=${gamma_energy_min}
    gamma_energy_max=${gamma_energy_max}
  gamma_energy_delta=${gamma_energy_delta}



#==================================#
#========== detector.mac ==========#
#==================================#
/ANNIERecoParticles/material                 ${detector_material}
/ANNIERecoParticles/stepVolumeWidth          ${detector_dX} m # dEdX
/ANNIERecoParticles/stepVolumeWidth          10 m # !dEdX
/ANNIERecoParticles/make/tuple/dEdX          0
/ANNIERecoParticles/make/tuple/emission      0
/ANNIERecoParticles/make/tuple/transmittance 0
/ANNIERecoParticles/make/hist/dEdX           0/1
/ANNIERecoParticles/make/hist/emission       0/1
/ANNIERecoParticles/make/hist/transmittance  0/1



#=============================#
#========== run.mac ==========#
#=============================#
/run/initialize
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/process/verbose 0
/gun/particle ${particle_type} # primary
/gun/particle gamma            # gamm
/gun/energy (${primary_energy_min},${primary_energy_max},${primary_energy_delta}) MeV # primary
/gun/energy (${gamma_energy_min},${gamma_energy_max},${gamma_energy_delta}) MeV # gamma
/gun/position 0 0 0
/gun/direction 1 0 0
/process/activate Cerenkov
/process/activate Scintillation
/process/optical/cerenkov/setTrackSecondariesFirst true
/process/optical/scintillation/setTrackSecondariesFirst true
/run/beamOn ${primary_num} # primary
/run/beamOn ${gamma_num} # gamma
EOF
}

run() {
    macro_detector
    macro_run

    ${path_exec} detector.mac run.mac
    rm G4ANNIERecoParticles_t*.root # shouldnt be needed but just in case

    if [ "${make_dEdX}" -eq "1" ]; then
        root -x -q ${dir_scripts}/scale_TH1D.C\(\"G4ANNIERecoParticles.root\",\"hist_dEdX_counts\;1\",\"hist_dEdX_dEdX\;1\"\)
        root -x -q ${dir_scripts}/addToTFile_TH1D.C\(\"${output_dir}/${output_name}\",\"G4ANNIERecoParticles.root\",\"hist_dEdX_dEdX\;1\"\)
    fi
    if [ "${make_emission}" -eq "1" ]; then
        root -x -q ${dir_scripts}/scale_TH2D.C\(\"G4ANNIERecoParticles.root\",\"hist_emission_counts\;1\",\"hist_emisssion_energies\;1\"\)
        root -x -q ${dir_scripts}/addToTFile_TH2D.C\(\"${output_dir}/${output_name}\",\"G4ANNIERecoParticles.root\",\"hist_emission_energies\;1\"\)
        root -x -q ${dir_scripts}/addToTFile_TH2D.C\(\"${output_dir}/${output_name}\",\"G4ANNIERecoParticles.root\",\"hist_emission_counts\;1\"\)
    fi
    if [ "${make_transmittance}" -eq "1" ]; then
        root -x -q ${dir_scripts}/addToTFile_TH1D.C\(\"${output_dir}/${output_name}\",\"G4ANNIERecoParticles.root\",\"hist_transmittance\;1\"\)
    fi

    rm G4ANNIERecoParticles.root
    rm run.mac
    rm detector.mac
}

main() {
# E.g. path: /this/is/a/path.exe
# E.g. dir:  /this/is/a/dir
export output_dir="/Users/noah-everett/Documents/ANNIE/ANNIE_Reco/G4VtxRecoParticles/reco-data"
export output_name="water_doped-mu-small.root"
export path_exec="/Users/noah-everett/Documents/ANNIE/ANNIE_Reco/G4VtxRecoParticles/build/G4ANNIERecoParticles"
export dir_scripts="/Users/noah-everett/Documents/ANNIE/ANNIE_Reco/G4VtxRecoParticles/scripts"
export detector_material="water_doped"
export detector_dX="0.01" # m
export primary_type="mu-"
export primary_num="10"
export primary_energy_min="0" # MeV
export primary_energy_max="1200" # MeV
export primary_energy_delta="10" # MeV
export dEdX_num="200"
export gamma_num="10000"
export gamma_energy_min="0" # eV
export gamma_energy_max="10" # eV
export gamma_energy_delta=".5" # eV

for i in "$@"; do
  case $i in
    --output_dir=*           ) export output_dir="${i#*=}"           shift    ;;
    --output_name=*          ) export output_name="${i#*=}"          shift    ;;
    --path_exec=*            ) export path_exec="${i#*=}"            shift    ;;
    --dir_scripts=*          ) export dir_scripts="${i#*=}"          shift    ;;
    --detector_material=*    ) export detector_material="${i#*=}"    shift    ;;
    --detector_dX=*          ) export detector_dX="${i#*=}"          shift    ;;
    --primary_type=*         ) export primary_type="${i#*=}"         shift    ;;
    --primary_num=*          ) export primary_num="${i#*=}"          shift    ;;
    --primary_energy_min=*   ) export primary_energy_min="${i#*=}"   shift    ;;
    --primary_energy_max=*   ) export primary_energy_max="${i#*=}"   shift    ;;
    --primary_energy_delta=* ) export primary_energy_delta="${i#*=}" shift    ;;
    --gamma_num=*            ) export gamma_num="${i#*=}"            shift    ;;
    --gamma_energy_min=*     ) export gamma_energy_min="${i#*=}"     shift    ;;
    --gamma_energy_max=*     ) export gamma_energy_max="${i#*=}"     shift    ;;
    --gamma_energy_delta=*   ) export gamma_energy_delta="${i#*=}"   shift    ;;
    -*                       ) echo "Unknown option \"$i\"";         return 1 ;;
  esac
done

export dir_out="$(dirname "${output_dir}/${output_name}")"
# cd ${output_dir}
# root -x -q ${dir_scripts}/make_outputFile.C\(\"${output_name}\"\)
# cd -

# make_log

export make_dEdX="1"
export make_emission="0"
export make_transmittance="0"
export energy_cur_export=${primary_energy_max}
export primary_num=${dEdX_num}
run

for (( primary_energy_cur = ${primary_energy_min}; ( primary_energy_cur <= ${primary_energy_max} && primary_energy_cur >= ${primary_energy_min} ); primary_energy_cur += ${primary_energy_delta} )); do
    export detector_dX="10"
    export energy_cur_export=${primary_energy_cur}
    export make_dEdX="0"
    export make_emission="1"
    export make_transmittance="0"
    run
done

for gamma_energy_cur in $(seq $(printf "%.10f" ${gamma_energy_min}) $(printf "%.10f" ${gamma_energy_delta}) $(printf "%.10f" ${gamma_energy_max})); do
    export detector_dX="10"
    export energy_cur_export=$(echo "scale=10; ${gamma_energy_cur}/1000000" | bc)
    export make_dEdX="0"
    export make_emission="0"
    export make_transmittance="1"
    export primary_type="opticalphoton"
    export primary_num=${gamma_num}
    run
done
}

main "$@"