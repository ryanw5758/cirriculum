#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {

    pid_t pid, pid2;
    pid_t pid_num[atoi(argv[1])];
    int i, NUM_PROC, status, childNo = 1;
    int childArray[atoi(argv[1])];
    //char* file[] = {"./test1",NULL};

    if (argc != 3) {
	cout << "Invalid number of command line arguments" << endl;
	return -1;
    }

    NUM_PROC = atoi(argv[1]);
    for (i = 1; i < NUM_PROC+1; i ++) {

	    pid_num[i] = fork();
	    if (pid_num[i] < 0) {
		// pid returns less than 0, child not created
		cout << "Fork failure" << endl;
		return -1;
	    }

	    else if (pid_num[i] == 0) {
	        if (i == 1) {
	        cout << "Parent pid is " << getppid() << endl;
	        }
		// pid equates to 0, child is created
		cout << "Started child " << i << " with pid (" << getpid() << ")" << endl;
		execlp(argv[2],argv[2],NULL);
		exit(0);
	    }

    }

    for (i = 1; i < NUM_PROC+1; i++){
            cout << "Child " << i << " (PID " << wait(&status-1) << ") finished" << endl;
    }

    return 0;
}
