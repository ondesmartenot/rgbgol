#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define print_fancy(red, green, blue, letter) fprintf(stdout, "%c[38;2;%d;%d;%dm%s", 0x1b, red, green, blue, letter )

typedef enum state {
    DOOMED,
    DEAD,
    BORN,
    ALIVE
} state;

typedef struct winsize winsize_t;

typedef struct cell {
    state s;
    state s_next;
} cell_t;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

typedef struct {
    rgb vals[504];
} colors;

static colors rgbvals = {
    {
        {0xff, 0x0, 0x0} ,
        {0xff, 0x2, 0x0} ,
        {0xff, 0x4, 0x0} ,
        {0xff, 0x6, 0x0} ,
        {0xff, 0x8, 0x0} ,
        {0xff, 0xa, 0x0} ,
        {0xff, 0xc, 0x0} ,
        {0xff, 0xe, 0x0} ,
        {0xff, 0x10, 0x0} ,
        {0xff, 0x12, 0x0} ,
        {0xff, 0x14, 0x0} ,
        {0xff, 0x16, 0x0} ,
        {0xff, 0x18, 0x0} ,
        {0xff, 0x1a, 0x0} ,
        {0xff, 0x1c, 0x0} ,
        {0xff, 0x1e, 0x0} ,
        {0xff, 0x20, 0x0} ,
        {0xff, 0x22, 0x0} ,
        {0xff, 0x24, 0x0} ,
        {0xff, 0x26, 0x0} ,
        {0xff, 0x28, 0x0} ,
        {0xff, 0x2a, 0x0} ,
        {0xff, 0x2c, 0x0} ,
        {0xff, 0x2e, 0x0} ,
        {0xff, 0x30, 0x0} ,
        {0xff, 0x32, 0x0} ,
        {0xff, 0x34, 0x0} ,
        {0xff, 0x36, 0x0} ,
        {0xff, 0x38, 0x0} ,
        {0xff, 0x3a, 0x0} ,
        {0xff, 0x3c, 0x0} ,
        {0xff, 0x3e, 0x0} ,
        {0xff, 0x40, 0x0} ,
        {0xff, 0x42, 0x0} ,
        {0xff, 0x44, 0x0} ,
        {0xff, 0x46, 0x0} ,
        {0xff, 0x48, 0x0} ,
        {0xff, 0x4a, 0x0} ,
        {0xff, 0x4c, 0x0} ,
        {0xff, 0x4e, 0x0} ,
        {0xff, 0x50, 0x0} ,
        {0xff, 0x52, 0x0} ,
        {0xff, 0x7d, 0x0} ,
        {0xff, 0x80, 0x0} ,
        {0xff, 0x83, 0x0} ,
        {0xff, 0x86, 0x0} ,
        {0xff, 0x89, 0x0} ,
        {0xff, 0x8c, 0x0} ,
        {0xff, 0x8f, 0x0} ,
        {0xff, 0x92, 0x0} ,
        {0xff, 0x95, 0x0} ,
        {0xff, 0x98, 0x0} ,
        {0xff, 0x9b, 0x0} ,
        {0xff, 0x9e, 0x0} ,
        {0xff, 0xa1, 0x0} ,
        {0xff, 0xa4, 0x0} ,
        {0xff, 0xa7, 0x0} ,
        {0xff, 0xaa, 0x0} ,
        {0xff, 0xad, 0x0} ,
        {0xff, 0xb0, 0x0} ,
        {0xff, 0xb3, 0x0} ,
        {0xff, 0xb6, 0x0} ,
        {0xff, 0xb9, 0x0} ,
        {0xff, 0xbc, 0x0} ,
        {0xff, 0xbf, 0x0} ,
        {0xff, 0xc2, 0x0} ,
        {0xff, 0xc5, 0x0} ,
        {0xff, 0xc8, 0x0} ,
        {0xff, 0xcb, 0x0} ,
        {0xff, 0xce, 0x0} ,
        {0xff, 0xd1, 0x0} ,
        {0xff, 0xd4, 0x0} ,
        {0xff, 0xd7, 0x0} ,
        {0xff, 0xda, 0x0} ,
        {0xff, 0xdd, 0x0} ,
        {0xff, 0xe0, 0x0} ,
        {0xff, 0xe3, 0x0} ,
        {0xff, 0xe6, 0x0} ,
        {0xff, 0xe9, 0x0} ,
        {0xff, 0xec, 0x0} ,
        {0xff, 0xef, 0x0} ,
        {0xff, 0xf2, 0x0} ,
        {0xff, 0xf5, 0x0} ,
        {0xff, 0xf8, 0x0} ,
        {0xff, 0xff, 0x0} ,
        {0xfb, 0xff, 0x0} ,
        {0xf7, 0xff, 0x0} ,
        {0xf3, 0xff, 0x0} ,
        {0xef, 0xff, 0x0} ,
        {0xeb, 0xff, 0x0} ,
        {0xe7, 0xff, 0x0} ,
        {0xe3, 0xff, 0x0} ,
        {0xdf, 0xff, 0x0} ,
        {0xdb, 0xff, 0x0} ,
        {0xd7, 0xff, 0x0} ,
        {0xd3, 0xff, 0x0} ,
        {0xcf, 0xff, 0x0} ,
        {0xcb, 0xff, 0x0} ,
        {0xc7, 0xff, 0x0} ,
        {0xc3, 0xff, 0x0} ,
        {0xbf, 0xff, 0x0} ,
        {0xbb, 0xff, 0x0} ,
        {0xb7, 0xff, 0x0} ,
        {0xb3, 0xff, 0x0} ,
        {0xaf, 0xff, 0x0} ,
        {0xab, 0xff, 0x0} ,
        {0xa7, 0xff, 0x0} ,
        {0xa3, 0xff, 0x0} ,
        {0x9f, 0xff, 0x0} ,
        {0x9b, 0xff, 0x0} ,
        {0x97, 0xff, 0x0} ,
        {0x93, 0xff, 0x0} ,
        {0x8f, 0xff, 0x0} ,
        {0x8b, 0xff, 0x0} ,
        {0x87, 0xff, 0x0} ,
        {0x83, 0xff, 0x0} ,
        {0x7f, 0xff, 0x0} ,
        {0x7b, 0xff, 0x0} ,
        {0x77, 0xff, 0x0} ,
        {0x73, 0xff, 0x0} ,
        {0x6f, 0xff, 0x0} ,
        {0x6b, 0xff, 0x0} ,
        {0x67, 0xff, 0x0} ,
        {0x63, 0xff, 0x0} ,
        {0x5f, 0xff, 0x0} ,
        {0x5b, 0xff, 0x0} ,
        {0x80, 0xff, 0x0} ,
        {0x7c, 0xff, 0x0} ,
        {0x78, 0xff, 0x0} ,
        {0x74, 0xff, 0x0} ,
        {0x70, 0xff, 0x0} ,
        {0x6c, 0xff, 0x0} ,
        {0x68, 0xff, 0x0} ,
        {0x64, 0xff, 0x0} ,
        {0x60, 0xff, 0x0} ,
        {0x5c, 0xff, 0x0} ,
        {0x58, 0xff, 0x0} ,
        {0x54, 0xff, 0x0} ,
        {0x50, 0xff, 0x0} ,
        {0x4c, 0xff, 0x0} ,
        {0x48, 0xff, 0x0} ,
        {0x44, 0xff, 0x0} ,
        {0x40, 0xff, 0x0} ,
        {0x3c, 0xff, 0x0} ,
        {0x38, 0xff, 0x0} ,
        {0x34, 0xff, 0x0} ,
        {0x30, 0xff, 0x0} ,
        {0x2c, 0xff, 0x0} ,
        {0x28, 0xff, 0x0} ,
        {0x24, 0xff, 0x0} ,
        {0x20, 0xff, 0x0} ,
        {0x1c, 0xff, 0x0} ,
        {0x18, 0xff, 0x0} ,
        {0x14, 0xff, 0x0} ,
        {0x10, 0xff, 0x0} ,
        {0xc, 0xff, 0x0} ,
        {0x8, 0xff, 0x0} ,
        {0x4, 0xff, 0x0} ,
        {0x0, 0xff, 0x0} ,
        {0x4, 0xff, 0x0} ,
        {0x8, 0xff, 0x0} ,
        {0xc, 0xff, 0x0} ,
        {0x10, 0xff, 0x0} ,
        {0x14, 0xff, 0x0} ,
        {0x18, 0xff, 0x0} ,
        {0x1c, 0xff, 0x0} ,
        {0x20, 0xff, 0x0} ,
        {0x24, 0xff, 0x0} ,
        {0x0, 0xff, 0x0} ,
        {0x0, 0xff, 0x3} ,
        {0x0, 0xff, 0x6} ,
        {0x0, 0xff, 0x9} ,
        {0x0, 0xff, 0xc} ,
        {0x0, 0xff, 0xf} ,
        {0x0, 0xff, 0x12} ,
        {0x0, 0xff, 0x15} ,
        {0x0, 0xff, 0x18} ,
        {0x0, 0xff, 0x1b} ,
        {0x0, 0xff, 0x1e} ,
        {0x0, 0xff, 0x21} ,
        {0x0, 0xff, 0x24} ,
        {0x0, 0xff, 0x27} ,
        {0x0, 0xff, 0x2a} ,
        {0x0, 0xff, 0x2d} ,
        {0x0, 0xff, 0x30} ,
        {0x0, 0xff, 0x33} ,
        {0x0, 0xff, 0x36} ,
        {0x0, 0xff, 0x39} ,
        {0x0, 0xff, 0x3c} ,
        {0x0, 0xff, 0x3f} ,
        {0x0, 0xff, 0x42} ,
        {0x0, 0xff, 0x45} ,
        {0x0, 0xff, 0x48} ,
        {0x0, 0xff, 0x4b} ,
        {0x0, 0xff, 0x4e} ,
        {0x0, 0xff, 0x51} ,
        {0x0, 0xff, 0x54} ,
        {0x0, 0xff, 0x57} ,
        {0x0, 0xff, 0x5a} ,
        {0x0, 0xff, 0x5d} ,
        {0x0, 0xff, 0x60} ,
        {0x0, 0xff, 0x63} ,
        {0x0, 0xff, 0x66} ,
        {0x0, 0xff, 0x69} ,
        {0x0, 0xff, 0x6c} ,
        {0x0, 0xff, 0x6f} ,
        {0x0, 0xff, 0x72} ,
        {0x0, 0xff, 0x75} ,
        {0x0, 0xff, 0x78} ,
        {0x0, 0xff, 0x7b} ,
        {0x0, 0xff, 0x80} ,
        {0x0, 0xff, 0x83} ,
        {0x0, 0xff, 0x86} ,
        {0x0, 0xff, 0x89} ,
        {0x0, 0xff, 0x8c} ,
        {0x0, 0xff, 0x8f} ,
        {0x0, 0xff, 0x92} ,
        {0x0, 0xff, 0x95} ,
        {0x0, 0xff, 0x98} ,
        {0x0, 0xff, 0x9b} ,
        {0x0, 0xff, 0x9e} ,
        {0x0, 0xff, 0xa1} ,
        {0x0, 0xff, 0xa4} ,
        {0x0, 0xff, 0xa7} ,
        {0x0, 0xff, 0xaa} ,
        {0x0, 0xff, 0xad} ,
        {0x0, 0xff, 0xb0} ,
        {0x0, 0xff, 0xb3} ,
        {0x0, 0xff, 0xb6} ,
        {0x0, 0xff, 0xb9} ,
        {0x0, 0xff, 0xbc} ,
        {0x0, 0xff, 0xbf} ,
        {0x0, 0xff, 0xc2} ,
        {0x0, 0xff, 0xc5} ,
        {0x0, 0xff, 0xc8} ,
        {0x0, 0xff, 0xcb} ,
        {0x0, 0xff, 0xce} ,
        {0x0, 0xff, 0xd1} ,
        {0x0, 0xff, 0xd4} ,
        {0x0, 0xff, 0xd7} ,
        {0x0, 0xff, 0xda} ,
        {0x0, 0xff, 0xdd} ,
        {0x0, 0xff, 0xe0} ,
        {0x0, 0xff, 0xe3} ,
        {0x0, 0xff, 0xe6} ,
        {0x0, 0xff, 0xe9} ,
        {0x0, 0xff, 0xec} ,
        {0x0, 0xff, 0xef} ,
        {0x0, 0xff, 0xf2} ,
        {0x0, 0xff, 0xf5} ,
        {0x0, 0xff, 0xf8} ,
        {0x0, 0xff, 0xfb} ,
        {0x0, 0xff, 0xff} ,
        {0x0, 0xfb, 0xff} ,
        {0x0, 0xf7, 0xff} ,
        {0x0, 0xf3, 0xff} ,
        {0x0, 0xef, 0xff} ,
        {0x0, 0xeb, 0xff} ,
        {0x0, 0xe7, 0xff} ,
        {0x0, 0xe3, 0xff} ,
        {0x0, 0xdf, 0xff} ,
        {0x0, 0xdb, 0xff} ,
        {0x0, 0xd7, 0xff} ,
        {0x0, 0xd3, 0xff} ,
        {0x0, 0xcf, 0xff} ,
        {0x0, 0xcb, 0xff} ,
        {0x0, 0xc7, 0xff} ,
        {0x0, 0xc3, 0xff} ,
        {0x0, 0xbf, 0xff} ,
        {0x0, 0xbb, 0xff} ,
        {0x0, 0xb7, 0xff} ,
        {0x0, 0xb3, 0xff} ,
        {0x0, 0xaf, 0xff} ,
        {0x0, 0xab, 0xff} ,
        {0x0, 0xa7, 0xff} ,
        {0x0, 0xa3, 0xff} ,
        {0x0, 0x9f, 0xff} ,
        {0x0, 0x9b, 0xff} ,
        {0x0, 0x97, 0xff} ,
        {0x0, 0x93, 0xff} ,
        {0x0, 0x8f, 0xff} ,
        {0x0, 0x8b, 0xff} ,
        {0x0, 0x87, 0xff} ,
        {0x0, 0x83, 0xff} ,
        {0x0, 0x7f, 0xff} ,
        {0x0, 0x7b, 0xff} ,
        {0x0, 0x77, 0xff} ,
        {0x0, 0x73, 0xff} ,
        {0x0, 0x6f, 0xff} ,
        {0x0, 0x6b, 0xff} ,
        {0x0, 0x67, 0xff} ,
        {0x0, 0x63, 0xff} ,
        {0x0, 0x5f, 0xff} ,
        {0x0, 0x5b, 0xff} ,
        {0x0, 0x7d, 0xff} ,
        {0x0, 0x7a, 0xff} ,
        {0x0, 0x77, 0xff} ,
        {0x0, 0x74, 0xff} ,
        {0x0, 0x71, 0xff} ,
        {0x0, 0x6e, 0xff} ,
        {0x0, 0x6b, 0xff} ,
        {0x0, 0x68, 0xff} ,
        {0x0, 0x65, 0xff} ,
        {0x0, 0x62, 0xff} ,
        {0x0, 0x5f, 0xff} ,
        {0x0, 0x5c, 0xff} ,
        {0x0, 0x59, 0xff} ,
        {0x0, 0x56, 0xff} ,
        {0x0, 0x53, 0xff} ,
        {0x0, 0x50, 0xff} ,
        {0x0, 0x4d, 0xff} ,
        {0x0, 0x4a, 0xff} ,
        {0x0, 0x47, 0xff} ,
        {0x0, 0x44, 0xff} ,
        {0x0, 0x41, 0xff} ,
        {0x0, 0x3e, 0xff} ,
        {0x0, 0x3b, 0xff} ,
        {0x0, 0x38, 0xff} ,
        {0x0, 0x35, 0xff} ,
        {0x0, 0x32, 0xff} ,
        {0x0, 0x2f, 0xff} ,
        {0x0, 0x2c, 0xff} ,
        {0x0, 0x29, 0xff} ,
        {0x0, 0x26, 0xff} ,
        {0x0, 0x23, 0xff} ,
        {0x0, 0x20, 0xff} ,
        {0x0, 0x1d, 0xff} ,
        {0x0, 0x1a, 0xff} ,
        {0x0, 0x17, 0xff} ,
        {0x0, 0x14, 0xff} ,
        {0x0, 0x11, 0xff} ,
        {0x0, 0xe, 0xff} ,
        {0x0, 0xb, 0xff} ,
        {0x0, 0x8, 0xff} ,
        {0x0, 0x5, 0xff} ,
        {0x0, 0x2, 0xff} ,
        {0x0, 0x0, 0xff} ,
        {0x2, 0x0, 0xff} ,
        {0x4, 0x0, 0xff} ,
        {0x6, 0x0, 0xff} ,
        {0x8, 0x0, 0xff} ,
        {0xa, 0x0, 0xff} ,
        {0xc, 0x0, 0xff} ,
        {0xe, 0x0, 0xff} ,
        {0x10, 0x0, 0xff} ,
        {0x12, 0x0, 0xff} ,
        {0x14, 0x0, 0xff} ,
        {0x16, 0x0, 0xff} ,
        {0x18, 0x0, 0xff} ,
        {0x1a, 0x0, 0xff} ,
        {0x1c, 0x0, 0xff} ,
        {0x1e, 0x0, 0xff} ,
        {0x20, 0x0, 0xff} ,
        {0x22, 0x0, 0xff} ,
        {0x24, 0x0, 0xff} ,
        {0x26, 0x0, 0xff} ,
        {0x28, 0x0, 0xff} ,
        {0x2a, 0x0, 0xff} ,
        {0x2c, 0x0, 0xff} ,
        {0x2e, 0x0, 0xff} ,
        {0x30, 0x0, 0xff} ,
        {0x32, 0x0, 0xff} ,
        {0x34, 0x0, 0xff} ,
        {0x36, 0x0, 0xff} ,
        {0x38, 0x0, 0xff} ,
        {0x3a, 0x0, 0xff} ,
        {0x3c, 0x0, 0xff} ,
        {0x3e, 0x0, 0xff} ,
        {0x40, 0x0, 0xff} ,
        {0x42, 0x0, 0xff} ,
        {0x44, 0x0, 0xff} ,
        {0x46, 0x0, 0xff} ,
        {0x48, 0x0, 0xff} ,
        {0x4a, 0x0, 0xff} ,
        {0x4c, 0x0, 0xff} ,
        {0x4e, 0x0, 0xff} ,
        {0x50, 0x0, 0xff} ,
        {0x52, 0x0, 0xff} ,
        {0x7d, 0x0, 0xff} ,
        {0x80, 0x0, 0xff} ,
        {0x83, 0x0, 0xff} ,
        {0x86, 0x0, 0xff} ,
        {0x89, 0x0, 0xff} ,
        {0x8c, 0x0, 0xff} ,
        {0x8f, 0x0, 0xff} ,
        {0x92, 0x0, 0xff} ,
        {0x95, 0x0, 0xff} ,
        {0x98, 0x0, 0xff} ,
        {0x9b, 0x0, 0xff} ,
        {0x9e, 0x0, 0xff} ,
        {0xa1, 0x0, 0xff} ,
        {0xa4, 0x0, 0xff} ,
        {0xa7, 0x0, 0xff} ,
        {0xaa, 0x0, 0xff} ,
        {0xad, 0x0, 0xff} ,
        {0xb0, 0x0, 0xff} ,
        {0xb3, 0x0, 0xff} ,
        {0xb6, 0x0, 0xff} ,
        {0xb9, 0x0, 0xff} ,
        {0xbc, 0x0, 0xff} ,
        {0xbf, 0x0, 0xff} ,
        {0xc2, 0x0, 0xff} ,
        {0xc5, 0x0, 0xff} ,
        {0xc8, 0x0, 0xff} ,
        {0xcb, 0x0, 0xff} ,
        {0xce, 0x0, 0xff} ,
        {0xd1, 0x0, 0xff} ,
        {0xd4, 0x0, 0xff} ,
        {0xd7, 0x0, 0xff} ,
        {0xda, 0x0, 0xff} ,
        {0xdd, 0x0, 0xff} ,
        {0xe0, 0x0, 0xff} ,
        {0xe3, 0x0, 0xff} ,
        {0xe6, 0x0, 0xff} ,
        {0xe9, 0x0, 0xff} ,
        {0xec, 0x0, 0xff} ,
        {0xef, 0x0, 0xff} ,
        {0xf2, 0x0, 0xff} ,
        {0xf5, 0x0, 0xff} ,
        {0xf8, 0x0, 0xff} ,
        {0xff, 0x0, 0xff} ,
        {0xff, 0x0, 0xfb} ,
        {0xff, 0x0, 0xf7} ,
        {0xff, 0x0, 0xf3} ,
        {0xff, 0x0, 0xef} ,
        {0xff, 0x0, 0xeb} ,
        {0xff, 0x0, 0xe7} ,
        {0xff, 0x0, 0xe3} ,
        {0xff, 0x0, 0xdf} ,
        {0xff, 0x0, 0xdb} ,
        {0xff, 0x0, 0xd7} ,
        {0xff, 0x0, 0xd3} ,
        {0xff, 0x0, 0xcf} ,
        {0xff, 0x0, 0xcb} ,
        {0xff, 0x0, 0xc7} ,
        {0xff, 0x0, 0xc3} ,
        {0xff, 0x0, 0xbf} ,
        {0xff, 0x0, 0xbb} ,
        {0xff, 0x0, 0xb7} ,
        {0xff, 0x0, 0xb3} ,
        {0xff, 0x0, 0xaf} ,
        {0xff, 0x0, 0xab} ,
        {0xff, 0x0, 0xa7} ,
        {0xff, 0x0, 0xa3} ,
        {0xff, 0x0, 0x9f} ,
        {0xff, 0x0, 0x9b} ,
        {0xff, 0x0, 0x97} ,
        {0xff, 0x0, 0x93} ,
        {0xff, 0x0, 0x8f} ,
        {0xff, 0x0, 0x8b} ,
        {0xff, 0x0, 0x87} ,
        {0xff, 0x0, 0x83} ,
        {0xff, 0x0, 0x7f} ,
        {0xff, 0x0, 0x7b} ,
        {0xff, 0x0, 0x77} ,
        {0xff, 0x0, 0x73} ,
        {0xff, 0x0, 0x6f} ,
        {0xff, 0x0, 0x6b} ,
        {0xff, 0x0, 0x67} ,
        {0xff, 0x0, 0x63} ,
        {0xff, 0x0, 0x5f} ,
        {0xff, 0x0, 0x5b} ,
        {0xff, 0x0, 0x7d} ,
        {0xff, 0x0, 0x7a} ,
        {0xff, 0x0, 0x77} ,
        {0xff, 0x0, 0x74} ,
        {0xff, 0x0, 0x71} ,
        {0xff, 0x0, 0x6e} ,
        {0xff, 0x0, 0x6b} ,
        {0xff, 0x0, 0x68} ,
        {0xff, 0x0, 0x65} ,
        {0xff, 0x0, 0x62} ,
        {0xff, 0x0, 0x5f} ,
        {0xff, 0x0, 0x5c} ,
        {0xff, 0x0, 0x59} ,
        {0xff, 0x0, 0x56} ,
        {0xff, 0x0, 0x53} ,
        {0xff, 0x0, 0x50} ,
        {0xff, 0x0, 0x4d} ,
        {0xff, 0x0, 0x4a} ,
        {0xff, 0x0, 0x47} ,
        {0xff, 0x0, 0x44} ,
        {0xff, 0x0, 0x41} ,
        {0xff, 0x0, 0x3e} ,
        {0xff, 0x0, 0x3b} ,
        {0xff, 0x0, 0x38} ,
        {0xff, 0x0, 0x35} ,
        {0xff, 0x0, 0x32} ,
        {0xff, 0x0, 0x2f} ,
        {0xff, 0x0, 0x2c} ,
        {0xff, 0x0, 0x29} ,
        {0xff, 0x0, 0x26} ,
        {0xff, 0x0, 0x23} ,
        {0xff, 0x0, 0x20} ,
        {0xff, 0x0, 0x1d} ,
        {0xff, 0x0, 0x1a} ,
        {0xff, 0x0, 0x17} ,
        {0xff, 0x0, 0x14} ,
        {0xff, 0x0, 0x11} ,
        {0xff, 0x0, 0xe} ,
        {0xff, 0x0, 0xb} ,
        {0xff, 0x0, 0x8} ,
        {0xff, 0x0, 0x5} ,
        {0xff, 0x0, 0x2}
    }
};

