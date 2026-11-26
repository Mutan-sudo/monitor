#include"monitor_queue.hpp"
#include"collect.hpp"
#include<iomanip>
#include<iostream>
#include<thread>
//std::atomic<bool>running{true};
void collect_cpu_thread(){
    while (!g_stop)
    {
        CpuStat st;
        if(collect_cpu(st)){
            std::lock_guard<std::mutex>lk(mtx_cpu);
            cpu_queue.push(st);
        
            cv_cpu.notify_one();
        }
            std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
     }
        

   
    
