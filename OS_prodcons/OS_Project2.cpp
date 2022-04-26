#include <stdio.h>
#include <iostream>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "prod_cons_MT.h"

using namespace std;

int proNum;
int conNum;
monitorClass projMonitor;

int main(int argc, char * argv[]){
    int checkCreate, checkJoin;
    long i, j;
    pthread_t proThreads[proNum];
    pthread_t conThreads[conNum];
    void* status;

    // add the command line handling
    if (argc != 4) {
	cout << "Invalid number of command line arguments" << endl;
	return -1;
    }

    projMonitor.bufferSpaces = atoi(argv[1]);
    proNum = atoi(argv[2]);
    conNum = atoi(argv[3]);

        // FIX TO INCLUDE MONITOR CLASS
    pthread_mutex_init(&projMonitor.bufferLock, NULL);
    pthread_cond_init(&projMonitor.condVarPro, NULL);
    pthread_cond_init(&projMonitor.condVarCon, NULL);
    srand(time(0)); // obtain seed before time operation

    // begin buffer/production operations
    for (i = 0; i < proNum; i++){
        checkCreate = pthread_create(&proThreads[i], NULL, Producer, (void *)i);
        if (checkCreate){
            cout << "Error: pthread_create return code = " << checkCreate << endl;
            exit(-1);
        }
        cout << "Main: started producer P" << i << endl;
    }
    for (j = 0; j < conNum; j++){
        checkCreate = pthread_create(&conThreads[j], NULL, Consumer, (void *)j);
        if (checkCreate){
            cout << "Error: pthread_create return code = " << checkCreate << endl;
            exit(-1);
        }
        cout << "Main: started consumer " << j << endl;
    }

    pthread_cond_destroy(&projMonitor.condVarPro);
    pthread_cond_destroy(&projMonitor.condVarCon);
    pthread_mutex_destroy(&projMonitor.bufferLock);

    // join the threads in order to not crash
    for (i = 0; i < proNum; i ++){
        checkJoin = pthread_join(proThreads[i], &status);
        if (checkJoin){
            cout << "Error: pthread_join return code = " << checkJoin << endl;
            exit(-1);
        }
        cout << "Main: producer " << i << " joined" << endl;
    }
    for (j = 0; j < conNum; j ++){
        checkJoin = pthread_join(conThreads[j], &status);
        if (checkJoin){
            cout << "Error: pthread_join return code = " << checkJoin << endl;
            exit(-1);
        }
        cout << "Main: consumer " << j << " joined" << endl;
    }

    cout << "Main: program completed" << endl;

    pthread_exit(NULL);
}
