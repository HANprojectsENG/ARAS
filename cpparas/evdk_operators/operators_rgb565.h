/******************************************************************************
 * Project    : Embedded Vision Design
 * Copyright  : 2019 HAN Electrical and Electronic Engineering
 * Author     : Hugo Arends
 *
 * Description: Header file for RGB565 image processing operators
 *
 * Copyright (C) 2019 HAN University of Applied Sciences. All Rights Reserved.
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
 ******************************************************************************
  Change History:

    Version 1.0 - November 2017
    > Initial revision

    Version 2.0 - September 2019
    > Updated for EVDK3.0

******************************************************************************/
#ifndef _OPERATORS_RGB565_H_
#define _OPERATORS_RGB565_H_

#include "operators.h"

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

void contrastStretch_rgb565( const image_t *src
                           ,       image_t *dst
                           , const rgb565_pixel_t bottom
                           , const rgb565_pixel_t top
                           );

void threshold_rgb565( const image_t *src
                     ,       image_t *dst
                     , const rgb565_pixel_t low
                     , const rgb565_pixel_t high
                     );

void erase_rgb565( const image_t *img );

void copy_rgb565( const image_t *src, image_t *dst );

#endif // _OPERATORS_RGB565_H_
// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
