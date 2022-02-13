yama_2_GFX.h、yama_2_GFX.cpp、draw_color_palette_table_GFXcanvas8.cpp、CMakeLists.txtを同じフォルダに置き pico-sdkでビルドしてください。  
  
![pico pinout](https://github.com/yamayamaru/yama_2_GFX/blob/main/img/raspberrypipicopinout.jpg)  
ソースコードに書かれてるMOSI、SCK、CS、MISOやRST、DCの番号はGPIOの番号です  
上記画像で緑で書かれてる番号になります。  
ソースコードの例では実際のピン番号は下記のようになります。  
  
    #define MOSI 19    // ピン番号25
    #define SCK  18    // ピン番号24
    #define CS   17    // ピン番号22
    #define MISO 16    // ピン番号21
    #define RST  22    // ピン番号29
    #define DC   20    // ピン番号26
  
画像からGP19、GP18、GP17、GP16のSPIはSPI0なので  
ソースコードの例ではSPIのポート番号は下記のようにspi0を指定してます  
`#define SPI_PORT  spi0`
