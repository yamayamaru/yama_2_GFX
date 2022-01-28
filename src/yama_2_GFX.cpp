// yama_2_GFX.cpp
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
#include "yama_2_GFX.h"
 
yama_2_GFX::yama_2_GFX(int16_t w, int16_t h){
    WIDTH = w;
    HEIGHT = h;
    _width = WIDTH;
    _height = HEIGHT;
    rotation = 0;
}
 
void yama_2_GFX::writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                             uint16_t color) {
  int16_t steep = yama_2_GFX_abs(y1 - y0) > yama_2_GFX_abs(x1 - x0);
  if (steep) {
    yama_2_GFX_swap_int16_t(x0, y0);
    yama_2_GFX_swap_int16_t(x1, y1);
  }
 
  if (x0 > x1) {
    yama_2_GFX_swap_int16_t(x0, x1);
    yama_2_GFX_swap_int16_t(y0, y1);
  }
 
  int16_t dx, dy;
  dx = x1 - x0;
  dy = yama_2_GFX_abs(y1 - y0);
 
  int16_t err = dx / 2;
  int16_t ystep;
 
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }
 
  for (; x0 <= x1; x0++) {
    if (steep) {
      writePixel(y0, x0, color);
    } else {
      writePixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
 
void yama_2_GFX::startWrite() {}
 
void yama_2_GFX::writePixel(int16_t x, int16_t y, uint16_t color) {
  drawPixel(x, y, color);
}
 
void yama_2_GFX::writeFastVLine(int16_t x, int16_t y, int16_t h,
                                  uint16_t color) {
  // Overwrite in subclasses if startWrite is defined!
  // Can be just writeLine(x, y, x, y+h-1, color);
  // or writeFillRect(x, y, 1, h, color);
  drawFastVLine(x, y, h, color);
}
 
void yama_2_GFX::writeFastHLine(int16_t x, int16_t y, int16_t w,
                                  uint16_t color) {
  // Overwrite in subclasses if startWrite is defined!
  // Example: writeLine(x, y, x+w-1, y, color);
  // or writeFillRect(x, y, w, 1, color);
  drawFastHLine(x, y, w, color);
}
 
void yama_2_GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 uint16_t color) {
  // Overwrite in subclasses if desired!
  fillRect(x, y, w, h, color);
}
 
void yama_2_GFX::endWrite() {}
 
void yama_2_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                 uint16_t color) {
  startWrite();
  writeLine(x, y, x, y + h - 1, color);
  endWrite();
}
 
void yama_2_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                 uint16_t color) {
  startWrite();
  writeLine(x, y, x + w - 1, y, color);
  endWrite();
}
 
void yama_2_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color) {
  startWrite();
  for (int16_t i = x; i < x + w; i++) {
    writeFastVLine(i, y, h, color);
  }
  endWrite();
}
 
void yama_2_GFX::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}
 
void yama_2_GFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                            uint16_t color) {
  // Update in subclasses if desired!
  if (x0 == x1) {
    if (y0 > y1)
      yama_2_GFX_swap_int16_t(y0, y1);
    drawFastVLine(x0, y0, y1 - y0 + 1, color);
  } else if (y0 == y1) {
    if (x0 > x1)
      yama_2_GFX_swap_int16_t(x0, x1);
    drawFastHLine(x0, y0, x1 - x0 + 1, color);
  } else {
    startWrite();
    writeLine(x0, y0, x1, y1, color);
    endWrite();
  }
}
 
void yama_2_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r,
                              uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
 
  startWrite();
  writePixel(x0, y0 + r, color);
  writePixel(x0, y0 - r, color);
  writePixel(x0 + r, y0, color);
  writePixel(x0 - r, y0, color);
 
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
 
    writePixel(x0 + x, y0 + y, color);
    writePixel(x0 - x, y0 + y, color);
    writePixel(x0 + x, y0 - y, color);
    writePixel(x0 - x, y0 - y, color);
    writePixel(x0 + y, y0 + x, color);
    writePixel(x0 - y, y0 + x, color);
    writePixel(x0 + y, y0 - x, color);
    writePixel(x0 - y, y0 - x, color);
  }
  endWrite();
}
 
