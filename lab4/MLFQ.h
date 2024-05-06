#include "Process.h"
#include <queue>
#include <vector>
#include <iostream>

class MLFQ 
{
public:
    MLFQ(int num_queues, std::vector<int> time_quantum);
    void addProcess(Process process);
    void schedule(int& current_time); // 添加参数 current_time
    void printResults(int current_time); // 添加参数 current_time

private:
    // 友元声明
    friend int main();

    int num_queues;
    std::vector<int> time_quantum;
    std::vector<std::queue<Process>> queues;
    Process* running_process;

    void addToQueue(Process process);
    Process* selectNextProcess();
    void updateProcessState(Process* process);
};

MLFQ::MLFQ(int num_queues, std::vector<int> time_quantum) : num_queues(num_queues), time_quantum(time_quantum) 
{
    queues.resize(num_queues);
    running_process = nullptr;
}

void MLFQ::addProcess(Process process) 
{
    addToQueue(process);
}

void MLFQ::schedule(int& current_time) 
{
    int total_processes = 0;
    int finished_processes = 0;
    
    // 初始化 total_processes
    for (int i = 0; i < num_queues; ++i) 
    {
        total_processes += queues[i].size();
    }

    while (finished_processes < total_processes) 
    {
        Process* next_process = selectNextProcess();
        if (next_process != nullptr) 
        {
            updateProcessState(next_process);
            int time_slice = time_quantum[next_process->priority];
            for (int i = 0; i < time_slice && next_process->burstTime > 0; ++i) 
            {
                next_process->burstTime--;
                current_time++;
            }
            if (next_process->burstTime == 0) 
            {
                next_process->state = TERMINATED;
                finished_processes++;
            }
            addToQueue(*next_process);
        } 
        else 
        {
            current_time++;
        }
    }
}

void MLFQ::addToQueue(Process process) 
{
    queues[process.priority].push(process);
}

Process* MLFQ::selectNextProcess() 
{
    for (int i = 0; i < num_queues; ++i) 
    {
        if (!queues[i].empty()) 
        {
            Process* next_process = &queues[i].front();
            queues[i].pop();
            return next_process;
        }
    }
    return nullptr;
}

void MLFQ::updateProcessState(Process* process) 
{
    if (process->state == READY) 
    {
        if (process->priority < num_queues - 1) 
        {
            process->priority++;
        }
    }
    process->state = RUNNING;
}

void MLFQ::printResults(int current_time) 
{
    std::cout << "MLFQ Scheduler Results:" << std::endl;

    for (int i = 0; i < num_queues; ++i) 
    {
        if (!queues[i].empty()) 
        { // 检查队列是否为空
            std::cout << "Queue " << i << ":" << std::endl;
            std::queue<Process> queue = queues[i];
            while (!queue.empty()) 
            {
                Process process = queue.front();
                queue.pop();
                // 计算周转时间
                process.turnaroundTime = current_time - process.arrivalTime;
                // 计算响应时间
                if (process.responseTime == 0) 
                {
                    process.responseTime = process.waitingTime;
                }
                std::cout << "Process ID: " << process.processId << std::endl;
                std::cout << "Waiting Time: " << process.waitingTime << std::endl;
                std::cout << "Turnaround Time: " << process.turnaroundTime << std::endl;
                std::cout << "Response Time: " << process.responseTime << std::endl;
                std::cout << std::endl;
            }
        }
    }
}
