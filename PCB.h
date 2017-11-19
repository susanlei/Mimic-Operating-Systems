#ifndef PCB_H
#define PCB_H


class PCB {
public:
	PCB(){
		priority = 0;
		byteSize = 0;
		PID = 0;
	}
	void setValues(int newPriority, long newSize, int PIDcounter);
	void setRamLocation(long startRAM); //takes the location where it should start

	int getPriorityLvl();
	long getByteSize();
	int getPID();
	long getStartRAM();
	long getEndRAM();
private:
	int priority;
	long byteSize;
	int PID;

	//Indicate location in RAM
	long startInRAM;
	long endInRAM;
};

#endif
