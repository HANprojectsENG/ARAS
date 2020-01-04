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

const uint8_t _font_simple6pt_cheight = 6;
const uint8_t _font_simple6pt_offset = 0x30;

// clang-format off
const image_t _font_simple6pt_characters[] = {
    /*ASCII 0x30*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x31*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x32*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x33*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x34*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x35*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x36*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x37*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x38*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x39*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3A*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3B*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3C*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3D*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3E*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x3F*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x40*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x41*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x42*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x43*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x44*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x45*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x46*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x47*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 0, 1, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x48*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x49*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x4A*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x4B*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 0, 1, 0, 0,
        1, 1, 0, 0, 0,
        1, 0, 1, 0, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x4C*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x4D*/
    {6, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 0, 1, 0,
        1, 1, 0, 1, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x4E*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 1, 0, 1, 0,
        1, 0, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x4F*/
    {6, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x50*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x51*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 1, 0, 0,
        0, 1, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x52*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x53*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        0, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 1, 0,
        1, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x54*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x55*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x56*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 1, 0,
        1, 0, 1, 0,
        1, 0, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x57*/
    {6, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x58*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
    }, },
    /*ASCII 0x59*/
    {4, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 0, 1, 0,
        1, 0, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
    }, },
    /*ASCII 0x5A*/
    {5, _font_simple6pt_cheight, IMGVIEW_BINARY, IMGTYPE_BASIC, (uint8_t []){
        1, 1, 1, 1, 0,
        0, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
    }, },
};
// clang-format on

const font_t _font_simple6pt = {
    _font_simple6pt_offset, sizeof(_font_simple6pt_characters) / sizeof(image_t), 0x40,
    (image_t*)_font_simple6pt_characters
};

const font_t* font_simple6pt = &_font_simple6pt;
