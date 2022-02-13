yama_2_GFX.h、yama_2_GFX.cpp、draw_16bit_rgb565_bitmap_picture_GFXcanvas16.cpp、CMakeLists.txtを同じフォルダに置き pico-sdkでビルドしてください。  
  
RGB565は1ピクセルを赤を5bit、緑を6bit、青を5ビットの16bit(2バイト)の数値で表現したものです。  
16bitのMSBから赤5bit、緑6bit、青5bitの並びになります。  

プログラム中のbitmap01はこの1ピクセル2バイトのデータを  
リトルエンディアン(下位バイトが先、上位バイトが後)で  
横320ピクセル、縦240ピクセルを横方向に順番に単に並べただけの配列です。  
配列の長さは320 * 240 = 153600になります。  
bitmap02も同様です。  
drawRGBBitmapで描画するbitmapのフォーマットはこのフォーマットになります。
  
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
