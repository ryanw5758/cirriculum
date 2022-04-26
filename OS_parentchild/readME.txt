Project 1 Operating Systems: Ryan White

This file contains a program to spawn a number of child processes from a parent given a command line argument, and have those processes run a test file which outputs to the terminal.

Compile each test case with the commands in the makefile. Note for test2.c, the -lm command must be added to satisfy the sqrt function's inclusion. After compiling each test case, compile the main program.

In order to run the main program, the command line must take three arguments: the program itself, the number of child processes the user wishes to spawn, and the test case the user wishes to run in each user process.

For example, if the user would like to run test case 1 in 3 child processes, they would input the following into the terminal:

./Project1_OS 3 ./test1

And the output would be as following:

Parent pid is 27687
Started child 1 with pid (27688)
Started child 2 with pid (27689)
Started child 3 with pid (27690)
Running program test1 in process 27688
T1: i 0, i^2 0
T1: i 1, i^2 1
T1: i 2, i^2 4
T1: i 3, i^2 9
T1: i 4, i^2 16
Child 1 (PID 27688) finished
Running program test1 in process 27689
T1: i 0, i^2 0
T1: i 1, i^2 1
T1: i 2, i^2 4
T1: i 3, i^2 9
T1: i 4, i^2 16
Running program test1 in process 27690
T1: i 0, i^2 0
T1: i 1, i^2 1
T1: i 2, i^2 4
T1: i 3, i^2 9
T1: i 4, i^2 16
Child 2 (PID 27689) finished
Child 3 (PID 27690) finished

