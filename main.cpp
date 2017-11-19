#include "PCB.h"
#include "ReadyQueue.h"
#include "RAM.h"
#include "OperatingSystem.h"
#include <iostream>
using namespace std;

int main() {
	OperatingSystem myOperatingSystem;

	long tempRAMmemory;
	int tempHardDisks, tempPrinters;

	cout << "How much RAM memory is there on the simulated computer in bytes? Enter up to 4000000000." << endl;
	cin >> tempRAMmemory;
	if (tempRAMmemory > 4000000000 || tempRAMmemory < 0) {
		cout << "Please enter RAM size of less than 4000000000." << endl;
		cin >> tempRAMmemory;
	}
	cout << "How many hard disks the simulated computer has?" << endl;
	cin >> tempHardDisks;
	if (tempHardDisks < 0) {
		cout << "Please enter a valid number of hard disks" << endl;
		cin >> tempHardDisks;
	}
	cout << "How many printers the simulated computer has?" << endl;
	cin >> tempPrinters;
	if (tempPrinters < 0) {
		cout << "Please enter a valid number of hard disks" << endl;
		cin >> tempPrinters;
	}
	cout << "Note: If you wish to quit, please enter 'Q' " << endl;

	char letterInput = 'S'; 

	myOperatingSystem.initialValues(tempRAMmemory, tempHardDisks, tempPrinters);

	while (letterInput != 'Q') {
		letterInput = myOperatingSystem.readCommands(letterInput);
	}

	return 0;
};
