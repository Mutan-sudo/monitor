#ifndef COLLECT_HPP
#define COLLECT_HPP

#include<cstdint>

struct CpuStat{
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
};
struct MemStat{
    uint64_t mem_total;
    uint64_t mem_free;
    uint64_t mem_available;
    uint64_t buffers;
    uint64_t cached;
};
bool collect_cpu(CpuStat&st);

bool collect_mem(MemStat&st);


#endif