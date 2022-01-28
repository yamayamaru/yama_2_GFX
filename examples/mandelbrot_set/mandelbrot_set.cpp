//    Raspberry Pi Pico pico-sdk C++ Mandelbrot Set ILI9341
//    Require:
//        yama_2_GFX.h
//        https://pastebin.com/DUS5TrWw
//        yama_2_GFX.cpp
//        https://pastebin.com/k9qAJMwF
//        CMakeLists.txt
//        https://pastebin.com/NjBZa5QY

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "yama_2_GFX.h"
 
#define MOSI 19
#define SCK  18
#define CS   17
#define MISO 16
 
#define RST  22
#define DC   20
 
#define SPI_PORT  spi0
const int tft_frequency = 10000000;

yama_2_GFX_ILI9341 tft = yama_2_GFX_ILI9341(SPI_PORT, DC, RST, CS);

void print_double(double a);
void print_double_ln(double a);

void mandelbrot(void);
void mandel(double xcorner, double ycorner, double length, int xdot, int ydot, int depth);
int mand(double a1, double b1, int depth1);

void loop(void);

int main() {

  stdio_init_all();

  spi_init(SPI_PORT, tft_frequency);
  gpio_set_function(MISO, GPIO_FUNC_SPI);
  gpio_set_function(SCK, GPIO_FUNC_SPI);
  gpio_set_function(MOSI, GPIO_FUNC_SPI);
  gpio_pull_up(MISO);
  gpio_pull_up(SCK);
  gpio_pull_up(MOSI);
  spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST

  tft.tft_setup();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);

  printf("ILI9341 Test!\r\n"); 

  while (1) {
    loop();
    sleep_ms(5000);
  }
  return 0;
}

void loop(void) {
    mandelbrot();
    sleep_ms(60000);
}

void mandelbrot(void) {

    double    xcorner, ycorner, length;
    int       xdot, ydot, depth;

    xdot = 320;
    ydot = 240;

    xcorner =  -2.4;
    ycorner =  -1.7;
    length  =   3.2;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -6.1099999999999965e-001;
    ycorner =  6e-001;
    length  =  1.0000000000000001e-001;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -7.512120844523107e-001;
    ycorner = 2.939359283447132e-002;
    length = 2.441406250000000e-005;
    depth = 1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.7878664118448890e+000;
    ycorner = -4.6994043985999932e-003;
    length  =  1.5258789062500001e-006;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.255058807618605e+000;
    ycorner =  3.834129844820908e-001;
    length  =  5.960464477539063e-009;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -7.424999999999979e-002;
    ycorner = -6.523749999999998e-001;
    length = 3.125000000000000e-003;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -7.366145833333310e-002;
    ycorner = -6.500052083333332e-001;
    length = 3.125000000000000e-003;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -7.451562499999977e-002;
    ycorner = -6.500117187500000e-001;
    length = 7.812500000000000e-004;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -7.409765624999977e-002;
    ycorner = -6.494752604166667e-001;
    length = 1.953125000000000e-004;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.408903645833333e+000;
    ycorner = -1.342989908854166e-001;
    length = 2.441406250000000e-005;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.408903645833333e+000;
    ycorner = -1.342989908854166e-001;
    length = 2.441406250000000e-005;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.408886164585749e+000;
    ycorner = -1.342802622318267e-001;
    length = 1.192092895507813e-008;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.408886160294215e+000;
    ycorner = -1.342802576224008e-001;
    length = 2.980232238769531e-009;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.023473307291662e-001;
    ycorner = 9.571370442708340e-001;
    length = 4.882812500000000e-005;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.023286539713537e-001;
    ycorner = 9.571538899739589e-001;
    length = 1.220703125000000e-005;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.165292968750000e+000;
    ycorner = 2.393867187500003e-001;
    length = 3.906250000000000e-004;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -1.164973597208659e+000;
    ycorner = 2.394546101888024e-001;
    length = 1.525878906250000e-006;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -6.703997395833329e-001;
    ycorner = -4.582591145833326e-001;
    length = 3.906250000000000e-004;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -6.702213948567705e-001;
    ycorner = -4.580732421874992e-001;
    length = 2.441406250000000e-005;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -6.702324136098221e-001;
    ycorner = -4.580734767913810e-001;
    length = 1.907348632812500e-007;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
    sleep_ms(10000);

    xcorner = -6.702323307991023e-001;
    ycorner = -4.580733914375297e-001;
    length = 2.384185791015625e-008;
    depth   =  1000;
    mandel(xcorner, ycorner, length, xdot, ydot, depth);
}