void get_colors(rgb *vec, state s) {
    uint now = (uint) time(NULL);
    now = (now * (uint) (s + 5)) % 504;
    vec->r = rgbvals.vals[now].r;
    vec->g = rgbvals.vals[now].g;
    vec->b = rgbvals.vals[now].b;
}

void compute_next_state(uint rows, uint cols, cell_t cs[rows][cols]){
    uint ct;
    uint prevrow;
    uint nextrow;
    uint prevcol;
    uint nextcol;
    for (uint i = 0; i < rows; ++i) {
        for (uint j = 0; j < cols; ++j) {
            ct = 0;
            prevrow = (i + rows - 1) % rows;
            nextrow = (i + rows + 1) % rows;
            prevcol = (j + cols - 1) % cols;
            nextcol = (j + cols + 1) % cols;
            /* UL */
            if (cs[prevrow][prevcol].s >> 1) ct++;
            /* U */
            if (cs[prevrow][j].s >> 1) ct++;
            /* UR */
            if (cs[prevrow][nextcol].s >> 1) ct++;
            /* L */
            if (cs[i][prevcol].s >> 1) ct++;
            /* R */
            if (cs[i][nextcol].s >> 1) ct++;
            /* BL */
            if (cs[nextrow][prevcol].s >> 1) ct++;
            /* B */
            if (cs[nextrow][j].s >> 1) ct++;
            /* BR */
            if (cs[nextrow][nextcol].s >> 1) ct++;

            switch (cs[i][j].s) {
            case DOOMED:
            case DEAD:
                if (ct == 3){
                    cs[i][j].s_next = BORN;
                } else {
                    cs[i][j].s_next = DEAD;
                }
                break;
            case BORN:
            case ALIVE:
                if (ct < 2 || ct > 3) {
                    cs[i][j].s_next = DOOMED;
                } else {
                    cs[i][j].s_next = ALIVE;
                }
                break;
            }
        }
    }
}

