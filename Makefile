# 1. 配置项目：编译器、可执行文件名、源文件
CC = g++
TARGET = grade_system  # 生成的可执行文件名称（可自定义）
SRCS = *.cpp  # 自动匹配所有.cpp文件（适配你当前的多文件项目）
CFLAGS = -Wall  # 开启编译警告，便于调试

# 2. 默认编译规则：执行make时自动编译
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET)

# 3. clean清理规则：执行make clean时删除编译产物
clean:
	rm -rf $(TARGET) a.out  # 删除自定义可执行文件和默认的a.out
