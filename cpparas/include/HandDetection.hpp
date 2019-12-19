#ifndef HANDDETECTION_HPP
#define HANDDETECTION_HPP

#include "operators.h"

class HandDetection {
public:
    HandDetection();
    void update(const image_t* image);
    bool containsHand() const;
    void simulateHand(bool handPresent);

private:
    bool handDetected;
    bool simulatedHandDetected;
};

#endif /* HANDDETECTION_HPP */
