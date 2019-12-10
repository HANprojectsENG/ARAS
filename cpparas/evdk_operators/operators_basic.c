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
    uint16_t i;
    uint16_t x;
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
        sum = (getBasicPixel(src,c,r) * getBasicPixel(dst,c,r));
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
    return;
}

void harrisCorner_basic(const image_t* src, image_t* dst, const uint8_t blockSize, const uint8_t ksize, const double k){
    
    image_t* der_x = newBasicImage(src->cols, src->rows);
    image_t* der_y = newBasicImage(src->cols, src->rows);
    image_t* der_x2 = newUInt16Image(src->cols, src->rows);
    image_t* der_y2 = newUInt16Image(src->cols, src->rows);
    image_t* der_xy = newUInt16Image(src->cols, src->rows);
    image_t* der_x2y2 = newBasicImage(src->cols, src->rows);
    image_t* mtrace = newBasicImage(src->cols, src->rows);
    basic_pixel_t temp;
    basic_pixel_t temp2;


    //Testing
    edge_basic(src,dst,blockSize);
    //gaussian_basic_xy(dst,ksize);

    //1. Calculate x and y derivative of image via sobel
    sobelX_basic(src,der_x);
    sobelY_basic(src,der_y);
    //2. Calculate other three images in M
    power_uint16(der_x, der_x2, blockSize); //der_x^2
    power_uint16(der_y, der_y2, blockSize); //der_y^2
    multiply_basic_2(der_x, der_y, der_xy); //der_x * der_y
    //3. Apply Gaussian
    gaussian_uint16_x(der_x2,ksize);
    gaussian_uint16_y(der_y2,ksize);
    gaussian_uint16_xy(der_xy,ksize);
    //4. Calulate R with K
    multiply_basic_2(der_x2,der_y2,der_x2y2);
    multiply_basic(der_xy,der_xy);
    
    //
    add_basic(der_x2,der_y2);
    subtract_basic(der_x2y2,der_xy);
    power_uint16(der_y2,mtrace,blockSize);

    //Multiply mtrace by k
    for (uint16_t r = 0; r < dst->rows; r++) {
        for (uint16_t c = 0; c < dst->cols; c++) {
            temp = getBasicPixel(mtrace,c,r);
            temp2 = temp * k;
            setBasicPixel(mtrace, c, r, temp2);
        }
    }

    //
    subtract_basic(der_xy,mtrace);
    //copy_basic(mtrace,dst);

    //5. Temp print results
    //Test every step next
    //TODO ADD CHECK FOR KERNAL SIZE in gauss filter
    return;
}

void edge_basic(const image_t* src, image_t* dst, const uint8_t blockSize){
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
            sum_x = getBasicPixel(src,c - 1,r - 1) + 
            (2 * getBasicPixel(src,c,r - 1)) +
            getBasicPixel(src,c + 1,r - 1) -
            getBasicPixel(src,c - 1,r + 1) -
            (2 * getBasicPixel(src,c ,r + 1)) -
            getBasicPixel(src,c + 1,r + 1);

            /*Apply sobel filter in y direction
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            *| -2 |  0 | +2 |
            *+----+----+----+
            *| -1 |  0 | +1 |
            *+----+----+----+
            */
            sum_y = getBasicPixel(src,c + 1,r - 1) + 
            (2 * getBasicPixel(src,c + 1,r)) +
            getBasicPixel(src,c + 1,r + 1) -
            getBasicPixel(src,c - 1,r - 1) -
            (2 * getBasicPixel(src,c - 1 ,r)) -
            getBasicPixel(src,c - 1,r + 1);

            //power of n of both x and y results
            sum_x = pow(sum_x, blockSize);
            sum_y = pow(sum_y, blockSize);

            //Add sums together
            sum = sum_x + sum_y;

            //Take nth root of sum to get result
            sum = pow(sum, (1./blockSize));

            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255.0 ? 255.0 : sum;
            setBasicPixel(dst,c, r, (uint8_t)sum);            
        }
    }
    return;
}
void sobelX_basic(const image_t* src, image_t* dst){
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
            sum = getBasicPixel(src,c - 1,r - 1) + 
            (2 * getBasicPixel(src,c,r - 1)) +
            getBasicPixel(src,c + 1,r - 1) -
            getBasicPixel(src,c - 1,r + 1) -
            (2 * getBasicPixel(src,c ,r + 1)) -
            getBasicPixel(src,c + 1,r + 1);
            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst,c, r, sum);
        }
    }
    return;
}

