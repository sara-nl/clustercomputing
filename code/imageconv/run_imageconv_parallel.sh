#!/bin/bash
#SBATCH -N 1
#SBATCH -t 00:10:00
##SBATCH --reservation=bootcamp

jobdir=$HOME/clustercomputing/code/imageconv

# Change directory to scratch
# Copy images to scratch
cp /scratch-shared/zhengm/data/*.png $TMPDIR
cp imagefile $TMPDIR
cd $TMPDIR

module load stopos
stopos purge -p images
stopos create -p images
stopos -p images add imagefile

starttime=`date +%s`
for i in {1..24}
do
(
  while true;
  do
    stopos next -p images
    if [ "$STOPOS_RC" != "OK" ]; then
      break
    fi
    $jobdir/imageconv $STOPOS_VALUE
    stopos remove -p images
  done
) &
done

wait
endtime=`date +%s`
runtime=$((endtime-starttime))

echo "Total runtime is $runtime seconds."

stopos purge -p images

# Copy results back to home directory
cp $TMPDIR/result* $jobdir/results_parallel/
