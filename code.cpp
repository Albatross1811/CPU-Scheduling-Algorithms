#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <map>
#include <vector>
using namespace std;

class Process {
    int id;
    int burstTime;
    int arrivalTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
public:
    int getId() const { 
        return id; 
    }
    int getBurstTime() const { 
        return burstTime; 
    }
    int getArrivalTime() const { 
        return arrivalTime; 
    }
    int getCompletionTime() const { 
        return completionTime; 
    }
    int getTurnAroundTime() const { 
        return turnAroundTime;
    }
    int getWaitingTime() const { 
        return waitingTime; 
    }
    
    void setId(int id) { 
        this->id = id; 
    }
    void setBurstTime(int burstTime) { 
        this->burstTime = burstTime; 
    }
    void setArrivalTime(int arrivalTime) { 
        this->arrivalTime = arrivalTime; 
    }
    void setCompletionTime(int completionTime) { 
        this->completionTime = completionTime; 
    }
    void setTurnAroundTime(int turnAroundTime) { 
        this->turnAroundTime = turnAroundTime; 
    }
    void setWaitingTime(int waitingTime) { 
        this->waitingTime = waitingTime; 
    }
};

bool compareByArrival(const Process &p, const Process &q) {
    return p.getArrivalTime() < q.getArrivalTime();
}

bool compareByBurst(const Process &p, const Process &q) {
    return p.getBurstTime() < q.getBurstTime();
}

bool compareById(const Process &p, const Process &q) {
    return p.getId() < q.getId();
}

void display(const Process P[], int jobCount, float avgwt = 0, float avgtat = 0) {
    vector<Process> processes(P, P + jobCount);
    sort(processes.begin(), processes.end(), compareById);
    cout << "\n\n\t\t The Process Status \n\n";
    cout << "\tProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time";
    for (const auto &process : processes)
        cout << "\n\t\t" << process.getId() << "\t\t" << process.getArrivalTime() << "\t\t" 
             << process.getBurstTime() << "\t\t" << process.getCompletionTime() << "\t\t" 
             << process.getTurnAroundTime() << "\t\t" << process.getWaitingTime();
    cout << "\n\n\t\tAverage Waiting Time: " << avgwt;
    cout << "\n\t\tAverage Turn Around Time: " << avgtat;
    cout << "\n\n\n";
}

void getData(Process P[], int &jobCount) {
    int x;
    for (int i = 0; i < jobCount; ++i) {
        P[i].setId(i + 1);
        cout << "\n\t Process ID: " << P[i].getId();
        cout << "\n\t Enter the Process Arrival Time: ";
        cin >> x;
        P[i].setArrivalTime(x);
        cout << "\n\t Enter the Process Burst Time: ";
        cin >> x;
        P[i].setBurstTime(x);
    }
}

void generateRandomData(Process P[], int jobCount) {
    srand(time(NULL));
    for (int i = 0; i < jobCount; ++i) {
        P[i].setId(i + 1);
        P[i].setArrivalTime(rand() % 16);
        P[i].setBurstTime(rand() % 20 + 2);
        P[i].setCompletionTime(0);
        P[i].setTurnAroundTime(0);
        P[i].setWaitingTime(0);
    }
}

