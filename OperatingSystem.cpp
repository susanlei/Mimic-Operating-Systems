#include "OperatingSystem.h"
#include <iostream>
using namespace std;

int OperatingSystem::establishPIDnum() {
	PIDcounter++;
	return PIDcounter;
}

void OperatingSystem::printIODeviceQueue() { //Print what process is using IO and processes in their queues
	cout << endl << endl;
	cout << "---------------------------------------------" << endl;
	//Hard Disks
	for (int i = 0; i < numOfHardDisks; i++) {
		cout << "Hard Disk #" << i+1;
		if (HardDisks[i].inUse == false) {
			cout << " is NOT being used." << endl;
		}
		else {
			cout << " used by Process PID: " << HardDisks[i].ptrToPCB->getPID() << "   RAM: " << HardDisks[i].ptrToPCB->getStartRAM() << " - " << HardDisks[i].ptrToPCB->getEndRAM() << endl;
			cout << "   Hard Disk #" << i+1 << "    Queue Size: " << HardDiskQueues[i].size() << endl;
			for (int j = 0; j < HardDiskQueues[i].size(); j++) {
				cout << "      " << j+1 << ". Process PID: " << HardDiskQueues[i].at(j)->getPID() << "  RAM: " << HardDiskQueues[i].at(j)->getStartRAM() << " - " << HardDiskQueues[i].at(j)->getEndRAM() << endl;
			}
		}
	}
	//Printers
	cout << endl;
	for (int i = 0; i < numOfPrinters; i++) {
		cout << "Printer #" << i+1;
		if (Printers[i].inUse == false) {
			cout << " is NOT being used." << endl;
		}
		else {
			cout << " used by Process PID: " << Printers[i].ptrToPCB->getPID() << "   RAM: " << Printers[i].ptrToPCB->getStartRAM() << " - " << Printers[i].ptrToPCB->getEndRAM() << endl;
			cout << "   Printer #" << i+1 << "    Queue Size " << PrinterQueues[i].size() << endl;
			for (int j = 0; j < PrinterQueues[i].size(); j++) {
				cout << "      " << j+1 << ". Process PID: " << PrinterQueues[i].at(j)->getPID() << " RAM: " << PrinterQueues[i].at(j)->getStartRAM() << " - " << PrinterQueues[i].at(j)->getEndRAM() << endl;
			}
		}
	}
	cout << "---------------------------------------------" << endl;
	cout << endl << endl;
}

void OperatingSystem::initialValues(long mRAM, int nHD, int nP){
	RAMmemory = mRAM;
	availableMemory = RAMmemory;
	numOfHardDisks = nHD;
	numOfPrinters = nP;

	//initialize the number of HardDisks to the vectors
	for (int i = 0; i < numOfHardDisks; i++) {
		HardDisks.push_back(HardDisk());
		HardDiskQueues.push_back(deque<PCB*>());
	}
	for (int i = 0; i < numOfPrinters; i++) {
		Printers.push_back(Printer());
		PrinterQueues.push_back(deque<PCB*>());
	}
}

//Hard Disk Functions
void OperatingSystem::useHardDiskNewProcess(int requestedHDnum, PCB* requestingProcess){
	if (HardDisks[requestedHDnum-1].inUse == false) {//Queue is empty & HardDisk# is empty
		HardDisks[requestedHDnum-1].inUse = true;
		HardDisks[requestedHDnum-1].ptrToPCB = requestingProcess;
	}
	else if (HardDisks[requestedHDnum-1].inUse == true) {//Queue is empty but HardDisk in use
		addHardDiskToQueue(requestedHDnum, requestingProcess);
		//cout << HardDiskQueues[2].at(0)->getByteSize() << endl;
	}
}
void OperatingSystem::addHardDiskToQueue(int requestedHDnum, PCB* requestingProcess) {
	HardDiskQueues[requestedHDnum-1].push_back(requestingProcess); //at the harddisk requested number
	//cout << HardDiskQueues[2].at(0)->getByteSize() << endl;
}
PCB* OperatingSystem::leaveHardDisk(int requestedHDnum) {
	if (HardDisks[requestedHDnum-1].inUse == false) {
		cout << "ERROR: Hard Disk # " << requestedHDnum << " is not being used." << endl;
	}
	else {
		PCB* tempPtr = new PCB;
		tempPtr = HardDisks[requestedHDnum-1].ptrToPCB;
		HardDisks[requestedHDnum-1].ptrToPCB = NULL;
		HardDisks[requestedHDnum-1].inUse = false;
		nextProcessUseHardDisk(requestedHDnum);
		return tempPtr;
	}
	//
	return NULL;
}
void OperatingSystem::nextProcessUseHardDisk(int requestedHDnum) {
	if (HardDiskQueues[requestedHDnum-1].empty()) { //Queue is empty
		return;
	}
	else {
		HardDisks[requestedHDnum-1].ptrToPCB = HardDiskQueues[requestedHDnum-1].at(0);
		HardDisks[requestedHDnum-1].inUse = true;
		HardDiskQueues[requestedHDnum-1].pop_front();
	}
}

