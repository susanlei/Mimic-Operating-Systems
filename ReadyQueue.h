#ifndef READYQUEUE_H
#define READYQUEUE_H

#include<deque>
#include "PCB.h"
using namespace std;

struct CPU {
	int processPID = 0;
	PCB* ptrToPCB;
	bool inUse = false;
};

///
class ReadyQueue {
public:
	void placeInQueue (PCB* newProcess);
	void addNewProcessToQueue(PCB* newProcess);
	void moveProcessToCPU();
	int terminateProcessInCPU(); //returns PID
	void processNeedsIODevice();

	int getPIDfromCPU();
	bool getUsagefromCPU();
	PCB* getProcessPtrCPU();
	void printProcessInCPUQueue();
private:
	CPU myCPU;
    deque<PCB*> priority0;
    deque<PCB*> priority1;
    deque<PCB*> priority2;
    deque<PCB*> priority3;
    deque<PCB*> priority4;
};

#endif
