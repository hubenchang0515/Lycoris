cmake_minimum_required(VERSION 3.13)
project(Lycoris)

# 读取源文件列表
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)

# 构建库文件
add_library(${PROJECT_NAME} ${SOURCES})

# 读取头文件列表
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/src/*.hpp" "${CMAKE_SOURCE_DIR}/src/*.h")

# 设置要安装的头文件
set_target_properties(${PROJECT_NAME}
                        PROPERTIES
                        PUBLIC_HEADER
                        "${HEADERS}"
)

# 安装
install(TARGETS
        ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Lycoris
)