void yama_2_GFX::drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                    uint8_t cornername, uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
 
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (cornername & 0x4) {
      writePixel(x0 + x, y0 + y, color);
      writePixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      writePixel(x0 + x, y0 - y, color);
      writePixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      writePixel(x0 - y, y0 + x, color);
      writePixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      writePixel(x0 - y, y0 - x, color);
      writePixel(x0 - x, y0 - y, color);
    }
  }
}
 
void yama_2_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r,
                              uint16_t color) {
  startWrite();
  writeFastVLine(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
  endWrite();
}
 
void yama_2_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                    uint8_t corners, int16_t delta,
                                    uint16_t color) {
 
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  int16_t px = x;
  int16_t py = y;
 
  delta++; // Avoid some +1's in the loop
 
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    // These checks avoid double-drawing certain lines, important
    // for the SSD1306 library which has an INVERT drawing mode.
    if (x < (y + 1)) {
      if (corners & 1)
        writeFastVLine(x0 + x, y0 - y, 2 * y + delta, color);
      if (corners & 2)
        writeFastVLine(x0 - x, y0 - y, 2 * y + delta, color);
    }
    if (y != py) {
      if (corners & 1)
        writeFastVLine(x0 + py, y0 - px, 2 * px + delta, color);
      if (corners & 2)
        writeFastVLine(x0 - py, y0 - px, 2 * px + delta, color);
      py = y;
    }
    px = x;
  }
}
 
void yama_2_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color) {
  startWrite();
  writeFastHLine(x, y, w, color);
  writeFastHLine(x, y + h - 1, w, color);
  writeFastVLine(x, y, h, color);
  writeFastVLine(x + w - 1, y, h, color);
  endWrite();
}
 
void yama_2_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t r, uint16_t color) {
  int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
  if (r > max_radius)
    r = max_radius;
  // smarter version
  startWrite();
  writeFastHLine(x + r, y, w - 2 * r, color);         // Top
  writeFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
  writeFastVLine(x, y + r, h - 2 * r, color);         // Left
  writeFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
  // draw four corners
  drawCircleHelper(x + r, y + r, r, 1, color);
  drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
  drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
  drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
  endWrite();
}
 
void yama_2_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t r, uint16_t color) {
  int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
  if (r > max_radius)
    r = max_radius;
  // smarter version
  startWrite();
  writeFillRect(x + r, y, w - 2 * r, h, color);
  // draw four corners
  fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
  endWrite();
}
 
void yama_2_GFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
 
void yama_2_GFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color) {
 
  int16_t a, b, y, last;
 
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    yama_2_GFX_swap_int16_t(y0, y1);
    yama_2_GFX_swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    yama_2_GFX_swap_int16_t(y2, y1);
    yama_2_GFX_swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    yama_2_GFX_swap_int16_t(y0, y1);
    yama_2_GFX_swap_int16_t(x0, x1);
  }
 
  startWrite();
  if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if (x1 < a)
      a = x1;
    else if (x1 > b)
      b = x1;
    if (x2 < a)
      a = x2;
    else if (x2 > b)
      b = x2;
    writeFastHLine(a, y0, b - a + 1, color);
    endWrite();
    return;
  }
 
  int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
          dx12 = x2 - x1, dy12 = y2 - y1;
  int32_t sa = 0, sb = 0;
 
  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if (y1 == y2)
    last = y1; // Include y1 scanline
  else
    last = y1 - 1; // Skip it
 
  for (y = y0; y <= last; y++) {
    a = x0 + sa / dy01;
    b = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      yama_2_GFX_swap_int16_t(a, b);
    writeFastHLine(a, y, b - a + 1, color);
  }
 
  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = (int32_t)dx12 * (y - y1);
  sb = (int32_t)dx02 * (y - y0);
  for (; y <= y2; y++) {
    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      yama_2_GFX_swap_int16_t(a, b);
    writeFastHLine(a, y, b - a + 1, color);
  }
  endWrite();
}
 
