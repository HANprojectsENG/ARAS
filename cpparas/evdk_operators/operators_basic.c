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
#include "stdio.h"

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
    } break;
    case IMGTYPE_UINT16: {
        // Loop all pixels, convert and copy
        for (uint16_t r = 0; r < src->rows; r++) {
            for (uint16_t c = 0; c < src->cols; c++) {
                uint16_t temp = (getUInt16Pixel(src, c, r));
                setBasicPixel(dst, c, r, (uint8_t)(temp / 255));
            }
        }

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
void threshold_basic(const image_t* src, image_t* dst, const basic_pixel_t low, const basic_pixel_t high, const uint8_t output)
{
    uint16_t i;
    uint16_t x;
    basic_pixel_t pixel;
    for (x = 0; x < src->rows; x++) {
        for (i = 0; i < src->cols; i++) {
            pixel = getBasicPixel(src, i, x);
            if ((pixel >= low) && (pixel <= high)) {
                setBasicPixel(dst, i, x, (basic_pixel_t)0);
            } else {
                setBasicPixel(dst, i, x, output);
            }
        }
    }
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
    register basic_pixel_t* s = (basic_pixel_t*)src->data;
    register basic_pixel_t* d = (basic_pixel_t*)dst->data;
    register long int i = src->rows * src->cols;
    while (i-- != 0) {
        basic_pixel_t originalVal = *s++;
        *d++ = originalVal == selected ? value : originalVal;
    }
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
    uint16_t c;
    uint16_t r;
    uint16_t sum;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the multiple of src and dst pixel
            sum = getBasicPixel(src, c, r) + getBasicPixel(dst, c, r);
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst, c, r, sum);
        }
    }
    return;
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
    uint16_t c;
    uint16_t r;
    uint16_t sum;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the multiple of src and dst pixel
            sum = (getBasicPixel(src, c, r) * getBasicPixel(dst, c, r));
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst, c, r, sum);
        }
    }
    return;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void invert_basic(const image_t* src, image_t* dst)
{
    uint16_t c;
    uint16_t r;
    if (max_basic(src) > 1) {
        for (r = 0; r < src->rows; r++) {
            for (c = 0; c < src->cols; c++) {
                setBasicPixel(dst, c, r, 255 - getBasicPixel(src, c, r));
            }
        }
    } else {
        for (r = 0; r < src->rows; r++) {
            for (c = 0; c < src->cols; c++) {
                setBasicPixel(dst, c, r, 1 - getBasicPixel(src, c, r));
            }
        }
    }
    return;
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
    return;
}

