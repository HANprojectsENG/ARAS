#include "HandDetection.hpp"

namespace cpparas {

HandDetection::HandDetection()
    : handDetected(false)
    , simulatedHandDetected(false)
{
}

void HandDetection::update(const image_t* image)
{
    (void)image;
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

} // namespace cpparas
