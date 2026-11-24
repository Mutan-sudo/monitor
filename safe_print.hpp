#ifndef SAFE_PRINT_HPP
#define SAFE_PRINT_HPP

#include<fmt/format.h>
#include<fmt/os.h>
#include<mutex>
inline std::mutex print_mtx;
template<typename...Args>
void safe_print(fmt::format_string<Args...>fmt_str,Args&&...args){
    std::lock_guard<std::mutex> lo(print_mtx);
    fmt::print(fmt_str,std::forward<Args>(args)...);
}
#endif