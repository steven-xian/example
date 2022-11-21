# CMakeList.txt: lib_add 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


# set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/cmake)


link_directories("../out")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

# 将源代码添加到此项目的可执行文件。
add_executable (test_add "test_add.cpp" "test_add.h") 
target_link_libraries(test_add lib_add)
 
# TODO: 如有需要，请添加测试并安装目标。
