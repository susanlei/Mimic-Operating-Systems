#include "RAM.h"
#include <iostream>
using namespace std;

void RAM::setRAM(long newRAMmemory) {
	RAMmemory = newRAMmemory;
}
PCB* RAM::addNewProcess(int nPriority, long nSize, int PIDcounter) {
	deque<PCB*>::iterator it = processList.begin();
	if (processList.empty()) { //Empty list
		if (nSize <= RAMmemory){
				PCB* tempPCB = new PCB;
				tempPCB->setValues(nPriority, nSize, PIDcounter);
				tempPCB->setRamLocation(0);
				processList.push_front(tempPCB);
				return tempPCB;
		}
	}
	else {
		if (processList.at(0)->getStartRAM() != 0) { //STARTING RAM DOES NOT START WITH 0 [gap in the front]
			long availStartRAM = 0;
			long availEndRAM = processList.at(0)->getStartRAM() - 1;
			long availTotalRAM = availEndRAM - availStartRAM + 1;
			if (availTotalRAM >= nSize) { //Enough RAM to fit new process
				PCB* tempPCB = new PCB;
				tempPCB->setValues(nPriority, nSize, PIDcounter);
				tempPCB->setRamLocation(availStartRAM);
				processList.insert(it, tempPCB);
				return tempPCB;
			}
		}
		for (int i = 0; i < processList.size(); i++) { //Go through the list until it reaches the end
			int endOfListNum = processList.size()-1;
			if(i < endOfListNum) { //Not the last element
				long availStartRAM = processList.at(i)->getEndRAM() + 1;
				long availEndRAM = processList.at(i+1)->getStartRAM() - 1;
				long availTotalRAM = availEndRAM - availStartRAM + 1;
				if (availTotalRAM >= nSize) { //Enough RAM to fit new process
					PCB* tempPCB = new PCB;
					tempPCB->setValues(nPriority, nSize, PIDcounter);
					tempPCB->setRamLocation(availStartRAM);
					processList.insert(it+1, tempPCB);
					return tempPCB;
				}
			}
			else if (i == endOfListNum) { //End of the list
				long availStartRAM = processList.at(i)->getEndRAM() + 1;
				long availEndRAM = RAMmemory - 1;
				long availTotalRAM = availEndRAM - availStartRAM + 1;
				if (availTotalRAM >= nSize) {
					PCB* tempPCB = new PCB;
					tempPCB->setValues(nPriority, nSize, PIDcounter);
					tempPCB->setRamLocation(availStartRAM);
					processList.push_back(tempPCB);
					return tempPCB;
				}
				else {
					cout << "ERROR: Not enough RAM to fit new process" << endl;
				}
			}
			it++;
		}
	}
}
void RAM::removeProcess(int processPID) { //DELETE THE ACTUAL PROCESS
	for (int i = 0; i < processList.size(); i++) {
		if (processList.at(i)->getPID() == processPID) {
			delete processList.at(i);
			processList.erase(processList.begin() + i);
			return;
		}
		else if (i == processList.size() - 1) {
			cout << "PID does not exist" << endl;
		}
	}
}

void RAM::printMemory() {
	cout << endl << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Total process inside RAM:" << processList.size() << endl;
	cout << "Process PID : Start RAM - End RAM " << endl;
	for (int i = 0; i < processList.size(); i++) {
		cout << "    " << processList.at(i)->getPID() << "    : " << processList.at(i)->getStartRAM() << " - " << processList.at(i)->getEndRAM() << endl;
	}
	cout << "---------------------------------------------" << endl;
	cout << endl << endl;
}