void mandel(double xcorner, double ycorner, double length, int xdot, int ydot, int depth) {
    double xgap, ygap;
    double xx, yy;
    int    i, j;
    int    col01, colr, colg, colb;

    // xgap = length / xdot;
    // ygap = length / xdot;
    xgap = length / ydot;
    ygap = length / ydot;
    //  x軸を240ドットから320ドットに広げる
    xcorner = xcorner - (xdot - ydot) / 2 * xgap;
    printf("xdot = %d    ydot = %d\r\n", xdot, ydot);
//    printf("xcorner = %.15e\r\n", xcorner);
//    printf("ycorner = %.15e\r\n", ycorner);
//    printf("length  = %.15e\r\n", length);
    printf("xcorner = ");
    print_double_ln(xcorner);
    printf("ycorner = ");
    print_double_ln(ycorner);
    printf("length  = ");
    print_double_ln(length);

    printf("depth   = %d\r\n", depth);
    printf("\r\n");

    xx = xcorner;
    yy = ycorner;
    for(j = 0; j < ydot; j++) {
        for(i = 0; i < xdot; i++) {
          col01 = (short) mand( xx, yy, depth);
            if (col01 == 0){
                colr = 0;
                colg = 0;
                colb = 0;
            } else {
                colr = (col01 % 64) * 2 + 129;
                colg = (col01 % 64) * 4 + 3;
                colb = (col01 % 64) * 4 + 3;
            }
            tft.fillRect(i, j, 2, 1, tft.color(colr, colg, colb));

          xx = xx + xgap;
        }
        yy = yy + ygap;
        xx = xcorner;
    }
}

int mand(double a1, double b1, int depth1) {
    int     i1;
    double  x1, y1, tmp1, x2, y2;

    i1 = 0;
    x1 = 0; y1 = 0;
    x2 = x1 * x1;   y2 = y1 * y1;
    while ((i1 < depth1) && (x2+y2 <=4)) {
        tmp1 = x2 - y2 + a1;
        y1 = 2 * x1 * y1 + b1;
        x1 = tmp1;
        x2 = x1 * x1;  y2 = y1 * y1;
        i1++;
    }

    if (i1 == depth1) i1 = 0;
    else            i1++;
    return i1;
}

void print_double(double a) {
    double exp01, exp02, a01, b01, c01, c_exp01, d01;
    int sign01 = 0;
    int digits01 = 15 - 1;

    a01 = a;
    if (a01 < 0) {
        sign01 = 1;
        a01 = -a01;
    }

    if (a01 > 5.0e-324) {
        b01 = log(a01)/log(10.0);
        c_exp01 = floor(b01);
        c01 = pow(10.0, (b01 - c_exp01));
    } else {
        c01 = 0.0;
        c_exp01 = 0.0;
    }

    c01 = c01 + 0.5 * pow(10.0, (double)(-digits01));

    if (sign01) printf("-");
    d01 = floor(c01);
    c01 = c01 - d01;
    printf("%1d.", (int)d01);
    for (int i = 0; i < digits01; i++) {
        c01 = c01 * 10.0;
        d01 = floor(c01);
        c01 = c01 - d01;
        printf("%1d", (int)d01);
    }
    if (c_exp01 >= 0) {
        printf("e+");
    } else {
        printf("e-");
        c_exp01 = -c_exp01;
    }

    printf("%03d", (int)c_exp01);
}

void print_double_ln(double a) {
    print_double(a);
    printf("\r\n");
}
