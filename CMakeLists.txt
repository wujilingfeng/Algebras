PROJECT(Algebras)
cmake_minimum_required(VERSION 2.8)
add_compile_options(-Wall -g -lstdc++)
#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -no-pie)
#生成可执行程序
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -std=c99)
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
add_subdirectory(./src)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdpart/cstructures/include)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/temp_libs)
aux_source_directory(${PROJECT_SOURCE_DIR}/Demo mysrc)
#add_subdirectory(${PROJECT_SOURCE_DIR}/src/tool)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/temp_libs)
link_libraries(m dl -lgmp  )
#add_subdirectory(/src)
add_executable(main ${mysrc})
target_link_libraries(main -Wl,--start-group algebras cstructures -Wl,--end-group)
