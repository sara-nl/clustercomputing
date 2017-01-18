# Hands-on: Using Cartesius and Lisa

> Login to Cartesius with your sdemo account and password

`ssh sdemoXXX@cartesius.surfsara.nl`

Replace `XXX` with your sdemo account number.

**Optional: Using public keys for SSH authentication**

After logging in to Cartesius, create a `.ssh` directory and copy your public key contents to file `authorized_keys`.
**NOTE** that
`.ssh` directory should have permission 700 (`drwx------`)
`authorized_keys` should have permission 644 (`-rw-r--r--`)

```
mkdir .ssh
chmod 700 .ssh
cd .ssh
nano authorized_keys
# copy your public key contents in the file and save it
chmod 644 authorized_keys
```

> Copy code examples to your home directory

`cp -r /home/sdemo001/usingcartesius .`

`.` is the current directory, you can also use `$HOME` instead

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

Go to *userinfo.surfsara.nl*, select *Cartesius -> Software* or *Lisa -> Software*.

You will see a list of sofware that is already installed on the system. Use the commands below to load/unload a module.

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
echo "command line argument is " $1
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
#!/bin/bash
#SBATCH -N 1
#SBATCH -t 00:05:00
#SBATCH -p short
./mycode 1
```

*Submit a batch job:*

- On Cartesius: `sbatch job.sh`
- On Lisa: `qsub job.sh`

*Query job status:*

- On Cartesius: `squeue -u sdemoXXX` or `squeue -j jobId`
- On Lisa: `qstat -u sdemoXXX` or `qstat -n jobId`

*Cancel batch job:*

- On Cartesius: `scancel jobID`
- On Lisa: `qdel jobID`

Have you got the output? How does it look like?

*Job output*

- On Cartesius: `slurm-NNNNN.out`
- On Lisa: `job.sh.eNNNNN` and `job.sh.oNNNNN`

Where `NNNNN` is the jobID.

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

- `$i` is the value of `i` in the current loop

- `&` makes sure that each process runs at backgroud simultaneously

- `wait` tells the script to wait until all processes are finished

Go to the `matlab` directory, look at the contents of script `matrixmul.sh`. Do you understand everything written there?

If so, submit the job.

```
cd matlab
sbatch matrixmul.sh
```

`ssh` to the node where your job is running. Use `top` to see what is going on.

The matlab program `matrixmul.m` is compiled using

```
module load matlab
mcc -R –singleCompThread -m matrixmul.m
module unload matlab
```

After compilation, no matlab module is needed to run the program, which means NO license is needed.

**NOTE** that,

we have limited number of matlab licenses, therefore, we strongly recommend everyone to compile their matlab code before submitting it to the system.

> Exercise 5: running a wave equation

```
cd wave
# load modules
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

> Exercise 6: Use scratch space

Look at `mydata.sh` in `data` directory and see how you can copy input data to `$TMPDIR` and copy the result back to your home directory.

```
cd data
sbatch mydata.sh
```

Copy result locally to view it.

`scp sdemoXXX@cartesius.surfsara.nl:usingcartesius/data/data_00000.h5.png .`
