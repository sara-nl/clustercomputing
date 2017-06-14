#!/bin/bash
#SBATCH -N 1
#SBATCH -t 00:10:00
##SBATCH --reservation=bootcamp

jobdir=$HOME/clustercomputing/code/imageconv

# Copy images to scratch
cp /scratch-shared/zhengm/data/*.png $TMPDIR

# Change directory to scratch
cd $TMPDIR
starttime=`date +%s`

for imag in `ls $TMPDIR`
do
  $jobdir/imageconv $imag
done

endtime=`date +%s`
runtime=$((endtime-starttime))

echo "Total runtime is $runtime seconds."
# Copy results back to home directory

cp $TMPDIR/result* $jobdir/results_serial/
