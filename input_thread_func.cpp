#include"monitor_queue.hpp"
#include<iostream>
#include"safe_print.hpp"

void input_thread_func(){
    std::string line;
    while (!g_stop)
    {
        if(!std::getline(std::cin,line))
        {
            std::cin.clear();
            continue;
        }
        if (line.empty() || line=="q" || line=="Q")
        {
            safe_print("收到退出信号，程序即将退出\n");
            g_stop=true;
            {
                std::lock_guard<std::mutex> lk(mtx_cpu);
                cv_cpu.notify_all();
            }
            {
                std::lock_guard<std::mutex> lk(mtx_mem);
                cv_mem.notify_all();
            }
            break;
        }
        if (g_stop)
        {
            {
                std::lock_guard<std::mutex> lk(mtx_cpu);
                cv_cpu.notify_all();
            }
            {
                std::lock_guard<std::mutex> lk(mtx_mem);
                cv_mem.notify_all();
            }
        }
        
    }
    
}