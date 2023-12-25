cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(helloworld_nc C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(helloworld_nc
main.S
)

pico_enable_stdio_uart(helloworld_nc 1) # Output mode
pico_enable_stdio_usb(helloworld_nc 0)

pico_add_extra_outputs(helloworld_nc)

target_link_libraries(helloworld_nc pico_stdlib)