void yama_2_GFX::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                              int16_t w, int16_t h, uint16_t color) {
 
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
 
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = *((const uint8_t *)(&bitmap[j * byteWidth + i / 8]));
      if (byte & 0x80)
        writePixel(x + i, y, color);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                              int16_t w, int16_t h, uint16_t color,
                              uint16_t bg) {
 
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
 
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = *((const uint8_t *)(&bitmap[j * byteWidth + i / 8]));
      writePixel(x + i, y, (byte & 0x80) ? color : bg);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                              int16_t h, uint16_t color) {
 
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
 
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = bitmap[j * byteWidth + i / 8];
      if (byte & 0x80)
        writePixel(x + i, y, color);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                              int16_t h, uint16_t color, uint16_t bg) {
 
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
 
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = bitmap[j * byteWidth + i / 8];
      writePixel(x + i, y, (byte & 0x80) ? color : bg);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                               int16_t w, int16_t h, uint16_t color) {
 
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
 
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte >>= 1;
      else
        byte = *((const uint8_t *)(&bitmap[j * byteWidth + i / 8]));
      // Nearly identical to drawBitmap(), only the bit order
      // is reversed here (left-to-right = LSB to MSB):
      if (byte & 0x01)
        writePixel(x + i, y, color);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
                                       const uint8_t bitmap[], int16_t w,
                                       int16_t h) {
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      writePixel(x + i, y, (uint8_t)*((const uint8_t *)(&bitmap[j * w + i])));
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,
                                       int16_t w, int16_t h) {
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      writePixel(x + i, y, bitmap[j * w + i]);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawGrayscaleBitmap(int16_t x, int16_t y,
                                       const uint8_t bitmap[],
                                       const uint8_t mask[], int16_t w,
                                       int16_t h) {
  int16_t bw = (w + 7) / 8; // Bitmask scanline pad = whole byte
  uint8_t byte = 0;
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = *((const uint8_t *)(&mask[j * bw + i / 8]));
      if (byte & 0x80) {
        writePixel(x + i, y, (uint8_t)*((const uint8_t *)(&bitmap[j * w + i])));
      }
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,
                                       uint8_t *mask, int16_t w, int16_t h) {
  int16_t bw = (w + 7) / 8; // Bitmask scanline pad = whole byte
  uint8_t byte = 0;
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = mask[j * bw + i / 8];
      if (byte & 0x80) {
        writePixel(x + i, y, bitmap[j * w + i]);
      }
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                                 int16_t w, int16_t h) {
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      writePixel(x + i, y, *((const uint16_t *)(&bitmap[j * w + i])));
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
                                 int16_t w, int16_t h) {
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      writePixel(x + i, y, bitmap[j * w + i]);
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                                 const uint8_t mask[], int16_t w, int16_t h) {
  int16_t bw = (w + 7) / 8; // Bitmask scanline pad = whole byte
  uint8_t byte = 0;
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = *((const uint8_t *)(&mask[j * bw + i / 8]));
      if (byte & 0x80) {
        writePixel(x + i, y, *((const uint16_t *)(&bitmap[j * w + i])));
      }
    }
  }
  endWrite();
}
 
void yama_2_GFX::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
                                 uint8_t *mask, int16_t w, int16_t h) {
  int16_t bw = (w + 7) / 8; // Bitmask scanline pad = whole byte
  uint8_t byte = 0;
  startWrite();
  for (int16_t j = 0; j < h; j++, y++) {
    for (int16_t i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else
        byte = mask[j * bw + i / 8];
      if (byte & 0x80) {
        writePixel(x + i, y, bitmap[j * w + i]);
      }
    }
  }
  endWrite();
}
 
void yama_2_GFX::setRotation(uint8_t x) {
  rotation = (x & 3);
  switch (rotation) {
  case 0:
  case 2:
    _width = WIDTH;
    _height = HEIGHT;
    break;
  case 1:
  case 3:
    _width = HEIGHT;
    _height = WIDTH;
    break;
  }
}
 
void yama_2_GFX::invertDisplay(bool i) {
}
 
uint16_t yama_2_GFX::width(void){
    return _width;
}
 
uint16_t yama_2_GFX::height(void){
    return _height;
}
 
 
 
yama_2_GFX_ILI9341::yama_2_GFX_ILI9341(spi_inst_t *inst, int32_t dc, int32_t rst, int32_t cs) :
  yama_2_GFX((int16_t)ILI9341_TFTWIDTH, (int16_t)ILI9341_TFTHEIGHT) {
    _spi = inst;
    _tft_dc = dc;
    _tft_rst = rst;
    _tft_cs = cs;
}
 
