#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <vector>
#include <deque>
#include "PCB.h"
#include "RAM.h"
#include "ReadyQueue.h"
using namespace std;

struct HardDisk {
	bool inUse = false;
	PCB* ptrToPCB;
};
struct Printer {
	bool inUse = false;
	PCB* ptrToPCB;
};

class OperatingSystem {
public:
	OperatingSystem(){
		RAMmemory = 0;
		numOfHardDisks = 0;
		numOfPrinters = 0;
		availableMemory = 0;
		PIDcounter = 0; 
	}
	void initialValues(long mRAM, int nHD, int nP);
	void updateMemory();
	char readCommands(char letterInput); //A function that reads in commands from user
	int getPIDNumber(); //helper function to get PID number

	int establishPIDnum(); //increase PID returns the PID num

	//HardDisk Functions
	void useHardDiskNewProcess(int requestedHDnum, PCB* requestingProcess);
	void addHardDiskToQueue(int requestedHDnum, PCB* requestingProcess);
	PCB* leaveHardDisk(int requestedHDnum);
	void nextProcessUseHardDisk(int requestedHDnum);
	//Printer Functions
	void usePrinterNewProcess(int requestedPnum, PCB* requestingProcess);
	void addPrinterToQueue(int requestedPnum, PCB* requestingProcess);
	PCB* leavePrinter(int requestedPnum);
	void nextProcessUsePrinter(int requestedPnum);

	void printIODeviceQueue();

private:
	RAM myRam;
	ReadyQueue myReadyQueue;
	vector<deque<PCB*> > HardDiskQueues; //vector of Queues for each HardDisk
	vector<HardDisk> HardDisks;

	vector<deque<PCB*> > PrinterQueues; //vector of Queues for each Printer
	vector<Printer> Printers;

	long RAMmemory;
	int numOfHardDisks;
	int numOfPrinters;
	long availableMemory;

	int PIDcounter; 
};

#endif
