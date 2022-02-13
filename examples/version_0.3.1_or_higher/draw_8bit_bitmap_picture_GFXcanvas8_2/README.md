yama_2_GFX.h、yama_2_GFX.cpp、draw_8bit_bitmap_picture_GFXcanvas8_2.cpp、CMakeLists.txtを同じフォルダに置き pico-sdkでビルドしてください。  
  
プログラム中のbitmap01は1ピクセル8bit(1バイト)を  
横240、縦320を横方向に単純に並べただけの配列です。  
1ピクセル1バイトなので1ピクセルあたり256色の表現可能です。  
bitmap01の配列の長さは240 * 320 = 76800バイトになります。  
bitmap02、bitmap03、bitmap04、bitmap05も同様になります。  
drawPalette256BitmapやdrawGrayscaleBitmapで扱うbitmap画像はこのフォーマットになります。  
  
パレットデータはRGB565で表現した色データの256色分の単純な配列です。  
RGB565は16bit(2バイト)のMSBから赤5bit、緑6bit、青5bitの数値で表現したものです。  
プログラム中のpalette_data01はこのRGB565の16bitの数値を  
256個単純に並べただけの配列です。  
配列の長さは256でサイズは2 * 256 = 512バイトになります。  
yama_2_GFXで扱うパレットの色はこのRGB565の16bitの数値になります。  
基本的にILI9341で扱う色表現はこのRGB565になります  
    
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
