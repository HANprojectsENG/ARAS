#ifndef HANDDETECTION_HPP
#define HANDDETECTION_HPP

#include "operators.h"

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

#endif /* HANDDETECTION_HPP */
