#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

#include "sched_sim.h"

using namespace std;

extern ifstream input;
extern ofstream output;
extern int cycle;
extern timeStruct firstCome, shortestJob, shortestTime, robin, prio;

void Process::setBurst(int set){burstTime = set;}
int Process::getBurst(){return burstTime;}

void Process::setPrio(int prio){priority = prio;}
int Process::getPrio(){return priority;}

void Process::setArrival(int arrive){arrivalTime = arrive;}
int Process::getArrival(){return arrivalTime;}

void Process::setProcessID(int ID){processID = ID;}
int Process::getProcessID(){return processID;}

void Process::setWait(int addWait){waitTime = waitTime + addWait;}
int Process::getWait(){return waitTime;}

void Process::setTT(int addTT){turnaround = turnaround + addTT;}
int Process::getTT(){return turnaround;}

static bool sortFunc (Process& p1,  Process& p2) {return p1.getBurst() < p2.getBurst();};
static bool sortID (Process& p1, Process& p2) {return p1.getProcessID() < p2.getProcessID();};

void FCFS (deque<Process> readyDeque, int processNum) { // disregard priority for FCFS: it doesn't matter
    unsigned int time = 0, i;
    int wait = 0, turn = 0;

    set<int> readySet; // set prevents duplication in ready q
    vector<Process> funcVector;
    vector<Process> finishedVec;

    // adapt to vector for implementation purposes: iterating through is easier
    output << "***** FCFS Scheduling *****" << endl;

    while (!readyDeque.empty()){
        funcVector.push_back(readyDeque.front());
        readyDeque.pop_front();
    }

    // simulator loop
    while (!funcVector.empty()) {
        output << "t = " << time << endl; // FIX outputS TO WRITE TO OUTPUT FILE

        // add to the ready set
        for (i = 0; i < funcVector.size(); i ++){
            if (funcVector.at(i).getArrival() <= time) {
                readySet.insert(readySet.end(), funcVector.at(i).getProcessID());
            }
        }

        // running
        if ((funcVector.at(0).getBurst() > 0) && time != 0) {
            output << "CPU: Running process " << funcVector.at(0).getProcessID() << " (CPU burst = " << funcVector.at(0).getBurst() << ")" << endl;
        }

        // running in the case of last process
        else if (funcVector.size() == 1 && (funcVector.at(0).getBurst() - cycle <= 0)) {
            output << "CPU: Running process " << funcVector.at(0).getProcessID() << " (CPU burst = " << funcVector.at(0).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), funcVector.at(0));
            break; // last process has finished running
        }  

        // finishing
        else if (funcVector.at(0).getBurst() <= 0 && (funcVector.at(0).getBurst() - cycle <= 0)) {
            // add handling to load another process
            output << "CPU: Finishing process " << funcVector.at(0).getProcessID() << ", loading process " << funcVector.at(1).getProcessID() 
            << " (CPU burst = " << funcVector.at(1).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), funcVector.at(0));
            funcVector.erase(funcVector.begin());
            readySet.erase(readySet.begin());
        }

        // loading
        if (funcVector.at(0).getArrival() >= time) {
            output << "CPU: Loading process " << funcVector.at(0).getProcessID() << " (CPU Burst = " << funcVector.at(0).getBurst() << ")" << endl;
        }

        // Ready set printing
        printSet(readySet);

        output << endl << endl;

        // update waitTime of processes in ready queue
        for (i = 1; i < funcVector.size()-1; i ++) {
            funcVector.at(i).setWait(funcVector.at(i).getWait() + cycle);
        }
        // update turnaround of all processes, both the one executing and those in the queue
        for (i = 0; i < funcVector.size(); i ++) {
            funcVector.at(i).setTT(funcVector.at(i).getTT() + cycle);
        }
        funcVector.at(0).setBurst(funcVector.at(0).getBurst()-cycle); // change burst time of current running process
        time += cycle; // update time for cycle
    }
    output << "End of FCFS" << endl;
    output << "FCFS Summary (WT = wait time, TT = turnaround time) :" << endl << endl;
    sort(finishedVec.begin(), finishedVec.end(), sortID);
    printFinish(finishedVec);
    // get average wait time and turnaround time
    for (i = 0; i < finishedVec.size(); i ++) {
        wait = wait + finishedVec.at(i).getWait();
        turn = turn + finishedVec.at(i).getTT();
    }
    firstCome.averageWait = (double) wait * 1.0 / (double) finishedVec.size();
    firstCome.averageTT = (double) turn * 1.0 / (double) finishedVec.size();
    output << "AVG" << setw(6) << fixed << setprecision(1) << firstCome.averageWait << setw(6) << firstCome.averageTT << endl;
}

