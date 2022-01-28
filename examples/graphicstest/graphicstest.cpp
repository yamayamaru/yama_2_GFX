//    
//    Copyright (c) 2012 Adafruit Industries.
//    Released under the BSD License
//    https://github.com/adafruit/Adafruit-GFX-Library/blob/master/license.txt
//

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

unsigned long long testFillScreen();
unsigned long long testLines(uint16_t color);
unsigned long long testFastLines(uint16_t color1, uint16_t color2);
unsigned long long testRects(uint16_t color);
unsigned long long testFilledRects(uint16_t color1, uint16_t color2);
unsigned long long testFilledCircles(uint8_t radius, uint16_t color);
unsigned long long testCircles(uint8_t radius, uint16_t color);
unsigned long long testTriangles();
unsigned long long testFilledTriangles();
unsigned long long testRoundRects();
unsigned long long testFilledRoundRects();

void loop(void);

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

  while (1) {
    loop();
    sleep_ms(5000);
  }
  return 0;
}

void loop(void) {
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  printf("Display Power Mode: 0x"); printf("%x\r\n", x);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  printf("MADCTL Mode: 0x"); printf("%x\r\n", x);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  printf("Pixel Format: 0x"); printf("%x\r\n", x);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  printf("Image Format: 0x"); printf("%x\r\n", x);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  printf("Self Diagnostic: 0x"); printf("%x\r\n", x); 
  
  printf("Benchmark                Time (microseconds)\r\n");
  sleep_ms(10);
  printf("Screen fill              ");
  printf("%lld\r\n", testFillScreen());
  sleep_ms(500);

  printf("Lines                    ");
  printf("%lld\r\n", testLines(ILI9341_CYAN));
  sleep_ms(500);

  printf("Horiz/Vert Lines         ");
  printf("%lld\r\n", testFastLines(ILI9341_RED, ILI9341_BLUE));
  sleep_ms(500);

  printf("Rectangles (outline)     ");
  printf("%lld\r\n", testRects(ILI9341_GREEN));
  sleep_ms(500);

  printf("Rectangles (filled)      ");
  printf("%lld\r\n", testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
  sleep_ms(500);

  printf("Circles (filled)         ");
  printf("%lld\r\n", testFilledCircles(10, ILI9341_MAGENTA));

  printf("Circles (outline)        ");
  printf("%lld\r\n", testCircles(10, ILI9341_WHITE));
  sleep_ms(500);

  printf("Triangles (outline)      ");
  printf("%lld\r\n", testTriangles());
  sleep_ms(500);

  printf("Triangles (filled)       ");
  printf("%lld\r\n", testFilledTriangles());
  sleep_ms(500);

  printf("Rounded rects (outline)  ");
  printf("%lld\r\n", testRoundRects());
  sleep_ms(500);

  printf("Rounded rects (filled)   ");
  printf("%lld\r\n", testFilledRoundRects());
  sleep_ms(500);

  printf("Done!\r\n");
}

void  yield(){};

unsigned long long testFillScreen() {
  unsigned long long start = time_us_64();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return time_us_64() - start;
}

unsigned long long testLines(uint16_t color) {
  unsigned long long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  yield();
  
  x1 = y1 = 0;
  y2    = h - 1;
  start = time_us_64();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = time_us_64() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = time_us_64();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += time_us_64() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = time_us_64();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += time_us_64() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = time_us_64();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return time_us_64() - start;
}

unsigned long long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = time_us_64();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return time_us_64() - start;
}

unsigned long long testRects(uint16_t color) {
  unsigned long long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = yama_2_GFX_min(tft.width(), tft.height());
  start = time_us_64();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return time_us_64() - start;
}

unsigned long long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = yama_2_GFX_min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = time_us_64();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += time_us_64() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = time_us_64();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return time_us_64() - start;
}

unsigned long long testCircles(uint8_t radius, uint16_t color) {
  unsigned long long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = time_us_64();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return time_us_64() - start;
}

unsigned long long testTriangles() {
  unsigned long long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = yama_2_GFX_min(cx, cy);
  start = time_us_64();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return time_us_64() - start;
}

unsigned long long testFilledTriangles() {
  unsigned long long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = time_us_64();
  for(i=yama_2_GFX_min(cx,cy); i>10; i-=5) {
    start = time_us_64();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i*10, i*10));
    t += time_us_64() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i*10, i*10, 0));
    yield();
  }

  return t;
}

unsigned long long testRoundRects() {
  unsigned long long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = yama_2_GFX_min(tft.width(), tft.height());
  start = time_us_64();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return time_us_64() - start;
}

unsigned long long testFilledRoundRects() {
  unsigned long long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = time_us_64();
  for(i=yama_2_GFX_min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
    yield();
  }

  return time_us_64() - start;
}
