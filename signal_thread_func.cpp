#include"monitor_queue.hpp"
#include"collect.hpp"
#include"safe_print.hpp"
#include<signal.h>
void signal_thread_func()
{
    sigset_t sig_mask;
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGINT);
    sigaddset(&sig_mask, SIGTERM);
    
    struct timespec timeout;
    timeout.tv_sec = 1;  // 1 seconds timeout
    timeout.tv_nsec = 0;

        while (!g_stop) {
        // 如果 1 秒内没信号，返回 EAGAIN；如果有信号，返回 0
        int ret = sigtimedwait(&sig_mask, nullptr, &timeout);
        
        if (ret == SIGINT) {
            safe_print("收到 SIGINT(Ctrl+C)\n");
            g_stop = true;
        } else if (ret == SIGTERM) {
            safe_print("收到 SIGTERM\n");
            g_stop = true;
        } else if (ret == -1 && errno != EAGAIN && errno != EINTR) {
            // 发生错误
            break;
        }
    }

    g_stop = true;
    {
        std::lock_guard<std::mutex> lk(mtx_cpu);
        cv_cpu.notify_all();
    }
    {
        std::lock_guard<std::mutex> lk(mtx_mem);
        cv_mem.notify_all();
    }
}