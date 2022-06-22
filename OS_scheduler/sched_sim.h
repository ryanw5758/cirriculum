#include <set>
#include <unordered_set>

using namespace std;

class Process {
    public:
        void setBurst(int set);
        int getBurst();
        void setPrio(int prio);
        int getPrio();
        void setArrival(int arrive);
        int getArrival();
        void setProcessID(int ID);
        int getProcessID();
        void setWait(int addWait);
        int getWait();
        void setTT(int addTT);
        int getTT();
        static bool sortFunc (const Process& p1, const Process& p2);
        static bool sortID (const Process& p1, const Process& p2);
    private:
        int burstTime;
        int priority;
        int arrivalTime;
        int processID;
        int waitTime = 0;
        int turnaround = 0;
};

class timeStruct {
    public:
        double averageWait;
        double averageTT;
};

void FCFS(deque<Process> readyDeque, int processNum);
void SJF(deque<Process> readyDeque, int processNum);
void STCF(deque<Process> readyDeque, int processNum);
void RoundRobin(deque<Process> readyDeque, int processNum);
void Priority(deque<Process> readyDeque, int processNum);
void printSet(set<int> s);
void printUnorderedSet(unordered_set<int> s);
void printVecIDs(vector<Process> v);
void printFinish(vector<Process> finish);
void printTable(timeStruct fc, timeStruct sjf, timeStruct stcf, timeStruct rr, timeStruct priority);
