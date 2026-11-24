#include"monitor_queue.hpp"
#include"collect.hpp"
#include<iostream>
#include<cstdio>
#include"safe_print.hpp"
void mem_calc_thread(){
    while (running)
    {
        MemStat mem;
        {
            std::unique_lock<std::mutex> lp(mtx_mem);
            cv_mem.wait(lp,[&]{return !mem_queue.empty()||!running;});
            if (!running && mem_queue.empty())
            {
                safe_print("队列空了，消费者退出");
                return;
            }
            mem = mem_queue.front();
            mem_queue.pop();
        }
        double Memory_usage = 100.0*(mem.mem_total-mem.mem_available)/mem.mem_total;
        safe_print("内存占用率: {:.2f}%\n", Memory_usage);
    }
    
}