cmake_minimum_required(VERSION 3.12)
 
# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
 
project(graphicstest_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
 
# Initialize the SDK
pico_sdk_init()
 
add_executable(
       graphicstest graphicstest.cpp 
                       yama_2_GFX.cpp
)
 
target_link_libraries(graphicstest
                       pico_stdlib
                       hardware_spi
)
 
pico_enable_stdio_usb(graphicstest 1)
pico_enable_stdio_uart(graphicstest 0)
 
pico_add_extra_outputs(graphicstest)
 