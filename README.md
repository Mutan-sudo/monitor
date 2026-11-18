# monitor
Linux 多线程资源监控工具（C++）
采用生产者-消费者模型，采集CPU使用率，后续扩展内存采集。

## 功能
- 独立采集线程：读取系统CPU采样
- 独立计算线程：计算CPU利用率
- 线程安全队列 + std::condition_variable 条件变量
- 原子变量控制线程退出

## 编译运行
```bash
make
./monitor
