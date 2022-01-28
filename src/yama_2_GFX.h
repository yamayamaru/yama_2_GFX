// yama_2_GFX.h
// Version : 0.3
//    
//    Copyright (c) 2012 Adafruit Industries.
//    Released under the BSD License
//    https://github.com/adafruit/Adafruit-GFX-Library/blob/master/license.txt
//
//    The yama_2_GFX_ILI9341 class is:
//    Copyright (c) 2016 Hiroshi Narimatsu
//    Released under the MIT License
//    https://github.com/h-nari/Humblesoft_ILI9341/blob/master/LICENSE
//
//
// Raspberry Pi Pico pico-sdk LCD ILI9341 Graphics Library (C++)
//                                 https://twitter.com/yama23238
//
//      これらのプログラムの使用に当たってはご自分の責任において使用してください
//      これらのプログラムで発生したいかなる損害、データの消失、金銭等の責任は一切負いません。
//

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware/spi.h"
#include "hardware/gpio.h"
 
 
#ifndef _YAMA_2_GFX_H
#define _YAMA_2_GFX_H
 
 
#define yama_2_GFX_min(a, b) (((a) < (b)) ? (a) : (b))
#define yama_2_GFX_swap_int16_t(a, b)                                                    \
{                                                                              \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
}
#define yama_2_GFX_abs(a)    ((a >= 0) ? a : (-(a)))
 
class yama_2_GFX {
protected:
    int16_t  WIDTH;
    int16_t  HEIGHT;
    int16_t  _width;
    int16_t  _height;
    uint8_t  rotation = 0;
public:
    yama_2_GFX(int16_t w, int16_t h);
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void startWrite(void);
    virtual void writePixel(int16_t x, int16_t y, uint16_t color);
    virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                             uint16_t color);
    virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         uint16_t color);
    virtual void endWrite(void);
    virtual void setRotation(uint8_t r);
    virtual void invertDisplay(bool i);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);
    virtual void fillScreen(uint16_t color);
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                        uint16_t color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r,
                                  uint16_t color);
    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                        uint8_t cornername, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r,
                                  uint16_t color);
    void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                        uint8_t corners, int16_t delta,
                                        uint16_t color);
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                     int16_t r, uint16_t color);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                     int16_t r, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                    int16_t x2, int16_t y2, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                    int16_t x2, int16_t y2, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                                  int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                                  int16_t w, int16_t h, uint16_t color,
                                  uint16_t bg);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                                  int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                                  int16_t h, uint16_t color, uint16_t bg);
    void drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                                   int16_t w, int16_t h, uint16_t color);
    void drawGrayscaleBitmap(int16_t x, int16_t y,
                                           const uint8_t bitmap[], int16_t w,
                                           int16_t h);
    void drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,
                                           int16_t w, int16_t h);
    void drawGrayscaleBitmap(int16_t x, int16_t y,
                                           const uint8_t bitmap[],
                                           const uint8_t mask[], int16_t w,
                                           int16_t h);
    void drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,
                                           uint8_t *mask, int16_t w, int16_t h);
    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                                     int16_t w, int16_t h);
    void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
                                     int16_t w, int16_t h);
    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                                     const uint8_t mask[], int16_t w, int16_t h);
    void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
                                     uint8_t *mask, int16_t w, int16_t h);
    uint16_t width(void);
    uint16_t height(void);
 
 
};
 
#endif // _YAMA_2_GFX_H
 
 
 
 
 
#ifndef _YAMA_2_GFX_ILI9341_H
#define _YAMA_2_GFX_ILI9341_H
 
 
#define PIXEL_BUF_SIZE  64      // 64byte
 
#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320
 
#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09
 
#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13
 
#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0D
#define ILI9341_RDSELFDIAG  0x0F
 
#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29
 
#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E
 
#define ILI9341_PTLAR   0x30
#define ILI9341_MADCTL  0x36
#define ILI9341_PIXFMT  0x3A
 
#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6
 
#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7
 
#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD
 
#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1
 
 
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04
 
// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198
 
#define ILI9341_DEFAULT_PIN_MISO 16
#define ILI9341_DEFAULT_PIN_CS   17
#define ILI9341_DEFAULT_PIN_SCK  18
#define ILI9341_DEFAULT_PIN_MOSI 19
 
#define ILI9341_DEFAULT_PIN_DC   20
#define ILI9341_DEFAULT_PIN_RST  22
 
