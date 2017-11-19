#include "ReadyQueue.h"
#include <iostream>
using namespace std;

void ReadyQueue::printProcessInCPUQueue() { //When user type S r
	cout << endl << endl;
	cout << "---------------------------------------------" << endl;
	if (myCPU.inUse == false) {//No Process using CPU and no process in Queue
		cout << "There is no process currently using CPU or in Queue" << endl;
	}
	else {
		cout << "Process using the CPU : " << endl;
		cout << "  Process PID: " << myCPU.processPID << "   RAM: " << myCPU.ptrToPCB->getStartRAM() << " - " << myCPU.ptrToPCB->getEndRAM() << endl << endl;
		cout << "Process that are currently waiting for the CPU:" << endl;
		cout << "  Queue - Priority 4: " << priority4.size() << endl;
		if (priority4.size() != 0) { //List has things
			for (int i = 0; i < priority4.size(); i++) {
				cout << "   " << i+1 << ". Process PID: " << priority4.at(i)->getPID() << "  RAM: " << priority4.at(i)->getStartRAM() << " - " << priority4.at(i)->getEndRAM() << endl;
			}
		}
		cout << "  Queue - Priority 3: " << priority3.size() << endl;
		if (priority3.size() != 0) { //List has things
			for (int i = 0; i < priority3.size(); i++) {
				cout << "   " << i+1 << ". Process PID: " << priority3.at(i)->getPID() << "  RAM: " << priority3.at(i)->getStartRAM() << " - " << priority3.at(i)->getEndRAM() << endl;
			}
		}
		cout << "  Queue - Priority 2: " << priority2.size() << endl;
		if (priority2.size() != 0) { //List has things
			for (int i = 0; i < priority2.size(); i++) {
				cout << "   " << i+1 << ". Process PID: " << priority2.at(i)->getPID() << "  RAM: " << priority2.at(i)->getStartRAM() << " - " << priority2.at(i)->getEndRAM() << endl;
			}
		}
		cout << "  Queue - Priority 1: " << priority1.size() << endl;
		if (priority1.size() != 0) { //List has things
			for (int i = 0; i < priority1.size(); i++) {
				cout << "   " << i+1 << ". Process PID: " << priority1.at(i)->getPID() << "  RAM: " << priority1.at(i)->getStartRAM() << " - " << priority1.at(i)->getEndRAM() << endl;
			}
		}
		cout << "  Queue - Priority 0: " << priority0.size() << endl;
		if (priority0.size() != 0) { //List has things
			for (int i = 0; i < priority0.size(); i++) {
				cout << "   " << i+1 << ". Process PID: " << priority0.at(i)->getPID() << "  RAM: " << priority0.at(i)->getStartRAM() << " - " << priority0.at(i)->getEndRAM() << endl;
			}
		}
	}
	cout << "---------------------------------------------" << endl;
	cout << endl << endl;

}
bool ReadyQueue::getUsagefromCPU() {
	return myCPU.inUse;
}
int ReadyQueue::getPIDfromCPU() {
	return myCPU.processPID;
}
PCB* ReadyQueue::getProcessPtrCPU() {
	return myCPU.ptrToPCB;
}

void ReadyQueue::placeInQueue(PCB* process) { //Always place into queue
	int newPP = process->getPriorityLvl();
	if (newPP == 0) {
		priority0.push_back(process);
	}
	else if (newPP == 1) {
		priority1.push_back(process);
	}
	else if (newPP == 2) {
		priority2.push_back(process);
	}
	else if (newPP == 3) {
		priority3.push_back(process);
	}
	else if (newPP == 4) {
		priority4.push_back(process);
	}
}
void ReadyQueue::addNewProcessToQueue(PCB* newProcess) {
	if (newProcess == NULL) {
		return;
	}
	int newPP = newProcess->getPriorityLvl();
	if (myCPU.inUse == false) { //empty CPU
		myCPU.inUse = true;
		myCPU.processPID = newProcess->getPID();
		myCPU.ptrToPCB = newProcess;
	}
	else if (newPP > myCPU.ptrToPCB->getPriorityLvl() && myCPU.inUse == true) { //CPU IN USE - new process has priority
		PCB* tempPtr = myCPU.ptrToPCB;
		placeInQueue(tempPtr); //place process using CPU back to queue due to low priority
		myCPU.ptrToPCB = newProcess;
		myCPU.processPID = newProcess->getPID();
		myCPU.inUse = true;
	}
	else if (newPP <= myCPU.ptrToPCB->getPriorityLvl()) { //CPU IN USE - Less priority than current process using CPU
		placeInQueue(newProcess);
	}

}
void ReadyQueue::moveProcessToCPU() { //Move highest process to CPU
	if (!priority4.empty()) {
		myCPU.inUse = true;
		myCPU.ptrToPCB = priority4.front();
		myCPU.processPID = priority4.front()->getPID();
		priority4.pop_front();
	}
	else if (!priority3.empty()) {
		myCPU.inUse = true;
		myCPU.ptrToPCB = priority3.front();
		myCPU.processPID = priority3.front()->getPID();
		priority3.pop_front();
	}
	else if (!priority2.empty()) {
		myCPU.inUse = true;
		myCPU.ptrToPCB = priority2.front();
		myCPU.processPID = priority2.front()->getPID();
		priority2.pop_front();
	}
	else if (!priority1.empty()) {
		myCPU.inUse = true;
		myCPU.ptrToPCB = priority1.front();
		myCPU.processPID = priority1.front()->getPID();
		priority1.pop_front();
	}
	else if (!priority0.empty()) {
		myCPU.inUse = true;
		myCPU.ptrToPCB = priority0.front();
		myCPU.processPID = priority0.front()->getPID();
		priority0.pop_front();
	}
	else {
		myCPU.inUse = false; //Ready Queue is Empty
	}
}
int ReadyQueue::terminateProcessInCPU() {
	int PIDofProcessT = myCPU.processPID;
	myCPU.processPID = 0;
	myCPU.inUse = false;
	myCPU.ptrToPCB = NULL;
	moveProcessToCPU();
	return PIDofProcessT;
}
void ReadyQueue::processNeedsIODevice() {
	//Another process use CPU
	myCPU.processPID = 0;
	myCPU.inUse = false;
	myCPU.ptrToPCB = NULL;
	moveProcessToCPU();
}
