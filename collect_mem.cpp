#include<fstream>
#include<string>
#include<cstdint>
#include<cstdio>
#include"collect.hpp"
#include <cinttypes>
bool collect_mem(MemStat&st){
    std::ifstream ifs("/proc/meminfo");
    if(!ifs.is_open()){
        return false;
    }
    std::string line;
    while (std::getline(ifs,line))
    {
        uint64_t val;
        if (sscanf(line.c_str(),"MemTotal:%" SCNu64 "%*s",&val)==1)
        {
            st.mem_total=val;
        }else if (sscanf(line.c_str(),"MemFree:%" SCNu64 "%*s",&val)==1)
        {
            st.mem_free=val;
        }else if (sscanf(line.c_str(),"MemAvailable:%" SCNu64 "%*s",&val)==1)
        {
            st.mem_available=val;
        }else if (sscanf(line.c_str(),"Buffers:%" SCNu64 "%*s",&val)==1)
        {
            st.buffers=val;
        }else if (sscanf(line.c_str(),"Cached:%" SCNu64 "%*s",&val)==1)
        {
            st.cached=val;
        }
        
    }
    return true;
}