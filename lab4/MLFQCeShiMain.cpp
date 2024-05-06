#include "MLFQ.h"
#include <iostream>

int main() 
{
    std::vector<int> time_quantum = {2, 4, 8};
    MLFQ scheduler(3, time_quantum);

    Process process1 = {1, 0, 6, 0, 0, 0, 0, 0, READY};
    Process process2 = {2, 1, 4, 0, 0, 0, 0, 0, READY};
    Process process3 = {3, 2, 8, 0, 0, 0, 0, 0, READY};
    Process process4 = {4, 3, 5, 0, 0, 0, 0, 0, READY};

    scheduler.addProcess(process1);
    scheduler.addProcess(process2);
    scheduler.addProcess(process3);
    scheduler.addProcess(process4);

    int current_time = 0;
    scheduler.schedule(current_time);
    scheduler.printResults(current_time);

    return 0;
}
