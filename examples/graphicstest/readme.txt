yama_2_GFX.h、yama_2_GFX.cpp、graphicstest.cpp、CMakeLists.txtを同じフォルダに置き
pico-sdkでビルドしてください。

ソースコードに書かれてるMOSI、SCK、CS、MISOやRST、DCの番号はGPIOの番号です
https://github.com/yamayamaru/yama_2_GFX/blob/main/img/raspberrypipicopinout.jpg
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
#define SPI_PORT  spi0  


ビルド方法はコマンドラインの場合
Linuxでは下記のようになります。

pico-sdkの場所を環境変数PICO_SDK_PATHに登録します
ここでは仮に~/pico/pico-sdkとします。
export PICO_SDK_PATH=~/pico/pico-sdk


cd graphicstest
mkdir build
cd build

cmake ..
make

これでコンパイルが正常に行われるとbuildディレクトリの中に
graphicstest.uf2
が作成されます。



Windowsでは下記のようになります。

まず、Developer Command Prompt for VS2019を起動します
次にpico-sdkの場所を環境変数PICO_SDK_PATHに登録します
ここでは仮にc:\/pico/pico-sdkとします。
setx PICO_SDK_PATH "c:\pico\pico-sdk"

cd graphicstest
mkdir build
cd build

cmake -G "NMake Makefiles" ..
nmake

これでコンパイルが正常に行われるとbuildディレクトリの中に
graphicstest.uf2
が作成されます。

ビルド環境の構築方法はgetting_started_with_pico.pdfに記載されています。
https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
Capter 2にLinux、Capter 8.1にMacOS、8.2にWindowsでのインストール方法が記載されています

Youtubeなどにもビルド環境のインストール方法を解説してる動画があるので参照してみてください
