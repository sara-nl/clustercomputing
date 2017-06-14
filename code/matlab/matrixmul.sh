#!/bin/bash
#SBATCH -n 24
#SBATCH -t 00:10:00
#SBATCH --reservation=bootcamp

module load mcr

for i in {1..24}
do
(
  export MCR_CACHE_ROOT=$TMPDIR/mcr_$i 
 ./matrixmul $i 10000
) &
done
wait
