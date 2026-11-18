#include<iostream>
#include"collect.hpp"
#include"monitor_queue.hpp"
#include<thread>
int main(){
    std::thread t_collect_cpu(collect_cpu_thread);
    std::thread t_calc_cpu(cpu_calc_thread);
    std::thread t_collect_mem(collect_mem_thread);
    std::thread t_calc_mem(mem_calc_thread);
    std::cout<<"按回车结束程序\n"<<std::endl;
    std::cin.get();
    
    running =false;
    cv_cpu.notify_all();
    cv_mem.notify_all();
    t_collect_cpu.join();
    t_calc_cpu.join();
    t_collect_mem.join();
    t_calc_mem.join();
    

    std::cout<<"程序执行完毕"<<std::endl;
    return 0;
}
