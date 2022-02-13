yama_2_GFX.h、yama_2_GFX.cpp、random_raspberry.cpp、CMakeLists.txtを同じフォルダに置き pico-sdkでビルドしてください。  
  
プログラム中のbitmap_mask01は32x32のピクセルのうち、透明色を0、色の付いたものを1にしたビットデータです。  
左上のピクセルから順番にビットで表現したものです。  
ビットの並びはMSBから始まります。  
配列の長さは32 * 32 / 8 = 128バイトになります。  
drawRGBBitmap、drawBitmap、drawGrayscaleBitmap、drawPalette256Bitmapで扱うマスクデータはこのフォーマットになります。  
  
プログラム中のbitmap01は32x32のピクセルデータです。  
1ピクセルは16bitのRGB565で表現されています。  
RGB565は16bitでMSBから赤5bit、緑6bit、青5bitの数値で表現したものです。  
この2バイトのピクセルデータをリトルエンディアン(下位バイトが先、上位バイトが先)で  
横32、縦32を左上から右方向に順番にピクセルを並べただけの配列です。　
配列の長さは2 * 32 * 32 = 2048バイトになります。  
drawRGBBitmapで扱うbitmapデータはこのフォーマットになります。  
  
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