void sobelY_basic(const image_t* src, image_t* dst){
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
            sum = getBasicPixel(src,c + 1,r - 1) + 
            (2 * getBasicPixel(src,c + 1,r)) +
            getBasicPixel(src,c + 1,r + 1) -
            getBasicPixel(src,c - 1,r - 1) -
            (2 * getBasicPixel(src,c - 1 ,r)) -
            getBasicPixel(src,c - 1,r + 1);
            sum = sum < 0.0 ? (0 - sum) : sum;
            sum = sum > 255 ? 255 : sum;
            setBasicPixel(dst,c, r, sum);
        }
    }
    return;
}

void power_uint16(const image_t* src,image_t* dst, const uint8_t blockSize){
    uint16_t c;
    uint16_t r;

    //Cycle through all pixels in image
    for (r = 0; r < src->rows; r++) {
        for (c = 0; c < src->cols; c++) {
            //Set every pixel to the power of blockSize    
            setUInt16Pixel(dst, c, r, pow(getUInt16Pixel(src,c,r),blockSize));
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
        setUInt16Pixel(dst, c, r, (getBasicPixel(src,c,r) * getBasicPixel(src2,c,r)));
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
        sum = (getBasicPixel(src,c,r) - getBasicPixel(dst,c,r));
        sum = sum < 0 ? 0 : sum;    
        setBasicPixel(dst, c, r, sum);
        }
    }
    return;
}

//TODO ADD CHECK FOR KERNAL SIZE
void gaussian_uint16_x(image_t* src, const uint8_t ksize){
    //http://dev.theomader.com/gaussian-kernel-calculator/
    //coefficients of 1D gaussian kernel with sigma = 1
    double coeffs[] = {0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059}; 
    uint8_t offset = ksize/2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
    float sum;
    uint16_t c;
    uint16_t r;
    image_t* temp_x = newUInt16Image(src->cols, src->rows);

    //Loop all pixels ignoring offset outside rows and cols
    //Maybe add mirror pixels for outside rows and cols
    for (r = offset; r < src->rows - offset; r++) {
        for (c = offset; c < src->cols - offset; c++) {
                sum = 0.0;
                for (int8_t i = -offset; i <= offset; i++){
                    //ksize 3 range(-1,1)   coeffs[2,3,4]
                    //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                    //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                    sum = sum + coeffs[i + 3] * getUInt16Pixel(src,(c + i),r);
                }
                setUInt16Pixel(temp_x,c,r,(uint16_t)sum);
        }
    }
    copy(temp_x,src);
    return;
}

void gaussian_uint16_y(image_t* src, const uint8_t ksize){
    //coefficients of 1D gaussian kernel with sigma = 1
    //http://dev.theomader.com/gaussian-kernel-calculator/
    double coeffs[] = {0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059}; 
    uint8_t offset = ksize/2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
    float sum;
    uint16_t c;
    uint16_t r;
    image_t* temp_x = newUInt16Image(src->cols, src->rows);

    //Loop all pixels ignoring offset outside rows and cols
    //Maybe add mirror pixels for outside rows and cols
    for (r = offset; r < src->rows - offset; r++) {
        for (c = offset; c < src->cols - offset; c++) {
                sum = 0.0;
                for (int8_t i = -offset; i <= offset; i++){
                    //ksize 3 range(-1,1)   coeffs[2,3,4]
                    //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                    //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                    sum = sum + coeffs[i + 3] * getUInt16Pixel(src,c,(r + i));
                }
                setUInt16Pixel(temp_x,c,r,sum);
        }
    }
    copy(temp_x,src);  
    return;
}

void gaussian_uint16_xy(image_t* src, const uint8_t ksize){
    //coefficients of 1D gaussian kernel with sigma = 1
    //http://dev.theomader.com/gaussian-kernel-calculator/
    double coeffs[] = {0.0059, 0.06062, 0.24184, 0.38310, 0.24184, 0.06062, 0.0059}; 
    uint8_t offset = ksize/2; //offset for finding pixel offset in kernal is ksize/2 rounded down to int
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
                for (int8_t r2 = -offset; r2 <= offset; r2++){
                    for (int8_t c2 = -offset; c2 <= offset; c2++){
                        //ksize 3 range(-1,1)   coeffs[2,3,4]
                        //ksize 5 range(-2,2)   coeffs[1,2,3,4,5]
                        //ksize 7 range(-3,3)   coeffs[0,1,2,3,4,5,6]
                        //Take coeffs in both x and y direction. 
                        sum = sum + (coeffs[r2 + 3] * coeffs[c2 + 3] * getUInt16Pixel(src,c + c2,r + r2));
                    }
                }
                setUInt16Pixel(temp_x,c,r,sum);
        }
    }
    copy(temp_x,src); 
    return; 
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