inline void yama_2_GFX_ILI9341::gpio_rst_on(void){
    gpio_put(_tft_rst, 0);
}
inline void yama_2_GFX_ILI9341::gpio_rst_off(void){
    gpio_put(_tft_rst, 1);
}
inline void yama_2_GFX_ILI9341::gpio_dc_on(void){
    gpio_put(_tft_dc, 0);
}
inline void yama_2_GFX_ILI9341::gpio_dc_off(void){
    gpio_put(_tft_dc, 1);
}
inline void yama_2_GFX_ILI9341::gpio_cs_on(void){
    gpio_put(_tft_cs, 0);
}
inline void yama_2_GFX_ILI9341::gpio_cs_off(void){
    gpio_put(_tft_cs, 1);
}
 
inline void yama_2_GFX_ILI9341::writedata(uint8_t byte){
    spi_write_blocking(_spi, &byte, 1);
}
 
void yama_2_GFX_ILI9341::writecommand(uint8_t byte) {
    gpio_dc_on();
    writedata(byte);
    gpio_dc_off();
}
 
inline void yama_2_GFX_ILI9341::spi_write(uint8_t byte){
    writedata(byte);
}
 
void yama_2_GFX_ILI9341::spi_begin() {
    asm volatile("nop \n nop \n nop");
    gpio_cs_on();
    asm volatile("nop \n nop \n nop");
}
 
void yama_2_GFX_ILI9341::spi_end() {
    asm volatile("nop \n nop \n nop");
    gpio_cs_off();
    asm volatile("nop \n nop \n nop");
}
 
void yama_2_GFX_ILI9341::tft_setup(){
    gpio_init(_tft_dc);
    gpio_init(_tft_cs);
    gpio_init(_tft_rst);
    gpio_set_dir(_tft_dc, GPIO_OUT);
    gpio_set_dir(_tft_cs, GPIO_OUT);
    gpio_set_dir(_tft_rst, GPIO_OUT);
    gpio_pull_up(_tft_cs);
 
    gpio_rst_off();
    sleep_ms(200);
    gpio_rst_on();
    sleep_ms(200);
    gpio_rst_off();
    sleep_ms(200);
 
  spi_begin();
 
  writecommand(0xEF);
  writedata(0x03);
  writedata(0x80);
  writedata(0x02);
 
  writecommand(0xCF);  
  writedata(0x00); 
  writedata(0XC1); 
  writedata(0X30); 
 
  writecommand(0xED);  
  writedata(0x64); 
  writedata(0x03); 
  writedata(0X12); 
  writedata(0X81); 
 
  writecommand(0xE8);  
  writedata(0x85); 
  writedata(0x00); 
  writedata(0x78); 
 
  writecommand(0xCB);  
  writedata(0x39); 
  writedata(0x2C); 
  writedata(0x00); 
  writedata(0x34); 
  writedata(0x02); 
 
  writecommand(0xF7);  
  writedata(0x20); 
 
  writecommand(0xEA);  
  writedata(0x00); 
  writedata(0x00); 
 
  writecommand(ILI9341_PWCTR1);    //Power control 
  writedata(0x23);   //VRH[5:0] 
 
  writecommand(ILI9341_PWCTR2);    //Power control 
  writedata(0x10);   //SAP[2:0];BT[3:0] 
 
  writecommand(ILI9341_VMCTR1);    //VCM control 
  writedata(0x3e); //¶O±E¶Eμ÷?U
  writedata(0x28); 
  
  writecommand(ILI9341_VMCTR2);    //VCM control2 
  writedata(0x86);  //--
 
  writecommand(ILI9341_MADCTL);    // Memory Access Control 
  writedata(0x48);
 
  writecommand(ILI9341_PIXFMT);    
  writedata(0x55); 
  
  writecommand(ILI9341_FRMCTR1);    
  writedata(0x00);  
  writedata(0x18); 
 
  writecommand(ILI9341_DFUNCTR);    // Display Function Control 
  writedata(0x08); 
  writedata(0x82);
  writedata(0x27);  
 
  writecommand(0xF2);    // 3Gamma Function Disable 
  writedata(0x00); 
 
  writecommand(ILI9341_GAMMASET);    //Gamma curve selected 
  writedata(0x01); 
 
  writecommand(ILI9341_GMCTRP1);    //Set Gamma 
  writedata(0x0F); 
  writedata(0x31); 
  writedata(0x2B); 
  writedata(0x0C); 
  writedata(0x0E); 
  writedata(0x08); 
  writedata(0x4E); 
  writedata(0xF1); 
  writedata(0x37); 
  writedata(0x07); 
  writedata(0x10); 
  writedata(0x03); 
  writedata(0x0E); 
  writedata(0x09); 
  writedata(0x00); 
  
  writecommand(ILI9341_GMCTRN1);    //Set Gamma 
  writedata(0x00); 
  writedata(0x0E); 
  writedata(0x14); 
  writedata(0x03); 
  writedata(0x11); 
  writedata(0x07); 
  writedata(0x31); 
  writedata(0xC1); 
  writedata(0x48); 
  writedata(0x08); 
  writedata(0x0F); 
  writedata(0x0C); 
  writedata(0x31); 
  writedata(0x36); 
  writedata(0x0F); 
 
  writecommand(ILI9341_SLPOUT);    //Exit Sleep 
  spi_end();
  sleep_ms(120);        
  spi_begin();
  writecommand(ILI9341_DISPON);    //Display on 
  spi_end();
}
 
