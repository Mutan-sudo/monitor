#include<iostream>
#include"collect.hpp"
#include"monitor_queue.hpp"
#include<thread>
#include"safe_print.hpp"
int main(){
    std::thread t_collect_cpu(collect_cpu_thread);
    std::thread t_calc_cpu(cpu_calc_thread);
    std::thread t_collect_mem(collect_mem_thread);
    std::thread t_calc_mem(mem_calc_thread);
    safe_print("按回车结束程序\n");
    std::cin.get();
    
    running =false;
    {std::unique_lock<std::mutex> lk(mtx_cpu);
    cv_cpu.notify_all();}
    {std::unique_lock<std::mutex> lp(mtx_mem);
    cv_mem.notify_all();}
    t_collect_cpu.join();
    t_calc_cpu.join();
    t_collect_mem.join();
    t_calc_mem.join();
    

    safe_print("程序执行完毕");
    return 0;
}
