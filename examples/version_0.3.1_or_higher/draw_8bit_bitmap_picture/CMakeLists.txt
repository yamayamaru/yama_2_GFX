cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(draw_8bit_bitmap_picture.cpp_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
      draw_8bit_bitmap_picture   draw_8bit_bitmap_picture.cpp
                                 yama_2_GFX.cpp
)

target_link_libraries(  draw_8bit_bitmap_picture
                         pico_stdlib
                         hardware_spi
)

pico_enable_stdio_usb(draw_8bit_bitmap_picture 1)
pico_enable_stdio_uart(draw_8bit_bitmap_picture 0)

pico_add_extra_outputs(draw_8bit_bitmap_picture)