void yama_2_GFX_ILI9341::setRotation(uint8_t r)
{
  spi_begin();
  writecommand(ILI9341_MADCTL);
  rotation = r % 4; 
  switch (rotation) {
   case 0:
     writedata(MADCTL_MX | MADCTL_BGR);
     _width  = ILI9341_TFTWIDTH;
     _height = ILI9341_TFTHEIGHT;
     break;
   case 1:
     writedata(MADCTL_MV | MADCTL_BGR);
     _width  = ILI9341_TFTHEIGHT;
     _height = ILI9341_TFTWIDTH;
     break;
  case 2:
    writedata(MADCTL_MY | MADCTL_BGR);
     _width  = ILI9341_TFTWIDTH;
     _height = ILI9341_TFTHEIGHT;
    break;
   case 3:
     writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
     _width  = ILI9341_TFTHEIGHT;
     _height = ILI9341_TFTWIDTH;
     break;
  }
  spi_end();
}
 
void yama_2_GFX_ILI9341::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
  gpio_dc_on();
  spi_write(ILI9341_CASET); // Column addr set
  gpio_dc_off();
  spi_write(x0 >> 8);
  spi_write(x0);
  spi_write(x1 >> 8);
  spi_write(x1);
 
  gpio_dc_on();
  spi_write(ILI9341_PASET); // Row addr set
  gpio_dc_off();
  spi_write(y0>>8);
  spi_write(y0);     // YSTART
  spi_write(y1>>8);
  spi_write(y1);     // YEND
 
  gpio_dc_on();
  spi_write(ILI9341_RAMWR); // write to RAM
  gpio_dc_off();
}
 
 
void yama_2_GFX_ILI9341::writedata1(uint8_t *buf, size_t count) {
    spi_write_blocking(_spi, buf, count);
}
 
void yama_2_GFX_ILI9341::pixel_flush(void) {
  if(m_pbi > 0){
    writedata1(m_pixelBuf, m_pbi);
    m_pbi = 0;
  }
};
 
inline void yama_2_GFX_ILI9341::pixel_write(uint16_t color){
  if(m_pbi > PIXEL_BUF_SIZE-2)
    pixel_flush();
  m_pixelBuf[m_pbi++] = color >> 8;
  m_pixelBuf[m_pbi++] = color;
};
 
inline void yama_2_GFX_ILI9341::pixel_write(uint8_t hi, uint8_t lo){
  if(m_pbi > PIXEL_BUF_SIZE-2)
    pixel_flush();
  m_pixelBuf[m_pbi++] = hi;
  m_pixelBuf[m_pbi++] = lo;
};
 
void yama_2_GFX_ILI9341::fill_color(uint16_t color, uint32_t len)
{
  uint8_t hi = color >> 8;
  uint8_t lo = color;
  for(uint32_t i=0; i<len;i++)
    pixel_write(hi,lo);
  pixel_flush();
}
 