void Corner_basic(const image_t* src, image_t* dst, const uint8_t blockSize, const uint8_t ksize, const float k, const uint8_t method)
{
    //method 0 = Harris
    //method 1 = Shi-Tomasi
    image_t* Ix = newBasicImage(src->cols, src->rows);
    image_t* Iy = newBasicImage(src->cols, src->rows);
    image_t* Ix2 = newUInt16Image(src->cols, src->rows);
    image_t* Iy2 = newUInt16Image(src->cols, src->rows);
    image_t* Ixy = newUInt16Image(src->cols, src->rows);
    image_t* mtrace = newFloatImage(src->cols, src->rows);

    uint32_t detM;
    float traceM;
    uint16_t c;
    uint16_t r;
    uint8_t max;
    uint32_t x2y2;
    uint32_t xy2;
    int32_t result;
    uint8_t corner[4] = { 0 };
    //find max value in image for scaling factor
    max = max_basic(src);

    //1. Calculate x and y derivative of image via sobel
    sobelX_basic(src, Ix); //input uint8 output uint8
    sobelY_basic(src, Iy); //input uint8 output uint8
    //2. Calculate three values in M
    //M = (x,y) [Ix * Ix     Ix * Iy]
    //   	    [Ix * Iy     Iy * Iy]
    power_uint16(Ix, Ix2, blockSize); //input uint8 output uint16
    power_uint16(Iy, Iy2, blockSize); //input uint8 output uint16
    multiply_basic_2(Ix, Iy, Ixy); //input uint8 output uint16
    //3. Apply Gaussian
    gaussian_uint16_x(Ix2, ksize); //input/output uint16
    gaussian_uint16_y(Iy2, ksize); //input/output uint16
    gaussian_uint16_xy(Ixy, ksize); //input/output uint16

    if (method == 0) { // Harris method
        /*R = score
        R = det(M) - k(trace(M))^2
        M = w(x,y) [Ix * Ix     Ix * Iy]
                   [Ix * Iy     Iy * Iy]
        R = score
        R = det(M) - k(trace(M))^2

        det(M) = ((Ix * Ix)𝜆) * ((Iy * Iy)𝜆) - (Ix*Iy * Ix*Iy)

        det(M) = 𝜆1 * 𝜆2
        trace(M) = 𝜆1 + 𝜆2
        𝜆1 and 𝜆2 are the eigen values of M

        When |R| is small, which is when 𝜆1 and 𝜆2 are small, region is flat
        when R < 0 which happens when 𝜆1 >> 𝜆2 or vice versa, region is edge
        When R is large, which happens when 𝜆1 and 𝜆2 are large, and 𝜆1 ~ 𝜆2, the region is a corner
        */
        //4. Calculate mtrace * K
        mtrace_basic(Ix2, Iy2, mtrace, k); //input uint16 output float
        //5. Calculate det(M), threshold result
        for (r = 0; r < src->rows - 0; r++) {
            for (c = 0; c < src->cols - 0; c++) {
                x2y2 = getUInt16Pixel(Ix2, c, r) * getUInt16Pixel(Iy2, c, r); //uint16 * uint16 = uint32
                xy2 = getUInt16Pixel(Ixy, c, r) * getUInt16Pixel(Ixy, c, r); //uint16 * uint16 = uint32
                result = x2y2 > xy2 ? xy2 : x2y2; //Find min value
                detM = x2y2 > xy2 ? x2y2 - xy2 : (xy2 - x2y2); //detM = abs value of x2y2 - xy2
                traceM = getFloatPixel(mtrace, c, r);
                result = detM - (uint32_t)traceM; //calculate result
                result = result < 0 ? 0 : result; //ignore negative results
                result = max > 2 ? result / 16581375 : result; //check if binary image, scale range down to 0-255

                if (corner[0] < result) {
                    corner[0] = result;
                    printf("Result1:%d\n", result);
                } //Find 4 max values in image
                else if (corner[1] < result) {
                    corner[1] = result;
                    printf("Result2:%d\n", result);
                } else if (corner[2] < result) {
                    corner[2] = result;
                    printf("Result3:%d\n", result);
                } else if (corner[3] < result) {
                    corner[3] = result;
                    printf("Result4:%d\n", result);
                }
                setBasicPixel(dst, c, r, result); //fill dst with R values;
            }
        }
        threshold_basic(dst, dst, corner[2], 255, 255); //threshold for highest R values
    } else if (method == 1) { // Shi-Tomasi method
        /*R = score
        R =  min(𝜆1,𝜆2)
        */
        for (r = 0; r < src->rows - 0; r++) {
            for (c = 0; c < src->cols - 0; c++) {
                x2y2 = getUInt16Pixel(Ix2, c, r) * getUInt16Pixel(Iy2, c, r); //uint16 * uint16 = uint32
                xy2 = getUInt16Pixel(Ixy, c, r) * getUInt16Pixel(Ixy, c, r); //uint16 * uint16 = uint32
                result = x2y2 > xy2 ? xy2 : x2y2; //Find min value
                result = max > 2 ? result / 16581375 : result;

                if (corner[0] < result) {
                    corner[0] = result;
                    printf("Result:%d\n", result);
                } //Find 4 max values in image
                else if (corner[1] < result) {
                    corner[1] = result;
                    printf("Result:%d\n", result);
                } else if (corner[2] < result) {
                    corner[2] = result;
                    printf("Result:%d\n", result);
                } else if (corner[3] < result) {
                    corner[3] = result;
                    printf("Result:%d\n", result);
                }
                setBasicPixel(dst, c, r, result);
            }
        }
        threshold_basic(dst, dst, corner[2], 255, 255); //threshold for highest R values
    }
    deleteImage(Ix);
    deleteImage(Iy);
    deleteImage(Ix2);
    deleteImage(Iy2);
    deleteImage(Ixy);
    deleteImage(mtrace);
    return;
}

