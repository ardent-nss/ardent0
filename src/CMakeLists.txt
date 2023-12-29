cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(a0_bl C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico_w) # Ardent 0 is based on the Pico W.

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(a0_bl
  main.c
)

pico_enable_stdio_uart(a0_bl 1) # Output mode
pico_enable_stdio_usb(a0_bl 0)

pico_add_extra_outputs(a0_bl)

target_link_libraries(a0_bl pico_stdlib pico_multicore pico_cyw43_arch_none hardware_gpio hardware_uart)