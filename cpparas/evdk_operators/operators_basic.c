/******************************************************************************
 * Project    : Embedded Vision Design
 * Copyright  : 2019 HAN Electrical and Electronic Engineering
 * Author     : Hugo Arends
 *
 * Description: Implementation file for basic image processing operators
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

#include "operators_basic.h"
#include "math.h"

#ifdef STM32F746xx
#include "mem_manager.h"
#endif

// ----------------------------------------------------------------------------
// Function implementations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* newBasicImage(const uint32_t cols, const uint32_t rows)
{
    image_t* img = (image_t*)malloc(sizeof(image_t));
    if (img == NULL) {
        // Unable to allocate memory for new image
        return NULL;
    }

#ifdef STM32F746xx
    img->data = mem_manager_alloc();
#else
    img->data = (uint8_t*)malloc((rows * cols) * sizeof(basic_pixel_t));
#endif

    if (img->data == NULL) {
        // Unable to allocate memory for data
        free(img);
        return NULL;
    }

    img->cols = cols;
    img->rows = rows;
    img->view = IMGVIEW_CLIP;
    img->type = IMGTYPE_BASIC;
    return (img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* toBasicImage(image_t* src)
{
    image_t* dst = newBasicImage(src->cols, src->rows);
    if (dst == NULL)
        return NULL;

    convertToBasicImage(src, dst);

    return dst;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void deleteBasicImage(image_t* img)
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
void convertToBasicImage(const image_t* src, image_t* dst)
{
    register long int i = src->rows * src->cols;
    register basic_pixel_t* d = (basic_pixel_t*)dst->data;

    dst->view = src->view;
    dst->cols = src->cols;
    dst->rows = src->rows;
    dst->view = src->view;

    switch (src->type) {
    case IMGTYPE_BASIC: {
        copy_basic(src, dst);

    } break;
    case IMGTYPE_INT16: {
        int16_pixel_t* s = (int16_pixel_t*)src->data;
        // Loop all pixels and copy
        while (i-- > 0)
            *d++ = (basic_pixel_t)(*s++);

    } break;
    case IMGTYPE_FLOAT: {
        float_pixel_t* s = (float_pixel_t*)src->data;
        // Loop all pixels and copy
        while (i-- > 0)
            *d++ = (basic_pixel_t)(*s++);

    } break;
    case IMGTYPE_RGB888: {
        rgb888_pixel_t* s = (rgb888_pixel_t*)src->data;
        // Loop all pixels, convert and copy
        while (i-- > 0) {
            unsigned char r = s->r;
            unsigned char g = s->g;
            unsigned char b = s->b;

            *d++ = (basic_pixel_t)(0.212671f * r + 0.715160f * g + 0.072169f * b);
            s++;
        }

    } break;
    case IMGTYPE_HSV: {
        // ToDo

    } break;
    default:
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void contrastStretch_basic(const image_t* src, image_t* dst, const basic_pixel_t bottom, const basic_pixel_t top)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)bottom;
    (void)top;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void contrastStretchFast_basic(const image_t* src, image_t* dst)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Rotation
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void rotate180_basic(const image_t* img)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;

#ifdef STM32F746xx
    // Target specific (assembly) implementation goes here
#else
    // Default implementation
#endif

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Thresholding
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void threshold_basic(const image_t* src, image_t* dst, const basic_pixel_t low, const basic_pixel_t high)
{
    int i;
    int x;
    basic_pixel_t pixel;
    for (x = 0; x < src->rows; x++) {
        for (i = 0; i < src->cols; i++) {
            pixel = getBasicPixel(src, i, x);
            if ((pixel >= low) && (pixel <= high)) {
                setBasicPixel(dst, i, x, (basic_pixel_t)0);
            } else {
                setBasicPixel(dst, i, x, (basic_pixel_t)255);
            }
        }
    }
    (void)src;
    (void)dst;
    (void)low;
    (void)high;
    return;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void threshold2Means_basic(const image_t* src, image_t* dst, const eBrightness brightness)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)brightness;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void thresholdOtsu_basic(const image_t* src, image_t* dst, const eBrightness brightness)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)brightness;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Miscellaneous
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void erase_basic(const image_t* img)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void copy_basic(const image_t* src, image_t* dst)
{
    register long int i = src->rows * src->cols;
    register basic_pixel_t* s = (basic_pixel_t*)src->data;
    register basic_pixel_t* d = (basic_pixel_t*)dst->data;

    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->type = src->type;
    dst->view = src->view;

    // Loop all pixels and copy
    while (i-- > 0)
        *d++ = *s++;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void setSelectedToValue_basic(const image_t* src,
    image_t* dst,
    const basic_pixel_t selected,
    const basic_pixel_t value)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)selected;
    (void)value;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t neighbourCount_basic(const image_t* img,
    const int32_t c,
    const int32_t r,
    const basic_pixel_t pixel,
    const eConnected connected)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;
    (void)c;
    (void)r;
    (void)pixel;
    (void)connected;

    return 0;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void histogram_basic(const image_t* img, uint16_t* hist)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;
    (void)hist;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Arithmetic
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void add_basic(const image_t* src, image_t* dst)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t sum_basic(const image_t* img)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;

    return 0;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void multiply_basic(const image_t* src, image_t* dst)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void invert_basic(const image_t* src, image_t* dst)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Filters
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void nonlinearFilter_basic(const image_t* src, image_t* dst, const eFilterOperation fo, const uint8_t n)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)fo;
    (void)n;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Binary
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void removeBorderBlobs_basic(const image_t* src, image_t* dst, const eConnected connected)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)connected;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void fillHoles_basic(const image_t* src, image_t* dst, const eConnected connected)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)connected;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t labelBlobs_basic(const image_t* src, image_t* dst, const eConnected connected)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)connected;

    return 0;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void binaryEdgeDetect_basic(const image_t* src, image_t* dst, const eConnected connected)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)src;
    (void)dst;
    (void)connected;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Analysis
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void blobAnalyse_basic(const image_t* img, const uint8_t blobnr, blobinfo_t* blobInfo)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;
    (void)blobnr;
    (void)blobInfo;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void centroid_basic(const image_t* img, const uint8_t blobnr, int32_t* cc, int32_t* rc)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;
    (void)blobnr;
    (void)cc;
    (void)rc;

    return;
    // ********************************************
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
float normalizedCentralMoments_basic(const image_t* img, const uint8_t blobnr, const int32_t p, const int32_t q)
{

    // Not yet implemented
    // ********************************************
    // Added to prevent compiler warnings
    // Remove these when implementation starts
    (void)img;
    (void)blobnr;
    (void)p;
    (void)q;

    return 0.0f;
    // ********************************************
}

// ----------------------------------------------------------------------------
// Custom operators
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void scaleImage_basic(const image_t* src, image_t* dst)
{
    float scaleFactorX = (float)src->cols / (float)dst->cols;
    float scaleFactorY = (float)src->rows / (float)dst->rows;

    for (int row = 0; row < dst->rows; row++) {
        for (int col = 0; col < dst->cols; col++) {
            int srcCol = (int)((float)col * scaleFactorX);
            int srcRow = (int)((float)row * scaleFactorY);
            setBasicPixel(dst, col, row, getBasicPixel(src, srcCol, srcRow));
        }
    }
}

void crop_basic(const image_t* img, image_t* dst, uint32_t top_left[2], uint32_t bottom_right[2])
{
    //Gotta check every check to make sure we are checked!
    if ((top_left[0] < img->cols) && (top_left[1] < img->rows) && 
        (bottom_right[0] < img->cols) && (bottom_right[1] < img->rows) && 
        (top_left[0] || bottom_right[0]) && (top_left[1] || bottom_right[1]))
    {
        dst->cols = bottom_right[0] - top_left[0]; 
        dst->rows = bottom_right[1] - top_left[1];  
        dst->type = img->type; 

        for (uint32_t i = 0; i < dst->rows; i++)
        {
            for (uint32_t j = 0; j < dst->cols; j++)
            {
                setBasicPixel(dst, j, i, getBasicPixel(img, top_left[0] + j, top_left[1] + i));
            }
        }
    }
}

// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