void SJF (deque<Process> readyDeque, int processNum) {
    unsigned int time = 0, i = 0;
    vector<Process> funcVector, preVec;
    vector<Process> finishedVec;
    unordered_set<int> readySet;
    double wait = 0, turn = 0;

    while (!readyDeque.empty()) {
        funcVector.insert(funcVector.begin(), readyDeque.front());
        readyDeque.pop_front();
    }

    sort(funcVector.begin(), funcVector.end(), sortFunc); // overloaded function to sort members of class based on burst

    // test print of funcVector to check if all elements in
    /* for (i = 0; i < funcVector.size(); i ++){
        output << "Process " << funcVector.at(i).getProcessID() << endl;
    } */

    output << endl;

    output << "***** SJF Scheduling *****" << endl;

    while (!funcVector.empty()) {
        output << "t = " << time << endl; // FIX outputS TO WRITE TO OUTPUT FILE

        // add to the ready set FIX THIS LOOP
        for (i = 0; i < funcVector.size(); i ++){
            if (funcVector.at(i).getArrival() <= time) {
                readySet.insert(readySet.begin(), funcVector.at(i).getProcessID());
            }
        }

        // running
        if ((funcVector.at(0).getBurst() > 0) && time != 0) {
            output << "CPU: Running process " << funcVector.at(0).getProcessID() << " (CPU burst = " << funcVector.at(0).getBurst() << ")" << endl;
        }

        // last case running
        else if (funcVector.size() == 1 && (funcVector.at(0).getBurst() - cycle <= 0)) {
            output << "CPU: Running process " << funcVector.at(0).getProcessID() << " (CPU burst = " << funcVector.at(0).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), funcVector.at(0));
            break; // last process has finished running
        }

        // finishing
        else if (funcVector.at(0).getBurst() <= 0 && (funcVector.at(0).getBurst() - cycle <= 0)) {
            // add handling to load another process
            output << "CPU: Finishing process " << funcVector.at(0).getProcessID() << ", loading process " << funcVector.at(1).getProcessID() 
            << " (CPU burst = " << funcVector.at(1).getBurst() << ")" << endl; // will throw out of range after last one is finished, maybe try using ready queue
            finishedVec.insert(finishedVec.end(), funcVector.at(0));
            readySet.erase(funcVector.at(0).getProcessID());
            funcVector.erase(funcVector.begin());
        }

        // loading
        if (funcVector.at(0).getArrival() >= time) {
            output << "CPU: Loading process " << funcVector.at(0).getProcessID() << " (CPU Burst = " << funcVector.at(0).getBurst() << ")" << endl;
        }

        printVecIDs(funcVector);

        output << endl << endl;

        // update waitTime of processes in ready queue
        for (i = 1; i < funcVector.size()-1; i ++) {
            funcVector.at(i).setWait(funcVector.at(i).getWait() + cycle);
        }
        // update turnaround of all processes, both the one executing and those in the queue
        for (i = 0; i < funcVector.size(); i ++) {
            funcVector.at(i).setTT(funcVector.at(i).getTT() + cycle);
        }

        funcVector.at(0).setBurst(funcVector.at(0).getBurst()-cycle);
        time += cycle;
    }
    output << "End of SJF" << endl << endl;
    output << "SJF Summary (WT = wait time, TT = turnaround time) :" << endl << endl;
    sort(finishedVec.begin(), finishedVec.end(), sortID);
    printFinish(finishedVec);
    // get average wait time and turnaround time
    for (i = 0; i < finishedVec.size(); i ++) {
        wait = wait + finishedVec.at(i).getWait();
        turn = turn + finishedVec.at(i).getTT();
    }
    shortestJob.averageWait = (double) wait * 1.0 / (double) finishedVec.size();
    shortestJob.averageTT = (double) turn * 1.0 / (double) finishedVec.size();
    output << "AVG" << setw(6) << shortestJob.averageWait << setw(6) << shortestJob.averageTT << endl;
}

