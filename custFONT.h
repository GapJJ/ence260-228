/** @file    custFONT.h
    @author  fontgen
    @date    10 Oct 2020

    @defgroup custFONT  Here's a demo font of three faces.

*/

#ifndef CUSTFONT_H_
#define CUSTFONT_H_

#define CUSTFONT_WIDTH 5
#define CUSTFONT_HEIGHT 7
#define CUSTFONT_OFFSET 80
#define CUSTFONT_SIZE 4

#ifndef FONT_WIDTH
#define FONT_WIDTH 5
#endif
#ifndef FONT_HEIGHT
#define FONT_HEIGHT 7
#endif
#ifndef FONT_OFFSET
#define FONT_OFFSET 80
#endif
#ifndef FONT_SIZE_MAX
#define FONT_SIZE_MAX 4
#endif
#include "font.h"

static font_t custFONT =
{
    .flags = 1, /* (packed)  */
    .width = 5,
    .height = 7,
    .offset = 80,
    .size = 4,
    .bytes = 5,
    .data =
    {
        /* P  */
        0xc0, 0x39, 0xe7, 0x1c, 0x00,
        /* Q  */
        0x00, 0x00, 0x00, 0x00, 0x00,
        /* R  */
        0x00, 0x18, 0xe7, 0x00, 0x00,
        /* S  */
        0x51, 0x11, 0x63, 0x00, 0x00,
    }
};
#endif  /* CUSTFONT_H_  */
