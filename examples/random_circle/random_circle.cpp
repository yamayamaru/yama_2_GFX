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

#define WIDTH    320
#define HEIGHT   240
#define CIRCLE_N  80
#define RDX        5
#define RDY        5


void random_circle(void);
void setup();
void loop();
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

    sleep_ms(100); 
    printf("\nReset:");


    tft.tft_setup();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);

    setup();
    while (1) {
        loop();
    }

    return 0;
}

void loop() {
    random_circle();
}

int rnd(int max);

struct {
    int    x;
    int    y;
    int    dx;
    int    dy;
    int    signx;
    int    signy;
    int    r;
    int    c;
} circle01[CIRCLE_N];

GFXcanvas16 canvas01 = GFXcanvas16(WIDTH, HEIGHT);

void setup(void){
    for (int i = 0; i < CIRCLE_N; i++) {
        circle01[i].x = rnd(WIDTH);
        circle01[i].y = rnd(HEIGHT);
        circle01[i].r = rnd(10) + 5;
        circle01[i].c = rnd(65534) + 1;
        circle01[i].dx = rnd(RDX) + 1;
        circle01[i].dy = rnd(RDY) + 1;
        circle01[i].signx = rnd(2) ? 1 : -1;
        circle01[i].signy = rnd(2) ? 1 : -1;
    }
}

void random_circle(void) {

    int temp1, temp2;
    canvas01.fillScreen(ILI9341_BLACK);
    for (int i = 0; i < CIRCLE_N; i++ ) {
        temp1 = circle01[i].dx * circle01[i].signx;
        temp2 = circle01[i].x + temp1;
        if (temp2 > WIDTH) {
            circle01[i].signx = -1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = WIDTH + circle01[i].signx * circle01[i].dx;
        } else if (temp2 < 0 ) {
            circle01[i].signx = 1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = 0 + circle01[i].signx * circle01[i].dx;
        } else {
            circle01[i].x = circle01[i].x + temp1;
        } 
        temp1 = circle01[i].dy * circle01[i].signy;
        temp2 = circle01[i].y + temp1;
        if (temp2 > HEIGHT) {
            circle01[i].signy = -1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = HEIGHT + circle01[i].signy * circle01[i].dy;
        } else if (temp2 < 0 ) {
            circle01[i].signy = 1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = 0 + circle01[i].signy * circle01[i].dy;
        } else {
            circle01[i].y = circle01[i].y + temp1;
        } 
        canvas01.fillCircle( circle01[i].x, circle01[i].y + 15, circle01[i].r, circle01[i].c);
    }
    tft.drawRGBBitmap(0, 0, canvas01.getBuffer(), WIDTH, HEIGHT); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}