uint8_t max_basic(const image_t* src)
{
    uint16_t c;
    uint16_t r;
    uint8_t max = 0;
    //Find max pixel value in image.
    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            max = max < getBasicPixel(src, c, r) ? getBasicPixel(src, c, r) : max;
        }
    }
    printf("Max:%d\n", max);
    return max;
}

void edge_basic(const image_t* src, image_t* dst, const uint8_t blockSize)
{
    uint16_t c;
    uint16_t r;
    int32_t sum_x, sum_y;
    double sum;

    //Cycle through all pixels in image excluding borders
    for (r = 1; r < src->rows - 1; r++) {
        for (c = 1; c < src->cols - 1; c++) {
            /*Apply sobel filter in x direction
            *+----+----+----+
            *| +1 | +2 | +1 |
            *+----+----+----+
            *|  0 |  0 |  0 |
            *+----+----+----+
            *| -1 | -2 | -1 |
            *+----+----+----+
            */
            sum_x = getBasicPixel(src, c - 1, r - 1) + (2 * getBasicPixel(src, c, r - 1)) + getBasicPixel(src, c + 1, r - 1) - getBasicPixel(src, c - 1, r + 1) - (2 * getBasicPixel(src, c, r + 1)) - getBasicPixel(src, c + 1, r + 1);

            /*Apply sobel filter in y direction
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            *| -2 |  0 | +2 |
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            */
            sum_y = getBasicPixel(src, c + 1, r - 1) + (2 * getBasicPixel(src, c + 1, r)) + getBasicPixel(src, c + 1, r + 1) - getBasicPixel(src, c - 1, r - 1) - (2 * getBasicPixel(src, c - 1, r)) - getBasicPixel(src, c - 1, r + 1);

            //power of n of both x and y results
            sum_x = pow(sum_x, blockSize);
            sum_y = pow(sum_y, blockSize);

            //Add sums together
            sum = sum_x + sum_y;

            //Take nth root of sum to get result
            sum = pow(sum, (1. / blockSize));

            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255.0 ? 255.0 : sum;
            setBasicPixel(dst, c, r, (uint8_t)sum);
        }
    }
    return;
}

void sobelX_basic(const image_t* src, image_t* dst)
{
    uint16_t c;
    uint16_t r;
    int32_t sum;

    //Cycle through all pixels in image excluding borders
    for (r = 1; r < src->rows - 1; r++) {
        for (c = 1; c < src->cols - 1; c++) {
            /*Apply sobel filter in x direction
            *+----+----+----+
            *| +1 | +2 | +1 |
            *+----+----+----+
            *|  0 |  0 |  0 |
            *+----+----+----+
            *| -1 | -2 | -1 |
            *+----+----+----+
            */
            sum = getBasicPixel(src, c - 1, r - 1) + (2 * getBasicPixel(src, c, r - 1)) + getBasicPixel(src, c + 1, r - 1) - getBasicPixel(src, c - 1, r + 1) - (2 * getBasicPixel(src, c, r + 1)) - getBasicPixel(src, c + 1, r + 1);
            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst, c, r, sum);
        }
    }
    return;
}

void sobelY_basic(const image_t* src, image_t* dst)
{
    uint16_t c;
    uint16_t r;
    int32_t sum;

    //Cycle through all pixels in image excluding borders
    for (r = 1; r < src->rows - 1; r++) {
        for (c = 1; c < src->cols - 1; c++) {
            /*Apply sobel filter in y direction
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            *| -2 |  0 | +2 |
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            */
            sum = getBasicPixel(src, c + 1, r - 1) + (2 * getBasicPixel(src, c + 1, r)) + getBasicPixel(src, c + 1, r + 1) - getBasicPixel(src, c - 1, r - 1) - (2 * getBasicPixel(src, c - 1, r)) - getBasicPixel(src, c - 1, r + 1);
            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst, c, r, sum);
        }
    }
    return;
}

