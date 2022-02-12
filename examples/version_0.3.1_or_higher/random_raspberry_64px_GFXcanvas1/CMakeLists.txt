cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(random_raspberry_64px_GFXcanvas1_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       random_raspberry_64px_GFXcanvas1  random_raspberry_64px_GFXcanvas1.cpp 
                                         yama_2_GFX.cpp       # yama_2_GFXを使うときはここに追加する
)

target_link_libraries(random_raspberry_64px_GFXcanvas1
                       pico_stdlib
                       hardware_spi
)

pico_enable_stdio_usb(random_raspberry_64px_GFXcanvas1 1)
pico_enable_stdio_uart(random_raspberry_64px_GFXcanvas1 0)

pico_add_extra_outputs(random_raspberry_64px_GFXcanvas1)

