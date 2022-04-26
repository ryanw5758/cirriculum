#include "prod_cons_MT.h"
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

extern int proNum;
extern int conNum;
extern monitorClass projMonitor;

using namespace std;
void *Producer(void *paramPro){ 
    int add, threadNum; // change to depend on buffer size later
    int i;

    threadNum = (long)paramPro;
    add = rand() % 7;
    cout << "P" << threadNum << ": Producing 6 values" << endl; // fix thread id
    for (i = 0; i < 6; i ++){
        // stuff here
        //sem_wait(&projMonitor.bufferEmpty);
        add = rand() % 7;
	sleep(1);
        pthread_mutex_lock(&projMonitor.bufferLock);
        if (projMonitor.count == projMonitor.bufferSpaces) {
            cout << "P" << threadNum << ": Blocked due to full buffer" << endl;
            while (projMonitor.count >= projMonitor.bufferSpaces) {
                pthread_cond_wait(&projMonitor.condVarPro, &projMonitor.bufferLock);
            }
            cout << "P" << threadNum << ": Done waiting on full buffer" << endl;
            projMonitor.count = 0;
            pthread_cond_signal(&projMonitor.condVarCon);
            break;
        }
        projMonitor.dataBuffer[i] = add;
        cout << "P"<< threadNum << ": Writing " << add << " to position " << projMonitor.pos << endl; // fix thread id
        projMonitor.pos = (projMonitor.pos + 1) % projMonitor.bufferSpaces;
        projMonitor.count++;
        pthread_mutex_unlock(&projMonitor.bufferLock);
    }
    pthread_exit((void*) paramPro);
}

void *Consumer(void *paramCon){ 
    int i, consume, threadNum;

    sleep(1);
    threadNum = (long)paramCon;
    cout << "C" << threadNum << ": Consuming 6 values" << endl; // fix thread id
    for (i = 0; i < 6; i ++){
	sleep(1);
        pthread_mutex_lock(&projMonitor.bufferLock);
        if (projMonitor.count == projMonitor.bufferSpaces) {
            cout << "C" << threadNum << ": Blocked due to empty buffer" << endl;
            while (projMonitor.count == 0) {
                pthread_cond_wait(&projMonitor.condVarCon, &projMonitor.bufferLock);
            }
            cout << "C" << threadNum << ": Done waiting on empty buffer" << endl;
            projMonitor.count--;
            pthread_cond_signal(&projMonitor.condVarPro);
            break;
        }
        consume = projMonitor.dataBuffer[projMonitor.output];
        cout << "C" << threadNum << ": Reading " << consume << " from  position " << projMonitor.output << endl; // fix thread id
        projMonitor.output = (projMonitor.output + 1) % projMonitor.bufferSpaces;
        pthread_mutex_unlock(&projMonitor.bufferLock);
    }

    pthread_exit((void*) paramCon);
}