void STCF (deque<Process> readyDeque, int processNum){
    // finish

    unsigned int time = 0, i = 0;
    vector<Process> funcVector, loopVec;
    vector<Process> finishedVec;
    unordered_set<int> readySet;
    vector<Process>::iterator itr;
    bool finished = false; // loop breaker for the last process case
    int temp;
    double wait = 0, turn = 0;

    // need to sort elements by arrival time
    // funcVector handling

    while (!readyDeque.empty()) {
        funcVector.insert(funcVector.begin(), readyDeque.front());
        readyDeque.pop_front();
    }

    sort(funcVector.begin(), funcVector.end(), sortFunc); // overloaded function to sort members of class based on burst time

    output << endl;

    output << "***** STCF Scheduling *****" << endl;

    while (!finished) {
        output << "t = " << time << endl; // FIX outputS TO WRITE TO OUTPUT FILE

        // add to the ready set
        for (i = 0; i < funcVector.size(); i ++){
            if (funcVector.at(i).getArrival() <= time) {
                readySet.insert(readySet.end(), funcVector.at(i).getProcessID());
            }
        }

        // populate a second vector that will contain the processes in the queue, not all the processes overall
        // this is necessary for ordering which process will be executing during each clock cycle

        for (i = 0; i < funcVector.size(); i++) {
            if (funcVector.at(i).getArrival() <= time) {
                // pop funcVector value and add to loopVec
                loopVec.insert(loopVec.begin(), funcVector.at(i));
                funcVector.erase(funcVector.begin() + i);
            }
        }

        // now, based on arrival time, might need to stop running process and run a shorter one instead: implement this
        // add another condition that's like "stopping process X, running process Y"
        // check for smallest burstTime among available processes to run
        // need to add something on context switches or something like that

        temp = loopVec.at(0).getBurst();
        
        for (i = 0; i < loopVec.size(); i ++) {
            if (loopVec.size() != 0) {
                if (loopVec.at(i).getBurst() < temp) {
                    swap(loopVec.at(0), loopVec.at(1));
                    temp = loopVec.at(0).getBurst();
                }
            }
        }
        
        // running
        if ((loopVec.at(0).getBurst() > 0) && time != 0) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        // last case running
        else if (loopVec.size() == 1 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), loopVec.at(0));
            finished = true;
            break; // last process has finished running
        }

        // finishing
        else if (loopVec.at(0).getBurst() <= 0 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            // add handling to load another process
            if (loopVec.size() > 1) {
                output << "CPU: Finishing process " << loopVec.at(0).getProcessID() << ", loading process " << loopVec.at(1).getProcessID() 
                << " (CPU burst = " << loopVec.at(1).getBurst() << ")" << endl; // will throw out of range after last one is finished, maybe try using ready queue
                finishedVec.insert(finishedVec.end(), loopVec.at(0));
                //readySet.erase(loopVec.at(0).getProcessID());
                loopVec.erase(loopVec.begin());
            }
        }

        // loading
        if (loopVec.at(0).getArrival() >= time) {
            output << "CPU: Loading process " << loopVec.at(0).getProcessID() << " (CPU Burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        printVecIDs(loopVec);

        output << endl << endl;

        // update waitTime of processes in ready queue
        for (i = 1; i < loopVec.size()-1; i ++) {
            loopVec.at(i).setWait(loopVec.at(i).getWait() + cycle);
        }
        // update turnaround of all processes, both the one executing and those in the queue
        for (i = 0; i < loopVec.size(); i ++) {
            loopVec.at(i).setTT(loopVec.at(i).getTT() + cycle);
        }

        loopVec.at(0).setBurst(loopVec.at(0).getBurst()-cycle);
        time += cycle;
    }
    output << "End of STCF" << endl;
    sort(finishedVec.begin(), finishedVec.end(), sortID);
    printFinish(finishedVec);
    // get average wait time and turnaround time
    for (i = 0; i < finishedVec.size(); i ++) {
        wait = wait + finishedVec.at(i).getWait();
        turn = turn + finishedVec.at(i).getTT();
    }
    shortestTime.averageWait = (float) wait * 1.0 / (double) finishedVec.size();
    shortestTime.averageTT = (float) turn * 1.0 / (double) finishedVec.size();
    output << "AVG" << setw(6) << shortestTime.averageWait << setw(6) << shortestTime.averageTT << endl;
}

