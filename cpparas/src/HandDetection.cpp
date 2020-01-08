#include "HandDetection.hpp"
#include "operators_hsv.h"

namespace cpparas {

HandDetection::HandDetection()
    : handDetected(false)
    , simulatedHandDetected(false)
{
}

void HandDetection::update(const image_t* image)
{
    image_t* hsvImage = toHSVImage(image);
    image_t* thresholdedImage = newBasicImage(image->cols, image->rows);
    threshold_hsv(hsvImage, thresholdedImage, HAND_THRESHOLD_LOW, HAND_THRESHOLD_HIGH);
    pixel_t th;
    th.basic_pixel = 1;
    uint32_t count = pixelCount(thresholdedImage, th);
    handDetected = count >= HAND_THRESHOLD_AREA;
    deleteImage(hsvImage);
    deleteImage(thresholdedImage);
}

bool HandDetection::containsHand() const
{
    return handDetected || simulatedHandDetected;
}

void HandDetection::simulateHand(bool handPresent)
{
    simulatedHandDetected = handPresent;
}

} // namespace cpparas
