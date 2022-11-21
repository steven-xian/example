# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("lib_add")


# 设置静态库的输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/lib")

# 设置动态库的输出目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/dll")

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out")

# 包含子项目。
add_subdirectory ("lib_add")
add_subdirectory ("test_dll")
