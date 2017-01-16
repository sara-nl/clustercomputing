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
