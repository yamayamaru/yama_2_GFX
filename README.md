# yama_2_GFX

yama_2_GFXはRaspberry Pi Picoの公式C/C++開発ツールのpico-sdk用のグラフィックスライブラリです。  
C++で書かれています。  
yama_2_GFXはILI9341搭載のLCD専用です。  
文字表示するには別途print_GFX_ILI9341も使ってください。  
<https://github.com/yamayamaru/print_GFX_ILI9341>  
  
また、SSD1306に対応したyama_2_GFX_SSD1306も作りました。  
<https://github.com/yamayamaru/yama_2_GFX_SSD1306>  

  
yama_2_GFXはAdafruit-GFX-LibraryとHumblesoft_ILI9341を元に作られています  
    <https://github.com/adafruit/Adafruit-GFX-Library>  
    <https://github.com/h-nari/Humblesoft_ILI9341>  
  

yama_2_GFXにdrawPalette256Bitmapを追加しました。  
これにより、GFXcanvas8で描画しておき、  
GFXcanvas8のバッファの内容を更新したいタイミングで  
yama_2_GFX_ILI9341のdrawPalette256Bitmapを使ってLCDに描画することで  
8bitカラーのフレームバッファのように使うことができます。  
また、GFXCanvas16やILI9341LCDに8bitカラーのbitmapを表示することもできます。  
今まではGFXcanvas16で同様のことができていたのですが、  
GFXcanvas8を使うことで使用するRAM容量を減らすことができます。  
  
drawPalette256BitmapではILI9341のLCDやGFXcanvas16に描画する際に  
256色のパレットで色を変換することが可能です。  
  
GFXcanvas8に8bitのbitmap画像を描画したい場合はdrawGrayscaleBitmapを使ってください。


## 変更履歴
* 0.3.1 2022/02/12  yama_2_GFX_ILI9341でdrawBitmapとdrawRGBBitmapで一部のパラメータで呼び出せなかった不具合を修正  
yama_2_GFXのdrawBitmapでbitmap_maskパラメータを使えるように追加  
yama_2_GFXにdrawPalette256Bitmapを追加して8bitカラーのbitmap描画やGFXcanvas8のバッファデータを描画可能にしました  
yama_2_GFXにdrawPalette256Bitmapで使う256色パレット機能を追加  
* 0.3    2022/01/28 マクロの一部が他と競合する不具合があったため名前を変更  
* 0.2    2021/11/12 pastebin.comにアップ drawBitmap、drawGrayscaleBitmap、drawRGBBitmap不具合を修正  
* 0.1    2021/11/11 pastebin.comに初版アップ  
