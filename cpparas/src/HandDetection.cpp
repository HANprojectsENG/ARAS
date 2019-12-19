#include "HandDetection.hpp"

HandDetection::HandDetection()
    : handDetected(false)
    , simulatedHandDetected(false)
{
}

void HandDetection::update(const image_t* image)
{
    // TODO: Detect hand presence.
    handDetected = false;
}

bool HandDetection::containsHand() const
{
    return handDetected || simulatedHandDetected;
}

void HandDetection::simulateHand(bool handPresent)
{
    simulatedHandDetected = handPresent;
}