//Printer Functions
void OperatingSystem::usePrinterNewProcess(int requestedPnum, PCB* requestingProcess) {
	if (Printers[requestedPnum-1].inUse ==false) {
		Printers[requestedPnum-1].inUse = true;
		Printers[requestedPnum-1].ptrToPCB = requestingProcess;
	}
	else if (Printers[requestedPnum-1].inUse == true) {
		addPrinterToQueue(requestedPnum, requestingProcess);
	}
}
void OperatingSystem::addPrinterToQueue(int requestedPnum, PCB* requestingProcess) {
	PrinterQueues[requestedPnum-1].push_back(requestingProcess);
}
PCB* OperatingSystem::leavePrinter(int requestedPnum) {
	if (Printers[requestedPnum-1].inUse == false) {
		cout << "ERROR: Printer# " << requestedPnum << " is not being used." << endl;
	}
	else {
		PCB* tempPtr = new PCB;
		tempPtr = Printers[requestedPnum-1].ptrToPCB;
		Printers[requestedPnum-1].ptrToPCB = NULL;
		Printers[requestedPnum-1].inUse = false;
		nextProcessUsePrinter(requestedPnum);
		return tempPtr;
	}
	return NULL;
}
void OperatingSystem::nextProcessUsePrinter(int requestedPnum) {
	if (PrinterQueues[requestedPnum-1].empty()) {
		return;
	}
	else {
		Printers[requestedPnum-1].ptrToPCB = PrinterQueues[requestedPnum-1].at(0);
		Printers[requestedPnum-1].inUse = true;
		PrinterQueues[requestedPnum-1].pop_front();
	}
}

