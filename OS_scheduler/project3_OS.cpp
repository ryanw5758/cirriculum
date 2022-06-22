#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>

#include "sched_sim.h"
using namespace std;

ifstream input;
ofstream output;
int cycle;

timeStruct firstCome, shortestJob, shortestTime, robin, prio;

int main(int argc, char* argv[]){
    deque<Process> readyQueue;
    deque<int> attrQueue;
    Process addObj;
    int count = 0, addData, attrSize;
    string readLine;

    // command line handling
    if (argc != 4) {
	    cout << "Invalid number of command line arguments" << endl;
	    return -1;
    }

    // global variable definition
    input.open(argv[1]);
    output.open(argv[2]);
    cycle = atoi(argv[3]);

    // exit program if input file not opened
    if (!input){
        cout << "Input file could not be opened. Exiting program." << endl;
        return -1;
    }

    // fill queue
    while (input >> addData) {
        attrQueue.push_front(addData);
    }

    attrSize = attrQueue.size() / 3 - 1;

    while (!attrQueue.empty()){
        addObj.setProcessID(attrSize-count);
        addObj.setArrival(attrQueue.front());
        attrQueue.pop_front();
        addObj.setPrio(attrQueue.front());
        attrQueue.pop_front();
        addObj.setBurst(attrQueue.front());
        attrQueue.pop_front();
        readyQueue.push_front(addObj);
        count ++;
    }
    
    // now that queue is full, perform scheduling operations
    // these functions write to the output file, so no need for any steps past this point in main
    FCFS(readyQueue, count);
    SJF(readyQueue, count);
    STCF(readyQueue, count);
    RoundRobin(readyQueue, count);
    Priority(readyQueue, count);

    // close files
    input.close();
    output.close();

    return 0;
}