void RoundRobin(Process P[], int jobCount) {
    cout << "\n\t*** Round Robin ***\n";
    int tQuantum;
    cout << "\t Time quantum : ";
    cin >> tQuantum;

    vector<bool> inQueue(jobCount + 1, false);
    map<int, int> id_compl;
    int jobDone = 0, curTime = 0;
    queue<Process> readyQueue;

    do {
        for (int i = 0; i < jobCount; ++i) {
            if (!inQueue[P[i].getId()] && P[i].getArrivalTime() == curTime) {
                readyQueue.push(P[i]);
                inQueue[P[i].getId()] = true;
            }
        }
        if (!readyQueue.empty()) {
            Process p = readyQueue.front();
            readyQueue.pop();
            int tq = min(tQuantum, p.getBurstTime());
            p.setBurstTime(p.getBurstTime() - tq);
            for (int i = curTime + 1; i <= curTime + tq; ++i) {
                for (int j = 0; j < jobCount; ++j) {
                    if (!inQueue[P[j].getId()] && P[j].getArrivalTime() == i) {
                        readyQueue.push(P[j]);
                        inQueue[P[j].getId()] = true;
                    }
                }
            }
            curTime += tq;
            if (p.getBurstTime() == 0) {
                jobDone++;
                p.setCompletionTime(curTime);
                id_compl[p.getId()] = p.getCompletionTime();
            } else {
                readyQueue.push(p);
            }
        } else {
            curTime++;
        }
    } while (jobDone != jobCount);

    float avgWaitTime = 0, avgTurnAroundTime = 0;

    for (int i = 0; i < jobCount; ++i) {
        P[i].setCompletionTime(id_compl[P[i].getId()]);
        P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
        P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
        avgWaitTime += P[i].getWaitingTime();
        avgTurnAroundTime += P[i].getTurnAroundTime();
    }

    avgWaitTime /= jobCount;
    avgTurnAroundTime /= jobCount;

    display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

void FirstComeFirstServed(Process P[], int jobCount) {
    cout << "\n\t*** FCFS ***\n";
    float avgWaitTime = 0, avgTurnAroundTime = 0;

    sort(P, P + jobCount, compareByArrival);
    for (int i = 0, prevEnd = 0; i < jobCount; ++i) {
        P[i].setCompletionTime(max(prevEnd, P[i].getArrivalTime()) + P[i].getBurstTime());
        P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
        P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
        prevEnd = P[i].getCompletionTime();
        avgWaitTime += P[i].getWaitingTime();
        avgTurnAroundTime += P[i].getTurnAroundTime();
    }

    avgWaitTime /= jobCount;
    avgTurnAroundTime /= jobCount;

    display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

void ShortestJobFirst(Process P[], int jobCount) {
    cout << "\n\t*** SJF ***\n";
    int executedCount = 0;
    vector<bool> processActive(jobCount, false);
    vector<Process> processQueue;
    map<int, int> id_compl;

    for (int time = 0; executedCount < jobCount;) {
        for (int i = 0; i < jobCount; ++i) {
            if (!processActive[P[i].getId() - 1] && P[i].getArrivalTime() <= time) {
                processQueue.push_back(P[i]);
                processActive[P[i].getId() - 1] = true;
            }
        }
        if (!processQueue.empty()) {
            auto minPosition = min_element(processQueue.begin(), processQueue.end(), compareByBurst);
            Process processMinBurstTime = *minPosition;
            time += processMinBurstTime.getBurstTime();
            id_compl[processMinBurstTime.getId()] = time;
            executedCount++;
            processQueue.erase(minPosition);
        } else {
            time++;
        }
    }

    float avgWaitTime = 0, avgTurnAroundTime = 0;

    for (int i = 0; i < jobCount; ++i) {
        P[i].setCompletionTime(id_compl[P[i].getId()]);
        P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
        P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
        avgWaitTime += P[i].getWaitingTime();
        avgTurnAroundTime += P[i].getTurnAroundTime();
    }

    avgWaitTime /= jobCount;
    avgTurnAroundTime /= jobCount;

    display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

void ShortestJobRemainingFirst(Process P[], int jobCount) {
    cout << "\n\t*** SJRF ***\n";
    int time = 0, executedCount = 0;
    float avgTurnAroundTime = 0, avgWaitTime = 0;
    vector<Process> processQueue;
    vector<bool> inQueue(jobCount, false);
    map<int, int> pid_compl;

    while (executedCount != jobCount) {
        for (int i = 0; i < jobCount; ++i) {
            if (P[i].getArrivalTime() <= time && !inQueue[i]) {
                processQueue.push_back(P[i]);
                inQueue[i] = true;
            }
        }
        if (!processQueue.empty()) {
            auto minPosition = min_element(processQueue.begin(), processQueue.end(), compareByBurst);
            (*minPosition).setBurstTime((*minPosition).getBurstTime() - 1);
            time++;
            if ((*minPosition).getBurstTime() == 0) {
                pid_compl[(*minPosition).getId()] = time;
                executedCount++;
                processQueue.erase(minPosition);
            }
        } else {
            time++;
        }
    }

    for (int i = 0; i < jobCount; ++i) {
        P[i].setCompletionTime(pid_compl[P[i].getId()]);
        P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
        P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
        avgWaitTime += P[i].getWaitingTime();
        avgTurnAroundTime += P[i].getTurnAroundTime();
    }

    avgWaitTime /= jobCount;
    avgTurnAroundTime /= jobCount;

    display(P, jobCount, avgWaitTime, avgTurnAroundTime);
}

int main() {
    int schedulingType, dataInputChoice, jobCount;
    while (true) {
        cout << "\n\t*****CPU Scheduling Algorithms*****\n";
        cout << "\t 1. First Come First Served (FCFS)\n\t 2. Shortest Job First (SJF)\n\t 3. Round Robin (RR)\n\t 4. Shortest Job Remaining First (SJRF)\n\t 5. All\n\t 0. Exit\n";
        cout << "\n\t Enter your choice [0-5] : ";
        cin >> schedulingType;

        if (schedulingType == 0) {
            exit(0);
        }

        cout << "\n\t Manually enter data or Auto generated data? \n\t 1. Manually \t 2. Random Generated \n";
        cout << "\n\t Enter your choice [1/2] : ";
        cin >> dataInputChoice;

        cout << "\t No. of processes : ";
        cin >> jobCount;

        vector<Process> P(jobCount);

        if (dataInputChoice == 1) {
            getData(P.data(), jobCount);
        } else {
            generateRandomData(P.data(), jobCount);
        }

        switch (schedulingType) {
            case 1:
                FirstComeFirstServed(P.data(), jobCount);
                break;
            case 2:
                ShortestJobFirst(P.data(), jobCount);
                break;
            case 3:
                RoundRobin(P.data(), jobCount);
                break;
            case 4:
                ShortestJobRemainingFirst(P.data(), jobCount);
                break;
            case 5:
                FirstComeFirstServed(P.data(), jobCount);
                ShortestJobFirst(P.data(), jobCount);
                RoundRobin(P.data(), jobCount);
                ShortestJobRemainingFirst(P.data(), jobCount);
                break;
        }
    }
    return 0;
}
