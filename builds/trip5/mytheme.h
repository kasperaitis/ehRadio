#ifndef _my_theme_h
#define _my_theme_h

/*
    Theming of color displays
    DSP_ST7735, DSP_ST7789, DSP_ILI9341, DSP_GC9106, DSP_ILI9225, DSP_ST7789_240
    ***********************************************************************
    *    !!! This file must be in the root directory of the sketch !!!    *
    ***********************************************************************
    Uncomment (remove double slash //) from desired line to apply color
*/
#define ENABLE_THEME
#ifdef  ENABLE_THEME

/* ehRadio theme colors below (yoRadio defaults are still in options.h)                          */
/*-----------------------------------------------------------------------------------------------*/
/*       | COLORS             |   values (0-255)  |                                              */
/*       | color name         |    R    G    B    |                                              */
/*-----------------------------------------------------------------------------------------------*/
#define COLOR_IP                200, 20,  240 // IP address
#define COLOR_VOLUME_VALUE      15,  180,  15 // volume number
#define COLOR_VOLBAR_OUT        30,  200,  30 // border of volume bar
#define COLOR_VOLBAR_IN         5,   140,   5 // inside volume bar
#define COLOR_DIGITS            255, 255, 255 // numbers...?
#define COLOR_DIVIDER           132, 132, 165 // lines around clock
#define COLOR_BACKGROUND          0,   0,   0 // background
#define COLOR_STATION_NAME        0,   0,   0 // station text color
#define COLOR_STATION_BG          0, 100, 255 // current station background
#define COLOR_STATION_FILL        0,  98, 250 // fill color (outside bg)
#define COLOR_BITRATE           220, 220,  90 // stream bitrate
#define COLOR_WEATHER             0, 255,   0 // weather string
#define COLOR_SNG_TITLE_1       255, 255, 255 // first title
#define COLOR_SNG_TITLE_2       220, 220, 220 // second title
#define COLOR_VU_MAX            178,  34,  34 // max of VU meter "FireBrick"
#define COLOR_VU_MIN              0, 128,   0 // min of VU meter "Green"
#define COLOR_CLOCK             255,  32,  16 // clock color
#define COLOR_SECONDS           255,  16,   4 // seconds color (DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_CLOCK_BG           30,   2,   2 // clock color background
#define COLOR_DAY_OF_W          240, 240, 240 // day of week color (for DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_DATE              255, 255, 255 // date color (DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_HEAP              231, 115,   0 // heap string
#define COLOR_BUFFER            220, 220,  90 // buffer line
#define COLOR_RSSI              200,  20, 240 // rssi
#define COLOR_PL_CURRENT          0, 170, 250 // playlist current item
#define COLOR_PL_CURRENT_BG      30,  30,  30 // playlist current item background
#define COLOR_PL_CURRENT_FILL    60,  60,  60 // playlist current item fill background
#define COLOR_PLAYLIST_0        250, 250, 250 // playlist string 0
#define COLOR_PLAYLIST_1        230, 230, 230 // playlist string 1
#define COLOR_PLAYLIST_2        210, 210, 210 // playlist string 2
#define COLOR_PLAYLIST_3        190, 190, 190 // playlist string 3
#define COLOR_PLAYLIST_4        170, 170, 170 // playlist string 4

#endif  /* #ifdef  ENABLE_THEME */
#endif  /* #define _my_theme_h  */