void update_state_cells(uint rows, uint cols, cell_t cs[rows][cols]) {
    for (uint i = 0; i < rows; ++i) {
        for (uint j = 0; j < cols; ++j) {
            cs[i][j].s = cs[i][j].s_next;
        }
    }
}


void display(cell_t *c) {
    rgb vec;
    get_colors(&vec, c->s);
    switch (c->s) {
    case DOOMED:
        print_fancy(vec.r, vec.g, vec.b, ".");
        break;
    case DEAD:
        printf(" ");
        break;
    case BORN:
        print_fancy(vec.r, vec.g, vec.b, "o");
        break;
    case ALIVE:
        print_fancy(vec.r, vec.g, vec.b, "O");
        break;
    }

}

void display_cells(uint rows, uint cols, cell_t cells[rows][cols]) {
    /* Get current window size */
    winsize_t ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    /* Use min(rows,rs), resp cols,cls */
    uint rs = ws.ws_row;
    uint cls = ws.ws_col;
    if (rs > rows) rs = rows;
    if (cls > cols) cls = cols;

    for (uint i = 0; i < rs; ++i) {
        for (uint j = 0; j < cls; ++j) {
            display(&cells[i][j]);
        }
        /* if the window size has grown we want to pad each row with whitespace */
        for (uint j = cls; j < ws.ws_col; ++j) {
            fprintf(stdout, " ");
        }
    }
    for (uint i = rs; i < ws.ws_row; ++i){
        for (uint j = 0; j < ws.ws_col; ++j){
            fprintf(stdout, " ");
        }
    }

    /* set cursor to top left */
    printf("\033[0;0H");

}

void int_handler(int sig) {
    /* Erase display */
    printf("\n");
    printf("\e[2J");

    /* Restore cursor */
    printf("\e[?25h");
    exit(sig);
}

int main()
{
    srand(time(NULL));
    winsize_t ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    uint rows = ws.ws_row;
    uint cols = ws.ws_col;
    cell_t cells[rows][cols];
    for (uint i = 0; i < rows; ++i) {
        for (uint j = 0; j < cols; ++j) {
            cells[i][j].s = (rand() % 12 == 0) ? ALIVE : DEAD;
            cells[i][j].s_next = DEAD;
        }
    }

    /* Hide cursor */
    printf("\e[?25l");

    signal(SIGINT, int_handler);
    while (1) {
        display_cells(rows, cols, cells);
        compute_next_state(rows, cols, cells);
        update_state_cells(rows, cols, cells);
        usleep(150000);
    }
    return 0;
}
