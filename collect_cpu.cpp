#include "collect.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <inttypes.h>

bool collect_cpu(CpuStat& st)
{
    int fd = open("/proc/stat", O_RDONLY);
    if(fd < 0)
    {
        perror("open /proc/stat fail");
        return false;
    }

    char buf[256] = {0};
    ssize_t n = read(fd, buf, sizeof(buf)-1);
    if(n < 0)
    {
        perror("read /proc/stat fail");
        close(fd); // ❗出错也要记得close，防止文件泄漏！
        return false;
    }
    buf[n] = '\0';

// 注意！字符串要拼接，直接写宏，不能放引号里面！
int ret = sscanf(buf, "cpu %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64,
                 &st.user,
                 &st.nice,
                 &st.system,
                 &st.idle,
                 &st.iowait,
                 &st.irq,
                 &st.softirq);

    close(fd);

    if(ret != 7)
    {
        std::cout << "sscanf 处理CPU数据失败" << std::endl;
        return false;
    }
    return true;
}



