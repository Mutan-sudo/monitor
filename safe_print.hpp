#ifndef SAFE_PRINT_HPP
#define SAFE_PRINT_HPP

#include<mutex>
#include<iostream>
inline std::mutex print_mtx;
template<typename...Args>
void safe_print(const char*fmt,Args&&...args){
    std::lock_guard<std::mutex> lo(print_mtx);
    printf(fmt,std::forward<Args>(args)...);
}
#endif