#!/bin/bash
# 开发助手脚本（适配 grade-management-system 项目，可执行文件：grade_manage）

case "$1" in
    "test")
        echo "🧪 运行查询功能测试..."
        ./grade_manage
        ;;
    "build")
        echo "🔨 编译项目..."
        if [ ! -f "Makefile" ]; then
            echo "❌ 未找到 Makefile，无法编译"
            exit 1
        fi
        make clean 2>/dev/null
        make
        if [ $? -eq 0 ]; then
            echo "✅ 编译成功，生成可执行文件：grade_manage"
        else
            echo "❌ 编译失败，请查看终端错误提示"
        fi
        ;;
    "sync")
        echo "🔄 同步到GitHub..."
        if [ -z "$2" ]; then
            echo "❌ 请传入提交信息，用法：./dev_helper.sh sync \"你的提交备注\""
            exit 1
        fi
        if [ -z "$(git status --porcelain)" ]; then
            echo "ℹ️  无文件变更，无需提交"
            exit 0
        fi
        git add .
        git commit -m "$2"
        git push origin master
        echo "✅ 已同步到 GitHub master 分支"
        ;;
    "stats")
        echo "📊 项目统计信息（C++相关文件）:"
        echo "----------------------------------------"
        cpp_files=$(find . -type f \( -name '*.cpp' -o -name '*.h' \) | wc -l)
        total_lines=$(find . -type f \( -name '*.cpp' -o -name '*.h' \) | xargs wc -l 2>/dev/null | tail -1 | awk '{print $1}')
        search_lines=$(grep -r -i "query\|search\|查找" --include="*.cpp" --include="*.h" . 2>/dev/null | wc -l)
        echo "C++ 文件总数: $cpp_files 个"
        echo "总代码行数: $total_lines 行"
        echo "查询功能相关代码行: $search_lines 行"
        echo "----------------------------------------"
        ;;
    *)
        echo "📋 用法: ./dev_helper.sh [命令] [可选参数]"
        echo "支持命令:"
        echo "  test    - 运行项目（测试查询功能）"
        echo "  build   - 清理旧产物并编译项目"
        echo "  sync    - 一键同步到GitHub（需传入提交信息）"
        echo "  stats   - 统计项目C++文件和代码行信息"
        echo "示例:"
        echo "  ./dev_helper.sh sync \"修复Search函数输入逻辑，优化查询功能\""
        ;;
esac
