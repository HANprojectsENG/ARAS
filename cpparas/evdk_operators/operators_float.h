/******************************************************************************
 * Project    : Embedded Vision Design
 * Copyright  : 2019 HAN Electrical and Electronic Engineering
 * Author     : Hugo Arends
 *
 * Description: Header file for float image processing operators
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
#ifndef _OPERATORS_FLOAT_H_
#define _OPERATORS_FLOAT_H_

#include "operators.h"

// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

void contrastStretch_float( const image_t *src
                          ,       image_t *dst
                          , const float_pixel_t bottom
                          , const float_pixel_t top
                          );

void threshold_float( const image_t *src
                    ,       image_t *dst
                    , const float_pixel_t low
                    , const float_pixel_t high
                    );

void erase_float( const image_t *img );

void copy_float( const image_t *src, image_t *dst );

void setSelectedToValue_float( const image_t *src
                             ,       image_t *dst
                             , const float_pixel_t selected
                             , const float_pixel_t value
                             );

#endif // _OPERATORS_FLOAT_H_
// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
