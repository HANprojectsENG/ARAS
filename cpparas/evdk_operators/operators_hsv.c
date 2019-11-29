/******************************************************************************
 * Project    : Embedded Vision Design
 * Copyright  : 2019 HAN Electrical and Electronic Engineering
 * Author     : Hugo Arends
 *
 * Description: Implementation file for RGB888 image processing operators
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
#include "operators_hsv.h"
#include "math.h"

#ifdef STM32F746xx
#include "mem_manager.h"
#endif

// ----------------------------------------------------------------------------
// Function implementations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* newHSVImage(const uint32_t cols, const uint32_t rows)
{
    image_t* img = (image_t*)malloc(sizeof(image_t));
    if (img == NULL) {
        // Unable to allocate memory for new image
        return NULL;
    }

#ifdef STM32F746xx
    img->data = mem_manager_alloc();
#else
    img->data = (uint8_t*)malloc((rows * cols) * sizeof(hsv_pixel_t));
#endif

    if (img->data == NULL) {
        // Unable to allocate memory for data
        free(img);
        return NULL;
    }

    img->cols = cols;
    img->rows = rows;
    img->view = IMGVIEW_CLIP;
    img->type = IMGTYPE_HSV;
    return (img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* toHSVImage(image_t* src)
{

    image_t* dst = newHSVImage(src->cols, src->rows);
    if (dst == NULL)
        return NULL;

    convertToHSVImage(src, dst);

    return dst;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void deleteHSVImage(image_t* img)
{
#ifdef STM32F746xx
    mem_manager_free(img->data);
#else
    free(img->data);
#endif

    free(img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void convertToHSVImage(const image_t* src, image_t* dst)
{
    //to do
    register long int i = src->rows * src->cols;
    register hsv_pixel_t* d = (hsv_pixel_t*)dst->data;

    dst->view = src->view;
    dst->cols = src->cols;
    dst->rows = src->rows;
    dst->view = src->view;

    switch (src->type) {
    case IMGTYPE_BASIC: {
        // TODO

    } break;
    case IMGTYPE_INT16: {
        // TODO

    } break;
    case IMGTYPE_FLOAT: {
        // TODO

    } break;
    case IMGTYPE_RGB888: {
        // TODO
        rgb888_pixel_t* s = (rgb888_pixel_t*)src->data;
        // Loop all pixels, convert and copy
        //Formulas taken from https://www.rapidtables.com/convert/color/rgb-to-hsv.html
        while (i-- > 0) {
            unsigned char r = s->r;
            unsigned char g = s->g;
            unsigned char b = s->b;

            double min, max, delta;

            //Change R,G,B ranges from 0-255 to 0-1
            double r_ = (double)r/255;  
            double g_ = (double)g/255;
            double b_ = (double)b/255;

            //find max and min values between R,G,B
            max = ((r_ > g_ ? r_ : g_) > b_ ? (r_ > g_ ? r_ : g_) : b_);
            min = ((r_ < g_ ? r_ : g_) < b_ ? (r_ < g_ ? r_ : g_) : b_);
            delta = max - min;
            

            //Calculate Hue
            if (max == r_){
                d->h = (fmod(((g_ - b_) / delta), 6.0)) * 60;
            }
            else if (max == g_ ){
                d->h = (((b_ - r_) / delta) + 2.0) * 60;
            }
            else{
                d->h = (((r_ - g_) / delta) + 4.0) * 60;
            }

            
            if (d->h > 360){
                d->h = 0 - d->h;
            }

            //Calculate Saturation
            if (max == 0.0){
                d->s = 0;
            }
            else{
                d->s = ((delta / max) * 100);
            }

            //Calculate Value
            d->v = (max * 100);

            d++;
            s++;
        }

    } break;
    default:
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void erase_hsv(const image_t* img)
{
    register long int i = img->rows * img->cols;
    register hsv_pixel_t* s = (hsv_pixel_t*)img->data;

    // Loop through the image and set all pixels to the value 0
    while (i-- > 0) {
        s->h = 0;
        s->s = 0;
        s->v = 0;

        s++;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void threshold_hsv(const image_t* src,
    image_t* dst,
    const hsv_pixel_t low,
    const hsv_pixel_t high)
{
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)low;
    (void)high;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void copy_hsv(const image_t* src, image_t* dst)
{
    register long int i = src->rows * src->cols;
    register hsv_pixel_t* s = (hsv_pixel_t*)src->data;
    register hsv_pixel_t* d = (hsv_pixel_t*)dst->data;

    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->type = src->type;
    dst->view = src->view;

    // Loop all pixels and copy
    while (i-- > 0)
        *d++ = *s++;
}


// ----------------------------------------------------------------------------
// Custom operators
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
