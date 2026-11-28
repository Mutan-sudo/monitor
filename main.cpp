#include<iostream>
#include"collect.hpp"
#include"monitor_queue.hpp"
#include<thread>
#include"safe_print.hpp"
#include<signal.h>
#include<error.h>
int main(){
    sigset_t sig_mask_all;
    sigemptyset(&sig_mask_all);
    sigaddset(&sig_mask_all,SIGINT);
    sigaddset(&sig_mask_all,SIGTERM);
    pthread_sigmask(SIG_BLOCK,&sig_mask_all,nullptr);
    
    std::thread t_signal(signal_thread_func);
    std::thread t_collect_cpu(collect_cpu_thread);
    std::thread t_calc_cpu(cpu_calc_thread);
    std::thread t_collect_mem(collect_mem_thread);
    std::thread t_calc_mem(mem_calc_thread);
    std::thread t_input(input_thread_func);
    

    t_collect_cpu.join();
    t_calc_cpu.join();
    t_collect_mem.join();
    t_calc_mem.join();
    t_signal.join();
    t_input.detach();
    

    safe_print("程序执行完毕\n");
    return 0;
}
