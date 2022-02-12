/*

    Raspberry Pi Pico pico-sdk LCD ILI9341 font print Library (C++)
    yama_2_GFX demo program draw_color_palette_table_GFXcanvas8.cpp
                                      https://twitter.com/yama23238

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "yama_2_GFX.h"


#define MOSI 19
#define SCK  18
#define CS   17
#define MISO 16

#define RST  22
#define DC   20

#define SPI_PORT  spi0



yama_2_GFX_ILI9341 tft = yama_2_GFX_ILI9341(SPI_PORT, DC, RST, CS);

GFXcanvas8 canvas01 = GFXcanvas8(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);


extern uint16_t default_palette_data[]; 
extern uint16_t web216_palette_data[];

void loop01(void);

int main() {

  stdio_init_all();

  spi_init(SPI_PORT, 10000000);
  gpio_set_function(MISO, GPIO_FUNC_SPI);
  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);
  gpio_pull_up(MISO);
  gpio_pull_up(SCK);
  gpio_pull_up(MOSI);
  spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST

  tft.tft_setup();
  tft.fillScreen(ILI9341_BLACK);
  printf("ILI9341 Test!\r\n"); 
  tft.setRotation(0);

  canvas01.fillScreen(DEFAULT_PALETTE_BLACK);
  canvas01.setRotation(0);

  while (1) {
    loop01();
  }
  return 0;
}

void loop01(void) {

    canvas01.fillScreen(DEFAULT_PALETTE_BLACK);
    for (int j = 0; j < 16; j++) {
        for (int i = 0; i < 16; i++) {
            canvas01.fillRect(i * 15, j * 15, 15, 15, j * 16 + i);    
        }
    }

    // パレットの設定はdrawPalette256Bitmapで使われるので
    // GFXcanvas8ではなくてyama_2_GFX_ILI9341側で設定する
    tft.setDefaultPalette256();
    tft.drawPalette256Bitmap(0, 0, canvas01.getBuffer(), tft.width(), tft.height());
    sleep_ms(20000);



    canvas01.fillScreen(WEB216_PALETTE_BLACK);
    for (int j = 0; j < 16; j++) {
        for (int i = 0; i < 16; i++) {
            canvas01.fillRect(i * 15, j * 15, 15, 15, j * 16 + i);    
        }
    }

    // パレットの設定はdrawPalette256Bitmapで使われるので
    // GFXcanvas8ではなくてyama_2_GFX_ILI9341側で設定する
    tft.setWeb216Palette256();
    tft.drawPalette256Bitmap(0, 0, canvas01.getBuffer(), tft.width(), tft.height());
    sleep_ms(20000);
}
