#include"monitor_queue.hpp"
#include"collect.hpp"
#include<iostream>
#include<cstdio>
#include"safe_print.hpp"
void cpu_calc_thread(){
    CpuStat prev;
    bool has_prev=false;
    
    while (!g_stop)
    {
        CpuStat curr;
        {
            std::unique_lock<std::mutex>lk(mtx_cpu);
            cv_cpu.wait(lk,[&]{return g_stop||!cpu_queue.empty();});
            if (g_stop && cpu_queue.empty())
            {
                safe_print("队列空了，消费者退出\n");
                return;
            }
            curr = cpu_queue.front();
            cpu_queue.pop();
        
        }
        if (!has_prev)
        {
            prev=curr;
            has_prev=true;
        }else{
        
        uint64_t total_prev = prev.user + prev.nice + prev.system + prev.idle
                                 + prev.iowait + prev.irq + prev.softirq;
        uint64_t total_curr = curr.user + curr.nice + curr.system + curr.idle
                                 + curr.iowait + curr.irq + curr.softirq;

        uint64_t delta_total = total_curr - total_prev;
        uint64_t delta_idle  = curr.idle - prev.idle;
        double cpu_usage = 0.0;
        if (delta_total > 0)
        {
            cpu_usage = 100.0 * (delta_total - delta_idle) / delta_total;
        }

        safe_print("CPU使用率: {:.2f}%\n", cpu_usage);

        prev=curr;
        
    }
    }
}