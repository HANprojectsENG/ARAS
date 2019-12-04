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
#include "operators_rgb888.h"
#include "math.h"

#ifdef STM32F746xx
#include "mem_manager.h"
#endif

// ----------------------------------------------------------------------------
// Function implementations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* newRGB888Image(const uint32_t cols, const uint32_t rows)
{
    image_t* img = (image_t*)malloc(sizeof(image_t));
    if (img == NULL) {
        // Unable to allocate memory for new image
        return NULL;
    }

#ifdef STM32F746xx
    img->data = mem_manager_alloc();
#else
    img->data = (uint8_t*)malloc((rows * cols) * sizeof(rgb888_pixel_t));
#endif

    if (img->data == NULL) {
        // Unable to allocate memory for data
        free(img);
        return NULL;
    }

    img->cols = cols;
    img->rows = rows;
    img->view = IMGVIEW_CLIP;
    img->type = IMGTYPE_RGB888;
    return (img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
image_t* toRGB888Image(image_t* src)
{

    image_t* dst = newRGB888Image(src->cols, src->rows);
    if (dst == NULL)
        return NULL;

    convertToRGB888Image(src, dst);

    return dst;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void deleteRGB888Image(image_t* img)
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
void convertToRGB888Image(const image_t* src, image_t* dst)
{
    register long int i = src->rows * src->cols;
    register rgb888_pixel_t* d = (rgb888_pixel_t*)dst->data;

    dst->view = src->view;
    dst->cols = src->cols;
    dst->rows = src->rows;
    dst->view = src->view;

    switch (src->type) {
    case IMGTYPE_BASIC: {
        basic_pixel_t* s = (basic_pixel_t*)src->data;
        // Loop all pixels and copy all channels with same value
        while (i-- > 0) {
            d->r = *s;
            d->g = *s;
            d->b = *s;

            s++;
            d++;
        }

    } break;
    case IMGTYPE_INT16: {
        // TODO

    } break;
    case IMGTYPE_FLOAT: {
        // TODO

    } break;
    case IMGTYPE_RGB888: {
        copy_rgb888(src, dst);

    } break;
    default:
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void contrastStretch_rgb888(const image_t* src,
    image_t* dst,
    const rgb888_pixel_t bottom,
    const rgb888_pixel_t top)
{
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
void erase_rgb888(const image_t* img)
{
    register long int i = img->rows * img->cols;
    register rgb888_pixel_t* s = (rgb888_pixel_t*)img->data;

    // Loop through the image and set all pixels to the value 0
    while (i-- > 0) {
        s->r = 0;
        s->g = 0;
        s->b = 0;

        s++;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void threshold_rgb888(const image_t* src,
    image_t* dst,
    const rgb888_pixel_t low,
    const rgb888_pixel_t high)
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
void copy_rgb888(const image_t* src, image_t* dst)
{
    register long int i = src->rows * src->cols;
    register rgb888_pixel_t* s = (rgb888_pixel_t*)src->data;
    register rgb888_pixel_t* d = (rgb888_pixel_t*)dst->data;

    dst->rows = src->rows;
    dst->cols = src->cols;
    dst->type = src->type;
    dst->view = src->view;

    // Loop all pixels and copy
    while (i-- > 0)
        *d++ = *s++;
}

static inline float affineTransformX(float x, float y, float warpMatrix[2][3])
{
    return warpMatrix[0][0] * x + warpMatrix[0][1] * y + warpMatrix[0][2];
}
static inline float affineTransformY(float x, float y, float warpMatrix[2][3])
{
    return warpMatrix[1][0] * x + warpMatrix[1][1] * y + warpMatrix[1][2];
}

// ----------------------------------------------------------------------------
// Custom operators
// ----------------------------------------------------------------------------
void warp_rgb888(const image_t* img, image_t* dst, int32_t colpos[4], int32_t rowpos[4])
{
    // Stage one - rotate, scale and translate based on the first two corners.
    float angleSrc = atan2(rowpos[1] - rowpos[0], colpos[1] - colpos[0]);
    int32_t xdiff = colpos[1] - colpos[0];
    int32_t ydiff = rowpos[1] - rowpos[0];
    float lengthSrc = sqrt(xdiff * xdiff + ydiff * ydiff);
    float lengthDst = dst->cols;

    float angle = -angleSrc;
    float scale = lengthDst / lengthSrc;
    float warpMatrixStageOne[2][3] = {
        { cos(angle) * scale, -sin(angle) * scale, 0.0f },
        { sin(angle) * scale, cos(angle) * scale, 0.0f }
    };
    float offsetX = -affineTransformX(colpos[0], rowpos[0], warpMatrixStageOne);
    float offsetY = -affineTransformY(colpos[0], rowpos[0], warpMatrixStageOne);
    warpMatrixStageOne[0][2] = offsetX;
    warpMatrixStageOne[1][2] = offsetY;

    // Stage two - adjust X and Y scale based on third corner.
    float newScaleX = scale * ((float)dst->cols / affineTransformX(colpos[2], rowpos[2], warpMatrixStageOne));
    float newScaleY = scale * ((float)dst->rows / affineTransformY(colpos[2], rowpos[2], warpMatrixStageOne));
    float newOffsetX = offsetX * (newScaleX / scale);
    float newOffsetY = offsetY * (newScaleY / scale);
    float warpMatrixStageTwo[2][3] = {
        { cos(angle) * newScaleX, -sin(angle) * newScaleX, newOffsetX },
        { sin(angle) * newScaleY, cos(angle) * newScaleY, newOffsetY }
    };

    warpAffine_rgb888(img, dst, warpMatrixStageTwo);
}

void warpAffine_rgb888(const image_t* img, image_t* dst, float warpMatrix[2][3])
{
    float maxFactor = warpMatrix[0][0];
    if (warpMatrix[0][1] > maxFactor)
        maxFactor = warpMatrix[0][1];
    if (warpMatrix[1][0] > maxFactor)
        maxFactor = warpMatrix[1][0];
    if (warpMatrix[1][1] > maxFactor)
        maxFactor = warpMatrix[1][1];
    int32_t maxPxSize = (int32_t)ceil(maxFactor * 2.0f);

    for (int32_t row = 0; row < img->rows; row++) {
        for (int32_t col = 0; col < img->cols; col++) {
            int32_t newCol = affineTransformX(col, row, warpMatrix);
            int32_t newRow = affineTransformY(col, row, warpMatrix);
            for (int32_t wRow = newRow; wRow < newRow + maxPxSize; wRow++) {
                for (int32_t wCol = newCol; wCol < newCol + maxPxSize; wCol++) {
                    if (wRow < 0 || wRow >= dst->rows
                        || wCol < 0 || wCol >= dst->cols) {
                        continue;
                    } else {
                        setRGB888Pixel(dst, wCol, wRow, getRGB888Pixel((image_t*)img, col, row));
                    }
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void scaleImage_rgb888(const image_t* src, image_t* dst)
{
    float scaleFactorX = (float)src->cols / (float)dst->cols;
    float scaleFactorY = (float)src->rows / (float)dst->rows;

    for (int row = 0; row < dst->rows; row++) {
        for (int col = 0; col < dst->cols; col++) {
            int srcCol = (int)((float)col * scaleFactorX);
            int srcRow = (int)((float)row * scaleFactorY);
            setRGB888Pixel(dst, col, row, getRGB888Pixel(src, srcCol, srcRow));
        }
    }
}

// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
