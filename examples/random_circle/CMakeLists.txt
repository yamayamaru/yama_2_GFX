cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(random_circle_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       random_circle random_circle.cpp 
                       yama_2_GFX.cpp
)

target_link_libraries(random_circle
                       pico_stdlib
                       hardware_spi
)

pico_enable_stdio_usb(random_circle 1)
pico_enable_stdio_uart(random_circle 0)

pico_add_extra_outputs(random_circle)

