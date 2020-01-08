#ifndef HANDDETECTION_HPP
#define HANDDETECTION_HPP

#include "operators.h"

namespace cpparas {

const hsv_pixel_t HAND_THRESHOLD_LOW = {
    0, // H
    30, // S
    50 // V
};
const hsv_pixel_t HAND_THRESHOLD_HIGH = {
    25, // H
    50, // S
    80 // V
};
const uint32_t HAND_THRESHOLD_AREA = 10000;

class HandDetection {
public:
    HandDetection();
    void update(const image_t* image);
    void simulateHand(bool handPresent);
    bool containsHand() const;

private:
    bool handDetected;
    bool simulatedHandDetected;
};

} // namespace cpparas

#endif /* HANDDETECTION_HPP */
