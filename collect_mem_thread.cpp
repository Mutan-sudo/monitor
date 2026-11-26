#include"monitor_queue.hpp"
#include"collect.hpp"
#include<thread>

void collect_mem_thread(){
    
    while (!g_stop)
    {
        MemStat st;
        
            if (collect_mem(st))
            {{
                std::lock_guard<std::mutex> lp(mtx_mem);
                mem_queue.push(st);
            
              cv_mem.notify_one();  
            }
            }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));   
            

                
    }
    
}