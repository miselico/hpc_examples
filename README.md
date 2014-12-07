This repository contains some basic examples about the use of MPI.


Commands for compiling and running the code.
============================================

*These commands are specific for the taito supercomputer at CSC in Finland* 
Other environments have similar commands, but they are likely different. Check the manual for the computer you are working on

Compiling MPI code
------------------

    mpicc -O3 -Wall codefile.c -o executable

* `mpicc` is the compiler use for compiling c code which uses MPI
* `-03` sets the optimization level, this should be left out if you plan to use a debugger,
* `-Wall` turns on all warnings
* `codefile.c` is the file you want to compile
* `-o ex2` specifies the name of the executable which will be created

Executing the code
------------------
In order to execute the code on the cluster, you need to create a batch script like the example `script.sh`

Using this script you can place the job on the queue as follows:

    sbatch script.sh 

Observing execution
-------------------
You can check the status of the job as follows:

    squeue -l -u $USER

which will give you the status of all jobs you currently have. You can also see all jobs currently queued using `squeue -l`.

If your program writes to standard out or error, this will be written to the files which you specified in the script.

To cancel a job, you need its ID (from the squeue command) and then execute 

    scancel  3382891

Other
-----
You can use nano or other editors on login-node. X-forwarding is possible.

Using `saldo`, you can see how many computation hours there are left.
