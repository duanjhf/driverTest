#头文件路径
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${NETLINK_LIB_USER_PATH}/include
)

#查找./目录下的所有源文件，赋值给SRC_FILES
aux_source_directory(. SRC_FILES)

#生成共享库
add_library(libnetlinkUser SHARED ${SRC_FILES})
