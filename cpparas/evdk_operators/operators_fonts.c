/******************************************************************************
 * Project    : Embedded Vision Design
 * Author     : Casper Uiterwijk
 *
 * Description: Source file for simple bitmap fonts
 *
 * Copyright (C) 2019 Casper Uiterwijk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
******************************************************************************/
#include "operators_fonts.h"

const uint8_t _font_simple6pt_cwidth = 5;
const uint8_t _font_simple6pt_cheight = 6;
const uint8_t _font_simple6pt_offset = 0x30;
const uint8_t _font_simple6pt_data[] = {
    /*ASCII 0x30*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x31*/
    0, 1, 1, 0, 0,
    1, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x32*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x33*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x34*/
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x35*/
    1, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x36*/
    0, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x37*/
    1, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 0, 0,
    0, 1, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x38*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x39*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3A*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3B*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3C*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3D*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3E*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x3F*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x40*/
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x41*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x42*/
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x43*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 0, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x44*/
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x45*/
    1, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x46*/
    1, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 0, 0,
    1, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x47*/
    0, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    1, 0, 1, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x48*/
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x49*/
    1, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4A*/
    1, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4B*/
    1, 0, 0, 1, 0,
    1, 0, 1, 0, 0,
    1, 1, 0, 0, 0,
    1, 0, 1, 0, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4C*/
    1, 0, 0, 0, 0,
    1, 0, 0, 0, 0,
    1, 0, 0, 0, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4D*/
    1, 1, 1, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4E*/
    1, 0, 0, 1, 0,
    1, 1, 0, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x4F*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x50*/
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 0, 0,
    1, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x51*/
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 1, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x52*/
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x53*/
    0, 1, 1, 1, 0,
    1, 0, 0, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 1, 0,
    1, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x54*/
    1, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x55*/
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x56*/
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x57*/
    1, 0, 0, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 1, 1, 0,
    1, 0, 1, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x58*/
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    1, 0, 0, 1, 0,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x59*/
    1, 0, 0, 1, 0,
    0, 1, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,
    /*ASCII 0x5A*/
    1, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 0, 0,
    1, 0, 0, 0, 0,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
};

#define CHARACTER_IMAGE(idx) \
    {_font_simple6pt_cwidth, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t *)&_font_simple6pt_data[idx * _font_simple6pt_cheight * _font_simple6pt_cwidth]}


const image_t _font_simple6pt_characters[] = {
    CHARACTER_IMAGE(0x00),
    CHARACTER_IMAGE(0x01),
    CHARACTER_IMAGE(0x02),
    CHARACTER_IMAGE(0x03),
    CHARACTER_IMAGE(0x04),
    CHARACTER_IMAGE(0x05),
    CHARACTER_IMAGE(0x06),
    CHARACTER_IMAGE(0x07),
    CHARACTER_IMAGE(0x08),
    CHARACTER_IMAGE(0x09),
    CHARACTER_IMAGE(0x0A),
    CHARACTER_IMAGE(0x0B),
    CHARACTER_IMAGE(0x0C),
    CHARACTER_IMAGE(0x0D),
    CHARACTER_IMAGE(0x0E),
    CHARACTER_IMAGE(0x0F),
    CHARACTER_IMAGE(0x10),
    CHARACTER_IMAGE(0x11),
    CHARACTER_IMAGE(0x12),
    CHARACTER_IMAGE(0x13),
    CHARACTER_IMAGE(0x14),
    CHARACTER_IMAGE(0x15),
    CHARACTER_IMAGE(0x16),
    CHARACTER_IMAGE(0x17),
    CHARACTER_IMAGE(0x18),
    CHARACTER_IMAGE(0x19),
    CHARACTER_IMAGE(0x1A),
    CHARACTER_IMAGE(0x1B),
    CHARACTER_IMAGE(0x1C),
    CHARACTER_IMAGE(0x1D),
    CHARACTER_IMAGE(0x1E),
    CHARACTER_IMAGE(0x1F),
    CHARACTER_IMAGE(0x20),
    CHARACTER_IMAGE(0x21),
    CHARACTER_IMAGE(0x22),
    CHARACTER_IMAGE(0x23),
    CHARACTER_IMAGE(0x24),
    CHARACTER_IMAGE(0x25),
    CHARACTER_IMAGE(0x26),
    CHARACTER_IMAGE(0x27),
    CHARACTER_IMAGE(0x28),
    CHARACTER_IMAGE(0x29),
    CHARACTER_IMAGE(0x2A),
};

const font_t _font_simple6pt = {
    _font_simple6pt_offset, sizeof(_font_simple6pt_characters) / sizeof(image_t), 0x40,
    (image_t *)_font_simple6pt_characters
};

const font_t* font_simple6pt = &_font_simple6pt;
