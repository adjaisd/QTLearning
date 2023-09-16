cmake_minimum_required(VERSION 3.24)
project(QTLearning C CXX)
set(CMAKE_C_STANDARD   23 CACHE INTERNAL "CMAKE_C_STANDARD")
set(CMAKE_CXX_STANDARD 23 CACHE INTERNAL "CMAKE_CXX_STANDARD")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH "C:/software/QT/6.5.2/mingw_64")
#set(CMAKE_PREFIX_PATH "/opt/Qt/6.2.4/gcc_64/lib/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(modules/demo1) # WinServer
add_subdirectory(modules/demo2) # 0911
add_subdirectory(modules/demo3) # 0911
add_subdirectory(modules/demo4) # 0912
add_subdirectory(modules/demo5) # 0912
add_subdirectory(modules/demo6) # 0912
add_subdirectory(modules/demo7) # 0913
add_subdirectory(modules/demo8) # 0913
add_subdirectory(modules/demo9) # 0913
add_subdirectory(modules/demo10) # 0914
add_subdirectory(modules/demo11) # 0914
add_subdirectory(modules/demo12) # 0914
add_subdirectory(modules/demo13) # 0915
add_subdirectory(modules/demo14) # 0915
add_subdirectory(modules/demo15) # 0916
add_subdirectory(modules/demo16) # 0916
add_subdirectory(modules/demo17) # 0916
add_subdirectory(modules/demo18) # 0916