char OperatingSystem::readCommands(char letterInput) {
	cout << "Enter your command: " << endl;
	cin >> letterInput;
	myRam.setRAM(RAMmemory);
	if (letterInput == 'A') { //new process created
		int priorityOfProcess;
		long sizeOfProcess;
		cin >> priorityOfProcess;
		if (priorityOfProcess >= 0 && priorityOfProcess < 5) {
			//valid priority
			cin >> sizeOfProcess;
			if (sizeOfProcess > RAMmemory || sizeOfProcess > availableMemory) {
				cout << "Error: Not enough memory within system for process." << endl;
			}
			else if (sizeOfProcess <= RAMmemory) {
				//VALID COMMAND
				PCB* tempPCB = myRam.addNewProcess(priorityOfProcess, sizeOfProcess, establishPIDnum());
				if (tempPCB != NULL) { //Not enough memory
					myReadyQueue.addNewProcessToQueue(tempPCB);
				}
			}
			else {
				cout << "Invalid command. Please input command again" << endl;
			}
		}
		else { //invalid priority number
			cout << "Invalid priority number. Please input command again with the correct priority" << endl;
		}
	}
	else if (letterInput == 't') { //process currently using CPU is terminated
		if (myReadyQueue.getUsagefromCPU() == false) {
			cout << "Process cannot be terminated: There is no process currently using the CPU" << endl;
		}
		else {
			int terminatedPID = myReadyQueue.terminateProcessInCPU();
			myRam.removeProcess(terminatedPID);
		}
	}
	else if (letterInput == 'd') { //process currently using CPU request Hard Disk
		int hardDiskNum;
		cin >> hardDiskNum;
		if (hardDiskNum > 0 && hardDiskNum <= numOfHardDisks) {
			//THIS IS IF THE HARD DISK NUMBER STARTS WITH 1
			//VALID COMMAND

			//Take information of PROCESS wanting to use CPU
			if (myReadyQueue.getUsagefromCPU() == true) { //There is a process using the CPU
				//int processPID_hd = myReadyQueue.getPIDfromCPU();
				PCB* processPtr_hd = myReadyQueue.getProcessPtrCPU();
				useHardDiskNewProcess(hardDiskNum, processPtr_hd); //Process using HD
				myReadyQueue.processNeedsIODevice();
			}
			else { //No process using CPU -> cannot be sent 
				cout << "There is no available process to send to Hard Disk #" << hardDiskNum << endl;
			}
		}
		else {
			cout << "Invalid Hard Disk Number. Please input command again with correct number" << endl;
		}
	}
	else if (letterInput == 'p') { //process currently using CPU request Printer
		int printerNum;
		cin >> printerNum;
		if (printerNum > 0 && printerNum <= numOfPrinters) {
			//THIS IS IF THE PRINTER NUMBER STARTS WITH 1
			//VALID COMMAND
			if (myReadyQueue.getUsagefromCPU() == true) { //There is a process using the CPU
				//int processPID_p = myReadyQueue.getPIDfromCPU();
				PCB* processPtr_p = myReadyQueue.getProcessPtrCPU();
				usePrinterNewProcess(printerNum, processPtr_p);
				myReadyQueue.processNeedsIODevice();
			}
			else { //No process using CPU -> cannot be sent 
				cout << "There is no available process to send to Printer #" << printerNum << endl;
			}
		}
		else {
			cout << "Invalid Printer Number. Please input command again with correct Number" << endl;
		}
	}
	else if (letterInput == 'D') { //Hard Disk NUMBER has finished the work for one process
		int hardDiskNum;
		cin >> hardDiskNum;
		if (hardDiskNum > 0 && hardDiskNum <= numOfHardDisks) {
			//THIS IS IF THE HARD DISK NUMBER STARTS WITH 1
			//VALID COMMAND

			//Get pointerToProcess currently using HD# return to here
			//move next Process to use the HD
			if (HardDisks[hardDiskNum-1].inUse == true) { //HardDisk Num is BEING used right now.
				PCB* tempPtr = leaveHardDisk(hardDiskNum);
				myReadyQueue.addNewProcessToQueue(tempPtr);
			}
			else {
				cout << "There is no process currently using Hard Disk #" << hardDiskNum << endl;
			}
			//Send pointer back to readyqueue -addNewProcessToQueue();
		}
		else {
			cout << "Invalid Hard Disk Number. Please input command again with correct number" << endl;
		}
	}
	else if (letterInput == 'P') { //Printer NUMBER has finished for one process
		int printerNum;
		cin >> printerNum;
		if (printerNum > 0 && printerNum <= numOfPrinters) {
			//THIS IS IF THE PRINTER NUMBER STARTS WITH 1
			//VALID COMMAND
			if (Printers[printerNum-1].inUse == true) { //HardDisk Num is BEING used right now.
				PCB* tempPtr = leavePrinter(printerNum);
				myReadyQueue.addNewProcessToQueue(tempPtr);
			}
			else {
				cout << "There is no process currently using Printer #" << printerNum << endl;
			}
		}
		else {
			cout << "Invalid Printer Number. Please input command again with correct Number" << endl;
		}
	}
	else if (letterInput == 'S') {
		char secondLetterInput;
		cin >> secondLetterInput;
		if (secondLetterInput == 'r') {
			//show what process is currently using the CPU
			myReadyQueue.printProcessInCPUQueue();
		}
		else if (secondLetterInput == 'i') {
			//show what processes are currently using the I/O devices
			printIODeviceQueue();
		}
		else if (secondLetterInput == 'm') {
			//show state of memory
			myRam.printMemory();
		}
		else { //INVALID COMMAND
			cout << "You command does not exist" << endl;
		}
	}
	else if (letterInput == 'Q') {
		return letterInput;
	}
	else {
		cout << "Error: Invalid command. Please try again." << endl;
	}
	return letterInput;
}