void yama_2_GFX_ILI9341::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;
 
  spi_begin();
  setAddrWindow(x,y,x+1,y+1);
 
  spi_write(color >> 8);
  spi_write(color);
  spi_end();
}
 
void yama_2_GFX_ILI9341::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  if(w > 0 && h > 0){
    // rudimentary clipping (drawChar w/big text requires this)
    if((x >= _width) || (y >= _height)) return;
    if((x + w - 1) >= _width)  w = _width  - x;
    if((y + h - 1) >= _height) h = _height - y;
 
    spi_begin();
    setAddrWindow(x, y, x+w-1, y+h-1);
    fill_color( color, w * h);
    spi_end();
  }
}
 
void yama_2_GFX_ILI9341::invertDisplay(bool i) {
  spi_begin();
  writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
  spi_end();
}
 
void yama_2_GFX_ILI9341::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
 
  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
 
  if((y+h-1) >= _height) 
    h = _height-y;
 
  spi_begin();
  setAddrWindow(x, y, x, y+h-1);
  fill_color(color,h);
  spi_end();
}
 
void yama_2_GFX_ILI9341::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
 
  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  
  spi_begin();
  setAddrWindow(x, y, x+w-1, y);
  fill_color(color, w);
  spi_end();
}
 
void yama_2_GFX_ILI9341::drawBitmap(int16_t x, int16_t y,const uint8_t bitmap[],
                    int16_t w, int16_t h,
                    uint16_t color, uint16_t bg)
{
  int16_t xi,yi;
  const uint8_t *p = bitmap;
 
  spi_begin();
  setAddrWindow(x, y, x+w-1, y+h-1);
  for(yi=0; yi<h; yi++){
    for(xi=0; xi<w; xi+=8){
      uint8_t m = 0x80;
      uint8_t d = *p++;
      for(int i=0; i<8 && xi+i < w; i++,m>>=1)
    pixel_write(m & d ? color : bg);
    }
  }
  pixel_flush();
  spi_end();
}
 
void yama_2_GFX_ILI9341::drawRGBBitmap(int16_t x, int16_t y,
                       const uint16_t bitmap[],
                       int16_t w, int16_t h)
{
  int16_t xi,yi;
  const uint16_t *p = bitmap;
 
  spi_begin();
  setAddrWindow(x, y, x+w-1, y+h-1);
  for(yi=0; yi<h; yi++){
    for(xi=0; xi<w; xi++)
      pixel_write(*p++);
  }
  pixel_flush();
  spi_end();
}
 
uint16_t yama_2_GFX_ILI9341::color(int colr, int colg, int colb) {
    uint16_t color;
    color = (uint16_t)((colr * 32 / 256) << 11) | ((colg * 64 / 256) << 5) | (colb * 32 / 256);
 
    return color;
}
 
uint16_t yama_2_GFX_ILI9341::color565(int colr, int colg, int colb) {
    return color(colr, colg, colb);
}
 
void yama_2_GFX_ILI9341::sendCommand(uint8_t commandByte, uint8_t *dataBytes, uint8_t numDataBytes) {
  spi_begin();
 
  gpio_dc_on();
  spi_write(commandByte);
  gpio_dc_off();
 
  for (int i = 0; i < numDataBytes; i++) {
      spi_write(*dataBytes);
      dataBytes++;
  }
 
  spi_end();
}
 
uint8_t yama_2_GFX_ILI9341::spiRead(void) {
  uint8_t buf_spi_read;
  spi_read_blocking(_spi, 0, &buf_spi_read, 1);
  return  buf_spi_read;
}
 
uint8_t yama_2_GFX_ILI9341::readcommand8(uint8_t commandByte, uint8_t index) {
    uint8_t result;
    uint8_t data = 0x10 + index;
    sendCommand(0xD9, &data, 1); // Set Index Register
 
    spi_begin();
    gpio_dc_on();
    spi_write(commandByte);
    gpio_dc_off();
    do {
      result = spiRead();
    } while (index--); // Discard bytes up to index'th
    spi_end();
    return result;
}
 
 
// -------------------------------------------------------------------------
 
