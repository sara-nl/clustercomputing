# Hands-on: Using Cartesius and Lisa

> Login to Cartesius with your sdemo account and password

`ssh sdemoXXX@cartesius.surfsara.nl`

Replace `XXX` with your sdemo account number.

> Copy code examples to your home directory

`cp -r /home/sdemo001/usingcartesius .`

`.` is the current directory

> Exercise 1: warm up

```
$ pwd             # current directory 
$ date            # print or set system date and time 
$ uname           # name of the system 
$ man bc          # manual of command ‘bc’, press 'q' to quit manual
$ touch test      # create an empty file 'test'
$ nano            # text editor
                  # enter some text and save it to a file
```

> Exercise 2: software modules

Go to *userinfo.cartesius.nl*, select *Cartesius -> Software* or *Lisa -> Software*.

```
module avail                # list installed modules on the system
module avail software       # list installed modules for 'software'
module load modulename      # load module 'modulename'
module unload modulename    # unload module 'modulename'
```

> Exercise 3: running a job

Open a text editor, e.g. `nano` and type in the code below, save it to a file `mycode`.

```
#!/bin/bash
echo "command line argument " $1
echo "running on " $(hostname)
echo "1 + 1" | bc
sleep 20
```

Execute the code:
`./mycode`

Does it work? Probably not! Why?
(Hint: change file permission to make it executable)

*Write a job script and save it as `job.sh`:*

```
#SBATCH -N 1
#SBATCH -t 00:05:00
#SBATCH -p short
./mycode
```

*Submit a batch job:*

On Cartesius: `sbatch job.sh`
On Lisa: `qsub job.sh`

*Query job status:*

On Cartesius: `squeue -u sdemoXXX` or `squeue jobId`
On Lisa: `qstat -u sdemoXXX` or `qstat -n jobId`

*Cancel batch job:*

On Cartesius: `scancel jobID`
On Lisa: `qdel jobID`

> Exercise 4: Run serial code on multiple cores

Use bash for loop:

```
for i in {1..24}
do
(
 ./mycode $i
) &
done
wait
```

**NOTE** that

`$i` is the value of `i` in the current loop

`&` makes sure that each process runs at backgroud

`wait` tells the script to wait until all processes are finished

> Exercise 5: running a wave equation

```
# load modules
module load openmpi
module load c/intel
module load hdf5
# compile the program
make
# submit the job
sbatch run_wave
```

Wait till the job finishes, and copy the result to your local computer to view

```
scp sdemoNNN@cartesius.surfsara.nl:usingcartesius/wave/wave.h5.gif  ./
```

