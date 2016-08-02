#cmake最低版本要求
cmake_minimum_required(VERSION 2.8)
#项目名称
project(driverTest)

#debug编译模式
set(CMAKE_BUILD_TYPE DEBUG)
#编译选项
set(CMAKE_C_FLAGS "-g -Wall")

#可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#设置库路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#源码路径定义
set(NETLINK_LIB_KERNEL_PATH ${PROJECT_SOURCE_DIR}/netlinkKernel)
set(NETLINK_LIB_USER_PATH ${PROJECT_SOURCE_DIR}/netlinkUser)

#添加子目录
#add_subdirectory(driverInstance)
add_subdirectory(netlinkUser)
#add_subdirectory(netlinkKernel)
