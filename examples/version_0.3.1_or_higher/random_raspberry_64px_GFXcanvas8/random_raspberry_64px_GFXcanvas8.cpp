/*

    Raspberry Pi Pico pico-sdk LCD ILI9341 font print Library (C++)
    print_GFX demo program random_raspberry_64px_GFXcanvas8.cpp
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


extern const uint8_t bitmap01[];
extern const uint8_t bitmap_mask01[];

#define RASPBERRY_N  40
#define RDX        5
#define RDY        5

void random_raspberry(void);
void setup();
void loop();
int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 40000000);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    gpio_pull_up(MISO);
    gpio_pull_up(SCK);
    gpio_pull_up(MOSI);
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST

    sleep_ms(100); 
    printf("\nReset:");


    tft.tft_setup();
    tft.setRotation(0);
    tft.fillScreen(ILI9341_BLACK);
    // tft.drawPalette256Bitmapで使用するパレットをweb safe color 216にする
    tft.setWeb216Palette256();

    while (1) {
        setup();
        for (int i = 0; i < 200; i++) {
            loop();
        }
    }

    return 0;
}

void loop() {
    random_raspberry();
}

GFXcanvas8 canvas01 = GFXcanvas8(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
    // GFXcanvas8はメモリ上の確保したフレームバッファ上に描画するクラスです。
    // GFXcanvas8でメモリ上に書き込んだうえで
    // print_GFX_ILI9341もしくはyama_2_GFX_ILI9341のdrawPalette256Bitmap()で
    // 実際にILI9341のLCDにフレームバッファのメモリの内容を
    // 一度に書き込むことで高速に描画ができます。


int rnd(int max);

struct {
    int    x;
    int    y;
    int    dx;
    int    dy;
    int    signx;
    int    signy;
    int    c;
} raspberry_data01[RASPBERRY_N];

void setup(void){
    static int r = 3;

    canvas01.setRotation(r);

    for (int i = 0; i < RASPBERRY_N; i++) {
        raspberry_data01[i].x = rnd(canvas01.width());
        raspberry_data01[i].y = rnd(canvas01.height());
        raspberry_data01[i].dx = rnd(RDX) + 1;
        raspberry_data01[i].dy = rnd(RDY) + 1;
        raspberry_data01[i].signx = rnd(2) ? 1 : -1;
        raspberry_data01[i].signy = rnd(2) ? 1 : -1;
    }

    r++;
    if (r >= 4) r = 0;
}

void random_raspberry(void) {

    int temp1, temp2;
    canvas01.fillScreen(WEB216_PALETTE_BLACK);
    for (int i = 0; i < RASPBERRY_N; i++ ) {
        temp1 = raspberry_data01[i].dx * raspberry_data01[i].signx;
        temp2 = raspberry_data01[i].x + temp1;
        if (temp2 > canvas01.width()) {
            raspberry_data01[i].signx = -1;
            raspberry_data01[i].dx = rnd(RDX) + 1;
            raspberry_data01[i].x = canvas01.width() + raspberry_data01[i].signx * raspberry_data01[i].dx;
        } else if (temp2 < 0 ) {
            raspberry_data01[i].signx = 1;
            raspberry_data01[i].dx = rnd(RDX) + 1;
            raspberry_data01[i].x = 0 + raspberry_data01[i].signx * raspberry_data01[i].dx;
        } else {
            raspberry_data01[i].x = raspberry_data01[i].x + temp1;
        } 
        temp1 = raspberry_data01[i].dy * raspberry_data01[i].signy;
        temp2 = raspberry_data01[i].y + temp1;
        if (temp2 > canvas01.height()) {
            raspberry_data01[i].signy = -1;
            raspberry_data01[i].dy = rnd(RDY) + 1;
            raspberry_data01[i].y = canvas01.height() + raspberry_data01[i].signy * raspberry_data01[i].dy;
        } else if (temp2 < 0 ) {
            raspberry_data01[i].signy = 1;
            raspberry_data01[i].dy = rnd(RDY) + 1;
            raspberry_data01[i].y = 0 + raspberry_data01[i].signy * raspberry_data01[i].dy;
        } else {
            raspberry_data01[i].y = raspberry_data01[i].y + temp1;
        }

        // GFXcanvas8のバッファにラズベリーのアイコンの描画
        canvas01.drawGrayscaleBitmap( raspberry_data01[i].x, raspberry_data01[i].y, bitmap01, bitmap_mask01, 64, 64);
    }

    // GFXcanvas8のバッファの内容を実際にILI9341のLCDに書き込む
    tft.drawPalette256Bitmap(0, 0, canvas01.getBuffer(), ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}

const uint8_t bitmap_mask01[] = {       // 64x64の8bitカラー画像マスクデータ
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x0f,0xc0,0x03,0xf0,0x00,0x00,0x00,0x00,0x7f,0xf0,0x0f,0xfe,0x00,0x00,
    0x00,0x01,0xff,0xfc,0x3f,0xff,0x80,0x00,0x00,0x01,0xff,0xfe,0x7f,0xff,0x80,0x00,
    0x00,0x01,0xff,0xfe,0x7f,0xff,0x80,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,
    0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,
    0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,
    0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,
    0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,
    0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x07,0xff,0xff,0xff,0xff,0xe0,0x00,
    0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xc0,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,
    0x00,0x01,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,
    0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xfe,0x00,0x00,
    0x00,0x00,0x3f,0xff,0xff,0xfc,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xf8,0x00,0x00,
    0x00,0x00,0x0f,0xff,0xff,0xf0,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xc0,0x00,0x00,
    0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xfc,0x00,0x00,0x00,
    0x00,0x00,0x00,0x1f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xe0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

const uint8_t bitmap01[] = {       // 64x64の8bitカラー画像データ(web216パレット)
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xac,0xac,0xac,0xd7,0xd7,0xac,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,0xac,0xac,0xac,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0xd7,0xd7,0xd1,0xd1,0xd1,0xd1,0xd1,0xd7,0xd7,0xd7,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,0xd1,0xd1,0xd1,0xd1,0xd1,0xd7,0xd7,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xd7,0xd7,0xa7,0xa7,0xa0,0x7c,0x75,0x7c,0x75,0xa7,0x7c,0xd1,0xd1,0xd7,0x00,0x00,
    0x00,0x00,0xd7,0xad,0xd1,0x7c,0xa7,0x7c,0x7c,0x75,0x7c,0xa0,0xa7,0xa7,0xd7,0xd7,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xa7,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xd1,0xd7,0x00,
    0x00,0xd7,0xad,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xa7,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xa6,0x75,0x75,0x75,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xd7,0x00,
    0x00,0xd7,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0x75,0x75,0x75,0xa6,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xa7,0x75,0x75,0x75,0x75,0x7c,0xa7,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0xd1,0xd7,
    0xd7,0xa6,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xa7,0x7c,0x75,0x75,0x75,0x75,0xa7,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xad,0x7c,0x75,0x75,0x75,0x75,0x7c,0xa7,0xa7,0x7c,0x75,0x75,0x75,0x75,0xa7,0xd7,
    0xd7,0xa7,0x75,0x75,0x75,0x75,0x7c,0xa6,0xa7,0xa0,0x75,0x75,0x75,0x75,0x7c,0xd1,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xd7,0xa6,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xa6,0xa7,0x75,0x75,0x76,0xa7,0xd7,
    0xd7,0xa7,0x75,0x75,0x75,0xa7,0xa6,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0xa6,0xd7,
    0xac,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xd7,0xd1,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xa6,0xa6,0x7c,0x7c,0xd1,0xd7,
    0xd7,0xd1,0x7c,0x7c,0xa6,0xa6,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xad,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xac,0xd7,0xa6,0x7c,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0xa6,0xad,0xad,0xd7,0xd7,
    0xd7,0xd7,0xad,0xad,0xa6,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x7c,0xa6,0xd7,0xac,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0xd7,0xa7,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0xd1,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0xd1,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0x75,0xa7,0xd7,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xd7,0xd7,0xa7,0x7c,0x75,0x75,0x75,0x75,0x75,0x7c,0xd7,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0xd7,0x7c,0x75,0x75,0x75,0x75,0x75,0x7c,0xa7,0xd7,0xd7,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xd7,0xd7,0xa6,0x7c,0x75,0x7c,0x7c,0xa6,0xd7,0xd7,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0xd7,0xd7,0xa6,0x7c,0x7c,0x75,0x7c,0xa6,0xd7,0xd7,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,0xd1,0xd0,0xd7,0xd7,0xd7,0xd7,0xd7,0xb3,0xb3,
    0xb3,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,0xd0,0xd1,0xd7,0xd7,0xd7,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xd7,0xd7,0xb3,0xb3,0xb3,0xb3,0xd7,0xd7,0x8e,0x6a,0x6a,0x3f,
    0x3f,0x6a,0x6a,0x8e,0xd7,0xd7,0xb3,0xb3,0xb3,0xb3,0xd7,0xd7,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xd7,0xb3,0x6a,0x6a,0x6a,0x3f,0x6a,0xd7,0x8e,0x6a,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0x6a,0x3f,0x6a,0x6a,0x6a,0xb3,0xd7,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0x8e,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xd7,0xd7,0xd7,0x8e,0x6a,0x6a,0x3f,
    0x3f,0x3f,0x6a,0x6a,0xb3,0xd7,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0xb3,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0x6a,0x3f,0x3f,0x6a,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xb3,0xb3,
    0xb3,0xb3,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x8e,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0xd7,0x6a,0x6a,0x8e,0xd7,0xd7,0xb3,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0xb3,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0xd7,0x8e,0x6a,0x6a,0xd7,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0xd7,0xb3,0xb3,0xd7,0xd7,0x8e,0x6a,0x3f,0x3f,0x3f,0x3f,0x6a,0x8e,0xd7,0xd7,
    0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0x8e,0xd7,0xd7,0xb3,0xb3,0xd7,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0xd7,0xd7,0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,
    0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xb3,0x6a,0xb3,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,
    0xd7,0xb3,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0xb3,0x6a,0xb3,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xb3,
    0x6a,0x3f,0x8e,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,
    0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0x6a,0x3f,0x6a,
    0xb3,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x6a,
    0x3f,0x3f,0x6a,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,
    0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0x6a,0x3f,0x3f,
    0x6a,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x8e,0x3f,
    0x3f,0x3f,0x6a,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,
    0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0x6a,0x3f,0x3f,
    0x3f,0xb3,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x8e,0x3f,
    0x3f,0x3f,0x8e,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,
    0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0x8e,0x3f,0x3f,
    0x3f,0x8e,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x8e,0x3f,
    0x3f,0x3f,0xb3,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0xd7,
    0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x8e,0x3f,0x3f,
    0x3f,0xb3,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xb3,0x6a,
    0x3f,0x6a,0xb3,0xd7,0xd7,0x8e,0x6a,0x3f,0x3f,0x3f,0x3f,0x6a,0x8e,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0x8e,0x6a,0x3f,0x3f,0x3f,0x3f,0x6a,0x8e,0xd7,0xd7,0xb3,0x6a,0x3f,
    0x6a,0xb3,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x6a,
    0x3f,0x6a,0xd7,0xd7,0xd7,0xd7,0xb3,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0xb3,0x6a,0x6a,
    0x6a,0x6a,0x8e,0xd7,0xb3,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0xd7,0xd7,0xd7,0x6a,0x3f,
    0x6a,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0x8e,
    0x3f,0x8e,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x8e,0x3f,
    0x8e,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xb3,0xd7,0xd7,0xb3,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xb3,0xb3,0xd7,0xd7,0xb3,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xd7,0xb3,0x6a,0x3f,0x6a,0x6a,0xd7,0xd7,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0xd7,0xd7,0xd7,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,
    0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,
    0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0xb3,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0xb3,0x3f,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0x8e,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x6a,0x8e,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0x8e,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xd7,0xd7,0x6a,0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0xd7,0xb3,0x6a,0x6a,0x3f,
    0x3f,0x6a,0x6a,0xb3,0xd7,0xd7,0xb3,0x3f,0x3f,0x3f,0x3f,0x3f,0x6a,0xd7,0xd7,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0xd7,0xd7,0xd7,0xb3,0xb3,
    0xb3,0xb3,0xd7,0xd7,0xd7,0xd7,0xb3,0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xd7,0xb3,0x6a,0x6a,0x6a,0x6a,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x8e,0x6a,0x6a,0x6a,
    0x6a,0x6a,0x6a,0x6a,0xb3,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x3f,0xb3,0xd7,0xd7,0xd7,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xb3,0x6a,0x3f,0x3f,0x3f,
    0x3f,0x3f,0x3f,0x6a,0xb3,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xd7,0x8e,0x6a,0x6a,
    0x6a,0x6a,0xb3,0xd7,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd7,0xd7,0xd7,
    0xd7,0xd7,0xd7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
