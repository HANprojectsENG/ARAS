#ifndef HANDDETECTION_HPP
#define HANDDETECTION_HPP

#include "operators.h"

namespace cpparas {

const hsv_pixel_t HAND_THRESHOLD_LOW = {
    0, // H
    25, // S
    50 // V
};
const hsv_pixel_t HAND_THRESHOLD_HIGH = {
    25, // H
    50, // S
    90 // V
};
const uint32_t HAND_THRESHOLD_AREA = 10000;

class HandDetection {
public:
    /**
     * @brief Creates a hand detection checker.
     */
    HandDetection();
    /**
     * @brief Runs the hand detection on the given image.
     */
    void update(const image_t* image);
    /**
     * @brief Sets whether a simulated hand is present.
     */
    void simulateHand(bool handPresent);
    /**
     * @brief Returns whether a hand was detected on the previous .update
     *        or if a simulated hand is present.
     */
    bool containsHand() const;

private:
    bool handDetected;
    bool simulatedHandDetected;
};

} // namespace cpparas

#endif /* HANDDETECTION_HPP */
