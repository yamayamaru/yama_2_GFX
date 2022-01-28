yama_2_GFX.h、yama_2_GFX.cpp、graphicstest.cpp、CMakeLists.txtを同じフォルダに置き
pico-sdkでビルドしてください。

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
