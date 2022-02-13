yama_2_GFX.h、yama_2_GFX.cpp、random_raspberry_64px_GFXcanvas1.cpp、CMakeLists.txtを同じフォルダに置き pico-sdkでビルドしてください。  
  
プログラム中のbitmap_mask01は64x64のピクセルのうち、透明色を0、色の付いたものを1にしたビットデータです。  
左上のピクセルから順番にビットで表現したものです。  
ビットの並びはMSBから始まります。  
8ピクセル分のデータで1バイトになります。  
配列の長さは64 * 64 / 8 = 512バイトになります。  
drawRGBBitmap、drawBitmap、drawGrayscaleBitmap、drawPalette256Bitmapで扱うマスクデータはこのフォーマットになります。  
  
プログラム中のbitmap01は点灯が1、消灯が0の1bitで表現したものです。  
横64、縦64を左上のピクセルから順番に単純にビットを並べた配列になります。  
ビットの並びはMSBが先でLSBが後方になります。  
8ピクセルで1バイトになります。  
bitmap01の配列の長さは64 * 64 / 8 = 512バイトになります。  
drawBitmapで扱うbitmap画像はこのフォーマットになります。  
  
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
