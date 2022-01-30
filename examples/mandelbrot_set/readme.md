yama_2_GFX.h、yama_2_GFX.cpp、mandelbrot_set.cpp、CMakeLists.txtを同じフォルダに置き
pico-sdkでビルドしてください。  
  
  
CMakeLists.txtでprintfの出力がUART0になっています。  
USBシリアルに出力したい場合はCMakeLists.txtの最後の方の3行を下記のように変更してください。  
  
    pico_enable_stdio_usb(mandelbrot_set 1)
    pico_enable_stdio_uart(mandelbrot_set 0)
    
    pico_add_extra_outputs(mandelbrot_set)
