#include "PCB.h"

void PCB::setValues(int newPriority, long newSize, int PIDcounter) {
	//PIDcounter++;
	PID = PIDcounter;
	priority = newPriority;
	byteSize = newSize;
}
void PCB::setRamLocation(long startRAM){
	startInRAM = startRAM; //Where THIS process's RAM suppose to start
	endInRAM = startRAM + byteSize - 1;
}
int PCB::getPriorityLvl() {
	return priority;
}
long PCB::getByteSize() {
	return byteSize;
}
int PCB::getPID() {
	return PID;
}
long PCB::getStartRAM() {
	return startInRAM;
}
long PCB::getEndRAM() {
	return endInRAM;
}
