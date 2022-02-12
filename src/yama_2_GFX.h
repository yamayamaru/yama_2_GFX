// yama_2_GFX.h
// Version : 0.3.1
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
 
#define WEB216_PALETTE_BLACK      0xd7     ///< 0x0000    0,   0,   0
#define WEB216_PALETTE_NAVY       0xda     ///< 0x0010    0,   0, 128
#define WEB216_PALETTE_DARKGREEN  0xdc     ///< 0x0400    0, 128,   0
#define WEB216_PALETTE_DARKCYAN   0xdb     ///< 0x0410    0, 125, 123
#define WEB216_PALETTE_MAROON     0xdf     ///< 0x8000  128,   0,   0
#define WEB216_PALETTE_PURPLE     0xde     ///< 0x8010  128,   0, 128
#define WEB216_PALETTE_OLIVE      0xdd     ///< 0x8400  128, 128,   0
#define WEB216_PALETTE_LIGHTGREY  0xd9     ///< 0xc618  198, 195, 198
#define WEB216_PALETTE_DARKGREY   0xd8     ///< 0x8410  128, 128, 128
#define WEB216_PALETTE_BLUE       0xd2     ///< 0x001f    0,   0, 255
#define WEB216_PALETTE_GREEN      0xd2     ///< 0x07e0    0, 255,   0
#define WEB216_PALETTE_CYAN       0xb4     ///< 0x07ff    0, 255, 255
#define WEB216_PALETTE_RED        0x23     ///< 0xf800  255,   0,   0
#define WEB216_PALETTE_MAGENTA    0x1e     ///< 0xf81f  255,   0, 255
#define WEB216_PALETTE_YELLOW     0x05     ///< 0xffe0  255, 255,   0
#define WEB216_PALETTE_WHITE      0x00     ///< 0xffff  255, 255, 255
#define WEB216_PALETTE_ORANGE     0x11     ///< 0xfcc0  255, 152,   0
#define WEB216_PALETTE_GREENYELLOW  0x4c   ///< 0x9fe6  152, 255,  48
#define WEB216_PALETTE_PINK       0x13     ///< 0xfb59  255, 104, 200


#define DEFAULT_PALETTE_BLACK      0x00     ///< 0x0000    0,   0,   0
#define DEFAULT_PALETTE_NAVY       0x04     ///< 0x0010    0,   0, 128
#define DEFAULT_PALETTE_DARKGREEN  0x02     ///< 0x0400    0, 128,   0
#define DEFAULT_PALETTE_DARKCYAN   0x06     ///< 0x0410    0, 125, 123
#define DEFAULT_PALETTE_MAROON     0x01     ///< 0x8000  128,   0,   0
#define DEFAULT_PALETTE_PURPLE     0x05     ///< 0x8010  128,   0, 128
#define DEFAULT_PALETTE_OLIVE      0x03     ///< 0x8400  128, 128,   0
#define DEFAULT_PALETTE_LIGHTGREY  0x07     ///< 0xc618  198, 195, 198
#define DEFAULT_PALETTE_DARKGREY   0xf8     ///< 0x8410  128, 128, 128
#define DEFAULT_PALETTE_BLUE       0xfc     ///< 0x001f    0,   0, 255
#define DEFAULT_PALETTE_GREEN      0xfa     ///< 0x07e0    0, 255,   0
#define DEFAULT_PALETTE_CYAN       0xfe     ///< 0x07ff    0, 255, 255
#define DEFAULT_PALETTE_RED        0xf9     ///< 0xf800  255,   0,   0
#define DEFAULT_PALETTE_MAGENTA    0xfd     ///< 0xf81f  255,   0, 255
#define DEFAULT_PALETTE_YELLOW     0xfb     ///< 0xffe0  255, 255,   0
#define DEFAULT_PALETTE_WHITE      0xff     ///< 0xffff  255, 255, 255
#define DEFAULT_PALETTE_ORANGE     0xc6     ///< 0xfce0  255, 156,   0
#define DEFAULT_PALETTE_GREENYELLOW  0x8d   ///< 0xafea  168, 255,  80
#define DEFAULT_PALETTE_PINK       0xc0     ///< 0xfaf5  255,  92, 168
 
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


    inline int bit_test(const uint8_t *data, int n) {
        return (data[n >> 3] >> (7 - (n & 7))) & 1;
    }


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


    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap01, const uint8_t *bitmap_mask01,
                                  int16_t width, int16_t height,
                                  uint16_t fg, uint16_t bg);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap01, uint8_t *bitmap_mask01,
                                  int16_t width, int16_t height,
                                  uint16_t fg, uint16_t bg);


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


    void drawPalette256Bitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                                     int16_t width, int16_t height);
    void drawPalette256Bitmap(int16_t x, int16_t y, 
                                     const uint8_t bitmap[], const uint8_t bitmap_mask[],
                                     int16_t width, int16_t height);
    void setDefaultPalette256();
    void setWeb216Palette256();
    void setPalette256(uint8_t palette_num, uint16_t color);
    uint16_t getPalette256(uint8_t palette_num);


    uint16_t width(void);
    uint16_t height(void);
 


protected:
    static const int palette_number = 256;
    uint16_t palette256_table[palette_number];
    static const uint16_t default_palette256_data[];
    static const uint16_t web216_palette256_data[];
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




    void drawRGBBitmap(int16_t x, int16_t y,
                           const uint16_t bitmap[], const uint8_t bitmap_mask[],
                           int16_t w, int16_t h);
    void drawBitmap(int16_t x, int16_t y,const uint8_t bitmap[],
                            int16_t w, int16_t h,
                        uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap01, const uint8_t *bitmap_mask01,
                                  int16_t width, int16_t height,
                                  uint16_t fg, uint16_t bg);
    void drawGrayscaleBitmap(int16_t x, int16_t y,
                       const uint8_t bitmap[],
                       int16_t w, int16_t h, bool red_flag=true, bool green_flag=true,
                       bool blue_flag=true, bool invert=false);
    void drawGrayscaleBitmap(int16_t x, int16_t y,
                       const uint8_t bitmap[], const uint8_t bitmap_mask[],
                       int16_t w, int16_t h, bool red_flag=true, bool green_flag=true,
                       bool blue_flag=true, bool invert=false);
    void drawPalette256Bitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                                     int16_t w, int16_t h);
    void drawPalette256Bitmap(int16_t x, int16_t y, 
                                     const uint8_t bitmap[], const uint8_t bitmap_mask[],
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


  void drawGrayscaleBitmap(int16_t x, int16_t y,
                       const uint8_t bitmap[],
                       int16_t w, int16_t h, bool red_flag=true, bool green_flag=true,
                       bool blue_flag=true, bool invert=false);
  void drawGrayscaleBitmap(int16_t x, int16_t y,
                       const uint8_t bitmap[], const uint8_t bitmap_mask[],
                       int16_t w, int16_t h, bool red_flag=true, bool green_flag=true,
                       bool blue_flag=true, bool invert=false);


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
 