void RoundRobin (deque<Process> readyDeque, int processNum) {
    // finish

    unsigned int time = 0, i = 0;
    vector<Process> funcVector, loopVec;
    vector<Process> finishedVec;
    unordered_set<int> readySet;
    vector<Process>::iterator itr;
    unordered_set<int>::iterator it;
    bool finished = false; // loop breaker for the last process case
    int temp, addCount;
    const int quan = 2;
    double wait = 0, turn = 0;

    while (!readyDeque.empty()) {
        funcVector.insert(funcVector.begin(), readyDeque.front());
        readyDeque.pop_front();
    }

    sort(funcVector.begin(), funcVector.end(), sortFunc); // overloaded function to sort members of class based on burst

    output << endl;

    output << "***** Round Robin Scheduling *****" << endl;

    while (!finished) {
        output << "t = " << time << endl; // FIX outputS TO WRITE TO OUTPUT FILE

        // add to the ready set
        for (i = 0; i < funcVector.size(); i ++){
            // need to sort processes of the same arrival time
            addCount++;
            if (funcVector.at(i).getArrival() <= time) {
                readySet.insert(readySet.end(), funcVector.at(i).getProcessID());
            }
        }

        addCount = 0;

        // populate a second vector that will contain the processes in the queue, not all the processes overall
        // this is necessary for ordering which process will be executing during each clock cycle

        for (i = 0; i < funcVector.size(); i++) {
            if (funcVector.at(i).getArrival() <= time) {
                // pop funcVector value and add to loopVec
                loopVec.insert(loopVec.begin(), funcVector.at(i));
                funcVector.erase(funcVector.begin() + i);
            }
        }

        // rotate processes 

        rotate(loopVec.begin(), loopVec.end()-1, loopVec.end());
        
        // running
        if ((loopVec.at(0).getBurst() > 0) && time != 0) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        // last case running
        else if (loopVec.size() == 1 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), loopVec.at(0));
            finished = true;
            break; // last process has finished running
        }

        // finishing
        else if (loopVec.at(0).getBurst() <= 0 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            // add handling to load another process
            output << "CPU: Finishing process " << loopVec.at(0).getProcessID() << ", loading process " << loopVec.at(1).getProcessID() 
            << " (CPU burst = " << loopVec.at(1).getBurst() << ")" << endl; // will throw out of range after last one is finished, maybe try using ready queue
            finishedVec.insert(finishedVec.end(), loopVec.at(0));
            loopVec.erase(loopVec.begin());
        }

        // loading
        if (loopVec.at(0).getArrival() >= time) {
            output << "CPU: Loading process " << loopVec.at(0).getProcessID() << " (CPU Burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        printVecIDs(loopVec);

        output << endl << endl;

        // update waitTime of processes in ready queue
        // cycle/quan to account for the burst time decreases across snapshot period
        for (i = 1; i < loopVec.size()-1; i ++) {
            loopVec.at(i).setWait(loopVec.at(i).getWait() + cycle/quan);
        }
        // update turnaround of all processes, both the one executing and those in the queue
        for (i = 0; i < loopVec.size(); i ++) {
            loopVec.at(i).setTT(loopVec.at(i).getTT() + cycle/quan);
        }

        loopVec.at(0).setBurst(loopVec.at(0).getBurst()- cycle/quan);
        time += cycle;
    }

    output << "End of Round Robin" << endl;
    sort(finishedVec.begin(), finishedVec.end(), sortID);
    printFinish(finishedVec);
    // get average wait time and turnaround time
    for (i = 0; i < finishedVec.size(); i ++) {
        wait = wait + finishedVec.at(i).getWait();
        turn = turn + finishedVec.at(i).getTT();
    }
    robin.averageWait = (float) wait * 1.0 / (double) finishedVec.size();
    robin.averageTT = (float) turn * 1.0 / (double) finishedVec.size();
    output << "AVG" << setw(9) << robin.averageWait << setw(9) << robin.averageTT << endl;
}

