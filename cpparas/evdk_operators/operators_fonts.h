/******************************************************************************
 * Project    : Embedded Vision Design
 * Author     : Casper Uiterwijk
 *
 * Description: Header file for simple bitmap fonts
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
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _OPERATORS_FONTS_H_
#define _OPERATORS_FONTS_H_

#include "operators.h"

// A 5x6 character cell font with only uppercase alphanumeric characters.
extern const font_t* font_simple6pt;

#endif // _OPERATORS_FONTS_H_

#ifdef __cplusplus
}
#endif
