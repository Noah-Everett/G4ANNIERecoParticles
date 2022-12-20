main() {
echo "Processing command line arguments."
for i in "$@"; do
  case $i in
    --dir_out=*          ) export dir_out="${i#*=}" shift    ;;
    --dir_exec=*         ) export dir_exec="${i#*=}" shift    ;;
    --dir_script=*       ) export dir_script="${i#*=}" shift    ;;
    --G4_particle=*      ) export G4_particle="${i#*=}" shift    ;;
    --G4_nParticles=*    ) export G4_nParticles="${i#*=}" shift    ;;
    --G4_material=*      ) export G4_material="${i#*=}" shift    ;;
    --G4_record_gammas=* ) export G4_record_gammas="${i#*=}" shift    ;;
    --G4_record_dEdX=*   ) export G4_record_dEdX="${i#*=}" shift    ;;
    --E_min=*            ) export E_min="${i#*=}" shift    ;;
    --E_max=*            ) export E_max="${i#*=}" shift    ;;
    --E_delta=*          ) export E_delta="${i#*=}" shift    ;;
    -*                   ) echo "Unknown option \"$i\""; return 1 ;;
  esac
done

mkdir ${dir_out}/macros
mkdir ${dir_out}/hists
mkdir ${dir_out}/G4

cat <<EOF > ${dir_out}/macros/detector.mac
/ANNIERecoParticles/material ${G4_material}
/ANNIERecoParticles/record/dEdX ${G4_record_dEdX}
/ANNIERecoParticles/record/gammas ${G4_record_gammas}
EOF

nRun=0
for (( E=${E_min}; ( E<=${E_max} && E>=${E_min} ); E+=${E_delta} )); do
    cat <<EOF > ${dir_out}/macros/run_${nRun}.mac
/run/initialize

/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/process/verbose 0

/gun/particle ${G4_particle}
/gun/energy ${E} MeV
/gun/position 0 0 0
/gun/direction 1 0 0

/process/activate Cerenkov
/process/activate Scintillation
/process/optical/cerenkov/setTrackSecondariesFirst true
/process/optical/scintillation/setTrackSecondariesFirst true

/run/beamOn ${G4_nParticles}
EOF
    ${dir_exec}/G4ANNIERecoParticles ${dir_out}/macros/detector.mac ${dir_out}/macros/run_${nRun}.mac
    mv G4ANNIERecoParticles.root ${dir_out}/G4/G4ANNIERecoParticles_${nRun}.root
    rm G4ANNIERecoParticles_t*.root
    root --web=off -x -q ${dir_script}/make_dTdXHist.C\(\"${dir_out}/G4/G4ANNIERecoParticles_${nRun}.root\",\"${dir_out}/hists/${E}.root\"\)
    rm ${dir_out}/macros/run_${nRun}.mac               # optional
    rm ${dir_out}/G4/G4ANNIERecoParticles_${nRun}.root # optional
    nRun=$((nRun+1))
done

mv ${dir_out}/hists/* ${dir_out}/ # optional
rm -r ${dir_out}/macros           # optional
rm -r ${dir_out}/G4               # optional
rm -r ${dir_out}/hists            # optional

cat <<EOF > ${dir_out}/batch.log
#==============================#
#========== settings ==========#
#==============================#
         dir_out=${dir_out}
        dir_exec=${dir_exec}
      dir_script=${dir_script}
     G4_particle=${G4_particle}
   G4_nParticles=${G4_nParticles}
     G4_material=${G4_material}
G4_record_gammas=${G4_record_gammas}
  G4_record_dEdX=${G4_record_dEdX}
           E_min=${E_min}
           E_max=${E_max}
         E_delta=${E_delta}



#==================================#
#========== detector.mac ==========#
#==================================#
/ANNIERecoParticles/material ${G4_material}
/ANNIERecoParticles/record/dEdX ${G4_record_dEdX}
/ANNIERecoParticles/record/gammas ${G4_record_gammas}



#=============================#
#========== run.mac ==========#
#=============================#
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/process/verbose 0

/gun/particle ${G4_particle}
/gun/energy <E> MeV
/gun/position 0 0 0
/gun/direction 1 0 0

/process/activate Cerenkov
/process/activate Scintillation
/process/optical/cerenkov/setTrackSecondariesFirst true
/process/optical/scintillation/setTrackSecondariesFirst true

/run/beamOn ${G4_nParticles}
EOF

}
main "$@"