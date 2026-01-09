# 1. 定义编译器（C++编译器用g++）
CXX = g++

# 2. 定义编译选项（指定C++标准，如C++11，去除警告可加 -w）
CXXFLAGS = -std=c++11 -Wall

# 3. 定义可执行文件名（自定义，如grade_manage、main，后续运行用./该名称）
TARGET = grade_manage

# 4. 定义所有源码文件（.cpp文件，若有多个，用空格分隔，如 main.cpp system.cpp student.cpp）
# 若当前目录下所有.cpp都需要编译，可简化为：SRCS = *.cpp
SRCS = *.cpp

# 5. 定义编译规则：生成可执行文件
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# 6. 定义清理规则（执行 make clean 可删除可执行文件，清理编译产物）
clean:
	rm -f $(TARGET)
