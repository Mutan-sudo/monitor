#ifndef MONITOR_QUEUE_HPP
#define MONITOR_QUEUE_HPP

#include "collect.hpp"
#include<queue>
#include<mutex>
#include<condition_variable>
#include<atomic>

inline std::queue<CpuStat>cpu_queue;
inline std::mutex mtx_cpu;
inline std::condition_variable cv_cpu;
inline std::queue<MemStat>mem_queue;
inline std::mutex mtx_mem;
inline std::condition_variable cv_mem;
inline std::atomic<bool>running{true};
void collect_cpu_thread();
void collect_mem_thread();
void cpu_calc_thread();
void mem_calc_thread();

#endif