void Priority (deque<Process> readyDeque, int processNum) {
    // finish

    unsigned int time = 0, i = 0;
    vector<Process> funcVector, loopVec;
    vector<Process> finishedVec;
    unordered_set<int> readySet;
    vector<Process>::iterator itr;
    bool finished = false; // loop breaker for the last process case
    int temp;
    double wait = 0, turn = 0;

    // need to sort elements by arrival time
    // funcVector handling

    while (!readyDeque.empty()) {
        funcVector.insert(funcVector.begin(), readyDeque.front());
        readyDeque.pop_front();
    }

    sort(funcVector.begin(), funcVector.end(), sortFunc); // overloaded function to sort members of class based on burst

    // test print of funcVector to check if all elements in
    /* for (i = 0; i < funcVector.size(); i ++){
        output << "Process " << funcVector.at(i).getProcessID() << endl;
    } */

    output << endl;

    output << "***** Priority Scheduling *****" << endl;

    while (!finished) {
        output << "t = " << time << endl; // FIX outputS TO WRITE TO OUTPUT FILE

        // add to the ready set
        for (i = 0; i < funcVector.size(); i ++){
            if (funcVector.at(i).getArrival() <= time) {
                readySet.insert(readySet.end(), funcVector.at(i).getProcessID());
            }
        }

        // populate a second vector that will contain the processes in the queue, not all the processes overall
        // this is necessary for ordering which process will be executing during each clock cycle

        for (i = 0; i < funcVector.size(); i++) {
            if (funcVector.at(i).getArrival() <= time) {
                // pop funcVector value and add to loopVec
                loopVec.insert(loopVec.begin(), funcVector.at(i));
                funcVector.erase(funcVector.begin() + i);
            }
        }

        // since it is priority scheduling, bump the process with the highest priority to the front in order to execute that
        // need to check every iteration if a process with lower priority has been added to loopVec

        for (i = 0; i < loopVec.size(); i ++) {
            if (loopVec.at(i).getPrio() > loopVec.at(0).getPrio()) {
                swap(loopVec.at(0), loopVec.at(i));
            }
        }
        
        // running
        if ((loopVec.at(0).getBurst() > 0) && time != 0) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        // last case running
        else if (loopVec.size() == 1 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            output << "CPU: Running process " << loopVec.at(0).getProcessID() << " (CPU burst = " << loopVec.at(0).getBurst() << ")" << endl;
            finishedVec.insert(finishedVec.end(), loopVec.at(0));
            finished = true;
            break; // last process has finished running
        }

        // finishing
        else if (loopVec.at(0).getBurst() <= 0 && (loopVec.at(0).getBurst() - cycle <= 0)) {
            // add handling to load another process
            output << "CPU: Finishing process " << loopVec.at(0).getProcessID() << ", loading process " << loopVec.at(1).getProcessID() 
            << " (CPU burst = " << loopVec.at(1).getBurst() << ")" << endl; // will throw out of range after last one is finished, maybe try using ready queue
            finishedVec.insert(finishedVec.end(), loopVec.at(0));
            readySet.erase(loopVec.at(0).getProcessID());
            loopVec.erase(loopVec.begin());
        }

        // loading
        if (loopVec.at(0).getArrival() >= time) {
            output << "CPU: Loading process " << loopVec.at(0).getProcessID() << " (CPU Burst = " << loopVec.at(0).getBurst() << ")" << endl;
        }

        printVecIDs(loopVec);

        output << endl << endl;

        // update waitTime of processes in ready queue
        for (i = 1; i < loopVec.size()-1; i ++) {
            loopVec.at(i).setWait(loopVec.at(i).getWait() + cycle);
        }
        // update turnaround of all processes, both the one executing and those in the queue
        for (i = 0; i < loopVec.size(); i ++) {
            loopVec.at(i).setTT(loopVec.at(i).getTT() + cycle);
        }

        loopVec.at(0).setBurst(loopVec.at(0).getBurst()-cycle);
        time += cycle;
    }
    output << "End of Priority" << endl;
    sort(finishedVec.begin(), finishedVec.end(), sortID);
    printFinish(finishedVec);
    // get average wait time and turnaround time
    for (i = 0; i < finishedVec.size(); i ++) {
        wait = wait * 1.0 + finishedVec.at(i).getWait();
        turn = turn * 1.0 + finishedVec.at(i).getTT();
    }
    prio.averageWait = (float) wait * 1.0 / (double) finishedVec.size();
    prio.averageTT = (float) turn * 1.0 / (double) finishedVec.size();
    output << "AVG" << setw(6) << prio.averageWait << setw(6) << prio.averageTT << endl;
    output << endl << endl;
    printTable(firstCome, shortestJob, shortestTime, robin, prio);
}

