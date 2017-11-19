Author: Shu Xin Lei
Course: CSCI34000-01
Program: Stimulates the operating system in C++ by mimicking OS's memory and scheduling. There are also options for process to use hard disks and printers. User enter commands in order to provide the OS with instructions. RAM follows a “First Fit” algorithm. Ready Queue is multilevel, having five priority levels ranging from 0-4. 4 being the highest priority, and 0 being the lowest priority. Ready Queue follows “Highest Priority First” algorithm, however within each priority queue, it follows “First Come First Serve”. Hard disk and printer queues follow a “First Come First Serve” algorithm.

To compile, type:       make all
To run, type:           ./operatingsystem