#define ILI9341_DEFAULT_SPI_PORT spi0
 
class yama_2_GFX_ILI9341 : public yama_2_GFX {
private:
    spi_inst_t   *_spi;
    int32_t    _tft_dc;
    int32_t    _tft_rst;
    int32_t    _tft_cs;
    uint16_t    m_pbi;
    uint8_t     m_pixelBuf[PIXEL_BUF_SIZE];
 
public:
    yama_2_GFX_ILI9341(spi_inst_t *inst = ILI9341_DEFAULT_SPI_PORT, int32_t dc=ILI9341_DEFAULT_PIN_DC, 
                  int32_t rst = ILI9341_DEFAULT_PIN_RST,
                  int32_t cs = ILI9341_DEFAULT_PIN_CS);
 
    inline void pixel_write(uint16_t color);
    inline void pixel_write(uint8_t hi, uint8_t lo);
    inline void gpio_rst_on(void);
    inline void gpio_rst_off(void);
    inline void gpio_dc_on(void);
    inline void gpio_dc_off(void);
    inline void gpio_cs_on(void);
    inline void gpio_cs_off(void);
    void writedata(uint8_t byte);
    void writecommand(uint8_t byte);
    void spi_write(uint8_t byte);
    void spi_begin();
    void spi_end();
    void tft_setup();
    void setRotation(uint8_t r);
    void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void writedata1(uint8_t *buf, size_t count);
    void pixel_flush(void);
    void fill_color(uint16_t color, uint32_t len);
    void drawPixel(int16_t x, int16_t y, uint16_t color)  override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void invertDisplay(bool i);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
    void drawBitmap(int16_t x, int16_t y,const uint8_t bitmap[],
                            int16_t w, int16_t h,
                        uint16_t color, uint16_t bg);
    void drawRGBBitmap(int16_t x, int16_t y,
                           const uint16_t bitmap[],
                           int16_t w, int16_t h);
    uint16_t color(int colr, int colg, int colb);
    uint16_t color565(int colr, int colg, int colb);
    void sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes);
    uint8_t readcommand8(uint8_t commandByte, uint8_t index = 0);
    uint8_t spiRead(void);
};
 
 
#endif // _YAMA_2_GFX_ILI9341_H
 
 
 
#ifndef _GFXCANVAS_H
#define _GFXCANVAS_H
 
/// A GFX 1-bit canvas context for graphics
class GFXcanvas1 : public yama_2_GFX {
public:
  GFXcanvas1(uint16_t w, uint16_t h);
  ~GFXcanvas1(void);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  bool getPixel(int16_t x, int16_t y) const;
  /**********************************************************************/
  /*!
    @brief    Get a pointer to the internal buffer memory
    @returns  A pointer to the allocated buffer
  */
  /**********************************************************************/
  uint8_t *getBuffer(void) const { return buffer; }
 
protected:
  bool getRawPixel(int16_t x, int16_t y) const;
 
private:
  uint8_t *buffer;
 
};
 
/// A GFX 8-bit canvas context for graphics
class GFXcanvas8 : public yama_2_GFX {
public:
  GFXcanvas8(uint16_t w, uint16_t h);
  ~GFXcanvas8(void);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  uint8_t getPixel(int16_t x, int16_t y) const;
  /**********************************************************************/
  /*!
   @brief    Get a pointer to the internal buffer memory
   @returns  A pointer to the allocated buffer
  */
  /**********************************************************************/
  uint8_t *getBuffer(void) const { return buffer; }
 
protected:
  uint8_t getRawPixel(int16_t x, int16_t y) const;
 
private:
  uint8_t *buffer;
};
 
///  A GFX 16-bit canvas context for graphics
class GFXcanvas16 : public yama_2_GFX {
public:
  GFXcanvas16(uint16_t w, uint16_t h);
  ~GFXcanvas16(void);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void fillScreen(uint16_t color);
  void byteSwap(void);
  uint16_t getPixel(int16_t x, int16_t y) const;
  /**********************************************************************/
  /*!
    @brief    Get a pointer to the internal buffer memory
    @returns  A pointer to the allocated buffer
  */
  /**********************************************************************/
  uint16_t *getBuffer(void) const { return buffer; }
 
protected:
  uint16_t getRawPixel(int16_t x, int16_t y) const;
 
private:
  uint16_t *buffer;
};
 
#endif // _GFXCANVAS_H
 