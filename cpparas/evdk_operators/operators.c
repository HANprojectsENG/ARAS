/******************************************************************************
 * Project    : Embedded Vision Design
 * Copyright  : 2019 HAN Electrical and Electronic Engineering
 * Author     : Hugo Arends
 *
 * Description: Implementation file for image processing operators
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
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "operators.h"
#include "operators_basic.h"
#include "operators_float.h"
#include "operators_int16.h"
#include "operators_rgb888.h"

// ----------------------------------------------------------------------------
// Function implementations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Pixel manipulation
// ----------------------------------------------------------------------------

inline void setBasicPixel(image_t* img, int32_t c, int32_t r, basic_pixel_t value)
{
    *((basic_pixel_t*)(img->data) + (r * img->cols + c)) = value;
}

inline basic_pixel_t getBasicPixel(const image_t* img, int32_t c, int32_t r)
{
    return (*((basic_pixel_t*)(img->data) + (r * img->cols + c)));
}

inline void setInt16Pixel(image_t* img, int32_t c, int32_t r, int16_pixel_t value)
{
    *((int16_pixel_t*)(img->data) + (r * img->cols + c)) = value;
}

inline int16_pixel_t getInt16Pixel(image_t* img, int32_t c, int32_t r)
{
    return (*((int16_pixel_t*)(img->data) + (r * img->cols + c)));
}

inline void setFloatPixel(image_t* img, int32_t c, int32_t r, float_pixel_t value)
{
    *((float_pixel_t*)(img->data) + (r * img->cols + c)) = value;
}

inline float_pixel_t getFloatPixel(image_t* img, int32_t c, int32_t r)
{
    return (*((float_pixel_t*)(img->data) + (r * img->cols + c)));
}

inline void setRGB888Pixel(image_t* img, int32_t c, int32_t r, rgb888_pixel_t value)
{
    *((rgb888_pixel_t*)(img->data) + (r * img->cols + c)) = value;
}

inline rgb888_pixel_t getRGB888Pixel(image_t* img, int32_t c, int32_t r)
{
    return (*((rgb888_pixel_t*)(img->data) + (r * img->cols + c)));
}

// ----------------------------------------------------------------------------
// Image creation
// ----------------------------------------------------------------------------

void deleteImage(image_t* img)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        deleteBasicImage(img);
        break;
    case IMGTYPE_INT16:
        deleteInt16Image(img);
        break;
    case IMGTYPE_FLOAT:
        deleteFloatImage(img);
        break;
    case IMGTYPE_RGB888:
        deleteRGB888Image(img);
        break;
    default:
        fprintf(stderr, "deleteImage(): image type %d not supported\n", img->type);
        break;
    }
}

void convertImage(const image_t* src, image_t* dst)
{
    switch (dst->type) {
    case IMGTYPE_BASIC:
        convertToBasicImage(src, dst);
        break;
    case IMGTYPE_INT16:
        convertToInt16Image(src, dst);
        break;
    case IMGTYPE_FLOAT:
        convertToFloatImage(src, dst);
        break;
    case IMGTYPE_RGB888:
        convertToRGB888Image(src, dst);
        break;
    default:
        fprintf(stderr, "convertImage(): image type %d not supported\n", dst->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Contrast stretching
// ----------------------------------------------------------------------------

void contrastStretch(const image_t* src, image_t* dst, const int32_t bottom, const int32_t top)
{
    if (src->type != dst->type) {
        fprintf(stderr, "contrastStretch(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        contrastStretch_basic(src, dst, (basic_pixel_t)bottom, (basic_pixel_t)top);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "contrastStretch(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "contrastStretch(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void contrastStretchFast(const image_t* src, image_t* dst)
{
    switch (src->type) {
    case IMGTYPE_BASIC:
        contrastStretchFast_basic(src, dst);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "contrastStretchFast(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "contrastStretchFast(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void contrastStretchRGB888(const image_t* src, image_t* dst, const rgb888_pixel_t bottom, const rgb888_pixel_t top)
{
    if (src->type != dst->type) {
        fprintf(stderr, "contrastStretchRGB888(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_RGB888:
        contrastStretch_rgb888(src, dst, bottom, top);
        break;
    default:
        fprintf(stderr, "contrastStretchRGB888(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Rotation
// ----------------------------------------------------------------------------

void rotate180(const image_t* img)
{
    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*) = {
        rotate180_basic,
        //rotate180_int16,
        //rotate180_float,
        //rotate180_rgb888
    };

    // Call the function
    fp[img->type](img);
}

// ----------------------------------------------------------------------------
// Thresholding
// ----------------------------------------------------------------------------

void threshold(const image_t* src, image_t* dst, const int32_t low, const int32_t high)
{
    if (src->type != dst->type) {
        fprintf(stderr, "threshold(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        if (low < 0) {
            fprintf(stderr, "threshold(): low < 0 is invalid for IMGTYPE_BASIC\n");
        }

        if (high > 255) {
            fprintf(stderr, "threshold(): high > 255 is invalid for IMGTYPE_BASIC\n");
        }

        threshold_basic(src, dst, (basic_pixel_t)low, (basic_pixel_t)high);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "threshold(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888: {
        rgb888_pixel_t rgb888_low;
        rgb888_low.r = rgb888_low.g = rgb888_low.b = (unsigned char)low;
        rgb888_pixel_t rgb888_high;
        rgb888_high.r = rgb888_high.g = rgb888_high.b = (unsigned char)high;

        threshold_rgb888(src, dst, rgb888_low, rgb888_high);
    } break;
    default:
        fprintf(stderr, "threshold(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void threshold2Means(const image_t* src, image_t* dst, const eBrightness brightness)
{
    switch (src->type) {
    case IMGTYPE_BASIC:
        threshold2Means_basic(src, dst, brightness);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "threshold2Means(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "threshold2Means(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void thresholdOtsu(const image_t* src, image_t* dst, const eBrightness brightness)
{
    switch (src->type) {
    case IMGTYPE_BASIC:
        thresholdOtsu_basic(src, dst, brightness);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "thresholdOtsu(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "thresholdOtsu(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Miscellaneous
// ----------------------------------------------------------------------------

void erase(const image_t* img)
{
    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*) = {
        erase_basic,
        erase_int16,
        erase_float,
        erase_rgb888
    };

    // Call the function
    fp[img->type](img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void copy(const image_t* src, image_t* dst)
{
    if (src->type != dst->type) {
        fprintf(stderr, "copy(): src and dst are of different type\n");
    }

    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*, image_t*) = {
        copy_basic,
        copy_int16,
        copy_float,
        copy_rgb888
    };

    // Call the function
    fp[src->type](src, dst);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void setSelectedToValue(const image_t* src, image_t* dst, const int32_t selected, const int32_t value)
{
    if (src->type != dst->type) {
        fprintf(stderr, "setSelectedToValue(): src and dst are of different type\n");
    }
    switch (src->type) {
    case IMGTYPE_BASIC:
        setSelectedToValue_basic(src, dst, (basic_pixel_t)selected, (basic_pixel_t)value);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "setSelectedToValue(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "setSelectedToValue(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t neighbourCount(const image_t* img, const int32_t c, const int32_t r, const int32_t pixel, const eConnected connected)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        return neighbourCount_basic(img, c, r, (basic_pixel_t)pixel, connected);
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "neighbourCount(): image type %d not yet implemented\n", img->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "neighbourCount(): image type %d not supported\n", img->type);
        break;
    }

    return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void histogram(const image_t* img, uint16_t* hist)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        histogram_basic(img, hist);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "histogram(): image type %d not yet implemented\n", img->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "histogram(): image type %d not supported\n", img->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Arithmetic
// ----------------------------------------------------------------------------

void add(const image_t* src, image_t* dst)
{
    if (src->type != dst->type) {
        fprintf(stderr, "add(): src and dst are of different type\n");
    }

    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*, image_t*) = {
        add_basic,
        //add_int16,
        //add_float,
        //add_rgb888,
    };

    // Call the function
    fp[src->type](src, dst);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t sum(const image_t* img)
{
    // Build function call table
    // (make sure order matches the order in eImageType)
    uint32_t (*fp[])(const image_t*) = {
        sum_basic,
        //sum_int16,
        //sum_float,
        //sum_rgb888,
    };

    // Call the function
    return fp[img->type](img);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void multiply(const image_t* src, image_t* dst)
{
    if (src->type != dst->type) {
        fprintf(stderr, "multiply(): src and dst are of different type\n");
    }

    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*, image_t*) = {
        multiply_basic,
        //multiply_int16,
        //multiply_float,
        //multiply_rgb888,
    };

    // Call the function
    fp[src->type](src, dst);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void invert(const image_t* src, image_t* dst)
{
    if (src->type != dst->type) {
        fprintf(stderr, "invert(): src and dst are of different type\n");
    }

    // Build function call table
    // (make sure order matches the order in eImageType)
    void (*fp[])(const image_t*, image_t*) = {
        invert_basic,
        //invert_int16,
        //invert_float,
        //invert_rgb888,
    };

    // Call the function
    fp[src->type](src, dst);
}

// ----------------------------------------------------------------------------
// Filters
// ----------------------------------------------------------------------------

void nonlinearFilter(const image_t* src, image_t* dst, const eFilterOperation fo, const uint8_t n)
{
    switch (src->type) {
    case IMGTYPE_BASIC:
        nonlinearFilter_basic(src, dst, fo, n);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "nonlinearFilter(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "nonlinearFilter(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Binary
// ----------------------------------------------------------------------------

void removeBorderBlobs(const image_t* src, image_t* dst, const eConnected connected)
{
    if (src->type != dst->type) {
        fprintf(stderr, "removeBorderBlobs(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        removeBorderBlobs_basic(src, dst, connected);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "removeBorderBlobs(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "removeBorderBlobs(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void fillHoles(const image_t* src, image_t* dst, const eConnected connected)
{
    if (src->type != dst->type) {
        fprintf(stderr, "fillHoles(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        fillHoles_basic(src, dst, connected);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "fillHoles(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "fillHoles(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
uint32_t labelBlobs(const image_t* src, image_t* dst, const eConnected connected)
{
    if (src->type != dst->type) {
        fprintf(stderr, "labelBlobs(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        return labelBlobs_basic(src, dst, connected);
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "labelBlobs(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "labelBlobs(): image type %d not supported\n", src->type);
        break;
    }

    return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void binaryEdgeDetect(const image_t* src, image_t* dst, const eConnected connected)
{
    if (src->type != dst->type) {
        fprintf(stderr, "binaryEdgeDetect(): src and dst are of different type\n");
    }

    switch (src->type) {
    case IMGTYPE_BASIC:
        binaryEdgeDetect_basic(src, dst, connected);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "binaryEdgeDetect(): image type %d not yet implemented\n", src->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "binaryEdgeDetect(): image type %d not supported\n", src->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// Analysis
// ----------------------------------------------------------------------------

void blobAnalyse(const image_t* img, const uint8_t blobnr, blobinfo_t* blobInfo)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        blobAnalyse_basic(img, blobnr, blobInfo);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "blobAnalyse(): image type %d not yet implemented\n", img->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "blobAnalyse(): image type %d not supported\n", img->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void centroid(const image_t* img, const uint8_t blobnr, int32_t* cc, int32_t* rc)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        centroid_basic(img, blobnr, cc, rc);
        break;
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "centroid(): image type %d not yet implemented\n", img->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "centroid(): image type %d not supported\n", img->type);
        break;
    }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
float normalizedCentralMoments(const image_t* img, const uint8_t blobnr, const int32_t p, const int32_t q)
{
    switch (img->type) {
    case IMGTYPE_BASIC:
        return normalizedCentralMoments_basic(img, blobnr, p, q);
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
        fprintf(stderr, "normalizedCentralMoments(): image type %d not yet implemented\n", img->type);
        break;
    case IMGTYPE_RGB888:
    default:
        fprintf(stderr, "normalizedCentralMoments(): image type %d not supported\n", img->type);
        break;
    }

    return 0.0f;
}

// ----------------------------------------------------------------------------
// Custom operators
// ----------------------------------------------------------------------------
void warpPerspective(const image_t* img, image_t* dst, int32_t colpos[4], int32_t rowpos[4])
{
    switch (img->type) {
    case IMGTYPE_RGB888:
        warpPerspective_rgb888(img, dst, colpos, rowpos);
        break;
    case IMGTYPE_BASIC:
    case IMGTYPE_INT16:
    case IMGTYPE_FLOAT:
    default:
        fprintf(stderr, "warpPerspective(): image type %d not supported\n", img->type);
        break;
    }
}

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