void power_uint16(const image_t* src, image_t* dst, const uint8_t blockSize)
{
    uint16_t c;
    uint16_t r;
    double pix;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the power of blockSize
            pix = pow((double)getBasicPixel(src, c, r), (double)blockSize);
            setUInt16Pixel(dst, c, r, (uint16_t)pix);
        }
    }
    return;
}

void multiply_basic_2(const image_t* src, const image_t* src2, image_t* dst)
{
    uint16_t c;
    uint16_t r;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the multiple of src and dst pixel
            setUInt16Pixel(dst, c, r, (getBasicPixel(src, c, r) * getBasicPixel(src2, c, r)));
        }
    }
    return;
}

void subtract_basic(const image_t* src, image_t* dst)
{
    uint16_t c;
    uint16_t r;
    int16_t sum;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the multiple of src and dst pixel
            sum = (getBasicPixel(src, c, r) - getBasicPixel(dst, c, r));
            sum = sum < 0 ? 0 : sum;
            setBasicPixel(dst, c, r, sum);
        }
    }
    return;
}

//TODO ADD CHECK FOR KERNAL SIZE
void gaussian_uint16_x(image_t* src, const uint8_t ksize)
{
    //http://dev.theomader.com/gaussian-kernel-calculator/
    //coefficients of 1D gaussian kernel with sigma = 1
    double coeffs[] = { 0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059 };
    uint8_t offset = ksize / 2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
    float sum;
    uint16_t c;
    uint16_t r;
    image_t* temp_x = newUInt16Image(src->cols, src->rows);

    //Loop all pixels ignoring offset outside rows and cols
    //Maybe add mirror pixels for outside rows and cols
    for (r = offset; r < src->rows - offset; r++) {
        for (c = offset; c < src->cols - offset; c++) {
            sum = 0.0;
            for (int8_t i = -offset; i <= offset; i++) {
                //ksize 3 range(-1,1)   coeffs[2,3,4]
                //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                sum = sum + coeffs[i + 3] * getUInt16Pixel(src, (c + i), r);
            }
            setUInt16Pixel(temp_x, c, r, (uint16_t)sum);
        }
    }
    copy(temp_x, src);
    deleteImage(temp_x);
    return;
}

void gaussian_uint16_y(image_t* src, const uint8_t ksize)
{
    //coefficients of 1D gaussian kernel with sigma = 1
    //http://dev.theomader.com/gaussian-kernel-calculator/
    double coeffs[] = { 0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059 };
    uint8_t offset = ksize / 2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
    float sum;
    uint16_t c;
    uint16_t r;
    image_t* temp_y = newUInt16Image(src->cols, src->rows);

    //Loop all pixels ignoring offset outside rows and cols
    //Maybe add mirror pixels for outside rows and cols
    for (r = offset; r < src->rows - offset; r++) {
        for (c = offset; c < src->cols - offset; c++) {
            sum = 0.0;
            for (int8_t i = -offset; i <= offset; i++) {
                //ksize 3 range(-1,1)   coeffs[2,3,4]
                //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                sum = sum + coeffs[i + 3] * getUInt16Pixel(src, c, (r + i));
            }
            setUInt16Pixel(temp_y, c, r, sum);
        }
    }
    copy(temp_y, src);
    deleteImage(temp_y);
    return;
}

