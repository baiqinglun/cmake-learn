cmake_minimum_required(VERSION 3.10)

# 设置c++标准
# set(CMAKE_CXX_STANDARD 11)
# 设置输出文件存放目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 设置静态文件存放目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 设置项目名称
project(demo VERSION 1.0 LANGUAGES CXX)
message(${PROJECT_NAME})
message(${PROJECT_SOURCE_DIR})
message(${demo_SOURCE_DIR})

# 开关
option(DATA_ENABLE "output version" ON)
if(DATA_ENABLE)
    set(DATA "2023.0.1")
endif()

# 输入文件替换成输出文件
configure_file(config.h.in config.h)

# 添加子目录
add_subdirectory(calc)
add_subdirectory(excel)

# 可执行文件
add_executable(demo main.cpp)

# 链接静态文件
target_link_libraries(demo PUBLIC addition)
target_link_libraries(demo PUBLIC sub)
target_link_libraries(demo PUBLIC excel)

# 将包含目录到目标
target_include_directories(demo PUBLIC
                            ${PROJECT_BINARY_DIR}
                            ${PROJECT_SOURCE_DIR}/calc
                            ${PROJECT_SOURCE_DIR}/excel
                            )

# 安装exe文件
install(TARGETS demo DESTINATION bin)
# 安装外部头文件
# 安装外部静态文件
# 安装外部动态文件
