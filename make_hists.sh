
echo "Processing command line arguments."
for i in "$@"; do
  case $i in
    --dir_out              ) export DIR_OUT="${i#*=}"     shift    ;;
    --dir_exec             ) export DIR_EXEC="${i#*=}"    shift    ;;
    --dir_script           ) export DIR_SCRIPT="${i#*=}"  shift    ;;
    --G4_particle          ) export DIR_SCRIPT="${i#*=}"  shift    ;;
    --G4_nParticles        ) export DIR_SCRIPT="${i#*=}"  shift    ;;
    --G4_material          ) export DIR_SCRIPT="${i#*=}"  shift    ;;
    -*                     ) echo "Unknown option \"$i\"" return 1 ;;
  esac
done


cat <<EOF > 
root --web=off -x -q ${DIR_SCRIPT}/make_dTdXHist.C\(\{\"G4ANNIERecoParticles.root\"\},\"${DIR_OUT}\",0\)