void gaussian_uint16_xy(image_t* src, const uint8_t ksize)
{
    //coefficients of 1D gaussian kernel with sigma = 1
    //http://dev.theomader.com/gaussian-kernel-calculator/
    double coeffs[] = { 0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059 };
    uint8_t offset = ksize / 2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
    float sum;
    uint16_t c;
    uint16_t r;
    image_t* temp_x = newUInt16Image(src->cols, src->rows);

    //Loop all pixels ignoring offset outside rows and cols
    //Maybe add mirror pixels for outside rows and cols
    for (r = offset; r < src->rows - offset; r++) {
        for (c = offset; c < src->cols - offset; c++) {
            //loop through gaussian filter
            sum = 0.0;
            for (int8_t r2 = -offset; r2 <= offset; r2++) {
                for (int8_t c2 = -offset; c2 <= offset; c2++) {
                    //ksize 3 range(-1,1)   coeffs[2,3,4]
                    //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                    //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                    //Take coeffs in both x and y direction.
                    sum = sum + (coeffs[r2 + 3] * coeffs[c2 + 3] * getUInt16Pixel(src, c + c2, r + r2));
                }
            }
            setUInt16Pixel(temp_x, c, r, sum);
        }
    }
    copy(temp_x, src);
    deleteImage(temp_x);
    return;
}

void mtrace_basic(const image_t* src, const image_t* src2, image_t* dst, const float k)
{
    //Calulate mtrace * K
    //((Ix2 + Iy2) ^ 2 ) * K
    uint16_t c;
    uint16_t r;
    uint16_t temp;
    float temp2;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            temp = getBasicPixel(src, c, r) + getBasicPixel(src2, c, r);
            temp2 = pow((double)temp, 2.0) * k;
            setFloatPixel(dst, c, r, temp2);
        }
    }
}

void crop_basic(const image_t* img, image_t* dst, int32_t top_left[2])
{
    if (top_left[0] >= img->cols || top_left[1] >= img->rows
        || top_left[0] + dst->cols <= 0 || top_left[1] + dst->cols <= 0) {
        // Cropping region is outside of the input image.
        return;
    }

    // Start is inclusive, end is exclusive.
    int32_t destStartCol = top_left[0] >= 0 ? 0 : -top_left[0];
    int32_t destStartRow = top_left[1] >= 0 ? 0 : -top_left[1];
    int32_t destEndCol = top_left[0] + dst->cols < img->cols ? dst->cols : (dst->cols - (top_left[0] + dst->cols - img->cols));
    int32_t destEndRow = top_left[1] + dst->rows < img->rows ? dst->rows : (dst->rows - (top_left[1] + dst->rows - img->rows));

    for (int32_t row = destStartRow; row < destEndRow; row++) {
        for (int32_t col = destStartCol; col < destEndCol; col++) {
            setBasicPixel(dst, col, row, getBasicPixel((image_t*)img, top_left[0] + col, top_left[1] + row));
        }
    }
}

void binaryErode_basic(const image_t* src, image_t* dst, uint8_t kernelSize)
{
    typedef uint64_t batch_t;
    int32_t batchSize = sizeof(batch_t);
    if (kernelSize > batchSize) {
        // Not implemented.
        return;
    }

    int32_t kernelOffset = kernelSize / 2;
    batch_t batchMask = 0;
    for (batch_t i = 0; i < kernelSize; i++) {
        batchMask |= 1ULL << (i * 8ULL);
    }

    for (int32_t row = 0; row < src->rows; row++) {
        for (int32_t col = 0; col < src->cols; col++) {
            if (row < batchSize || row >= src->rows - batchSize
                || col < batchSize || col >= src->cols - batchSize) {
                // Don't attempt erosion on edge pixels.
                setBasicPixel(dst, col, row, getBasicPixel(src, col, row));
                continue;
            }

            basic_pixel_t result = 1;
            for (int32_t innerRow = row - kernelOffset; innerRow < row - kernelOffset + kernelSize; innerRow++) {
                batch_t batch = *(batch_t*)(((basic_pixel_t*)src->data) + (innerRow * src->cols + col - kernelOffset));
                if ((batch & batchMask) != batchMask) {
                    result = 0;
                    break;
                }
            }
            setBasicPixel(dst, col, row, result);
        }
    }
}

uint32_t pixelCount_basic(const image_t* img, const basic_pixel_t value)
{
    uint32_t count = 0;
    register basic_pixel_t* s = (basic_pixel_t*)img->data;
    register long int i = img->rows * img->cols;
    while (i-- != 0) {
        if (*s++ == value) {
            count++;
        }
    }
    return count;
}

// ----------------------------------------------------------------------------
// EOF
// ----------------------------------------------------------------------------