// GFXcanvas1, GFXcanvas8 and GFXcanvas16 (currently a WIP, don't get too
// comfy with the implementation) provide 1-, 8- and 16-bit offscreen
// canvases, the address of which can be passed to drawBitmap() or
// pushColors() (the latter appears only in a couple of GFX-subclassed TFT
// libraries at this time).  This is here mostly to help with the recently-
// added proportionally-spaced fonts; adds a way to refresh a section of the
// screen without a massive flickering clear-and-redraw...but maybe you'll
// find other uses too.  VERY RAM-intensive, since the buffer is in MCU
// memory and not the display driver...GXFcanvas1 might be minimally useful
// on an Uno-class board, but this and the others are much more likely to
// require at least a Mega or various recent ARM-type boards (recommended,
// as the text+bitmap draw can be pokey).  GFXcanvas1 requires 1 bit per
// pixel (rounded up to nearest byte per scanline), GFXcanvas8 is 1 byte
// per pixel (no scanline pad), and GFXcanvas16 uses 2 bytes per pixel (no
// scanline pad).
// NOT EXTENSIVELY TESTED YET.  MAY CONTAIN WORST BUGS KNOWN TO HUMANKIND.
 
/**************************************************************************/
/*!
   @brief    Instatiate a GFX 1-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas1::GFXcanvas1(uint16_t w, uint16_t h) : yama_2_GFX(w, h) {
  uint16_t bytes = ((w + 7) / 8) * h;
  if ((buffer = (uint8_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}
 
/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas1::~GFXcanvas1(void) {
  if (buffer)
    free(buffer);
}
 
/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x     x coordinate
    @param  y     y coordinate
    @param  color Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas1::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;
 
    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }
 
    uint8_t *ptr = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
#ifdef __AVR__
    if (color)
      *ptr |= *((uint8_t *)(&GFXsetBit[x & 7]));
    else
      *ptr &= *((uint8_t *)(&GFXclrBit[x & 7]));
#else
    if (color)
      *ptr |= 0x80 >> (x & 7);
    else
      *ptr &= ~(0x80 >> (x & 7));
#endif
  }
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given coordinate
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's binary color value, either 0x1 (on) or 0x0
   (off)
*/
/**********************************************************************/
bool GFXcanvas1::getPixel(int16_t x, int16_t y) const {
  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }
  return getRawPixel(x, y);
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given, unrotated coordinate.
              This method is intended for hardware drivers to get pixel value
              in physical coordinates.
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's binary color value, either 0x1 (on) or 0x0
   (off)
*/
/**********************************************************************/
bool GFXcanvas1::getRawPixel(int16_t x, int16_t y) const {
  if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
    return 0;
  if (this->getBuffer()) {
    uint8_t *buffer = this->getBuffer();
    uint8_t *ptr = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
 
#ifdef __AVR__
    return ((*ptr) & *((uint8_t *)(&GFXsetBit[x & 7]))) != 0;
#else
    return ((*ptr) & (0x80 >> (x & 7))) != 0;
#endif
  }
  return 0;
}
 
/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color Binary (on or off) color to fill with
*/
/**************************************************************************/
void GFXcanvas1::fillScreen(uint16_t color) {
  if (buffer) {
    uint16_t bytes = ((WIDTH + 7) / 8) * HEIGHT;
    memset(buffer, color ? 0xFF : 0x00, bytes);
  }
}
 
/**************************************************************************/
/*!
   @brief    Instatiate a GFX 8-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas8::GFXcanvas8(uint16_t w, uint16_t h) : yama_2_GFX(w, h) {
  uint32_t bytes = w * h;
  if ((buffer = (uint8_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}
 
/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas8::~GFXcanvas8(void) {
  if (buffer)
    free(buffer);
}
 
/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x   x coordinate
    @param  y   y coordinate
    @param  color 8-bit Color to fill with. Only lower byte of uint16_t is used.
*/
/**************************************************************************/
void GFXcanvas8::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;
 
    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }
 
    buffer[x + y * WIDTH] = color;
  }
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given coordinate
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's 8-bit color value
*/
/**********************************************************************/
uint8_t GFXcanvas8::getPixel(int16_t x, int16_t y) const {
  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }
  return getRawPixel(x, y);
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given, unrotated coordinate.
              This method is intended for hardware drivers to get pixel value
              in physical coordinates.
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's 8-bit color value
*/
/**********************************************************************/
uint8_t GFXcanvas8::getRawPixel(int16_t x, int16_t y) const {
  if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
    return 0;
  if (buffer) {
    return buffer[x + y * WIDTH];
  }
  return 0;
}
 