void printSet(set<int> s) {
    set<int>::iterator itr;
    output << "Ready queue: ";
    for (itr = s.begin(); itr != s.end(); itr++) {
        output << *itr << " ";
    }
}

void printVecIDs(vector<Process> v) {
    unsigned int i;

    output << "Ready queue: ";
    for (i = 0; i < v.size(); i ++) {
        output << v.at(i).getProcessID() << " ";
    }
}

void printFinish(vector<Process> finish) {
    unsigned int i;

    output << "PID" << setw(9) << "WT" << setw(9) << "TT" << endl;
    // adjust for cycle, and then print
    for (i = 0; i < finish.size(); i ++) {
        finish.at(i).setWait(finish.at(i).getWait()/cycle);
        finish.at(i).setTT(finish.at(i).getTT()/cycle);
        output << finish.at(i).getProcessID();
        output << setw(11) << finish.at(i).getWait();
        output << setw(9) << finish.at(i).getTT() << endl;
    }
    output << endl;
}

void printTable(timeStruct fc, timeStruct sjf, timeStruct stcf, timeStruct rr, timeStruct prio) {
    unsigned int i;
    vector<double> waitTimes, turnTimes;

    // load vectors
    waitTimes.push_back(fc.averageWait);
    turnTimes.push_back(fc.averageTT);

    waitTimes.push_back(sjf.averageWait);
    turnTimes.push_back(sjf.averageTT);

    waitTimes.push_back(stcf.averageWait);
    turnTimes.push_back(stcf.averageTT);

    waitTimes.push_back(rr.averageWait);
    turnTimes.push_back(rr.averageTT);

    waitTimes.push_back(prio.averageWait);
    turnTimes.push_back(prio.averageTT);

    // sort vector values for displaying
    //sort(waitTimes.begin(), waitTimes.end());
    //sort(turnTimes.begin(), waitTimes.end());

    output << "***** OVERALL SUMMARY *****" << endl << endl;
    output << "Average Wait Time Comparison" << endl;
    output << setw(0) << "1. FCFS" << setw(8) << waitTimes.at(0) << endl;
    output << setw(0) << "2. SJF" << setw(9) << waitTimes.at(1) << endl;
    output << setw(0) << "3. STCF" << setw(8) << waitTimes.at(2) << endl;
    output << setw(0) << "4. RR" << setw(10) << waitTimes.at(3) << endl;
    output << setw(0) << "5. Prio" << setw(8) << waitTimes.at(4) << endl;
    output << "Average Turnaround Time Comparison" << endl;
    output << setw(0) << "1. FCFS" << setw(8) << turnTimes.at(0) << endl;
    output << setw(0) << "2. SJF" << setw(9) << turnTimes.at(1) << endl;
    output << setw(0) << "3. STCF" << setw(8) << turnTimes.at(2) << endl;
    output << setw(0) << "4. RR" << setw(10) << turnTimes.at(3) << endl;
    output << setw(0) << "5. Prio" << setw(8) << turnTimes.at(4) << endl;
}