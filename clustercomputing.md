# Hands-on: Using Cartesius and Lisa

> Login to Cartesius with your sdemo account and password

`ssh sdemoXXX@cartesius.surfsara.nl`

Replace `XXX` with your sdemo account number.

> Exercise 1: warm up

```
$ pwd         # current directory 
$ date        # print or set system date and time 
$ uname       # name of the system 
$ man bc      # manual of command ‘bc’, press 'q' to quit manual
$ touch test  # create an empty file test
$ nano        # text editor
              # enter some text and save it to a file
```

> Exercise 2: software modules

Go to *userinfo.cartesius.nl*, select Cartesius/Lisa -> Software.

```
module avail              # list installed modules on the system
module avail software     # list installed modules for 'software'
module load modulename    # load module 'modulename'
module unload modulename  # unload module 'modulename'
```

> Exercise 3: running a job

Open text editor, and type in the code below, save it to a file 'mycode'.

```
#!/bin/bash
echo "running on " $(hostname)
echo "1 + 1" | bc
sleep 20
```

Execute the code:
`./mycode`

Does it work? Probably not! Why?
(Hint: change file permission to executable)

*Write a job script and save it as 'job.sh':*

```
#SBATCH -N 1
#SBATCH -t 00:05:00
#SBATCH -p short
./mycode
```

*Submit a batch job:*

`sbatch job.sh`

*Query job status:*

`squeue -u sdemoXXX`

*Cancel batch job:*

`scancel jobID`

> Exercise 4: Run serial code on multiple cores