/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color 8-bit Color to fill with. Only lower byte of uint16_t is used.
*/
/**************************************************************************/
void GFXcanvas8::fillScreen(uint16_t color) {
  if (buffer) {
    memset(buffer, color, WIDTH * HEIGHT);
  }
}
 
void GFXcanvas8::writeFastHLine(int16_t x, int16_t y, int16_t w,
                                uint16_t color) {
 
  if ((x >= _width) || (y < 0) || (y >= _height))
    return;
  int16_t x2 = x + w - 1;
  if (x2 < 0)
    return;
 
  // Clip left/right
  if (x < 0) {
    x = 0;
    w = x2 + 1;
  }
  if (x2 >= _width)
    w = _width - x;
 
  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }
 
  memset(buffer + y * WIDTH + x, color, w);
}
 
/**************************************************************************/
/*!
   @brief    Instatiate a GFX 16-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas16::GFXcanvas16(uint16_t w, uint16_t h) : yama_2_GFX(w, h) {
  uint32_t bytes = w * h * 2;
  if ((buffer = (uint16_t *)malloc(bytes))) {
    memset(buffer, 0, bytes);
  }
}
 
/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas16::~GFXcanvas16(void) {
  if (buffer)
    free(buffer);
}
 
/**************************************************************************/
/*!
    @brief  Draw a pixel to the canvas framebuffer
    @param  x   x coordinate
    @param  y   y coordinate
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;
 
    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }
 
    buffer[x + y * WIDTH] = color;
  }
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given coordinate
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's 16-bit 5-6-5 color value
*/
/**********************************************************************/
uint16_t GFXcanvas16::getPixel(int16_t x, int16_t y) const {
  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = WIDTH - 1 - y;
    y = t;
    break;
  case 2:
    x = WIDTH - 1 - x;
    y = HEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = y;
    y = HEIGHT - 1 - t;
    break;
  }
  return getRawPixel(x, y);
}
 
/**********************************************************************/
/*!
        @brief    Get the pixel color value at a given, unrotated coordinate.
              This method is intended for hardware drivers to get pixel value
              in physical coordinates.
        @param    x   x coordinate
        @param    y   y coordinate
        @returns  The desired pixel's 16-bit 5-6-5 color value
*/
/**********************************************************************/
uint16_t GFXcanvas16::getRawPixel(int16_t x, int16_t y) const {
  if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
    return 0;
  if (buffer) {
    return buffer[x + y * WIDTH];
  }
  return 0;
}
 
/**************************************************************************/
/*!
    @brief  Fill the framebuffer completely with one color
    @param  color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::fillScreen(uint16_t color) {
  if (buffer) {
    uint8_t hi = color >> 8, lo = color & 0xFF;
    if (hi == lo) {
      memset(buffer, lo, WIDTH * HEIGHT * 2);
    } else {
      uint32_t i, pixels = WIDTH * HEIGHT;
      for (i = 0; i < pixels; i++)
        buffer[i] = color;
    }
  }
}
 
/**************************************************************************/
/*!
    @brief  Reverses the "endian-ness" of each 16-bit pixel within the
            canvas; little-endian to big-endian, or big-endian to little.
            Most microcontrollers (such as SAMD) are little-endian, while
            most displays tend toward big-endianness. All the drawing
            functions (including RGB bitmap drawing) take care of this
            automatically, but some specialized code (usually involving
            DMA) can benefit from having pixel data already in the
            display-native order. Note that this does NOT convert to a
            SPECIFIC endian-ness, it just flips the bytes within each word.
*/
/**************************************************************************/
void GFXcanvas16::byteSwap(void) {
  if (buffer) {
    uint32_t i, pixels = WIDTH * HEIGHT;
    for (i = 0; i < pixels; i++)
      buffer[i] = __builtin_bswap16(buffer[i]);
  }
}