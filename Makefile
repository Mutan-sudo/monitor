CXX = g++
CXXFLAGS = -Wall -g -std=c++20 -pthread 

TARGET = main
# ✅暂时拿掉collect_mem.cpp！等写完再加回来
SRCS = main.cpp \
       collect_cpu_thread.cpp \
       cpu_calc_thread.cpp \
       collect_cpu.cpp\
	   collect_mem_thread.cpp\
	   mem_calc_thread.cpp\
	   collect_mem.cpp\
	   signal_thread_func.cpp\
	   input_thread_func.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lfmt

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean