cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(draw_8bit_bitmap_picture_GFXcanvas16.cpp_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
      draw_8bit_bitmap_picture_GFXcanvas16   draw_8bit_bitmap_picture_GFXcanvas16.cpp
                                yama_2_GFX.cpp
)

target_link_libraries(  draw_8bit_bitmap_picture_GFXcanvas16
                         pico_stdlib
                         hardware_spi
)

pico_enable_stdio_usb(draw_8bit_bitmap_picture_GFXcanvas16 1)
pico_enable_stdio_uart(draw_8bit_bitmap_picture_GFXcanvas16 0)

pico_add_extra_outputs(draw_8bit_bitmap_picture_GFXcanvas16)

