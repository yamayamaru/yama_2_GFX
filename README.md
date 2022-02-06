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
  
## 変更履歴
* 0.3  2022/01/28 マクロの一部が他と競合する不具合があったため名前を変更  
* 0.2  2021/11/12 pastebin.comにアップ drawBitmap、drawGrayscaleBitmap、drawRGBBitmap不具合を修正  
* 0.1  2021/11/11 pastebin.comに初版アップ  
