# Hands-on: Introduction to UNIX

> Generate SSH key **on your laptop** and upload the public key to portal.surfsara.nl

```
$ cd                            # change directory to home directory
$ ssh-keygen                    # generate SSH key pair
$ cat .ssh/id_rsa.pub           # view contents of public key
```

MobaXterm user can find the generated key-pair at

	`My Documents -> MobaXterm -> home -> .ssh`


> Login to  LISA with your sdemo account and password

`ssh sdemoXXX@lisa.surfsara.nl`

Replace `XXX` with your sdemo account number. You should be able to login to LISA without being asked for a password, because you’ve already uploaded your public key onto the SURFsara Portal.
Type `logout` or `Ctrl+d` to logout from LISA


> Login to LISA with your sdemo account and your key pair. You don't need to type in the password now if you didn't use a password to generate your key pair.

`ssh sdemoXXX@lisa.surfsara.nl`

*My first commands*

```
$ pwd           # current directory
$ date          # print or set system date and time
$ w             # who logged in
$ whoami        # who am I?
$ abc           # an unknown command
$ uname         # name of the system
$ man bc        # manual of command ‘bc’, press 'q' to quit manual
$ bc            # calculator, type ‘quit’ to quit ‘bc’
$ logout        # logout of the system
```

> Login to LISA and download the examples we prepared for you and we will look at some more commands

```
$ svn export https://subtrac.surfsara.nl/userdoc/examples/lisatutorial
$ ls                    # list contents of directory
$ ls -l                 # what is the difference?
$ ls -a                 # show all directories
                        # '.' current directory
                        # '..' parent directory
$ cd ..                 # move one directory up
$ pwd                   # where am I
```

*Permission bits*
```
$ ls –l                         # notice the permission bits
                                # drwx------
                                # ‘d’ directory = folder
                                # ‘r’ read, ‘w’ write, ‘x’ execute
$ cd lisatutorial               # notice the change in prompt
                                # ~ home directory
                                # / separates directory names
$ ls –l
$ chmod –x jobs                 # remove x-bit from jobs
$ ls –ld jobs                   # -d flag shows properties of directory, not contents
$ cd jobs                       # will fail
$ chmod 700 jobs                # ‘r’ read = 4
                                # ‘w’ write = 2
                                # ‘x’ execute = 1
                                # ‘rw’ 4+2 = 6
                                # ‘rwx’ 4+2+1 = 7
$ cd jobs                       # now you can access jobs
```

*Standard input, output, and error*

> Every program has three predefined input/output files associated:
- Standard input (stdin): normally your keyboard
- Standard output (stdout): normally your screen
- Standard error (stderr): normally your screen
- stderr is for error messages (in general)

```
$ cd
$ cd lisatutorial/simple
$ cat bcin                      # show contents of file ‘bcin’
$ bc < bcin                     # ‘bc’ takes stdin from file ‘bcin’
$ bc < bcin > bcout             # write output to ‘bcout’
$ cat bcout
$ cat bcin | bc                 # | ‘pipe’: output of ‘cat’ goes to
                                # input of ‘bc’
```

*Create simple text files*

```
$ nano                          # text editor, use ^X (Ctrl + X) to quit 
```

*Environment variables*

```
$ echo $HOME                    # home directory
$ echo $PATH                    # directories in which shell will search for programs
$ export PATH=$HOME/bin:$PATH
                                # extend the PATH variable to search
                                # also for programs in $HOME/bin
```

*Some more commands*

```
$ touch one             # create an empty file
$ cp one two            # copy
$ less bcout            # view file, 'q' to quit
$ mv two three          # rename file
$ mkdir mydir           # create directory
$ rmdir mydir           # delete directory
$ rm three              # delete file
```

## My first script
> Type in *nano* the following and save the script as *myscript* 

```
#!/bin/bash
echo "Hello World!"
echo "$1 + $2 is "
echo "$1 + $2" | bc
```

> Execute *myscript*

```
$ chmod +x myscript     # make the script executable
$ ./myscript 3 4        # run the script
```
`$1` and `$2` are the command line arguments given to the program.

## Exercises
> Write a script to display current directory, home directory and the PATH environment variable

Result should look like:
```
Thu Jan  5 14:03:55 CET 2017
/home/sdemo001
/sara/sw/modules-ng-64/wrappers/sara:/bin:/usr/bin:/usr/bin/X11:/usr/local/bin
```
> Write a script using for loop to display number 1 to 10
(Hint: bash for loop)

```
for i in {1..10}
do
# write something here
done
```

> Write a script to list all file names in directory lisatutorial/simple
(Hint: Everything you type between backticks \`\` is evaluated (executed) by the shell before the main command,
e.g. \`ls ~/lisatutorial/simple\`)

Result of the program should be:
```
bcin
file1
file2.txt
```

**For future questions, please contact us at [SURFsara helpdesk](mailto:helpdesk@surfsara.nl).**

## Solution to exercises

> Write a script to display date, home directory and the PATH environment variable

```
#!/bin/bash
date
echo $HOME
echo $PATH
```

> Write a script using for loop to display number 1 to 10

```
#!/bin/bash
for i in {1..10}
do
  echo $i
done
```

> Write a script to list all file names in directory lisatutorial/simple

```
#!/bin/bash
for file in `ls ~/lisatutorial/simple`
do
  echo $file
done
```
