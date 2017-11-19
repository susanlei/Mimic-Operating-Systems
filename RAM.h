#ifndef RAM_H
#define RAM_H

#include<deque>
#include "PCB.h"
class RAM {
public:
	void setRAM(long newRAMmemory);
	PCB* addNewProcess(int nPriority, long nSize, int PIDcounter);
	void removeProcess(int processPID); //Process leaves RAM

	void printMemory();
private:
    std::deque<PCB*> processList;
	long RAMmemory;
};

#endif
